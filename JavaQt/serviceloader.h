#ifndef SERVICELOADER_H
#define SERVICELOADER_H

#include <QObject>
#include "iterator.h"

class ClassLoader;
class AccessControlContext;
//class LazyIterator;
template <typename Key, typename T>
class OrderedMap
{
    public:
         // ... all your functions here, straigtforward enough to use indexOf()...
    OrderedMap(Key key, T value) { m_keys.append(key); m_values = value;}
    void clear() { m_keys.clear(); m_values.clear();}
    private:
       QList<Key> m_keys;
       QList<T> m_values;
};

template<typename S>
class ServiceLoader
{
public:
 //explicit ServiceLoader(QObject *parent = 0);
 /*public*/ static ServiceLoader<S>* load(QString service, ClassLoader* loader);
 /*public*/ static ServiceLoader<S>* load(QString service);
 /*public*/ void reload();
 /*public*/ QString toString();

signals:

public slots:

private:
 /*private*/ static /*final*/ QString PREFIX;// = "META-INF/services/";

 // The class or interface representing the service being loaded
 /*private*/ /*final*/ QString service;

 // The class loader used to locate, load, and instantiate providers
 /*private*/ /*final*/ ClassLoader* loader;

 // The access control context taken when the ServiceLoader is created
 /*private*/ /*final*/ AccessControlContext* acc;

 // Cached providers, in instantiation order
 /*private*/ /*LinkedHashMap<String,S>*/ OrderedMap<QString, S>* providers;// = new OrderedMap<QString, S>();
 /*private*/ ServiceLoader(QString svc, ClassLoader* cl);

 // The current lazy-lookup iterator

 /*private*/ class LazyIterator : public QListIterator<S>
 {
     QString service;
     ClassLoader* loader;
     QListIterator<QUrl>* configs;// = null;
     QListIterator<QString>* pending;// = null;
     QString nextName;// = null;
     ServiceLoader* sl;

     /*private*/ LazyIterator(QString service, ClassLoader* loader, ServiceLoader* sl);
     /*private*/ bool hasNextService();
     /*private*/ S nextService();
     /*public*/ bool hasNext();
     /*public*/ S next();
     /*public*/ void remove();
 };
 // The current lazy-lookup iterator
 /*private*/ LazyIterator* lookupIterator;

 // Private inner class implementing fully-lazy provider lookup
 //
friend class StartupActionsManager;
};

#endif // SERVICELOADER_H
