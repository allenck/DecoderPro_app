#include "yardmasterbytrackaction.h"

using namespace Operations;
/**
 * Swing action open the yardmaster by track frame.
 *
 * @author Daniel Boudreau Copyright (C) 2015
 *
 */
//public class YardmasterByTrackAction extends AbstractAction {

/*public*/ YardmasterByTrackAction::YardmasterByTrackAction(QString s, Location* location, QObject* parent) :AbstractAction(s, parent)
{
    //super(s);
 common();
    _location = location;
}

/*public*/ YardmasterByTrackAction::YardmasterByTrackAction(QString s, QObject* parent) :AbstractAction(s, parent)
{
    //super(s);
 common();
}

/*public*/ YardmasterByTrackAction::YardmasterByTrackAction(QObject* parent) : AbstractAction(tr("Yardmaster By Track"), parent)
{
 //super(Bundle.getMessage("TitleYardmasterByTrack"));
 common();
}

/*public*/ YardmasterByTrackAction::YardmasterByTrackAction(Location* location, QObject* parent) : AbstractAction(tr("Yardmaster By Track"), parent){
    //super(Bundle.getMessage("TitleYardmasterByTrack"));
 common();
    _location = location;
}

void YardmasterByTrackAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void YardmasterByTrackAction::actionPerformed(JActionEvent* e) {
    // create a frame
    if (f == NULL || !f->isVisible()) {
        f = new YardmasterByTrackFrame(_location);
    }
//    f->setExtendedState(Frame::NORMAL);
    f->setVisible(true); // this also brings the frame into focus
}
