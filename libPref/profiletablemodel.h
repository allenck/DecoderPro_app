#ifndef PROFILETABLEMODEL_H
#define PROFILETABLEMODEL_H
#include "abstracttablemodel.h"

class PropertyChangeEvent;
class ProfileTableModel : public AbstractTableModel
{
    Q_OBJECT
public:
    explicit ProfileTableModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* evt);

};

#endif // PROFILETABLEMODEL_H
