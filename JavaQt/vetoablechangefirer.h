#ifndef VETOABLECHANGEFIRER_H
#define VETOABLECHANGEFIRER_H
#include <QtCore>
#include "propertyvetoexception.h"

/**
 * Interface that defines the methods needed to fire vetoable property changes.
 *
 * @author Randall Wood Copyright 2020
 */
// This interface exists so that multiple implementations can inherit the Javadocs
/*public*/ /*interface*/class  VetoableChangeFirer {

    /**
     * Fire a property change. Despite being public due to limitations in Java
     * 8, this method should only be called by the subclasses of implementing
     * classes, as this will become a protected class when JMRI requires Java 11
     * or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     * @throws PropertyVetoException if one of listeners vetoes the property
     *                               update
     */
    virtual void fireVetoableChange(QString propertyName, bool oldValue, bool newValue) throw (PropertyVetoException) =0;

    /**
     * Fire a property change. Despite being public due to limitations in Java
     * 8, this method should only be called by the subclasses of implementing
     * classes, as this will become a protected class when JMRI requires Java 11
     * or newer.
     *
     * @param event the PropertyChangeEvent to be fired
     * @throws PropertyVetoException if one of listeners vetoes the property
     *                               update
     */
    virtual void fireVetoableChange(PropertyChangeEvent* event) throw (PropertyVetoException) = 0;

    /**
     * Fire a property change. Despite being public due to limitations in Java
     * 8, this method should only be called by the subclasses of implementing
     * classes, as this will become a protected class when JMRI requires Java 11
     * or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     * @throws PropertyVetoException if one of listeners vetoes the property
     *                               update
     */
    virtual void fireVetoableChange(QString propertyName, int oldValue, int newValue) throw (PropertyVetoException) = 0;

    /**
     * Fire a property change. Despite being public due to limitations in Java
     * 8, this method should only be called by the subclasses of implementing
     * classes, as this will become a protected class when JMRI requires Java 11
     * or newer.
     *
     * @param propertyName the programmatic name of the property that was
     *                     changed
     * @param oldValue     the old value of the property
     * @param newValue     the new value of the property
     * @throws PropertyVetoException if one of listeners vetoes the property
     *                               update
     */
    virtual void fireVetoableChange(QString propertyName, QVariant oldValue, QVariant newValue) throw (PropertyVetoException) = 0;

};
Q_DECLARE_INTERFACE(VetoableChangeFirer, "VetoableChangeFirer")
#endif // VETOABLECHANGEFIRER_H
