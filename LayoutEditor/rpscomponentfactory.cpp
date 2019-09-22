#include "rpscomponentfactory.h"
#include "rpssystemconnectionmemo.h"
#include "rpsmenu.h"

/**
 * Provide access to Swing components for the RPS subsystem.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Paul Bender Copyright (C) 2010
 * @since 2.11.1
 */
// /*public*/ class RpsComponentFactory extends jmri.jmrix.swing.ComponentFactory {

    /*public*/ RpsComponentFactory::RpsComponentFactory(RpsSystemConnectionMemo* memo) {
        this->memo = memo;
    }


    /**
     * Provide a menu with all items attached to this system connection.
     */
    //@Override
    /*public*/ QMenu* RpsComponentFactory::getMenu() {
        if (memo->getDisabled()) {
            return nullptr;
        }
        return new RpsMenu(memo);
    }
