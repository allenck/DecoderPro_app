#include "sprogmonframe.h"
#include "loggerfactory.h"
#include "sprogreply.h"

using namespace Sprog;

/**
 * Frame displaying (and logging) Sprog command messages
 *
 * @author Bob Jacobsen Copyright (C) 2001
 */
///*public*/ class SprogMonFrame extends jmri.jmrix.AbstractMonFrame implements SprogListener {


/*public*/ SprogMonFrame::SprogMonFrame(SprogSystemConnectionMemo* memo, QWidget* parent): AbstractMonFrame(parent) {
    //super();
    _memo = memo;
}

//@Override
/*protected*/ QString SprogMonFrame::title() {
    return tr("MonitorX %1").arg("SPROG");
}

//@Override
/*protected*/ void SprogMonFrame::init() {
    // connect to TrafficController
    _memo->getSprogTrafficController()->addSprogListener((SprogListener*)this);
}

//@Override
/*public*/ void SprogMonFrame::dispose() {
    _memo->getSprogTrafficController()->removeSprogListener((SprogListener*)this);
    AbstractMonFrame::dispose();
}

//@Override
/*public*/ /*synchronized*/ void SprogMonFrame::notifyMessage(SprogMessage* l) { // receive a message and log it
    nextLine("cmd: \"" + l->toString(_memo->getSprogTrafficController()->isSIIBootMode()) + "\"\n", "");

}

//@Override
/*public*/ /*synchronized*/ void SprogMonFrame::notifyReply(SprogReply* l) { // receive a reply and log it
    nextLine("rep: \"" + l->toString() + "\"\n", "");
    log->debug("reply heard");
}

/*private*/ /*final*/ /*static*/ Logger* SprogMonFrame::log = LoggerFactory::getLogger("SprogMonFrame");
