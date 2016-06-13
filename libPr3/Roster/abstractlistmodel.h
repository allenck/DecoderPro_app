#ifndef ABSTRACTLISTMODEL_H
#define ABSTRACTLISTMODEL_H
#include "listmodel.h"
#include "libPr3_global.h"

class EventListenerList;
class LIBPR3SHARED_EXPORT AbstractListModel : public ListModel
{
    //Q_OBJECT
public:
    explicit AbstractListModel(QObject *parent = 0);
    /*public*/ void addListDataListener(ListDataListener* l);
    /*public*/ void removeListDataListener(ListDataListener* l);
    /*public*/ QList<ListDataListener*>* getListDataListeners();

signals:

public slots:
private:
protected:
//    /*protected*/ EventListenerList* listenerList;// = new EventListenerList();
    /*protected*/ void fireContentsChanged(QObject* source, int index0, int index1);
    /*protected*/ void fireIntervalAdded(QObject* source, int index0, int index1);
    /*protected*/ void fireIntervalRemoved(QObject* source, int index0, int index1);

};

#endif // ABSTRACTLISTMODEL_H
