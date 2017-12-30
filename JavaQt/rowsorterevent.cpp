#include "rowsorterevent.h"
#include <QVector>
#include "exceptions.h"

//RowSorterEvent::RowSorterEvent()
//{

//}
/**
 * <code>RowSorterEvent</code> provides notification of changes to
 * a <code>RowSorter</code>.  Two types of notification are possible:
 * <ul>
 * <li><code>Type.SORT_ORDER_CHANGED</code>: indicates the sort order has
 *     changed.  This is typically followed by a notification of:
 * <li><code>Type.SORTED</code>: indicates the contents of the model have
 *     been transformed in some way.  For example, the contents may have
 *     been sorted or filtered.
 * </ul>
 *
 * @see javax.swing.RowSorter
 * @since 1.6
 */
///*public*/ class RowSorterEvent extends java.util.EventObject {

/**
 * Enumeration of the types of <code>RowSorterEvent</code>s.
 *
 * @since 1.6
 */

/**
 * Creates a <code>RowSorterEvent</code> of type
 * <code>SORT_ORDER_CHANGED</code>.
 *
 * @param source the source of the change
 * @throws IllegalArgumentException if <code>source</code> is
 *         <code>NULL</code>
 */
/*public*/ RowSorterEvent::RowSorterEvent(RowSorter* source) : EventObject(source)
{
    //this(source, SORT_ORDER_CHANGED, NULL);
 type = SORT_ORDER_CHANGED;
 oldViewToModel = NULL;
}

/**
 * Creates a <code>RowSorterEvent</code>.
 *
 * @param source the source of the change
 * @param type the type of event
 * @param previousRowIndexToModel the mapping from model indices to
 *        view indices prior to the sort, may be <code>NULL</code>
 * @throws IllegalArgumentException if source or <code>type</code> is
 *         <code>NULL</code>
 */
/*public*/ RowSorterEvent::RowSorterEvent(RowSorter* source, Type type,
                      QVector<int>* previousRowIndexToModel) : EventObject(source)
{
    //super(source);
    if (type == NULL) {
        throw new IllegalArgumentException("type must be non-NULL");
    }
    this->type = type;
    this->oldViewToModel = previousRowIndexToModel;
}

/**
 * Returns the source of the event as a <code>RowSorter</code>.
 *
 * @return the source of the event as a <code>RowSorter</code>
 */
/*public*/ RowSorter* RowSorterEvent::getSource() {
    return (RowSorter*)EventObject::getSource();
}

/**
 * Returns the type of event.
 *
 * @return the type of event
 */
/*public*/ RowSorterEvent::Type RowSorterEvent::getType() {
    return type;
}

/**
 * Returns the location of <code>index</code> in terms of the
 * model prior to the sort.  This method is only useful for events
 * of type <code>SORTED</code>.  This method will return -1 if the
 * index is not valid, or the locations prior to the sort have not
 * been provided.
 *
 * @param index the index in terms of the view
 * @return the index in terms of the model prior to the sort, or -1 if
 *         the location is not valid or the mapping was not provided.
 */
/*public*/ int RowSorterEvent::convertPreviousRowIndexToModel(int index) {
    if (oldViewToModel != NULL && index >= 0 &&
            index < oldViewToModel->length()) {
        return oldViewToModel->at(index);
    }
    return -1;
}

/**
 * Returns the number of rows before the sort.  This method is only
 * useful for events of type <code>SORTED</code> and if the
 * last locations have not been provided will return 0.
 *
 * @return the number of rows in terms of the view prior to the sort
 */
/*public*/ int RowSorterEvent::getPreviousRowCount() {
    return (oldViewToModel == NULL) ? 0 : oldViewToModel->length();
}
