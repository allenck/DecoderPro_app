#include "sprogslotmonaction.h"
#include "sprogslotmonframe.h"

using namespace Sprog;
/**
 * Swing action to create and register a SprogSlotMonFrame object.
 *
 * @author	Bob Jacobsen Copyright (C) 2001
 * @author      Andrew Crosland (C) 2006 ported to SPROG
 */
// /*public*/ class SprogSlotMonAction extends AbstractAction {


/*public*/ SprogSlotMonAction::SprogSlotMonAction(QString s, SprogSystemConnectionMemo* memo, QWidget* parent) : AbstractAction(s, parent) {
    //super(s);
    _memo = memo;
    connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

/*public*/ SprogSlotMonAction::SprogSlotMonAction(SprogSystemConnectionMemo* memo, QWidget* parent) : AbstractAction(tr("Sprog Slot Monitor"), parent){
    //this(Bundle.getMessage("SprogSlotMonitorTitle"), memo);
 _memo = memo;
connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void SprogSlotMonAction::actionPerformed(/*ActionEvent e*/) {

    if(_memo->getCommandStation() == NULL) {
       // create SlotManager if it doesn't exist
       _memo->configureCommandStation();
    }

    SprogSlotMonFrame* f = new SprogSlotMonFrame(_memo);
    f->setVisible(true);
}
