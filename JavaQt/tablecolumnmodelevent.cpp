#include "tablecolumnmodelevent.h"

//TableColumnModelEvent::TableColumnModelEvent()
//{

//}
/**
 * <B>TableColumnModelEvent</B> is used to notify listeners that a table
 * column model has changed, such as a column was added, removed, or
 * moved.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @author Alan Chung
 * @see TableColumnModelListener
 */
///*public*/ class TableColumnModelEvent extends java.util.EventObject
//{
//

//
// Constructors
//

/**
 * Constructs a {@code TableColumnModelEvent} object.
 *
 * @param source  the {@code TableColumnModel} that originated the event
 * @param from    an int specifying the index from where the column was
 *                moved or removed
 * @param to      an int specifying the index to where the column was
 *                moved or added
 * @see #getFromIndex
 * @see #getToIndex
 */
/*public*/ TableColumnModelEvent::TableColumnModelEvent(TableColumnModel* source, int from, int to) {
    //super(source);
    fromIndex = from;
    toIndex = to;
}

//
// Querying Methods
//

/** Returns the fromIndex.  Valid for removed or moved events */
/*public*/ int TableColumnModelEvent::getFromIndex() { return fromIndex; }

/** Returns the toIndex.  Valid for add and moved events */
/*public*/ int TableColumnModelEvent::getToIndex() { return toIndex; }
