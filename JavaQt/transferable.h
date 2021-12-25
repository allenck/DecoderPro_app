#ifndef TRANSFERABLE_H
#define TRANSFERABLE_H
#include <QObject>
#include "exceptions.h"
#include <QVariant>

/**
 * Defines the interface for classes that can be used to provide data
 * for a transfer operation.
 * <p>
 * For information on using data transfer with Swing, see
 * <a href="http://docs.oracle.com/javase/tutorial/uiswing/dnd/index.html">
 * How to Use Drag and Drop and Data Transfer</a>,
 * a section in <em>The Java Tutorial</em>, for more information.
 *
 * @author      Amy Fowler
 */

class DataFlavor;
/*public*/ /*interface*/ class Transferable  : public QObject
{
 Q_OBJECT
public:
    Transferable() {}

/**
 * Returns an array of DataFlavor objects indicating the flavors the data
 * can be provided in.  The array should be ordered according to preference
 * for providing the data (from most richly descriptive to least descriptive).
 * @return an array of data flavors in which this data can be transferred
 */
virtual /*public*/ QVector<DataFlavor*>* getTransferDataFlavors() {return NULL;}

/**
 * Returns whether or not the specified data flavor is supported for
 * this object.
 * @param flavor the requested flavor for the data
 * @return boolean indicating whether or not the data flavor is supported
 */
virtual /*public*/ bool isDataFlavorSupported(DataFlavor* /*flavor*/) {return false;}

/**
 * Returns an object which represents the data to be transferred.  The class
 * of the object returned is defined by the representation class of the flavor.
 *
 * @param flavor the requested flavor for the data
 * @see DataFlavor#getRepresentationClass
 * @exception IOException                if the data is no longer available
 *              in the requested flavor.
 * @exception UnsupportedFlavorException if the requested data flavor is
 *              not supported.
 */
    /*public*/ QVariant getTransferData(DataFlavor* /*flavor*/) /*throw (UnsupportedFlavorException, IOException)*/ {return QVariant();}

};
#endif // TRANSFERABLE_H
