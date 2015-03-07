#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSet>
#include <QThread>
#include <QWebFrame>

#include "directoryanalyzer.h"
#include "settingsdialog.h"
#include "filestatdialog.h"




namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void centerWindow();

    QString getCurrentDUA() const;
    void setCurrentDUA(const QString &value);

signals:
    void startAnalysis(QString, QString, int);

private slots:
    void on_actionAnalyzeDirectory_triggered();

    void on_twgDirViewer_doubleClicked(const QModelIndex &index);

    void on_twgDirViewer_expanded(const QModelIndex &index);

    void on_actionRefresh_triggered();

    void analysisComplete();

    void on_actionOpen_Terminal_triggered();

    void on_actionExploreDirectory_triggered();

    void on_actionSettings_triggered();

    void on_actionUp_triggered();

public slots:
    void exposeObjectsToJS();
    void setCurrentPath(QString);
    void setDirectoryJson(QString, QString);
    void navigateTo(QString);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    DirectoryAnalyzer *analyzer;
    QWebFrame *frame;
    SettingsDialog *settingsDialog;
    FileStatDialog *statDialog;
    QString currentPath;
    QString currentDUA;
    QThread analysisThread;
};


#endif // MAINWINDOW_H
