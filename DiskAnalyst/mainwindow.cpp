#include <QDesktopWidget>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QWebPage>
#include <QWebFrame>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>
#include <QFileSystemModel>

#include "file_analyzer.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setRootPath("/home/");
    ui->twgDirViewer->setModel(model);
    ui->twgDirViewer->hideColumn(1);
    ui->twgDirViewer->hideColumn(3);
    centerWindow();

    setWindowState(Qt::WindowMaximized);
    setFixedSize(width(), height() + 40);
    centerWindow();
    statusBar()->setSizeGripEnabled(false);

    QWebFrame *frame = ui->wvwCharts->page()->mainFrame();
    ui->wvwCharts->setContextMenuPolicy(Qt::NoContextMenu);
    ui->wvwCharts->setUrl(QUrl("qrc:/charts/Charts/index.html"));

    frame->setScrollBarValue(Qt::Vertical, frame->scrollBarMaximum(Qt::Vertical));
    frame->setScrollBarValue(Qt::Horizontal, frame->scrollBarMaximum(Qt::Horizontal));
    frame->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    frame->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);

    connect(frame, SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(exposeObjectsToJS()));

}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::exposeObjectsToJS(){
    //qDebug() << "Adding objects" << endl;
    //ui->wvwCharts->page()->mainFrame()->addToJavaScriptWindowObject(QString("name"), objecy, QWebFrame::ScriptOwnership);
}

void MainWindow::setCurrentPath(QString newPath){
    currentPath = newPath;
    model->setRootPath(newPath);
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

typedef QPair<QString, long long> ItemEntryPair;
typedef QSet<ItemEntryPair> FileEntriesSet;
typedef  QMap<QString, FileEntriesSet> DirectoryTreeStructure;

void MainWindow::setDirectoryJson(QString dirStr, QString nodeName)
{
    char *dir = dirStr.toLocal8Bit().data();
    file_stat dir_stat_buf;
    int return_code;
    QList<file_stat> analyzedDirectories = analyze_directory(&dir_stat_buf, dir, FLAG_RECURSE_MASK, &return_code);
    QMap<QString, DirectoryEntry *> directoryTrace;
    QList<DirectoryEntry *> childEntries;
    QList<DirectoryEntry *> rootEntries;
    QMap<DirectoryEntry *, QJsonObject *> entriesJsons;
    QMap<int, QSet<DirectoryEntry *> > entriesLevels;
    int maxLevel = 0;
    for(int i = 0; i < analyzedDirectories.size(); i++){
        DirectoryEntry *entry = new DirectoryEntry(analyzedDirectories[i].name, analyzedDirectories[i].directory,
                                                   analyzedDirectories[i].size, analyzedDirectories[i].depth);
        if(analyzedDirectories[i].type == DIRECTORY)
            directoryTrace[QString(analyzedDirectories[i].directory) + analyzedDirectories[i].name + QString("/")] = entry;
        else
            directoryTrace[QString(analyzedDirectories[i].directory) + analyzedDirectories[i].name] = entry;
        childEntries.append(entry);

        QJsonObject *entryJson = new QJsonObject;
        entryJson->insert("name", entry->getName());
        entryJson->insert("size", entry->getEntrySize());
        entriesJsons[entry] = entryJson;

        entriesLevels[entry->getDepth()].insert(entry);
        if (entry->getDepth() > maxLevel)
            maxLevel = entry->getDepth();
    }


    for(int i = 0; i < childEntries.size(); i++){
        if (childEntries[i]->getDepth() > 1){
            childEntries[i]->setSource(directoryTrace[childEntries[i]->getPath()]);
            directoryTrace[childEntries[i]->getPath()]->addChild(childEntries[i]);
        }else{
            rootEntries.append(childEntries[i]);
        }
    }

    QJsonArray emptyArray;
    for(int i = 0; i < childEntries.size(); i++)
        if (!childEntries[i]->getChildren().isEmpty())
            entriesJsons[childEntries[i]]->insert(QString("children"), emptyArray);

    for(int i = 0; i < rootEntries.size(); i++)
        if (!rootEntries[i]->getChildren().isEmpty())
            entriesJsons[rootEntries[i]]->insert(QString("children"), emptyArray);

    for(int i = maxLevel; i > 1; i--){
        QSet<DirectoryEntry *> &levelSet = entriesLevels[i];
        for(QSet<DirectoryEntry *>::iterator  it = levelSet.begin(); it != levelSet.end(); it++){
            DirectoryEntry *entry = *it;
            DirectoryEntry *parentEnrty = entry->getSource();
            QJsonObject *parentJson = entriesJsons[parentEnrty];
            QJsonArray parentChildren = parentJson->value("children").toArray();
            parentChildren.push_front(*entriesJsons[entry]);
            parentJson->insert("children", parentChildren);
        }

    }


    QJsonObject rootElement;
    rootElement.insert("name", nodeName);
    rootElement.insert("size", dir_stat_buf.size);
    QJsonArray rootChildren;

    for(int i = 0; i < rootEntries.size(); i++)
       rootChildren.push_front(*entriesJsons[rootEntries[i]]);

    rootElement.insert("children", rootChildren);

    qDebug() << QString(QJsonDocument(rootElement).toJson());
    ui->wvwCharts->page()->mainFrame()->evaluateJavaScript("visualize("+ QString(QJsonDocument(rootElement).toJson(QJsonDocument::Compact)) +"); null");
}

void MainWindow::on_actionAnalyzeDirectory_triggered(){
    QString dir("/home/");
    setDirectoryJson(dir, "home");

}

void MainWindow::on_twgDirViewer_doubleClicked(const QModelIndex &index){   
    if(model->isDir(index)){
        QString directory = model->filePath(index) + QString("/");
        setDirectoryJson(directory, model->fileName(index));
    }
}

DirectoryEntry::DirectoryEntry(QString name, QString path, long long size, int depth, DirectoryEntry *source, QSet<DirectoryEntry *> children){
    setName(name);
    setPath(path);
    setEntrySize(size);
    setDepth(depth);
    setSource(source);
    setChildren(children);
}

QString DirectoryEntry::getName() const{
    return name;
}

void DirectoryEntry::setName(const QString &value){
    name = value;
}
QString DirectoryEntry::getPath() const{
    return path;
}

void DirectoryEntry::setPath(const QString &value){
    path = value;
}
int DirectoryEntry::getDepth() const{
    return depth;
}

void DirectoryEntry::setDepth(int value){
    depth = value;
}
long long DirectoryEntry::getEntrySize() const{
    return entrySize;
}

void DirectoryEntry::setEntrySize(long long value){
    entrySize = value;
}
DirectoryEntry *DirectoryEntry::getSource() const{
    return source;
}

void DirectoryEntry::setSource(DirectoryEntry *value){
    source = value;
}
QSet<DirectoryEntry *> DirectoryEntry::getChildren() const{
    return children;
}

void DirectoryEntry::setChildren(const QSet<DirectoryEntry *> &value){
    children = value;
}

void DirectoryEntry::addChild(DirectoryEntry *value){
    children.insert(value);
}

void DirectoryEntry::removeChild(DirectoryEntry *value){
    children.remove(value);
}





