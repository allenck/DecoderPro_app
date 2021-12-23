#include "eventlistenerlist.h"
#include "loggerbase.h"

QVector<EventListener*> EventListenerList::NULL_ARRAY =  QVector<EventListener*>();

/*private*/ /*final*/ /*static*/ Logger* EventListenerList::log = LoggerFactory::getLogger("EventListenerList");

EventListenerList::EventListenerList(QObject *parent) :
    QObject(parent)
{
    listenerList = NULL_ARRAY;
}
/**
 * A class that holds a list of EventListeners.  A single instance
 * can be used to hold all listeners (of all types) for the instance
 * using the list.  It is the responsiblity of the class using the
 * EventListenerList to provide type-safe API (preferably conforming
 * to the JavaBeans spec) and methods which dispatch event notification
 * methods to appropriate Event Listeners on the list.
 *
 * The main benefits that this class provides are that it is relatively
 * cheap in the case of no listeners, and it provides serialization for
 * event-listener lists in a single place, as well as a degree of MT safety
 * (when used correctly).
 *
 * Usage example:
 *    Say one is defining a class that sends out FooEvents, and one wants
 * to allow users of the class to register FooListeners and receive
 * notification when FooEvents occur.  The following should be added
 * to the class definition:
 * <pre>
 * EventListenerList listenerList = new EventListenerList();
 * FooEvent fooEvent = NULL;
 *
 * public void addFooListener(FooListener l) {
 *     listenerList.add(FooListener.class, l);
 * }
 *
 * public void removeFooListener(FooListener l) {
 *     listenerList.remove(FooListener.class, l);
 * }
 *
 *
 * // Notify all listeners that have registered interest for
 * // notification on this event type.  The event instance
 * // is lazily created using the parameters passed into
 * // the fire method.
 *
 * protected void fireFooXXX() {
 *     // Guaranteed to return a non-NULL array
 *     Object[] listeners = listenerList.getListenerList();
 *     // Process the listeners last to first, notifying
 *     // those that are interested in this event
 *     for (int i = listeners.length-2; i>=0; i-=2) {
 *         if (listeners[i]==FooListener.class) {
 *             // Lazily create the event:
 *             if (fooEvent == NULL)
 *                 fooEvent = new FooEvent(this);
 *             ((FooListener)listeners[i+1]).fooXXX(fooEvent);
 *         }
 *     }
 * }
 * </pre>
 * foo should be changed to the appropriate name, and fireFooXxx to the
 * appropriate method name.  One fire method should exist for each
 * notification method in the FooListener interface.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author Georges Saab
 * @author Hans Muller
 * @author James Gosling
 */
// /*public*/ class EventListenerList implements Serializable {

/**
 * Passes back the event listener list as an array
 * of ListenerType-listener pairs.  Note that for
 * performance reasons, this implementation passes back
 * the actual data structure in which the listener data
 * is stored internally!
 * This method is guaranteed to pass back a non-NULL
 * array, so that no NULL-checking is required in
 * fire methods.  A zero-length array of Object should
 * be returned if there are currently no listeners.
 *
 * WARNING!!! Absolutely NO modification of
 * the data contained in this array should be made -- if
 * any such manipulation is necessary, it should be done
 * on a copy of the array returned rather than the array
 * itself.
 */
/*public*/ QVector<EventListener*> EventListenerList::getListenerList() {
    return listenerList;
}

/**
 * Return an array of all the listeners of the given type.
 * @return all of the listeners of the specified type.
 * @exception  ClassCastException if the supplied class
 *          is not assignable to EventListener
 *
 * @since 1.3
 */
//template <class T>
/*public*/ /*<T extends EventListener>*/ QVector<EventListener *> EventListenerList::getListeners(QString t) {
    QVector<EventListener*> lList = listenerList;
    int n = getListenerCount(lList, t);
    QVector<EventListener*> result = QVector<EventListener*>(n);//(T[])Array.newInstance(t, n);
    int j = 0;
    for (int i = lList.length()-2; i>=0; i-=2) {
        if (lList.at(i)->self()->metaObject()->className() == t) {
            result.replace(j++, (EventListener*)lList.at(i+1));
        }
    }
    return result;
}

/**
 * Returns the total number of listeners for this listener list.
 */
/*public*/ int EventListenerList::getListenerCount() {
    return listenerList.count()/2;
}

/**
 * Returns the total number of listeners of the supplied type
 * for this listener list.
 */
/*public*/ int EventListenerList::getListenerCount(QString t) {
    QVector<EventListener*> lList = listenerList;
    QVector<QObject*> oList = QVector<QObject*>();
    for(int i=0; i < lList.count(); i++)
     oList.append(lList.at(i)->self());
   // return getListenerCount(lList, t);
    int n =0;
    foreach (QObject* obj, oList) {
     Q_ASSERT(obj->objectName()!= "");
     if(obj->objectName() == t)
      n++;
    }
    return n;
}

/*private*/ int EventListenerList::getListenerCount(QVector<EventListener *> list, QString t)
{
 int count = 0;
 for (int i = 0; i < list.length(); i+=2)
 {
  if (t == list.at(i)->self()->metaObject()->className())
   count++;
 }
 return count;
}

/**
 * Adds the listener as a listener of the specified type.
 * @param t the type of the listener to be added
 * @param l the listener to be added
 */
//template<class T>
/*public*/ /*synchronized*/ /*<T extends EventListener>*/  void EventListenerList::add(QString t, EventListener* l) {
    if (l==NULL) {
        // In an ideal world, we would do an assertion here
        // to help developers know they are probably doing
        // something wrong
        return;
    }
    //if (!t->isInstance(l))
    QObject* obj = l->self();
    if(QString(l->self()->metaObject()->superClass()->className()) != t )
    {
     log->warn("Listener " + QString(l->self()->metaObject()->className()) +
                 " is not of type " + t);
//        throw new IllegalArgumentException("Listener " + QString(l->metaObject()->className()) +
//        + " superclass " +   QString(l->metaObject()->superClass()->className())+                           " is not of type " + t);
    }
    if (listenerList == NULL_ARRAY) {
        // if this is the first listener added,
        // initialize the lists
        listenerList = QVector<EventListener*>(); listenerList << l ;
    } else {
        // Otherwise copy the array and add the new listener
        int i = listenerList.length();
        QVector<EventListener*> tmp = QVector<EventListener*>(i+2);
        //System.arraycopy(listenerList, 0, tmp, 0, i);
        foreach (EventListener* o, listenerList) {
         tmp.append(o);
        }
        tmp.replace(i, (EventListener*)Class::forName(t));
        tmp.replace(i+1, l);

        listenerList = tmp;
    }
}

/**
 * Removes the listener as a listener of the specified type.
 * @param t the type of the listener to be removed
 * @param l the listener to be removed
 */
//template<class T>
/*public*/ /*synchronized*/ /*<T extends EventListener> */void EventListenerList::remove(QString t, EventListener* l) {
    if (l ==NULL) {
        // In an ideal world, we would do an assertion here
        // to help developers know they are probably doing
        // something wrong
        return;
    }
    //if (!t.isInstance(l))
    if(l->self()->metaObject()->className() != t)
    {
        throw new IllegalArgumentException(QString("Listener ") + l->self()->metaObject()->className() +
                                     " is not of type " + t);
    }
    // Is l on the list?
    int index = -1;
    for (int i = listenerList.length()-2; i>=0; i-=2)
    {
        if ((listenerList.at(i)->self()->metaObject()->className() == t)// listenerList[i]==t)
            && (listenerList[i+1] ==  (l) /*== true*/)) {
            index = i;
            break;
        }
    }

    // If so,  remove it
    if (index != -1) {
        QVector<EventListener*> tmp = QVector<EventListener*>(listenerList.length()-2);
        // Copy the list up to index
        //System.arraycopy(listenerList, 0, tmp, 0, index);
        for(int i = 0; i < index; i++)
        {
         tmp.replace(i, listenerList.at(i));
        }
        // Copy from two past the index, up to
        // the end of tmp (which is two elements
        // shorter than the old list)
        if (index < tmp.length())
//            System.arraycopy(listenerList, index+2, tmp, index,
//                             tmp.length - index);
         for(int i = index+2; i < tmp.length() - index; i++)
         {
          tmp.replace(i, listenerList.at(tmp.length()-i));
         }

        // set the listener array to the new array or NULL
        listenerList = (tmp.length() == 0) ? NULL_ARRAY : tmp;
        }
}
#if 0
// Serialization support.
/*private*/ void writeObject(ObjectOutputStream s) throws IOException {
    Object[] lList = listenerList;
    s.defaultWriteObject();

    // Save the non-NULL event listeners:
    for (int i = 0; i < lList.length; i+=2) {
        Class t = (Class)lList[i];
        EventListener l = (EventListener)lList[i+1];
        if ((l!=NULL) && (l instanceof Serializable)) {
            s.writeObject(t.getName());
            s.writeObject(l);
        }
    }

    s.writeObject(NULL);
}

/*private*/ void readObject(ObjectInputStream s)
    throws IOException, ClassNotFoundException {
    listenerList = NULL_ARRAY;
    s.defaultReadObject();
    Object listenerTypeOrNull;

    while (NULL != (listenerTypeOrNull = s.readObject())) {
        ClassLoader cl = Thread.currentThread().getContextClassLoader();
        EventListener l = (EventListener)s.readObject();
        add((Class<EventListener>)Class.forName((String)listenerTypeOrNull, true, cl), l);
    }
}
#endif
/**
 * Returns a string representation of the EventListenerList.
 */
/*public*/ QString EventListenerList::toString() {
    QVector<EventListener*> lList = listenerList;
    QString s = "EventListenerList: ";
    s += lList.length()/2 + " listeners: ";
    for (int i = 0 ; i <= lList.length()-2 ; i+=2) {
        s += " type " + QString((/*(Class)*/lList[i])->self()->metaObject()->className());
        s += " listener " + lList[i+1]->self()->objectName();
    }
    return s;
}

