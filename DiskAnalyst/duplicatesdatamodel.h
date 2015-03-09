#ifndef DUPLICATESDATAMODEL_H
#define DUPLICATESDATAMODEL_H

#include <QAbstractItemModel>

#include "dupeschecker.h"

typedef QPair<QString, QString> StringPair;
typedef QList<StringPair> StringPairList;

class DuplicatesDataModel : public QAbstractTableModel
{
    Q_OBJECT
    DuplicateEntryList duplicates;
public:
    explicit DuplicatesDataModel(QObject *parent = 0, DuplicateEntryList = DuplicateEntryList());

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    void emitDataChanged();
    void removeAllEntries(QString);
    QString firstEntry(int index) const;
    QString secondEntry(int index) const;
    ~DuplicatesDataModel();
signals:

public slots:

};



#endif // DUPLICATESDATAMODEL_H
