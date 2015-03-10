#include <QDesktopWidget>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QWebPage>
#include <QWebFrame>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QFileSystemModel>
#include <QProcess>
#include <QMessageBox>
#include <QEvent>
#include <QSignalMapper>
#include <QMouseEvent>
#include <QIcon>
#include <QSplitter>

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsmanager.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow), model(new QFileSystemModel(this)), analyzer(0), dupesAnalyzer(0){

    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    qRegisterMetaType<DirectoryEntriesList>("DirectoryEntriesList");
    qRegisterMetaType<DirectoryEntry>("DirectoryEntry");
    qRegisterMetaType<DuplicateEntryList>("DuplicateEntryList");
    qRegisterMetaType<AnalysisTarget>("AnalysisTarget");

    ui->setupUi(this);

    QSplitter *splitter = new QSplitter(this);
    splitter->addWidget(ui->twgDirViewer);
    splitter->addWidget(ui->tbsMain);
    setCentralWidget(splitter);
    ui->tbsMain->setCurrentIndex(0);

    ui->twgDirViewer->setModel(model);
    setCurrentPath(QDir::homePath ());
    ui->twgDirViewer->hideColumn(1);
    ui->twgDirViewer->hideColumn(3);
    centerWindow();

    setWindowState(Qt::WindowMaximized);
    centerWindow();
    statusBar()->setSizeGripEnabled(false);

    visFrame = ui->wvwCharts->page()->mainFrame();
    statFrame = ui->wvwStatistics->page()->mainFrame();

   // ui->wvwCharts->setContextMenuPolicy(Qt::NoContextMenu);
    ui->wvwCharts->setUrl(QUrl("qrc:/charts/Charts/index.html"));
    ui->wvwStatistics->setUrl(QUrl("qrc:/charts/Charts/barchart.html"));

    //visFrame->setScrollBarValue(Qt::Vertical, visFrame->scrollBarMaximum(Qt::Vertical));
    //visFrame->setScrollBarValue(Qt::Horizontal, visFrame->scrollBarMaximum(Qt::Horizontal));
    visFrame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    //visFrame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    statFrame->setScrollBarValue(Qt::Vertical, visFrame->scrollBarMaximum(Qt::Vertical));
    //statFrame->setScrollBarValue(Qt::Horizontal, visFrame->scrollBarMaximum(Qt::Horizontal));
    statFrame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    //statFrame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    connect(visFrame, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(exposeObjectsToJS()));
    settingsDialog = 0;
    statDialog = 0;
    dupesDialog = 0;
    progress = 0;
    aboutDialog = 0;

    ui->twgDirViewer->setRootIsDecorated(true);
    QObject::connect(ui->twgDirViewer, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeMenuRequested(QPoint)), Qt::UniqueConnection);
    ui->twgDirViewer->setContextMenuPolicy(Qt::CustomContextMenu);

}


MainWindow::~MainWindow(){
    analysisThread.quit();
    analysisThread.wait();
    dupesCheckerThread.quit();
    dupesCheckerThread.wait();
    dupesHashingThread.quit();
    dupesHashingThread.wait();
    delete ui;
}

bool MainWindow::eventFilter(QObject *o, QEvent *e){
    return QMainWindow::eventFilter(o, e);
}

void MainWindow::analyzeDirectory(QString path){
    QFileInfo fileInfo(path);
    if (fileInfo.isDir()){
        QString directory =fileInfo.absoluteDir().absolutePath();
        if (directory != QDir::rootPath() && !directory.endsWith("/"))
            directory.append("/");
        QString fileName = fileInfo.baseName();
        setCurrentDUA(directory + fileName);
        setDirectoryJson(directory, fileName);
    }

}

void MainWindow::launchTerminal(QString path){
    if(path.trimmed().isEmpty())
        return;

    QFileInfo pathInfo(path);
    if(!pathInfo.isDir()){
        QMessageBox::critical(this, "Error", "Invalid directory " + path);
        return;
    }

    QString terminal(qgetenv("TERM"));

    if (terminal.trimmed().isEmpty()){
        QMessageBox::critical(this, "Error", "The terminal environment variable $TERM is not set");
        return;
    }else{
        QProcess *terminalProcess = new QProcess(this);
        QString option("-e");
        QString argument(QString("cd ") + path + " && /bin/bash");
        QStringList arguments;
        arguments << option << argument;
        terminalProcess->start(terminal, arguments);
    }
}

void MainWindow::launchDupeChecker(QString path){
    if (path.trimmed().isEmpty()){
        QMessageBox::critical(this, "Error", "You need to open a directory first");
        return;
    }

    dupCheckDUA = path;
    if (dupCheckDUA.endsWith("/") && dupCheckDUA != QDir::rootPath())
        dupCheckDUA.remove(dupCheckDUA.length() - 1, 1);
    QDir currentDir(dupCheckDUA);
    QFileInfo pathInfo(dupCheckDUA);
    QString fileName = pathInfo.baseName();

    QString directory;
    if (currentDir.isRoot())
        directory = "";
    else
        directory = pathInfo.absolutePath() + QString("/");

    stopDupesAnalyzer();
    dupesAnalyzer = new DirectoryAnalyzer;
    dupesAnalyzer->moveToThread(&dupesCheckerThread);
    connect(&dupesCheckerThread, SIGNAL(finished()), dupesAnalyzer, SLOT(deleteLater()));
    connect(this, SIGNAL(startScanning(QString,QString,int, AnalysisTarget)), dupesAnalyzer, SLOT(startAnalysis(QString,QString,int, AnalysisTarget)));
    connect(dupesAnalyzer, SIGNAL(analysisComplete(AnalysisTarget)), this, SLOT(scanComplete()));
    connect(this, SIGNAL(stopScanning(bool)), dupesAnalyzer, SLOT(setStopped(bool)), Qt::DirectConnection);
    emit stopScanning(false);
    dupesCheckerThread.start();
    qDebug() << "Thread running? " << dupesCheckerThread.isRunning();


    qDebug() << "Scanning..";
    emit startScanning(directory, fileName, 0, DupeChecking);
}

void MainWindow::exposeObjectsToJS(){
    visFrame->addToJavaScriptWindowObject(QString("mainWindow"), this, QWebFrame::ScriptOwnership);
}

void MainWindow::setCurrentPath(QString newPath){
    if (!QFileInfo(newPath).isDir()){
        QMessageBox::critical(this, "Error", "Invalid directory " + newPath);
        return;
    }

    currentPath = newPath;
    if (newPath == QDir::rootPath()){
        model->setRootPath("/");
        QModelIndex rootIndex = model->index("");
        ui->twgDirViewer->setRootIndex(rootIndex);
    }else{
        model->setRootPath(newPath);
        QModelIndex rootIndex = model->index(newPath);
        ui->twgDirViewer->setRootIndex(rootIndex);
    }

}

void MainWindow::centerWindow(){
    QDesktopWidget *desktop = QApplication::desktop();

    int screenWidth, width;
    int screenHeight, height;
    int x, y;
    QSize windowSize;

    screenWidth = desktop->width();
    screenHeight = desktop->height();

    windowSize = size();
    width = windowSize.width();
    height = windowSize.height();

    x = (screenWidth - width) / 2;
    y = (screenHeight - height) / 2;
    y -= 50;

    move ( x, y );
}

void MainWindow::stopAnalyzer(){
    if (analysisThread.isRunning()){
        qDebug() << "Terminating";
        emit stopAnalysis(true);
        analysisThread.quit();
        analysisThread.wait();
        qDebug() << "Terminated";
    }
}

void MainWindow::stopDupesAnalyzer(){
    if (dupesCheckerThread.isRunning()){
        qDebug() << "Terminating";
        emit stopScanning(true);
        dupesCheckerThread.quit();
        dupesCheckerThread.wait();
        qDebug() << "Terminated";
        stopDupesChecking();
    }
}

void MainWindow::stopDupesChecking(){
    if(dupesHashingThread.isRunning()){
        qDebug() << "Terminating";
        emit stopHashing(true);
        dupesHashingThread.quit();
        dupesHashingThread.wait();
        qDebug() << "Terminated";
        progress->hide();
    }
}

void MainWindow::onDupesProgress(int value){
    progress->setValue(value);
}

void MainWindow::openDirectory(QString path){
    openDirectory(path, this);
}

void MainWindow::statFile(QString path){
    QFileInfo pathInfo(path);
    if (!pathInfo.exists() || !pathInfo.isReadable())
        return;

    struct stat sb;
    printf("Test");

    if (stat(pathInfo.absoluteFilePath().toLocal8Bit().data(), &sb) == -1) {
        qDebug() << "Stat error";
        return;
    }

    QString fileType;
    switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  fileType = "Block Device";       break;
    case S_IFCHR:  fileType = "Character Device";   break;
    case S_IFDIR:  fileType = "Directory";          break;
    case S_IFIFO:  fileType = "FIFO/pipe";          break;
    case S_IFLNK:  fileType = "System Link";        break;
    case S_IFREG:  fileType = "Regular File";       break;
    case S_IFSOCK: fileType = "Socket";             break;
    default:       fileType = "Unknown";            break;
    }

    QString mode;
    if(sb.st_mode &  S_IRUSR ) mode.append("r"); else mode.append("-");
    if(sb.st_mode &  S_IWUSR ) mode.append("w"); else mode.append("-");
    if(sb.st_mode &  S_IXUSR ) mode.append("x"); else mode.append("-");
    if(sb.st_mode &  S_IRGRP ) mode.append("r"); else mode.append("-");
    if(sb.st_mode &  S_IWGRP ) mode.append("w"); else mode.append("-");
    if(sb.st_mode &  S_IXGRP ) mode.append("x"); else mode.append("-");
    if(sb.st_mode &  S_IROTH ) mode.append("r"); else mode.append("-");
    if(sb.st_mode &  S_IWOTH ) mode.append("w"); else mode.append("-");
    if(sb.st_mode &  S_IXOTH ) mode.append("x"); else mode.append("-");

    long inodeNumber = (long) sb.st_ino;
    long linkCount = (long) sb.st_nlink;
    long uid = (long) sb.st_uid;
    long gid = (long) sb.st_gid;
    QString uname(getpwuid(sb.st_uid)->pw_name);
    QString gname(getgrgid(sb.st_gid)->gr_name);
    long preferredIOSize = (long) sb.st_blksize;
    long fileSize = (long long) sb.st_size;
    long long blocks = (long long) sb.st_blocks;
    QString lastStatusChange(ctime(&sb.st_ctime));
    QString lastFileAccess(ctime(&sb.st_atime));
    QString lastFileModification(ctime(&sb.st_mtime));

    if(!statDialog)
        statDialog = new FileStatDialog(this);

    statDialog->setFileName(pathInfo.baseName())->setFileExtenstion(pathInfo.completeSuffix())->setFilePath(pathInfo.absolutePath())
            ->setFileType(fileType)->setInodeNumber(inodeNumber)
            ->setMode(mode)->setLinkCount(linkCount)->setPreferredIOSize(preferredIOSize)
            ->setOwnership(uname + "(" + QString::number(uid) + "):" + gname + "(" + QString::number(gid) + ")")
            ->setSize(fileSize)->setNumberOfBlocks(blocks)->setLastStatusChange(lastStatusChange)
            ->setLastFileAccess(lastFileAccess)->setLastModification(lastFileModification);
    statDialog->setWindowTitle("File Status: " + pathInfo.baseName());
    statDialog->show();
    statDialog->setModal(true);

}

void MainWindow::setDirectoryJson(QString dirStr, QString nodeName)
{
    stopAnalyzer();
    analyzer = new DirectoryAnalyzer;
    analyzer->moveToThread(&analysisThread);
    connect(&analysisThread, SIGNAL(finished()), analyzer, SLOT(deleteLater()));
    connect(this, SIGNAL(startAnalysis(QString,QString,int, AnalysisTarget)), analyzer, SLOT(startAnalysis(QString, QString, int, AnalysisTarget)));
    connect(analyzer, SIGNAL(analysisComplete(AnalysisTarget)), this, SLOT(analysisComplete(AnalysisTarget)));
    connect(this, SIGNAL(stopAnalysis(bool)), analyzer, SLOT(setStopped(bool)), Qt::DirectConnection);
    emit stopAnalysis(false);
    analysisThread.start();
    qDebug() << "Thread running? " << analysisThread.isRunning();


    qDebug() << "Analyzing..";
    if (SettingsManager::getListEntriesByBlocks())
        emit startAnalysis(dirStr, nodeName, 0, BlockVisualization);
    else
        emit startAnalysis(dirStr, nodeName, 0, SizeVisualization);

}

void MainWindow::navigateTo(QString path){
    if(path.isEmpty())
        return;
    if (path.startsWith("/"))
        path.remove(0, 1);

    if (path.endsWith("/"))
        path.remove(path.length() - 1, 1);

    tempNavigationPath = path;

    QString fullPath = getCurrentDUA();
    QFileInfo pathInfo(fullPath);
    if(pathInfo.isDir()){

    }else if(pathInfo.exists()){
        statFile(pathInfo.canonicalFilePath());
    }else{
        qDebug() << pathInfo.absoluteFilePath() << " does not exist";
    }
}

QString MainWindow::getCurrentDUA() const{
    return currentDUA + tempNavigationPath;
}

void MainWindow::setCurrentDUA(const QString &value){
    currentDUA = value;
    tempNavigationPath = "";
    if (!value.endsWith("/") && !(value == "/"))
        currentDUA.append("/");
}

void MainWindow::openDirectory(QString path, QWidget *parent){
    if(path.isEmpty())
        return;
    QFileInfo pathInfo(path);
    if(!pathInfo.isDir()){
        QMessageBox::critical(parent, "Error", "Invalid directory " + path);
        return;
    }

    QProcess *fileManagerProcess = new QProcess(parent);
    QStringList arguments;
    arguments << path;
    fileManagerProcess->start("xdg-open", arguments);
}

void MainWindow::on_actionAnalyzeDirectory_triggered(){
    QModelIndex index = ui->twgDirViewer->currentIndex();
    if (index.isValid())
        on_twgDirViewer_doubleClicked(index);
}

void MainWindow::on_twgDirViewer_doubleClicked(const QModelIndex &index){
    if (!index.isValid())
        return;
    if(model->isDir(index)){
        analyzeDirectory(model->fileInfo(index).canonicalFilePath());
    }else if (model->fileInfo(index).isReadable())
        statFile(model->fileInfo(index).canonicalFilePath());
}

void MainWindow::on_twgDirViewer_expanded(const QModelIndex &){
    ui->twgDirViewer->resizeColumnToContents(0);
}

void MainWindow::on_actionRefresh_triggered(){
    model->setRootPath("");
    setCurrentPath(currentPath);
}

void MainWindow::analysisComplete(AnalysisTarget target){
    qDebug() << "Analysis complete: " << target;
    if (analyzer->getAnalysisDone()){
        QList<DirectoryEntry *> entries = analyzer->getEntries();
        qDebug() << "Analyzed..";
        if (target == SizeVisualization){
             qDebug() << "Listing by size";
            DirectoryEntry *rootEntry = analyzer->getRoot();
            QString entriesJson = DirectoryAnalyzer::getEntriesJsonString(rootEntry);
            QString jsCommand = QString("visualize(") + entriesJson + QString("); null");
            visFrame->evaluateJavaScript(jsCommand);
            passGraphParamters();
        }else if (target == BlockVisualization){
            qDebug() << "Listing by blocks";
            DirectoryEntry *rootEntry = analyzer->getRoot();
            QString entriesJson = DirectoryAnalyzer::getEntriesJsonStringByBlock(rootEntry);
            QString jsCommand = QString("visualize(") + entriesJson + QString("); null");
            visFrame->evaluateJavaScript(jsCommand);
            passGraphParamters(false);
        }else{
            qSort(entries.begin(), entries.end(), DirectoryEntry::isLessThan);
            qDebug() << "Largest entry" << entries[0]->getFormattedSize(entries[0]->getTotalSize());
        }
        if (target != DupeChecking)
            setWindowTitle(QString("Disk Analyst - ") + currentDUA + (tempNavigationPath.trimmed().isEmpty()? "" : "[" + tempNavigationPath.trimmed() + "]"));
    }
}

void MainWindow::scanComplete(){
    qDebug() << "Done initial scanning";
    if (dupesAnalyzer->getAnalysisDone()){

        if(!progress){
            progress = new CustomProgressBar(this);
            statusBar()->addWidget(progress);
            progress->setDescription("(Double-click here to cancel duplicate checker)");
            connect(progress, SIGNAL(doubleClicked()), this, SLOT(stopDupesChecking()));

        }

        progress->setValue(0);
        progress->show();

        stopDupesChecking();
        dupesChecker = new DupesChecker;
        dupesChecker->moveToThread(&dupesHashingThread);
        connect(&dupesHashingThread, SIGNAL(finished()), dupesChecker, SLOT(deleteLater()));
        connect(this, SIGNAL(startHashing(DirectoryEntriesList, DirectoryEntry*)), dupesChecker, SLOT(startAnalysis(DirectoryEntriesList, DirectoryEntry *)));
        connect(dupesChecker, SIGNAL(analysisComplete(DuplicateEntryList)), this, SLOT(hashingComplete(DuplicateEntryList)));
        connect(dupesChecker, SIGNAL(onProgress(int)), this, SLOT(onDupesProgress(int)));
        connect(this, SIGNAL(stopHashing(bool)), dupesChecker, SLOT(setStopped(bool)), Qt::DirectConnection);
        emit stopHashing(false);
        dupesHashingThread.start();
        qDebug() << "Thread running? " << dupesHashingThread.isRunning();


        qDebug() << "Scanning..";
        emit startHashing(dupesAnalyzer->getEntries(), dupesAnalyzer->getRoot());




    }
}

void MainWindow::hashingComplete(DuplicateEntryList duplicates){
    qDebug() << "Hashing complete";
    if (dupesChecker->getAnalysisDone()){
        qDebug() << "Analysis done";
        progress->setValue(100);
        progress->hide();
        QDir currentDir(dupCheckDUA);
        QFileInfo pathInfo(dupCheckDUA);
        QString fileName = pathInfo.baseName();

        QString directory;
        if (currentDir.isRoot())
            directory = "";
        else
            directory = pathInfo.absolutePath() + QString("/");



        if (duplicates.size() == 0){
            QMessageBox::information(this, "No Duplicates", "No duplicate file entries were found in the scanned directory");
            return;
        }

        if(!dupesDialog)
            dupesDialog = new DupesDialog(this);

        dupesDialog->setWindowTitle(QString("Duplicate Entries in ") + directory + fileName);
        dupesDialog->setDuplicates(duplicates);
        dupesDialog->exec();
        setDirectoryJson(directory, fileName);
    }else if (progress)
        progress->hide();
}

void MainWindow::treeMenuRequested(QPoint loc){
    QModelIndex index = ui->twgDirViewer->indexAt(loc);
    if (!index.isValid())
        return;

    QFileInfo itemInfo = model->fileInfo(index);
    if (itemInfo.exists() && itemInfo.isDir()){
        QMenu *menu = new QMenu(this);
        QAction *analyzeAction = new QAction(QIcon(":/icons/Icons/file-explore-icon.png"), "Analyze Directory", this);
        QAction *openAction = new QAction(QIcon(":/icons/Icons/Folder-Open-icon.png"), "Open Directory", this);
        QAction *openParentAction = new QAction(QIcon(":/icons/Icons/Folder-Open-icon (1).png"), "Open Containing Directory", this);
        QAction *terminalAction = new QAction(QIcon(":/icons/Icons/Apps-Terminal-Pc-104-icon.png"), "Launch Terminal", this);
        QAction *dupesAction = new QAction(QIcon(":/icons/Icons/duplicate-icon-md.png"), "Run Duplicate Files Checker", this);

        QSignalMapper *analyzeMapper = new QSignalMapper(this);
        QSignalMapper *openMapper = new QSignalMapper(this);
        QSignalMapper *openParentMapper = new QSignalMapper(this);
        QSignalMapper *terminalMapper = new QSignalMapper(this);
        QSignalMapper *dupesMapper = new QSignalMapper(this);

        analyzeMapper->setMapping(analyzeAction, itemInfo.canonicalFilePath());
        connect(analyzeAction, SIGNAL(triggered()), analyzeMapper, SLOT(map()));
        connect(analyzeMapper, SIGNAL(mapped(QString)), this, SLOT(analyzeDirectory(QString)));

        openMapper->setMapping(openAction, itemInfo.canonicalFilePath());
        connect(openAction, SIGNAL(triggered()), openMapper, SLOT(map()));
        connect(openMapper, SIGNAL(mapped(QString)), this, SLOT(openDirectory(QString)));

        openParentMapper->setMapping(openParentAction, itemInfo.canonicalPath());
        connect(openParentAction, SIGNAL(triggered()), openParentMapper, SLOT(map()));
        connect(openParentMapper, SIGNAL(mapped(QString)), this, SLOT(openDirectory(QString)));

        terminalMapper->setMapping(terminalAction, itemInfo.canonicalFilePath());
        connect(terminalAction, SIGNAL(triggered()), terminalMapper, SLOT(map()));
        connect(terminalMapper, SIGNAL(mapped(QString)), this, SLOT(launchTerminal(QString)));

        dupesMapper->setMapping(dupesAction, itemInfo.canonicalFilePath());
        connect(dupesAction, SIGNAL(triggered()), dupesMapper, SLOT(map()));
        connect(dupesMapper, SIGNAL(mapped(QString)), this, SLOT(launchDupeChecker(QString)));



        menu->addAction(analyzeAction);
        menu->addAction(openAction);
        if (!itemInfo.isRoot())
            menu->addAction(openParentAction);
        menu->addSeparator();
        menu->addAction(terminalAction);
        menu->addAction(dupesAction);
        menu->popup(ui->twgDirViewer->viewport()->mapToGlobal(loc));
    }else if (itemInfo.exists() && !itemInfo.isRoot()){
        QAction *openParentAction = new QAction(QIcon(":/icons/Icons/Folder-Open-icon (1).png"), "Show Containing Directory", this);
        QSignalMapper *openParentMapper = new QSignalMapper(this);

        openParentMapper->setMapping(openParentAction, itemInfo.canonicalPath());
        connect(openParentAction, SIGNAL(triggered()), openParentMapper, SLOT(map()));
        connect(openParentMapper, SIGNAL(mapped(QString)), this, SLOT(openDirectory(QString)));

        QMenu *menu = new QMenu(this);
        menu->addAction(openParentAction);
        menu->popup(ui->twgDirViewer->viewport()->mapToGlobal(loc));
    }

}

void MainWindow::on_actionOpen_Terminal_triggered(){
    if (getCurrentDUA().trimmed().isEmpty()){
        QModelIndex index = ui->twgDirViewer->currentIndex();
        QFileInfo fileInfo = model->fileInfo(index);
        if (index.isValid() && fileInfo.isDir() && fileInfo.exists() && fileInfo.isReadable()){
            launchTerminal(fileInfo.canonicalFilePath());
            return;
        }
    }

    launchTerminal(getCurrentDUA());

}

void MainWindow::on_actionExploreDirectory_triggered(){
    if (getCurrentDUA().trimmed().isEmpty()){
        QModelIndex index = ui->twgDirViewer->currentIndex();
        QFileInfo fileInfo = model->fileInfo(index);
        if (index.isValid() && fileInfo.isDir() && fileInfo.exists() && fileInfo.isReadable()){
            openDirectory(fileInfo.canonicalFilePath());
            return;
        }
    }
    openDirectory(getCurrentDUA());
}

void MainWindow::on_actionSettings_triggered(){
    if(!settingsDialog){
        settingsDialog = new SettingsDialog(this);
    }
    settingsDialog->setModal(true);
    settingsDialog->exec();
    if(settingsDialog->result() == QDialog::Accepted){
        if(!getCurrentDUA().isEmpty()){
            analyzeDirectory(getCurrentDUA());
        }
    }
}

void MainWindow::on_actionUp_triggered(){
    if(!getCurrentDUA().isEmpty() && getCurrentDUA() != "/"){
        QDir currentDir(getCurrentDUA());
        if(currentDir.cdUp()){
            QFileInfo pathInfo(currentDir.absolutePath());
            QString fileName = pathInfo.baseName();

            QString directory;
            if (currentDir.isRoot())
                directory = "";
            else
                directory = pathInfo.absolutePath() + QString("/");

            setDirectoryJson(directory, fileName);
            setCurrentDUA(directory + fileName);

        }else
            qDebug() << "Invalid path.";
    }
}


void MainWindow::passGraphParamters(bool displayUnit){
    QString fadeEnabled;
    if (SettingsManager::getFadeEnabled())
        fadeEnabled = "0.3, ";
    else
        fadeEnabled = "1.0, ";
    QString colorSet = QString::number(SettingsManager::getColorSet()) + ", ";
    QString readable;

    QString displayUnitParam;
    if (displayUnit){
        readable = QString::number(SettingsManager::getHumanReadable()) + ", ";
        displayUnitParam = "1, ";
    }else{
        readable = "0, ";
        displayUnitParam = "0, ";
    }

    QString navigateGraph = QString::number(SettingsManager::getNavigateChart());

    visFrame->evaluateJavaScript(QString("applySettings(") + fadeEnabled + colorSet
                              + readable + displayUnitParam + navigateGraph + QString("); null"));

}



void MainWindow::on_actionDuplicateFilesChecker_triggered(){
    if (getCurrentDUA().trimmed().isEmpty()){
        QModelIndex index = ui->twgDirViewer->currentIndex();
        QFileInfo fileInfo = model->fileInfo(index);
        if (index.isValid() && fileInfo.isDir() && fileInfo.exists() && fileInfo.isReadable()){
            launchDupeChecker(fileInfo.canonicalFilePath());
            return;
        }
    }

    launchDupeChecker(getCurrentDUA());
}

void MainWindow::on_actionSelectRootDirectory_triggered(){
    QString fileName = QFileDialog::getExistingDirectory(this, "Select Root Directory..", getCurrentDUA());
    if (fileName.trimmed() != "")
        setCurrentPath(fileName);
}

void MainWindow::on_actionAbout_triggered(){
    if(!aboutDialog){
        aboutDialog = new AboutDialog(this);
        aboutDialog->setModal(true);
    }
    aboutDialog->show();
}

void MainWindow::on_btnLargestFiles_clicked(){

    /*stopAnalyzer();
    analyzer = new DirectoryAnalyzer;
    analyzer->moveToThread(&analysisThread);
    connect(&analysisThread, SIGNAL(finished()), analyzer, SLOT(deleteLater()));
    connect(this, SIGNAL(startAnalysis(QString,QString,int, AnalysisTarget)), analyzer, SLOT(startAnalysis(QString, QString, int, AnalysisTarget)));
    connect(analyzer, SIGNAL(analysisComplete(AnalysisTarget)), this, SLOT(analysisComplete(AnalysisTarget)));
    connect(this, SIGNAL(stopAnalysis(bool)), analyzer, SLOT(setStopped(bool)), Qt::DirectConnection);
    emit stopAnalysis(false);
    analysisThread.start();
    qDebug() << "Thread running? " << analysisThread.isRunning();


    qDebug() << "Analyzing..";
    emit startAnalysis(dirStr, nodeName, 0, FileSorting);
*/

    QJsonArray entriesArray;
    QJsonObject entriesObject;
    entriesObject.insert("name", "Entry1");
    entriesObject.insert("value", 120);
    entriesArray.push_back(entriesObject);
    entriesObject.insert("name", "Entry2");
    entriesObject.insert("value", 200);
    entriesArray.push_back(entriesObject);
    entriesObject.insert("name", "Entry3");
    entriesObject.insert("value", 100);
    entriesArray.push_back(entriesObject);
    entriesObject.insert("name", "Entry5");
    entriesObject.insert("value", 300);
    entriesArray.push_back(entriesObject);
    statFrame->evaluateJavaScript("visualize(" + QString(QJsonDocument(entriesArray).toJson(QJsonDocument::Compact)) + "); null");
}

void MainWindow::on_btnExtensions_clicked(){
    /*stopAnalyzer();
    analyzer = new DirectoryAnalyzer;
    analyzer->moveToThread(&analysisThread);
    connect(&analysisThread, SIGNAL(finished()), analyzer, SLOT(deleteLater()));
    connect(this, SIGNAL(startAnalysis(QString,QString,int, AnalysisTarget)), analyzer, SLOT(startAnalysis(QString, QString, int, AnalysisTarget)));
    connect(analyzer, SIGNAL(analysisComplete(AnalysisTarget)), this, SLOT(analysisComplete(AnalysisTarget)));
    connect(this, SIGNAL(stopAnalysis(bool)), analyzer, SLOT(setStopped(bool)), Qt::DirectConnection);
    emit stopAnalysis(false);
    analysisThread.start();
    qDebug() << "Thread running? " << analysisThread.isRunning();


    qDebug() << "Analyzing..";
    emit startAnalysis(dirStr, nodeName, 0, ExtenstionSorting);
*/

}

void MainWindow::on_btnSizeGroups_clicked(){
    /*stopAnalyzer();
    analyzer = new DirectoryAnalyzer;
    analyzer->moveToThread(&analysisThread);
    connect(&analysisThread, SIGNAL(finished()), analyzer, SLOT(deleteLater()));
    connect(this, SIGNAL(startAnalysis(QString,QString,int, AnalysisTarget)), analyzer, SLOT(startAnalysis(QString, QString, int, AnalysisTarget)));
    connect(analyzer, SIGNAL(analysisComplete(AnalysisTarget)), this, SLOT(analysisComplete(AnalysisTarget)));
    connect(this, SIGNAL(stopAnalysis(bool)), analyzer, SLOT(setStopped(bool)), Qt::DirectConnection);
    emit stopAnalysis(false);
    analysisThread.start();
    qDebug() << "Thread running? " << analysisThread.isRunning();


    qDebug() << "Analyzing..";
    emit startAnalysis(dirStr, nodeName, 0, GroupSorting);
    */
}
