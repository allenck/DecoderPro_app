#ifndef PROPERTYCHANGELISTENERPROXY_H
#define PROPERTYCHANGELISTENERPROXY_H
#include "eventlistenerproxy.h"
#include "propertychangelistener.h"

class PropertyChangeListenerProxy : public EventListenerProxy<PropertyChangeListener>
{
    //Q_OBJECT
public:
    //explicit PropertyChangeListenerProxy(QObject *parent = 0);
    /**
     * Constructor which binds the {@code PropertyChangeListener}
     * to a specific property.
     *
     * @param propertyName  the name of the property to listen on
     * @param listener      the listener object
     */
    PropertyChangeListenerProxy(QString propertyName, PropertyChangeListener* listener);
    /**
     * Forwards the property change event to the listener delegate.
     *
     * @param event  the property change event
     */
    void propertyChange(PropertyChangeEvent *event);
    /**
     * Returns the name of the named property associated with the listener.
     *
     * @return the name of the named property associated with the listener
     */
    QString getPropertyName();

signals:
    
public slots:
private:
    /*private final*/ QString propertyName;

};

#endif // PROPERTYCHANGELISTENERPROXY_H
