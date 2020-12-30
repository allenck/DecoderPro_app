#include "newpanelaction.h"
#include "layouteditoraction.h"
#include "paneleditoraction.h"
#include "joptionpane.h"
#include "controlpaneleditoraction.h"
#include "switchboardeditoraction.h"

NewPanelAction::NewPanelAction(QObject *parent) :
  AbstractAction(tr("New Panel..."),parent)
{
 common();
}
/**
 * Start a Panel Editor or a Layout Editor for a new Panel.
 * <P>
 * Uses the individual LayoutEditorAction or PanelEditorAction to start the
 * editors, to ensure consistent operation.
 *
 * @author	Dave Duchamp Copyright (C) 2007
 * @author	Bob Jacobsen Copyright (C) 2008
 * @version	$Revision: 28746 $
 */
///*public*/ class NewPanelAction extends AbstractAction {

/**
 *
 */
///*private*/ static final long serialVersionUID = -4195350738625521948L;

/*public*/ NewPanelAction::NewPanelAction(QString s,QObject *parent) :
  AbstractAction(s, parent) {
    //super(s);
 common();
}

///*public*/ NewPanelAction() {
//    this(tr("MenuItemNew"));
//}
void NewPanelAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void NewPanelAction::actionPerformed(JActionEvent* /*e*/)
{
 // allow user to choose a panel editor
 int response = JOptionPane::showOptionDialog(nullptr,
                 tr("Please choose an editor for your new panel:") + "\n" + tr("Click 'Panel Editor' for the iconic PanelPro editor.") + "\n"
                 + tr("Click 'Control Panel Editor' for another panel editor.") + "\n" + tr("Click 'Layout Editor' for the drawing editor.") + "\n"
                         + tr("Click 'Switchboard Editor' for a compact control panel."),
                 tr("ChooseEditor"),
                 JOptionPane::YES_NO_OPTION, JOptionPane::QUESTION_MESSAGE, QIcon(),
                  QVariantList{tr("SwitchboardEditor"), tr("LayoutEditor"),
                         tr("ControlPanelEditor"), tr("PanelEditor"),
                         tr("ButtonCancel")},
                 tr("PanelEditor")); // title
         if (response == 3) {
             PanelEditorAction(this).actionPerformed(nullptr);
         } else if (response == 2) {
              ControlPanelEditorAction(this).actionPerformed(nullptr);
         } else if (response == 1) {
              LayoutEditorAction(this).actionPerformed(nullptr);
         } else if (response == 0) {
              SwitchboardEditorAction(this).actionPerformed(nullptr);
         }}
