#ifndef DUPLICATESDATAMODEL_H
#define DUPLICATESDATAMODEL_H

#include <QAbstractItemModel>

class DuplicatesDataModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit DuplicatesDataModel(QObject *parent = 0);

signals:

public slots:

};

#endif // DUPLICATESDATAMODEL_H
