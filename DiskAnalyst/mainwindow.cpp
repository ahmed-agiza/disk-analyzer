#include <QFileSystemModel>
#include <QDesktopWidget>
#include <QDockWidget>
#include <QHBoxLayout>
#include <QFileDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QWebPage>
#include <QWebFrame>
#include <QDebug>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    QFileSystemModel *model = new QFileSystemModel(this);
    model->setRootPath("/");
    ui->twgDirViewer->setModel(model);
    ui->twgDirViewer->hideColumn(1);
    ui->twgDirViewer->hideColumn(3);
    centerWindow();

    QDockWidget *dckDir = new QDockWidget(this);
    dckDir->setFeatures(QDockWidget::DockWidgetMovable);
    dckDir->setWidget(ui->twgDirViewer);
    dckDir->setAllowedAreas(Qt::LeftDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, dckDir);

    QDockWidget *dckWeb = new QDockWidget(this);
    dckWeb->setFeatures(QDockWidget::DockWidgetMovable);
    dckWeb->setWidget(ui->wvwCharts);
    dckWeb->setAllowedAreas(Qt::RightDockWidgetArea);
    addDockWidget(Qt::RightDockWidgetArea, dckWeb);

    ui->wvwCharts->setUrl(QUrl("qrc:/charts/Icons/main.html"));
    connect(ui->wvwCharts->page()->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()), this, SLOT(exposeObjectToJS()));
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::exposeObjectToJS(){
    qDebug() << "Adding object" << endl;
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
