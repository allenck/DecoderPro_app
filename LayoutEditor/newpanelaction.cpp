#include "newpanelaction.h"
#include "layouteditoraction.h"
#include "paneleditoraction.h"
#include <QMessageBox>

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
//    this(Bundle.getMessage("MenuItemNew"));
//}
void NewPanelAction::common()
{
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void NewPanelAction::actionPerformed(ActionEvent* /*e*/)
{
 // allow user to choose a panel editor
// int response = JOptionPane.showOptionDialog(null,
//         Bundle.getMessage("ChoiceText1") + "\n" + Bundle.getMessage("ChoiceText2") + "\n"
//         + Bundle.getMessage("ChoiceText3"), Bundle.getMessage("ChooseEditor"),
//         JOptionPane.YES_NO_OPTION, JOptionPane.QUESTION_MESSAGE, null,
//         new Object[]{Bundle.getMessage("Cancel"), Bundle.getMessage("LayoutEditor"),
//             Bundle.getMessage("PanelEditor")},
//         Bundle.getMessage("PanelEditor"));
 QMessageBox* box = new
 QMessageBox(QMessageBox::Question, tr("Choose Editor"), tr("Please choose an editor for your new panel.") + "\n" + tr("Click 'Panel Editor' for the iconic PanelPro editor.") + "\n" + tr("Click 'Control Panel Editor' for another panel editor."));
 QPushButton* panelButton = box->addButton(tr("Panel Editor"),QMessageBox::AcceptRole);
 QPushButton* controlPanelButton = box->addButton(tr("Control Panel Editor"),QMessageBox::AcceptRole);
 box->addButton(QMessageBox::Cancel);
 box->exec();
 if(box->clickedButton() == (QAbstractButton*)panelButton)
 {
  LayoutEditorAction(this).actionPerformed(NULL);
 }
 else if (box->clickedButton() == (QAbstractButton*)controlPanelButton)
 {
  PanelEditorAction(this).actionPerformed(NULL);
 }
}
