#include "activesystemsmenu.h"
#include "instancemanager.h"
#include <QMenuBar>
#include "activeflag.h"
#include "loconetmenu.h"
#include "loconetsystemconnectionmemo.h"
#include "class.h"
#include "loggerfactory.h"
#include "componentfactory.h"
#include "class.h"

//ActiveSystemsMenu::ActiveSystemsMenu(QWidget *parent) :
//  QMenu(parent)
//{
//}
/**
 * Create a "Systems" menu containing as submenus the JMRI system-specific menus
 * for available systems.
 * <P>
 * Also provides a static member for adding these items to an existing menu.
 *
 * @see SystemsMenu
 *
 * @author	Bob Jacobsen Copyright 2003
 * @version $Revision: 29193 $
 */
//  /*public*/ class ActiveSystemsMenu extends JMenu {

/**
 *
 */
//private static final long serialVersionUID = -6929237793054146826L;

/*public*/ ActiveSystemsMenu::ActiveSystemsMenu(QString name, QWidget *parent) :
  QMenu(name, parent)
{
 //this();
 common();
 setTitle(name);

 addItems(this, parent);
}

/*public*/ ActiveSystemsMenu::ActiveSystemsMenu(QWidget *parent) :
  QMenu(tr("Systems"), parent)
{
    //super();
 common();
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrix.JmrixSystemsBundle");
 setTitle(tr("Systems"));

 addItems(this,parent);
}
void ActiveSystemsMenu::common()
{

}

/**
 * Add menus for active systems to the menu bar
 */
/*static*/ /*public*/ void ActiveSystemsMenu::addItems(QMenuBar* m, QWidget* frame)
{
 // get ComponentFactory objects and create menus
 QList<QObject*>* list = InstanceManager::getList("ComponentFactory");
  for (QObject* obj : *list)
  {
   ComponentFactory* memo = (ComponentFactory*)obj;
   QMenu* menu = memo->getMenu(frame);
   if (menu != NULL) {
       m->addMenu(menu);
   }
  }
 }

 /**
  * Add active systems as submenus inside a single menu entry.
  */
 /*static*/ /*public*/ void ActiveSystemsMenu::addItems(QMenu* m, QWidget* frame) {

     // get ComponentFactory objects and create menus
     QList<QObject*>* list
             = InstanceManager::getList("ComponentFactory");

     for (QObject* memo : *list) {
         QMenu* menu = ((ComponentFactory*)memo)->getMenu(frame);
         if (menu != NULL) {
             m->addMenu(menu);
         }
     }
 }

 /*static*/ QMenu* ActiveSystemsMenu::getMenu(QString className)
{
     try {
         return (QMenu*) Class::forName(className)->newInstance();
     }
 catch (ClassNotFoundException*  e) {
         log->error(tr("Could not load class %1").arg(className), e);
         return NULL;
     }
 catch ( InstantiationException*  e) {
         log->error(tr("Could not load class %1").arg(className), e);
         return NULL;
     }
 catch ( IllegalAccessException* e) {
         log->error(tr("Could not load class %1").arg(className), e);
         return NULL;
     }
 }

 /*private*/ /*final*/ /*static*/ Logger* ActiveSystemsMenu::log = LoggerFactory::getLogger("ActiveSystemsMenu");
