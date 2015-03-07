#include "mainwindow.h"
#include <QApplication>

#include <QMessageBox>

int main(int argc, char *argv[]){

#ifndef Q_OS_UNIX
    QMessageBox::critical(0, "Error", "this tool works on Unix operating systems only");
#endif
    QCoreApplication::setOrganizationName("AUC Egypt");
    QCoreApplication::setOrganizationDomain("aucegypt.edu.eg");
    QCoreApplication::setApplicationName("Disk Analyzer");
    QApplication a(argc, argv);
    MainWindow w;
    w.showMaximized();

    return a.exec();
}
