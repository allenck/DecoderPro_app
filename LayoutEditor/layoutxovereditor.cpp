#include "layoutxovereditor.h"
#include "loggerfactory.h"
#include "layouttrack.h"
#include "titledborder.h"
#include "borderfactory.h"
#include <QPushButton>
#include "layouteditor.h"
#include "layoutturnout.h"
#include "jmrijframe.h"

/**
 * MVC Editor component for LayoutXOver objects.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class LayoutXOverEditor extends LayoutTurnoutEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutXOverEditor::LayoutXOverEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTurnoutEditor(layoutEditor){
        //super(layoutEditor);
    }

    /**
     * Edit a XOver
     */
    //@Override
    /*public*/ void LayoutXOverEditor::editLayoutTrack(/*@Nonnull*/ LayoutTrack* layoutTrack) {
        log->trace(tr("LayoutXOverEditor.editLayoutTrack(%1) of a %2").arg(layoutTrack->getName()).arg(layoutTrack->metaObject()->className()));
        LayoutTurnoutEditor::editLayoutTrack(layoutTrack);
    }


    // not used by crossover
    //@Override
    /*protected*/ void LayoutXOverEditor::extendAddContinuingStateChoice(QWidget* contentPane) {
    }

    //@Override
    /*protected*/ void LayoutXOverEditor::extendBlockBCDSetup(QWidget* contentPane) {
        JPanel* panel21 = new JPanel();
        panel21->setLayout(new FlowLayout());
        TitledBorder* borderblk2 = BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black));
        borderblk2->setTitle(tr("Block") + " 2");  // NOI18N
        panel21->setBorder(borderblk2);
        LayoutEditor::setupComboBox(editLayoutTurnoutBlockBNameComboBox, false, true, true);
        editLayoutTurnoutBlockBNameComboBox->setToolTip(tr("Edit this Block name to change the block linked to the second connecting point."));  // NOI18N
        panel21->layout()->addWidget(editLayoutTurnoutBlockBNameComboBox);

        panel21->layout()->addWidget(editLayoutTurnoutBlockBButton = new QPushButton(tr("Create/Edit")));  // NOI18N
        //editLayoutTurnoutBlockBButton.addActionListener(this::editLayoutTurnoutEditBlockBPressed);
        connect(editLayoutTurnoutBlockBButton, &QPushButton::clicked, [=]{
         editLayoutTurnoutEditBlockBPressed();
        });
        editLayoutTurnoutBlockBButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.").arg("2"));  // NOI18N
        contentPane->layout()->addWidget(panel21);

        JPanel* panel22 = new JPanel();
        panel22->setLayout(new FlowLayout());
        TitledBorder* borderblk3 = BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black));
        borderblk3->setTitle(tr("Block") + " 3");  // NOI18N
        panel22->setBorder(borderblk3);
        LayoutEditor::setupComboBox(editLayoutTurnoutBlockCNameComboBox, false, true, true);
        editLayoutTurnoutBlockCNameComboBox->setToolTip(tr("Edit this Block name to change the block linked to third connecting point."));  // NOI18N
        panel22->layout()->addWidget(editLayoutTurnoutBlockCNameComboBox);
        panel22->layout()->addWidget(editLayoutTurnoutBlockCButton = new QPushButton(tr("Create/Edit")));  // NOI18N
        //editLayoutTurnoutBlockCButton.addActionListener(this::editLayoutTurnoutEditBlockCPressed);
        connect(editLayoutTurnoutBlockCButton, &QPushButton::clicked, [=]{
         editLayoutTurnoutEditBlockCPressed();
        });
        editLayoutTurnoutBlockCButton->setToolTip(tr("Click here to create/edit information for Block {0} shown above.", "3"));  // NOI18N
        contentPane->layout()->addWidget(panel22);

        JPanel* panel23 = new JPanel();
        panel23->setLayout(new FlowLayout());
        TitledBorder* borderblk4 = BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black));
        borderblk4->setTitle(tr("Block") + " 4");  // NOI18N
        panel23->setBorder(borderblk4);
        LayoutEditor::setupComboBox(editLayoutTurnoutBlockDNameComboBox, false, true, true);
        editLayoutTurnoutBlockDNameComboBox->setToolTip(tr("Edit this Block name to change the block linked to fourth connecting point."));  // NOI18N
        panel23->layout()->addWidget(editLayoutTurnoutBlockDNameComboBox);
        panel23->layout()->addWidget(editLayoutTurnoutBlockDButton = new QPushButton(tr("Create/Edit")));  // NOI18N
        //editLayoutTurnoutBlockDButton.addActionListener(this::editLayoutTurnoutEditBlockDPressed);
        connect(editLayoutTurnoutBlockDButton, &QPushButton::clicked, [=]{
         editLayoutTurnoutEditBlockDPressed();
        });
        editLayoutTurnoutBlockDButton->setToolTip(tr("Click here to create/edit information for Block {0} shown above.", "4"));  // NOI18N
        contentPane->layout()->addWidget(panel23);
    }

    //@Override
    /*protected*/ void LayoutXOverEditor::configureCheckBoxes(BlockManager* bm) {
        //editLayoutTurnoutBlockBNameComboBox.getEditor().setItem(bm.getBlock(layoutTurnout.getBlockBName()));
        editLayoutTurnoutBlockBNameComboBox->setCurrentIndex(editLayoutTurnoutBlockBNameComboBox->findText(layoutTurnout->getBlockBName()));
        //editLayoutTurnoutBlockCNameComboBox.getEditor().setItem(bm.getBlock(layoutTurnout.getBlockCName()));
          editLayoutTurnoutBlockCNameComboBox->setCurrentIndex(editLayoutTurnoutBlockCNameComboBox->findText(layoutTurnout->getBlockCName()));
        //editLayoutTurnoutBlockDNameComboBox.getEditor().setItem(bm.getBlock(layoutTurnout.getBlockDName()));
          editLayoutTurnoutBlockDNameComboBox->setCurrentIndex(editLayoutTurnoutBlockDNameComboBox->findText(layoutTurnout->getBlockDName()));
        editLayoutTurnoutBlockBNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlockB()));
        editLayoutTurnoutBlockCNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlockC()));
        editLayoutTurnoutBlockDNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlockD()));
    }

    // Set up for Edit
    //@Override
    /*protected*/ void LayoutXOverEditor::setUpForEdit() {
            editLayoutTurnoutFrame->setTitle(tr("EditXEdit Crossoverover"));
            editLayoutTurnoutHiddenCheckBox->setText(tr("Hide Crossover"));
    }

    //@Override
    /*protected*/ void LayoutXOverEditor::setUpContinuingSense() {}

    //@Override
    /*protected*/ void LayoutXOverEditor::donePressedSecondTurnoutName(QString newName) {
        // turnout has changed
        if (layoutEditor->validatePhysicalTurnout(
                newName, editLayoutTurnoutFrame)) {
            layoutTurnout->setSecondTurnout(newName);
        } else {
            editLayoutTurnout2ndTurnoutCheckBox->setChecked(false);
            layoutTurnout->setSecondTurnout(nullptr);
            editLayoutTurnout2ndTurnoutComboBox->setSelectedItem(nullptr);
        }
        editLayoutTurnoutNeedRedraw = true;
    }

    // set the continuing route Turnout State
    //@Override
    /*protected*/ void LayoutXOverEditor::setContinuingRouteTurnoutState() {
        // this had content in LayoutTurnoutEditor superclass, which we don't want to do here.
    }

    //@Override
     /*protected*/ void LayoutXOverEditor::checkBlock234Changed() {
        QString newName;
        // check if Block 2 changed
        newName = editLayoutTurnoutBlockBNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getBlockBName() != (newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlockB(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if Block 3 changed
        newName = editLayoutTurnoutBlockCNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getBlockCName() != (newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlockC(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if Block 4 changed
        newName = editLayoutTurnoutBlockDNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutTurnout->getBlockDName() != (newName)) {
            // get new block, or null if block has been removed
            layoutTurnout->setLayoutBlockD(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* LayoutXOverEditor::log = LoggerFactory::getLogger("LayoutXOverEditor");
