#ifndef ABSTRACTLISTMODEL_H
#define ABSTRACTLISTMODEL_H
#include "listmodel.h"
#include "javaqt_global.h"
#include "listdataevent.h"

class EventListenerList;
class JAVAQTSHARED_EXPORT AbstractListModel : public ListModel
{
    Q_OBJECT
public:
    explicit AbstractListModel(QObject *parent = 0);
 virtual ~AbstractListModel() {}
    /*public*/ void addListDataListener(ListDataListener* l);
    /*public*/ void removeListDataListener(ListDataListener* l);
    /*public*/ QList<ListDataListener*>* getListDataListeners();

signals:
 void contentsChanged(ListDataEvent*);

public slots:
private:
protected:
//    /*protected*/ EventListenerList* listenerList;// = new EventListenerList();
    /*protected*/ void fireContentsChanged(QObject* source, int index0, int index1);
    /*protected*/ void fireIntervalAdded(QObject* source, int index0, int index1);
    /*protected*/ void fireIntervalRemoved(QObject* source, int index0, int index1);

};

#endif // ABSTRACTLISTMODEL_H
