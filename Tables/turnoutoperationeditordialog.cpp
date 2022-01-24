#include "turnoutoperationeditordialog.h"
#include "turnoutoperation.h"
#include "propertychangeevent.h"
#include "turnoutoperationconfig.h"
#include "box.h"
#include "loggerfactory.h"
#include "jbutton.h"
#include "joptionpane.h"


/**
 * Display a TurnoutOperationConfig Dialog for the turnout.
 *
 * Code originally within TurnoutTableAction.
 *
 * @author Bob Jacobsen Copyright (C) 2003, 2004, 2007
 * @author Egbert Broerse Copyright (C) 2017
 * @author Steve Young Copyright (C) 2021
 */
///*public*/ class TurnoutOperationEditorDialog extends JDialog {

/*static*/ bool TurnoutOperationEditorDialog::editingOps = false;


/**
 * Pop up a TurnoutOperationConfig Dialog for the turnout.
 *
 * @param op TunoutOperation to edit.
 * @param t   turnout
 * @param box JComboBox that triggered the edit, currently unused.
 */
TurnoutOperationEditorDialog::TurnoutOperationEditorDialog( /*@Nonnull*/ TurnoutOperation* op, Turnout* t, JComboBox* box)
 : JDialog()
{
    //super();
    self = this;
    myOp = op;
    myTurnout = t;
    init();
}

/*private*/ void TurnoutOperationEditorDialog::init() {

    //myOp.addPropertyChangeListener(evt -> {
    connect(myOp, &TurnoutOperation::propertyChange, [=](PropertyChangeEvent* evt){
        if (evt->getPropertyName() == ("Deleted")) {
            setVisible(false);
        }
    });

    TurnoutOperationConfig* config = TurnoutOperationConfig::getConfigPanel(myOp);
    setTitle();
    log->debug("TurnoutOpsEditDialog title set");
    if (config != nullptr) {
        log->debug("OpsEditDialog opening");
        Box* outerBox = Box::createVerticalBox();
        outerBox->layout()->addWidget(config);
        Box* buttonBox = Box::createHorizontalBox();
        JButton* nameButton = new JButton(tr("Give name to this setting"));
//        nameButton.addActionListener(e -> {
        connect(nameButton, &JButton::clicked, [=]{
            QString newName = JOptionPane::showInputDialog(tr("New name for this parameter setting:"));
            if (newName != "" && !newName.isEmpty()) {
                if (!myOp->rename(newName)) {
                    JOptionPane::showMessageDialog(self, tr("This name is already in use\nPlease provide a different name"),
                            tr("Warning"), JOptionPane::ERROR_MESSAGE);
                }
                setTitle();
                myTurnout->setTurnoutOperation(nullptr);
                myTurnout->setTurnoutOperation(myOp); // no-op but updates display - have to <i>change</i> value
            }
        });
        JButton* okButton = new JButton(tr("OK"));
//        okButton.addActionListener(e -> {
        connect(okButton, &JButton::clicked, [=]{
            config->endConfigure();
            if (myOp->isNonce() && myOp->equivalentTo(myOp->getDefinitive())) {
                myTurnout->setTurnoutOperation(nullptr);
                myOp->dispose();
                myOp = nullptr;
            }
            self->setVisible(false);
//            editingOps.set(false);
        });
        JButton* cancelButton = new JButton(tr("Cancel"));
//        cancelButton.addActionListener(e -> {
        connect(cancelButton, &JButton::clicked, [=]{
            self->setVisible(false);
//            editingOps.set(false);
        });
        buttonBox->layout()->addWidget(Box::createHorizontalGlue());
        if (!myOp->isDefinitive()) {
            buttonBox->layout()->addWidget(nameButton);
        }
        buttonBox->layout()->addWidget(okButton);
        buttonBox->layout()->addWidget(cancelButton);
        outerBox->layout()->addWidget(buttonBox);
        getContentPane()->layout()->addWidget(outerBox);
//        this.addWindowListener(new java.awt.event.WindowAdapter() {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                editingOps.set(false);
//            }
//        });
//        addWindowListener(new TurnoutOperationEditorDialog(this));

    } else {
        log->error("Error opening Turnout automation edit pane");
    }
    pack();
}

/*private*/ void TurnoutOperationEditorDialog::setTitle() {
    QString title = tr("Turnout Operation") + " \"" + myOp->getName() + "\"";
    if (myOp->isNonce()) {
        title = tr("Turnout Operation for Turnout") + " " + myTurnout->getSystemName();
    }
    JDialog::setTitle(title);
}

/*private*/ /*final*/ /*static*/ Logger* TurnoutOperationEditorDialog::log = LoggerFactory::getLogger("TurnoutOperationEditorDialog");
