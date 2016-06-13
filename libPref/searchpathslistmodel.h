#ifndef SEARCHPATHSLISTMODEL_H
#define SEARCHPATHSLISTMODEL_H
#include "abstractlistmodel.h"
#include "libpref_global.h"
class IndexedPropertyChangeEvent;
class PropertyChangeEvent;
class LIBPREFSHARED_EXPORT SearchPathsListModel : public AbstractListModel
{
    Q_OBJECT
public:
    explicit SearchPathsListModel(QObject *parent = 0);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    /*public*/ int getSize();
signals:

public slots:
    /*public*/ void propertyChange(IndexedPropertyChangeEvent* evt);
private:
    /*private*/ void fireContentsChanged(int index0, int index1);
    /*private*/ void fireIntervalAdded(int index0, int index1);
    /*private*/ void fireIntervalRemoved(int index0, int index1) ;

};

#endif // SEARCHPATHSLISTMODEL_H
