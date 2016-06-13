#include "droptargetevent.h"
#include "droptargetcontext.h"

//DropTargetEvent::DropTargetEvent(QObject *parent) :
//    DropEvent(parent)
//{
//}
/**
 * The <code>DropTargetEvent</code> is the base
 * class for both the <code>DropTargetDragEvent</code>
 * and the <code>DropTargetDropEvent</code>.
 * It encapsulates the current state of the Drag and
 * Drop operations, in particular the current
 * <code>DropTargetContext</code>.
 *
 * @since 1.2
 *
 */

// /*public*/ class DropTargetEvent extends java.util.EventObject {

//    private static final long serialVersionUID = 2821229066521922993L;

/**
 * Construct a <code>DropTargetEvent</code> object with
 * the specified <code>DropTargetContext</code>.
 * <P>
 * @param dtc The <code>DropTargetContext</code>
 * @throws NullPointerException if {@code dtc} equals {@code null}.
 * @see #getSource()
 * @see #getDropTargetContext()
 */

/*public*/ DropTargetEvent::DropTargetEvent(DropTargetContext* dtc)
{
 //   super(dtc.getDropTarget());

 context  = dtc;
}

/**
 * This method returns the <code>DropTargetContext</code>
 * associated with this <code>DropTargetEvent</code>.
 * <P>
 * @return the <code>DropTargetContext</code>
 */

/*public*/ DropTargetContext* DropTargetEvent::getDropTargetContext() {
 return context;
}

/**
 * The <code>DropTargetContext</code> associated with this
 * <code>DropTargetEvent</code>.
 *
 * @serial
 */
