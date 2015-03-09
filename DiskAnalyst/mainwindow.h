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
#include "customprogressbar.h"
#include "mainwindow.h"
#include "aboutdialog.h"



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
    void startAnalysis(QString, QString, int, AnalysisTarget);
    void stopAnalysis(bool);

    void startScanning(QString, QString, int, AnalysisTarget);
    void stopScanning(bool);

    void startHashing(DirectoryEntriesList, DirectoryEntry *);
    void stopHashing(bool);


protected:
    bool eventFilter(QObject *, QEvent *);


private slots:

    void analyzeDirectory(QString);
    void launchTerminal(QString);
    void launchDupeChecker(QString);
    void analysisComplete(AnalysisTarget);
    void scanComplete();
    void hashingComplete(DuplicateEntryList);
    void treeMenuRequested(QPoint);
    void on_actionAnalyzeDirectory_triggered();
    void on_twgDirViewer_doubleClicked(const QModelIndex &index);
    void on_twgDirViewer_expanded(const QModelIndex &index);
    void on_actionRefresh_triggered();
    void on_actionOpen_Terminal_triggered();
    void on_actionExploreDirectory_triggered();
    void on_actionSettings_triggered();
    void on_actionUp_triggered();
    void on_actionDuplicateFilesChecker_triggered();
    void on_actionSelectRootDirectory_triggered();

    void on_actionAbout_triggered();

public slots:
    void exposeObjectsToJS();
    void setCurrentPath(QString);
    void setDirectoryJson(QString, QString);
    void navigateTo(QString);
    void stopAnalyzer();
    void stopDupesAnalyzer();
    void stopDupesChecking();
    void onDupesProgress(int);
    void openDirectory(QString path);
    void statFile(QString);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    DirectoryAnalyzer *analyzer;
    DirectoryAnalyzer *dupesAnalyzer;
    QWebFrame *frame;
    SettingsDialog *settingsDialog;
    FileStatDialog *statDialog;
    CustomProgressBar *progress;
    DupesDialog *dupesDialog;
    DupesChecker *dupesChecker;
    AboutDialog *aboutDialog;
    QString currentPath;
    QString currentDUA;
    QString dupCheckDUA;
    QThread analysisThread;
    QThread dupesCheckerThread;
    QThread dupesHashingThread;
    QString tempNavigationPath;
};


#endif // MAINWINDOW_H
