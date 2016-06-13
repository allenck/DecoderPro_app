#ifndef INTERNALFRAMEEVENT_H
#define INTERNALFRAMEEVENT_H

#include <QObject>

class JInternalFrame;
class InternalFrameEvent : public QObject
{
 Q_OBJECT
public:
 explicit InternalFrameEvent(QObject *parent = 0);
 enum IDS
 {
 /**
  * The first number in the range of IDs used for internal frame events.
  */
 INTERNAL_FRAME_FIRST        = 25549,

 /**
  * The last number in the range of IDs used for internal frame events.
  */
 INTERNAL_FRAME_LAST         = 25555,

 /**
  * The "window opened" event.  This event is delivered only
  * the first time the internal frame is made visible.
  *
  * @see JInternalFrame#show
  */
 INTERNAL_FRAME_OPENED       = INTERNAL_FRAME_FIRST,

 /**
  * The "window is closing" event. This event is delivered when
  * the user attempts to close the internal frame, such as by
  * clicking the internal frame's close button,
  * or when a program attempts to close the internal frame
  * by invoking the <code>setClosed</code> method.
  *
  * @see JInternalFrame#setDefaultCloseOperation
  * @see JInternalFrame#doDefaultCloseAction
  * @see JInternalFrame#setClosed
  */
 INTERNAL_FRAME_CLOSING      = 1 + INTERNAL_FRAME_FIRST,

 /**
  * The "window closed" event. This event is delivered after
  * the internal frame has been closed as the result of a call to
  * the <code>setClosed</code> or
  * <code>dispose</code> method.
  *
  * @see JInternalFrame#setClosed
  * @see JInternalFrame#dispose
  */
 INTERNAL_FRAME_CLOSED       = 2 + INTERNAL_FRAME_FIRST,

 /**
  * The "window iconified" event.
  * This event indicates that the internal frame
  * was shrunk down to a small icon.
  *
  * @see JInternalFrame#setIcon
  */
 INTERNAL_FRAME_ICONIFIED    = 3 + INTERNAL_FRAME_FIRST,

 /**
  * The "window deiconified" event type. This event indicates that the
  * internal frame has been restored to its normal size.
  *
  * @see JInternalFrame#setIcon
  */
 INTERNAL_FRAME_DEICONIFIED  = 4 + INTERNAL_FRAME_FIRST,

 /**
  * The "window activated" event type. This event indicates that keystrokes
  * and mouse clicks are directed towards this internal frame.
  *
  * @see JInternalFrame#show
  * @see JInternalFrame#setSelected
  */
 INTERNAL_FRAME_ACTIVATED    = 5 + INTERNAL_FRAME_FIRST,

 /**
  * The "window deactivated" event type. This event indicates that keystrokes
  * and mouse clicks are no longer directed to the internal frame.
  *
  * @see JInternalFrame#setSelected
  */
 INTERNAL_FRAME_DEACTIVATED  = 6 + INTERNAL_FRAME_FIRST
 };

 /*public*/ InternalFrameEvent(JInternalFrame* source, int id, QObject *parent = 0);
 /*public*/ QString paramString() ;
 /*public*/ QObject* getSource();
 /*public*/ int getID();
 /*public*/ JInternalFrame* getInternalFrame ();

signals:

public slots:
 private:
  QObject* source;
  int id;
};

#endif // INTERNALFRAMEEVENT_H
