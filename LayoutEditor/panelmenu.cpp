#include "panelmenu.h"
#include "editor.h"
#include "exceptions.h"
#include "layouteditor.h"
//#include "Throttle/listthrottles.h"
#include "Roster/rosterframe.h"
#include "Throttle/throttlewindow.h"
#include "paneleditor.h"
#include "paneleditoraction.h"
#include "controlpaneleditoraction.h"
#include "layouteditoraction.h"
#include "loadxmluseraction.h"
#include "storexmluseraction.h"
#ifdef SCRIPTING_ENABLED
#include "runjythonscript.h"
#include "inputwindowaction.h"
#include "jythonwindow.h"
#endif
#include "automattableaction.h"
#include "filehistoryaction.h"
#include "switchboardeditoraction.h"

/**
 * Create the default "Panels" menu for use in a menubar.
 *
 * Also manages the Show Panel menu for all Editor panels.
 *
 * @author	Bob Jacobsen   Copyright 2003, 2004, 2010
 * @author  Dave Duchamp   Copyright 2007
 * @author  Pete Cressman   Copyright 2010
 * @version     $Revision: 22320 $
 */
//public class PanelMenu extends JMenu {
/**
 * The single PanelMenu must accessed using
 * {@link jmri.InstanceManager#getDefault(java.lang.Class)}.
 */
/*public*/ PanelMenu::PanelMenu(QWidget *parent) : QMenu(parent)
{
 log = new Logger("PanelMenu");
 setObjectName("PanelMenu");
 panelsSubMenu	= nullptr;
 noPanelsItem  = new QAction(tr("(No Panels Available)"), this);
 //thisMenu = nullptr;
 panelsList = new QList<Editor*>();
 actionGroup = new QActionGroup(this);
 this->setTitle(tr("Panels"));
 connect(this, SIGNAL(aboutToShow()), this, SLOT(menuSelected()));

 // new panel is a submenu
 //add(new jmri.jmrit.display.NewPanelAction());
 QMenu* newPanel = new QMenu(tr("New Panel..."));
 PanelEditorAction* panelEditorAction;
 ControlPanelEditorAction* controlPanelEditorAction;
 LayoutEditorAction* layoutEditorAction;
 SwitchboardEditorAction* switchboardEditorAction;
 newPanel->addAction(panelEditorAction = new PanelEditorAction(tr("Panel Editor"),parent));
 panelEditorAction->setCheckable(true);
 newPanel->addAction(controlPanelEditorAction = new ControlPanelEditorAction(tr("Control Panel Editor"),parent));
 controlPanelEditorAction->setCheckable(true);
 newPanel->addAction(layoutEditorAction = new LayoutEditorAction(tr("Layout Editor"),parent));
 layoutEditorAction->setCheckable(true);
 newPanel->addAction(switchboardEditorAction =new SwitchboardEditorAction(tr("Switchboard Editor"),parent));
 switchboardEditorAction->setCheckable(true);

 addMenu(newPanel);

 addAction(new LoadXmlUserAction(tr("Open Panels..."),parent));
 addAction(new StoreXmlUserAction(tr("Save Panels..."),parent));
 addAction(new FileHistoryAction(tr("Show History"),parent));
 addSeparator();

 panelsSubMenu = new QMenu(tr("Show Panel"),parent);
 // Add the 'No Panels' item to the sub-menu
 noPanelsItem = new QAction(tr("(No Panels Available)"),parent);
 noPanelsItem->setEnabled(false);
 panelsSubMenu->addAction(noPanelsItem);
 addMenu(panelsSubMenu);
 addSeparator();
#ifdef SCRIPTING_ENABLED
 addAction(new RunJythonScript(tr("Run Script..."),parent));
 addAction(new AutomatTableAction(tr("Thread Monitor"),parent));
 addAction(new JythonWindow(tr("Script Output"), parent));
 addAction(new InputWindowAction(tr("Script Input"),parent));
#endif
 connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(on_panelSelected(QAction*)));
}



/**
 * Utility routine for getting the number of panels in the Panels sub menu
 */
/*public*/ int PanelMenu::getNumberOfPanels() {return panelsList->size();}

/**
 * Delete a panel from Show Panel sub menu
 */
/*public*/ void PanelMenu::deletePanel (Editor* panel)
{
 if (log->isDebugEnabled()) log->debug("deletePanel");
 if (panelsList->size()==0) return;
 for (int i = 0; i<panelsList->size(); i++)
 {
  QObject* o = panelsList->at(i);
  if (o == panel)
  {
   // Editors that are their own TargetFrame dispose themselves
   if (panel != panel->getTargetFrame() )
   {
    panel->getTargetFrame()->close();
   }
   panelsList->removeAt(panelsList->indexOf(panel));
//   panelsSubMenu->removeItemAt(i);  // TODO:
   // If there are no panels on the list,
   // replace the 'No Panels' menu item
   if (panelsList->size()==0)
   {
    panelsSubMenu->addAction(noPanelsItem);
   }
   return;
  }
 }
}

/**
 * Add an Editor panel to Show Panels sub menu
 */
/*public*/ void PanelMenu::addEditorPanel(/*final*/ Editor* panel)
{
 // If this is the first panel, remove the 'No Panels' menu item
 if (panelsList->size()==0) {
        panelsSubMenu->removeAction(noPanelsItem);
    }
 if(!panelsList->contains(panel))
    panelsList->append(panel);
//    ActionListener a = new ActionListener() {
//            public void actionPerformed(ActionEvent e) {
//                if (panel instanceof LayoutEditor) {
//                    panel.setVisible(true);
//                    panel.repaint();
//                } else {
//                    panel.getTargetFrame().setVisible(true);
//                }
//                updateEditorPanel(panel);
//            }
//        };
//    JCheckBoxMenuItem r = new JCheckBoxMenuItem(panel.getTitle());
//    QAction* act;
//    QVariant var;
//    QString pName = panel->metaObject()->className();
//    if(pName == "ListThrottles")
//    {
//     ListThrottles* pt = (ListThrottles*)panel;
//     act = new QAction(pt->getTitle(), this);
//     var = VPtr<ListThrottles>::asQVariant(pt);
//    }
//    else
//    if(pName == "ThrottleWindow")
//    {
//     ThrottleWindow* pt = (ThrottleWindow*)panel;
//     act = new QAction(pt->getTitle(), this);
//     var = VPtr<ThrottleWindow>::asQVariant(pt);
//     emit newThrottleWindow();
//    }
//    else if(pName == "RosterFrame")
//    {
//     RosterFrame* pt = (RosterFrame*)panel;
//     act = new QAction(pt->getTitle(), this);
//     var = VPtr<RosterFrame>::asQVariant(pt);
//    }
//    else if(pName == "JmriJFrame")
//    {
//     JmriJFrame* pt = (JmriJFrame*)panel;
//     act = new QAction(pt->getTitle(), this);
//     var = VPtr<JmriJFrame>::asQVariant(pt);
//    }
//    else
//    {
//     act = new QAction(panel->getTitle(), this);
//     var = VPtr<Editor>::asQVariant(panel);
//    }

//    act->setCheckable(true);
//    act->setChecked(panel->isVisible());
//    actionGroup->addAction(act);
//    //var = VPtr<Editor>::asQVariant(panel);
//    act->setData(var);
//    r.addActionListener(a);
   PanelActionListener* a = new PanelActionListener(panel, this);
   QAction* r = new QAction(panel->getTitle(), this);
   r->setCheckable(true);
   connect(r, SIGNAL(toggled(bool)), a, SLOT(actionPerformed()));
   panelsSubMenu->addAction(r);
   updateEditorPanel (panel);
}

PanelActionListener::PanelActionListener(Editor *panel, PanelMenu* pm)
{
 this->panel = panel;
 this->pm = pm;
}
/*public*/ void PanelActionListener::actionPerformed(/*ActionEvent**/ /*e*/)
{
    //if (panel instanceof LayoutEditor) {
 if(qobject_cast<LayoutEditor*>(panel)!= nullptr)
 {
        panel->setVisible(true);
        panel->update();
    } else {
        panel->getTargetFrame()->setVisible(true);
    }
    pm->updateEditorPanel(panel);
}

void PanelMenu::on_panelSelected(QAction* act)
{
 Editor* panel = VPtr<Editor>::asPtr(act->data());
// if(!panel->isVisible() || panel->isMinimized())
// {
//  panel->showNormal();
//  panel->toFront();
// }
 panel->setWindowState((panel->windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
}

void PanelMenu::menuSelected()
{
 panelsSubMenu->clear();
 actionGroup= new QActionGroup(this);
 for(int i =0; i < panelsList->count(); i++)
 {
  Editor* panel = panelsList->at(i);
  QAction* act = new QAction(panel->windowTitle(), this);
  act->setCheckable(true);
  //act->setChecked(panel->isVisible() && !panel->isMinimized());
  act->setData(VPtr<Editor>::asQVariant(panelsList->at(i)));
  panelsSubMenu->addAction(act);
  actionGroup->addAction(act);
  if(qobject_cast<LayoutEditor*>(panel) != nullptr)
  {
   if (panel->isVisible()) act->setChecked(true);
       else act->setChecked(false);
  }
  else
  {
   if (panel->getTargetFrame()->isVisible()) act->setChecked(true);
    else act->setChecked(false);
   act->setText(panel->getTargetFrame()->windowTitle());
  }
 }
 connect(actionGroup, SIGNAL(triggered(QAction*)), this, SLOT(on_panelSelected(QAction*)));
}

/**
 * Update an Editor type panel in Show Panels sub menu
 */
/*public*/ void PanelMenu::updateEditorPanel (Editor* panel)
{
 if (panelsList->size()==0) return;
 for (int i = 0; i<panelsList->size(); i++)
 {
  QObject* o = panelsList->at(i);
  if (o == panel)
  {
#if 1
   //QAction* r = (JCheckBoxMenuItem)panelsSubMenu->getItem(i);
   //if (panel instanceof LayoutEditor)
   QObjectList ol = panelsSubMenu->children();
   if(ol.isEmpty()) return;
   log->debug(tr("panelsList has %1 entries; panelsSubMenu has %2 entries.").arg(panelsList->count()).arg(ol.count()));
   QAction* r = new QAction(this);
   if(qobject_cast<QAction*>(ol.at(0)) != nullptr)
   {
    r = qobject_cast<QAction*>(ol.at(0));
    if(qobject_cast<LayoutEditor*>(panel) != nullptr)
    {
     if (panel->isVisible()) r->setChecked(true);
         else r->setChecked(false);
    }
    else
    {
     if (panel->getTargetFrame()->isVisible()) r->setChecked(true);
      else r->setChecked(false);
    }
    return;
   }
#endif
  }
 }
}

/**
 * Rename an Editor type panel in Show Panels sub menu
 */
/*public*/ void PanelMenu::renameEditorPanel (Editor* panel)
{
#if 1
    if (panelsList->size()==0) return;
    for (int i = 0; i<panelsList->size(); i++) {
        Editor* o = panelsList->at(i);
        if (o == panel) {
            QAction* r = panelsSubMenu->actions().at(i);
            r->setText(panel->getTitle());
            return;
        }
    }
#endif
}

/**
 * Determine if named panel already exists
 * returns true if named panel already loaded
 */
/*public*/ bool PanelMenu::isPanelNameUsed (QString name)
{
 if (panelsList->size()==0) return false;
 for (int i = 0; i<panelsList->size(); i++)
 {
  try
  {
   JFrame* editor = panelsList->at(i);
   if (editor->windowTitle()==(name))
   {
     return true;
    }
   }
   catch(Exception e){
  }
 }
 return false;
}

/*public*/ Editor* PanelMenu::getEditorByName (QString name)
{
 if (panelsList->size()==0) return nullptr;
 for (int i = 0; (i<panelsList->size()); i++)
 {
  try
  {
   if(qobject_cast<Editor*>(panelsList->at(i)) != nullptr)
   {
    Editor* editor = panelsList->at(i);
    if (editor->getTargetFrame()->windowTitle()==(name))
    {
     return editor;
    }
   }
  }
  catch(Exception e)
  {
  }
 }
 return nullptr;
}

/*public*/ QList<Editor*>* PanelMenu::getEditorPanelList()
{
    return panelsList;
}

/*public*/ QList<LayoutEditor*>* PanelMenu::getLayoutEditorPanelList()
{
 QList<LayoutEditor*>* lePanelsList = new QList<LayoutEditor*>();
 for (int i = 0; (i<panelsList->size()); i++)
 {
//  try
//  {
  if(qobject_cast<LayoutEditor*>(panelsList->at(i)) != nullptr)
  {
   LayoutEditor* le = (LayoutEditor*)panelsList->at(i);
   lePanelsList->append(le);
  }
//  }
//  catch(Exception e)
//  {
//  }
 }
 return lePanelsList;
}
//static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(PanelMenu.class.getName());
//}

//void PanelMenu::updatePanelMenu(QMenu *menu )
//{
// QActionGroup* actGrp = new QActionGroup(this);
// for(int i=0; i < panelsList->count(); i++)
// {
//  Editor* panel = panelsList->at(i);
//  QString pName = panel->metaObject()->className();
//  QAction* act;
//  QVariant var;
//  if(pName == "ListThrottles")
//  {
//   ListThrottles* pt = (ListThrottles*)panel;
//   act = new QAction(pt->getTitle(), this);
//   var = VPtr<ListThrottles>::asQVariant(pt);
//  }
//  else
//  if(pName == "ThrottleWindow")
//  {
//   ThrottleWindow* pt = (ThrottleWindow*)panel;
//   act = new QAction(pt->getTitle(), this);
//   var = VPtr<ThrottleWindow>::asQVariant(pt);
//  }
//  else
//  if(pName == "RosterTable")
//  {
//   RosterFrame* pt = (RosterFrame*)panel;
//   act = new QAction(pt->getTitle(), this);
//   var = VPtr<RosterFrame>::asQVariant(pt);
//  }
//  else
//  if(pName == "JmriJFrame")
//  {
//   JmriJFrame* pt = (JmriJFrame*)panel;
//   act = new QAction(pt->getTitle(), this);
//   var = VPtr<JmriJFrame>::asQVariant(pt);
//  }
//  else if(pName == "RosterFrame")
//  {
//   JmriJFrame* pt = (JmriJFrame*)panel;
//   act = new QAction(pt->getTitle(), this);
//   var = VPtr<JmriJFrame>::asQVariant(pt);
//  }
//  else
//  {
//   act = new QAction(panel->getTitle(), this);
//   var = VPtr<Editor>::asQVariant(panel);
//  }
//  act->setCheckable(true);
//  act->setChecked(panel->isVisible());
//  actGrp->addAction(act);
//  act->setData(var);
////    r.addActionListener(a);
//  menu->addAction(act);
// }
// connect(actGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_panelSelected(QAction*)));
// //menu->show();
//}
