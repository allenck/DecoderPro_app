#include "internalframeevent.h"
#include "jinternalframe.h"

InternalFrameEvent::InternalFrameEvent(QObject *parent) :
  QObject(parent)
{
}
/**
 * An <code>AWTEvent</code> that adds support for
 * <code>JInternalFrame</code> objects as the event source.  This class has the
 * same event types as <code>WindowEvent</code>,
 * although different IDs are used.
 * Help on handling internal frame events
 * is in
 * <a href="http://docs.oracle.com/javase/tutorial/uiswing/events/internalframelistener.html" target="_top">How to Write an Internal Frame Listener</a>,
 * a section in <em>The Java Tutorial</em>.
 * <p>
 * <strong>Warning:</strong>
 * Serialized objects of this class will not be compatible with
 * future Swing releases. The current serialization support is
 * appropriate for short term storage or RMI between applications running
 * the same version of Swing.  As of 1.4, support for long term storage
 * of all JavaBeans&trade;
 * has been added to the <code>java.beans</code> package.
 * Please see {@link java.beans.XMLEncoder}.
 *
 * @see java.awt.event.WindowEvent
 * @see java.awt.event.WindowListener
 * @see JInternalFrame
 * @see InternalFrameListener
 *
 * @author Thomas Ball
 */
///*public*/ class InternalFrameEvent extends AWTEvent {


/**
 * Constructs an <code>InternalFrameEvent</code> object.
 * @param source the <code>JInternalFrame</code> object that originated the event
 * @param id     an integer indicating the type of event
 */
/*public*/ InternalFrameEvent::InternalFrameEvent(JInternalFrame* source, int id, QObject *parent) :
  QObject(parent)  {
    //super(source, id);
}

/**
 * Returns a parameter string identifying this event.
 * This method is useful for event logging and for debugging.
 *
 * @return a string identifying the event and its attributes
 */
/*public*/ QString InternalFrameEvent::paramString() {
    QString typeStr;
    switch(id) {
      case INTERNAL_FRAME_OPENED:
          typeStr = "INTERNAL_FRAME_OPENED";
          break;
      case INTERNAL_FRAME_CLOSING:
          typeStr = "INTERNAL_FRAME_CLOSING";
          break;
      case INTERNAL_FRAME_CLOSED:
          typeStr = "INTERNAL_FRAME_CLOSED";
          break;
      case INTERNAL_FRAME_ICONIFIED:
          typeStr = "INTERNAL_FRAME_ICONIFIED";
          break;
      case INTERNAL_FRAME_DEICONIFIED:
          typeStr = "INTERNAL_FRAME_DEICONIFIED";
          break;
      case INTERNAL_FRAME_ACTIVATED:
          typeStr = "INTERNAL_FRAME_ACTIVATED";
          break;
      case INTERNAL_FRAME_DEACTIVATED:
          typeStr = "INTERNAL_FRAME_DEACTIVATED";
          break;
      default:
          typeStr = "unknown type";
    }
    return typeStr;
}


/**
 * Returns the originator of the event.
 *
 * @return the <code>JInternalFrame</code> object that originated the event
 * @since 1.3
 */

/*public*/ JInternalFrame* InternalFrameEvent::getInternalFrame ()
{
  //return (source instanceof JInternalFrame)? (JInternalFrame)source : null;
 if(qobject_cast<JInternalFrame*>(source) != NULL)
  return (JInternalFrame*)source;
 else
  return NULL;
}

/**
 * The object on which the Event initially occurred.
 *
 * @return   The object on which the Event initially occurred.
 */
/*public*/ QObject* InternalFrameEvent::getSource() {
    return source;
}
/**
 * Returns the event type.
 */
/*public*/ int InternalFrameEvent::getID() {
    return id;
}
