#include "powermanagermenu.h"
#include <QButtonGroup>
#include "instancemanager.h"

//PowerManagerMenu::PowerManagerMenu(QWidget *parent) :
//    QMenu(parent)
//{
//}
/**
 * Create a menu for selecting the Power Manager to use
 *
 * @author	Bob Jacobsen   Copyright 2010
 * @version     $Revision: 17977 $
 * @since 2.9.5
 */
//abstract /*public*/ class PowerManagerMenu extends JMenu {

/**
 * Get the currently selected manager
 */
/*public*/ PowerManager* PowerManagerMenu::get() {
    return NULL;
}


/**
 * Create a PowerManager menu.
 */
/*public*/ PowerManagerMenu::PowerManagerMenu(QWidget *parent) :
    QMenu(parent)
{
    //super();
  items =  QList<QAction*>();

 //QButtonGroup* group = new QButtonGroup();

 // label this menu
 setTitle("Connection");

 // now add an item for each available manager
 QObjectList* managers = InstanceManager::getList("PowerManager");
 if (!managers->isEmpty())
 {
  foreach (QObject* obj, *managers)
  {
   PowerManager* mgr = (PowerManager*) obj;
   if (mgr != NULL)
   {
    QAction* item = new QAction(mgr->getUserName(),this);
    item->setCheckable(true);
    addAction(item);
//        group.add(item);
    items.append(item);
//        item.addActionListener(new java.awt.event.ActionListener(){
//            /*public*/ void actionPerformed(java.awt.event.ActionEvent e) {
//                choiceChanged();
//            }
//        });
   }
  }
 }
 setDefault();
}


void PowerManagerMenu::setDefault()
{
 // name of default
 PowerManager* manager = (PowerManager*)InstanceManager::getDefault("PowerManager");
 if (manager == NULL) return;
 QString defaultMgr = manager->getUserName();
 if (defaultMgr == NULL) return;

 foreach (QAction* item, items)
 {
  if (defaultMgr==(item->text()))
  {
   item->setChecked(true);
  }
 }
}

/*public*/ PowerManager* PowerManagerMenu::getManager()
{
 // start with default
 PowerManager* manager = (PowerManager*)InstanceManager::getDefault("PowerManager");
 if (manager == NULL) return NULL;
 QString name = manager->getUserName();

 // find active name
 foreach (QAction* item, items)
 {
  if (item->isChecked())
  {
   name = item->text();
   break;
  }
 }
 // find PowerManager and return
 QObjectList* managers = InstanceManager::getList("PowerManager");
 foreach (QObject* obj, *managers)
 {
  PowerManager* mgr = (PowerManager*) obj;
  if (name==(mgr->getUserName())) return mgr;
 }
 // should not happen
 return nullptr;
}
