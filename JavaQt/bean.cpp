#include "bean.h"
#include "propertychangesupport.h"
#include "propertychangeevent.h"
/**
 * Generic implementation of {@link jmri.beans.BeanInterface} with a complete
 * implementation of {@link java.beans.PropertyChangeSupport}.
 * <p>
 * See the PropertyChangeSupport documentation for complete documentation of
 * those methods.
 *
 * @author rhwood
 * @see java.beans.PropertyChangeSupport
 */
///*public*/ abstract class Bean extends UnboundBean implements PropertyChangeProvider {

/*protected*/ Bean::Bean(QObject *parent) : UnboundBean(parent)
{
 /**
  * Provide a {@link java.beans.PropertyChangeSupport} helper.
  */
  propertyChangeSupport = new PropertyChangeSupport(this);
}

/**
 * Create a bean.
 *
 * @param notifyOnEDT true to notify property change listeners on the EDT;
 *                    false to notify listeners on the thread the event was
 *                    generated on (which may or may not be the EDT)
 */
/*protected*/ Bean::Bean(bool notifyOnEDT, QObject *parent) : UnboundBean(parent) {
    propertyChangeSupport = new PropertyChangeSupport(this/*, notifyOnEDT*/);
}

/**
 * Add a PropertyChangeListener to the listener list.
 *
 * @param listener The PropertyChangeListener to be added
 */
//@Override
/*public*/ void Bean::addPropertyChangeListener(PropertyChangeListener* listener) {
    propertyChangeSupport->addPropertyChangeListener(listener);
}

/**
 * Add a PropertyChangeListener for a specific property.
 *
 * @param propertyName The name of the property to listen on.
 * @param listener     The PropertyChangeListener to be added
 */
//@Override
/*public*/ void Bean::addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    propertyChangeSupport->addPropertyChangeListener(propertyName, listener);
}

/**
 * Fire an indexed property change on the Event dispatch (Swing) thread. Use
 * {@link java.beans.PropertyChangeSupport#fireIndexedPropertyChange(java.lang.String, int, boolean, boolean)}
 * directly to fire this notification on another thread.
 */
/*protected*/ void Bean::fireIndexedPropertyChange(QString propertyName, int index, bool oldValue, bool newValue) {
//    ThreadingUtil.runOnGUIEventually(() -> {
//        propertyChangeSupport.fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
//    });
 propertyChangeSupport->fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
}

/**
 * Fire an indexed property change on the Event dispatch (Swing) thread. Use
 * {@link java.beans.PropertyChangeSupport#fireIndexedPropertyChange(java.lang.String, int, int, int)}
 * directly to fire this notification on another thread.
 */
/*protected*/ void Bean::fireIndexedPropertyChange(QString propertyName, int index, int oldValue, int newValue) {
//    ThreadingUtil.runOnGUIEventually(() -> {
//        propertyChangeSupport.fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
//    });
 propertyChangeSupport->fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
}

/**
 * Fire an indexed property change on the Event dispatch (Swing) thread. Use
 * {@link java.beans.PropertyChangeSupport#fireIndexedPropertyChange(java.lang.String, int, java.lang.Object, java.lang.Object)}
 * directly to fire this notification on another thread.
 */
/*protected*/ void Bean::fireIndexedPropertyChange(QString propertyName, int index, QVariant oldValue, QVariant newValue) {
//    ThreadingUtil.runOnGUIEventually(() -> {
        propertyChangeSupport->fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
//    });
}

/**
 * Fire an indexed property change on the Event dispatch (Swing) thread. Use
 * {@link java.beans.PropertyChangeSupport#firePropertyChange(java.lang.String, boolean, boolean)}
 * directly to fire this notification on another thread.
 */
/*protected*/ void Bean::firePropertyChange(QString key, bool oldValue, bool value) {
//    ThreadingUtil.runOnGUIEventually(() -> {
        propertyChangeSupport->firePropertyChange(key, oldValue, value);
//    });
}

/**
 * Fire an indexed property change on the Event dispatch (Swing) thread. Use
 * {@link java.beans.PropertyChangeSupport#firePropertyChange(java.beans.PropertyChangeEvent)}
 * directly to fire this notification on another thread.
 */
/*protected*/ void Bean::firePropertyChange(PropertyChangeEvent* evt) {
//    ThreadingUtil.runOnGUIEventually(() -> {
        propertyChangeSupport->firePropertyChange(evt);
//    });
}

/**
 * Fire an indexed property change on the Event dispatch (Swing) thread. Use
 * {@link java.beans.PropertyChangeSupport#firePropertyChange(java.lang.String, int, int)}
 * directly to fire this notification on another thread.
 *
 */
/*protected*/ void Bean::firePropertyChange(QString key, int oldValue, int value) {
//    ThreadingUtil.runOnGUIEventually(() -> {
        propertyChangeSupport->firePropertyChange(key, oldValue, value);
//    });
// emit propertyChange(new PropertyChangeEvent(this, key, oldValue, value));
}

/**
 * Fire an indexed property change on the Event dispatch (Swing) thread. Use
 * {@link java.beans.PropertyChangeSupport#firePropertyChange(java.lang.String, java.lang.Object, java.lang.Object)}
 * directly to fire this notification on another thread.
 *
 */
/*protected*/ void Bean::firePropertyChange(QString key, QVariant oldValue, QVariant value) {
//    ThreadingUtil.runOnGUIEventually(() -> {
        propertyChangeSupport->firePropertyChange(key, oldValue, value);
//    });
// emit propertyChange(new PropertyChangeEvent(this, key, oldValue, value));
}

//@Override
/*public*/ QVector<PropertyChangeListener*> Bean::getPropertyChangeListeners() {
    return propertyChangeSupport->getPropertyChangeListeners();
}

//@Override
/*public*/ QVector<PropertyChangeListener*> Bean::getPropertyChangeListeners(QString propertyName) {
    return propertyChangeSupport->getPropertyChangeListeners(propertyName);
}

//@Override
/*public*/ void Bean::removePropertyChangeListener(PropertyChangeListener* listener) {
    propertyChangeSupport->removePropertyChangeListener(listener);
}

//@Override
/*public*/ void Bean::removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) {
    propertyChangeSupport->removePropertyChangeListener(propertyName, listener);
}

/*public*/ QString Bean::getClass()
{
 return metaObject()->className();
}
