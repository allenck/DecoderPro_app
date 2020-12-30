#include "switchboardeditoraction.h"
#include "instancemanager.h"
#include "panelmenu.h"
#include "switchboardeditor.h"

//SwitchboardEditorAction::SwitchboardEditorAction()
//{

//}
/**
 * Start a SwitchboardEditor.
 *
 * @author	Bob Jacobsen Copyright (C) 2002
 * @see jmri.jmrit.display.switchboardEditor.SwitchboardEditorAction
 */
// /*public*/ class SwitchboardEditorAction extends AbstractAction {

/*public*/ SwitchboardEditorAction::SwitchboardEditorAction(QString s, QObject* parent) : AbstractAction(s, parent) {
    //super(s);
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ SwitchboardEditorAction::SwitchboardEditorAction(QObject* parent) : AbstractAction(tr("New Switchboard"),parent) {
   // this("New Switchboard");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

} // NO I18N

//@Override
/*public*/ void SwitchboardEditorAction::actionPerformed(JActionEvent * /*e*/) {
    QString name = tr("Switchboard%1").arg("");
    for (int i = 2; i < 100; i++) {
        if (static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->isPanelNameUsed(name)) {
            name = tr("Switchboard%1").arg(" " + QString::number(i));
        }
    }
    SwitchboardEditor* frame = new SwitchboardEditor(name);
    static_cast<PanelMenu*>(InstanceManager::getDefault("PanelMenu"))->addEditorPanel(frame);
    frame->setLocation(570, 20); // position Editor

    frame->setWindowTitle(tr("Switchboard Editor"));
    frame->initView();

    frame->pack();
    frame->setVisible(true);
    frame->newPanelDefaults();
}

