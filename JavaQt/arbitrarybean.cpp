#include "arbitrarybean.h"
#include "beans.h"
#include "arbitrarypropertysupport.h"
#include <QVariant>
#include <QSet>

ArbitraryBean::ArbitraryBean(QObject* parent) : Bean(parent)
{
  arbitraryPropertySupport = new ArbitraryPropertySupport(this);
}

/**
 * Generic implementation of {@link jmri.beans.BeanInterface} with a complete
 * implementation of {@link java.beans.PropertyChangeSupport} and support for
 * arbitrary properties defined at runtime.
 * <p>
 * See the PropertyChangeSupport documentation for complete documentation of
 * those methods.
 *
 * @author rhwood
 * @see java.beans.PropertyChangeSupport
 */
// /*public*/ abstract class ArbitraryBean extends Bean {


    //@Override
    /*public*/ void ArbitraryBean::setProperty(QString key, QVariant value) {
        if (Beans::hasIntrospectedProperty(this, key)) {
            Beans::setIntrospectedProperty(this, key, value);
        } else {
            QVariant oldValue = this->arbitraryPropertySupport->getProperty(key);
            this->arbitraryPropertySupport->setProperty(key, value);
            this->firePropertyChange(key, oldValue, value);
        }
    }

    //@Override
    /*public*/ void ArbitraryBean::setIndexedProperty(QString key, int index, QVariant value) {
        if (Beans::hasIntrospectedIndexedProperty(this, key)) {
            Beans::setIntrospectedIndexedProperty(this, key, index, value);
        } else {
            QVariant oldValue = this->arbitraryPropertySupport->getIndexedProperty(key, index);
            this->arbitraryPropertySupport->setIndexedProperty(key, index, value);
            this->fireIndexedPropertyChange(key, index, oldValue, value);
        }
    }

    //@Override
    /*public*/ QVariant ArbitraryBean::getIndexedProperty(QString key, int index) {
        return this->arbitraryPropertySupport->getIndexedProperty(key, index);
    }

    //@Override
    /*public*/ QVariant ArbitraryBean::getProperty(QString key) {
        return this->arbitraryPropertySupport->getProperty(key);
    }

    //@Override
    /*public*/ bool ArbitraryBean::hasProperty(QString key) {
        return this->arbitraryPropertySupport->hasProperty(key);
    }

    //@Override
    /*public*/ bool ArbitraryBean::hasIndexedProperty(QString key) {
        return this->arbitraryPropertySupport->hasIndexedProperty(key);
    }

    //@Override
    /*public*/ QSet<QString> ArbitraryBean::getPropertyNames() {
        return this->arbitraryPropertySupport->getPropertyNames();
    }
