#ifndef PROPERTYCHANGEFIRER_H
#define PROPERTYCHANGEFIRER_H
#include "propertychangeevent.h"

/**
 * Interface that defines the methods needed to fire property changes.
 *
 * @author Randall Wood Copyright 2020
 */
//This interface exists so that multiple implementations can inherit the Javadocs
/*public*/ /*interface*/class  PropertyChangeFirer {
public:
    /**
     * Fire an indexed property change. Despite being public due to limitations
     * in Java 8, this method should only be called by the subclasses of
     * implementing classes, as this will become a protected class when JMRI
     * requires Java 11 or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param index        the index of the property element that was changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     */
    //virtual void fireIndexedPropertyChange(QString propertyName, int index, bool oldValue, bool newValue) const =0;

    /**
     * Fire an indexed property change. Despite being public due to limitations
     * in Java 8, this method should only be called by the subclasses of
     * implementing classes, as this will become a protected class when JMRI
     * requires Java 11 or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param index        the index of the property element that was changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     */
    //virtual void fireIndexedPropertyChange(QString propertyName, int index, int oldValue, int newValue) const =0;

    /**
     * Fire an indexed property change. Despite being public due to limitations
     * in Java 8, this method should only be called by the subclasses of
     * implementing classes, as this will become a protected class when JMRI
     * requires Java 11 or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param index        the index of the property element that was changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     */
  virtual void fireIndexedPropertyChange(QString propertyName, int /*index*/, QVariant /*oldValue*/, QVariant /*newValue*/) const{}

    /**
     * Fire a property change. Despite being public due to limitations
     * in Java 8, this method should only be called by the subclasses of
     * implementing classes, as this will become a protected class when JMRI
     * requires Java 11 or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     */
  virtual void firePropertyChange(QString /*propertyName*/, bool /*oldValue*/, bool /*newValue*/) const {}

    /**
     * Fire a property change. Despite being public due to limitations
     * in Java 8, this method should only be called by the subclasses of
     * implementing classes, as this will become a protected class when JMRI
     * requires Java 11 or newer.
     *
     * @param event the PropertyChangeEvent to be fired
     */
  virtual void firePropertyChange(PropertyChangeEvent* /*event*/) const {}

    /**
     * Fire a property change. Despite being public due to limitations
     * in Java 8, this method should only be called by the subclasses of
     * implementing classes, as this will become a protected class when JMRI
     * requires Java 11 or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     */
    //virtual void firePropertyChange(QString propertyName, int oldValue, int newValue) const =0;

    /**
     * Fire a property change. Despite being public due to limitations
     * in Java 8, this method should only be called by the subclasses of
     * implementing classes, as this will become a protected class when JMRI
     * requires Java 11 or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     */
    virtual void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue) const =0;

};
Q_DECLARE_INTERFACE(PropertyChangeFirer, "PropertyChangeFirer")
#endif // PROPERTYCHANGEFIRER_H
