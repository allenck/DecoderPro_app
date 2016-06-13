#ifndef INDEXEDPROPERTYCHANGEEVENT_H
#define INDEXEDPROPERTYCHANGEEVENT_H
#include "propertychangeevent.h"
#include "javaqt_global.h"

class JAVAQTSHARED_EXPORT IndexedPropertyChangeEvent : public PropertyChangeEvent
{
    Q_OBJECT
public:
//    explicit IndexedPropertyChangeEvent(QObject *parent = 0);
    /**
     * Constructs a new <code>IndexedPropertyChangeEvent</code> object.
     *
     * @param source  The bean that fired the event.
     * @param propertyName  The programmatic name of the property that
     *             was changed.
     * @param oldValue      The old value of the property.
     * @param newValue      The new value of the property.
     * @param index index of the property element that was changed.
     */
    IndexedPropertyChangeEvent(QObject* source, QString propertyName,
                                      QVariant oldValue, QVariant newValue,
                                      int index);
    /**
     * Gets the index of the property that was changed.
     *
     * @return The index specifying the property element that was
     *         changed.
     */
    int getIndex();
    void appendTo(QString sb);

signals:
    
public slots:
private:
    static const long long serialVersionUID = -320227448495806870L;
    int index;

};

#endif // INDEXEDPROPERTYCHANGEEVENT_H
