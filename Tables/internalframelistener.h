#ifndef INTERNALFRAMELISTENER_H
#define INTERNALFRAMELISTENER_H

#include "eventlistener.h"
#include "internalframeevent.h"

/**
 * The listener interface for receiving internal frame events.
 * This class is functionally equivalent to the WindowListener class
 * in the AWT.
 * <p>
 * See <a href="http://docs.oracle.com/javase/tutorial/uiswing/events/internalframelistener.html">How to Write an Internal Frame Listener</a>
 * in <em>The Java Tutorial</em> for further documentation.
 *
 * @see java.awt.event.WindowListener
 *
 * @author Thomas Ball
 */
///*public*/ interface InternalFrameListener extends EventListener {
class InternalFrameListener : public EventListener
{
public:
/**
 * Invoked when a internal frame has been opened.
 * @see javax.swing.JInternalFrame#show
 */
/*public*/ virtual void internalFrameOpened(InternalFrameEvent* e);

/**
 * Invoked when an internal frame is in the process of being closed.
 * The close operation can be overridden at this point.
 * @see javax.swing.JInternalFrame#setDefaultCloseOperation
 */
/*public*/ virtual void internalFrameClosing(InternalFrameEvent* e);

/**
 * Invoked when an internal frame has been closed.
 * @see javax.swing.JInternalFrame#setClosed
 */
/*public*/ virtual void internalFrameClosed(InternalFrameEvent* e);

/**
 * Invoked when an internal frame is iconified.
 * @see javax.swing.JInternalFrame#setIcon
 */
/*public*/ virtual void internalFrameIconified(InternalFrameEvent* e);

/**
 * Invoked when an internal frame is de-iconified.
 * @see javax.swing.JInternalFrame#setIcon
 */
/*public*/ virtual void internalFrameDeiconified(InternalFrameEvent* e);

/**
 * Invoked when an internal frame is activated.
 * @see javax.swing.JInternalFrame#setSelected
 */
/*public*/ virtual void internalFrameActivated(InternalFrameEvent* e);

/**
 * Invoked when an internal frame is de-activated.
 * @see javax.swing.JInternalFrame#setSelected
 */
/*public*/ virtual void internalFrameDeactivated(InternalFrameEvent* e);

};
#endif // INTERNALFRAMELISTENER_H
