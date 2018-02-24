#ifndef EVENTLISTENERLIST_H
#define EVENTLISTENERLIST_H

#include <QObject>
#include <QVector>
#include "class.h"
#include "eventlistener.h"
#include "loggerfactory.h"

class EventListenerList : public QObject
{
    Q_OBJECT
public:
    explicit EventListenerList(QObject *parent = 0);
    /*public*/ QVector<QObject*> getListenerList();
    /*public*/ int getListenerCount();
    /*public*/ int getListenerCount(QString t);
 //template<class T>
 /*public*/ /*synchronized*/ /*<T extends EventListener>*/  void add(QString t, EventListener* l);
 template<class T>
 /*public*/ /*synchronized*/ /*<T extends EventListener> */void remove(QString t, T* l);
// template <class T>
// /*public*/ /*<T extends EventListener>*/ QVector<T*> getListeners(QString t);
 /*public*/ QString toString();

signals:

public slots:
private:
    /* A null array to be shared by all empty listener lists*/
    /*private*/ /*final*/ static QVector<QObject*> NULL_ARRAY;// = new QVector<QObject*>();
    /*private*/ int getListenerCount( QVector<QObject*>* list, QString t);
 static Logger* log;
protected:
    /* The list of ListenerType - Listener pairs */
    /*protected*/ /*transient*/ QVector<QObject*> listenerList;// = NULL_ARRAY;

};

#endif // EVENTLISTENERLIST_H
