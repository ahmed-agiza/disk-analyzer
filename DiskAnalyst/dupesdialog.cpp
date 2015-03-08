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

void DupesDialog::setDuplicates(QList<StringPair> dupes){
    duplicates = dupes;
    model = new DuplicatesDataModel(this, dupes);
    connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)), this, SLOT(refreshTableView()));
    ui->tblDuplicates->setModel(model);
    ui->tblDuplicates->resizeColumnsToContents();
    /*ui->tblDuplicates->setRowCount(0);
    for(int i = 0; i < dupes.size(); i++){
        QTableWidgetItem *firstEntry = new QTableWidgetItem(dupes[i].first);
        QTableWidgetItem *firstView = new QTableWidgetItem(QIcon(":/icons/Icons/Folder-Open-icon (1).png"), "");
        QTableWidgetItem *firstDelete = new QTableWidgetItem(QIcon(":/icons/Icons/Actions-dialog-cancel-icon.png"), "");

        QTableWidgetItem *secondEntry = new QTableWidgetItem(dupes[i].second);
        QTableWidgetItem *secondView = new QTableWidgetItem(QIcon(":/icons/Icons/Folder-Open-icon (1).png"), "");
        QTableWidgetItem *secondDelete = new QTableWidgetItem(QIcon(":/icons/Icons/Actions-dialog-cancel-icon.png"), "");


        firstEntry->setTextAlignment(Qt::AlignCenter);
        firstView->setTextAlignment(Qt::AlignCenter);
        firstDelete->setTextAlignment(Qt::AlignCenter);
        secondEntry->setTextAlignment(Qt::AlignCenter);
        secondView->setTextAlignment(Qt::AlignCenter);
        secondDelete->setTextAlignment(Qt::AlignCenter);

        int row = ui->tblDuplicates->rowCount();
        ui->tblDuplicates->insertRow(row);
        ui->tblDuplicates->setItem(row, 0, firstEntry);
        ui->tblDuplicates->setItem(row, 1, firstView);
        ui->tblDuplicates->setItem(row, 2, firstDelete);
        ui->tblDuplicates->setItem(row, 3, secondEntry);
        ui->tblDuplicates->setItem(row, 4, secondView);
        ui->tblDuplicates->setItem(row, 5, secondDelete);
    }
    ui->tblDuplicates->resizeColumnsToContents();
    ui->tblDuplicates->resizeRowsToContents();
    int totalWidth = 0;
    for(int i = 0; i < ui->tblDuplicates->colorCount(); i++){
        totalWidth += ui->tblDuplicates->columnWidth(i);
    }
    resize(totalWidth + 20, height());*/
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


