#include "swingpropertychangesupport.h"
#include "indexedpropertychangeevent.h"
#include "exceptions.h"
#include <QDebug>
#include "propertychangelistenerproxy.h"
#include <QPointer>

/**
 * This is a utility class that can be used by beans that support bound
 * properties.  It manages a list of listeners and dispatches
 * {@link PropertyChangeEvent}s to them.  You can use an instance of this class
 * as a member field of your bean and delegate these types of work to it.
 * The {@link PropertyChangeListener} can be registered for all properties
 * or for a property specified by name.
 * <p>
 * Here is an example of {@code SwingPropertyChangeSupport} usage that follows
 * the rules and recommendations laid out in the JavaBeans&trade; specification:
 * <pre>
 * public class MyBean {
 *     private final SwingPropertyChangeSupport pcs = new SwingPropertyChangeSupport(this, nullptr);
 *
 *     public void addPropertyChangeListener(PropertyChangeListener listener) {
 *         this.pcs.addPropertyChangeListener(listener);
 *     }
 *
 *     public void removePropertyChangeListener(PropertyChangeListener listener) {
 *         this.pcs.removePropertyChangeListener(listener);
 *     }
 *
 *     private String value;
 *
 *     public String getValue() {
 *         return this.value;
 *     }
 *
 *     public void setValue(String newValue) {
 *         String oldValue = this.value;
 *         this.value = newValue;
 *         this.pcs.firePropertyChange("value", oldValue, newValue);
 *     }
 *
 *     [...]
 * }
 * </pre>
 * <p>
 * A {@code SwingPropertyChangeSupport} instance is thread-safe.
 * <p>
 * This class is serializable.  When it is serialized it will save
 * (and restore) any listeners that are themselves serializable.  Any
 * non-serializable listeners will be skipped during serialization.
 *
 * @see VetoableChangeSupport
 */
//public class SwingPropertyChangeSupport implements Serializable {


/**
 * Constructs a <code>SwingPropertyChangeSupport</code> object.
 *
 * @param sourceBean  The bean to be given as the source for any events.
 */
/*public*/ SwingPropertyChangeSupport::SwingPropertyChangeSupport(QObject* sourceBean, QObject *parent)
 : QObject(parent)
{
 this->parent = sourceBean;
 if (sourceBean == NULL)
 {

  throw new NullPointerException("SwingPropertyChangeSupport:Null Pointer (Source)");
 }
 map = new PropertyChangeListenerMap();
 source = sourceBean;
}

/**
 * Add a PropertyChangeListener to the listener list.
 * The listener is registered for all properties.
 * The same listener object may be added more than once, and will be called
 * as many times as it is added.
 * If <code>listener</code> is NULL, no exception is thrown and no action
 * is taken.
 *
 * @param listener  The PropertyChangeListener to be added
 */
/*public*/ void SwingPropertyChangeSupport::addPropertyChangeListener(PropertyChangeListener* listener)
{
 if (listener == NULL)
 {
  return;
 }

 // If a listener has no self() function, a chrash here will occur!
// if(listener->self()->metaObject() == nullptr)
//  return;

 // add to catch bad listener pointers: qDebug()<< tr("add listener ") + listener->metaObject()->className();

// if (qobject_cast<PropertyChangeListenerProxy*>(listener) != nullptr)
// {
//  PropertyChangeListenerProxy* proxy =
//                   (PropertyChangeListenerProxy*)listener;
//  // Call two argument add method.
//  addPropertyChangeListener(proxy->getPropertyName(),
//                                      proxy->getListener());
// }
// else
 {
  //QPointer<PropertyChangeListener> l = listener;
  this->map->add("", /*l*/listener);
  //connect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/**
 * Remove a PropertyChangeListener from the listener list.
 * This removes a PropertyChangeListener that was registered
 * for all properties.
 * If <code>listener</code> was added more than once to the same event
 * source, it will be notified one less time after being removed.
 * If <code>listener</code> is NULL, or was never added, no exception is
 * thrown and no action is taken.
 *
 * @param listener  The PropertyChangeListener to be removed
 */
/*public*/ void SwingPropertyChangeSupport::removePropertyChangeListener(PropertyChangeListener* listener)
{
 if (listener == NULL)
 {
  return;
 }
#if 1
 if (qobject_cast<PropertyChangeListenerProxy*>(listener->pself()) != nullptr)
 {
  PropertyChangeListenerProxy* proxy =
                (PropertyChangeListenerProxy*)listener;
  // Call two argument remove method.
  removePropertyChangeListener(proxy->getPropertyName(),
                                     proxy->getListener());
 }
 else
#endif
 {
  this->map->remove("", listener);
//  disconnect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/**
 * Returns an array of all the listeners that were added to the
 * SwingPropertyChangeSupport object with addPropertyChangeListener().
 * <p>
 * If some listeners have been added with a named property, then
 * the returned array will be a mixture of PropertyChangeListeners
 * and <code>PropertyChangeListenerProxy</code>s. If the calling
 * method is interested in distinguishing the listeners then it must
 * test each element to see if it's a
 * <code>PropertyChangeListenerProxy</code>, perform the cast, and examine
 * the parameter.
 *
 * <pre>
 * PropertyChangeListener[] listeners = bean.getPropertyChangeListeners();
 * for (int i = 0; i < listeners.length; i++) {
 *   if (listeners[i] instanceof PropertyChangeListenerProxy) {
 *     PropertyChangeListenerProxy proxy =
 *                    (PropertyChangeListenerProxy)listeners[i];
 *     if (proxy.getPropertyName().equals("foo")) {
 *       // proxy is a PropertyChangeListener which was associated
 *       // with the property named "foo"
 *     }
 *   }
 * }
 *</pre>
 *
 * @see PropertyChangeListenerProxy
 * @return all of the <code>PropertyChangeListeners</code> added or an
 *         empty array if no listeners have been added
 * @since 1.4
 */
/*public*/ QVector<PropertyChangeListener*> SwingPropertyChangeSupport::getPropertyChangeListeners()const {
    return this->map->getListeners();
}

/**
 * Add a PropertyChangeListener for a specific property.  The listener
 * will be invoked only when a call on firePropertyChange names that
 * specific property.
 * The same listener object may be added more than once.  For each
 * property,  the listener will be invoked the number of times it was added
 * for that property.
 * If <code>propertyName</code> or <code>listener</code> is NULL, no
 * exception is thrown and no action is taken.
 *
 * @param propertyName  The name of the property to listen on.
 * @param listener  The PropertyChangeListener to be added
 */
/*public*/ void SwingPropertyChangeSupport::addPropertyChangeListener(
            QString propertyName,
            PropertyChangeListener* listener)
{
 if (listener == NULL || propertyName == NULL)
 {
  return;
 }
 listener = this->map->extract(listener);
 if (listener != NULL)
 {
  this->map->add(propertyName, listener);
//  connect(this, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
 }
}

/**
 * Remove a PropertyChangeListener for a specific property.
 * If <code>listener</code> was added more than once to the same event
 * source for the specified property, it will be notified one less time
 * after being removed.
 * If <code>propertyName</code> is NULL,  no exception is thrown and no
 * action is taken.
 * If <code>listener</code> is NULL, or was never added for the specified
 * property, no exception is thrown and no action is taken.
 *
 * @param propertyName  The name of the property that was listened on.
 * @param listener  The PropertyChangeListener to be removed
 */
/*public*/ void SwingPropertyChangeSupport::removePropertyChangeListener(
            QString propertyName,
            PropertyChangeListener* listener)
{
 if (listener == NULL || propertyName == NULL)
 {
  return;
 }
 listener = this->map->extract(listener);
 if (listener != NULL)
 {
  this->map->remove(propertyName, listener);
 }
}

/**
 * Returns an array of all the listeners which have been associated
 * with the named property.
 *
 * @param propertyName  The name of the property being listened to
 * @return all of the <code>PropertyChangeListeners</code> associated with
 *         the named property.  If no such listeners have been added,
 *         or if <code>propertyName</code> is NULL, an empty array is
 *         returned.
 * @since 1.4
 */
/*public*/ QVector<PropertyChangeListener*> SwingPropertyChangeSupport::getPropertyChangeListeners(QString propertyName) {
    return this->map->getListeners(propertyName);
}

/**
 * Reports a bound property update to listeners
 * that have been registered to track updates of
 * all properties or a property with the specified name.
 * <p>
 * No event is fired if old and new values are equal and non-NULL.
 * <p>
 * This is merely a convenience wrapper around the more general
 * {@link #firePropertyChange(PropertyChangeEvent)} method.
 *
 * @param propertyName  the programmatic name of the property that was changed
 * @param oldValue      the old value of the property
 * @param newValue      the new value of the property
 */
/*public*/ void SwingPropertyChangeSupport::firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue) const
{
 if (!oldValue.isNull() && oldValue==(newValue))
  return;
 //emit propertyChange(new PropertyChangeEvent(this->source, propertyName, oldValue, newValue));
 firePropertyChange(new PropertyChangeEvent(this->source, propertyName, oldValue, newValue));
}

///*public*/ void SwingPropertyChangeSupport::firePropertyChange(QString propertyName, QObject* oldValue, QObject* newValue) const
//{
// if ( !(oldValue==newValue))
// {
//  firePropertyChange(new PropertyChangeEvent(this->source, propertyName, oldValue, newValue));
// }
//}
/**
 * Reports a boolean bound property update to listeners
 * that have been registered to track updates of
 * all properties or a property with the specified name.
 * <p>
 * No event is fired if old and new values are equal.
 * <p>
 * This is merely a convenience wrapper around the more general
 * {@link #firePropertyChange(String, Object, Object)}  method.
 *
 * @param propertyName  the programmatic name of the property that was changed
 * @param oldValue      the old value of the property
 * @param newValue      the new value of the property
 */
/*public*/ void SwingPropertyChangeSupport::firePropertyChange(QString propertyName, bool oldValue, bool newValue) const
{
 if (oldValue != newValue)
 {
  firePropertyChange(propertyName, /*Boolean.valueOf*/QVariant(oldValue), /*Boolean.valueOf*/QVariant(newValue));
 }
}

/**
 * Fires a property change event to listeners
 * that have been registered to track updates of
 * all properties or a property with the specified name.
 * <p>
 * No event is fired if the given event's old and new values are equal and non-NULL.
 *
 * @param event  the {@code PropertyChangeEvent} to be fired
 */
/*public*/ void SwingPropertyChangeSupport::firePropertyChange(PropertyChangeEvent* event) const
{
 QVariant oldValue = event->getOldValue();
 QVariant newValue = event->getNewValue();
 if (oldValue != QVariant() && oldValue ==(newValue))
   return;
  QString name = event->getPropertyName();

  QVector<PropertyChangeListener*> common = this->map->get("");
  QVector<PropertyChangeListener*> named = !name.isEmpty() ? this->map->get(name): QVector<PropertyChangeListener*>();

  fire(common, event);
  fire(named, event);
  //emit propertyChange(event);
  foreach (PropertyChangeListener* l, common)
  {
   if(!QMetaObject::invokeMethod(l->pself(), "propertyChange", Qt::AutoConnection, Q_ARG(PropertyChangeEvent*, event)))
   {
       Logger::error(tr("invoke method 'propertyChange' failed for %1").arg(l->pself()->metaObject()->className()));
       return;
   }
  }
}

/*private static*/ void SwingPropertyChangeSupport::fire(QVector<PropertyChangeListener*> listeners, PropertyChangeEvent* event)
{
#if 1
 if (!listeners.isEmpty())
 {
  foreach(PropertyChangeListener* listener, listeners)
  {
   if(listener != NULL)
   { // NOTE: listener MUST be derived from PropertyChangeListener!!!
    if(qobject_cast<PropertyChangeListener*>(listener->pself()) != NULL)
    {
     //((PropertyChangeListener*)listener)->propertyChange(event);
     QObject* s = listener->pself();
     //int ix = s->metaObject()->indexOfMethod("propertyChange");

     if(!QMetaObject::invokeMethod(s, "propertyChange", Qt::AutoConnection, Q_ARG(PropertyChangeEvent *, event)))
     {
         Logger::error(tr("invoke method 'propertyChange' failed for %1").arg(s->metaObject()->className()));
         return;
     }
    }
    else
    {
     Logger::error(tr("PropertyChangeListener not implemented %1").arg(listener->pself()->metaObject()->className()));
    //Q_ASSERT(false);
    }
     // NOTE: Class must have a Q_OBJECT macro otherwise you will get  a "void value not ignored as it ought to be error on Q_OBJECT!
   }
  }
 }
#endif
}

/**
 * Reports a bound indexed property update to listeners
 * that have been registered to track updates of
 * all properties or a property with the specified name.
 * <p>
 * No event is fired if old and new values are equal and non-NULL.
 * <p>
 * This is merely a convenience wrapper around the more general
 * {@link #firePropertyChange(PropertyChangeEvent)} method.
 *
 * @param propertyName  the programmatic name of the property that was changed
 * @param index         the index of the property element that was changed
 * @param oldValue      the old value of the property
 * @param newValue      the new value of the property
 * @since 1.5
 */
/*public*/ void SwingPropertyChangeSupport::fireIndexedPropertyChange(QString propertyName, int index, QVariant oldValue, QVariant newValue) const
{
 if (oldValue == QVariant() || newValue == QVariant() || !(oldValue == newValue))
 {
  firePropertyChange(new IndexedPropertyChangeEvent(source, propertyName, oldValue, newValue, index));
 }
}

/**
 * Reports an integer bound indexed property update to listeners
 * that have been registered to track updates of
 * all properties or a property with the specified name.
 * <p>
 * No event is fired if old and new values are equal.
 * <p>
 * This is merely a convenience wrapper around the more general
 * {@link #fireIndexedPropertyChange(String, int, Object, Object)} method.
 *
 * @param propertyName  the programmatic name of the property that was changed
 * @param index         the index of the property element that was changed
 * @param oldValue      the old value of the property
 * @param newValue      the new value of the property
 * @since 1.5
 */
///*public*/ void SwingPropertyChangeSupport::fireIndexedPropertyChange(QString propertyName, int index, int oldValue, int newValue) {
//    if (oldValue != newValue) {
//        fireIndexedPropertyChange(propertyName, index, /*Integer.valueOf*/(oldValue), /*Integer.valueOf*/(newValue));
//    }
//}

/**
 * Reports a boolean bound indexed property update to listeners
 * that have been registered to track updates of
 * all properties or a property with the specified name.
 * <p>
 * No event is fired if old and new values are equal.
 * <p>
 * This is merely a convenience wrapper around the more general
 * {@link #fireIndexedPropertyChange(String, int, Object, Object)} method.
 *
 * @param propertyName  the programmatic name of the property that was changed
 * @param index         the index of the property element that was changed
 * @param oldValue      the old value of the property
 * @param newValue      the new value of the property
 * @since 1.5
 */
///*public*/ void SwingPropertyChangeSupport::fireIndexedPropertyChange(QString propertyName, int index, bool oldValue, bool newValue) {
//    if (oldValue != newValue) {
//        fireIndexedPropertyChange(propertyName, index, /*Boolean.valueOf*/(oldValue), /*Boolean.valueOf*/(newValue));
//    }
//}

/**
 * Check if there are any listeners for a specific property, including
 * those registered on all properties.  If <code>propertyName</code>
 * is NULL, only check for listeners registered on all properties.
 *
 * @param propertyName  the property name.
 * @return true if there are one or more listeners for the given property
 */
/*public*/ bool SwingPropertyChangeSupport::hasListeners(QString propertyName) {
    return this->map->hasListeners(propertyName);
}
#if 0
/**
 * @serialData Null terminated list of <code>PropertyChangeListeners</code>.
 * <p>
 * At serialization time we skip non-serializable listeners and
 * only serialize the serializable listeners.
 */
private void writeObject(ObjectOutputStream s) throws IOException {
    Hashtable<String, SwingPropertyChangeSupport> children = NULL;
    PropertyChangeListener[] listeners = NULL;
    synchronized (this.map) {
        for (Entry<String, PropertyChangeListener[]> entry : this.map.getEntries()) {
            String property = entry.getKey();
            if (property == NULL) {
                listeners = entry.getValue();
            } else {
                if (children == NULL) {
                    children = new Hashtable<String, SwingPropertyChangeSupport>();
                }
                SwingPropertyChangeSupport pcs = new SwingPropertyChangeSupport(this.source);
                pcs.map.set(NULL, entry.getValue());
                children.put(property, pcs);
            }
        }
    }
    ObjectOutputStream.PutField fields = s.putFields();
    fields.put("children", children);
    fields.put("source", this.source);
    fields.put("SwingPropertyChangeSupportSerializedDataVersion", 2);
    s.writeFields();

    if (listeners != NULL) {
        for (PropertyChangeListener l : listeners) {
            if (l instanceof Serializable) {
                s.writeObject(l);
            }
        }
    }
    s.writeObject(NULL);
}

private void readObject(ObjectInputStream s) throws ClassNotFoundException, IOException {
    this.map = new PropertyChangeListenerMap();

    ObjectInputStream.GetField fields = s.readFields();

    Hashtable<String, SwingPropertyChangeSupport> children = (Hashtable<String, SwingPropertyChangeSupport>) fields.get("children", NULL);
    this.source = fields.get("source", NULL);
    fields.get("SwingPropertyChangeSupportSerializedDataVersion", 2);

    Object listenerOrNull;
    while (NULL != (listenerOrNull = s.readObject())) {
        this.map.add(NULL, (PropertyChangeListener)listenerOrNull);
    }
    if (children != NULL) {
        for (Entry<String, SwingPropertyChangeSupport> entry : children.entrySet()) {
            for (PropertyChangeListener listener : entry.getValue().getPropertyChangeListeners()) {
                this.map.add(entry.getKey(), listener);
            }
        }
    }
}


/**
 * @serialField children                                   Hashtable
 * @serialField source                                     Object
 * @serialField SwingPropertyChangeSupportSerializedDataVersion int
 */
private static final ObjectStreamField[] serialPersistentFields = {
        new ObjectStreamField("children", Hashtable.class),
        new ObjectStreamField("source", Object.class),
        new ObjectStreamField("SwingPropertyChangeSupportSerializedDataVersion", Integer.TYPE)
};
#endif
