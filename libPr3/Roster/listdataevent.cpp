#include "listdataevent.h"


//ListDataEvent::ListDataEvent(QObject *parent) :
//    EventObject(parent)
//{
//}
/**
 * Defines an event that encapsulates changes to a list.
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
 * @author Hans Muller
 */
// /*public*/ class ListDataEvent extends EventObject
//{


    /**
     * Returns the event type. The possible values are:
     * <ul>
     * <li> {@link #CONTENTS_CHANGED}
     * <li> {@link #INTERVAL_ADDED}
     * <li> {@link #INTERVAL_REMOVED}
     * </ul>
     *
     * @return an int representing the type value
     */
    /*public*/ int ListDataEvent::getType() { return type; }

    /**
     * Returns the lower index of the range. For a single
     * element, this value is the same as that returned by {@link #getIndex1}.

     *
     * @return an int representing the lower index value
     */
    /*public*/ int ListDataEvent::getIndex0() { return index0; }
    /**
     * Returns the upper index of the range. For a single
     * element, this value is the same as that returned by {@link #getIndex0}.
     *
     * @return an int representing the upper index value
     */
    /*public*/ int ListDataEvent::getIndex1() { return index1; }

    /**
     * Constructs a ListDataEvent object. If index0 is >
     * index1, index0 and index1 will be swapped such that
     * index0 will always be <= index1.
     *
     * @param source  the source Object (typically <code>this</code>)
     * @param type    an int specifying {@link #CONTENTS_CHANGED},
     *                {@link #INTERVAL_ADDED}, or {@link #INTERVAL_REMOVED}
     * @param index0  one end of the new interval
     * @param index1  the other end of the new interval
     */
/*public*/ ListDataEvent::ListDataEvent(QObject* source, int type, int index0, int index1, QObject *parent) : EventObject(source, parent)
{
        //super(source);
        this->type = type;
        this->index0 = qMin(index0, index1);
        this->index1 = qMax(index0, index1);
    }

    /**
     * Returns a string representation of this ListDataEvent. This method
     * is intended to be used only for debugging purposes, and the
     * content and format of the returned string may vary between
     * implementations. The returned string may be empty but may not
     * be <code>null</code>.
     *
     * @since 1.4
     * @return  a string representation of this ListDataEvent.
     */
    /*public*/ QString ListDataEvent::toString() {
        return /*getClass().getName()*/ QString("ListDataEvent")+
        "[type=" + QString::number(type) +
        ",index0=" + QString::number(index0) +
        ",index1=" + QString::number(index1) + "]";
    }
