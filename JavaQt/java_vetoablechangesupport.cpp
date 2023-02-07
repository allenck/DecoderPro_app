#include "java_vetoablechangesupport.h"
#include "exceptions.h"
#include "vetoablechangelistenerproxy.h"
#include "propertychangeevent.h"

/**
 * VetoableChangeSupport makes it easy to fire vetoable change events and
 * handle listeners. It allows chaining of listeners, as well as filtering
 * by property name. In addition, it will serialize only those listeners
 * which are serializable, ignoring the others without problem. This class
 * is thread-safe.
 *
 * @author John Keiser
 * @author Eric Blake (ebb9@email.byu.edu)
 * @since 1.1
 * @status updated to 1.4
 */
///*public*/  class VetoableChangeSupport implements Serializable
//{


  /**
   * Create a VetoableChangeSupport to work with a specific source bean.
   *
   * @param source the source bean to use
   * @throws NullPointerException if source is null
   */
  /*public*/  Java_VetoableChangeSupport::Java_VetoableChangeSupport(QObject* source)
  {
    this->source = source;
    if (source == nullptr)
      throw new NullPointerException();
  }

  /**
   * Adds a VetoableChangeListener to the list of global listeners. All
   * vetoable change events will be sent to this listener. The listener add
   * is not unique: that is, <em>n</em> adds with the same listener will
   * result in <em>n</em> events being sent to that listener for every
   * vetoable change. This method will unwrap a VetoableChangeListenerProxy,
   * registering the underlying delegate to the named property list.
   *
   * @param l the listener to add (<code>null</code> ignored).
   */
  /*public*/  /*synchronized*/ void Java_VetoableChangeSupport::addVetoableChangeListener(VetoableChangeListener* l)
  {
    if (l == nullptr)
      return;
//    if (static_cast<VetoableChangeListenerProxy*>(l))
//    {
//        VetoableChangeListenerProxy* p = (VetoableChangeListenerProxy*) l;
//        addVetoableChangeListener(p->propertyName,
//                                   (VetoableChangeListener*) p->getListener());
//    }
//    else
    {
        if (listeners == nullptr)
          listeners = new QVector<VetoableChangeListener*>();
        listeners->append(l);
      }
  }

  /**
   * Removes a VetoableChangeListener from the list of global listeners. If
   * any specific properties are being listened on, they must be deregistered
   * by themselves; this will only remove the general listener to all
   * properties. If <code>add()</code> has been called multiple times for a
   * particular listener, <code>remove()</code> will have to be called the
   * same number of times to deregister it. This method will unwrap a
   * VetoableChangeListenerProxy, removing the underlying delegate from the
   * named property list.
   *
   * @param l the listener to remove
   */
  /*public*/  /*synchronized*/ void
    Java_VetoableChangeSupport::removeVetoableChangeListener(VetoableChangeListener* l)
  {
//    if (static_cast<VetoableChangeListenerProxy*>(l))
//      {
//        VetoableChangeListenerProxy* p = (VetoableChangeListenerProxy*) l;
//        removeVetoableChangeListener(p->propertyName,
//                                     (VetoableChangeListener*) p->getListener());
//      }
//    else
     if (listeners != nullptr)
      {
        listeners->removeOne(l);
        if (listeners->isEmpty())
          listeners = nullptr;
      }
   }

  /**
   * Returns an array of all registered vetoable change listeners. Those that
   * were registered under a name will be wrapped in a
   * <code>VetoableChangeListenerProxy</code>, so you must check whether the
   * listener is an instance of the proxy class in order to see what name the
   * real listener is registered under. If there are no registered listeners,
   * this returns an empty array.
   *
   * @return the array of registered listeners
   * @see VetoableChangeListenerProxy
   * @since 1.4
   */
  /*public*/  /*synchronized*/ QVector<VetoableChangeListener*>* Java_VetoableChangeSupport::getVetoableChangeListeners()
  {
    QList<VetoableChangeListener*>* list = new QList<VetoableChangeListener*>();
    if (listeners != nullptr)
      //list.addAll(listeners);
     foreach(VetoableChangeListener* l , *listeners) list->append(l);
    if (children != nullptr)
      {
        int i = children->size();
        QMapIterator<QString,Java_VetoableChangeSupport*> iter(*children);//.entrySet().iterator();
        //while (--i >= 0)
        while(iter.hasNext())
          {
            /*Entry e = (Entry)*/ iter.next();
            QString name = /*(String)*/ iter.key();
            QVector<VetoableChangeListener*>* v = ((Java_VetoableChangeSupport*) iter.value())->listeners;
            int j = v->size();
            while (--j >= 0)
              list->append(new VetoableChangeListenerProxy
                (name, (VetoableChangeListener*) v->at(j)));
          }
      }
//    return (VetoableChangeListener[])
//      list.toArray(new VetoableChangeListener[list.size()]);
    QVector<VetoableChangeListener*> vector = list->toVector();
    return (new QVector<VetoableChangeListener*>(vector));
  }

  /**
   * Adds a VetoableChangeListener listening on the specified property. Events
   * will be sent to the listener only if the property name matches. The
   * listener add is not unique; that is, <em>n</em> adds on a particular
   * property for a particular listener will result in <em>n</em> events
   * being sent to that listener when that property is changed. The effect is
   * cumulative, too; if you are registered to listen to receive events on
   * all vetoable changes, and then you register on a particular property,
   * you will receive change events for that property twice. This method
   * will unwrap a VetoableChangeListenerProxy, registering the underlying
   * delegate to the named property list if the names match, and discarding
   * it otherwise.
   *
   * @param propertyName the name of the property to listen on
   * @param l the listener to add
   */
  /*public*/  /*synchronized*/ void Java_VetoableChangeSupport::addVetoableChangeListener(QString propertyName,
                                                     VetoableChangeListener* l)
  {
    if (propertyName == "" || l == nullptr)
      return;
    while (dynamic_cast<VetoableChangeListenerProxy*>(l))
    {
        VetoableChangeListenerProxy* p = (VetoableChangeListenerProxy*) l;
        if (propertyName == "" ? p->propertyName != ""
            :  propertyName!=(p->propertyName))
          return;
        l = (VetoableChangeListener*) p->getListener();
      }
    Java_VetoableChangeSupport* s = nullptr;
    if (children == nullptr)
      children = new QMap<QString,Java_VetoableChangeSupport*>();
    else
      s = (Java_VetoableChangeSupport*) children->value(propertyName);
    if (s == nullptr)
      {
        s = new Java_VetoableChangeSupport(source);
        s->listeners = new QVector<VetoableChangeListener*>();
        children->insert(propertyName, s);
      }
    s->listeners->append(l);
  }

  /**
   * Removes a VetoableChangeListener from listening to a specific property.
   * If <code>add()</code> has been called multiple times for a particular
   * listener on a property, <code>remove()</code> will have to be called the
   * same number of times to deregister it. This method will unwrap a
   * VetoableChangeListenerProxy, removing the underlying delegate from the
   * named property list if the names match.
   *
   * @param propertyName the property to stop listening on
   * @param l the listener to remove
   * @throws NullPointerException if propertyName is null
   */
  /*public*/  /*synchronized*/ void
    Java_VetoableChangeSupport::removeVetoableChangeListener(QString propertyName, VetoableChangeListener* l)
  {
    if (children == nullptr)
      return;
    Java_VetoableChangeSupport* s
      = (Java_VetoableChangeSupport*) children->value(propertyName);
    if (s == nullptr)
      return;
    while (dynamic_cast<VetoableChangeListenerProxy*>(l))
     {
        VetoableChangeListenerProxy* p = (VetoableChangeListenerProxy*) l;
        if (propertyName == "" ? p->propertyName != ""
           :  propertyName != (p->propertyName))
          return;
        l = (VetoableChangeListener*) p->getListener();
      }
    s->listeners->removeOne(l);
    if (s->listeners->isEmpty())
      {
        children->remove(propertyName);
        if (children->isEmpty())
          children = nullptr;
     }
  }

  /**
   * Returns an array of all vetoable change listeners registered under the
   * given property name. If there are no registered listeners, this returns
   * an empty array.
   *
   * @return the array of registered listeners
   * @throws NullPointerException if propertyName is null
   * @since 1.4
   */
  /*public*/  /*synchronized*/ QVector<VetoableChangeListener*>*
    Java_VetoableChangeSupport::getVetoableChangeListeners(QString propertyName)
  {
    if (children == nullptr)
      return new QVector<VetoableChangeListener*>();
    Java_VetoableChangeSupport* s
      = (Java_VetoableChangeSupport*) children->value(propertyName);
    if (s == nullptr)
      return new QVector<VetoableChangeListener*>();
//    return (VetoableChangeListener[])
//      s->listeners.toArray(new VetoableChangeListener[s.listeners.size()]);
    return new QVector<VetoableChangeListener*>(*s->listeners);
  }

  /**
   * Fire a PropertyChangeEvent containing the old and new values of the
   * property to all the global listeners, and to all the listeners for the
   * specified property name. This does nothing if old and new are non-null
   * and equal. If the change is vetoed, a new event is fired to notify
   * listeners about the rollback before the exception is thrown.
   *
   * @param propertyName the name of the property that changed
   * @param oldVal the old value
   * @param newVal the new value
   * @throws PropertyVetoException if the change is vetoed by a listener
   */
  /*public*/  void Java_VetoableChangeSupport::fireVetoableChange(QString propertyName,
                                 QVariant oldVal, QVariant newVal)
//    throws PropertyVetoException
  {
    fireVetoableChange(new PropertyChangeEvent(source, propertyName,
                                               oldVal, newVal));
  }

  /**
   * Fire a PropertyChangeEvent containing the old and new values of the
   * property to all the global listeners, and to all the listeners for the
   * specified property name. This does nothing if old and new are equal.
   * If the change is vetoed, a new event is fired to notify listeners about
   * the rollback before the exception is thrown.
   *
   * @param propertyName the name of the property that changed
   * @param oldVal the old value
   * @param newVal the new value
   * @throws PropertyVetoException if the change is vetoed by a listener
   */
  /*public*/  void Java_VetoableChangeSupport::fireVetoableChange(QString propertyName, int oldVal, int newVal)
//    throws PropertyVetoException
  {
    if (oldVal != newVal)
      fireVetoableChange(new PropertyChangeEvent(source, propertyName,
                                                 oldVal,
                                                  newVal));
  }

  /**
   * Fire a PropertyChangeEvent containing the old and new values of the
   * property to all the global listeners, and to all the listeners for the
   * specified property name. This does nothing if old and new are equal.
   * If the change is vetoed, a new event is fired to notify listeners about
   * the rollback before the exception is thrown.
   *
   * @param propertyName the name of the property that changed
   * @param oldVal the old value
   * @param newVal the new value
   * @throws PropertyVetoException if the change is vetoed by a listener
   */
  /*public*/  void Java_VetoableChangeSupport::fireVetoableChange(QString propertyName,
                                 bool oldVal, bool newVal)
//    throws PropertyVetoException
  {
    if (oldVal != newVal)
      fireVetoableChange(new PropertyChangeEvent(source, propertyName,
                                                 oldVal,
                                                 newVal));
  }

  /**
   * Fire a PropertyChangeEvent to all the global listeners, and to all the
   * listeners for the specified property name. This does nothing if old and
   * new values of the event are equal. If the change is vetoed, a new event
   * is fired to notify listeners about the rollback before the exception is
   * thrown.
   *
   * @param event the event to fire
   * @throws NullPointerException if event is null
   * @throws PropertyVetoException if the change is vetoed by a listener
   */
   /*public*/  void Java_VetoableChangeSupport::fireVetoableChange(PropertyChangeEvent* event)
//    throws PropertyVetoException
  {
     if (event->oldValue != QVariant() && event->oldValue == (event->newValue))
       return;
     QVector<VetoableChangeListener*>* v = listeners; // Be thread-safe.
    if (v != nullptr)
      {
        int i = v->size();
        try
          {
             while (--i >= 0)
              ((VetoableChangeListener*) v->at(i))->vetoableChange(event);
           }
         catch (PropertyVetoException* e)
           {
//             event = event->rollback();
             int limit = i;
             i = v->size();
            while (--i >= limit)
              ((VetoableChangeListener*) v->at(i))->vetoableChange(event);
            throw e;
          }
      }
    QMap<QString,Java_VetoableChangeSupport*>*  h = children; // Be thread-safe.
     if (h != nullptr && event->propertyName != "")
       {
         Java_VetoableChangeSupport* s
           = (Java_VetoableChangeSupport*) h->value(event->propertyName);
         if (s != nullptr)
           {
             QVector<VetoableChangeListener*>* v1 = s->listeners; // Be thread-safe.
             int i = v1 == nullptr ? 0 : v1->size();
            try
               {
                while (--i >= 0)
                   ((VetoableChangeListener*) v1->at(i))->vetoableChange(event);
               }
             catch (PropertyVetoException* e)
              {
//                event = event->rollback();
                int limit = i;
                i = v->size();
                while (--i >= 0)
                  ((VetoableChangeListener*) v->at(i))->vetoableChange(event);
                i = v1->size();
                while (--i >= limit)
                  ((VetoableChangeListener*) v1->at(i))->vetoableChange(event);
                throw e;
               }
           }
      }
  }

  /**
   * Tell whether the specified property is being listened on or not. This
   * will only return <code>true</code> if there are listeners on all
   * properties or if there is a listener specifically on this property.
   *
   * @param propertyName the property that may be listened on
   * @return whether the property is being listened on
   * @throws NullPointerException if propertyName is null
   */
  /*public*/  /*synchronized*/ bool Java_VetoableChangeSupport::hasListeners(QString propertyName)
  {
     return listeners != nullptr || (children != nullptr
                                 && children->value(propertyName) != nullptr);
  }
#if 0
  /**
   * Saves the state of the object to the stream.
   *
   * @param s the stream to write to
   * @throws IOException if anything goes wrong
   * @serialData this writes out a null-terminated list of serializable
   *             global vetoable change listeners (the listeners for a named
   *             property are written out as the global listeners of the
   *             children, when the children hashtable is saved)
   */
  /*private*/ /*synchronized*/ void writeObject(ObjectOutputStream s)
    throws IOException
  {
    s.defaultWriteObject();
    if (listeners != null)
      {
        int i = listeners.size();
        while (--i >= 0)
         if (listeners.get(i) instanceof Serializable)
            s.writeObject(listeners.get(i));
      }
    s.writeObject(null);
  }

  /**
   * Reads the object back from stream (deserialization).
   *
   * XXX Since serialization for 1.1 streams was not documented, this may
   * not work if vetoableChangeSupportSerializedDataVersion is 1.
   *
   * @param s the stream to read from
   * @throws IOException if reading the stream fails
   * @throws ClassNotFoundException if deserialization fails
   * @serialData this reads in a null-terminated list of serializable
   *             global vetoable change listeners (the listeners for a named
   *             property are written out as the global listeners of the
   *             children, when the children hashtable is saved)
   */
  /*private*/ void readObject(ObjectInputStream s)
    throws IOException, ClassNotFoundException
  {
    s.defaultReadObject();
    VetoableChangeListener l = (VetoableChangeListener) s.readObject();
    while (l != null)
      {
        addVetoableChangeListener(l);
        l = (VetoableChangeListener) s.readObject();
       }
    // Sun is not as careful with children as we are, and lets some proxys
    // in that can never receive events. So, we clean up anything that got
    // serialized, to make sure our invariants hold.
    if (children != null)
      {
        int i = children.size();
        Iterator iter = children.entrySet().iterator();
        while (--i >= 0)
          {
            Entry e = (Entry) iter.next();
            String name = (String) e.getKey();
            VetoableChangeSupport vcs = (VetoableChangeSupport) e.getValue();
            if (vcs.listeners == null)
              vcs.listeners = new Vector();
            if (vcs.children != null)
              vcs.listeners.addAll
                (Arrays.asList(vcs.getVetoableChangeListeners(name)));
            if (vcs.listeners.size() == 0)
              iter.remove();
            else
              vcs.children = null;
          }
        if (children.size() == 0)
          children = null;
      }
  }
#endif
//} // class VetoableChangeSupport
