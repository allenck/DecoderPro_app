#include "propertychangeevent.h"

PropertyChangeEvent::PropertyChangeEvent(QObject* source, QString propertyName,
                                         QVariant oldValue, QVariant newValue, QObject *parent)
 : EventObject(source, parent)
{
 this->parent = parent;
 this->source = source;
 this->propertyName = propertyName;
 this->newValue = newValue;
 this->oldValue = oldValue;
}
PropertyChangeEvent::PropertyChangeEvent(QObject *source, QString propertyName, QObject* oldValue, QObject* newValue, QObject *parent)
: EventObject(source, parent)
{
 this->parent = parent;
 this->source = source;
 this->propertyName = propertyName;
}

/**
 * A "PropertyChange" event gets delivered whenever a bean changes a "bound"
 * or "constrained" property.  A PropertyChangeEvent object is sent as an
 * argument to the PropertyChangeListener and VetoableChangeListener methods.
 * <P>
 * Normally PropertyChangeEvents are accompanied by the name and the old
 * and new value of the changed property.  If the new value is a primitive
 * type (such as int or boolean) it must be wrapped as the
 * corresponding java.lang.* Object type (such as Integer or Boolean).
 * <P>
 * Null values may be provided for the old and the new values if their
 * true values are not known.
 * <P>
 * An event source may send a null object as the name to indicate that an
 * arbitrary set of if its properties have changed.  In this case the
 * old and new values should also be null.
 */

//public class PropertyChangeEvent extends java.util.EventObject {


/**
 * Gets the programmatic name of the property that was changed.
 *
 * @return  The programmatic name of the property that was changed.
 *          May be null if multiple properties have changed.
 */
 QString PropertyChangeEvent::getPropertyName() {
    return propertyName;
}

/**
 * Gets the new value for the property, expressed as an Object.
 *
 * @return  The new value for the property, expressed as an Object.
 *          May be null if multiple properties have changed.
 */
 QVariant PropertyChangeEvent::getNewValue() {
    return newValue;
}

/**
 * Gets the old value for the property, expressed as an Object.
 *
 * @return  The old value for the property, expressed as an Object.
 *          May be null if multiple properties have changed.
 */
QVariant PropertyChangeEvent::getOldValue() {
    return oldValue;
}

/**
 * Sets the propagationId object for the event.
 *
 * @param propagationId  The propagationId object for the event.
 */
void PropertyChangeEvent::setPropagationId(QVariant propagationId) {
    this->propagationId = propagationId;
}

/**
 * The "propagationId" field is reserved for future use.  In Beans 1.0
 * the sole requirement is that if a listener catches a PropertyChangeEvent
 * and then fires a PropertyChangeEvent of its own, then it should
 * make sure that it propagates the propagationId field from its
 * incoming event to its outgoing event.
 *
 * @return the propagationId object associated with a bound/constrained
 *          property update.
 */
QVariant PropertyChangeEvent::getPropagationId() {
    return propagationId;
}

/**
 * Returns a string representation of the object.
 *
 * @return a string representation of the object
 *
 * @since 1.7
 */
 QString PropertyChangeEvent::toString() {
    QString sb;
    sb.append(/*getClass().getName()*/objectName());
    sb.append("[propertyName=").append(getPropertyName());
    appendTo(sb);
    sb.append("; oldValue=").append(getOldValue().toString());
    sb.append("; newValue=").append(getNewValue().toString());
    sb.append("; propagationId=").append(getPropagationId().toString());
    sb.append("; source=").append(getSource()->objectName());
    return sb.append("]")/*.toString()*/;
}

void PropertyChangeEvent::appendTo(QString sb) {
 Q_UNUSED(sb)
}
