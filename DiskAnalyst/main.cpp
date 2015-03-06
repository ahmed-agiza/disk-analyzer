#include "mainwindow.h"
#include <QApplication>
#include <QProcess>
#include <QMessageBox>

int main(int argc, char *argv[]){

#ifndef Q_OS_UNIX
    QMessageBox::critical("Error", "this tool works on Unix operating systems only");
#endif

    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();
    QProcess process;



    return a.exec();
}
