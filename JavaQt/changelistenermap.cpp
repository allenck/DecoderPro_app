#include "changelistenermap.h"

//ChangeListenerMap<L>::ChangeListenerMap<L>(QObject *parent) :
//    QObject(parent)
//{
//}
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
//    void ChangeListenerMap::add(QString name, L* listener) {
//        if (this->map == NULL) {
//            this->map = new QHash<QString, QList<L*>>;
//        }
//        QList<L> array = this->map->get(name);
//        int size = (array != NULL)
//                ? array.length
//                : 0;

//        QList<L> clone = newArray(size + 1);
//        clone[size] = listener;
//        if (array != NULL) {
//            System.arraycopy(array, 0, clone, 0, size);
//        }
//        this->map->put(name, clone);
//    }

    /**
     * Removes a listener from the list of listeners for the specified property.
     * If the listener was added more than once to the same event source,
     * this listener will be notified one less time after being removed.
     *
     * @param name      the name of the property to listen on
     * @param listener  the listener to process events
     */
//    /*public final synchronized */void ChangeListenerMap::remove(QString name, L* listener) {
//        if (this->map != NULL) {
//            QList<L*> array = this->map->get(name);
//            if (array != NULL) {
//                for (int i = 0; i < array.length; i++) {
//                    if (listener == (array[i])) {
//                        int size = array.length - 1;
//                        if (size > 0) {
//                            QList<L*> clone = newArray(size);
//                            System.arraycopy(array, 0, clone, 0, i);
//                            System.arraycopy(array, i + 1, clone, i, size - i);
//                            this.map.put(name, clone);
//                        }
//                        else {
//                            this.map.remove(name);
//                            if (this.map.isEmpty()) {
//                                this.map = NULL;
//                            }
//                        }
//                        break;
//                    }
//                }
//            }
//        }
//    }

    /**
     * Returns the list of listeners for the specified property.
     *
     * @param name  the name of the property
     * @return      the corresponding list of listeners
     */
//    /*public final synchronized*/ QList<L> ChangeListenerMap::get(QString name) {
//        return (this->map != NULL)
//                ? this->map.get(name)
//                : NULL;
//    }

    /**
     * Sets new list of listeners for the specified property.
     *
     * @param name       the name of the property
     * @param listeners  new list of listeners
     */
//    /*public final*/ void ChangeListenerMap::set(QString name, QList<L> listeners) {
//        if (listeners != NULL) {
//            if (this->map == NULL) {
//                this->map = new QHash<QString, QList<L>>;
//            }
//            this->map->put(name, listeners);
//        }
//        else if (this->map != NULL) {
//            this->map->remove(name);
//            if (this->map.isEmpty()) {
//                this->map = NULL;
//            }
//        }
//    }

    /**
     * Returns all listeners in the map.
     *
     * @return an array of all listeners
     */
//    /*public final synchronized*/ QList<L*> ChangeListenerMap::getListeners() {
//        if (this->map == NULL) {
//            return newArray(0);
//        }
//        QList<L*> list = new QList<L*>();

//        QList<L*> listeners = this.map.get(NULL);
//        if (listeners != NULL) {
//            for (L listener : listeners) {
//                list.add(listener);
//            }
//        }
//        foreach(Entry<QString, QList<L*>> entry , this->map->entrySet()) {
//            QString name = entry.getKey();
//            if (name != NULL) {
//                for (L listener : entry.getValue()) {
//                    list.add(newProxy(name, listener));
//                }
//            }
//        }
//        return list.toArray(newArray(list.size()));
//    }

    /**
     * Returns listeners that have been associated with the named property.
     *
     * @param name  the name of the property
     * @return an array of listeners for the named property
     */
//    /*public final*/ QList<L*> ChangeListenerMap::getListeners(QString name) {
//        if (name != NULL) {
//            QList<L*> listeners = get(name);
//            if (listeners != NULL) {
//                return listeners.clone();
//            }
//        }
//        return newArray(0);
//    }

    /**
     * Indicates whether the map contains
     * at least one listener to be notified.
     *
     * @param name  the name of the property
     * @return      {@code true} if at least one listener exists or
     *              {@code false} otherwise
     */
//    /*public final synchronized*/ bool ChangeListenerMap::hasListeners(QString name) {
//        if (this->map == NULL) {
//            return false;
//        }
//        QList<L*>* array = this->map.get(NULL);
//        return (array != NULL) || ((name != NULL) && (NULL != this->map->get(name)));
//    }
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
