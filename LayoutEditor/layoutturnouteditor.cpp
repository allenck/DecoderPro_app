#include "layoutturnouteditor.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include "layouttrack.h"
#include "jmrijframe.h"
#include "layoutturnout.h"
#include "layouteditor.h"
#include "borderfactory.h"

/**
 * MVC Editor component for LayoutTurnout objects.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutTurnoutEditor extends LayoutTrackEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutTurnoutEditor::LayoutTurnoutEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTrackEditor(layoutEditor) {
        //super(layoutEditor);
    }

    /*===================*\
    | Edit Layout Turnout |
    \*===================*/
    // variables for Edit Layout Turnout pane

    /**
     * Edit a Layout Turnout.
     * Invoked for any of the subtypes, has conditional code for crossovers
     */
    //@Override
    /*public*/ void LayoutTurnoutEditor::editLayoutTrack(/*@Nonnull*/ LayoutTrackView* layoutTrackView) {
        log->trace(tr("LayoutTurnoutEditor.editLayoutTrack(%1) of a %2").arg(layoutTrackView->getName()).arg(layoutTrackView->metaObject()->className()));
        if ( qobject_cast<LayoutTurnoutView*>(layoutTrackView) ) {
         this->layoutTurnoutView = (LayoutTurnoutView*) layoutTrackView;
         this->layoutTurnout = this->layoutTurnoutView->getLayoutTurnout();
        } else {
            log->error(tr("editLayoutTrack called with wrong type %1").arg(layoutTurnout->getName()),  Exception("traceback"));
        }
        sensorList.clear();

        if (editLayoutTurnoutOpen) {
            editLayoutTurnoutFrame->setVisible(true);
        } else if (editLayoutTurnoutFrame == nullptr) { // Initialize if needed
            editLayoutTurnoutFrame = new JmriJFrameX(tr("Edit Turnout"), false, true);  // NOI18N

            editLayoutTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutTurnout", true);  // NOI18N
            editLayoutTurnoutFrame->setLocation(50, 30);
            JPanel* contentPane = editLayoutTurnoutFrame->getContentPane();
            contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));
            // setup turnout name
            JPanel* panel1 = new JPanel();
            panel1->setLayout(new FlowLayout());
            JLabel* turnoutNameLabel = new JLabel(tr("%1:").arg(tr("Turnout")));  // NOI18N
            panel1->layout()->addWidget(turnoutNameLabel);

            // add combobox to select turnout
            editLayoutTurnout1stTurnoutComboBox = new NamedBeanComboBox((TurnoutManager*)
                    InstanceManager::getDefault("TurnoutManager"));
            editLayoutTurnout1stTurnoutComboBox->setToolTip(tr("EditTurnoutToolTip"));
            LayoutEditor::setupComboBox(editLayoutTurnout1stTurnoutComboBox, false, true, false);
            turnoutNameLabel->setLabelFor(editLayoutTurnout1stTurnoutComboBox);

            panel1->layout()->addWidget(editLayoutTurnout1stTurnoutComboBox);
            contentPane->layout()->addWidget(panel1);

            JPanel* panel1a = new JPanel();
            panel1a->setLayout(new QVBoxLayout());//panel1a, BoxLayout.Y_AXIS));

            editLayoutTurnout2ndTurnoutComboBox = new NamedBeanComboBox(
                    (TurnoutManager*)InstanceManager::getDefault("TurnoutManager"));
            editLayoutTurnout2ndTurnoutComboBox->setToolTip(tr("Select a turnout, used turnouts are excluded from the list."));
            LayoutEditor::setupComboBox(editLayoutTurnout2ndTurnoutComboBox, false, true, false);

            //editLayoutTurnout2ndTurnoutCheckBox.addActionListener((ActionEvent e) -> {
            connect(editLayoutTurnout2ndTurnoutCheckBox, &QCheckBox::clicked, [=]{
                bool additionalEnabled = editLayoutTurnout2ndTurnoutCheckBox->isChecked();
                editLayoutTurnout2ndTurnoutLabel->setEnabled(additionalEnabled);
                editLayoutTurnout2ndTurnoutComboBox->setEnabled(additionalEnabled);
                editLayoutTurnout2ndTurnoutInvertCheckBox->setEnabled(additionalEnabled);
            });
            panel1a->layout()->addWidget(editLayoutTurnout2ndTurnoutCheckBox);
            contentPane->layout()->addWidget(panel1a);

            editLayoutTurnout2ndTurnoutLabel = new JLabel(tr("Supporting %1:").arg(tr("Turnout")));  // NOI18N
            editLayoutTurnout2ndTurnoutLabel->setEnabled(false);
            JPanel* panel1b = new JPanel(new FlowLayout());
            panel1b->layout()->addWidget(editLayoutTurnout2ndTurnoutLabel);
            editLayoutTurnout2ndTurnoutLabel->setLabelFor(editLayoutTurnout2ndTurnoutComboBox);
            panel1b->layout()->addWidget(editLayoutTurnout2ndTurnoutComboBox);
            //editLayoutTurnout2ndTurnoutInvertCheckBox.addActionListener((ActionEvent e) -> layoutTurnout.setSecondTurnoutInverted(editLayoutTurnout2ndTurnoutInvertCheckBox.isSelected()));
            connect(editLayoutTurnout2ndTurnoutInvertCheckBox, &QCheckBox::clicked, [=]
            {
             layoutTurnout->setSecondTurnoutInverted(editLayoutTurnout2ndTurnoutInvertCheckBox->isChecked());
            });
            editLayoutTurnout2ndTurnoutInvertCheckBox->setEnabled(false);
            panel1b->layout()->addWidget(editLayoutTurnout2ndTurnoutInvertCheckBox);
            contentPane->layout()->addWidget(panel1b);

            // add continuing state choice
            extendAddContinuingStateChoice(contentPane);

            JPanel* panel3a = new JPanel();
            panel3a->setLayout(new FlowLayout());
            editLayoutTurnoutHiddenCheckBox = new JCheckBox(tr("Hide Turnout"));  // NOI18N
            editLayoutTurnoutHiddenCheckBox->setToolTip(tr("Check to hide this track segment when not in edit mode."));  // NOI18N
            panel3a->layout()->addWidget(editLayoutTurnoutHiddenCheckBox);
            contentPane->layout()->addWidget(panel3a);

            TitledBorder* border = BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black));
            border->setTitle(tr("Block"));  // NOI18N
            // setup block name
            JPanel* panel2 = new JPanel();
            panel2->setLayout(new FlowLayout());
            panel2->setBorder(border);
            panel2->layout()->addWidget(editLayoutTurnoutBlockNameComboBox);
            LayoutEditor::setupComboBox(editLayoutTurnoutBlockNameComboBox, false, true, true);
            editLayoutTurnoutBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
            panel2->layout()->addWidget(editLayoutTurnoutBlockButton = new QPushButton(tr("Create/Edit")));  // NOI18N
            editLayoutTurnoutBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.").arg("")); // empty value for block 1  // NOI18N
            //editLayoutTurnoutBlockButton.addActionListener(this::editLayoutTurnoutEditBlockPressed);
            connect(editLayoutTurnoutBlockButton, &QPushButton::clicked, [=]{
             editLayoutTurnoutEditBlockPressed();
            });
            contentPane->layout()->addWidget(panel2);

            extendBlockBCDSetup(contentPane);

            // set up Edit Block, Done and Cancel buttons
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            // Edit Block

            ELT_editLayoutTurnoutCancelPressed* _editLayoutTurnoutCancelPressed = new ELT_editLayoutTurnoutCancelPressed(this);
            ELT_editLayoutTurnoutDonePressed* _editLayoutTurnoutDonePressed = new ELT_editLayoutTurnoutDonePressed(this);
            addDoneCancelButtons(panel5, editLayoutTurnoutFrame->getRootPane(),
                    _editLayoutTurnoutDonePressed, _editLayoutTurnoutCancelPressed);
            contentPane->layout()->addWidget(panel5);
        }

        setUpForEdit();

        editLayoutTurnoutHiddenCheckBox->setChecked(layoutTurnoutView->isHidden());

        QList<Turnout*> currentTurnouts = QList<Turnout*>();
        currentTurnouts.append(layoutTurnout->getTurnout());
        currentTurnouts.append(layoutTurnout->getSecondTurnout());

        editLayoutTurnout1stTurnoutComboBox->setSelectedItem(layoutTurnout->getTurnout());
#if 0
        editLayoutTurnout1stTurnoutComboBox->addPopupMenuListener(
                layoutEditor->newTurnoutComboBoxPopupMenuListener(editLayoutTurnout1stTurnoutComboBox, currentTurnouts));
#endif
        BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
#if 0
        editLayoutTurnoutBlockNameComboBox->getEditor().setItem(bm.getBlock(layoutTurnout.getBlockName()));
#endif
        editLayoutTurnoutBlockNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlock()));

        configureCheckBoxes(bm);

        bool enable2nd = !layoutTurnout->getSecondTurnoutName().isEmpty();
        editLayoutTurnout2ndTurnoutCheckBox->setChecked(enable2nd);
        editLayoutTurnout2ndTurnoutInvertCheckBox->setEnabled(enable2nd);
        editLayoutTurnout2ndTurnoutLabel->setEnabled(enable2nd);
        editLayoutTurnout2ndTurnoutComboBox->setEnabled(enable2nd);
        if (enable2nd) {
            editLayoutTurnout2ndTurnoutInvertCheckBox->setChecked(layoutTurnout->isSecondTurnoutInverted());
            editLayoutTurnout2ndTurnoutComboBox->setSelectedItem(layoutTurnout->getSecondTurnout());
        } else {
            editLayoutTurnout2ndTurnoutInvertCheckBox->setChecked(false);
            editLayoutTurnout2ndTurnoutComboBox->setSelectedItem(nullptr);
        }

        setUpContinuingSense();

        editLayoutTurnoutFrame->addWindowListener(new ELTWindowListener(this));
//        {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                editLayoutTurnoutCancelPressed(null);
//            }
//        });

        editLayoutTurnoutFrame->pack();
        editLayoutTurnoutFrame->setVisible(true);
        editLayoutTurnoutOpen = true;
        editLayoutTurnoutNeedsBlockUpdate = false;

        showSensorMessage();
    }


    // add continuing state choice
    /*protected*/ void LayoutTurnoutEditor::extendAddContinuingStateChoice(QWidget *contentPane) {
        JPanel* panel3 = new JPanel();
        panel3->setLayout(new FlowLayout());
        editLayoutTurnoutStateComboBox->clear();
        editLayoutTurnoutStateComboBox->addItem(InstanceManager::turnoutManagerInstance()->getClosedText());
        editLayoutTurnoutClosedIndex = 0;
        editLayoutTurnoutStateComboBox->addItem(InstanceManager::turnoutManagerInstance()->getThrownText());
        editLayoutTurnoutThrownIndex = 1;
        editLayoutTurnoutStateComboBox->setToolTip(tr("StateToolTip"));  // NOI18N
        JLabel* label3 = new JLabel(tr("Continuing Route Turnout State"));
        panel3->layout()->addWidget(label3);  // NOI18N
        label3->setLabelFor(editLayoutTurnoutStateComboBox);
        panel3->layout()->addWidget(editLayoutTurnoutStateComboBox);
        contentPane->layout()->addWidget(panel3);
    }

    // for extension in e.g. XOver Editor
    /*protected*/ void LayoutTurnoutEditor::extendBlockBCDSetup(QWidget *contentPane) {}

    /*protected*/ void LayoutTurnoutEditor::configureCheckBoxes(BlockManager* bm) {
        editLayoutTurnout2ndTurnoutCheckBox->setText(tr("Also Throw Turnout"));  // NOI18N
    }

    // Set up for Edit
    /*protected*/ void LayoutTurnoutEditor::setUpForEdit() {
        editLayoutTurnoutFrame->setTitle(tr("Edit Turnout"));
        editLayoutTurnoutHiddenCheckBox->setText(tr("Hide Turnout"));
    }

    /*protected*/ void LayoutTurnoutEditor::setUpContinuingSense() {
        if (layoutTurnout->getContinuingSense() == Turnout::CLOSED) {
            editLayoutTurnoutStateComboBox->setCurrentIndex(editLayoutTurnoutClosedIndex);
        } else {
            editLayoutTurnoutStateComboBox->setCurrentIndex(editLayoutTurnoutThrownIndex);
        }
    }

    /*private*/ void LayoutTurnoutEditor::editLayoutTurnoutEditBlockPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editLayoutTurnoutBlockNameComboBox->getSelectedItemDisplayName();
        if (newName == "") {
            newName = "";
        }
        if (layoutTurnout->getBlockName() != (newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if a block exists to edit
        if (layoutTurnout->getLayoutBlock() == nullptr) {
            JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                    tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }
        layoutTurnout->getLayoutBlock()->editLayoutBlock(editLayoutTurnoutFrame);
        editLayoutTurnoutNeedRedraw = true;
        layoutEditor->setDirty();
    }

    /*protected*/ void LayoutTurnoutEditor::editLayoutTurnoutEditBlockBPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editLayoutTurnoutBlockBNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getBlockBName() !=(newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlockB(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if a block exists to edit
        if (layoutTurnout->getLayoutBlockB() == nullptr) {
            JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                    tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }
        layoutTurnout->getLayoutBlockB()->editLayoutBlock(editLayoutTurnoutFrame);
        editLayoutTurnoutNeedRedraw = true;
        layoutEditor->setDirty();
    }

    /*protected*/ void LayoutTurnoutEditor::editLayoutTurnoutEditBlockCPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editLayoutTurnoutBlockCNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getBlockCName() != (newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlockC(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if a block exists to edit
        if (layoutTurnout->getLayoutBlockC() == nullptr) {
            JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                    tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }
        layoutTurnout->getLayoutBlockC()->editLayoutBlock(editLayoutTurnoutFrame);
        editLayoutTurnoutNeedRedraw = true;
        layoutEditor->setDirty();
    }

    /*protected*/ void LayoutTurnoutEditor::editLayoutTurnoutEditBlockDPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editLayoutTurnoutBlockDNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getBlockDName() != (newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlockD(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if a block exists to edit
        if (layoutTurnout->getLayoutBlockD() == nullptr) {
            JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                    tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }
        layoutTurnout->getLayoutBlockD()->editLayoutBlock(editLayoutTurnoutFrame);
        editLayoutTurnoutNeedRedraw = true;
        layoutEditor->setDirty();
    }

    /*private*/ void LayoutTurnoutEditor::editLayoutTurnoutDonePressed(/*ActionEvent a*/) {
        // check if Turnout changed
        QString newName = editLayoutTurnout1stTurnoutComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getTurnoutName() !=(newName)) {
            // turnout has changed
            if (layoutEditor->validatePhysicalTurnout(
                    newName, editLayoutTurnoutFrame)) {
                layoutTurnout->setTurnout(newName);
            } else {
                layoutTurnout->setTurnout(nullptr);
                editLayoutTurnout1stTurnoutComboBox->setSelectedItem(nullptr);
            }
            editLayoutTurnoutNeedRedraw = true;
        }

        if (editLayoutTurnout2ndTurnoutCheckBox->isChecked()) {
            newName = editLayoutTurnout2ndTurnoutComboBox->getSelectedItemDisplayName();
            if (newName.isNull()) {
                newName = "";
            }
            if (layoutTurnout->getSecondTurnoutName() != (newName)) {
                donePressedSecondTurnoutName(newName);
            }
        } else {
            layoutTurnout->setSecondTurnout(nullptr);
        }

        setContinuingRouteTurnoutState();

        // check if Block changed
        newName = editLayoutTurnoutBlockNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getBlockName() != (newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }

        checkBlock234Changed();

        // set hidden
        bool oldHidden = layoutTurnoutView->isHidden();
        layoutTurnout->setHidden(editLayoutTurnoutHiddenCheckBox->isChecked());
        if (oldHidden != layoutTurnoutView->isHidden()) {
            editLayoutTurnoutNeedRedraw = true;
        }
        editLayoutTurnoutOpen = false;
        editLayoutTurnoutFrame->setVisible(false);
        editLayoutTurnoutFrame->dispose();
        editLayoutTurnoutFrame = nullptr;
        if (editLayoutTurnoutNeedsBlockUpdate) {
            layoutTurnout->updateBlockInfo();
            layoutTurnout->reCheckBlockBoundary();
        }
        if (editLayoutTurnoutNeedRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLayoutTurnoutNeedRedraw = false;
        }
    }

    /*protected*/ void LayoutTurnoutEditor::donePressedSecondTurnoutName(QString newName) {
        layoutTurnout->setSecondTurnout(newName);
    }

    // set the continuing route Turnout State
    /*protected*/ void LayoutTurnoutEditor::setContinuingRouteTurnoutState() {
        log->info(tr("LayoutTurnoutEditor#setContinuingRouteTurnoutState should have been overridden in class %1 object %2").arg(this->metaObject()->className()).arg(this->objectName()));
        if ((layoutTurnout->getTurnoutType() == LayoutTurnout::TurnoutType::RH_TURNOUT)
                || (layoutTurnout->getTurnoutType() == LayoutTurnout::TurnoutType::LH_TURNOUT)
                || (layoutTurnout->getTurnoutType() == LayoutTurnout::TurnoutType::WYE_TURNOUT)) {
            layoutTurnout->setContinuingSense(Turnout::CLOSED);
            if (editLayoutTurnoutStateComboBox->currentIndex() == editLayoutTurnoutThrownIndex) {
                layoutTurnout->setContinuingSense(Turnout::THROWN);
            }
        }
    }

    /*protected*/ void LayoutTurnoutEditor::checkBlock234Changed() {}

    /*private*/ void LayoutTurnoutEditor::editLayoutTurnoutCancelPressed(/*ActionEvent* a*/) {
        editLayoutTurnoutOpen = false;
        editLayoutTurnoutFrame->setVisible(false);
        editLayoutTurnoutFrame->dispose();
        editLayoutTurnoutFrame = nullptr;
        if (editLayoutTurnoutNeedsBlockUpdate) {
            layoutTurnout->updateBlockInfo();
        }
        if (editLayoutTurnoutNeedRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLayoutTurnoutNeedRedraw = false;
        }
    }


    /*private*/ /*final*/ /*static*/ Logger* LayoutTurnoutEditor::log = LoggerFactory::getLogger("LayoutTurnoutEditor");
