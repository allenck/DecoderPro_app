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
    ChangeListenerMap() : EventListener()
 {
  map = new QMap<QString, QVector<L> >;
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
  this->map = new QMap<QString, QVector<L> >;
 }
 QVector<L> array = this->map->value(name);
//        int size = (array != NULL)
//                ? array.count()
//                : 0;
 int size = array.count();

 QVector<L> clone = newArray(size + 1);
 //clone.reserve(size+1);
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
  QVector<L> array = this->map->value(name);
  if (!array .isEmpty())
  {
   for (int i = 0; i < array.length(); i++)
   {
    if (listener == (array[i]))
    {
     int size = array.length() - 1;
     if (size > 0)
     {
      QVector<L> clone; // = newArray(size);
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
QVector<L> get(QString name)
{
 QMutexLocker locker(&mutex);

 return (this->map != NULL && !this->map->isEmpty())
            ? this->map->value(name)
            : QVector<L>();
}
/**
 * Sets new list of listeners for the specified property.
 *
 * @param name       the name of the property
 * @param listeners  new list of listeners
 */
/*public final*/
void set(QString name, QVector<L> listeners)
{
 if (listeners != NULL)
 {
  if (this->map == NULL)
  {
   this->map = new QMap<QString, QVector<L> >;
  }
  this->map->insert(name, listeners);
 }
 else if (this->map != NULL)
 {
  this->map->remove(name);
  if (this->map->isEmpty())
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
QVector<L> getListeners()
{
  //QMutexLocker locker(&mutex);

    if (this->map == NULL) {
        return QVector<L>();
    }
    QVector<L> list = QVector<L>();

    QVector<L> listeners = this->map->value("");
    if (!listeners.isEmpty()) {
        foreach (L listener , listeners) {
            list.append(listener);
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
    QMapIterator<QString, QVector<L> > entry(*this->map);
    while(entry.hasNext())
    {
     entry.next();
     QString name = entry.key();
     if (name != NULL)
     {
      foreach (L listener , entry.value())
      {
       //listadd(newProxy(name, listener));
       list.append(newProxy(name, listener));
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
QVector<L> getListeners(QString name){
    if (!name.isNull()) {
        QVector<L> listeners = this->map->value(name);
        if (!listeners.isEmpty()) {
            //return listeners.clone();
            return QVector<L>();
        }
    }
    return QVector<L>();
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
 QVector<L> array = this->map->value(NULL);
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
 QMap<QString, QVector<L> >* map;
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
virtual QVector<L> newArray(int length) = 0;
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
