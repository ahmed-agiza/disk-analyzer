#ifndef DUPESDIALOG_H
#define DUPESDIALOG_H

#include <QDialog>

#include "duplicatesdatamodel.h"

namespace Ui {
class DupesDialog;
}

typedef QPair<QString, QString> StringPair;

class DupesDialog : public QDialog
{
    Q_OBJECT
    QList<QPair<QString, QString> > duplicates;
public:
    explicit DupesDialog(QWidget *parent = 0);
    void setDuplicates(QList<StringPair> dupes);
    ~DupesDialog();
protected:
    void showEvent(QShowEvent *event);
private slots:
    int deleteFile(QString filePath);
    void openFolder(QString filePath);
    void refreshTableView();

    void on_tblDuplicates_clicked(const QModelIndex &index);

private:
    Ui::DupesDialog *ui;
    DuplicatesDataModel *model;
};

#endif // DUPESDIALOG_H
