#ifndef DROPTARGETCONTEXTPEER_H
#define DROPTARGETCONTEXTPEER_H
#include <QObject>
#include "exceptions.h"
/**
 * <p>
 * This interface is exposed by the underlying window system platform to
 * enable control of platform DnD operations
 * </p>
 *
 * @since 1.2
 *
 */

class Transferable;
class DataFlavor;
class DropTarget;
/*public*/ /*interface*/class  DropTargetContextPeer : public QObject
{
 Q_OBJECT
public:

    /**
     * update the peer's notion of the Target's actions
     */

    virtual void setTargetActions(int /*actions*/) {}

    /**
     * get the current Target actions
     */

    virtual int getTargetActions() {return 0;}

    /**
     * get the DropTarget associated with this peer
     */

    virtual DropTarget* getDropTarget() {return NULL;}

    /**
     * get the (remote) DataFlavors from the peer
     */

    virtual QVector<DataFlavor*>* getTransferDataFlavors() {return NULL;}

    /**
     * get an input stream to the remote data
     */

    virtual Transferable* getTransferable() throw (InvalidDnDOperationException){return NULL;}

    /**
     * @return if the DragSource Transferable is in the same JVM as the Target
     */

    virtual bool isTransferableJVMLocal() {return false;}

    /**
     * accept the Drag
     */

    virtual void acceptDrag(int /*dragAction*/) {}

    /**
     * reject the Drag
     */

    virtual void rejectDrag() {}

    /**
     * accept the Drop
     */

    virtual void acceptDrop(int /*dropAction*/) {}

    /**
     * reject the Drop
     */

    virtual void rejectDrop(){}

    /**
     * signal complete
     */

    virtual void dropComplete(bool /*success*/) {}
};
#endif // DROPTARGETCONTEXTPEER_H
