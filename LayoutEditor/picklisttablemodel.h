#ifndef PICKLISTTABLEMODEL_H
#define PICKLISTTABLEMODEL_H

#include <QAbstractTableModel>

class PickListTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit PickListTableModel(QObject *parent = 0);
    virtual int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant data(const QModelIndex &index, int role) const;
    void fireTableDataChanged();
    void fireTableRowsUpdated(int r1, int r2);

signals:

public slots:

};

#endif // PICKLISTTABLEMODEL_H
