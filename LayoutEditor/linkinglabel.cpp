#include "linkinglabel.h"
#include "jmrijframe.h"
#include "positionablepopuputil.h"
#include "namedicon.h"
#include "coordinateedit.h"
#include "loggerfactory.h"

LinkingLabel::LinkingLabel(QWidget *parent) : PositionableLabel((Positionable*)parent)
{

}
/**
 * LinkingLabel is a PositionableLabel that opens a link to another window or
 * URL when clicked
 *
 * @author Bob Jacobsen Copyright (c) 2013
 */
// /*public*/ class LinkingLabel extends PositionableLabel implements LinkingObject {

/*public*/ LinkingLabel::LinkingLabel(/*@Nonnull*/ QString s, /*@Nonnull*/ Editor* editor, /*@Nonnull */QString url, QWidget *parent)
 : PositionableLabel(s, editor, (Positionable*)parent)
{
    //super(s, editor);
    this->url = url;
    setPopupUtility(new PositionablePopupUtil(this, this));
}

/*public*/ LinkingLabel::LinkingLabel(NamedIcon* s, /*@Nonnull*/ Editor* editor, /*@Nonnull*/ QString url, QWidget *parent)
: PositionableLabel(s, editor,(Positionable*)parent)
{
    //super(s, editor);
    this->url = url;
    setPopupUtility(new PositionablePopupUtil(this, this));
}

//@Override
/*public*/ Positionable* LinkingLabel::deepClone() {
    PositionableLabel* pos;
    if (_icon) {
        NamedIcon* icon = new NamedIcon((NamedIcon*) getIcon());
        pos = new LinkingLabel(icon, _editor, url);
    } else {
        pos = new LinkingLabel(_unRotatedText, _editor, url);
    }
    return finishClone((LinkingLabel*)pos);
}

/*protected*/ Positionable* LinkingLabel::finishClone(LinkingLabel* pos) {
    return PositionableLabel::finishClone(pos);
}


//@Override
/*public*/ QString LinkingLabel::getURL() {
    return url;
}

//@Override
/*public*/ void LinkingLabel::setULRL(QString u) {
    url = u;
}

//@Override
/*public*/ bool LinkingLabel::setLinkMenu(QMenu* popup) {
    popup->addAction(CoordinateEdit::getLinkEditAction(this, tr("Edit Link"), (QObject*)parent));
    return true;
}

// overide where used - e.g. momentary
//    /*public*/ void doMousePressed(MouseEvent event) {}
//    /*public*/ void doMouseReleased(MouseEvent event) {}
//@Override
/*public*/ void LinkingLabel::doMouseClicked(QGraphicsSceneMouseEvent* event)
{
 log->debug("click to " + url);
 try
 {
  if (url.startsWith("frame:"))
  {
   // locate JmriJFrame and push to front
   QString frame = url.mid(6);
   /*final*/ JmriJFrame* jframe = JmriJFrame::getFrame(frame);
   if (jframe != nullptr) {  //ignore if jframe not found
//       java.awt.EventQueue.invokeLater(new Runnable() {
//           @Override
//           /*public*/ void run() {
               //if frame was minimized, restore
#if 0 // TODO:
               if (jframe->getExtendedState() == JFrame::ICONIFIED) {
                   jframe->setExtendedState(JFrame::NORMAL);
               }
#endif
               //bring the frame to the foreground
               jframe->toFront();
               jframe->update();
//           }
//       });
   } else {
       log->error("Frame '" + frame + "' not found, cannot link to it.");
   }
  } else if (url.length() > 0) {
//      ExternalLinkContentViewerUI.activateURL(new java.net.URL(url));
  }
 } catch (IOException /*| URISyntaxException*/ t) {
     log->error("Error handling link", t);
 }
 PositionableLabel::doMouseClicked(event);
}

/*private*/ /*final*/ /*static*/ Logger* LinkingLabel::log = LoggerFactory::getLogger("LinkingLabel");
