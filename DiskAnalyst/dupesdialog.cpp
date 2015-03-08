#include "dupesdialog.h"
#include "ui_dupesdialog.h"

#include "mainwindow.h"

#include <QTableWidgetItem>
#include <QMessageBox>

DupesDialog::DupesDialog(QWidget *parent) :
    QDialog(parent), ui(new Ui::DupesDialog){
    ui->setupUi(this);
    QPalette palette = ui->tblDuplicates->palette();
    palette.setBrush(QPalette::Highlight,QBrush(Qt::white));
    palette.setBrush(QPalette::HighlightedText,QBrush(Qt::black));
    ui->tblDuplicates->setPalette(palette);
    ui->tblDuplicates->setFocusPolicy(Qt::NoFocus);
    ui->tblDuplicates->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
}

void DupesDialog::setDuplicates(DuplicateEntryList dupes){
    duplicates = dupes;
    model = new DuplicatesDataModel(this, dupes);
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(refreshTableView()));
    ui->tblDuplicates->setModel(model);
    ui->tblDuplicates->resizeColumnsToContents();

}

DupesDialog::~DupesDialog(){
    delete ui;
}

void DupesDialog::showEvent(QShowEvent *event){
    QDialog::showEvent(event);

}

int DupesDialog::deleteFile(QString filePath){
    if (QMessageBox::critical(this, "Delete File", QString("Are you sure you want to delete the file: \n") + filePath + "?", QMessageBox::No | QMessageBox::Yes, QMessageBox::No)
        != QMessageBox::Yes)
        return 0;
    QFile file(filePath);
    return file.remove();
}


void DupesDialog::openFolder(QString filePath){
    QString openPath;
    QFileInfo fileInfo(filePath);
    if (fileInfo.isDir())
        openPath = filePath;
    else if (!fileInfo.exists()){
        qDebug() << filePath << " does not exits";
        return;
    }else{
        openPath = fileInfo.absolutePath();
        qDebug() << "Opening " << openPath;
    }
    MainWindow::openDirectory(openPath, this);
}

void DupesDialog::refreshTableView(){
    ui->tblDuplicates->repaint();
    ui->tblDuplicates->setModel(model);
}

void DupesDialog::on_tblDuplicates_clicked(const QModelIndex &index){
   if (index.column() == 1){
        openFolder(model->firstEntry(index.row()));
    }else if (index.column() == 2){
        QString deletePath = model->firstEntry(index.row());
        int returnCode = deleteFile(deletePath);
        qDebug() << returnCode;
        if(returnCode == 1){
            model->removeAllEntries(deletePath);
        }else if (returnCode)
            QMessageBox::critical(this, "Error", "Could not remove the file " + deletePath);
    }else if (index.column() == 4){
        openFolder(model->secondEntry(index.row()));
    }else if (index.column() == 5){
        QString deletePath = model->secondEntry(index.row());
        int returnCode = deleteFile(deletePath);
        if(returnCode == 1){
            model->removeAllEntries(deletePath);
        }else if (returnCode)
            QMessageBox::critical(this, "Error", "Could not remove the file " + deletePath);
    }

}


