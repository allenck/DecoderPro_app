#include "sprogversionaction.h"
#include "loggerfactory.h"
#include "sprogversionframe.h"
using namespace Sprog;
/**
 * Swing action to get SPROG firmware version
 *
 * @author	Andrew Crosland Copyright (C) 2004
 */
///*public*/ class SprogVersionAction extends AbstractAction {


/*public*/ SprogVersionAction::SprogVersionAction(QString s,SprogSystemConnectionMemo* memo, QObject* parent) : AbstractAction(s, parent)
{
   // super(s);
    _memo = memo;
    connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void  SprogVersionAction::actionPerformed(/*ActionEvent* e*/) {
    // create a SprogVersionFrame
    SprogVersionFrame* f = new SprogVersionFrame(_memo);
    try {
        f->initComponents();
    } catch (Exception* ex) {
        log->warn("SprogIIUpdateAction starting SprogIIUpdateFrame: Exception: " + ex->getMessage());
    }
//        f.setVisible(true);
}

/*private*/ /*final*/ /*static*/ Logger* SprogVersionAction::log = LoggerFactory::getLogger("SprogVersionAction");
