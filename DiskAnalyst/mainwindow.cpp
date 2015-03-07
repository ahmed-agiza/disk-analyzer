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
#include <QCryptographicHash>

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
#include <stdbool.h>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settingsmanager.h"



MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow), model(new QFileSystemModel(this)), analyzer(new DirectoryAnalyzer(this)){
    ui->setupUi(this);
    ui->twgDirViewer->setModel(model);
    setCurrentPath(QDir::homePath ());
    ui->twgDirViewer->hideColumn(1);
    ui->twgDirViewer->hideColumn(3);
    centerWindow();

    setWindowState(Qt::WindowMaximized);
    setFixedSize(width(), height() + 40);
    centerWindow();
    statusBar()->setSizeGripEnabled(false);

    frame = ui->wvwCharts->page()->mainFrame();
    ui->wvwCharts->setContextMenuPolicy(Qt::NoContextMenu);
    ui->wvwCharts->setUrl(QUrl("qrc:/charts/Charts/index.html"));

    frame->setScrollBarValue(Qt::Vertical, frame->scrollBarMaximum(Qt::Vertical));
    frame->setScrollBarValue(Qt::Horizontal, frame->scrollBarMaximum(Qt::Horizontal));
    frame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    frame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    connect(frame, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(exposeObjectsToJS()));
    settingsDialog = 0;
    statDialog = 0;
    dupesDialog = 0;

    ui->twgDirViewer->setRootIsDecorated(true);
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::exposeObjectsToJS(){
    frame->addToJavaScriptWindowObject(QString("mainWindow"), this, QWebFrame::ScriptOwnership);
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

void MainWindow::setDirectoryJson(QString dirStr, QString nodeName)
{
    qDebug() << "Analyzing..";
    analyzer->startAnalysis(dirStr, nodeName);
    qDebug() << "Analyzed..";
    DirectoryEntry *rootEntry = analyzer->getRoot();
    QString entriesJson = DirectoryAnalyzer::getEntriesJsonString(rootEntry);
    QString jsCommand = QString("visualize(") + entriesJson + QString("); null");
    frame->evaluateJavaScript(jsCommand);
    passGraphParamters();
}

void MainWindow::navigateTo(QString path){
    if(path.isEmpty())
        return;
    if (path.startsWith("/"))
        path.remove(0, 1);

    if (path.endsWith("/"))
        path.remove(path.length() - 1, 1);

    QString fullPath = currentDUA + path;
    QFileInfo pathInfo(fullPath);
    if(pathInfo.isDir()){
        QString directory = pathInfo.absoluteDir().absolutePath() + QString("/");
        QString fileName = pathInfo.baseName();
        setCurrentDUA(directory + fileName);
        //setDirectoryJson(directory, fileName);
    }else if(pathInfo.exists()){
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
    }else{
        qDebug() << pathInfo.absoluteFilePath() << " does not exist";
    }
}
QString MainWindow::getCurrentDUA() const{
    return currentDUA;
}

void MainWindow::setCurrentDUA(const QString &value){
    currentDUA = value;
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
    QString fileName = QFileDialog::getExistingDirectory(this, "Select Root Directory..", currentDUA);
    if (fileName.trimmed() != "")
        setCurrentPath(fileName);
}

void MainWindow::on_twgDirViewer_doubleClicked(const QModelIndex &index){   
    if(model->isDir(index)){
        QString directory = model->fileInfo(index).absoluteDir().absolutePath();
        if (directory != QDir::rootPath() && !directory.endsWith("/"))
            directory.append("/");
        QString fileName = model->fileInfo(index).baseName();
        setCurrentDUA(directory + fileName);
        setDirectoryJson(directory, fileName);
    }
}


void MainWindow::on_twgDirViewer_expanded(const QModelIndex &){
    ui->twgDirViewer->resizeColumnToContents(0);
}

void MainWindow::on_actionRefresh_triggered(){
    model->setRootPath("");
    setCurrentPath(currentPath);
}

void MainWindow::analysisComplete(){

}

void MainWindow::on_actionOpen_Terminal_triggered(){
    if(currentDUA.isEmpty())
        return;

    QFileInfo pathInfo(currentDUA);
    if(!pathInfo.isDir()){
        QMessageBox::critical(this, "Error", "Invalid directory " + currentDUA);
        return;
    }

    QString terminal(qgetenv("TERM"));

    if (terminal.isEmpty()){
        QMessageBox::critical(this, "Error", "The terminal environment variable $TERM is not set");
        return;
    }else{
        QProcess *terminalProcess = new QProcess(this);
        QString option("-e");
        QString argument(QString("cd ") + currentDUA + " && /bin/bash");
        QStringList arguments;
        arguments << option << argument;
        terminalProcess->start(terminal, arguments);
    }
}

void MainWindow::on_actionExploreDirectory_triggered(){
    openDirectory(currentDUA, this);
}

void MainWindow::on_actionSettings_triggered(){
    if(!settingsDialog){
        settingsDialog = new SettingsDialog(this);
    }
    settingsDialog->setModal(true);
    settingsDialog->exec();
    if(settingsDialog->result() == QDialog::Accepted){
        passGraphParamters();
    }
}

void MainWindow::on_actionUp_triggered(){
    if(!currentDUA.isEmpty() && currentDUA != "/"){
        QDir currentDir(currentDUA);
        if(currentDir.cdUp()){
            QFileInfo pathInfo(currentDir.absolutePath());
            QString fileName = pathInfo.baseName();

            QString directory;
            if (currentDir.isRoot())
                directory = "";
            else
                directory = pathInfo.absolutePath() + QString("/");

            setCurrentDUA(directory + fileName);
            setDirectoryJson(directory, fileName);
        }else
            qDebug() << "Invalid path.";
    }
}


void MainWindow::passGraphParamters(bool displayUnit){
    QString fadeEnabled;
    if (SettingsManager::getFadeEnabled())
        fadeEnabled = "0.3, ";
    else
        fadeEnabled = "0.0, ";
    QString colorSet = QString::number(SettingsManager::getColorSet()) + ", ";
    QString readable = QString::number(SettingsManager::getHumanReadable()) + ", ";

    QString displayUnitParam;
    if (displayUnit)
        displayUnitParam = "1, ";
    else
        displayUnitParam = "0, ";

    QString navigateGraph = QString::number(SettingsManager::getNavigateChart());

    frame->evaluateJavaScript(QString("applySettings(") + fadeEnabled + colorSet
                              + readable + displayUnitParam + navigateGraph + QString("); null"));

}

QString MainWindow::hashFile(QString filePath){
    QFile file(filePath);
    if(file.open(QIODevice::ReadOnly))
    {
        QString hash = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex().constData();
        file.close();
        return hash;
    }

    return "";
}

void MainWindow::on_actionDuplicateFilesChecker_triggered(){
    DirectoryAnalyzer checkerAnalyzer;
    QString dupCheckDUA = currentDUA;
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


    checkerAnalyzer.startAnalysis(directory, fileName);
    QList<DirectoryEntry *> entries = checkerAnalyzer.getEntries();
    QMap<long long, QStringList> sizesTable;
    QMap<QString, QString> hashCache;
    QList<QPair<QString, QString> > duplicates;
    DirectoryEntry *rootEntry = analyzer->getRoot();
    for(int i = 0; i < entries.size(); i++){
        if (entries[i] == rootEntry)
            continue;
        if (entries[i]->isValid() && entries[i]->isRegularFile()){
            QString entryPath = entries[i]->getPath() + entries[i]->getName();
            if(!sizesTable.contains(entries[i]->getEntrySize())){
                sizesTable[entries[i]->getEntrySize()].append(entryPath);
            }else{
                QList<QString> &matchingSize = sizesTable[entries[i]->getEntrySize()];
                qDebug() << "Size: " << entries[i]->getEntrySize();
                qDebug() << "Entry: " << entryPath;
                qDebug() << "Older entries: " << matchingSize;
                QString entryHash;
                if(hashCache.contains(entryPath))
                    entryHash = hashCache[entryPath];
                else{
                    entryHash = hashFile(entryPath);
                    if (entryHash != "")
                        hashCache[entryPath] = entryHash;
                }

                if (entryHash == ""){
                    qDebug() << "Cannot hash " << entries[i]->getPath() + entries[i]->getName();
                }else{
                    for(int j = 0; j < matchingSize.size(); j++){
                        QString fileHash;
                        if(hashCache.contains(matchingSize[j]))
                            fileHash = hashCache[matchingSize[j]];
                        else{
                            fileHash = hashFile(matchingSize[j]);
                            if(fileHash != "")
                                hashCache[matchingSize[j]] = fileHash;
                        }

                        if(fileHash == ""){
                            qDebug() << "Cannot hash " << matchingSize[j];
                        }else if (fileHash == entryHash){
                            duplicates.append(QPair<QString, QString>(matchingSize[j], entryPath));
                        }else{
                            qDebug() << "Entries " << entryPath << " and " << matchingSize[j]
                                        << " have the same size but different hashing";
                        }
                    }
                }
                matchingSize.append(entryPath);
            }

        }
    }

    if (duplicates.size() == 0){
        QMessageBox::information(this, "No Duplicates", "No duplicate file entries were found in the scanned directory");
        return;
    }

    if(!dupesDialog)
        dupesDialog = new DupesDialog(this);

    dupesDialog->setDuplicates(duplicates);
    dupesDialog->exec();
    setDirectoryJson(directory, fileName);

}
