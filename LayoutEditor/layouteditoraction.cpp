#include "layouteditoraction.h"
#include "panelmenu.h"
#include "layouteditor.h"
#include "editormanager.h"

//LayoutEditorAction::LayoutEditorAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Start a LayoutEditor.
 *
 * @author	Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.display.panelEditor.PanelEditorAction
 */
///*public*/ class LayoutEditorAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 8529340792792129330L;

/*public*/ LayoutEditorAction::LayoutEditorAction(QString s, QObject *parent)
 :  AbstractAction(s, parent)
{
 //super(s);
 common();
}

/*public*/ LayoutEditorAction::LayoutEditorAction(QObject *parent) :
  AbstractAction(tr("New Panel"),parent) {
    //this("New Panel");
 common();
}

void LayoutEditorAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void LayoutEditorAction::actionPerformed(JActionEvent * /*e*/)
{
 QString name = "My Layout";
 for (int i = 2; i < 100; i++)
 {
  if (static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name)) {
      name = "My Layout " + QString::number(i);
  }
 }
 LayoutEditor* panel = new LayoutEditor(name);
 panel->pack();
 panel->setVisible(true);
 panel->setAllEditable(true);
 panel->setCurrentPositionAndSize();
 ((EditorManager*)InstanceManager::getDefault("EditorManager"))->add(panel);
 ((EditorManager*)InstanceManager::getDefault("EditorManager"))->setChanged(true);
 static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(panel);
}
