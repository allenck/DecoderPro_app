#include "propertyvetoexception.h"
#include "propertychangeevent.h"

/**
 * A PropertyVetoException is thrown when a proposed change to a
 * property represents an unacceptable value.
 */

/*public*/
//class PropertyVetoException extends Exception {
//    private static final long serialVersionUID = 129596057694162164L;

/**
 * Constructs a <code>PropertyVetoException</code> with a
 * detailed message.
 *
 * @param mess Descriptive message
 * @param evt A PropertyChangeEvent describing the vetoed change.
 */
/*public*/ PropertyVetoException::PropertyVetoException(QString mess, PropertyChangeEvent* evt, Throwable *cause)
 : Exception(mess)
{
    //super(mess);
    this->evt = evt;
}

 /**
 * Gets the vetoed <code>PropertyChangeEvent</code>.
 *
 * @return A PropertyChangeEvent describing the vetoed change.
 */
/*public*/ PropertyChangeEvent* PropertyVetoException::getPropertyChangeEvent() {
    return evt;
}


