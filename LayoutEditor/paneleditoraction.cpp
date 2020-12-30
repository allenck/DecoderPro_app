#include "paneleditoraction.h"
#include "panelmenu.h"
#include "paneleditor.h"
#include "instancemanager.h"

//PanelEditorAction::PanelEditorAction(QObject *parent) :
//  QAction(parent)
//{
//}
/**
 * Start a PanelEditor.
 *
 * @author	Bob Jacobsen Copyright (C) 2002
 * @version	$Revision: 28746 $
 * @see jmri.jmrit.display.panelEditor.PanelEditorAction
 */
// /*public*/ class PanelEditorAction extends AbstractAction {

/**
 *
 */
//private static final long serialVersionUID = 1057276169969379561L;

/*public*/ PanelEditorAction::PanelEditorAction(QString s, QObject *parent) :
    QAction(s, parent)
{
 //super(s);
 common();
}

/*public*/ PanelEditorAction::PanelEditorAction(QObject *parent) :
  QAction(tr("New Panel"), parent)
{
 //this("New Panel");
 common();
}
void PanelEditorAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void PanelEditorAction::actionPerformed(JActionEvent* /*e*/)
{
 QString name = "Panel";
 for (int i = 2; i < 100; i++)
 {
  if (static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name)) {
      name = "Panel " + i;
  }
 }
 PanelEditor* frame = new PanelEditor(name);
 static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(frame);
 frame->setLocation(20, 20);

 frame->setTitle();

 frame->pack();
 frame->setVisible(true);
}
