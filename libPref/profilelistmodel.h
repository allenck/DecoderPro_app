#ifndef PROFILELISTMODEL_H
#define PROFILELISTMODEL_H
#include "abstractlistmodel.h"
#include "libpref_global.h"

class PropertyChangeEvent;
class LIBPREFSHARED_EXPORT ProfileListModel : public AbstractListModel
{
    Q_OBJECT
public:
    explicit ProfileListModel(QObject *parent = 0);
    /*public*/ int getSize() ;
    /*public*/ QObject* getElementAt(int index);
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    void reset();
signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent *evt);
private:
    /*private*/ void fireContentsChanged(int index0, int index1);
    /*private*/ void fireIntervalAdded(int index0, int index1);
    /*private*/ void fireIntervalRemoved(int index0, int index1);

};

#endif // PROFILELISTMODEL_H
