#ifndef DUPLICATESDATAMODEL_H
#define DUPLICATESDATAMODEL_H

#include <QAbstractItemModel>

typedef QPair<QString, QString> StringPair;
typedef QList<StringPair> StringPairList;

class DuplicatesDataModel : public QAbstractTableModel
{
    Q_OBJECT
    StringPairList duplicates;
public:
    explicit DuplicatesDataModel(QObject *parent = 0, StringPairList = StringPairList());

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
