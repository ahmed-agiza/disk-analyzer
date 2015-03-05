#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileSystemModel>
#include <QSet>

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
    void setDirectoryJson(QString, QString);
private slots:
    void on_actionAnalyzeDirectory_triggered();

    void on_twgDirViewer_doubleClicked(const QModelIndex &index);

public slots:
    void exposeObjectsToJS();
    void setCurrentPath(QString);

private:
    Ui::MainWindow *ui;
    QFileSystemModel *model;
    QString currentPath;
};

class DirectoryEntry;

class DirectoryEntry{

public:
    DirectoryEntry(QString, QString, long long, int, DirectoryEntry * = 0, QSet<DirectoryEntry *> = QSet<DirectoryEntry *> ());

    QString getName() const;
    void setName(const QString &value);

    QString getPath() const;
    void setPath(const QString &value);

    int getDepth() const;
    void setDepth(int value);

    long long getEntrySize() const;
    void setEntrySize(long long value);

    DirectoryEntry *getSource() const;
    void setSource(DirectoryEntry *value);

    QSet<DirectoryEntry *> getChildren() const;
    void setChildren(const QSet<DirectoryEntry *> &value);
    void addChild(DirectoryEntry *value);
    void removeChild(DirectoryEntry* value);

private:
    QString name;
    QString path;
    int depth;
    long long entrySize;
    DirectoryEntry *source;
    QSet<DirectoryEntry *> children;
};



#endif // MAINWINDOW_H
