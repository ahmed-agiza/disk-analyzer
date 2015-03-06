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


MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent), ui(new Ui::MainWindow), model(new QFileSystemModel(this)), analyzer(new DirectoryAnalyzer(this)){
    ui->setupUi(this);
    setCurrentPath("~/");
    ui->twgDirViewer->setModel(model);
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

}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::exposeObjectsToJS(){
    //qDebug() << "Adding objects" << endl;
    frame->addToJavaScriptWindowObject(QString("mainWindow"), this, QWebFrame::ScriptOwnership);
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

void MainWindow::setDirectoryJson(QString dirStr, QString nodeName)
{
    analyzer->startAnalysis(dirStr, nodeName);
    DirectoryEntry *rootEntry = analyzer->getRoot();
    QString entriesJson = DirectoryAnalyzer::getEntriesJsonString(rootEntry);
    QString jsCommand = QString("visualize(") + entriesJson + QString("); null");
    frame->evaluateJavaScript(jsCommand);
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
        setDirectoryJson(directory, fileName);
    }
}
QString MainWindow::getCurrentDUA() const{
    return currentDUA;
}

void MainWindow::setCurrentDUA(const QString &value){
    currentDUA = value;
    if (!value.endsWith("/"))
        currentDUA.append("/");
}


void MainWindow::on_actionAnalyzeDirectory_triggered(){
    QModelIndex index = ui->twgDirViewer->currentIndex();
    on_twgDirViewer_doubleClicked(index);
}

void MainWindow::on_twgDirViewer_doubleClicked(const QModelIndex &index){   
    if(model->isDir(index)){
        QString directory = model->fileInfo(index).absoluteDir().absolutePath() + QString("/");
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
