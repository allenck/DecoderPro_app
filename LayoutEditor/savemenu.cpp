#include "savemenu.h"
#include "storexmlconfigaction.h"
#include "storexmluseraction.h"

//SaveMenu::SaveMenu(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Create a "Save" menu item containing actions for storing
 * various data (subsets).
 *
 * @author	Bob Jacobsen   Copyright 2005
 * @version     $Revision: 17977 $
 */
///*public*/ class SaveMenu extends JMenu {
/*public*/ SaveMenu::SaveMenu(QString name, QWidget *parent) {
    //this();
    setTitle(name);
}

/*public*/ SaveMenu::SaveMenu(QWidget *parent) : QMenu(parent)
{
 //super();

 //    ResourceBundle rb = ResourceBundle.getBundle("jmri.configurexml.SaveMenuBundle");

 setTitle(tr("Store"));
 //add(new jmri.configurexml.StoreXmlConfigAction(rb.getString("MenuItemStoreConfig")));
 QAction* storeConfig = new QAction( tr("Store Configuration only to file ..."), this);
 StoreXmlConfigAction* storeXmlConfigAction = new StoreXmlConfigAction(tr("Store Configuration only to file ..."));
 connect(storeConfig, SIGNAL(triggered()), storeXmlConfigAction, SLOT(actionPerformed()));
 addAction(storeConfig);
//    add(new jmri.configurexml.StoreXmlUserAction(rb.getString("MenuItemStoreUser")));
 QAction* storeUser = new QAction("Store configuration and panels to file...",this);
 StoreXmlUserAction* storeXmlUserAction = new StoreXmlUserAction(tr("Store configuration and panels to file..."));
 connect(storeUser, SIGNAL(triggered()), storeXmlUserAction, SLOT(actionPerformed()));
 addAction(storeUser);

}
