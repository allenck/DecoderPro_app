#ifndef PROPERTYCHANGESUPPORT_H
#define PROPERTYCHANGESUPPORT_H

#include <QObject>
#include "propertychangelistenermap.h"
#include "javaqt_global.h"
#include "logger.h"
#include "propertychangeprovider.h"
#include "propertychangefirer.h"
#include "swingpropertychangesupport.h"

class JAVAQTSHARED_EXPORT PropertyChangeSupport :  public PropertyChangeProvider, public PropertyChangeFirer
{
 public:
  Q_INTERFACES(PropertyChangeProvider PropertyChangeFirer)
 protected:
    //virtual QObject* self() =0;

    /**
     * Provide a {@link java.beans.PropertyChangeSupport} helper.
     */
    /*protected*/ /*final*/ SwingPropertyChangeSupport* propertyChangeSupport = new SwingPropertyChangeSupport((QObject*)this, (QObject*)this);
 public:
    /** {@inheritDoc} */
    //@Override
    /*public*/ void addPropertyChangeListener(/*@CheckForNull*/ PropertyChangeListener* listener) override{
        propertyChangeSupport->addPropertyChangeListener(listener);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void addPropertyChangeListener(/*@CheckForNull*/ QString propertyName,
            /*@CheckForNull*/ PropertyChangeListener* listener) override{
        propertyChangeSupport->addPropertyChangeListener(propertyName, listener);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners()const override{
        return propertyChangeSupport->getPropertyChangeListeners();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(/*@CheckForNull*/ QString propertyName) override{
        return propertyChangeSupport->getPropertyChangeListeners(propertyName);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void removePropertyChangeListener(/*@CheckForNull*/ PropertyChangeListener* listener) override{
        propertyChangeSupport->removePropertyChangeListener(listener);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void removePropertyChangeListener(/*@CheckForNull*/ QString propertyName,
            /*@CheckForNull*/ PropertyChangeListener* listener) override{
        propertyChangeSupport->removePropertyChangeListener(propertyName, listener);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
//    /*public*/ void fireIndexedPropertyChange(QString propertyName, int index, bool oldValue, bool newValue) {
//        propertyChangeSupport.fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
//    }

    /**
     * {@inheritDoc}
     */
    //@Override
//    /*public*/ void fireIndexedPropertyChange(String propertyName, int index, int oldValue, int newValue) {
//        propertyChangeSupport.fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
//    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void fireIndexedPropertyChange(QString propertyName, int index, QVariant oldValue, QVariant newValue) {
        propertyChangeSupport->fireIndexedPropertyChange(propertyName, index, oldValue, newValue);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
//    /*public*/ void firePropertyChange(String propertyName, boolean oldValue, boolean newValue) {
//        propertyChangeSupport.firePropertyChange(propertyName, oldValue, newValue);
//    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void firePropertyChange(PropertyChangeEvent* event) {
        propertyChangeSupport->firePropertyChange(event);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
//    /*public*/ void firePropertyChange(String propertyName, int oldValue, int newValue) {
//        propertyChangeSupport.firePropertyChange(propertyName, oldValue, newValue);
//    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void firePropertyChange(QString propertyName, QVariant oldValue, QVariant newValue)const override{
        propertyChangeSupport->firePropertyChange(propertyName, oldValue, newValue);
    }

};
Q_DECLARE_INTERFACE(PropertyChangeSupport, "PropertyChangeSupport")
#endif // PROPERTYCHANGESUPPORT_H
