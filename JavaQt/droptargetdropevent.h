#ifndef DROPTARGETDROPEVENT_H
#define DROPTARGETDROPEVENT_H
#include "droptargetevent.h"

class Transferable;
class DataFlavor;
class DropTargetContext;
class DropTargetDropEvent : public DropTargetEvent
{
    Q_OBJECT
public:
    //explicit DropTargetEvent(QObject *parent = 0);
    /*public*/ DropTargetDropEvent(DropTargetContext* dtc, QPoint cursorLocn, int dropAction, int srcActions, bool isLocal = false, QObject *parent = 0);
    /*public*/ QPoint getLocation();
    /*public*/ QVector<DataFlavor*>* getCurrentDataFlavors();
    /*public*/QList<DataFlavor*> getCurrentDataFlavorsAsList();
    /*public*/ bool isDataFlavorSupported(DataFlavor* df);
    /*public*/ int getSourceActions();
    /*public*/ int getDropAction();
    /*public*/ Transferable* getTransferable();
    /*public*/ void acceptDrop(int dropAction);
    /*public*/ void rejectDrop();
    /*public*/ void dropComplete(bool success);
    /*public*/ bool isLocalTransfer();
    /*public*/ void setDropEvent(QDropEvent *de);
signals:

public slots:
private:
    /**
     * The location of the drag cursor's hotspot in Component coordinates.
     *
     * @serial
     */
    /*private*/ QPoint               location;//   = zero;

    /**
     * The source drop actions.
     *
     * @serial
     */
    /*private*/ int                 actions;//    = DnDConstants.ACTION_NONE;

    /**
     * The user drop action.
     *
     * @serial
     */
    /*private*/ int                 dropAction;// = DnDConstants.ACTION_NONE;

    /**
     * <code>true</code> if the source is in the same JVM as the target.
     *
     * @serial
     */
    /*private*/ bool             isLocalTx;// = false;
    static /*final*/ /*private*/ QPoint  zero;//     = new Point(0,0);
    DropTargetContext* dtc;
    QDropEvent *de;
    friend class DropJLabel;
};

#endif // DROPTARGETDROPEVENT_H
