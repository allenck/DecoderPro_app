#include "controlpaneleditoraction.h"
#include "panelmenu.h"
#include "controlpaneleditor.h"
#include "instancemanager.h"

//ControlPanelEditorAction::ControlPanelEditorAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Start a ControlPanelEditor.
 *
 * @author	Bob Jacobsen Copyright (C) 2002
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.display.controlPanelEditor.ControlPanelEditorAction
 */
// /*public*/ class ControlPanelEditorAction extends AbstractAction {

/**
 *
 */
// private static final long serialVersionUID = 7670881366702521286L;

/*public*/ ControlPanelEditorAction::ControlPanelEditorAction(QString s, QObject *parent) :
  QAction(s, parent) {
    //super(s);
 common();
}

/*public*/ ControlPanelEditorAction::ControlPanelEditorAction(QObject *parent) :
  QAction(tr("New Panel"), parent) {
    //this("New Panel");
 common();
}
void ControlPanelEditorAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void ControlPanelEditorAction::actionPerformed(JActionEvent* /*e*/) {
 QString name = "Control Panel";
 for (int i = 2; i < 100; i++)
 {
  if (((PanelMenu*)InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name))
  {
      name = "Panel " + i;
  }
 }
 ControlPanelEditor* frame = new ControlPanelEditor(name);
 static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(frame);
 frame->setLocation(20, 20);

 frame->setTitle();
 frame->initView();

 frame->pack();
 frame->setVisible(true);
}
