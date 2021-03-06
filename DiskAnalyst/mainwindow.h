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
    QString getSettingsJS(bool displayUnit = true);


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void centerWindow();

    QString getCurrentDUA() const;
    void setCurrentDUA(const QString &value);

    static void openDirectory(QString path, QWidget *parent);

    static QString getStatsticsJson(QSet<DirectoryEntry *> &entries);
    static QString getStatsticsJson(QSet<QPair<QString, long long> > entries);

signals:
    void startAnalysis(QString, QString, int, AnalysisTarget);
    void stopAnalysis(bool);

    void startScanning(QString, QString, int, AnalysisTarget);
    void stopScanning(bool);

    void startHashing(DirectoryEntriesList, DirectoryEntry *);
    void stopHashing(bool);

    void visualizeStat(QString);


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
    void listLargestFiles(QString);
    void listLargestExtension(QString);
    void listLargestGroups(QString);
    void onStatLoadStart();
    void onStatLoadFinished(bool ok);

    void onVisualizeStat(QString);

    void exportHTML();
    void exportJson();

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
    void on_btnLargestFiles_clicked();
    void on_btnExtensions_clicked();
    void on_btnSizeGroups_clicked();
    void on_btnBarChart_clicked(bool checked);
    void on_btnDoughChart_clicked(bool checked);
    void applyStatSettings(bool);

    void on_sldZoom_sliderMoved(int position);

    void on_sldStatZoom_sliderMoved(int position);

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
    QWebFrame *visFrame;
    QWebFrame *statFrame;
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
    QString currentStatJson;
    QString currentAnalysisJson;
    AnalysisTarget lastStatTarget;
    bool statLoaded;
    bool lastListByBlocks;
    QMenu *exportMenu;
    QAction *exportHTMLAction;
    QAction *exportJsonAction;

    void initializeExportMenu();
    void registerMetaObjects();
    void initializeWebViews();
};


#endif // MAINWINDOW_H
