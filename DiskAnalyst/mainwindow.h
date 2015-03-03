#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

public slots:
    void exposeObjectToJS();

private:
    Ui::MainWindow *ui;
};



#endif // MAINWINDOW_H
