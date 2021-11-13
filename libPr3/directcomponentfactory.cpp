#include "directcomponentfactory.h"
#include "directmenu.h"

/**
 * Provide access to Swing components for the Direct subsystem.
 *
 * @author Bob Jacobsen Copyright (C) 2010
 * @author Paul Bender Copyright (C) 2017
 * @since 4.9.6
 */
///*public*/ class DirectComponentFactory extends jmri.jmrix.swing.ComponentFactory {

    /*public*/ DirectComponentFactory::DirectComponentFactory(DirectSystemConnectionMemo* memo) : ComponentFactory()  {
        this->memo = memo;
    }


    /**
     * Provide a menu with all (in this case: no) items attached to this system connection.
     */
    //@Override
    /*public*/ QMenu* DirectComponentFactory::getMenu() {
        if (memo->getDisabled()) {
            return nullptr;
        }
        return new DirectMenu(memo);
    }

//}
