#ifndef DROPTARGETCONTEXT_H
#define DROPTARGETCONTEXT_H

#include <QObject>
#include "exceptions.h"

class Transferable;
class Component;
class DataFlavor;
class DropTargetContextPeer;
class DropTarget;
class DropTargetContext : public QObject
{
    Q_OBJECT
public:
//    explicit DropTargetContext(QObject *parent = 0);
    DropTargetContext(DropTarget* dt);
    /*public*/ DropTarget* getDropTarget();
    /*public*/ Component* getComponent();
    /*public*/ void addNotify(DropTargetContextPeer* dtcp);
    /*public*/ void removeNotify();
    /*public*/ void dropComplete(bool success) /*throw (InvalidDnDOperationException)*/;
    DropTargetContextPeer* getDropTargetContextPeer();

signals:

public slots:
private:
    /*
     * fields
     */

    /**
     * The DropTarget associated with this DropTargetContext.
     *
     * @serial
     */
    /*private*/ DropTarget* dropTarget;

    /*private*/ /*transient*/ DropTargetContextPeer* dropTargetContextPeer;

    /*private*/ /*transient*/ Transferable* transferable;

protected:
    /*protected*/ void setTargetActions(int actions);
    /*protected*/ int getTargetActions();
    /*protected*/ void acceptDrag(int dragOperation);
    /*protected*/ void rejectDrag();

    /*protected*/ void acceptDrop(int dropOperation);
    /*protected*/ void rejectDrop();
    /*protected*/ QVector<DataFlavor*>* getCurrentDataFlavors();
    /*protected*/ QList<DataFlavor*> getCurrentDataFlavorsAsList();
    /*protected*/ bool isDataFlavorSupported(DataFlavor* df);
    /*protected*/ Transferable* getTransferable() /*throw (InvalidDnDOperationException)*/;
    /*protected*/ Transferable* createTransferableProxy(Transferable* t, bool local);

    friend class DropTarget;
    friend class DropTargetDropEvent;
};

#endif // DROPTARGETCONTEXT_H
