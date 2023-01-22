#include "levelxingeditor.h"
#include "joptionpane.h"
#include "layouteditorauxtools.h"
#include "levelxing.h"


/**
 * MVC Editor component for LevelXing objects.
 *
 * Note there might not be anything for this class to do;
 * LayoutTrackEditors has a comment saying that PositionablePoint
 * doesn't have an editor.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LevelXingEditor extends LayoutTurntableEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LevelXingEditor::LevelXingEditor(/*@Nonnull*/ LayoutEditor* layoutEditor)
     : LayoutTurntableEditor(layoutEditor)
    {
        //super(layoutEditor);
    }

    /*===============*\
    | Edit Level Xing |
    \*===============*/

    /**
     * Edit a Level Crossing.
     * @param levelXing the level crossing to edit.
     */
    /*public*/ void LevelXingEditor::editLayoutTrack(LevelXing* levelXing) {
        sensorList.clear();

        this->levelXing = levelXing;
        if (editLevelXingOpen) {
            editLevelXingFrame->setVisible(true);
        } else // Initialize if needed
        if (editLevelXingFrame == nullptr) {
            editLevelXingFrame = new JmriJFrameX(tr("Edit Crossing"), false, true);  // NOI18N
            editLevelXingFrame->addHelpMenu("package.jmri.jmrit.display.EditLevelXing", true);  // NOI18N
            editLevelXingFrame->setLocation(50, 30);
            QWidget* contentPane = editLevelXingFrame->getContentPane();
            contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

            JPanel* panel33 = new JPanel();
            panel33->setLayout(new FlowLayout());
            editLevelXingHiddenCheckBox->setToolTip(tr("Check to hide this track segment when not in edit mode."));  // NOI18N
            panel33->layout()->addWidget(editLevelXingHiddenCheckBox);
            contentPane->layout()->addWidget(panel33);

            // setup block AC name
            JPanel* panel1 = new JPanel();
            panel1->setLayout(new FlowLayout());
            JLabel* block1NameLabel = new JLabel(tr("Block %1").arg("AC"));  // NOI18N
            panel1->layout()->addWidget(block1NameLabel);
            block1NameLabel->setLabelFor(editLevelXingBlock1NameComboBox);
            panel1->layout()->addWidget(editLevelXingBlock1NameComboBox);
            editLevelXingBlock1NameComboBox->setObjectName("Block AC");
            LayoutEditor::setupComboBox(editLevelXingBlock1NameComboBox, false, true, true);
            editLevelXingBlock1NameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
            contentPane->layout()->addWidget(panel1);

            // setup block BD name
            JPanel* panel2 = new JPanel();
            panel2->setLayout(new FlowLayout());
            JLabel* block2NameLabel = new JLabel(tr("Block %1").arg("BD"));  // NOI18N
            panel2->layout()->addWidget(block2NameLabel);
            block2NameLabel->setLabelFor(editLevelXingBlock2NameComboBox);
            panel2->layout()->addWidget(editLevelXingBlock2NameComboBox);
            editLevelXingBlock2NameComboBox->setObjectName("Block BD");
            LayoutEditor::setupComboBox(editLevelXingBlock2NameComboBox, false, true, true);
            editLevelXingBlock2NameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
            contentPane->layout()->addWidget(panel2);

            // set up Edit 1 Block and Edit 2 Block buttons
            JPanel* panel4 = new JPanel();
            panel4->setLayout(new FlowLayout());
            // Edit 1 Block
            panel4->layout()->addWidget(editLevelXingBlock1Button = new QPushButton(tr("Create/Edit Block %1").arg("AC")));  // NOI18N
            //editLevelXingBlock1Button.addActionListener(this::editLevelXingBlockACPressed);
            connect(editLevelXingBlock1Button, &QPushButton::clicked, [=]{
             editLevelXingBlockACPressed();
            });
            editLevelXingBlock1Button->setToolTip(tr("Click here to create/edit information for Block {0} shown above.", "")); // empty value for block 1  // NOI18N
            // Edit 2 Block
            panel4->layout()->addWidget(editLevelXingBlock2Button = new QPushButton(tr("Create/Edit Block %1").arg("BD")));  // NOI18N
            //editLevelXingBlock2Button.addActionListener(this::editLevelXingBlockBDPressed);
            connect(editLevelXingBlock2Button, &QPushButton::clicked, [=]{
             editLevelXingBlockBDPressed();
            });
            editLevelXingBlock2Button->setToolTip(tr("Click here to create/edit information for Block %1 shown above.").arg("")); // empty value for block 1  // NOI18N
            contentPane->layout()->addWidget(panel4);

            // set up Done and Cancel buttons
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            LXEeditLevelXingDonePressed* _editLevelXingDonePressed = new LXEeditLevelXingDonePressed(this);
            LXEeditLevelXingCancelPressed* _editLevelXingCancelPressed = new LXEeditLevelXingCancelPressed(this);
            addDoneCancelButtons(panel5, editLevelXingFrame->getRootPane(),
                    _editLevelXingDonePressed, _editLevelXingCancelPressed);
            contentPane->layout()->addWidget(panel5);
        }

        editLevelXingHiddenCheckBox->setChecked(levelXingView->isHidden());

        // Set up for Edit
        BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
        //editLevelXingBlock1NameComboBox.getEditor().setItem(bm.getBlock(levelXing.getBlockNameAC()));
        editLevelXingBlock1NameComboBox->setCurrentIndex(editLevelXingBlock1NameComboBox->findText(levelXing->getBlockNameAC()));
        //editLevelXingBlock2NameComboBox.getEditor().setItem(bm.getBlock(levelXing.getBlockNameBD()));
        editLevelXingBlock2NameComboBox->setCurrentIndex(editLevelXingBlock1NameComboBox->findText(levelXing->getBlockNameBD()));
        editLevelXingBlock1NameComboBox->setEnabled(!hasNxSensorPairs(levelXing->getLayoutBlockAC()));  // NOI18N
        editLevelXingBlock2NameComboBox->setEnabled(!hasNxSensorPairs(levelXing->getLayoutBlockBD()));  // NOI18N
        editLevelXingFrame->addWindowListener(new ELXWindowListener(this));
//        {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                editLevelXingCancelPressed(null);
//            }
//        });
        editLevelXingFrame->pack();
        editLevelXingFrame->setVisible(true);
        editLevelXingOpen = true;
        editLevelXingNeedsBlockUpdate = false;

        showSensorMessage();
    }   // editLevelXing

    /*private*/ void LevelXingEditor::editLevelXingBlockACPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editLevelXingBlock1NameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (levelXing->getBlockNameAC()!=(newName)) {
            // get new block, or null if block has been removed
            levelXing->setLayoutBlockAC(layoutEditor->provideLayoutBlock(newName));
            editLevelXingNeedsRedraw = true;
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
            editLevelXingNeedsBlockUpdate = true;
        }
        // check if a block exists to edit
        if (levelXing->getLayoutBlockAC() == nullptr) {
            JOptionPane::showMessageDialog(editLevelXingFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                    tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }
        levelXing->getLayoutBlockAC()->editLayoutBlock(editLevelXingFrame);
        editLevelXingNeedsRedraw = true;
    }

    /*private*/ void LevelXingEditor::editLevelXingBlockBDPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editLevelXingBlock2NameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (levelXing->getBlockNameBD() != (newName)) {
            // get new block, or null if block has been removed
            levelXing->setLayoutBlockBD(layoutEditor->provideLayoutBlock(newName));
            editLevelXingNeedsRedraw = true;
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
            editLevelXingNeedsBlockUpdate = true;
        }
        // check if a block exists to edit
        if (levelXing->getLayoutBlockBD() == nullptr) {
            JOptionPane::showMessageDialog(editLevelXingFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                    tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }
        levelXing->getLayoutBlockBD()->editLayoutBlock(editLevelXingFrame);
        editLevelXingNeedsRedraw = true;
    }

    /*private*/ void LevelXingEditor::editLevelXingDonePressed(/*ActionEvent a*/) {
        // check if Blocks changed
        QString newName = editLevelXingBlock1NameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (levelXing->getBlockNameAC() != (newName)) {
            // get new block, or null if block has been removed
            levelXing->setLayoutBlockAC(layoutEditor->provideLayoutBlock(newName));
            editLevelXingNeedsRedraw = true;
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
            editLevelXingNeedsBlockUpdate = true;
        }
        newName = editLevelXingBlock2NameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (levelXing->getBlockNameBD()!=(newName)) {
            // get new block, or null if block has been removed
            levelXing->setLayoutBlockBD(layoutEditor->provideLayoutBlock(newName));
            editLevelXingNeedsRedraw = true;
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
            editLevelXingNeedsBlockUpdate = true;
        }

        // set hidden
        bool oldHidden = levelXingView->isHidden();
        levelXingView->setHidden(editLevelXingHiddenCheckBox->isChecked());
        if (oldHidden != levelXingView->isHidden()) {
            editLevelXingNeedsRedraw = true;
        }

        editLevelXingOpen = false;
        editLevelXingFrame->setVisible(false);
        editLevelXingFrame->dispose();
        editLevelXingFrame = nullptr;
        if (editLevelXingNeedsBlockUpdate) {
            levelXing->updateBlockInfo();
        }
        if (editLevelXingNeedsRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLevelXingNeedsRedraw = false;
        }
    }

    /*private*/ void LevelXingEditor::editLevelXingCancelPressed(/*ActionEvent a*/) {
        editLevelXingOpen = false;
        editLevelXingFrame->setVisible(false);
        editLevelXingFrame->dispose();
        editLevelXingFrame = nullptr;
        if (editLevelXingNeedsBlockUpdate) {
            levelXing->updateBlockInfo();
        }
        if (editLevelXingNeedsRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLevelXingNeedsRedraw = false;
        }
    }



    // /*private*/ final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LevelXingEditor.class);
