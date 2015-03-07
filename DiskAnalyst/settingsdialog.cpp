#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include "settingsmanager.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>


SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::SettingsDialog){
    ui->setupUi(this);
    loadValues();
    setModal(true);
    setWindowTitle("Settings");
    refreshDisplayReableButton();
    connect(ui->rbtSize, SIGNAL(clicked()), this, SLOT(refreshDisplayReableButton()));
    connect(ui->rbtBlocks, SIGNAL(clicked()), this, SLOT(refreshDisplayReableButton()));
}

SettingsDialog::~SettingsDialog(){
    delete ui;
}

void SettingsDialog::SettingsDialog::showEvent(QShowEvent *event){
    QDialog::showEvent(event);
    loadValues();
}

void SettingsDialog::loadValues(){
    ui->lblStartupDirectory->setText(SettingsManager::getStartupDir());
    ui->chkReadable->setChecked(SettingsManager::getHumanReadable());
    if (SettingsManager::getListEntriesByBlocks()){
        ui->rbtBlocks->setChecked(true);
        ui->rbtSize->setChecked(false);
        ui->chkReadable->setEnabled(false);
    }else{
        ui->rbtBlocks->setChecked(false);
        ui->rbtSize->setChecked(true);
    }
    ui->chkFading->setChecked(SettingsManager::getFadeEnabled());
    ui->chkNavigate->setChecked(SettingsManager::getNavigateChart());
    ui->sbxGraphDepth->setValue(SettingsManager::getGrapthDepth());
}

bool SettingsDialog::saveValues(){
    int graphDepth = ui->sbxGraphDepth->value();
    if (graphDepth < 1 || graphDepth > 5){
        QMessageBox::critical(this, "Error", QString("Invalid graph depth ") + QString::number(ui->sbxGraphDepth->value()));
        return false;
    }
    QString startupDir = ui->lblStartupDirectory->text();
    if (!startupDir.endsWith("/"))
        startupDir.append("/");
    QFileInfo dirInfo(startupDir);
    if(!dirInfo.exists() || !dirInfo.isDir()){
        QMessageBox::critical(this, "Error", QString("Invalid directory ") + startupDir);
        return false;
    }
    if (ui->rbtBlocks->isChecked() == ui->rbtSize->isChecked()){
        QMessageBox::critical(this, "Error", "Invalid choice for entries listing");
        return false;
    }
    if (ui->rbtSize->isChecked()){
        SettingsManager::setListEntriesByBlocks(false);
        SettingsManager::setHumanReadable(ui->chkReadable->isChecked());
    }else{
        SettingsManager::setListEntriesByBlocks(true);
    }
    SettingsManager::setFadeEnabled(ui->chkFading->isChecked());
    SettingsManager::setGrapthDepth(graphDepth);
    SettingsManager::setNavigateChart(ui->chkNavigate->isChecked());
    SettingsManager::setStartupDir(startupDir);
    return true;
}



void SettingsDialog::on_bbxOkCancel_clicked(QAbstractButton *button){
    if (ui->bbxOkCancel->standardButton(button) == QDialogButtonBox::Ok){
        if(saveValues()){
            setResult(QDialog::Accepted);
            hide();
        }else
            setResult(QDialog::Rejected);

    }else if (ui->bbxOkCancel->standardButton(button) == QDialogButtonBox::RestoreDefaults){
        loadDefaultValues();
    }
}

void SettingsDialog::refreshDisplayReableButton(){
    if(ui->rbtSize->isChecked()){
       ui->chkReadable->setEnabled(true);
       ui->rbtBlocks->setChecked(false);
    }else{
        ui->chkReadable->setEnabled(false);
        ui->rbtSize->setChecked(false);
    }
}

void SettingsDialog::on_btnStartupDirectory_clicked(){
    QString directory = QFileDialog::getExistingDirectory(this, "Select Root Directory..", ui->lblStartupDirectory->text());
    if (directory.trimmed() == "")
        return;
    if(!directory.endsWith("/"))
        directory.append("/");
    if(!QFileInfo(directory).isDir()){
        QMessageBox::critical(this, "Error", "Invalid directory " + directory);
        return;
    }
    ui->lblStartupDirectory->setText(directory);
}

void SettingsDialog::loadDefaultValues(){
    ui->lblStartupDirectory->setText(SettingsManager::defaultStartupDir());
    ui->chkReadable->setChecked(SettingsManager::defaultHumanReadable());
    if (SettingsManager::defaultListEntriesByBlocks()){
        ui->rbtBlocks->setChecked(true);
        ui->rbtSize->setChecked(false);
        ui->chkReadable->setEnabled(false);
    }else{
        ui->rbtBlocks->setChecked(false);
        ui->rbtSize->setChecked(true);
    }
    ui->chkFading->setChecked(SettingsManager::defaultFadeEnabled());
    ui->chkNavigate->setChecked(SettingsManager::defaultNavigateChart());
    ui->sbxGraphDepth->setValue(SettingsManager::defaultGraphDepth());
}
