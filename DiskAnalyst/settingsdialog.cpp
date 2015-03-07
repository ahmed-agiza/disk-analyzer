#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>

const QString STARTUP_DIRECTORY_KEY("startup directory");

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent), settings("AUC Egypt", "Disk Analyzer"), ui(new Ui::SettingsDialog){
    ui->setupUi(this);
    if(!settings.contains(STARTUP_DIRECTORY_KEY))
        ui->lblStartupDirectory->setText(QDir::homePath());
    setModal(true);
    setWindowTitle("Settings");
}

SettingsDialog::~SettingsDialog(){
    delete ui;
}

void SettingsDialog::on_btnStartuoDirectory_clicked(){
    QString directory = QFileDialog::getExistingDirectory(this, "Select Root Directory..", ui->lblStartupDirectory->text());
    if (directory.trimmed() == "")
        return;
    if(!QFileInfo(directory).isDir()){
        QMessageBox::critical(this, "Error", "Invalid directory " + directory);
        return;
    }
    ui->lblStartupDirectory->setText(directory);
    ui->letGraphDepth->setValidator(new QIntValidator(0, 5, this));
}



void SettingsDialog::on_bbxOkCancel_clicked(QAbstractButton *button){
    if (ui->bbxOkCancel->standardButton(button) == QDialogButtonBox::Ok){

    }
}
