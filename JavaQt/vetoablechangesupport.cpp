#include "vetoablechangesupport.h"
#include "propertychangeevent.h"
#include "exceptions.h"
#include "vetoablechangelistener.h"
#include "vetoablechangelistenerproxy.h"

/**
 * This is a utility class that can be used by beans that support constrained
 * properties.  It manages a list of listeners and dispatches
 * {@link PropertyChangeEvent}s to them.  You can use an instance of this class
 * as a member field of your bean and delegate these types of work to it.
 * The {@link VetoableChangeListener} can be registered for all properties
 * or for a property specified by name.
 * <p>
 * Here is an example of {@code VetoableChangeSupport} usage that follows
 * the rules and recommendations laid out in the JavaBeans&trade; specification:
 * <pre>{@code
 * public class MyBean {
 *     private final VetoableChangeSupport vcs = new VetoableChangeSupport(this);
 *
 *     public void addVetoableChangeListener(VetoableChangeListener listener) {
 *         this.vcs.addVetoableChangeListener(listener);
 *     }
 *
 *     public void removeVetoableChangeListener(VetoableChangeListener listener) {
 *         this.vcs.removeVetoableChangeListener(listener);
 *     }
 *
 *     private String value;
 *
 *     public String getValue() {
 *         return this.value;
 *     }
 *
 *     public void setValue(String newValue) throws PropertyVetoException {
 *         String oldValue = this.value;
 *         this.vcs.fireVetoableChange("value", oldValue, newValue);
 *         this.value = newValue;
 *     }
 *
 *     [...]
 * }
 * }</pre>
 * <p>
 * A {@code VetoableChangeSupport} instance is thread-safe.
 * <p>
 * This class is serializable.  When it is serialized it will save
 * (and restore) any listeners that are themselves serializable.  Any
 * non-serializable listeners will be skipped during serialization.
 *
 * @see SwingPropertyChangeSupport
 */
///*public*/ class VetoableChangeSupport implements Serializable {
//    private VetoableChangeListenerMap map = new VetoableChangeListenerMap();

    /**
     * Constructs a <code>VetoableChangeSupport</code> object.
     *
     * @param sourceBean  The bean to be given as the source for any events.
     */
    /*public*/ VetoableChangeSupport::VetoableChangeSupport( QObject* parent)
      : PropertyChangeSupport( parent) {
//        if (sourceBean == nullptr) {
//            throw new NullPointerException();
//        }
    }

   /**
     * Add a VetoableChangeListener to the listener list.
     * The listener is registered for all properties.
     * The same listener object may be added more than once, and will be called
     * as many times as it is added.
     * If <code>listener</code> is null, no exception is thrown and no action
     * is taken.
     *
     * @param listener  The VetoableChangeListener to be added
     */
    /*public*/ void VetoableChangeSupport::addVetoableChangeListener(VetoableChangeListener* listener) {
     vetoableChangeSupport->addVetoableChangeListener(listener);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void VetoableChangeSupport::addVetoableChangeListener(/*@CheckForNull*/ QString propertyName,/* @CheckForNull*/ VetoableChangeListener* listener) {
        vetoableChangeSupport->addVetoableChangeListener(propertyName, listener);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QVector<VetoableChangeListener*>* VetoableChangeSupport::getVetoableChangeListeners() {
        return vetoableChangeSupport->getVetoableChangeListeners();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QVector<VetoableChangeListener *> *VetoableChangeSupport::getVetoableChangeListeners(QString propertyName) {
        return vetoableChangeSupport->getVetoableChangeListeners(propertyName);
    }

    /**
     * Remove a VetoableChangeListener from the listener list.
     * This removes a VetoableChangeListener that was registered
     * for all properties.
     * If <code>listener</code> was added more than once to the same event
     * source, it will be notified one less time after being removed.
     * If <code>listener</code> is null, or was never added, no exception is
     * thrown and no action is taken.
     *
     * @param listener  The VetoableChangeListener to be removed
     */
    /*public*/ void VetoableChangeSupport::removeVetoableChangeListener(VetoableChangeListener* listener) {
        vetoableChangeSupport->removeVetoableChangeListener(listener);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void VetoableChangeSupport::removeVetoableChangeListener(/*@CheckForNull*/ QString propertyName, /*@CheckForNull*/ VetoableChangeListener* listener) {
        vetoableChangeSupport->removeVetoableChangeListener(propertyName, listener);
    }


    /**
     * Reports a constrained property update to listeners
     * that have been registered to track updates of
     * all properties or a property with the specified name.
     * <p>
     * Any listener can throw a {@code PropertyVetoException} to veto the update.
     * If one of the listeners vetoes the update, this method passes
     * a new "undo" {@code PropertyChangeEvent} that reverts to the old value
     * to all listeners that already confirmed this update
     * and throws the {@code PropertyVetoException} again.
     * <p>
     * No event is fired if old and new values are equal and non-null.
     * <p>
     * This is merely a convenience wrapper around the more general
     * {@link #fireVetoableChange(PropertyChangeEvent)} method.
     *
     * @param propertyName  the programmatic name of the property that is about to change
     * @param oldValue      the old value of the property
     * @param newValue      the new value of the property
     * @throws PropertyVetoException if one of listeners vetoes the property update
     */
    /*public*/ void VetoableChangeSupport::fireVetoableChange(QString propertyName, bool oldValue, bool newValue) /*throw (PropertyVetoException)*/{
     vetoableChangeSupport->fireVetoableChange(propertyName, oldValue, newValue);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void VetoableChangeSupport::fireVetoableChange(PropertyChangeEvent* event) /*throw (PropertyVetoException)*/ {
        vetoableChangeSupport->fireVetoableChange(event);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void VetoableChangeSupport::fireVetoableChange(QString propertyName, int oldValue, int newValue) /*throw (PropertyVetoException)*/ {
        vetoableChangeSupport->fireVetoableChange(propertyName, oldValue, newValue);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void VetoableChangeSupport::fireVetoableChange(QString propertyName, QVariant oldValue, QVariant newValue) /*throw (PropertyVetoException)*/ {
        vetoableChangeSupport->fireVetoableChange(propertyName, oldValue, newValue);
    }



