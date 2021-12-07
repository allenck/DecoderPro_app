#include "base.h"
#include <QString>
#include "malesocket.h"
#include "abstractmalesocket.h"

/**
 * The name of the property child count.
 * To get the number of children, use the method getChildCount().
 * This constant is used in calls to firePropertyChange().
 * The class fires a property change then a child is added or removed.
 * <p>
 * If children are removed, the field oldValue of the PropertyChange event
 * must be a List&lt;FemaleSocket&gt; with the FemaleSockets that are
 * removed from the list so that the listener can unregister itself as a
 * listener of this female socket.
 * <p>
 * If children are added, the field newValue of the PropertyChange event
 * must be a List&lt;FemaleSocket&gt; with the FemaleSockets that are
 * added to the list so that the listener can register itself as a
 * listener of this female socket.
 */
/*public*/ /*static*/ /*final*/QString Base::PROPERTY_CHILD_COUNT = "ChildCount";

/**
 * The name of the property child reorder.
 * The number of children has remained the same, but the order of children
 * has changed.
 * <p>
 * The field newValue of the PropertyChange event must be a
 * List&lt;FemaleSocket&gt; with the FemaleSockets that are reordered so
 * that the listener can update the tree.
 */
/*public*/ /*static*/ /*final*/ QString Base::PROPERTY_CHILD_REORDER = "ChildReorder";

/**
 * The socket has been connected.
 * This constant is used in calls to firePropertyChange().
 * The socket fires a property change when it is connected or disconnected.
 */
/*public*/ /*static*/ /*final*/ QString Base::PROPERTY_SOCKET_CONNECTED = "SocketConnected";

/**
 * The socket has been disconnected.
 * This constant is used in calls to firePropertyChange().
 * The socket fires a property change when it is connected or disconnected.
 */
/*public*/ /*static*/ /*final*/ QString Base::PROPERTY_SOCKET_DISCONNECTED = "SocketDisconnected";

/**
 * The last result of the expression has changed.
 * This constant is used in calls to firePropertyChange().
 */
/*public*/ /*static*/ /*final*/ QString Base::PROPERTY_LAST_RESULT_CHANGED = "LastResultChanged";

/**
 * Is the operation allowed on this child?
 * @param index the index of the child to do the operation on
 * @param oper the operation to do
 * @return true if operation is allowed, false otherwise
 */
/*public*/ /*default*/ bool Base::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
    if (qobject_cast<MaleSocket*>(this->self())) {
        return ((AbstractMaleSocket*)this->self())->getObject()->isSocketOperationAllowed(index, oper);
    }
    return false;
}

/**
 * Do an operation on a child
 * @param index the index of the child to do the operation on
 * @param oper the operation to do
 */
/*public*/ /*virtual*/ /*default*/ void Base::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
    if (qobject_cast<MaleSocket*>(this->self())) {
        ((AbstractMaleSocket*)this->self())->getObject()->doSocketOperation(index, oper);
    }
    // By default, do nothing if not a male socket
}
