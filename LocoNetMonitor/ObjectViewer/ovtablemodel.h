#ifndef OVTABLEMODEL_H
#define OVTABLEMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include "lnturnout.h"

struct ItemData
{
 QString systemName;
 QString type;
 QString userName;
 QString comment;
};

class OVTableModel : public QAbstractTableModel
{
 Q_OBJECT
public:
 explicit OVTableModel(QObject *parent = 0);
 void setData(QList<ItemData>* mapData);
signals:
    
public slots:

private:
 int rowCount(const QModelIndex &parent) const;
 int columnCount(const QModelIndex &parent) const;
 QVariant data(const QModelIndex &index, int role) const;
 QVariant headerData(int section, Qt::Orientation orientation, int role) const;
 QList<ItemData>* list;
};


#endif // OVTABLEMODEL_H
