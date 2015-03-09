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
        mainwindow.cpp \
    directoryentry.cpp \
    directoryanalyzer.cpp \
    settingsdialog.cpp \
    filestatdialog.cpp \
    dupesdialog.cpp \
    dupeschecker.cpp \
    duplicatesdatamodel.cpp \
    customprogressbar.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    directoryanalyzer.h \
    directoryentry.h \
    settingsdialog.h \
    filestatdialog.h \
    settingsmanager.h \
    dupesdialog.h \
    dupeschecker.h \
    duplicatesdatamodel.h \
    customprogressbar.h \
    aboutdialog.h

FORMS    += mainwindow.ui \
    settingsdialog.ui \
    filestatdialog.ui \
    dupesdialog.ui \
    aboutdialog.ui

RESOURCES += \
    files.qrc
