#include "changeevent.h"

//ChangeEvent::ChangeEvent(QObject *parent) :
//    EventObject(parent)
//{
//}
/**
 * ChangeEvent is used to notify interested parties that
 * state has changed in the event source.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans<sup><font size="-2">TM</font></sup>
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author Jeff Dinkins
 */
// /*public*/ class ChangeEvent extends EventObject {
    /**
     * Constructs a ChangeEvent object.
     *
     * @param source  the Object that is the source of the event
     *                (typically <code>this</code>)
     */
/*public*/ ChangeEvent::ChangeEvent(QObject* source, QObject *parent) : EventObject(source, parent)
{
 //super(source);
}
