#include "propertychangelistenermap.h"
#include "propertychangelistenerproxy.h"

PropertyChangeListenerMap::PropertyChangeListenerMap(QObject *parent) :
    ChangeListenerMap(parent)
{
}
/**
     * This is a {@link ChangeListenerMap ChangeListenerMap} implementation
     * that works with {@link PropertyChangeListener PropertyChangeListener} objects.
     */
   // private static final class PropertyChangeListenerMap extends ChangeListenerMap<PropertyChangeListener> {
       // private static final PropertyChangeListener[] EMPTY = {};

        /**
         * Creates an array of {@link PropertyChangeListener PropertyChangeListener} objects.
         * This method uses the same instance of the empty array
         * when {@code length} equals {@code 0}.
         *
         * @param length  the array length
         * @return        an array with specified length
         */
        //@Override
        /*protected*/ QList<PropertyChangeListener*> PropertyChangeListenerMap::newArray(int length) {
            return (0 < length)
                    ? QList< PropertyChangeListener*>()
                    : /*EMPTY*/QList< PropertyChangeListener*>();
        }

        /**
         * Creates a {@link PropertyChangeListenerProxy PropertyChangeListenerProxy}
         * object for the specified property.
         *
         * @param name      the name of the property to listen on
         * @param listener  the listener to process events
         * @return          a {@code PropertyChangeListenerProxy} object
         */
        //@Override
        /*protected*/ PropertyChangeListener* PropertyChangeListenerMap::newProxy(QString name, PropertyChangeListener* listener) {
            return (PropertyChangeListener*)(new PropertyChangeListenerProxy(name, listener));
        }

        /**
         * {@inheritDoc}
         */
        /*public final*/ PropertyChangeListener* PropertyChangeListenerMap::extract(PropertyChangeListener* listener) {
            //while (listener instanceof PropertyChangeListenerProxy) {
            while(dynamic_cast<PropertyChangeListenerProxy*>( listener) != NULL)
            {
                listener = ((PropertyChangeListenerProxy*) listener)->getListener();
            }
            return listener;
        }

