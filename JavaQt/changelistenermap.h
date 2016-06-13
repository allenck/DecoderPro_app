#ifndef CHANGELISTENERMAP_H
#define CHANGELISTENERMAP_H

#include <QObject>
#include "eventlistener.h"
#include <QMap>
#include <QMutex>

template <class L>
class ChangeListenerMap : public EventListener
{

    //Q_OBJECT
public:
    ChangeListenerMap(QObject *parent = 0) : EventListener(parent)
 {
  map = new QMap<QString, QList<L> >;
  //map = NULL;
 }

/**
 * Adds a listener to the list of listeners for the specified property.
 * This listener is called as many times as it was added.
 *
 * @param name      the name of the property to listen on
 * @param listener  the listener to process events
 */
//    public final synchronized
void add(QString name, L listener)
{
 QMutexLocker locker(&mutex);
 if (this->map == NULL)
 {
  this->map = new QMap<QString, QList<L> >;
 }
 QList<L> array = this->map->value(name);
//        int size = (array != NULL)
//                ? array.count()
//                : 0;
 int size = array.count();

 QList<L> clone; // = newArray(size + 1);
 clone.reserve(size+1);
 for(int i=0; i < size+1; i++)
  clone << NULL;
 clone.replace(size, listener);
 if (!array.isEmpty())
 {
  //System.arraycopy(array, 0, clone, 0, size);
  int k=0;
  foreach(L val, array )
  {
    //clone.append(val);
   clone.replace(k++,val);
  }
 }
 this->map->insert(name, clone);
}
/*public final synchronized */
void remove(QString name, L listener)
{
 QMutexLocker locker(&mutex);
 if (this->map != NULL)
 {
  QList<L> array = this->map->value(name);
  if (!array .isEmpty())
  {
   for (int i = 0; i < array.length(); i++)
   {
    if (listener == (array[i]))
    {
     int size = array.length() - 1;
     if (size > 0)
     {
      QList<L> clone; // = newArray(size);
      //System.arraycopy(array, 0, clone, 0, i);
      foreach(L val, array )
       clone.append(val);
      //System.arraycopy(array, i + 1, clone, i, size - i);
      this->map->insert(name, clone);
     }
     else
     {
      this->map->remove(name);
      if (this->map->isEmpty())
      {
       this->map = NULL;
      }
     }
     break;
    }
   }
  }
 }
}
/**
 * Returns the list of listeners for the specified property.
 *
 * @param name  the name of the property
 * @return      the corresponding list of listeners
 */
/*public final synchronized*/
QList<L> get(QString name)
{
 QMutexLocker locker(&mutex);

 return (this->map != NULL && !this->map->isEmpty())
            ? this->map->value(name)
            : QList<L>();
}
/**
 * Sets new list of listeners for the specified property.
 *
 * @param name       the name of the property
 * @param listeners  new list of listeners
 */
/*public final*/
void set(QString name, QList<L> listeners)
{
 if (listeners != NULL)
 {
  if (this->map == NULL)
  {
   this->map = new QMap<QString, QList<L> >;
  }
  this->map->put(name, listeners);
 }
 else if (this->map != NULL)
 {
  this->map->remove(name);
  if (this->map.isEmpty())
  {
   this->map = NULL;
  }
 }
}
/**
 * Returns all listeners in the map.
 *
 * @return an array of all listeners
 */
/*public final synchronized*/
QList<L>* getListeners()
{
  //QMutexLocker locker(&mutex);

    if (this->map == NULL) {
        return NULL;
    }
    QList<L>* list = new QList<L>();

    QList<L> listeners = this->map->value("");
    if (!listeners.isEmpty()) {
        foreach (L listener , listeners) {
            list->append(listener);
        }
    }
#if 1
//    foreach((Entry<QString, QList<L*>> entry), this->map->entrySet())
//    {
//        QString name = entry.getKey();
//        if (name != NULL) {
//            foreach (L* listener , entrygetValue()) {
//                listadd(newProxy(name, listener));
//            }
//        }
//    }
    QMapIterator<QString, QList<L> > entry(*this->map);
    while(entry.hasNext())
    {
     entry.next();
     QString name = entry.key();
     if (name != NULL)
     {
      foreach (L listener , entry.value())
      {
       //listadd(newProxy(name, listener));
       list->append(newProxy(name, listener));
      }
     }
    }
#endif
        return list/*.toArray(newArray(list.size()))*/;
}
/**
 * Returns listeners that have been associated with the named property.
 *
 * @param name  the name of the property
 * @return an array of listeners for the named property
 */
/*public final*/
QList<L>* getListeners(QString name){
    if (!name.isNull()) {
        QList<L> listeners = this->map->value(name);
        if (!listeners.isEmpty()) {
            //return listeners.clone();
            return new QList<L>();
        }
    }
    return new QList<L>();
}
/**
 * Indicates whether the map contains
 * at least one listener to be notified.
 *
 * @param name  the name of the property
 * @return      {@code true} if at least one listener exists or
 *              {@code false} otherwise
 */
/*public final synchronized*/
bool hasListeners(QString name)
{
 QMutexLocker locker(&mutex);
 if (this->map == NULL)
 {
  return false;
 }
 QList<L> array = this->map->value(NULL);
    return (!array .isEmpty()) || ((!name.isEmpty()) && (this->map->value(name).isEmpty()));
}
#if 0
/**
 * Returns a set of entries from the map.
 * Each entry is a pair consisted of the property name
 * and the corresponding list of listeners.
 *
 * @return a set of entries from the map
 */
/*public final*/
QMap<Entry<QString, QList<L*> > > getEntries()
{
 QMap<Entry<QString, QList<L*> > > emptySet;
 return (this.map != null)
            ? this.map.entrySet()
            //: Collections.<Entry<String, L[]>>emptySet();
            : emptySet;
}
#endif
/**
 * Extracts a real listener from the proxy listener.
 * It is necessary because default proxy class is not serializable.
 *
 * @return a real listener
 */
/*public abstract*/
L extract(L listener);
signals:

public slots:
private:
 QMap<QString, QList<L> >* map;
 QMutex mutex;
protected:
/**
 * Creates an array of listeners.
 * This method can be optimized by using
 * the same instance of the empty array
 * when {@code length} is equal to {@code 0}.
 *
 * @param length  the array length
 * @return        an array with specified length
 */
virtual QList<L> newArray(int length) = 0;
/**
 * Creates a proxy listener for the specified property.
 *
 * @param name      the name of the property to listen on
 * @param listener  the listener to process events
 * @return          a proxy listener
 */
virtual L newProxy(QString name, L listener) =0;
    
};

#endif // CHANGELISTENERMAP_H
