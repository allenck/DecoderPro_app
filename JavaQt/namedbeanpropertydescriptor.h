#ifndef NAMEDBEANPROPERTYDESCRIPTOR_H
#define NAMEDBEANPROPERTYDESCRIPTOR_H
#include <QString>
#include <namedbean.h>

/**
 * Describes metadata about a given property key for a NamedBean. This metadata is used by the
 * BeanTable actions to display and edit the properties in question.
 *
 * @author Balazs Racz Copyright (C) 2018
 */
//template<class E>
/*public*/ /*abstract*/ class NamedBeanPropertyDescriptor {
public:
    /**
     * Key of the property, to be used in the setProperty and getProperty functions on the
     * NamedBean.
     */
    /*public*/ /*final*/ QString propertyKey;
    /**
     * Return user-visible text to render as a column header for the BeanTable representing this
     * setting.
     * @return localized string
     */
 virtual /*public*/ /*abstract*/ QString getColumnHeaderText() {return "";}

    /**
     * Determines whether this property is editable.
     * @param bean the Bean object of the given row.
     * @return true for editable, false for disabled.
     */
 virtual /*public*/ /*abstract*/ bool isEditable(NamedBean* bean) {return false;}

    /** @return Class for the property values. This class is used to find a matching Renderer for
     the BeanTable column to display and edit the value of this property. For example returning
     Boolean.class will show a checkbox.  */
    /*public*/ QString getValueClass() {
        return defaultValue.typeName();
    }
 /** What should be displayed when a given Bean does not have this property set. */
 //template<class E>
 /*public*/ /*final*/ QVariant defaultValue;
protected:
 //template<class E>
 /*protected*/ NamedBeanPropertyDescriptor(QString propertyKey, QVariant defaultValue) {
     this->propertyKey = propertyKey;
     this->defaultValue = defaultValue;
 }

};

#endif // NAMEDBEANPROPERTYDESCRIPTOR_H
