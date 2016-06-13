#ifndef EVENTLISTENERLIST_H
#define EVENTLISTENERLIST_H

#include <QObject>
#include <QVector>

class EventListenerList : public QObject
{
    Q_OBJECT
public:
    explicit EventListenerList(QObject *parent = 0);
    /*public*/ QVector<QObject*>* getListenerList();
    /*public*/ int getListenerCount();
    /*public*/ int getListenerCount(QString t);

signals:

public slots:
private:
    /* A null array to be shared by all empty listener lists*/
    /*private*/ /*final*/ static QVector<QObject*>* NULL_ARRAY;// = new QVector<QObject*>();
    /*private*/ int getListenerCount( QVector<QObject*>* list, QString t);

protected:
    /* The list of ListenerType - Listener pairs */
    /*protected*/ /*transient*/ QVector<QObject*>* listenerList;// = NULL_ARRAY;

};

#endif // EVENTLISTENERLIST_H
