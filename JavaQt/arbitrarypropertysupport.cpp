#include "arbitrarypropertysupport.h"
#include "beans.h"
#include <QMap>
#include "exceptions.h"
#include <QSet>
#include <QVariant>

ArbitraryPropertySupport::ArbitraryPropertySupport(QObject *parent) : QObject(parent)
{
 properties = QMap<QString, QVariantList>();
}
/**
 * Provide support for converging the Arbitrary* classes with the non-arbitrary
 * versions of those classes so that the Arbitrary* version can extend the
 * non-arbitrary class.
 */
// /*public*/ class ArbitraryPropertySupport implements BeanInterface {


    /*public*/ ArbitraryPropertySupport::ArbitraryPropertySupport(UnboundBean* bean, QObject *parent) {
        this->bean = bean;
    }

    //@Override
    /*public*/ void ArbitraryPropertySupport::setIndexedProperty(QString key, int index, QVariant value) {
        if (Beans::hasIntrospectedProperty((QObject*)this->bean, key)) {
            Beans::setIntrospectedIndexedProperty((QObject*)this->bean, key, index, value);
        } else {
            if (!this->properties.contains(key)) {
                this->properties.insert(key, QVariantList());
            }
            QVariantList array =/* (QVariant[])*/ this->properties.value(key);
            if (index < array.length()) {
                array.replace(index, value);
            } else {
                QVariantList grown = QVariantList(array);//Arrays.copyOf(array, index + 1);
                grown.replace(index, value);
                this->properties.insert(key, grown);
            }
        }
    }

    //@Override
    /*public*/ QVariant ArbitraryPropertySupport::getIndexedProperty(QString key, int index) {
#if 0
        if (this->properties.contains(key) && this->properties.value(key).getClass().isArray()) {
            try {
                return ( this->properties.value(key)).at(index);
            } catch (ArrayIndexOutOfBoundsException ex) {
                return QVariant();
            }
        }
#endif
        return Beans::getIntrospectedIndexedProperty((QObject*)this->bean, key, index);
    }

    //@Override
    /*public*/ void ArbitraryPropertySupport::setProperty(QString key, QVariant value) {
        QVariantList valueList = QVariantList();
        valueList.append(value);

        // use write method for property if it exists
        if (Beans::hasIntrospectedProperty((QObject*)this->bean, key)) {
            Beans::setIntrospectedProperty((QObject*)this->bean, key, valueList);
        } else {
            this->properties.insert(key, valueList);
        }
    }

    //@Override
    /*public*/ QVariant ArbitraryPropertySupport::getProperty(QString key) {
        if (this->properties.contains(key)) {
            return this->properties.value(key);
        }
        return Beans::getIntrospectedProperty((QObject*)this->bean, key);
    }

    //@Override
    /*public*/ bool ArbitraryPropertySupport::hasProperty(QString key) {
        return (this->properties.contains(key) || Beans::hasIntrospectedProperty((QObject*)this->bean, key));
    }

    //@Override
    /*public*/ bool ArbitraryPropertySupport::hasIndexedProperty(QString key) {
        return (/*(this->properties.contains(key) && this->properties.value(key).getClass().isArray())
                ||*/ Beans::hasIntrospectedIndexedProperty((QObject*)this->bean, key));
    }

    //@Override
    /*public*/ QSet<QString> ArbitraryPropertySupport::getPropertyNames() {
        QSet<QString> names = QSet<QString>();
        names.unite(this->properties.keys().toSet());
        names.unite(Beans::getIntrospectedPropertyNames((QObject*)this->bean));
        return names;
    }
