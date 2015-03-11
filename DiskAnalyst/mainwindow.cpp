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
#include <QToolButton>

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
    :QMainWindow(parent), ui(new Ui::MainWindow), model(new QFileSystemModel(this)), analyzer(0), dupesAnalyzer(0), statLoaded(false), lastListByBlocks(false){
    registerMetaObjects();

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

    initializeWebViews();

    settingsDialog = 0;
    statDialog = 0;
    dupesDialog = 0;
    progress = 0;
    aboutDialog = 0;
    lastStatTarget = Unkown;

    ui->twgDirViewer->setRootIsDecorated(true);
    QObject::connect(ui->twgDirViewer, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(treeMenuRequested(QPoint)), Qt::UniqueConnection);
    ui->twgDirViewer->setContextMenuPolicy(Qt::CustomContextMenu);

    initializeExportMenu();

    ui->tbsMain->setTabIcon(0, QIcon(":/icons/Icons/statistics-icon.png"));
    ui->tbsMain->setTabIcon(1, QIcon(":/icons/Icons/chart-icon.png"));
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

void MainWindow::initializeExportMenu()
{
    exportMenu = new QMenu("Export As..", this);
    exportMenu->setToolTip("Export Current Graph As..");
    exportMenu->setIcon(QIcon(":/icons/Icons/Arrow-download-icon.png"));
    exportHTMLAction = new QAction("Export As HTML", this);
    exportJsonAction = new QAction("Export As JSON", this);
    connect(exportHTMLAction, SIGNAL(triggered()), this, SLOT(exportHTML()));
    connect(exportJsonAction, SIGNAL(triggered()), this, SLOT(exportJson()));
    exportMenu->addAction(exportHTMLAction);
    exportMenu->addAction(exportJsonAction);
    QToolButton* exportToolButton = new QToolButton(this);
    exportToolButton->setText("Export As..");
    exportToolButton->setToolTip("Export Current Graph As..");
    exportToolButton->setIcon(QIcon(":/icons/Icons/Arrow-download-icon.png"));
    exportToolButton->setMenu(exportMenu);
    exportToolButton->setPopupMode(QToolButton::InstantPopup);
    ui->mainToolBar->insertWidget(ui->actionSettings, exportToolButton);
}

void MainWindow::registerMetaObjects()
{
    qRegisterMetaType<DirectoryEntriesList>("DirectoryEntriesList");
    qRegisterMetaType<DirectoryEntry>("DirectoryEntry");
    qRegisterMetaType<DuplicateEntryList>("DuplicateEntryList");
    qRegisterMetaType<AnalysisTarget>("AnalysisTarget");
}

void MainWindow::initializeWebViews()
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, true);

    visFrame = ui->wvwCharts->page()->mainFrame();
    statFrame = ui->wvwStatistics->page()->mainFrame();

    ui->wvwCharts->setContextMenuPolicy(Qt::NoContextMenu);
    ui->wvwStatistics->setContextMenuPolicy(Qt::NoContextMenu);
    ui->wvwCharts->setUrl(QUrl("qrc:/charts/Charts/sunburst.html"));
    ui->wvwStatistics->setUrl(QUrl("qrc:/charts/Charts/barchart.html"));

    //visFrame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    //visFrame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    //statFrame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    //statFrame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    connect(visFrame, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(exposeObjectsToJS()));

    connect(ui->wvwStatistics, SIGNAL(loadStarted()), this, SLOT(onStatLoadStart()), Qt::DirectConnection);
    connect(ui->wvwStatistics, SIGNAL(loadFinished(bool)), this, SLOT(onStatLoadFinished(bool)), Qt::DirectConnection);
    connect(this, SIGNAL(visualizeStat(QString)), this, SLOT(onVisualizeStat(QString)), Qt::QueuedConnection);

    QPalette visPalette = ui->wvwCharts->palette();
    visPalette.setColor(QPalette::Window, QColor(Qt::white));
    visPalette.setColor(QPalette::Background, QColor(Qt::white));
    visPalette.setColor(QPalette::Base, QColor(Qt::white));
    ui->wvwCharts->setPalette(visPalette);
    ui->wvwCharts->page()->setPalette(visPalette);

    QPalette statPalette = ui->wvwStatistics->palette();
    statPalette.setColor(QPalette::Window, QColor(Qt::white));
    statPalette.setColor(QPalette::Background, QColor(Qt::white));
    statPalette.setColor(QPalette::Base, QColor(Qt::white));
    ui->wvwStatistics->setPalette(statPalette);
    ui->wvwStatistics->page()->setPalette(statPalette);
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
    currentStatJson = "";
    currentAnalysisJson = "";
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

void MainWindow::setDirectoryJson(QString dirStr, QString nodeName){
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
    visFrame->evaluateJavaScript("showProgress(); null");
    visFrame->evaluateJavaScript("scaleChart(1.0); null");
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
        //setWindowTitle(QString("Disk Analyst - ") + currentDUA + (tempNavigationPath.trimmed().isEmpty()? QString("x") : QString(QString("[") + tempNavigationPath.trimmed() + "]")));
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

QString MainWindow::getStatsticsJson(QSet<DirectoryEntry *> &entries){
    QJsonArray array;
    for(QSet<DirectoryEntry *>::iterator i = entries.begin(); i != entries.end(); i++){
        QJsonObject entryJson;
        entryJson.insert("name", (*i)->getName());
        entryJson.insert("value", (*i)->getTotalSize());
        array.push_front(entryJson);
    }

    return QString(QJsonDocument(array).toJson(QJsonDocument::Compact));
}

QString MainWindow::getStatsticsJson(QSet<QPair<QString, long long> > entries){
    QJsonArray array;
    for(QSet<QPair<QString, long long> >::iterator i = entries.begin(); i != entries.end(); i++){
        QJsonObject entryJson;
        entryJson.insert("name", (*i).first);
        entryJson.insert("value", (*i).second);
        array.push_front(entryJson);
    }

    return QString(QJsonDocument(array).toJson(QJsonDocument::Compact));
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
    lastStatTarget = target;
    qDebug() << "Analysis complete: " << target;
    if (analyzer->getAnalysisDone()){
        QList<DirectoryEntry *> entries = analyzer->getEntries();
        long long maxDepth = analyzer->getMaxDepth();
        qDebug() << maxDepth;

        qDebug() << "Analyzed..";
        if (target == SizeVisualization){
            qDebug() << "Listing by size";
            DirectoryEntry *rootEntry = analyzer->getRoot();
            QString entriesJson = DirectoryAnalyzer::getEntriesJsonString(rootEntry);
            currentAnalysisJson = entriesJson;
            lastListByBlocks = false;
            QString jsCommand = QString("visualize(") + entriesJson + QString("); null");
            passGraphParamters();
            visFrame->evaluateJavaScript(jsCommand);
            if (SettingsManager::getRelativeScalingEnbaled()){
                QString jsScale = QString("scaleChart(") + QString::number(((maxDepth)/ 30.0) + 0.78) + ")";
                //qDebug() << jsScale;
                visFrame->evaluateJavaScript(jsScale);
            }
            ui->tbsMain->setCurrentIndex(0);
        }else if (target == BlockVisualization){
            qDebug() << "Listing by blocks";
            DirectoryEntry *rootEntry = analyzer->getRoot();
            QString entriesJson = DirectoryAnalyzer::getEntriesJsonStringByBlock(rootEntry);
            currentAnalysisJson = entriesJson;
            lastListByBlocks = true;
            QString jsCommand = QString("visualize(") + entriesJson + QString("); null");
            passGraphParamters(false);
            visFrame->evaluateJavaScript(jsCommand);
            ui->tbsMain->setCurrentIndex(0);
        }else if (target == FileSorting){
            for(int i = 0; i < entries.size(); i++)
                if (entries[i]->isDirectory())
                    entries.removeAt(i--);

            qSort(entries.begin(), entries.end(), DirectoryEntry::isLessThan);
            QSet<DirectoryEntry *> largestEntries;

            for(int i = entries.size() - 1; (i > entries.size() - 11) && (i >= 0); i--)
                largestEntries.insert(entries[i]);

            QString entriesJson = getStatsticsJson(largestEntries);
            currentStatJson = entriesJson;
            applyStatSettings(true);
            statFrame->evaluateJavaScript(QString("visualize(") + entriesJson + "); null");
            ui->tbsMain->setCurrentIndex(1);

        }else if (target == ExtenstionSorting){
            for(int i = 0; i < entries.size(); i++)
                if (entries[i]->isDirectory())
                    entries.removeAt(i--);

            QMap<QString, long long>  largestEntriesMap;

            for(int i = 0; i < entries.size(); i++){
                QFileInfo fileInfo(entries[i]->getFullPath());
                if (fileInfo.isExecutable() || entries[i]->isExecutable()){
                    if (!largestEntriesMap.contains("Executables"))
                        largestEntriesMap["Executables"] = entries[i]->getEntrySize();
                    else
                        largestEntriesMap["Executables"] += entries[i]->getEntrySize();
                }else{
                    while (!entries[i]->getName().trimmed().isEmpty() && entries[i]->getName().startsWith("."))
                        entries[i]->setName(entries[i]->getName().remove(0, 1));
                    if(entries[i]->getName().trimmed() == "")
                        return;
                    fileInfo = QFileInfo(entries[i]->getFullPath());
                    if (fileInfo.suffix().trimmed() == ""){
                        if (!largestEntriesMap.contains("Unknown"))
                            largestEntriesMap["Unknown"] = entries[i]->getEntrySize();
                        else
                            largestEntriesMap["Unknown"] += entries[i]->getEntrySize();
                    }else{
                        if (!largestEntriesMap.contains(fileInfo.suffix().toLower()))
                            largestEntriesMap[fileInfo.suffix().toLower()] = entries[i]->getEntrySize();
                        else
                            largestEntriesMap[fileInfo.suffix().toLower()] += entries[i]->getEntrySize();
                    }
                }
            }

            QList<QPair<QString, long long> > largestEntriesList;
            for(QMap<QString, long long>::iterator i = largestEntriesMap.begin(); i != largestEntriesMap.end(); i++){
                largestEntriesList.append(QPair<QString, long long>(i.key(), largestEntriesMap[i.key()]));
            }
            qSort(largestEntriesList.begin(), largestEntriesList.end(), DirectoryEntry::pairIsLessThan);
            QSet<QPair<QString, long long> > largestEntries;
            for(int i = largestEntriesList.size() - 1; ((i >= 0) && (i > largestEntriesList.size() - 12)); i--){
                largestEntries.insert(largestEntriesList[i]);
            }

            QString entriesJson = getStatsticsJson(largestEntries);
            currentStatJson = entriesJson;
            applyStatSettings(true);
            statFrame->evaluateJavaScript(QString("visualize(") + entriesJson + "); null");
            ui->tbsMain->setCurrentIndex(1);

        }else if (target ==  GroupSorting){
            for(int i = 0; i < entries.size(); i++)
                if (entries[i]->isDirectory())
                    entries.removeAt(i--);

            QMap<QString, long long>  largestEntriesMap;
            largestEntriesMap[">10GB"] = 0;
            largestEntriesMap["5GB:10GB"] = 0;
            largestEntriesMap["1GB:5GB"] = 0;
            largestEntriesMap["500MB:1GB"] = 0;
            largestEntriesMap["100MB:500MB"] = 0;
            largestEntriesMap["1MB:100MB"] = 0;
            largestEntriesMap["1KB:1MB"] = 0;
            largestEntriesMap["<1KB"] = 0;

            for(int i = 0; i < entries.size(); i++){
                long long size = entries[i]->getEntrySize();
                if(size > 10000000001)
                    largestEntriesMap[">10GB"]++;
                else if(size > 5000000000)
                    largestEntriesMap["5GB:10GB"]++;
                else if (size > 1000000000)
                    largestEntriesMap["1GB:5GB"]++;
                else if (size > 500000000)
                    largestEntriesMap["500MB:1GB"]++;
                else if (size > 100000000)
                    largestEntriesMap["100MB:500MB"]++;
                else if (size > 1000000)
                    largestEntriesMap["1MB:100MB"]++;
                else if (size > 1000)
                    largestEntriesMap["1KB:1MB"]++;
                else
                    largestEntriesMap["<1KB"]++;

            }

            QList<QPair<QString, long long> > largestEntriesList;
            for(QMap<QString, long long>::iterator i = largestEntriesMap.begin(); i != largestEntriesMap.end(); i++){
                if (largestEntriesMap[i.key()] > 0)
                    largestEntriesList.append(QPair<QString, long long>(i.key(), largestEntriesMap[i.key()]));
            }

            QString entriesJson = getStatsticsJson(largestEntriesList.toSet());
            currentStatJson = entriesJson;
            applyStatSettings(false);
            statFrame->evaluateJavaScript(QString("visualize(") + entriesJson + "); null");
            ui->tbsMain->setCurrentIndex(1);
        }
        if (target != DupeChecking)
            setWindowTitle(QString("Disk Analyst") + (getCurrentDUA().trimmed().isEmpty()? QString("") : (QString(" - ") + currentDUA)));
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

void MainWindow::listLargestFiles(QString path){
    QFileInfo fileInfo(path);
    if (fileInfo.isDir()){
        QString directory =fileInfo.absoluteDir().absolutePath();
        if (directory != QDir::rootPath() && !directory.endsWith("/"))
            directory.append("/");
        QString fileName = fileInfo.baseName();
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
        statFrame->evaluateJavaScript("showProgress(); null");
        emit startAnalysis(directory, fileName, 0, FileSorting);
    }
}

void MainWindow::listLargestExtension(QString path){

    QFileInfo fileInfo(path);
    if (fileInfo.isDir()){
        QString directory =fileInfo.absoluteDir().absolutePath();
        if (directory != QDir::rootPath() && !directory.endsWith("/"))
            directory.append("/");
        QString fileName = fileInfo.baseName();
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
        statFrame->evaluateJavaScript("showProgress(); null");
        emit startAnalysis(directory, fileName, 0, ExtenstionSorting);
    }
}

void MainWindow::listLargestGroups(QString path){
    QFileInfo fileInfo(path);
    if (fileInfo.isDir()){
        QString directory =fileInfo.absoluteDir().absolutePath();
        if (directory != QDir::rootPath() && !directory.endsWith("/"))
            directory.append("/");
        QString fileName = fileInfo.baseName();
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
        statFrame->evaluateJavaScript("showProgress(); null");
        emit startAnalysis(directory, fileName, 0, GroupSorting);
    }
}

void MainWindow::onStatLoadStart(){
    statLoaded = false;
}

void MainWindow::onStatLoadFinished(bool ok){
    statLoaded = ok;
}

void MainWindow::onVisualizeStat(QString entries){
    qDebug() << statLoaded;
    statFrame->evaluateJavaScript(QString("visualize(") + entries + "); null");

}

void MainWindow::exportHTML(){
    if (currentAnalysisJson.trimmed().isEmpty()){
        QMessageBox::critical(this, "Error", "You have to generate a graph before exporting");
        return;
    }
    QString savePath = QFileDialog::getSaveFileName(this, "Export to..", QDir::homePath(), "HTML Page (*.html)");
    if(savePath.trimmed().isEmpty())
        return;
    if (!savePath.endsWith(".html"))
        savePath.append(".html");
    QFile templateFile(":/charts/Charts/sunburst.expanded.html");
    QFile saveFile(savePath);
    if (!templateFile.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::critical(this, "Error", "Unknown error");
        return;
    }
    QString templateData = QString(templateFile.readAll()).replace("1234567as890129809382fbyjtnd4092803456789", currentAnalysisJson);
    if (!saveFile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)){
        QMessageBox::critical(this, "Error", "Cannot open the file for saving");
        templateFile.close();
        return;
    }
   templateData = templateData.replace("24829028adfv309528509823905afdsav820935820", getSettingsJS(!lastListByBlocks));
    QTextStream writeStream(&saveFile);
    writeStream << templateData;
    saveFile.close();


}

void MainWindow::exportJson(){
    if (currentAnalysisJson.trimmed().isEmpty()){
        QMessageBox::critical(this, "Error", "You have to generate a graph before exporting");
        return;
    }

    QString savePath = QFileDialog::getSaveFileName(this, "Export to..", QDir::homePath(), "JSON Document (*.json)");
    if(savePath.trimmed().isEmpty())
        return;
    if (!savePath.endsWith(".json"))
        savePath.append(".json");

    QFile saveFile(savePath);
    if(!saveFile.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)){
        QMessageBox::critical(this, "Error", "Cannot open the file for saving");
        return;
    }

    QTextStream writeStream(&saveFile);
    writeStream << QJsonDocument::fromJson(currentAnalysisJson.toUtf8()).toJson();
    saveFile.close();
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
    QString settingsJs = getSettingsJS(displayUnit) + " null";
    visFrame->evaluateJavaScript(settingsJs);
}

QString MainWindow::getSettingsJS(bool displayUnit){
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

    return QString("applySettings(") + fadeEnabled + colorSet
                                     + readable + displayUnitParam + navigateGraph + QString(");");
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
    if(getCurrentDUA().trimmed().isEmpty()){
        QModelIndex index = ui->twgDirViewer->currentIndex();
        QFileInfo fileInfo = model->fileInfo(index);
        if (index.isValid() && fileInfo.isDir() && fileInfo.exists() && fileInfo.isReadable()){
            listLargestFiles(fileInfo.canonicalFilePath());
            return;
        }
    }else
        listLargestFiles(getCurrentDUA());

}

void MainWindow::on_btnExtensions_clicked(){
    if(getCurrentDUA().trimmed().isEmpty()){
        QModelIndex index = ui->twgDirViewer->currentIndex();
        QFileInfo fileInfo = model->fileInfo(index);
        if (index.isValid() && fileInfo.isDir() && fileInfo.exists() && fileInfo.isReadable()){
            listLargestExtension(fileInfo.canonicalFilePath());
            return;
        }
    }else
        listLargestExtension(getCurrentDUA());


}

void MainWindow::on_btnSizeGroups_clicked(){
    if(getCurrentDUA().trimmed().isEmpty()){
        QModelIndex index = ui->twgDirViewer->currentIndex();
        QFileInfo fileInfo = model->fileInfo(index);
        if (index.isValid() && fileInfo.isDir() && fileInfo.exists() && fileInfo.isReadable()){
            listLargestGroups(fileInfo.canonicalFilePath());
            return;
        }
    }else
        listLargestGroups(getCurrentDUA());

}



void MainWindow::on_btnBarChart_clicked(bool checked){
    ui->btnDoughChart->setChecked(!checked);
    if(checked){
        QEventLoop loop;
        connect(ui->wvwStatistics, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
        ui->wvwStatistics->setUrl(QUrl("qrc:/charts/Charts/barchart.html"));
        if (!currentStatJson.trimmed().isEmpty()){
            loop.exec();
            if (lastStatTarget == FileSorting || lastStatTarget == ExtenstionSorting)
                applyStatSettings(true);
            else
                applyStatSettings(false);
            statFrame->evaluateJavaScript(QString("visualize(") + currentStatJson + "); null");

        }
    }
}

void MainWindow::on_btnDoughChart_clicked(bool checked){
    ui->btnBarChart->setChecked(!checked);
    if(checked){
        QEventLoop loop;
        connect(ui->wvwStatistics, SIGNAL(loadFinished(bool)), &loop, SLOT(quit()));
        ui->wvwStatistics->setUrl(QUrl("qrc:/charts/Charts/doughnut.html"));
        if (!currentStatJson.trimmed().isEmpty()){
            loop.exec();
            if (lastStatTarget == FileSorting || lastStatTarget == ExtenstionSorting)
                applyStatSettings(true);
            else
                applyStatSettings(false);
            statFrame->evaluateJavaScript(QString("visualize(") + currentStatJson + "); null");
        }
    }
}

void MainWindow::applyStatSettings(bool readable){
    statFrame->evaluateJavaScript(QString("applySettings(") + QString::number(readable) + QString("); null"));
}



void MainWindow::on_sldZoom_sliderMoved(int position){
    ui->wvwCharts->setZoomFactor(position / 100.0);
    ui->lblZoomValue->setText(QString::number(position, 'f', 0) + "%");
}

void MainWindow::on_sldStatZoom_sliderMoved(int position){
    ui->wvwStatistics->setZoomFactor(position / 100.0);
    ui->lblStatZoomValue->setText(QString::number(position, 'f', 0) + "%");
}
