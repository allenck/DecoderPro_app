#include "constrainedbean.h"
#include "vetoablechangesupport.h"
#include "loggerfactory.h"
#include "indexedpropertychangeevent.h"

ConstrainedBean::ConstrainedBean(QObject *parent) : Bean(parent)
{

}
/**
 * A Bean with support for {@link java.beans.VetoableChangeListener}s.
 *
 * @author Randall Wood
 */
///*public*/ abstract class ConstrainedBean extends Bean implements VetoableChangeProvider {


    //@Override
    /*public*/ void ConstrainedBean::setProperty(QString key, QVariant value) {
        try {
            this->fireVetoableChange(key, getProperty(key), value);
            Bean::setProperty(key, value);
        } catch (PropertyVetoException* ex) {
            // use the logger for the implementing class instead of a logger for ConstrainedBean
            LoggerFactory::getLogger(this->getClass())->warn(tr("Property %1 change vetoed.").arg(key).arg(ex->getMessage()));
            // fire a property change that does not have the new value to indicate
            // to any other listeners that the property was "reset" back to its
            // orginal value as a result of the veto
            this->firePropertyChange(key, getProperty(key), getProperty(key));
        }
    }

    //@Override
    /*public*/ void ConstrainedBean::setIndexedProperty(QString key, int index, QVariant value) {
        try {
            this->fireVetoableChange(new IndexedPropertyChangeEvent(this, key, this->getIndexedProperty(key, index), value, index));
            Bean::setIndexedProperty(key, index, value);
        } catch (PropertyVetoException* ex) {
            // use the logger for the implementing class instead of a logger for ConstrainedBean
            LoggerFactory::getLogger(this->getClass())->warn(tr("Property %1 change vetoed.").arg(key).arg(ex->getMessage()));
            // fire a property change that does not have the new value to indicate
            // to any other listeners that the property was "reset" back to its
            // orginal value as a result of the veto
            this->fireIndexedPropertyChange(key, index, getProperty(key), getProperty(key));
        }
    }

    //@Override
    /*public*/ void ConstrainedBean::addVetoableChangeListener(VetoableChangeListener* listener) {
        this->vetoableChangeSupport->addVetoableChangeListener(listener);
    }

    //@Override
    /*public*/ void ConstrainedBean::addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
        this->vetoableChangeSupport->addVetoableChangeListener(propertyName, listener);
    }

    //@Override
    /*public*/ QVector<VetoableChangeListener*> ConstrainedBean::getVetoableChangeListeners() {
        return this->vetoableChangeSupport->getVetoableChangeListeners();
    }

    //@Override
    /*public*/ QVector<VetoableChangeListener*> ConstrainedBean::getVetoableChangeListeners(QString propertyName) {
        return this->vetoableChangeSupport->getVetoableChangeListeners(propertyName);
    }

    //@Override
    /*public*/ void ConstrainedBean::removeVetoableChangeListener(VetoableChangeListener* listener) {
        this->vetoableChangeSupport->removeVetoableChangeListener(listener);
    }

    //@Override
    /*public*/ void ConstrainedBean::removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) {
        this->vetoableChangeSupport->removeVetoableChangeListener(propertyName, listener);
    }

    /**
     * Fire a vetoable property change on the current thread. Use
     * {@link java.beans.VetoableChangeSupport#fireVetoableChange(java.beans.PropertyChangeEvent)}
     * directly to fire this notification on another thread.
     *
     * If a PropertyVetoException is thrown, ensure the property change does not
     * complete.
     *
     * @param event {@link PropertyChangeEvent} to be fired
     * @throws PropertyVetoException if property update vetoed
     */
    /*public*/ void ConstrainedBean::fireVetoableChange(PropertyChangeEvent* event)  {
        this->vetoableChangeSupport->fireVetoableChange(event);
    }

    /**
     * Fire a vetoable property change on the current thread. Use
     * {@link java.beans.VetoableChangeSupport#fireVetoableChange(java.lang.String, java.lang.Object, java.lang.Object)}
     * directly to fire this notification on another thread.
     *
     * If a PropertyVetoException is thrown, ensure the property change does not
     * complete.
     *
     * @param propertyName property that is about to change
     * @param oldValue     old value of the property
     * @param newValue     new value of the property
     * @throws PropertyVetoException if property update vetoed
     */
    /*public*/ void ConstrainedBean::fireVetoableChange(QString propertyName, QVariant oldValue, QVariant newValue)  {
        this->vetoableChangeSupport->fireVetoableChange(propertyName, oldValue, newValue);
    }

    /**
     * Fire a vetoable property change on the current thread. Use
     * {@link java.beans.VetoableChangeSupport#fireVetoableChange(java.lang.String, int, int)}
     * directly to fire this notification on another thread.
     *
     * If a PropertyVetoException is thrown, ensure the property change does not
     * complete.
     *
     * @param propertyName property that is about to change
     * @param oldValue     old value of the property
     * @param newValue     new value of the property
     * @throws PropertyVetoException if property update vetoed
     */
    /*public*/ void ConstrainedBean::fireVetoableChange(QString propertyName, int oldValue, int newValue)  {
        this->vetoableChangeSupport->fireVetoableChange(propertyName, oldValue, newValue);
    }

    /**
     * Fire a vetoable property change on the current thread. Use
     * {@link java.beans.VetoableChangeSupport#fireVetoableChange(java.lang.String, boolean, boolean)}
     * directly to fire this notification on another thread.
     *
     * If a PropertyVetoException is thrown, ensure the property change does not
     * complete.
     *
     * @param propertyName property that is about to change
     * @param oldValue     old value of the property
     * @param newValue     new value of the property
     * @throws PropertyVetoException if property update vetoed
     */
    /*public*/ void ConstrainedBean::fireVetoableChange(QString propertyName, bool oldValue, bool newValue)  {
        this->vetoableChangeSupport->fireVetoableChange(propertyName, oldValue, newValue);
    }
