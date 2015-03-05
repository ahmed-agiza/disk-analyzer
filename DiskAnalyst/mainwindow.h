#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>

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
private slots:
    void on_actionAnalyzeDirectory_triggered();

    void on_twgDirViewer_doubleClicked(const QModelIndex &index);

public slots:
    void exposeObjectsToJS();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
};



#endif // MAINWINDOW_H
