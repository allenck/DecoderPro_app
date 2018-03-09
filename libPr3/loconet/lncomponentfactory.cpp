#include "lncomponentfactory.h"
#include "loconetmenu.h"
/**
 * Provide access to Swing components for the LocoNet subsystem.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @since 2.9.4
 */
///*public*/ class LnComponentFactory extends jmri.jmrix.swing.ComponentFactory {

/*public*/ LnComponentFactory::LnComponentFactory(LocoNetSystemConnectionMemo* memo) {
    this->memo = memo;
}

/**
 * Provide a menu with all items attached to this system connection.
 */
//@Override
/*public*/ QMenu* LnComponentFactory::getMenu(QWidget* frame) {
    if (memo->getDisabled()) {
        return NULL;
    }
    return new LocoNetMenu(memo,frame);
}
