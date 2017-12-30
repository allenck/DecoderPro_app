#include "nodechangeevent.h"
#include "preferences.h"

//NodeChangeEvent::NodeChangeEvent()
//{

//}
/**
 * An event emitted by a <tt>Preferences</tt> node to indicate that
 * a child of that node has been added or removed.<p>
 *
 * Note, that although NodeChangeEvent inherits Serializable interface from
 * java.util.EventObject, it is not intended to be Serializable. Appropriate
 * serialization methods are implemented to throw NotSerializableException.
 *
 * @author  Josh Bloch
 * @see     Preferences
 * @see     NodeChangeListener
 * @see     PreferenceChangeEvent
 * @since   1.4
 * @serial  exclude
 */

// /*public*/ class NodeChangeEvent extends java.util.EventObject {

/**
 * Constructs a new <code>NodeChangeEvent</code> instance.
 *
 * @param parent  The parent of the node that was added or removed.
 * @param child   The node that was added or removed.
 */
/*public*/ NodeChangeEvent::NodeChangeEvent(Preferences* parent, Preferences* child) : EventObject(parent)
{
    //super(parent);
    this->child = child;
}

/**
 * Returns the parent of the node that was added or removed.
 *
 * @return  The parent Preferences node whose child was added or removed
 */
/*public*/ Preferences* NodeChangeEvent::getParent() {
    return (Preferences*) getSource();
}

/**
 * Returns the node that was added or removed.
 *
 * @return  The node that was added or removed.
 */
/*public*/ Preferences* NodeChangeEvent::getChild() {
    return child;
}
#if 0
/**
 * Throws NotSerializableException, since NodeChangeEvent objects are not
 * intended to be serializable.
 */
 /*private*/ void writeObject(java.io.ObjectOutputStream out)
                                           throws NotSerializableException {
     throw new NotSerializableException("Not serializable.");
 }

/**
 * Throws NotSerializableException, since NodeChangeEvent objects are not
 * intended to be serializable.
 */
 /*private*/ void readObject(java.io.ObjectInputStream in)
                                           throws NotSerializableException {
     throw new NotSerializableException("Not serializable.");
 }
#endif
// Defined so that this class isn't flagged as a potential problem when
// searches for missing serialVersionUID fields are done.
/*private*/ /*static*/ /*final*/ long NodeChangeEvent::serialVersionUID = 8068949086596572957L;
