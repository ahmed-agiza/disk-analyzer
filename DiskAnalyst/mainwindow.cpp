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
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    model = new QFileSystemModel(this);
    model->setRootPath("/");
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


void MainWindow::on_actionAnalyzeDirectory_triggered(){

}

void MainWindow::on_twgDirViewer_doubleClicked(const QModelIndex &index){
    QJsonObject mainData;
    QJsonObject childA;
    childA.insert("name", "childA");
    childA.insert("size", 1000);
    QJsonObject childB;
    childB.insert("name", "childB");
    QJsonObject childBA;
    childBA.insert("name", "childBA");
    childBA.insert("size", 400);
    QJsonObject childBB;
    childBB.insert("name", "childBB");
    childBB.insert("size",  700);
    QJsonArray childBChildren;
    childBChildren.push_back(childBA);;
    childBChildren.push_back(childBB);
    childB.insert("children", childBChildren);
    QJsonArray mainChildren;
    mainChildren.push_back(childA);
    mainChildren.push_back(childB);
    mainData.insert("children", mainChildren);
    mainData.insert("name", "main");
    QString jsonString = QString(QJsonDocument(mainData).toJson(QJsonDocument::Compact));
    qDebug() << jsonString;
    ui->wvwCharts->page()->mainFrame()->evaluateJavaScript("visualize("+ jsonString +"); alert('X'); null");
    //ui->wvwCharts->page()->mainFrame()->evaluateJavaScript("test(); null");
    //01012230444
}
