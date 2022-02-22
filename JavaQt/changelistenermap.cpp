#include "changelistenermap.h"
#include "eventlistenerproxy.h"

template<class L>
ChangeListenerMap<L>::ChangeListenerMap(QObject *parent) :
    QObject(parent)
{
 map = new QMap<QString, QVector<L>* >;
 //map = NULL;
}
/**
 * This is an abstract class that provides base functionality
 * for the {@link PropertyChangeSupport PropertyChangeSupport} class
 * and the {@link VetoableChangeSupport VetoableChangeSupport} class.
 *
 * @see PropertyChangeListenerMap
 * @see VetoableChangeListenerMap
 *
 * @author Sergey A. Malenkov
 */
//abstract class ChangeListenerMap<L extends EventListener> {
//    private Map<QString, QList<L>> map;


    /**
     * Creates a proxy listener for the specified property.
     *
     * @param name      the name of the property to listen on
     * @param listener  the listener to process events
     * @return          a proxy listener
     */
//    L ChangeListenerMap::newProxy(QString name, L* listener);

    /**
     * Adds a listener to the list of listeners for the specified property.
     * This listener is called as many times as it was added.
     *
     * @param name      the name of the property to listen on
     * @param listener  the listener to process events
     */
template<class L>
    void ChangeListenerMap<L>::add(QString name, L listener) {
     QMutexLocker locker(mutex);
     if (this->map == NULL)
     {
      this->map = new QMap<QString, QVector<L>* >;
      QVector<L>* array = new QVector<L>();
      array->append(listener);
      this->map->insert(name, array);
      return;
     }
     if(!this->map->contains(name))
     {
      QVector<L>* array = new QVector<L>();
      array->append(listener);
      this->map->insert(name, array);
      return;
     }
      this->map->value(name)->append(listener);
    }

    /**
     * Removes a listener from the list of listeners for the specified property.
     * If the listener was added more than once to the same event source,
     * this listener will be notified one less time after being removed.
     *
     * @param name      the name of the property to listen on
     * @param listener  the listener to process events
     */
    template<class L>
    /*public final synchronized */void ChangeListenerMap<L>::remove(QString name, L listener) {
     QMutexLocker locker(mutex);
     if (this->map != NULL)
     {
      QVector<L>* array = this->map->value(name);
      if (!array->isEmpty())
      {
       for (int i = 0; i < array->length(); i++)
       {
        if (listener == (array->at(i)))
        {
         int size = array->length() - 1;
         if (size > 0)
         {
#if 0
//      QVector<L> clone; // = newArray(size);
//      //System.arraycopy(array, 0, clone, 0, i);
//      foreach(L val, array )
//       clone.append(val);
//      //System.arraycopy(array, i + 1, clone, i, size - i);
//      this->map->insert(name, clone);

      this->map.value(name)->removeAt(i);
#else
      QVector<L>* clone = new QVector<L>(size);
      //System.arraycopy(array, 0, clone, 0, i)
      for(int j=0; j<i; j++) clone->replace(j, array->at(j));
      //System.arraycopy(array, i + 1, clone, i, size - i)
      for(int j=i+1; j < array->size(); j++) clone->replace(j-1, array->at(j));
      this->map.insert(name, clone);
#endif
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
    template<class L>
    /*public final synchronized*/ QVector<L> ChangeListenerMap<L>::get(QString name)
     {
      QMutexLocker locker(mutex);

      return (this->map != NULL && !this->map->isEmpty())
                 ? (this->map->contains(name)? *this->map->value(name): QVector<L>())
                 : QVector<L>();
    }

    /**
     * Sets new list of listeners for the specified property.
     *
     * @param name       the name of the property
     * @param listeners  new list of listeners
     */
     template<class L>
    /*public final*/ void ChangeListenerMap<L>::set(QString name, QVector<L>* listeners) {
      if (listeners != NULL)
      {
       if (this->map == NULL)
       {
        this->map = new QMap<QString, QVector<L>* >;
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
      }    }

    /**
     * Returns all listeners in the map.
     *
     * @return an array of all listeners
     */
    template<class L>
    /*public final synchronized*/ QVector<L> ChangeListenerMap<L>::getListeners()
    {
      QMutexLocker locker(mutex);
      QVector<L> listeners = QVector<L>();
      if(map!= nullptr && !map->values().isEmpty)
      {
       foreach(QString key, map->values())
       {
        foreach(L listener, *map->value(key))
         listeners.append(listener);
       }
       return QVector<L>(listeners);
      }
      return QVector<L>();
    }

    /**
     * Returns listeners that have been associated with the named property.
     *
     * @param name  the name of the property
     * @return an array of listeners for the named property
     */
    template<class L>/*public final*/ QVector<L> ChangeListenerMap<L>::getListeners(QString name)
     {
     if (!name.isNull()) {
         QVector<L>* listeners = this->map->value(name);
         if (!listeners->isEmpty()) {
             //return listeners.clone();
             return QVector<L>(*listeners);
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
    template<class L>
    /*public final synchronized*/ bool ChangeListenerMap<L>::hasListeners(QString name) {
     QMutexLocker locker(mutex);
     if (this->map == NULL)
     {
      return false;
     }
     QVector<L>* array = this->map->value(NULL);
        return (!array ->isEmpty()) || ((!name.isEmpty()) && (this->map->value(name)->isEmpty()));
    }
#if 0
    /**
     * Returns a set of entries from the map.
     * Each entry is a pair consisted of the property name
     * and the corresponding list of listeners.
     *
     * @return a set of entries from the map
     */
    /*public final*/ QMap<Entry<QString, QList<L>>> ChangeListenerMap::getEntries() {
        return (this->map != NULL)
                ? this->map.entrySet()
                : Collections.<Entry<QString, QList<L>>>emptySet();
    }
#endif
    template<class L>
    /*public*/ L ChangeListenerMap<L>::extract(L listener)
    {
    }
