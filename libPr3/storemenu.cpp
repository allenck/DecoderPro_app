#include "storemenu.h"
#include "storexmlconfigaction.h"
#include "storexmluseraction.h"
/**
 * Create a "Save" menu item containing actions for storing various data
 * (subsets).
 *
 * @author Bob Jacobsen Copyright 2005
 */
///*public*/ class StoreMenu extends JMenu {

    /*public*/ StoreMenu::StoreMenu(QString name) : QMenu(){
        //this();
        setTitle(name);
        addAction(new StoreXmlConfigAction(tr("Store Configuration Only To File...")));
        addAction(new StoreXmlUserAction(tr("Store Configuration And Panels To File...")));
    }

    /*public*/ StoreMenu::StoreMenu() : QMenu(){

        //super();

        setTitle(tr("Store"));

        addAction(new StoreXmlConfigAction(tr("Store Configuration Only To File...")));
        addAction(new StoreXmlUserAction(tr("Store Configuration And Panels To File...")));

    }
