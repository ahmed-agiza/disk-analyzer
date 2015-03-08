#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSet>
#include <QThread>
#include <QWebFrame>
#include <QProgressBar>

#include "directoryanalyzer.h"
#include "settingsdialog.h"
#include "filestatdialog.h"
#include "dupesdialog.h"
#include "dupeschecker.h"



namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

    void passGraphParamters(bool displayUnit = true);


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void centerWindow();

    QString getCurrentDUA() const;
    void setCurrentDUA(const QString &value);

    static void openDirectory(QString path, QWidget *parent);

signals:
    void startAnalysis(QString, QString, int);
    void stopAnalysis(bool);

    void startScanning(QString, QString, int);
    void stopScanning(bool);

    void startHashing(DirectoryEntriesList, DirectoryEntry *);
    void stopHashing(bool);





private slots:
    void on_actionAnalyzeDirectory_triggered();

    void on_twgDirViewer_doubleClicked(const QModelIndex &index);

    void on_twgDirViewer_expanded(const QModelIndex &index);

    void on_actionRefresh_triggered();

    void analysisComplete();
    void scanComplete();
    void hashingComplete(QList<QPair<QString, QString> >);

    void on_actionOpen_Terminal_triggered();

    void on_actionExploreDirectory_triggered();

    void on_actionSettings_triggered();

    void on_actionUp_triggered();

    void on_actionDuplicateFilesChecker_triggered();

    void on_actionSelectRootDirectory_triggered();

public slots:
    void exposeObjectsToJS();
    void setCurrentPath(QString);
    void setDirectoryJson(QString, QString);
    void navigateTo(QString);
    void stopAnalyzer();
    void stopDupesAnalyzer();
    void stopDupesChecking();
    void onDupesProgress(int);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    DirectoryAnalyzer *analyzer;
    DirectoryAnalyzer *dupesAnalyzer;
    QWebFrame *frame;
    SettingsDialog *settingsDialog;
    FileStatDialog *statDialog;
    QProgressBar *progress;
    DupesDialog *dupesDialog;
    DupesChecker *dupesChecker;
    QString currentPath;
    QString currentDUA;
    QString dupCheckDUA;
    QThread analysisThread;
    QThread dupesCheckerThread;
    QThread dupesHashingThread;
};


#endif // MAINWINDOW_H
