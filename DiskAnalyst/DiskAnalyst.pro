#-------------------------------------------------
#
# Project created by QtCreator 2015-03-02T11:34:04
#
#-------------------------------------------------

QT       += core gui webkitwidgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DiskAnalyst
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    file_analyzer.h

FORMS    += mainwindow.ui

RESOURCES += \
    files.qrc
