#include "sprogpacketgenaction.h"
#include "sprogpacketgenframe.h"
#include "loggerfactory.h"

using namespace Sprog;

/**
 * Swing action to create and register a SprogPacketGenFrame object
 *
 * @author	Bob Jacobsen Copyright (C) 2001
  */
// /*public*/ class SprogPacketGenAction extends AbstractAction {


/*public*/ SprogPacketGenAction::SprogPacketGenAction(QString s, SprogSystemConnectionMemo* memo, QWidget* frame) : AbstractAction(s, frame)
{
    //super(s);
    _memo = memo;
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void SprogPacketGenAction::actionPerformed(/*ActionEvent e*/) {
    SprogPacketGenFrame* f = new SprogPacketGenFrame(_memo);
    try {
        f->initComponents();
    } catch (Exception* ex) {
        log->error("Exception: " + ex->getMessage());
    }
    f->setVisible(true);
}
/*private*/ /*final*/ /*static*/ Logger* SprogPacketGenAction::log = LoggerFactory::getLogger("SprogPacketGenAction");
