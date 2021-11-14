#include "directmenu.h"

/**
 * Create a "Systems" menu containing the Jmri direct-drive-specific tools (none at present).
 *
 * @author Bob Jacobsen Copyright 2003
 */
// /*public*/ class DirectMenu : public QMenu {

    /*public*/ DirectMenu::DirectMenu(QString name, DirectSystemConnectionMemo* memo) {
        common(memo);
        setTitle(name);
    }

    /*public*/ DirectMenu::DirectMenu(DirectSystemConnectionMemo* memo) {
        //super();
       common(memo);
    }
    void DirectMenu::common(DirectSystemConnectionMemo *memo)
    {
        if (memo != nullptr) {
            setTitle(memo->getUserName());
        } else {
            setTitle(tr("DirectDrive"));
        }

        // no items
        if (memo != nullptr) {
            // do we have a TrafficController?
            setEnabled(false); // memo.getTrafficController() != null); // disable menu, no connection, no tools!
            addAction(new QAction(tr("MenuNoOptions"), this));
        }
    }

