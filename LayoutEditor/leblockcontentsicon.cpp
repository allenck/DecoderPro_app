#include "leblockcontentsicon.h"
#include "loggerfactory.h"
#include "positionablepopuputil.h"
#include "transferhandler.h"
#include "editor.h"
#include "instancemanager.h"
#include "jtextfield.h"
#include "joptionpane.h"
#include "throttlemanager.h"
#include "dcclocoaddress.h"
#include "rosterentry.h"
#include "abstractaction.h"
#include "layoutblockmanager.h"
#include "path.h"

/**
 * An icon to display a status of a Block Object.
 * <p>
 * This is the same name as display.BlockContentsIcon, it follows
 * on from the MemoryIcon
 */
//@SuppressFBWarnings(value = "NM_SAME_SIMPLE_NAME_AS_SUPERCLASS")
// /*public*/ class BlockContentsIcon extends jmri.jmrit.display.BlockContentsIcon {

//TODO: unused - dead-code strip
//@SuppressFBWarnings(value = "SE_TRANSIENT_FIELD_NOT_RESTORED")
//private final transient String defaultText = " ";

/*public*/ LEBlockContentsIcon::LEBlockContentsIcon(QString s, LayoutEditor* panel, QObject* parent) :
 BlockContentsIcon(s, panel,parent)
{
    //super(s, panel);
    log->debug(tr("BlockContentsIcon ctor= %1").arg("jmri.jmrit.layouteditor.BlockContentsIcon"));
}


/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LEBlockContentsIcon::setBlock(NamedBeanHandle<Block*>* m) {
    BlockContentsIcon::setBlock(m);
    if (getBlock() != nullptr) {
        lBlock = ((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(getBlock());
    }
}

/**
 * add a roster to this icon
 * @param roster to add
 */
//@Override
/*protected*/ void LEBlockContentsIcon::addRosterToIcon(RosterEntry* roster) {
    if (!((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled() || lBlock == nullptr) {
        BlockContentsIcon::addRosterToIcon(roster);
        return;
    }

    int paths = lBlock->getNumberOfThroughPaths();
    Block* srcBlock = nullptr;
    Block* desBlock = nullptr;
    for (int i = 0; i < paths; i++) {
        if (lBlock->isThroughPathActive(i)) {
            srcBlock = lBlock->getThroughPathSource(i);
            desBlock = lBlock->getThroughPathDestination(i);
            break;
        }
    }
    int dirA;
    int dirB;
    if (srcBlock != nullptr && desBlock != nullptr) {
        dirA = lBlock->getNeighbourDirection(srcBlock);
        dirB = lBlock->getNeighbourDirection(desBlock);
    } else {
        dirA = Path::EAST;
        dirB = Path::WEST;
    }

    QVariantList options = QVariantList() <<"Facing " + Path::decodeDirection(dirB) <<
        "Facing " + Path::decodeDirection(dirA) <<
        "Do Not Add";
    int n = JOptionPane::showOptionDialog(this,
            "Would you like to assign loco "
            + roster->titleString() + " to this location",
            "Assign Loco",
            JOptionPane::YES_NO_CANCEL_OPTION,
            JOptionPane::QUESTION_MESSAGE,
            QIcon(),
            options,
            options[2]);
    if (n == 2) {
        return;
    }
    if (n == 0) {
        flipRosterIcon = true;
        getBlock()->setDirection(dirB);
    } else {
        flipRosterIcon = false;
        getBlock()->setDirection(dirA);
    }
    if (VPtr<RosterEntry>::asPtr(getBlock()->getValue()) == roster) {
        //No change in the loco but a change in direction facing might have occurred
        updateIconFromRosterVal(roster);
    } else {
        setValue(VPtr<RosterEntry>::asQVariant(roster));
    }
}



/*private*/ /*final*/ /*static*/ Logger* LEBlockContentsIcon::log = LoggerFactory::getLogger("BlockContentsIcon");
