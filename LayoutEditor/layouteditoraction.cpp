#include "layouteditoraction.h"
#include "panelmenu.h"
#include "layouteditor.h"

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
 :  QAction(s, parent)
{
 //super(s);
 common();
}

/*public*/ LayoutEditorAction::LayoutEditorAction(QObject *parent) :
  QAction(tr("New Panel"),parent) {
    //this("New Panel");
 common();
}

void LayoutEditorAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void LayoutEditorAction::actionPerformed(ActionEvent* /*e*/)
{
 QString name = "My Layout";
 for (int i = 2; i < 100; i++)
 {
  if (PanelMenu::instance()->isPanelNameUsed(name)) {
      name = "My Layout " + i;
  }
 }
 LayoutEditor* panel = new LayoutEditor(name);
 panel->pack();
 panel->setVisible(true);
 panel->setAllEditable(true);
 panel->setCurrentPositionAndSize();
}
