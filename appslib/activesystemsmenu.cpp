#include "activesystemsmenu.h"
#include "instancemanager.h"
#include <QMenuBar>
#include "activeflag.h"
#include "loconetmenu.h"
#include "loconetsystemconnectionmemo.h"
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

 addItems(this);
}

/*public*/ ActiveSystemsMenu::ActiveSystemsMenu(QWidget *parent) :
  QMenu(tr("Systems"), parent)
{
    //super();
 common();
//    ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrix.JmrixSystemsBundle");
 setTitle(tr("Systems"));

 addItems(this);
}
void ActiveSystemsMenu::common()
{

}

/**
 * Add menus for active systems to the menu bar
 */
/*static*/ /*public*/ void ActiveSystemsMenu::addItems(QMenuBar* m)
{
 // get ComponentFactory objects and create menus
// QList<ComponentFactory> list
//         = InstanceManager::getList(ComponentFactory.class);
// if (list != null) {
//     for (ComponentFactory memo : list) {
//         JMenu menu = memo.getMenu();
//         if (menu != null) {
//             m.add(menu);
//         }
//     }
// }
#if 0
 // the following is somewhat brute-force!
 if (jmri.jmrix.acela.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.acela.AcelaMenu"));
 }

 if (jmri.jmrix.bachrus.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.bachrus.SpeedoMenu"));
 }

 if (jmri.jmrix.cmri.serial.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.cmri.CMRIMenu"));
 }

 if (jmri.jmrix.easydcc.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.easydcc.EasyDCCMenu"));
 }

 /*        if (jmri.jmrix.dcc4pc.ActiveFlag.isActive())
  m.add(getMenu("jmri.jmrix.dcc4pc.Dcc4PcMenu"));*/
 if (jmri.jmrix.grapevine.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.grapevine.GrapevineMenu"));
 }

 if (jmri.jmrix.oaktree.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.oaktree.OakTreeMenu"));
 }

 if (jmri.jmrix.pricom.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.pricom.PricomMenu"));
 }

 if (jmri.jmrix.qsi.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.qsi.QSIMenu"));
 }

 if (jmri.jmrix.rps.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.rps.RpsMenu"));
 }

 if (jmri.jmrix.secsi.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.secsi.SecsiMenu"));
 }

 if (jmri.jmrix.sprog.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.sprog.SPROGMenu"));
 }

 if (jmri.jmrix.sprog.ActiveFlagCS.isActive()) {
     m.add(getMenu("jmri.jmrix.sprog.SPROGCSMenu"));
 }

 if (jmri.jmrix.srcp.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.srcp.SystemMenu"));
 }

 if (jmri.jmrix.tmcc.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.tmcc.TMCCMenu"));
 }

 /*        if (jmri.jmrix.wangrow.ActiveFlag.isActive())
  m.add(getMenu("jmri.jmrix.wangrow.WangrowMenu"));*/
 if (jmri.jmrix.xpa.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.xpa.XpaMenu"));
 }

 if (jmri.jmrix.direct.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.direct.DirectMenu"));
 }

 if (jmri.jmrix.maple.ActiveFlag.isActive()) {
     m.add(getMenu("jmri.jmrix.maple.MapleMenu"));
 }
#endif
 if(ActiveFlag::isActive())
 {
  m->addMenu(LocoNetMenu::instance((LocoNetSystemConnectionMemo*)InstanceManager::instance()->getDefault("LocoNetSystemConnectionMemo"),(QWidget*)m->parent()));
 }
}

/**
 * Add active systems as submenus inside a single menu entry. Only used in
 * JmriDemo, which has a huge number of menus
 */
/*static*/ /*public*/ void ActiveSystemsMenu::addItems(QMenu* /*m*/) {
    //ResourceBundle rb = ResourceBundle.getBundle("jmri.jmrix.JmrixSystemsBundle");
#if 0
    // the following is somewhat brute-force!
    if (jmri.jmrix.acela.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.acela.AcelaMenu"));
    }
    if (jmri.jmrix.bachrus.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.bachrus.SpeedoMenu"));
    }
    if (jmri.jmrix.cmri.serial.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.cmri.CMRIMenu"));
    }
    if (jmri.jmrix.easydcc.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.easydcc.EasyDCCMenu"));
    }
    if (jmri.jmrix.grapevine.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.grapevine.GrapevineMenu"));
    }
    if (jmri.jmrix.oaktree.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.oaktree.OakTreeMenu"));
    }
    if (jmri.jmrix.pricom.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.pricom.PricomMenu"));
    }
    if (jmri.jmrix.qsi.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.qsi.QSIMenu"));
    }
    if (jmri.jmrix.rps.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.rps.RpsMenu"));
    }
    if (jmri.jmrix.secsi.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.secsi.SecsiMenu"));
    }
    if (jmri.jmrix.sprog.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.sprog.SPROGMenu"));
    }
    if (jmri.jmrix.sprog.ActiveFlagCS.isActive()) {
        m.add(getMenu("jmri.jmrix.sprog.SPROGCSMenu"));
    }
    if (jmri.jmrix.srcp.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.srcp.SystemMenu"));
    }
    if (jmri.jmrix.tmcc.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.tmcc.TMCCMenu"));
    }
    /*if (jmri.jmrix.wangrow.ActiveFlag.isActive())
     m.add(getMenu("jmri.jmrix.wangrow.WangrowMenu"));*/
    if (jmri.jmrix.xpa.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.xpa.XpaMenu"));
    }

    m.add(new javax.swing.JSeparator());

    m.add(new javax.swing.JSeparator());

    if (jmri.jmrix.direct.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.direct.DirectMenu"));
    }

    if (jmri.jmrix.maple.ActiveFlag.isActive()) {
        m.add(getMenu("jmri.jmrix.maple.MapleMenu"));
    }
#endif
}

/*static*/ QMenu* ActiveSystemsMenu::getMenu(QString className)
{
#if 1
    try {
        return (QMenu*) Class::forName(className)->newInstance();
    } catch (Exception e) {
        Logger::error("Could not load class " + className, e.getMessage());
        return NULL;
    }
#endif
}
