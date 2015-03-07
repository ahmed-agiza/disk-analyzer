#include "duplicatesdatamodel.h"

#include <QIcon>
#include <QDebug>

DuplicatesDataModel::DuplicatesDataModel(QObject *parent, StringPairList dupes) :
    QAbstractTableModel(parent), duplicates(dupes){
}

int DuplicatesDataModel::rowCount(const QModelIndex &) const{

    return duplicates.size();
}

int DuplicatesDataModel::columnCount(const QModelIndex &) const{
    return 6;
}

QVariant DuplicatesDataModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid() || index.row() >= rowCount(QModelIndex()) || index.row() < 0 || index.column() < 0 || index.column() > 5)
        return QVariant();
    if (role == Qt::DecorationRole){
        if(index.column() == 1 || index.column() == 4)
            return QVariant(QIcon(":/icons/Icons/Folder-Open-icon (1).png"));
        if (index.column() == 2 || index.column() == 5)
            return QVariant(QIcon(":/icons/Icons/Actions-dialog-cancel-icon.png"));
    }else if (role == Qt::DisplayRole){
        if(index.column() == 0)
            return duplicates[index.row()].first;
        if (index.column() == 3)
            return duplicates[index.row()].second;
        return QVariant();

    }
    return QVariant();
}

QVariant DuplicatesDataModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal)
    {
        switch (section) {
        case 0:
            return QVariant("First Entry");
        case 3:
            return QVariant("Second Entry");

        default:
            return QVariant("");


            return QVariant();
        }
    }

    return QVariant();
}

Qt::ItemFlags DuplicatesDataModel::flags(const QModelIndex &index) const{
    return QAbstractTableModel::flags(index);
}

void DuplicatesDataModel::removeAllEntries(QString fileName){
    for(int i = 0; i < duplicates.size(); i++)
        if (duplicates[i].first.trimmed() == fileName.trimmed() || duplicates[i].second.trimmed() == fileName.trimmed())
            duplicates.removeAt(i--);

    qDebug() << "New size: " << duplicates.size();
    emit dataChanged(QModelIndex(), QModelIndex());

}

QString DuplicatesDataModel::firstEntry(int index) const{
    if (index >= 0 && index < duplicates.size())
        return duplicates[index].first;
    return QString();
}

QString DuplicatesDataModel::secondEntry(int index) const{
    if (index >= 0 && index < duplicates.size())
        return duplicates[index].second;
    return QString();
}

DuplicatesDataModel::~DuplicatesDataModel(){

}
