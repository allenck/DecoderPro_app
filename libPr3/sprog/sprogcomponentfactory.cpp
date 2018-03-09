#include "sprogcomponentfactory.h"
#include "sprogmenu.h"
#include "sprogcsmenu.h"

using namespace Sprog;
/**
 * Provide access to Swing components for the Sprog subsystem.
 *
 * @author	Bob Jacobsen Copyright (C) 2010
 * @author	Paul Bender Copyright (C) 2010
 * @since 3.5.1
 */
///*public*/ class SprogComponentFactory extends jmri.jmrix.swing.ComponentFactory {

/*public*/ SprogComponentFactory::SprogComponentFactory(SprogSystemConnectionMemo* memo, QObject* parent) : ComponentFactory(parent)
{
    this->memo = memo;
}


/**
 * Provide a menu with all items attached to this system connection
 */
//@Override
/*public*/ QMenu* SprogComponentFactory::getMenu(QWidget* frame) {
    if (memo->getDisabled()) {
        return NULL;
    }
    if(memo->getSprogMode() == SprogConstants::SprogMode::SERVICE) {
        return new SPROGMenu(memo, frame);
    } else {  // must be command station mode.
        return new SPROGCSMenu(memo, frame);
    }
}
