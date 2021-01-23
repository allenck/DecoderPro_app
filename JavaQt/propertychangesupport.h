#ifndef PROPERTYCHANGESUPPORT_H
#define PROPERTYCHANGESUPPORT_H

#include <QObject>
#include "propertychangelistenermap.h"
#include "javaqt_global.h"
#include "logger.h"

class JAVAQTSHARED_EXPORT PropertyChangeSupport : public QObject
{
    Q_OBJECT
public:
//    explicit PropertyChangeSupport(QObject *parent = 0);
/**
 * Constructs a <code>PropertyChangeSupport</code> object.
 *
 * @param sourceBean  The bean to be given as the source for any events.
 */
PropertyChangeSupport(QObject* sourceBean, QObject *parent = 0);
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
/*public*/ void addPropertyChangeListener(PropertyChangeListener* listener);
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
/*public*/ void removePropertyChangeListener(PropertyChangeListener* listener);
/**
 * Returns an array of all the listeners that were added to the
 * PropertyChangeSupport object with addPropertyChangeListener().
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
 *     }source
 *   }
 * }
 *</pre>
 *
 * @see PropertyChangeListenerProxy
 * @return all of the <code>PropertyChangeListeners</code> added or an
 *         empty array if no listeners have been added
 * @since 1.4
 */
/*public*/ QVector<PropertyChangeListener *> getPropertyChangeListeners();
/**
 * Add a PropertyChangeListensourceer for a specific property.  The listener
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
/*public*/ void addPropertyChangeListener(
            QString propertyName,
            PropertyChangeListener* listener);
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
/*public*/ void removePropertyChangeListener(
            QString propertyName,
            PropertyChangeListener* listener);
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
/*public*/ QVector<PropertyChangeListener *> getPropertyChangeListeners(QString propertyName);
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
/*public*/ void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue);
//void firePropertyChange(QString properyName, QObject* oldValue, QObject* newValue);

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
/*public*/ void firePropertyChange(QString propertyName, bool oldValue, bool newValue);
/**
 * Fires a property change event to listeners
 * that have been registered to track updates of
 * all properties or a property with the specified name.
 * <p>
 * No event is fired if the given event's old and new values are equal and non-NULL.
 *
 * @param event  the {@code PropertyChangeEvent} to be fired
 */
/*public*/ void firePropertyChange(PropertyChangeEvent* event);
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
/*public*/ void fireIndexedPropertyChange(QString propertyName, int index, QVariant oldValue, QVariant newValue);
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
/*public*/ void fireIndexedPropertyChange(QString propertyName, int index, int oldValue, int newValue);
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
/*public*/ void fireIndexedPropertyChange(QString propertyName, int index, bool oldValue, bool newValue);
/**
 * Check if there are any listeners for a specific property, including
 * those registered on all properties.  If <code>propertyName</code>
 * is NULL, only check for listeners registered on all properties.
 *
 * @param propertyName  the property name.
 * @return true if there are one or more listeners for the given property
 */
/*public*/ bool hasListeners(QString propertyName);

signals:
void propertyChange(PropertyChangeEvent*);

public slots:
private:
 PropertyChangeListenerMap* map = nullptr;
 /*private*/ static void fire(QVector<PropertyChangeListener*> listeners, PropertyChangeEvent* event);
 /**
  * The object to be provided as the "source" for any generated events.
  */
 /*private*/ QObject* source;
 /**
  * Serialization version ID, so we're compatible with JDK 1.1
  */
 static const long long serialVersionUID = 6401253773779951803L;
 QObject* parent;
};
//    /**
//     * This is a {@link ChangeListenerMap ChangeListenerMap} implementation
//     * that works with {@link PropertyChangeListener PropertyChangeListener} objects.
//     */
//    class PropertyChangeListenerMap : private ChangeListenerMap<PropertyChangeListener>
//    {
//    private:
//        static /*final*/ QList<PropertyChangeListener*> EMPTY;

//        /**
//         * Creates an array of {@link PropertyChangeListener PropertyChangeListener} objects.
//         * This method uses the same instance of the empty array
//         * when {@code length} equals {@code 0}.
//         *
//         * @param length  the array length
//         * @return        an array with specified length
//         */
//        //@Override
//    protected:
//        QList<PropertyChangeListener*> newArray(int length) {
//            return (0 < length)
//                    ? new PropertyChangeListener[length]
//                    : EMPTY;
//        }

//        /**
//         * Creates a {@link PropertyChangeListenerProxy PropertyChangeListenerProxy}
//         * object for the specified property.
//         *
//         * @param name      the name of the property to listen on
//         * @param listener  the listener to process events
//         * @return          a {@code PropertyChangeListenerProxy} object
//         */
//        //@Override
//        /*protected*/ PropertyChangeListener* newProxy(QString name, PropertyChangeListener* listener) {
//            return new PropertyChangeListenerProxy(name, listener);
//        }

//        /**
//         * {@inheritDoc}
//         */
//    public:
//        /*final*/ PropertyChangeListener extract(PropertyChangeListener listener) {
//            while (listener instanceof PropertyChangeListenerProxy) {
//                listener = ((PropertyChangeListenerProxy) listener).getListener();
//            }
//            return listener;
//        }
//    };

#endif // PROPERTYCHANGESUPPORT_H
