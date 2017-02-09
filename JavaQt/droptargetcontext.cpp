#include "droptargetcontext.h"
#include "droptarget.h"
#include "droptargetcontextpeer.h"
#include "component.h"
#include "dataflavor.h"
#include "transferable.h"
#include <QVector>

//DropTargetContext::DropTargetContext(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * A <code>DropTargetContext</code> is created
 * whenever the logical cursor associated
 * with a Drag and Drop operation coincides with the visible geometry of
 * a <code>Component</code> associated with a <code>DropTarget</code>.
 * The <code>DropTargetContext</code> provides
 * the mechanism for a potential receiver
 * of a drop operation to both provide the end user with the appropriate
 * drag under feedback, but also to effect the subsequent data transfer
 * if appropriate.
 *
 * @since 1.2
 */

// /*public*/ class DropTargetContext implements Serializable {

//    private static final long serialVersionUID = -634158968993743371L;

/**
 * Construct a <code>DropTargetContext</code>
 * given a specified <code>DropTarget</code>.
 * <P>
 * @param dt the DropTarget to associate with
 */

DropTargetContext::DropTargetContext(DropTarget* dt) {
    //super();

    dropTarget = dt;
    dropTargetContextPeer = NULL;
    transferable = NULL;
}

/**
 * This method returns the <code>DropTarget</code> associated with this
 * <code>DropTargetContext</code>.
 * <P>
 * @return the <code>DropTarget</code> associated with this <code>DropTargetContext</code>
 */

/*public*/ DropTarget* DropTargetContext::getDropTarget() { return dropTarget; }

/**
 * This method returns the <code>Component</code> associated with
 * this <code>DropTargetContext</code>.
 * <P>
 * @return the Component associated with this Context
 */

/*public*/ Component* DropTargetContext::getComponent() { return dropTarget->getComponent(); }

/**
 * Called when associated with the <code>DropTargetContextPeer</code>.
 * <P>
 * @param dtcp the <code>DropTargetContextPeer</code>
 */

/*public*/ void DropTargetContext::addNotify(DropTargetContextPeer* dtcp) {
    dropTargetContextPeer = dtcp;
}

/**
 * Called when disassociated with the <code>DropTargetContextPeer</code>.
 */

/*public*/ void DropTargetContext::removeNotify() {
    dropTargetContextPeer = NULL;
//    transferable          = NULL;
}

/**
 * This method sets the current actions acceptable to
 * this <code>DropTarget</code>.
 * <P>
 * @param actions an <code>int</code> representing the supported action(s)
 */

/*protected*/ void DropTargetContext::setTargetActions(int actions)
{
 DropTargetContextPeer* peer = getDropTargetContextPeer();
 if (peer != NULL)
 {
//        synchronized (peer) {
  peer->setTargetActions(actions);
  getDropTarget()->doSetDefaultActions(actions);
//        }
 }
 else
 {
  getDropTarget()->doSetDefaultActions(actions);
 }
}

/**
 * This method returns an <code>int</code> representing the
 * current actions this <code>DropTarget</code> will accept.
 * <P>
 * @return the current actions acceptable to this <code>DropTarget</code>
 */

/*protected*/ int DropTargetContext::getTargetActions() {
    DropTargetContextPeer* peer = getDropTargetContextPeer();
    return ((peer != NULL)
                    ? peer->getTargetActions()
                    : dropTarget->getDefaultActions()
    );
}

/**
 * This method signals that the drop is completed and
 * if it was successful or not.
 * <P>
 * @param success true for success, false if not
 * <P>
 * @throws InvalidDnDOperationException if a drop is not outstanding/extant
 */

/*public*/ void DropTargetContext::dropComplete(bool success) throw (InvalidDnDOperationException)
{
    DropTargetContextPeer* peer = getDropTargetContextPeer();
    if (peer != NULL) {
        peer->dropComplete(success);
    }
}

/**
 * accept the Drag.
 * <P>
 * @param dragOperation the supported action(s)
 */

/*protected*/ void DropTargetContext::acceptDrag(int dragOperation) {
    DropTargetContextPeer* peer = getDropTargetContextPeer();
    if (peer != NULL) {
        peer->acceptDrag(dragOperation);
    }
}

/**
 * reject the Drag.
 */

/*protected*/ void DropTargetContext::rejectDrag() {
    DropTargetContextPeer* peer = getDropTargetContextPeer();
    if (peer != NULL) {
        peer->rejectDrag();
    }
}

/**
 * called to signal that the drop is acceptable
 * using the specified operation.
 * must be called during DropTargetListener.drop method invocation.
 * <P>
 * @param dropOperation the supported action(s)
 */

/*protected*/ void DropTargetContext::acceptDrop(int dropOperation) {
    DropTargetContextPeer* peer = getDropTargetContextPeer();
    if (peer != NULL) {
        peer->acceptDrop(dropOperation);
    }
}

/**
 * called to signal that the drop is unacceptable.
 * must be called during DropTargetListener.drop method invocation.
 */

/*protected*/ void DropTargetContext::rejectDrop() {
    DropTargetContextPeer* peer = getDropTargetContextPeer();
    if (peer != NULL) {
        peer->rejectDrop();
    }
}

/**
 * get the available DataFlavors of the
 * <code>Transferable</code> operand of this operation.
 * <P>
 * @return a <code>DataFlavor[]</code> containing the
 * supported <code>DataFlavor</code>s of the
 * <code>Transferable</code> operand.
 */

/*protected*/ QVector<DataFlavor*>* DropTargetContext::getCurrentDataFlavors() {
    DropTargetContextPeer* peer = getDropTargetContextPeer();
    return peer != NULL ? peer->getTransferDataFlavors() : new QVector<DataFlavor*>();
}

/**
 * This method returns a the currently available DataFlavors
 * of the <code>Transferable</code> operand
 * as a <code>java.util.List</code>.
 * <P>
 * @return the currently available
 * DataFlavors as a <code>java.util.List</code>
 */

/*protected*/ QList<DataFlavor*> DropTargetContext::getCurrentDataFlavorsAsList() {
    return getCurrentDataFlavors()->toList();
}

/**
 * This method returns a <code>boolean</code>
 * indicating if the given <code>DataFlavor</code> is
 * supported by this <code>DropTargetContext</code>.
 * <P>
 * @param df the <code>DataFlavor</code>
 * <P>
 * @return if the <code>DataFlavor</code> specified is supported
 */

/*protected*/ bool DropTargetContext::isDataFlavorSupported(DataFlavor* df) {
    return getCurrentDataFlavorsAsList().contains(df);
}

/**
 * get the Transferable (proxy) operand of this operation
 * <P>
 * @throws InvalidDnDOperationException if a drag is not outstanding/extant
 * <P>
 * @return the <code>Transferable</code>
 */

/*protected*/ Transferable* DropTargetContext::getTransferable() throw (InvalidDnDOperationException)
{
 DropTargetContextPeer* peer = getDropTargetContextPeer();
 if (peer == NULL)
 {
  throw new InvalidDnDOperationException();
 }
 else
 {
  if (transferable == NULL)
  {
   Transferable* t = peer->getTransferable();
   bool isLocal = peer->isTransferableJVMLocal();
   /*synchronized (this)*/
   {
    if (transferable == NULL)
    {
     transferable = createTransferableProxy(t, isLocal);
    }
   }
  }
  return transferable;
 }
}

/**
 * Get the <code>DropTargetContextPeer</code>
 * <P>
 * @return the platform peer
 */

DropTargetContextPeer* DropTargetContext::getDropTargetContextPeer() {
    return dropTargetContextPeer;
}

/**
 * Creates a TransferableProxy to proxy for the specified
 * Transferable.
 *
 * @param t the <tt>Transferable</tt> to be proxied
 * @param local <tt>true</tt> if <tt>t</tt> represents
 *        the result of a local drag-n-drop operation.
 * @return the new <tt>TransferableProxy</tt> instance.
 */
/*protected*/ Transferable* DropTargetContext::createTransferableProxy(Transferable* /*t*/, bool /*local*/) {
 // TODO::   return new TransferableProxy(t, local);
    return NULL;
}

/****************************************************************************/

#if 0
/**
 * <code>TransferableProxy</code> is a helper inner class that implements
 * <code>Transferable</code> interface and serves as a proxy for another
 * <code>Transferable</code> object which represents data transfer for
 * a particular drag-n-drop operation.
 * <p>
 * The proxy forwards all requests to the encapsulated transferable
 * and automatically performs additional conversion on the data
 * returned by the encapsulated transferable in case of local transfer.
 */

/*protected*/ class TransferableProxy implements Transferable {

    /**
     * Constructs a <code>TransferableProxy</code> given
     * a specified <code>Transferable</code> object representing
     * data transfer for a particular drag-n-drop operation and
     * a <code>boolean</code> which indicates whether the
     * drag-n-drop operation is local (within the same JVM).
     * <p>
     * @param t the <code>Transferable</code> object
     * @param local <code>true</code>, if <code>t</code> represents
     *        the result of local drag-n-drop operation
     */
    TransferableProxy(Transferable t, boolean local) {
        proxy = new sun.awt.datatransfer.TransferableProxy(t, local);
        transferable = t;
        isLocal      = local;
    }

    /**
     * Returns an array of DataFlavor objects indicating the flavors
     * the data can be provided in by the encapsulated transferable.
     * <p>
     * @return an array of data flavors in which the data can be
     *         provided by the encapsulated transferable
     */
    /*public*/ DataFlavor[] getTransferDataFlavors() {
        return proxy.getTransferDataFlavors();
    }

    /**
     * Returns whether or not the specified data flavor is supported by
     * the encapsulated transferable.
     * @param flavor the requested flavor for the data
     * @return <code>true</code> if the data flavor is supported,
     *         <code>false</code> otherwise
     */
    /*public*/ boolean isDataFlavorSupported(DataFlavor flavor) {
        return proxy.isDataFlavorSupported(flavor);
    }

    /**
     * Returns an object which represents the data provided by
     * the encapsulated transferable for the requested data flavor.
     * <p>
     * In case of local transfer a serialized copy of the object
     * returned by the encapsulated transferable is provided when
     * the data is requested in application/x-java-serialized-object
     * data flavor.
     *
     * @param df the requested flavor for the data
     * @throws IOException if the data is no longer available
     *              in the requested flavor.
     * @throws UnsupportedFlavorException if the requested data flavor is
     *              not supported.
     */
    /*public*/ Object getTransferData(DataFlavor df)
        throws UnsupportedFlavorException, IOException
    {
        return proxy.getTransferData(df);
    }

    /*
     * fields
     */

    // We don't need to worry about client code changing the values of
    // these variables. Since TransferableProxy is a /*protected*/ class, only
    // subclasses of DropTargetContext can access it. And DropTargetContext
    // cannot be subclassed by client code because it does not have a
    // /*public*/ constructor.

    /**
     * The encapsulated <code>Transferable</code> object.
     */
    /*protected*/ Transferable  transferable;

    /**
     * A <code>boolean</code> indicating if the encapsulated
     * <code>Transferable</code> object represents the result
     * of local drag-n-drop operation (within the same JVM).
     */
    /*protected*/ boolean       isLocal;

    private sun.awt.datatransfer.TransferableProxy proxy;
}
#endif
/****************************************************************************/

