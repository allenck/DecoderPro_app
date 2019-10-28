#ifndef JLISTTABLEMODEL_H
#define JLISTTABLEMODEL_H
#include "abstractlistmodel.h"

class JListTableModel : public AbstractListModel
{
public:
 JListTableModel(QStringList list, QObject *parent= nullptr);
 int rowCount(const QModelIndex &parent) const;
 QVariant data(const QModelIndex &index, int role) const;

private:
 QStringList list;
};

#endif // JLISTTABLEMODEL_H
