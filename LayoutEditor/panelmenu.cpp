#include "panelmenu.h"
#include "editor.h"
#include "exceptions.h"
#include "layouteditor.h"
#include "Throttle/listthrottles.h"
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

/*static*/ /*private*/ PanelMenu*  PanelMenu::thisMenu = NULL;
//PanelMenu::PanelMenu(QObject *parent) :
//    Qmenu(parent)
//{
//}
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
 * The single PanelMenu must now be accessed via the instance() method
 */
/*private*/ PanelMenu::PanelMenu(QWidget *parent) : QMenu(parent)
{
 log = new Logger("PanelMenu");
 panelsSubMenu	= NULL;
 noPanelsItem  = new QAction(tr("(No Panels Available)"), this);
 thisMenu = NULL;
 panelsList = new QList<Editor*>();
 actionGroup = new QActionGroup(this);
 this->setTitle(tr("Panels"));

 // new panel is a submenu
 //add(new jmri.jmrit.display.NewPanelAction());
 QMenu* newPanel = new QMenu(tr("New Panel..."));

 newPanel->addAction(new PanelEditorAction(tr("Panel Editor"),parent));
 newPanel->addAction(new ControlPanelEditorAction(tr("Control Panel Editor"),parent));
 newPanel->addAction(new LayoutEditorAction(tr("Layout Editor"),parent));
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
 * Provide method to reference this panel menu
 */
/*static*/ /*public*/ PanelMenu* PanelMenu::instance() {
    if (thisMenu==NULL) thisMenu = new PanelMenu();
    return thisMenu;
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
    QAction* act;
    QVariant var;
    QString pName = panel->metaObject()->className();
    if(pName == "ListThrottles")
    {
     ListThrottles* pt = (ListThrottles*)panel;
     act = new QAction(pt->getTitle(), this);
     var = VPtr<ListThrottles>::asQVariant(pt);
    }
    else
    if(pName == "ThrottleWindow")
    {
     ThrottleWindow* pt = (ThrottleWindow*)panel;
     act = new QAction(pt->getTitle(), this);
     var = VPtr<ThrottleWindow>::asQVariant(pt);
     emit newThrottleWindow();
    }
    else if(pName == "RosterFrame")
    {
     RosterFrame* pt = (RosterFrame*)panel;
     act = new QAction(pt->getTitle(), this);
     var = VPtr<RosterFrame>::asQVariant(pt);
    }
    else if(pName == "JmriJFrame")
    {
     JmriJFrame* pt = (JmriJFrame*)panel;
     act = new QAction(pt->getTitle(), this);
     var = VPtr<JmriJFrame>::asQVariant(pt);
    }
    else
    {
     act = new QAction(panel->getTitle(), this);
     var = VPtr<Editor>::asQVariant(panel);
    }

    act->setCheckable(true);
    act->setChecked(panel->isVisible());
    actionGroup->addAction(act);
    //var = VPtr<Editor>::asQVariant(panel);
    act->setData(var);
//    r.addActionListener(a);
    panelsSubMenu->addAction(act);
    updateEditorPanel (panel);
}
void PanelMenu::on_panelSelected(QAction* act)
{
 Editor* panel = VPtr<Editor>::asPtr(act->data());
 if(!panel->isVisible() || panel->isMinimized())
 {
  panel->showNormal();
  panel->toFront();
 }
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
#if 0
//        JCheckBoxMenuItem r = (JCheckBoxMenuItem)panelsSubMenu->getItem(i);
   //if (panel instanceof LayoutEditor)
      QAction* r = new QAction()
   if(qobject_cast<LayoutEditor*>(panel) != NULL)
   {
    if (panel->isVisible()) r.setSelected(true);
        else r.setSelected(false);
   }
   else
   {
    if (panel->getTargetFrame().isVisible()) r.setSelected(true);
     else r.setSelected(false);
   }
   return;
#endif
  }
 }
}

/**
 * Rename an Editor type panel in Show Panels sub menu
 */
/*public*/ void PanelMenu::renameEditorPanel (Editor* /*panel*/)
{
#if 0
    if (panelsList.size()==0) return;
    for (int i = 0; i<panelsList.size(); i++) {
        Object o = panelsList.get(i);
        if (o == panel) {
            JCheckBoxMenuItem r = (JCheckBoxMenuItem)panelsSubMenu.getItem(i);
            r.setText(panel.getTitle());
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
 if (panelsList->size()==0) return NULL;
 for (int i = 0; (i<panelsList->size()); i++)
 {
  try
  {
   if(qobject_cast<Editor*>(panelsList->at(i)) != NULL)
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
 return NULL;
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
  if(qobject_cast<LayoutEditor*>(panelsList->at(i)) != NULL)
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

void PanelMenu::updatePanelMenu(QMenu *menu )
{
 QActionGroup* actGrp = new QActionGroup(this);
 for(int i=0; i < panelsList->count(); i++)
 {
  Editor* panel = panelsList->at(i);
  QString pName = panel->metaObject()->className();
  QAction* act;
  QVariant var;
  if(pName == "ListThrottles")
  {
   ListThrottles* pt = (ListThrottles*)panel;
   act = new QAction(pt->getTitle(), this);
   var = VPtr<ListThrottles>::asQVariant(pt);
  }
  else
  if(pName == "ThrottleWindow")
  {
   ThrottleWindow* pt = (ThrottleWindow*)panel;
   act = new QAction(pt->getTitle(), this);
   var = VPtr<ThrottleWindow>::asQVariant(pt);
  }
  else
  if(pName == "RosterTable")
  {
   RosterFrame* pt = (RosterFrame*)panel;
   act = new QAction(pt->getTitle(), this);
   var = VPtr<RosterFrame>::asQVariant(pt);
  }
  else
  if(pName == "JmriJFrame")
  {
   JmriJFrame* pt = (JmriJFrame*)panel;
   act = new QAction(pt->getTitle(), this);
   var = VPtr<JmriJFrame>::asQVariant(pt);
  }
  else if(pName == "RosterFrame")
  {
   JmriJFrame* pt = (JmriJFrame*)panel;
   act = new QAction(pt->getTitle(), this);
   var = VPtr<JmriJFrame>::asQVariant(pt);
  }
  else
  {
   act = new QAction(panel->getTitle(), this);
   var = VPtr<Editor>::asQVariant(panel);
  }
  act->setCheckable(true);
  act->setChecked(panel->isVisible());
  actGrp->addAction(act);
  act->setData(var);
//    r.addActionListener(a);
  menu->addAction(act);
 }
 connect(actGrp, SIGNAL(triggered(QAction*)), this, SLOT(on_panelSelected(QAction*)));
 //menu->show();
}
