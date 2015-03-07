#include "filestatdialog.h"
#include "ui_filestatdialog.h"

FileStatDialog::FileStatDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileStatDialog){
    ui->setupUi(this);
    setModal(true);
}

FileStatDialog::~FileStatDialog(){
    delete ui;
}

FileStatDialog *FileStatDialog::setFileName(QString value){
    ui->lblFilename->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setFilePath(QString value){
    ui->lblFilePath->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setFileExtenstion(QString value){
    ui->lblFileExtension->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setFileType(QString value){
    ui->lblFileType->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setInodeNumber(long value){
    ui->lblInodeNumber->setText(QString::number(value));
    return this;
}

FileStatDialog *FileStatDialog::setMode(QString value){
    ui->lblMode->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setLinkCount(long value){
    ui->lblLinkCount->setText(QString::number(value));
    return this;
}

FileStatDialog *FileStatDialog::setOwnership(QString value){
    ui->lblOwnership->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setPreferredIOSize(long value){
    ui->lblPreferredIOSize->setText(QString::number(value) + "B");
    return this;
}

FileStatDialog *FileStatDialog::setSize(long long value){
    if(1){
        if (value <= 1000){
            ui->lblFileSize->setText(QString::number(value) + "B");
          }else if (value <= 1000000){
            ui->lblFileSize->setText(QString::number(value/1000.0, 'f', 2) + "KB");
          }else if(value <= 1000000000){
            ui->lblFileSize->setText(QString::number(value/1000000.0, 'f', 2) + "MB");
          }else{
            ui->lblFileSize->setText(QString::number(value/1000000000.0, 'f', 2) + "GB");
          }
    }else{
        ui->lblFileSize->setText(QString::number(value) + "B");
    }
    return this;
}

FileStatDialog *FileStatDialog::setNumberOfBlocks(long long value){
    ui->lblBlocksAllocated->setText(QString::number(value) + " Blocks");
    return this;
}

FileStatDialog *FileStatDialog::setLastStatusChange(QString value){
    ui->lblLastStatus->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setLastFileAccess(QString value){
    ui->lblLastFileAccess->setText(value.trimmed());
    return this;
}

FileStatDialog *FileStatDialog::setLastModification(QString value){
    ui->lblLastFileModification->setText(value.trimmed());
    return this;
}


