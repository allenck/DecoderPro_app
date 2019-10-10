#include "vetoablechangelistenerproxy.h"
#include "propertychangeevent.h"
#include "eventlistenerproxy.h"

/**
 * This class provides an extension to <code>VetoableChangeListener</code> -
 * associating a name with the listener. This can be used to filter the
 * changes that one is interested in.
 *
 * @author Eric Blake (ebb9@email.byu.edu)
 * @since 1.4
 * @status udpated to 1.4
 */
// /*public*/ class VetoableChangeListenerProxy : public EventListenerProxy
//   //implements VetoableChangeListener
// {
//   /**
//    * The name of the property to listen for. Package visible for use by
//    * VetoableChangeSupport.
//    */
//   /*final*/ QString propertyName;

   /**
    * Create a new proxy which filters property change events and only passes
    * changes to the named property on to the delegate.
    *
    * @param propertyName the property's name to filter on
    * @param listener the delegate listener
    */
   /*public*/ VetoableChangeListenerProxy::VetoableChangeListenerProxy(QString propertyName,
                                      VetoableChangeListener* listener) : EventListenerProxy<VetoableChangeListener*>(listener)
   {
     //super(listener);
     this->propertyName = propertyName;
   }

   /**
    * Forwards the event on to the delegate if the property name matches.
    *
    * @param event the event to pass on, if it meets the filter
    * @throws NullPointerException if the delegate this was created with is null
    * @throws PropertyVetoException if the change is vetoed by the listener
    */
   /*public*/ void VetoableChangeListenerProxy::vetoableChange(PropertyChangeEvent* event)
     throw (PropertyVetoException)
   {
     // Note: Sun does not filter, under the assumption that since
     // VetoableChangeSupport unwraps proxys, this method should never be
     // called by normal use of listeners.
     QString name = event == nullptr ? "" : event->getPropertyName();
     if (name == "" ? propertyName == "" : name == (propertyName))
       ((VetoableChangeListener*) getListener())->vetoableChange(event);
   }

   /**
    * Gets the name of the property this proxy is filtering on.
    *
    * @return the property name
    */
   /*public*/ QString VetoableChangeListenerProxy::getPropertyName()
   {
     return propertyName;
   }
 //}; // class VetoableChangeListenerProxy
