#ifndef FILESTATDIALOG_H
#define FILESTATDIALOG_H

#include <QDialog>

namespace Ui {
class FileStatDialog;
}

class FileStatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileStatDialog(QWidget *parent = 0);
    ~FileStatDialog();
    FileStatDialog *setFileName(QString value);
    FileStatDialog *setFilePath(QString value);
    FileStatDialog *setFileExtenstion(QString value);
    FileStatDialog *setFileType(QString value);
    FileStatDialog *setInodeNumber(long value);
    FileStatDialog *setMode(QString value);
    FileStatDialog *setLinkCount(long value);
    FileStatDialog *setOwnership(QString value);
    FileStatDialog *setPreferredIOSize(long value);
    FileStatDialog *setSize(long long value);
    FileStatDialog *setNumberOfBlocks(long long value);
    FileStatDialog *setLastStatusChange(QString value);
    FileStatDialog *setLastFileAccess(QString value);
    FileStatDialog *setLastModification(QString value);


private:
    Ui::FileStatDialog *ui;
};

#endif // FILESTATDIALOG_H
