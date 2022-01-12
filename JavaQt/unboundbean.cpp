#include "unboundbean.h"
#include "beans.h"
#include <qvariant.h>
#include <QSet>

UnboundBean::UnboundBean(QObject *parent) : QObject(parent)
{

}
/**
 * Generic implementation of {@link jmri.beans.BeanInterface} without support
 * for arbitrary properties defined at runtime.
 * <p>
 * <b>NOTE</b> This class does not implement
 * {@link java.beans.SwingPropertyChangeSupport}. Subclass {@link jmri.beans.Bean} if
 * you need to support property change listeners.
 *
 * @author rhwood
 */
// /*public*/ abstract class UnboundBean implements BeanInterface {

    /**
     * Get value of element at <i>index</i> of property array <i>key</i>.
     * <p>
     * This implementation calls a read method for the indexed property using
     * JavaBeans introspection, and assumes, based on JavaBeans coding patterns,
     * that the read method has the following parameter: <code>index</code>.
     *
     * Note that this method returns null instead of throwing
     * {@link java.lang.ArrayIndexOutOfBoundsException} if the index is invalid
     * since the Java introspection methods provide no reliable way to get the
     * size of the indexed property.
     *
     * @return value of element or null
     */
    //@Override
    /*public*/ QVariant UnboundBean::getIndexedProperty(QString key, int index) {
        return Beans::getIntrospectedIndexedProperty(this, key, index);
    }

    /**
     * Get the value of property key.
     * <p>
     * If <i>null</i> is a valid (or expected) value for <i>key</i>, you might
     * want to use {@link Bean#hasProperty(java.lang.String)} to test that the
     * property exists.
     * <p>
     *
     * @return value of key or null.
     * @see BeanInterface#getProperty(java.lang.String)
     */
    //@Override
    /*public*/ QVariant UnboundBean::getProperty(QString key) {
        return Beans::getIntrospectedProperty(this, key);
    }

    /**
     * Return a list of property names.
     *
     * @return a Set of names
     * @see BeanInterface#getPropertyNames()
     */
    //@Override
    /*public*/ QSet<QString> UnboundBean::getPropertyNames() {
        return Beans::getIntrospectedPropertyNames(this);
    }

    /**
     * Test if a property exists.
     *
     * @return true if property exists
     * @see BeanInterface#hasProperty(java.lang.String)
     */
    //@Override
    /*public*/ bool UnboundBean::hasProperty(QString key) {
        return Beans::hasIntrospectedProperty(this, key);
    }

    //@Override
    /*public*/ bool UnboundBean::hasIndexedProperty(QString key) {
        return Beans::hasIntrospectedIndexedProperty(this, key);
    }

    /**
     * Set element at <i>index</i> of property array <i>key</i> to <i>value</i>.
     * <p>
     * This implementation calls a write method for the indexed property using
     * JavaBeans introspection, and assumes, based on JavaBeans coding patterns,
     * that the write method has the following two parameters in order:
     * <code>index</code>, <code>value</code>.
     *
     * @see BeanInterface#setIndexedProperty(java.lang.String, int,
     * java.lang.Object)
     */
    //@Override
    /*public*/ void UnboundBean::setIndexedProperty(QString key, int index, QVariant value) {
        Beans::setIntrospectedIndexedProperty(this, key, index, value);
    }

    /**
     * Set property <i>key</i> to <i>value</i>.
     * <p>
     * This implementation calls a write method for the indexed property using
     * JavaBeans introspection.
     *
     * @see BeanInterface#setProperty(java.lang.String, java.lang.Object)
     */
    //@Override
    /*public*/ void UnboundBean::setProperty(QString key, QVariant value) {
        Beans::setIntrospectedProperty(this, key, value);
    }
