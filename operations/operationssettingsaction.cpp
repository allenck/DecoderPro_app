#include "operationssettingsaction.h"

/**
 * Swing action to create and register a OperationsSetupFrame object.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2008
 */
// /*public*/ class OperationsSettingsAction extends AbstractAction {
namespace Operations
{
    /*public*/ OperationsSettingsAction::OperationsSettingsAction(QObject* parent) : AbstractAction(tr("Setup"), parent){
        //super(Bundle.getMessage("MenuSetup")); // NOI18N
  connect(this, &AbstractAction::triggered, [=]{actionPerformed();});
    }

    /*static*/ QPointer<OperationsSettingsFrame> OperationsSettingsAction::operationsSettingsFrame = nullptr;

    //@Override
    //@SuppressFBWarnings(value = "ST_WRITE_TO_STATIC_FROM_INSTANCE_METHOD", justification = "Only one OperationsSetupFrame")
    /*public*/ void OperationsSettingsAction::actionPerformed(JActionEvent* /*e*/) {
        // create a settings frame
        if (operationsSettingsFrame == nullptr || !operationsSettingsFrame->isVisible()) {
            operationsSettingsFrame = new OperationsSettingsFrame();
            operationsSettingsFrame->initComponents();
        }
        operationsSettingsFrame->setExtendedState(JFrame::NORMAL);
        operationsSettingsFrame->setVisible(true); // this also brings the frame into focus
    }
}
