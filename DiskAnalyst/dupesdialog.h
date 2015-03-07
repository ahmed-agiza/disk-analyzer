#ifndef DUPESDIALOG_H
#define DUPESDIALOG_H

#include <QDialog>

namespace Ui {
class DupesDialog;
}

typedef QPair<QString, QString> StringPair;

class DupesDialog : public QDialog
{
    Q_OBJECT
    void removeAllEntries(QString filePath);
public:
    explicit DupesDialog(QWidget *parent = 0);
    void setDuplicates(QList<StringPair> dupes);
    ~DupesDialog();
protected:
    void showEvent(QShowEvent *event);
private slots:
    bool deleteFile(QString filePath);
    void openFolder(QString filePath);

    void on_tblDuplicates_clicked(const QModelIndex &index);

private:
    Ui::DupesDialog *ui;
};

#endif // DUPESDIALOG_H
