#ifndef PROPERTYCHANGELISTENERMAP_H
#define PROPERTYCHANGELISTENERMAP_H
#include <QList>
#include "propertychangelistener.h"
#include "changelistenermap.h"

class PropertyChangeListenerMap : public ChangeListenerMap<PropertyChangeListener*>
{
    Q_OBJECT
public:
    explicit PropertyChangeListenerMap(QObject *parent = 0);
    /*public final */PropertyChangeListener* extract(PropertyChangeListener* listener);

signals:
    
public slots:
private:
 /*private static final*/ static QList<PropertyChangeListener*> EMPTY()/* = {}*/;
 protected:
    /**
     * Creates an array of {@link PropertyChangeListener PropertyChangeListener} objects.
     * This method uses the same instance of the empty array
     * when {@code length} equals {@code 0}.
     *
     * @param length  the array length
     * @return        an array with specified length
     */
    //@Override
    /*protected*/ QList<PropertyChangeListener*> newArray(int length);
    /**
     * Creates a {@link PropertyChangeListenerProxy PropertyChangeListenerProxy}
     * object for the specified property.
     *
     * @param name      the name of the property to listen on
     * @param listener  the listener to process events
     * @return          a {@code PropertyChangeListenerProxy} object
     */
    //@Override
    /*protected*/ PropertyChangeListener* newProxy(QString name, PropertyChangeListener* listener);

    
};

#endif // PROPERTYCHANGELISTENERMAP_H
