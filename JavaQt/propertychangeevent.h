#ifndef PROPERTYCHANGEEVENT_H
#define PROPERTYCHANGEEVENT_H

#include <QEvent>
#include <QVariant>
#include "eventobject.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT PropertyChangeEvent : public EventObject
{
    Q_OBJECT
public:
    /**
     * Constructs a new <code>PropertyChangeEvent</code>.
     *
     * @param source  The bean that fired the event.
     * @param propertyName  The programmatic name of the property
     *          that was changed.
     * @param oldValue  The old value of the property.
     * @param newValue  The new value of the property.
     */

    explicit PropertyChangeEvent(QObject* source, QString propertyName,
                                 QVariant oldValue, QVariant newValue, QObject *parent = 0);
    PropertyChangeEvent(QObject* source, QString propertyName,
                                     QObject* oldValue, QObject* newValue, QObject *parent = 0);
    /**
     * Gets the programmatic name of the property that was changed.
     *
     * @return  The programmatic name of the property that was changed.
     *          May be null if multiple properties have changed.
     */
    QString getPropertyName();
    /**
     * Gets the new value for the property, expressed as an Object.
     *
     * @return  The new value for the property, expressed as an Object.
     *          May be null if multiple properties have changed.
     */
    QVariant getNewValue();

    /**
     * Gets the old value for the property, expressed as an Object.
     *
     * @return  The old value for the property, expressed as an Object.
     *          May be null if multiple properties have changed.
     */
    QVariant getOldValue();

    /**
     * Sets the propagationId object for the event.
     *
     * @param propagationId  The propagationId object for the event.
     */
    void setPropagationId(QVariant propagationId);
    /**
     * The "propagationId" field is reserved for future use.  In Beans 1.0
     * the sole requirement is that if a listener catches a PropertyChangeEvent
     * and then fires a PropertyChangeEvent of its own, then it should
     * make sure that it propagates the propagationId field from its
     * incoming event to its outgoing event.
     *"item"
     * @return the propagationId object associated with a bound/constrained
     *          property update.
     */
    QVariant getPropagationId();
    /**
     * Returns a string representation of the object.
     *
     * @return a string representation of the object
     *
     * @since 1.7
     */
    QString toString();
    void appendTo(QString sb);
    QObject* source;
signals:
    
public slots:
private:
    QObject *parent;
 const static long long serialVersionUID = 7042693688939648123L;
 /**
  * name of the property that changed.  May be null, if not known.
  * @serial
  */
 QString propertyName;

 /**
  * New value for property.  May be null if not known.
  * @serial
  */
 QVariant newValue;

 /**
  * Previous value for property.  May be null if not known.
  * @serial
  */
 QVariant oldValue;

 /**
  * Propagation ID.  May be null.
  * @serial
  * @see #getPropagationId
  */
 QVariant propagationId;

 friend class Java_VetoableChangeSupport;
};

#endif // PROPERTYCHANGEEVENT_H
