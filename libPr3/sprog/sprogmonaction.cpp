#include "sprogmonaction.h"
#include "loggerfactory.h"
#include "sprogmonframe.h"

using namespace Sprog;
/**
 * Swing action to create and register a SprogMonFrame object
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 */
///*public*/ class SprogMonAction extends AbstractAction {


/*public*/ SprogMonAction::SprogMonAction(QString s, SprogSystemConnectionMemo* memo, QWidget* frame) : AbstractAction(s, frame) {
    //super(s);
    this->_memo = memo;
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void SprogMonAction::actionPerformed() {
    // create a SprogMonFrame
    SprogMonFrame* f = new SprogMonFrame(_memo);
    try {
        f->initComponents();
    } catch (Exception* ex) {
        log->warn("SprogMonAction starting SprogMonFrame: Exception: " + ex->getMessage());
    }
    f->setVisible(true);
}

/*private*/ /*final*/ /*static*/ Logger* SprogMonAction::log = LoggerFactory::getLogger("SprogMonAction");


