#include "layouttrackeditors.h"
#include "loggerfactory.h"
#include "layouttrack.h"
#include "positionablepoint.h"
#include "jmribeancombobox.h"
#include <QPushButton>
#include <QCheckBox>
#include "instancemanager.h"
#include "blockmanager.h"
#include "jtextfield.h"
#include "jmribeancombobox.h"
#include "blockmanager.h"
#include "mathutil.h"
#include "block.h"
#include <QMenu>
#include <QGridLayout>
#include "layoutslip.h"
#include "entryexitpairs.h"
#include "userpreferencesmanager.h"
#include "namedbean.h"
#include "layouteditor.h"
#include "joptionpane.h"
#include "layoutturnout.h"
#include "jtextfield.h"
#include <QGroupBox>
#include "levelxing.h"
#include "jtextfield.h"
#include "layoutturntable.h"

/**
 * Editors for all layout track objects (PositionablePoint, TrackSegment,
 * LayoutTurnout, LayoutSlip, LevelXing and LayoutTurntable)
 *
 * @author George Warner Copyright (c) 2017-2018
 */
///*public*/ class LayoutTrackEditors {


/**
 * constructor method
 */
/*public*/ LayoutTrackEditors::LayoutTrackEditors(/*@Non nullptr*/ LayoutEditor* layoutEditor, QObject* parent ) : QObject(parent){
    this->layoutEditor = layoutEditor;
 sensorList = QList<QString>();
 editTrackSegmentMainlineComboBox = new QComboBox();
 editTrackSegmentDashedComboBox = new QComboBox();
 editTrackSegmentHiddenCheckBox = new QCheckBox(tr("Hide Track"));  // NOI18N
 editTrackSegmentBlockNameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editTrackSegmentArcTextField = new JTextField(5);

 editLayoutTurnoutBlockNameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutBlockBNameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutBlockCNameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutBlockDNameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutStateComboBox = new QComboBox();
 editLayoutTurnoutHiddenCheckBox = new QCheckBox(tr("Hide Turnout"));  // NOI18N
 editLayoutTurnout2ndTurnoutCheckBox = new QCheckBox(tr("Use Two Physical Addresses"));  // NOI18N
 editLayoutTurnout2ndTurnoutInvertCheckBox = new QCheckBox(tr("SecondTurnoutInvert"));  // NOI18N

 editLayoutSlipHiddenBox = new QCheckBox(tr("Hide Slip"));
 editLayoutSlipBlockNameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editLevelXingBlock1NameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
     InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editLevelXingBlock2NameComboBox = new NamedBeanComboBox(static_cast<BlockManager*>(
     InstanceManager::getDefault("BlockManager")),  nullptr, NamedBean::DisplayOptions::DISPLAYNAME);
 editLevelXingHiddenCheckBox = new QCheckBox(tr("Hide Crossing"));  // NOI18N
 editLayoutTurntableRadiusTextField = new JTextField(8);
 editLayoutTurntableAngleTextField = new JTextField(8);

}

/*=================*\
| Edit Layout Track |
\*=================*/
//@InvokeOnGuiThread
/*protected*/ void LayoutTrackEditors::editLayoutTrack(/*@Non nullptr*/ LayoutTrack* layoutTrack) {
    sensorList.clear();

    if (qobject_cast<PositionablePoint*>(layoutTrack)) {
        // PositionablePoint's don't have an editor...
    }
    else if (qobject_cast<TrackSegment*>(layoutTrack)) {
        editTrackSegment((TrackSegment*) layoutTrack);
    }
    else // this has to be before LayoutTurnout
    if (qobject_cast<LayoutSlip*>(layoutTrack)) {
        editLayoutSlip((LayoutSlip*) layoutTrack);
    }
    else if (qobject_cast<LayoutTurnout*>(layoutTrack)) {
        editLayoutTurnout((LayoutTurnout*) layoutTrack);
    } else if (qobject_cast<LevelXing*>(layoutTrack)) {
        editLevelXing((LevelXing*) layoutTrack);
    } else if (qobject_cast<PositionablePoint*>(layoutTrack)) {
        editLayoutTurntable((LayoutTurntable*) layoutTrack);
    }
    else
    {
        log->error(tr("editLayoutTrack unknown LayoutTrack subclass:") + layoutTrack->metaObject()->className());  // NOI18N
    }
}


/**
 * Create a list of NX sensors that refer to the current layout block.
 * This is used to disable block selection in the edit dialog.
 * The list is built by {@link jmri.jmrit.entryexit.EntryExitPairs#layoutBlockSensors}.
 * @since 4.11.2
 * @param loBlk The current layout block.
 * @return true if sensors are affected.
 */
bool LayoutTrackEditors::hasNxSensorPairs(LayoutBlock* loBlk) {
    if (loBlk ==  nullptr) {
        return false;
    }
    QList<QString> blockSensors = static_cast<EntryExitPairs*>(InstanceManager::getDefault("EntryExitPairs"))
            ->layoutBlockSensors(loBlk);
    if (blockSensors.isEmpty()) {
        return false;
    }
    //sensorList.addAll(blockSensors);
    for(QString blockSensor : blockSensors)
     sensorList.append(blockSensor);
    return true;
}

/**
 * Display a message describing the reason for the block selection combo box being disabled.
 * An option is provided to hide the message.
 * Note: The PanelMenu class is being used to satisfy the showInfoMessage requirement
 * for a default manager type class.
 * @since 4.11.2
 */
//@InvokeOnGuiThread
void LayoutTrackEditors::showSensorMessage() {
    if (sensorList.isEmpty()) {
        return;
    }
    QString msg = tr("<html>Block selection is disabled because the current block is being used by Entry/Exit Pairs.<p>");  // NOI18N
    msg.append(tr("The Entry/Exit sensors are listed below."));  // NOI18N
    QString chkDup = "";
    //sensorList.sort( nullptr);
    qSort(sensorList.begin(), sensorList.end());
    for (QString sName : sensorList) {
        if (sName !=(chkDup)) {
            msg.append("<br>&nbsp;&nbsp;&nbsp; " + sName);  // NOI18N
        }
        chkDup = sName;
    }
    msg.append("<br>&nbsp;</html>");  // NOI18N
    static_cast<UserPreferencesManager*>(InstanceManager::getDefault("UserPreferencesManager"))->
        showInfoMessage(
            tr("Block Entry/Exit Sensor Notification"),  // NOI18N
            msg,
            "jmri.jmrit.display.PanelMenu",  // NOI18N
            "BlockSensorMessage");  // NOI18N
    return;
}

/*==================*\
| Edit Track Segment |
\*==================*/


/**
 * Edit a Track Segment.
 */
//@InvokeOnGuiThread
/*protected*/ void LayoutTrackEditors::editTrackSegment(/*@Non nullptr*/ TrackSegment* trackSegment) {
    this->trackSegment = trackSegment;
    sensorList.clear();

    if (editTrackSegmentOpen)
    {
     editTrackSegmentFrame->setVisible(true);
    }
    else if (editTrackSegmentFrame ==  nullptr)
    { // Initialize if needed
     editTrackSegmentFrame = new JmriJFrameX(tr("Edit Track Segment"), false, true); // key moved to DisplayBundle to be found by CircuitBuilder.java   // NOI18N
     editTrackSegmentFrame->addHelpMenu("package.jmri.jmrit.display.EditTrackSegment", true);  // NOI18N
     editTrackSegmentFrame->setLocation(50, 30);
     editTrackSegmentFrame->setMinimumSize(300, 400);
     QWidget* contentPane = editTrackSegmentFrame->getContentPane(true);
     //contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));

     // add dashed choice
     QWidget* panel31 = new QWidget();
     FlowLayout* panel31Layout;
     panel31->setLayout(panel31Layout = new FlowLayout());
     editTrackSegmentDashedComboBox->clear();
     editTrackSegmentDashedComboBox->addItem(tr("Solid"));  // NOI18N
     editTrackSegmentSolidIndex = 0;
     editTrackSegmentDashedComboBox->addItem(tr("Dashed"));  // NOI18N
     editTrackSegmentDashedIndex = 1;
     editTrackSegmentDashedComboBox->setToolTip(tr("Select style for track segment."));  // NOI18N
     panel31Layout->addWidget(new QLabel(tr("Style") + " : "));
     panel31Layout->addWidget(editTrackSegmentDashedComboBox);
     contentPane->layout()->addWidget(panel31);

     // add mainline choice
     QWidget* panel32 = new QWidget();
     FlowLayout* panel32Layout;
     panel32->setLayout(panel32Layout = new FlowLayout());
     editTrackSegmentMainlineComboBox->clear();
     editTrackSegmentMainlineComboBox->addItem(tr("Mainline Track"));  // NOI18N
     editTrackSegmentMainlineTrackIndex = 0;
     editTrackSegmentMainlineComboBox->addItem(tr("Side Track"));  // NOI18N
     editTrackSegmentSideTrackIndex = 1;
     editTrackSegmentMainlineComboBox->setToolTip(tr("Select whether track segment is part of a mainline, or is a side track."));  // NOI18N
     panel32Layout->addWidget(editTrackSegmentMainlineComboBox);
     contentPane->layout()->addWidget(panel32);

     // add hidden choice
     QWidget* panel33 = new QWidget();
     FlowLayout* panel33Layout;
     panel33->setLayout(panel33Layout = new FlowLayout());
     editTrackSegmentHiddenCheckBox->setToolTip(tr("Check to hide this track segment when not in edit mode."));  // NOI18N
     panel33Layout->addWidget(editTrackSegmentHiddenCheckBox);
     contentPane->layout()->addWidget(panel33);

     // setup block name
     QWidget* panel2 = new QWidget();
     FlowLayout* panel2Layout;
     panel2->setLayout(panel2Layout = new FlowLayout());
     QLabel* blockNameLabel = new QLabel(tr("Block Name:"));  // NOI18N
     panel2Layout->addWidget(blockNameLabel);
     LayoutEditor::setupComboBox(editTrackSegmentBlockNameComboBox, false, true, true);
     editTrackSegmentBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
     panel2Layout->addWidget(editTrackSegmentBlockNameComboBox);

     contentPane->layout()->addWidget(panel2);

     QWidget* panel20 = new QWidget();
     FlowLayout* panel20Layout;
     panel20->setLayout(panel20Layout = new FlowLayout());
     QLabel* arcLabel = new QLabel(tr("Set Arc Angle"));  // NOI18N
     panel20Layout->addWidget(arcLabel);
     panel20Layout->addWidget(editTrackSegmentArcTextField);
     editTrackSegmentArcTextField->setToolTip(tr("Set Arc Angle"));  // NOI18N
     contentPane->layout()->addWidget(panel20);

     // set up Edit Block, Done and Cancel buttons
     QWidget* panel5 = new QWidget();
     FlowLayout* panel5Layout;
     panel5->setLayout(panel5Layout = new FlowLayout());

     // Edit Block
     panel5Layout->addWidget(editTrackSegmentSegmentEditBlockButton = new QPushButton(tr("Create/Edit Block %1").arg("")));  // NOI18N
//        editTrackSegmentSegmentEditBlockButton.addActionListener((ActionEvent e) -> {
//            editTrackSegmentEditBlockPressed(e);
//        });
     connect(editTrackSegmentSegmentEditBlockButton, SIGNAL(clicked(bool)), this, SLOT(editTrackSegmentEditBlockPressed()));
     editTrackSegmentSegmentEditBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.").arg("")); // empty value for block 1  // NOI18N
     panel5Layout->addWidget(editTrackSegmentSegmentEditDoneButton = new QPushButton(tr("Done")));  // NOI18N
//        editTrackSegmentSegmentEditDoneButton.addActionListener((ActionEvent e) -> {
//            editTracksegmentDonePressed(e);
//        });
     editTrackSegmentSegmentEditDoneButton->setToolTip(tr("Click %1 to save the changes").arg(tr("Done")));  // NOI18N

     // make this button the default button (return or enter activates)
     // Note: We have to invoke this later because we don't currently have a root pane
//        SwingUtilities.invokeLater(() -> {
//            JRootPane rootPane = SwingUtilities.getRootPane(editTrackSegmentSegmentEditDoneButton);
//            rootPane.setDefaultButton(editTrackSegmentSegmentEditDoneButton);
//        });
     editTrackSegmentSegmentEditDoneButton->setDefault(true);


     // Cancel
     panel5Layout->addWidget(editTrackSegmentSegmentEditCancelButton = new QPushButton(tr("Cancel")));  // NOI18N
//        editTrackSegmentSegmentEditCancelButton.addActionListener((ActionEvent e) -> {
//            editTrackSegmentCancelPressed(e);
//        });
     connect(editTrackSegmentSegmentEditCancelButton, SIGNAL(clicked(bool)), this, SLOT(editTrackSegmentCancelPressed()));
     editTrackSegmentSegmentEditCancelButton->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));  // NOI18N
     contentPane->layout()->addWidget(panel5);
    }
    // Set up for Edit
    if (trackSegment->isMainline()) {
        editTrackSegmentMainlineComboBox->setCurrentIndex(editTrackSegmentMainlineTrackIndex);
    } else {
        editTrackSegmentMainlineComboBox->setCurrentIndex(editTrackSegmentSideTrackIndex);
    }
    if (trackSegment->isDashed()) {
        editTrackSegmentDashedComboBox->setCurrentIndex(editTrackSegmentDashedIndex);
    } else {
        editTrackSegmentDashedComboBox->setCurrentIndex(editTrackSegmentSolidIndex);
    }
    editTrackSegmentHiddenCheckBox->setChecked(trackSegment->isHidden());
    editTrackSegmentBlockNameComboBox->setSelectedItemByName(trackSegment->getBlockName());
    editTrackSegmentBlockNameComboBox->setEnabled(!hasNxSensorPairs(trackSegment->getLayoutBlock()));

    if (trackSegment->isArc() && trackSegment->isCircle()) {
        editTrackSegmentArcTextField->setText("" + QString::number(trackSegment->getAngle()));
        editTrackSegmentArcTextField->setEnabled(true);
    } else {
        editTrackSegmentArcTextField->setEnabled(false);
    }

//    editTrackSegmentFrame.addWindowListener(new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            editTrackSegmentCancelPressed( nullptr);
//        }
//    });
    editTrackSegmentFrame->addWindowListener(new EditTrackSegmentWindowListener(this));
    editTrackSegmentFrame->pack();
    editTrackSegmentFrame->setVisible(true);
    editTrackSegmentOpen = true;

    showSensorMessage();

}   // editTrackSegment

//@InvokeOnGuiThread
/*private*/ void LayoutTrackEditors::editTrackSegmentEditBlockPressed(/*ActionEvent a*/) {
    // check if a block name has been entered
    QString newName = editTrackSegmentBlockNameComboBox->getSelectedItemDisplayName();
    if ((trackSegment->getBlockName() ==  nullptr)
            || trackSegment->getBlockName() != (newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            trackSegment->setLayoutBlock( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            trackSegment->setLayoutBlock( nullptr);
        }
        editTrackSegmentNeedsRedraw = true;
         layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
        trackSegment->updateBlockInfo();
    }
    // check if a block exists to edit
    if (trackSegment->getLayoutBlock() ==  nullptr) {
        JOptionPane::showMessageDialog(editTrackSegmentFrame,
                tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),  // NOI18N
                tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
        return;
    }
    trackSegment->getLayoutBlock()->editLayoutBlock(editTrackSegmentFrame);
     layoutEditor->setDirty();
    editTrackSegmentNeedsRedraw = true;
}   // editTrackSegmentEditBlockPressed

//@InvokeOnGuiThread
/*private*/ void LayoutTrackEditors::editTracksegmentDonePressed(/*ActionEvent a*/) {
    // set dashed
    bool oldDashed = trackSegment->isDashed();
    trackSegment->setDashed(editTrackSegmentDashedComboBox->currentIndex() == editTrackSegmentDashedIndex);

    // set mainline
    bool oldMainline = trackSegment->isMainline();
    trackSegment->setMainline(editTrackSegmentMainlineComboBox->currentIndex() == editTrackSegmentMainlineTrackIndex);

    // set hidden
    bool oldHidden = trackSegment->isHidden();
    trackSegment->setHidden(editTrackSegmentHiddenCheckBox->isChecked());

    if (trackSegment->isArc()) {
        bool bok;
            double newAngle = (editTrackSegmentArcTextField->text().toDouble(&bok));
            trackSegment->setAngle(newAngle);
            editTrackSegmentNeedsRedraw = true;
        if(!bok) {
            editTrackSegmentArcTextField->setText("" + QString::number(trackSegment->getAngle()));
        }
    }
    // check if anything changed
    if ((oldDashed != trackSegment->isDashed())
            || (oldMainline != trackSegment->isMainline())
            || (oldHidden != trackSegment->isHidden())) {
        editTrackSegmentNeedsRedraw = true;
    }
    // check if Block changed
    QString newName = editTrackSegmentBlockNameComboBox->getSelectedItemDisplayName();
    if ((trackSegment->getBlockName() ==  nullptr)
            || trackSegment->getBlockName() != (newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            trackSegment->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            trackSegment->setLayoutBlock( nullptr);
        }
        editTrackSegmentNeedsRedraw = true;
         layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
        trackSegment->updateBlockInfo();
    }
    editTrackSegmentOpen = false;

    editTrackSegmentFrame->setVisible(false);
    editTrackSegmentFrame->dispose();
    editTrackSegmentFrame =  nullptr;

    if (editTrackSegmentNeedsRedraw) {
         layoutEditor->redrawPanel();
        editTrackSegmentNeedsRedraw = false;
    }
     layoutEditor->setDirty();
}   // editTracksegmentDonePressed

//@InvokeOnGuiThread
/*private*/ void LayoutTrackEditors::editTrackSegmentCancelPressed(/*ActionEvent a*/) {
    editTrackSegmentOpen = false;
    editTrackSegmentFrame->setVisible(false);
    editTrackSegmentFrame->dispose();
    editTrackSegmentFrame =  nullptr;
    if (editTrackSegmentNeedsRedraw) {
         layoutEditor->setDirty();
         layoutEditor->redrawPanel();
        editTrackSegmentNeedsRedraw = false;
    }
}

/*===================*\
| Edit Layout Turnout |
\*===================*/


/**
 * Edit a Layout Turnout
 */
/*protected*/ void LayoutTrackEditors::editLayoutTurnout(/*@Non nullptr*/ LayoutTurnout* layoutTurnout) {
    this->layoutTurnout = layoutTurnout;
#if 1
    sensorList.clear();

    if (editLayoutTurnoutOpen) {
        editLayoutTurnoutFrame->setVisible(true);
    } else if (editLayoutTurnoutFrame ==  nullptr) { // Initialize if needed
        editLayoutTurnoutFrame = new JmriJFrameX(tr("Edit Turnout"), false, true);  // NOI18N
        editLayoutTurnoutFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutTurnout", true);  // NOI18N
        editLayoutTurnoutFrame->setLocation(50, 30);
        QWidget* contentPane = editLayoutTurnoutFrame->getContentPane(true);
//        contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));
        // setup turnout name
        QWidget* panel1 = new QWidget();
        FlowLayout* panel1Layout;
        panel1->setLayout(panel1Layout =new FlowLayout());
        QLabel* turnoutNameLabel = new QLabel(tr("%1").arg(tr("Turnout")));  // NOI18N
        panel1Layout->addWidget(turnoutNameLabel);

        // add combobox to select turnout
        editLayoutTurnout1stTurnoutComboBox = new NamedBeanComboBox(
                InstanceManager::turnoutManagerInstance(),
                layoutTurnout->getTurnout(),
                NamedBean::DisplayOptions::DISPLAYNAME);
         layoutEditor->setupComboBox(editLayoutTurnout1stTurnoutComboBox, false, true, false);
#if 0
        // disable items that are already in use
        PopupMenuListener* pml = new PopupMenuListener() {
            @Override
            /*public*/ void popupMenuWillBecomeVisible(PopupMenuEvent e) {
                // This method is called before the popup menu becomes visible.
                log.debug("PopupMenuWillBecomeVisible");  // NOI18N
                Object o = e.getSource();
                if (o instanceof JmriBeanComboBox) {
                    JmriBeanComboBox* jbcb = (JmriBeanComboBox) o;
                    for (int idx = 0; idx < jbcb.getItemCount(); idx++) {
                        jbcb.setItemEnabled(idx,  layoutEditor->validatePhysicalTurnout(jbcb.getItemAt(idx),  nullptr));
                    }
                }
            }

            @Override
            /*public*/ void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
                // This method is called before the popup menu becomes invisible
                log.debug("PopupMenuWillBecomeInvisible");  // NOI18N
            }

            @Override
            /*public*/ void popupMenuCanceled(PopupMenuEvent e) {
                // This method is called when the popup menu is canceled
                log.debug("PopupMenuCanceled");  // NOI18N
            }
        };
#endif
        TurnoutPopupMenuListener* pml;
#if 0
        editLayoutTurnout1stTurnoutComboBox->addPopupMenuListener(pml = new TurnoutPopupMenuListener(this));
        editLayoutTurnout1stTurnoutComboBox->setEnabledColor(Qt::darkGreen);
        editLayoutTurnout1stTurnoutComboBox->setDisabledColor(Qt::red);
#endif
        panel1Layout->addWidget(editLayoutTurnout1stTurnoutComboBox);
        contentPane->layout()->addWidget(panel1);

        QWidget* panel1a = new QWidget();
        QVBoxLayout* panel1aLayout;
        panel1a->setLayout(panel1aLayout = new QVBoxLayout());//panel1a, BoxLayout.Y_AXIS));

        editLayoutTurnout2ndTurnoutComboBox = new NamedBeanComboBox(
                InstanceManager::turnoutManagerInstance(),
                layoutTurnout->getSecondTurnout(),
                NamedBean::DisplayOptions::DISPLAYNAME);
         layoutEditor->setupComboBox(editLayoutTurnout2ndTurnoutComboBox, false, true, false);
#if 0
        editLayoutTurnout2ndTurnoutComboBox->addPopupMenuListener(pml);
        editLayoutTurnout2ndTurnoutComboBox->setEnabledColor(Qt::darkGreen);
        editLayoutTurnout2ndTurnoutComboBox->setDisabledColor(Qt::red);
#endif

//        editLayoutTurnout2ndTurnoutCheckBox.addActionListener((ActionEvent e) -> {
//            bool additionalEnabled = editLayoutTurnout2ndTurnoutCheckBox->isChecked();
//            editLayoutTurnout2ndTurnoutLabel->setEnabled(additionalEnabled);
//            editLayoutTurnout2ndTurnoutComboBox->setEnabled(additionalEnabled);
//            editLayoutTurnout2ndTurnoutInvertCheckBox->setEnabled(additionalEnabled);
//        });
        connect(editLayoutTurnout2ndTurnoutCheckBox, SIGNAL(clicked(bool)), this, SLOT(onEditLayoutTurnout2ndTurnoutCheckBox(bool)));
        panel1aLayout->addWidget(editLayoutTurnout2ndTurnoutCheckBox);
        contentPane->layout()->addWidget(panel1a);

        editLayoutTurnout2ndTurnoutLabel = new QLabel(tr("Supporting %1:").arg(tr("Turnout")));  // NOI18N
        editLayoutTurnout2ndTurnoutLabel->setEnabled(false);
        QWidget* panel1b = new QWidget();
        panel1b->setLayout(new QVBoxLayout());
        panel1b->layout()->addWidget(editLayoutTurnout2ndTurnoutLabel);
        panel1b->layout()->addWidget(editLayoutTurnout2ndTurnoutComboBox);
//        editLayoutTurnout2ndTurnoutInvertCheckBox.addActionListener((ActionEvent e) -> {
//            LayoutTurnout::setSecondTurnoutInverted(editLayoutTurnout2ndTurnoutInvertCheckBox->isChecked());
//        });
        connect(editLayoutTurnout2ndTurnoutInvertCheckBox, SIGNAL(clicked(bool)), this, SLOT(onEditLayoutTurnout2ndTurnoutInvertCheckBox(bool)));
        editLayoutTurnout2ndTurnoutInvertCheckBox->setEnabled(false);
        panel1b->layout()->addWidget(editLayoutTurnout2ndTurnoutInvertCheckBox);
        contentPane->layout()->addWidget(panel1b);

        // add continuing state choice, if not crossover
        if ((layoutTurnout->getTurnoutType() != LayoutTurnout::DOUBLE_XOVER)
                && (layoutTurnout->getTurnoutType() != LayoutTurnout::RH_XOVER)
                && (layoutTurnout->getTurnoutType() != LayoutTurnout::LH_XOVER)) {
            QWidget* panel3 = new QWidget();
            FlowLayout* panel3Layout;
            panel3->setLayout(panel3Layout = new FlowLayout());
            editLayoutTurnoutStateComboBox->clear();
            editLayoutTurnoutStateComboBox->addItem(InstanceManager::turnoutManagerInstance()->getClosedText());
            editLayoutTurnoutClosedIndex = 0;
            editLayoutTurnoutStateComboBox->addItem(InstanceManager::turnoutManagerInstance()->getThrownText());
            editLayoutTurnoutThrownIndex = 1;
            editLayoutTurnoutStateComboBox->setToolTip(tr("Select turnout state corresponding to continuing route."));  // NOI18N
            panel3Layout->addWidget(new QLabel(tr("Continuing Route Turnout State")));  // NOI18N
            panel3Layout->addWidget(editLayoutTurnoutStateComboBox);
            contentPane->layout()->addWidget(panel3);
        }

        QWidget* panel33 = new QWidget();
        FlowLayout* panel33Layout;
        panel33->setLayout(panel33Layout = new FlowLayout());
        editLayoutTurnoutHiddenCheckBox->setToolTip(tr("HiddenToolTip"));  // NOI18N
        panel33Layout->addWidget(editLayoutTurnoutHiddenCheckBox);
        contentPane->layout()->addWidget(panel33);

//        TitledBorder border = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
//        border.setTitle(tr("Block"));  // NOI18N
        // setup block name
        QGroupBox* panel2 = new QGroupBox();
        //panel2.setBorder(border);
        panel2->setTitle(tr("Block"));
        FlowLayout* panel2Layout;
        panel2->setLayout(panel2Layout = new FlowLayout());
        panel2Layout->addWidget(editLayoutTurnoutBlockNameComboBox);
         layoutEditor->setupComboBox(editLayoutTurnoutBlockNameComboBox, false, true, true);
        editLayoutTurnoutBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
        panel2Layout->addWidget(editLayoutTurnoutBlockButton = new QPushButton(tr("Create/Edit")));  // NOI18N
//        editLayoutTurnoutBlockButton.addActionListener((ActionEvent e) -> {
//            editLayoutTurnoutEditBlockPressed(e);
//        });
        connect(editLayoutTurnoutBlockButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurnoutEditBlockPressed()));
        contentPane->layout()->addWidget(panel2);
        if ((layoutTurnout->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
                || (layoutTurnout->getTurnoutType() == LayoutTurnout::RH_XOVER)
                || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_XOVER)) {
            QGroupBox* panel21 = new QGroupBox();
            FlowLayout* panel21Layout;
            panel21->setLayout(panel21Layout = new FlowLayout());
            //TitledBorder borderblk2 = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
            //borderblk2.setTitle(tr("BeanNameBlock") + " 2");  // NOI18N
            //panel21.setBorder(borderblk2);
            panel21->setTitle(tr("Block"));
             layoutEditor->setupComboBox(editLayoutTurnoutBlockBNameComboBox, false, true, true);
            editLayoutTurnoutBlockBNameComboBox->setToolTip(tr("Edit this Block name to change the block linked to the second connecting point."));  // NOI18N
            panel21Layout->addWidget(editLayoutTurnoutBlockBNameComboBox);

            panel21Layout->addWidget(editLayoutTurnoutBlockBButton = new QPushButton(tr("Create/Edit")));  // NOI18N
//            editLayoutTurnoutBlockBButton.addActionListener((ActionEvent e) -> {
//                editLayoutTurnoutEditBlockBPressed(e);
//            });
            connect(editLayoutTurnoutBlockBButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurnoutEditBlockBPressed()));
            editLayoutTurnoutBlockBButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "2"));  // NOI18N
            contentPane->layout()->addWidget(panel21);

            QGroupBox* panel22 = new QGroupBox();
            FlowLayout* panel22Layout;
            panel22->setLayout(panel22Layout = new FlowLayout());
            //TitledBorder borderblk3 = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
            //borderblk3.setTitle(tr("BeanNameBlock") + " 3");  // NOI18N
            //panel22.setBorder(borderblk3);
            panel22->setTitle(tr("Block"));
             layoutEditor->setupComboBox(editLayoutTurnoutBlockCNameComboBox, false, true, true);
            editLayoutTurnoutBlockCNameComboBox->setToolTip(tr("Edit this Block name to change the block linked to third connecting point."));  // NOI18N
            panel22Layout->addWidget(editLayoutTurnoutBlockCNameComboBox);
            panel22Layout->addWidget(editLayoutTurnoutBlockCButton = new QPushButton(tr("Create/Edit")));  // NOI18N
//            editLayoutTurnoutBlockCButton.addActionListener((ActionEvent e) -> {
//                editLayoutTurnoutEditBlockCPressed(e);
//            });
            connect(editLayoutTurnoutBlockCButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurnoutEditBlockCPressed()));
            editLayoutTurnoutBlockCButton->setToolTip(tr("Click here to create/edit information for Block {0} shown above.", "3"));  // NOI18N
            contentPane->layout()->addWidget(panel22);

            QGroupBox* panel23 = new QGroupBox();
            FlowLayout* panel23Layout;
            panel23->setLayout(panel23Layout = new FlowLayout());
            //TitledBorder borderblk4 = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));
            //borderblk4.setTitle(tr("BeanNameBlock") + " 4");  // NOI18N
            //panel23.setBorder(borderblk4);
            panel23->setTitle(tr("Block"));
             layoutEditor->setupComboBox(editLayoutTurnoutBlockDNameComboBox, false, true, true);
            editLayoutTurnoutBlockDNameComboBox->setToolTip(tr("Edit this Block name to change the block linked to fourth connecting point."));  // NOI18N
            panel23Layout->addWidget(editLayoutTurnoutBlockDNameComboBox);
            panel23Layout->addWidget(editLayoutTurnoutBlockDButton = new QPushButton(tr("Create/Edit")));  // NOI18N
//            editLayoutTurnoutBlockDButton.addActionListener((ActionEvent e) -> {
//                editLayoutTurnoutEditBlockDPressed(e);
//            });
            connect(editLayoutTurnoutBlockDButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurnoutEditBlockDPressed()));
            editLayoutTurnoutBlockDButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "4"));  // NOI18N
            contentPane->layout()->addWidget(panel23);
        }
        // set up Edit Block, Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        FlowLayout* panel5Layout;
        panel5->setLayout(panel5Layout = new FlowLayout());
        // Edit Block

        editLayoutTurnoutBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.").arg("")); // empty value for block 1  // NOI18N
        // Done
        panel5Layout->addWidget(editLayoutTurnoutDoneButton = new QPushButton(tr("Done")));  // NOI18N

        // make this button the default button (return or enter activates)
        // Note: We have to invoke this later because we don't currently have a root pane
//        SwingUtilities.invokeLater(() -> {
//            JRootPane rootPane = SwingUtilities.getRootPane(editLayoutTurnoutDoneButton);
//            rootPane.setDefaultButton(editLayoutTurnoutDoneButton);
//        });
        editLayoutTurnoutDoneButton->setDefault(true);

//        editLayoutTurnoutDoneButton.addActionListener((ActionEvent e) -> {
//            editLayoutTurnoutDonePressed(e);
//        });
        connect(editLayoutTurnoutDoneButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurnoutDonePressed()));
        editLayoutTurnoutDoneButton->setToolTip(tr("Click [{0}] to accept any changes made above and close this dialog. %1").arg(tr("Done")));  // NOI18N
        // Cancel
        panel5Layout->addWidget(editLayoutTurnoutCancelButton = new QPushButton(tr("Cancel")));  // NOI18N
//        editLayoutTurnoutCancelButton.addActionListener((ActionEvent e) -> {
//            editLayoutTurnoutCancelPressed(e);
//        });
        connect(editLayoutTurnoutCancelButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurnoutCancelPressed()));
        editLayoutTurnoutCancelButton->setToolTip(tr("Click %1 to dismiss this dialog without making changes.").arg(tr("Cancel")));  // NOI18N
        contentPane->layout()->addWidget(panel5);
    }

    editLayoutTurnout1stTurnoutComboBox->setSelectedItemByName(layoutTurnout->getTurnoutName());

    editLayoutTurnoutHiddenCheckBox->setChecked(layoutTurnout->isHidden());

    // Set up for Edit
    editLayoutTurnoutBlockNameComboBox->setSelectedItemByName(layoutTurnout->getBlockName());
    editLayoutTurnoutBlockNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlock()));
    if ((layoutTurnout->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::RH_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_XOVER)) {
        editLayoutTurnoutBlockBNameComboBox->setSelectedItemByName(layoutTurnout->getBlockBName());
        editLayoutTurnoutBlockCNameComboBox->setSelectedItemByName(layoutTurnout->getBlockCName());
        editLayoutTurnoutBlockDNameComboBox->setSelectedItemByName(layoutTurnout->getBlockDName());
        editLayoutTurnoutBlockBNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlockB()));
        editLayoutTurnoutBlockCNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlockC()));
        editLayoutTurnoutBlockDNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlockD()));
    }

    if ((layoutTurnout->getTurnoutType() != LayoutTurnout::DOUBLE_XOVER)
            && (layoutTurnout->getTurnoutType() != LayoutTurnout::RH_XOVER)
            && (layoutTurnout->getTurnoutType() != LayoutTurnout::LH_XOVER)) {
        editLayoutTurnout2ndTurnoutCheckBox->setText(tr("ThrowTwoTurnouts"));  // NOI18N
    }

    bool enable2nd = !layoutTurnout->getSecondTurnoutName().isEmpty();
    editLayoutTurnout2ndTurnoutCheckBox->setChecked(enable2nd);
    editLayoutTurnout2ndTurnoutInvertCheckBox->setEnabled(enable2nd);
    editLayoutTurnout2ndTurnoutLabel->setEnabled(enable2nd);
    editLayoutTurnout2ndTurnoutComboBox->setEnabled(enable2nd);
    if (enable2nd) {
        editLayoutTurnout2ndTurnoutInvertCheckBox->setChecked(layoutTurnout->isSecondTurnoutInverted());
        editLayoutTurnout2ndTurnoutComboBox->setSelectedItemByName(layoutTurnout->getSecondTurnoutName());
    } else {
        editLayoutTurnout2ndTurnoutInvertCheckBox->setChecked(false);
        editLayoutTurnout2ndTurnoutComboBox->setSelectedItemByName("");
    }

    if ((layoutTurnout->getTurnoutType() != LayoutTurnout::DOUBLE_XOVER)
            && (layoutTurnout->getTurnoutType() != LayoutTurnout::RH_XOVER)
            && (layoutTurnout->getTurnoutType() != LayoutTurnout::LH_XOVER)) {
        if (layoutTurnout->getContinuingSense() == Turnout::CLOSED) {
            editLayoutTurnoutStateComboBox->setCurrentIndex(editLayoutTurnoutClosedIndex);
        } else {
            editLayoutTurnoutStateComboBox->setCurrentIndex(editLayoutTurnoutThrownIndex);
        }
    }

//    new java.awt.event.WindowAdapter() {
//        @Override
//        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//            editLayoutTurnoutCancelPressed( nullptr);
//        }
//    });
        editLayoutTurnoutFrame->addWindowListener(new EditLayoutWindowListener(this));
    editLayoutTurnoutFrame->pack();
    editLayoutTurnoutFrame->setVisible(true);
    editLayoutTurnoutOpen = true;
    editLayoutTurnoutNeedsBlockUpdate = false;

    showSensorMessage();
#endif
}   // editLayoutTurnout

// disable items that are already in use
//PopupMenuListener* pml = new PopupMenuListener() {
    TurnoutPopupMenuListener::TurnoutPopupMenuListener(LayoutTrackEditors *layoutTrackEditors) { this->layoutTrackEditors = layoutTrackEditors;}
   // @Override
/*public*/ void TurnoutPopupMenuListener::popupMenuWillBecomeVisible(/*PopupMenuEvent e*/) {
    // This method is called before the popup menu becomes visible.
    layoutTrackEditors->log->debug("PopupMenuWillBecomeVisible");  // NOI18N
//        Object o = e.getSource();
//        if (o instanceof JmriBeanComboBox) {
//            JmriBeanComboBox* jbcb = (JmriBeanComboBox) o;
//            for (int idx = 0; idx < jbcb.getItemCount(); idx++) {
//                jbcb.setItemEnabled(idx,  layoutEditor->validatePhysicalTurnout(jbcb.getItemAt(idx),  nullptr));
//            }
//        }
}

//@Override
/*public*/ void TurnoutPopupMenuListener::popupMenuWillBecomeInvisible(/*PopupMenuEvent e*/) {
    // This method is called before the popup menu becomes invisible
    layoutTrackEditors->log->debug("PopupMenuWillBecomeInvisible");  // NOI18N
}

//@Override
/*public*/ void TurnoutPopupMenuListener::popupMenuCanceled(/*PopupMenuEvent e*/) {
    // This method is called when the popup menu is canceled
    layoutTrackEditors->log->debug("PopupMenuCanceled");  // NOI18N
}
//};

/*private*/ void LayoutTrackEditors::onEditLayoutTurnout2ndTurnoutCheckBox(bool)
{
 bool additionalEnabled = editLayoutTurnout2ndTurnoutCheckBox->isChecked();
 editLayoutTurnout2ndTurnoutLabel->setEnabled(additionalEnabled);
 editLayoutTurnout2ndTurnoutComboBox->setEnabled(additionalEnabled);
 editLayoutTurnout2ndTurnoutInvertCheckBox->setEnabled(additionalEnabled);
}

/*private*/ void LayoutTrackEditors::onEditLayoutTurnout2ndTurnoutInvertCheckBox(bool)
{
 layoutTurnout->setSecondTurnoutInverted(editLayoutTurnout2ndTurnoutInvertCheckBox->isChecked());
}

/*private*/ void LayoutTrackEditors::editLayoutTurnoutEditBlockPressed(/*ActionEvent a*/) {
    // check if a block name has been entered
    QString newName = editLayoutTurnoutBlockNameComboBox->getSelectedItemDisplayName();
    if (layoutTurnout->getBlockName() != (newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            layoutTurnout->setLayoutBlock( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            layoutTurnout->setLayoutBlock( nullptr);
        }
        editLayoutTurnoutNeedRedraw = true;
        editLayoutTurnoutNeedsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (layoutTurnout->getLayoutBlock() ==  nullptr) {
        JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),  // NOI18N
                tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
        return;
    }
    layoutTurnout->getLayoutBlock()->editLayoutBlock(editLayoutTurnoutFrame);
    editLayoutTurnoutNeedRedraw = true;
     layoutEditor->setDirty();
}   // editLayoutTurnoutEditBlockPressed

/*private*/ void LayoutTrackEditors::editLayoutTurnoutEditBlockBPressed(/*ActionEvent a*/) {
    // check if a block name has been entered
    QString newName = editLayoutTurnoutBlockBNameComboBox->getSelectedItemDisplayName();
    if (layoutTurnout->getBlockBName() != (newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            layoutTurnout->setLayoutBlockB( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            layoutTurnout->setLayoutBlockB( nullptr);
        }
        editLayoutTurnoutNeedRedraw = true;
        editLayoutTurnoutNeedsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (layoutTurnout->getLayoutBlockB() ==  nullptr) {
        JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),  // NOI18N
                tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
        return;
    }
    layoutTurnout->getLayoutBlockB()->editLayoutBlock(editLayoutTurnoutFrame);
    editLayoutTurnoutNeedRedraw = true;
     layoutEditor->setDirty();
}   // editLayoutTurnoutEditBlockBPressed

/*private*/ void LayoutTrackEditors::editLayoutTurnoutEditBlockCPressed(/*ActionEvent a*/) {
    // check if a block name has been entered
    QString newName = editLayoutTurnoutBlockCNameComboBox->getSelectedItemDisplayName();
    if (layoutTurnout->getBlockCName() != (newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            layoutTurnout->setLayoutBlockC( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            layoutTurnout->setLayoutBlockC( nullptr);
        }
        editLayoutTurnoutNeedRedraw = true;
        editLayoutTurnoutNeedsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (layoutTurnout->getLayoutBlockC() ==  nullptr) {
        JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),  // NOI18N
                tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
        return;
    }
    layoutTurnout->getLayoutBlockC()->editLayoutBlock(editLayoutTurnoutFrame);
    editLayoutTurnoutNeedRedraw = true;
     layoutEditor->setDirty();
}   // editLayoutTurnoutEditBlockCPressed

/*private*/ void LayoutTrackEditors::editLayoutTurnoutEditBlockDPressed(/*ActionEvent a*/) {
    // check if a block name has been entered
    QString newName = editLayoutTurnoutBlockDNameComboBox->getSelectedItemDisplayName();
    if (layoutTurnout->getBlockDName() != (newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            layoutTurnout->setLayoutBlockD( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            layoutTurnout->setLayoutBlockD( nullptr);
        }
        editLayoutTurnoutNeedRedraw = true;
        editLayoutTurnoutNeedsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (layoutTurnout->getLayoutBlockD() ==  nullptr) {
        JOptionPane::showMessageDialog(editLayoutTurnoutFrame,
                tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),  // NOI18N
                tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
        return;
    }
    layoutTurnout->getLayoutBlockD()->editLayoutBlock(editLayoutTurnoutFrame);
    editLayoutTurnoutNeedRedraw = true;
     layoutEditor->setDirty();
}   // editLayoutTurnoutEditBlockDPressed

/*private*/ void LayoutTrackEditors::editLayoutTurnoutDonePressed(/*ActionEvent a*/) {
    // check if Turnout changed
    QString newName = editLayoutTurnout1stTurnoutComboBox->getSelectedItemDisplayName();
    if (layoutTurnout->getTurnoutName() != (newName)) {
        // turnout has changed
        if ( layoutEditor->validatePhysicalTurnout(
                newName, editLayoutTurnoutFrame)) {
            layoutTurnout->setTurnout(newName);
        } else {
            layoutTurnout->setTurnout( nullptr);
            editLayoutTurnout1stTurnoutComboBox->setSelectedItemByName("");
        }
        editLayoutTurnoutNeedRedraw = true;
    }

    if (editLayoutTurnout2ndTurnoutCheckBox->isChecked()) {
        newName = editLayoutTurnout2ndTurnoutComboBox->getSelectedItemDisplayName();
        if (layoutTurnout->getSecondTurnoutName() != (newName)) {
            if ((layoutTurnout->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
                    || (layoutTurnout->getTurnoutType() == LayoutTurnout::RH_XOVER)
                    || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_XOVER)) {
                // turnout has changed
                if ( layoutEditor->validatePhysicalTurnout(
                        newName, editLayoutTurnoutFrame)) {
                    layoutTurnout->setSecondTurnout(newName);
                } else {
                    editLayoutTurnout2ndTurnoutCheckBox->setChecked(false);
                    layoutTurnout->setSecondTurnout( nullptr);
                    editLayoutTurnout2ndTurnoutComboBox->setSelectedItemByName("");
                }
                editLayoutTurnoutNeedRedraw = true;
            } else {
                layoutTurnout->setSecondTurnout(newName);
            }
        }
    } else {
        layoutTurnout->setSecondTurnout( nullptr);
    }

    // set the continuing route Turnout State
    if ((layoutTurnout->getTurnoutType() == LayoutTurnout::RH_TURNOUT)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_TURNOUT)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::WYE_TURNOUT)) {
        layoutTurnout->setContinuingSense(Turnout::CLOSED);
        if (editLayoutTurnoutStateComboBox->currentIndex() == editLayoutTurnoutThrownIndex) {
            layoutTurnout->setContinuingSense(Turnout::THROWN);
        }
    }

    // check if Block changed
    newName = editLayoutTurnoutBlockNameComboBox->getSelectedItemDisplayName();
    if (layoutTurnout->getBlockName() != (newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            layoutTurnout->setLayoutBlock( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            layoutTurnout->setLayoutBlock( nullptr);
        }
        editLayoutTurnoutNeedRedraw = true;
        editLayoutTurnoutNeedsBlockUpdate = true;
    }
    if ((layoutTurnout->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::RH_XOVER)) {
        // check if Block 2 changed
        newName = editLayoutTurnoutBlockBNameComboBox->getSelectedItemDisplayName();
        if (layoutTurnout->getBlockBName() != (newName)) {
            // get new block, or  nullptr if block has been removed
            try {
                layoutTurnout->setLayoutBlockB( layoutEditor->provideLayoutBlock(newName));
            } catch (IllegalArgumentException ex) {
                layoutTurnout->setLayoutBlockB( nullptr);
            }
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if Block 3 changed
        newName = editLayoutTurnoutBlockCNameComboBox->getSelectedItemDisplayName();
        if (layoutTurnout->getBlockCName() != (newName)) {
            // get new block, or  nullptr if block has been removed
            try {
                layoutTurnout->setLayoutBlockC( layoutEditor->provideLayoutBlock(newName));
            } catch (IllegalArgumentException ex) {
                layoutTurnout->setLayoutBlockC( nullptr);
            }
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
        // check if Block 4 changed
        newName = editLayoutTurnoutBlockDNameComboBox->getSelectedItemDisplayName();
        if (layoutTurnout->getBlockDName() != (newName)) {
            // get new block, or  nullptr if block has been removed
            try {
                layoutTurnout->setLayoutBlockD( layoutEditor->provideLayoutBlock(newName));
            } catch (IllegalArgumentException ex) {
                layoutTurnout->setLayoutBlockD( nullptr);
            }
            editLayoutTurnoutNeedRedraw = true;
            editLayoutTurnoutNeedsBlockUpdate = true;
        }
    }
    // set hidden
    bool oldHidden = layoutTurnout->isHidden();
    layoutTurnout->setHidden(editLayoutTurnoutHiddenCheckBox->isChecked());
    if (oldHidden != layoutTurnout->isHidden()) {
        editLayoutTurnoutNeedRedraw = true;
    }
    editLayoutTurnoutOpen = false;
    editLayoutTurnoutFrame->setVisible(false);
    editLayoutTurnoutFrame->dispose();
    editLayoutTurnoutFrame =  nullptr;
    if (editLayoutTurnoutNeedsBlockUpdate) {
        layoutTurnout->updateBlockInfo();
        layoutTurnout->reCheckBlockBoundary();
    }
    if (editLayoutTurnoutNeedRedraw) {
         layoutEditor->redrawPanel();
         layoutEditor->setDirty();
        editLayoutTurnoutNeedRedraw = false;
    }
}   // editLayoutTurnoutDonePressed


/*private*/ void LayoutTrackEditors::editLayoutTurnoutCancelPressed(/*ActionEvent a*/) {
    editLayoutTurnoutOpen = false;
    editLayoutTurnoutFrame->setVisible(false);
    editLayoutTurnoutFrame->dispose();
    editLayoutTurnoutFrame =  nullptr;
    if (editLayoutTurnoutNeedsBlockUpdate) {
        layoutTurnout->updateBlockInfo();
    }
    if (editLayoutTurnoutNeedRedraw) {
         layoutEditor->redrawPanel();
         layoutEditor->setDirty();
        editLayoutTurnoutNeedRedraw = false;
    }
}

/*================*\
| Edit Layout Slip |
\*================*/

/**
 * Edit a Slip
 */
/*protected*/ void LayoutTrackEditors::editLayoutSlip(LayoutSlip* layoutSlip)
{
 sensorList.clear();

 this->layoutSlip = layoutSlip;
 if (editLayoutSlipOpen) {
    editLayoutSlipFrame->setVisible(true);
 }
 else if (editLayoutSlipFrame ==  nullptr)
 {   // Initialize if needed
    editLayoutSlipFrame = new JmriJFrameX(tr("Edit Slip"), false, true);  // NOI18N
    editLayoutSlipFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutSlip", true);  // NOI18N
    editLayoutSlipFrame->setLocation(50, 30);

    QWidget* contentPane = editLayoutSlipFrame->getContentPane(true);
    //contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

    QWidget* panel1 = new QWidget();
    panel1->setLayout(new FlowLayout());
    QLabel* turnoutNameLabel = new QLabel(tr("Turnout") + " A " + tr("Name"));  // NOI18N
    panel1->layout()->addWidget(turnoutNameLabel);
    editLayoutSlipTurnoutAComboBox = new NamedBeanComboBox(
            InstanceManager::turnoutManagerInstance(),
            layoutSlip->getTurnout(),
            NamedBean::DisplayOptions::DISPLAYNAME);
    LayoutEditor::setupComboBox(editLayoutSlipTurnoutAComboBox, false, true, false);

    // disable items that are already in use
#if 0 // see after this method:
    SlipPopupMenuListener pml = new slipPopupMenuListener() {
        @Override
        /*public*/ void popupMenuWillBecomeVisible(PopupMenuEvent e) {
            // This method is called before the popup menu becomes visible.
            log.debug("PopupMenuWillBecomeVisible");  // NOI18N
            Object o = e.getSource();
            if (o instanceof JmriBeanComboBox) {
                JmriBeanComboBox* jbcb = (JmriBeanComboBox) o;
                jmri.Manager m = jbcb.getManager();
                if (m !=  nullptr) {
                    int idx = 0;
                    for (Object obj : m.getNamedBeanSet()) {
                        NamedBean bean = (NamedBean) obj;  // entire class needs more attention to typing
                        String systemName = bean.getSystemName();
                        jbcb.setItemEnabled(idx++,  layoutEditor->validatePhysicalTurnout(systemName,  nullptr));
                    }
                }
            }
        }

        @Override
        /*public*/ void popupMenuWillBecomeInvisible(PopupMenuEvent e) {
            // This method is called before the popup menu becomes invisible
            log.debug("PopupMenuWillBecomeInvisible");  // NOI18N
        }

        @Override
        /*public*/ void popupMenuCanceled(PopupMenuEvent e) {
            // This method is called when the popup menu is canceled
            log.debug("PopupMenuCanceled");  // NOI18N
        }
    };
#endif
    SlipPopupMenuListener* pml = new SlipPopupMenuListener(this);
#if 0
    editLayoutSlipTurnoutAComboBox->addPopupMenuListener(pml);
    editLayoutSlipTurnoutAComboBox->setEnabledColor(QColor(Qt::darkGreen));
    editLayoutSlipTurnoutAComboBox->setDisabledColor(QColor(Qt::red));
#endif
    panel1->layout()->addWidget(editLayoutSlipTurnoutAComboBox);
    contentPane->layout()->addWidget(panel1);

    QWidget* panel1a = new QWidget();
    panel1a->setLayout(new FlowLayout());
    QLabel* turnoutBNameLabel = new QLabel(tr("Turnout") + " B " + tr("Name"));  // NOI18N
    panel1a->layout()->addWidget(turnoutBNameLabel);

    editLayoutSlipTurnoutBComboBox = new NamedBeanComboBox(
            InstanceManager::turnoutManagerInstance(),
            layoutSlip->getTurnoutB(),
            NamedBean::DisplayOptions::DISPLAYNAME);
    LayoutEditor::setupComboBox(editLayoutSlipTurnoutBComboBox, false, true, false);
#if 0
    editLayoutSlipTurnoutBComboBox->addPopupMenuListener(pml);
    editLayoutSlipTurnoutBComboBox->setEnabledColor(QColor(Qt::darkGreen));
    editLayoutSlipTurnoutBComboBox->setDisabledColor(QColor(Qt::red));
#endif
    panel1a->layout()->addWidget(editLayoutSlipTurnoutBComboBox);

    contentPane->layout()->addWidget(panel1a);

    QWidget* panel2 = new QWidget();
    QGridLayout* panel2Layout;
    panel2->setLayout(panel2Layout = new QGridLayout()); //GridLayout(0, 3, 2, 2));

    panel2Layout->addWidget(new QLabel("   "),0, 0, 1, 1);
    panel2Layout->addWidget(new QLabel(tr("Turnout") + " A:"),0, 1, 1,1);  // NOI18N
    panel2Layout->addWidget(new QLabel(tr("Turnout") + " B:"), 0,2, 1,1);  // NOI18N
    //for (Map.Entry<Integer, LayoutSlip.TurnoutState> ts : layoutSlip.getTurnoutStates().entrySet())
    QHashIterator<int, TurnoutState*> ts(layoutSlip->getTurnoutStates());
    while(ts.hasNext())
    {
     ts.next();
#if 1
     SampleStates* draw = new SampleStates(ts.key(), this);
     draw->repaint();
     draw->resize(QSize(40, 40));
     panel2Layout->addWidget(draw);

     panel2Layout->addWidget(ts.value()->getComboA());
     panel2Layout->addWidget(ts.value()->getComboB());
#endif
    }
#if 1
    testPanel = new TestState(this);
    testPanel->resize(40, 40);
    testPanel->setMaximumSize(QSize(40, 40));
    panel2Layout->addWidget(testPanel);
#endif
    QPushButton* testButton = new QPushButton("Test");  // NOI18N
//    testButton.addActionListener((ActionEvent e) -> {
//        toggleStateTest();
//    });
    connect(testButton, SIGNAL(clicked(bool)), this, SLOT(toggleStateTest()));
    panel2Layout->addWidget(testButton);
    contentPane->layout()->addWidget(panel2);

    QWidget* panel33 = new QWidget();
    FlowLayout* panel33Layout;
    panel33->setLayout(panel33Layout = new FlowLayout());
    editLayoutSlipHiddenBox->setToolTip(tr("Check to hide this track segment when not in edit mode."));  // NOI18N
    panel33Layout->addWidget(editLayoutSlipHiddenBox);
    contentPane->layout()->addWidget(panel33);

    // setup block name
    QWidget* panel3 = new QWidget();
    FlowLayout* panel3Layout;
    panel3->setLayout(panel3Layout = new FlowLayout());
    QLabel* block1NameLabel = new QLabel(tr("Block Name:"));  // NOI18N
    panel3Layout->addWidget(block1NameLabel);
    panel3Layout->addWidget(editLayoutSlipBlockNameComboBox);
     layoutEditor->setupComboBox(editLayoutSlipBlockNameComboBox, false, true, true);
    editLayoutSlipBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N

    contentPane->layout()->addWidget(panel3);
    // set up Edit Block buttons
    QWidget* panel4 = new QWidget();
    FlowLayout* panel4Layout;
    panel4->setLayout(panel4Layout =new FlowLayout());
    // Edit Block
    panel4Layout->addWidget(editLayoutSlipBlockButton = new QPushButton(tr("Create/Edit Block %1").arg("")));  // NOI18N
//    editLayoutSlipBlockButton.addActionListener(
//            (ActionEvent event) -> {
//                editLayoutSlipEditBlockPressed(event);
//            }
//    );
    connect(editLayoutSlipBlockButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutSlipEditBlockPressed()));
    editLayoutSlipBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "")); // empty value for block 1  // NOI18N

    contentPane->layout()->addWidget(panel4);
    // set up Done and Cancel buttons
    QWidget* panel5 = new QWidget();
    FlowLayout* panel5Layout;
    panel5->setLayout(panel5Layout = new FlowLayout());
    panel5Layout->addWidget(editLayoutSlipDoneButton = new QPushButton(tr("Done")));  // NOI18N

    // make this button the default button (return or enter activates)
    // Note: We have to invoke this later because we don't currently have a root pane
//    SwingUtilities.invokeLater(() -> {
//        JRootPane rootPane = SwingUtilities.getRootPane(editLayoutSlipDoneButton);
//        rootPane.setDefaultButton(editLayoutSlipDoneButton);
//    }
//    );
    editLayoutSlipDoneButton->setDefault(true);

//    editLayoutSlipDoneButton.addActionListener((ActionEvent event) -> {
//        editLayoutSlipDonePressed(event);
//    });
    connect(editLayoutSlipDoneButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutSlipDonePressed()));
    editLayoutSlipDoneButton->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));  // NOI18N
    // Cancel
    panel5Layout->addWidget(editLayoutSlipCancelButton = new QPushButton(tr("Cancel")));  // NOI18N
//    editLayoutSlipCancelButton.addActionListener((ActionEvent event) -> {
//        editLayoutSlipCancelPressed(event);
//    });
    connect(editLayoutSlipCancelButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutSlipCancelPressed()));
    editLayoutSlipCancelButton->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));  // NOI18N
    contentPane->layout()->addWidget(panel5);
 }

 editLayoutSlipHiddenBox->setChecked(layoutSlip->isHidden());

 // Set up for Edit
 editLayoutSlipTurnoutAComboBox->setSelectedItemByName(layoutSlip->getTurnoutName());
 editLayoutSlipTurnoutBComboBox->setSelectedItemByName(layoutSlip->getTurnoutBName());
 editLayoutSlipBlockNameComboBox->setSelectedItemByName(layoutSlip->getBlockName());
 editLayoutSlipBlockNameComboBox->setEnabled(!hasNxSensorPairs(layoutSlip->getLayoutBlock()));

 //    editLayoutSlipFrame.addWindowListener(new java.awt.event.WindowAdapter() {
 //        @Override
 //        /*public*/ void windowClosing(WindowEvent e) {
 //            editLayoutSlipCancelPressed( nullptr);
 //        }
 //    });

 editLayoutSlipFrame->addWindowListener(new SlipEditWindowListener(this));
 editLayoutSlipFrame->pack();
 editLayoutSlipFrame->setVisible(true);
 editLayoutSlipOpen = true;
 editLayoutSlipNeedsBlockUpdate = false;

 showSensorMessage();

}   // editLayoutSlip

/*public*/ SlipPopupMenuListener::SlipPopupMenuListener(LayoutTrackEditors *layoutTrackEditors)
{
 this->lte = layoutTrackEditors;
}

/*public*/ void SlipPopupMenuListener::popupMenuWillBecomeVisible(PopupMenuEvent* e) {
    // This method is called before the popup menu becomes visible.
    lte->log->debug("PopupMenuWillBecomeVisible");  // NOI18N
    QObject* o = e->getSource();
    if (qobject_cast<JmriBeanComboBox*>(o))
    {
        JmriBeanComboBox* jbcb = (JmriBeanComboBox*) o;
        Manager* m = jbcb->getManager();
        if (m !=  nullptr)
        {
            int idx = 0;
            for (NamedBean* bean : m->getNamedBeanSet())
            {
               // NamedBean bean = (NamedBean) obj;  // entire class needs more attention to typing
                QString systemName = bean->getSystemName();
                jbcb->setItemEnabled(idx++, lte->layoutEditor->validatePhysicalTurnout(systemName,  nullptr));
            }
        }
    }
}

//@Override
/*public*/ void SlipPopupMenuListener::popupMenuWillBecomeInvisible(PopupMenuEvent *) {
    // This method is called before the popup menu becomes invisible
    lte->log->debug("PopupMenuWillBecomeInvisible");  // NOI18N
}

//@Override
/*public*/ void SlipPopupMenuListener::popupMenuCanceled(PopupMenuEvent *) {
    // This method is called when the popup menu is canceled
    lte->log->debug("PopupMenuCanceled");  // NOI18N
}
//};

/*private*/ void LayoutTrackEditors::drawSlipState(QPainter* g2, int state) {
QPointF cenP = layoutSlip->getCoordsCenter();
QPointF A = MathUtil::subtract(layoutSlip->getCoordsA(), cenP);
QPointF B = MathUtil::subtract(layoutSlip->getCoordsB(), cenP);
QPointF C = MathUtil::subtract(layoutSlip->getCoordsC(), cenP);
QPointF D = MathUtil::subtract(layoutSlip->getCoordsD(), cenP);

QPointF ctrP = QPointF(20.0, 20.0);
A = MathUtil::add(MathUtil::normalize(A, 18.0), ctrP);
B = MathUtil::add(MathUtil::normalize(B, 18.0), ctrP);
C = MathUtil::add(MathUtil::normalize(C, 18.0), ctrP);
D = MathUtil::add(MathUtil::normalize(D, 18.0), ctrP);

//g2->setColor(Color.black);
//g2->setStroke(new BasicStroke(2, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));
QPen pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);
g2->setPen(pen);

g2->drawLine(QLine(A.toPoint(), MathUtil::oneThirdPoint(A, C).toPoint()));
g2->drawLine(QLine(C.toPoint(), MathUtil::oneThirdPoint(C, A).toPoint()));

if (state == LayoutTurnout::STATE_AC || state == LayoutTurnout::STATE_BD || state == LayoutTurnout::UNKNOWN) {
    g2->drawLine(QLine(A.toPoint(), MathUtil::oneThirdPoint(A, D).toPoint()));
    g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, A).toPoint()));

    if (layoutSlip->getSlipType() == LayoutTurnout::DOUBLE_SLIP) {
        g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, C).toPoint()));
        g2->drawLine(QLine(C.toPoint(), MathUtil::oneThirdPoint(C, B).toPoint()));
    }
} else {
    g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, D).toPoint()));
    g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, B).toPoint()));
}

if (layoutSlip->getSlipType() == LayoutTurnout::DOUBLE_SLIP) {
    if (state == LayoutTurnout::STATE_AC) {
        g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, D).toPoint()));
        g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, B).toPoint()));

        //g2->setColor(Color.red);
        g2->drawLine(QLine(A.toPoint(), C.toPoint()));
    } else if (state == LayoutTurnout::STATE_BD) {
        //g2->setColor(Color.red);
     pen.setColor(Qt::red);
        g2->drawLine(QLine(B.toPoint(), D.toPoint()));
    } else if (state == LayoutTurnout::STATE_AD) {
        g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, C).toPoint()));

        g2->drawLine(QLine(C.toPoint(), MathUtil::oneThirdPoint(C, B).toPoint()));

        //g2->setColor(Color.red);
        pen.setColor(Qt::red);
        g2->drawLine(QLine(A.toPoint(), D.toPoint()));
    } else if (state == LayoutTurnout::STATE_BC) {
        g2->drawLine(QLine(A.toPoint(), MathUtil::oneThirdPoint(A, D).toPoint()));

        g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, A).toPoint()));
        //g2->setColor(Color.red);
        pen.setColor(Qt::red);
        g2->drawLine(QLine(B.toPoint(), C.toPoint()));
    } else {
        g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, D).toPoint()));
        g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, B).toPoint()));
    }
} else {
    g2->drawLine(QLine(A.toPoint(), MathUtil::oneThirdPoint(A, D).toPoint()));
    g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, A).toPoint()));

    if (state == LayoutTurnout::STATE_AD) {
        //g2->setColor(Color.red);
     pen.setColor(Qt::red);
        g2->drawLine(QLine(A.toPoint(), D.toPoint()));
    } else if (state == LayoutTurnout::STATE_AC) {
        g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, D).toPoint()));
        g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, B).toPoint()));

        //g2->setColor(Color.red);
        pen.setColor(Qt::red);
        g2->drawLine(QLine(A.toPoint(), C.toPoint()));
    } else if (state == LayoutTurnout::STATE_BD) {
        //g2->setColor(Color.red);
     pen.setColor(Qt::red);
        g2->drawLine(QLine(B.toPoint(), D.toPoint()));
    } else {
        g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, D).toPoint()));
        g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, B).toPoint()));
    }
 }
}   // drawSlipState
#if 0
class SampleStates extends QWidget {

// Methods, constructors, fields.
SampleStates(int state) {
    super();
    this.state = state;
}
int state;

//@Override
/*public*/ void paintComponent(Graphics g) {
    super.paintComponent(g);    // paints background
    if (g instanceof Graphics2D) {
        drawSlipState((Graphics2D) g, state);
    }
}
}

#endif
/**
* Toggle slip states if clicked on, physical turnout exists, and not
* disabled
*/
/*public*/ void LayoutTrackEditors::toggleStateTest() {
 int turnAState;
 int turnBState;
 switch (testState) {
    default:
    case LayoutTurnout::STATE_AC: {
        testState = LayoutTurnout::STATE_AD;
        break;
    }

    case LayoutTurnout::STATE_BD: {
        if (layoutSlip->getSlipType() == LayoutTurnout::SINGLE_SLIP) {
            testState = LayoutTurnout::STATE_AC;
        } else {
            testState = LayoutTurnout::STATE_BC;
        }
        break;
    }

    case LayoutTurnout::STATE_AD: {
        testState = LayoutTurnout::STATE_BD;
        break;
    }

    case LayoutTurnout::STATE_BC: {
        testState = LayoutTurnout::STATE_AC;
        break;
    }
 }
 turnAState = layoutSlip->getTurnoutStates().value(testState)->getTestTurnoutAState();
 turnBState = layoutSlip->getTurnoutStates().value(testState)->getTestTurnoutBState();

 if (editLayoutSlipTurnoutAComboBox->getSelectedItem() !=  nullptr) {
     ((Turnout*) editLayoutSlipTurnoutAComboBox->getSelectedItem())->setCommandedState(turnAState);
 }
 if (editLayoutSlipTurnoutBComboBox->getSelectedItem() !=  nullptr) {
     ((Turnout*) editLayoutSlipTurnoutBComboBox->getSelectedItem())->setCommandedState(turnBState);
 }
    if (testPanel !=  nullptr) {
        testPanel->repaint();
    }
}   // togleStateTest

#if 0
class TestState extends QWidget* {

@Override
/*public*/ void paintComponent(Graphics g) {
    super.paintComponent(g);
    if (g instanceof Graphics2D) {
        drawSlipState((Graphics2D) g, testState);
    }
}
}
#endif

/*private*/ void LayoutTrackEditors::editLayoutSlipEditBlockPressed(/*ActionEvent a*/) {
// check if a block name has been entered
 QString newName = editLayoutSlipBlockNameComboBox->getSelectedItemDisplayName();
 if (layoutSlip->getBlockName() !=(newName)) {
     // get new block, or  nullptr if block has been removed
     try {
         layoutSlip->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
     } catch (IllegalArgumentException ex) {
         layoutSlip->setLayoutBlock( nullptr);
     }
     editLayoutSlipNeedsRedraw = true;
     editLayoutSlipNeedsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (layoutSlip->getLayoutBlock() ==  nullptr) {
     JOptionPane::showMessageDialog(editLayoutSlipFrame,
             tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),
             tr("Error"), JOptionPane::ERROR_MESSAGE);
     return;
 }
 layoutSlip->getLayoutBlock()->editLayoutBlock(editLayoutSlipFrame);
 editLayoutSlipNeedsRedraw = true;
 layoutEditor->setDirty();
}   // editLayoutSlipEditBlockPressed(

/*private*/ void LayoutTrackEditors::editLayoutSlipDonePressed(/*ActionEvent a*/) {
 QString newName = editLayoutSlipTurnoutAComboBox->getSelectedItemDisplayName();
 if (layoutSlip->getTurnoutName() != (newName)) {
     if (layoutEditor->validatePhysicalTurnout(newName, editLayoutSlipFrame)) {
         layoutSlip->setTurnout(newName);
     } else {
         layoutSlip->setTurnout("");
     }
     editLayoutSlipNeedsRedraw = true;
 }

 newName = editLayoutSlipTurnoutBComboBox->getSelectedItemDisplayName();
 if (layoutSlip->getTurnoutBName() != (newName)) {
    if (layoutEditor->validatePhysicalTurnout(newName, editLayoutSlipFrame)) {
        layoutSlip->setTurnoutB(newName);
    } else {
        layoutSlip->setTurnoutB("");
    }
    editLayoutSlipNeedsRedraw = true;
 }

 newName = editLayoutSlipBlockNameComboBox->getSelectedItemDisplayName();
 if (layoutSlip->getBlockName() !=(newName)) {
    // get new block, or  nullptr if block has been removed
    try {
        layoutSlip->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
    } catch (IllegalArgumentException ex) {
        layoutSlip->setLayoutBlock( nullptr);
        editLayoutSlipBlockNameComboBox->setSelectedItemByName("");
        editLayoutSlipBlockNameComboBox->setCurrentIndex(-1);
    }
    editLayoutSlipNeedsRedraw = true;
    layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
    editLayoutSlipNeedsBlockUpdate = true;
 }
 for (TurnoutState* ts : layoutSlip->getTurnoutStates().values()) {
     ts->updateStatesFromCombo();
 }

 // set hidden
 bool oldHidden = layoutSlip->isHidden();
 layoutSlip->setHidden(editLayoutSlipHiddenBox->isChecked());
 if (oldHidden != layoutSlip->isHidden()) {
     editLayoutSlipNeedsRedraw = true;
 }

 editLayoutSlipOpen = false;
 editLayoutSlipFrame->setVisible(false);
 editLayoutSlipFrame->dispose();
 editLayoutSlipFrame =  nullptr;
 if (editLayoutSlipNeedsBlockUpdate) {
     layoutSlip->updateBlockInfo();
 }
 if (editLayoutSlipNeedsRedraw) {
     layoutEditor->redrawPanel();
     layoutEditor->setDirty();
     editLayoutSlipNeedsRedraw = false;
 }
}   // editLayoutSlipDonePressed

/*private*/ void LayoutTrackEditors::editLayoutSlipCancelPressed(/*ActionEvent a*/) {
 editLayoutSlipOpen = false;
 editLayoutSlipFrame->setVisible(false);
 editLayoutSlipFrame->dispose();
 editLayoutSlipFrame =  nullptr;
 if (editLayoutSlipNeedsBlockUpdate) {
     layoutSlip->updateBlockInfo();
 }
 if (editLayoutSlipNeedsRedraw) {
     layoutEditor->redrawPanel();
     layoutEditor->setDirty();
     editLayoutSlipNeedsRedraw = false;
 }
}

#if 0
/*===============*\
| Edit Level Xing |
\*===============*/
#endif
/**
* Edit a Level Crossing
*/
/*protected*/ void LayoutTrackEditors::editLevelXing(LevelXing* levelXing) {
#if 1
 sensorList.clear();

 this->levelXing = levelXing;
 if (editLevelXingOpen) {
     editLevelXingFrame->setVisible(true);
 } else // Initialize if needed
 if (editLevelXingFrame ==  nullptr) {
    editLevelXingFrame = new JmriJFrameX(tr("EditXing"), false, true);  // NOI18N
    editLevelXingFrame->addHelpMenu("package.jmri.jmrit.display.EditLevelXing", true);  // NOI18N
    editLevelXingFrame->setLocation(50, 30);
    QWidget* contentPane = editLevelXingFrame->getContentPane();
    contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

    QWidget* panel33 = new QWidget();
    FlowLayout* panel33Layout;
    panel33->setLayout(panel33Layout =new FlowLayout());
    editLevelXingHiddenCheckBox->setToolTip(tr("HiddenToolTip"));  // NOI18N
    panel33Layout->addWidget(editLevelXingHiddenCheckBox);
    contentPane->layout()->addWidget(panel33);

    // setup block 1 name
    QWidget* panel1 = new QWidget();
    FlowLayout* panel1Layout;
    panel1->setLayout(panel1Layout = new FlowLayout());
    QLabel* block1NameLabel = new QLabel(tr("Block %1").arg(1));  // NOI18N
    panel1Layout->addWidget(block1NameLabel);
    panel1Layout->addWidget(editLevelXingBlock1NameComboBox);
     layoutEditor->setupComboBox(editLevelXingBlock1NameComboBox, false, true, true);
    editLevelXingBlock1NameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
    contentPane->layout()->addWidget(panel1);

    // setup block 2 name
    QWidget* panel2 = new QWidget();
    FlowLayout* panel2Layout;
    panel2->setLayout(panel2Layout = new FlowLayout());
    QLabel* block2NameLabel = new QLabel(tr("Block %1").arg(2));  // NOI18N
    panel2Layout->addWidget(block2NameLabel);
    panel2Layout->addWidget(editLevelXingBlock2NameComboBox);
     layoutEditor->setupComboBox(editLevelXingBlock2NameComboBox, false, true, true);
    editLevelXingBlock2NameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
    contentPane->layout()->addWidget(panel2);

    // set up Edit 1 Block and Edit 2 Block buttons
    QWidget* panel4 = new QWidget();
    FlowLayout* panel4Layout;
    panel4->setLayout(panel4Layout = new FlowLayout());
    // Edit 1 Block
    panel4Layout->addWidget(editLevelXingBlock1Button = new QPushButton(tr("Create/Edit Block %1").arg(1)));  // NOI18N
//    editLevelXingBlock1Button.addActionListener((ActionEvent e) -> {
//        editLevelXingBlockACPressed(e);
//    });
    connect(editLevelXingBlock1Button, SIGNAL(clicked(bool)), this, SLOT(editLevelXingBlockACPressed()));
    editLevelXingBlock1Button->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "")); // empty value for block 1  // NOI18N
    // Edit 2 Block
    panel4Layout->addWidget(editLevelXingBlock2Button = new QPushButton(tr("Create/Edit Block %1").arg(2)));  // NOI18N
//    editLevelXingBlock2Button.addActionListener((ActionEvent e) -> {
//        editLevelXingBlockBDPressed(e);
//    });
    connect(editLevelXingBlock2Button, SIGNAL(clicked(bool)), this, SLOT(editLevelXingBlockBDPressed()));

    editLevelXingBlock2Button->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "")); // empty value for block 1  // NOI18N
    contentPane->layout()->addWidget(panel4);
    // set up Done and Cancel buttons
    QWidget* panel5 = new QWidget();
    FlowLayout* panel5Layout;
    panel5->setLayout(panel5Layout = new FlowLayout());
    panel5Layout->addWidget(editLevelXingDoneButton = new QPushButton(tr("ButtonDone")));  // NOI18N
//    editLevelXingDoneButton.addActionListener((ActionEvent e) -> {
//        editLevelXingDonePressed(e);
//    });
    connect(editLevelXingDoneButton, SIGNAL(clicked(bool)), this, SLOT(editLevelXingDonePressed()));
    editLevelXingDoneButton->setToolTip(tr("Click [%1] to accept any changes made above and close this dialog.").arg(tr("Done")));  // NOI18N

    // make this button the default button (return or enter activates)
    // Note: We have to invoke this later because we don't currently have a root pane
//    SwingUtilities.invokeLater(() -> {
//        JRootPane rootPane = SwingUtilities.getRootPane(editLevelXingDoneButton);
//        rootPane.setDefaultButton(editLevelXingDoneButton);
//    });
    editLevelXingDoneButton->setDefault(true);

    // Cancel
    panel5Layout->addWidget(editLevelXingCancelButton = new QPushButton(tr("Cancel")));  // NOI18N
//    editLevelXingCancelButton.addActionListener((ActionEvent e) -> {
//        editLevelXingCancelPressed(e);
//    });
    connect(editLevelXingCancelButton, SIGNAL(clicked(bool)), this, SLOT(editLevelXingCancelPressed()));
    editLevelXingCancelButton->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));  // NOI18N
    contentPane->layout()->addWidget(panel5);
}

 editLevelXingHiddenCheckBox->setChecked(levelXing->isHidden());

 // Set up for Edit
 editLevelXingBlock1NameComboBox->setSelectedItemByName(levelXing->getBlockNameAC());
 editLevelXingBlock2NameComboBox->setSelectedItemByName(levelXing->getBlockNameBD());
 editLevelXingBlock1NameComboBox->setEnabled(!hasNxSensorPairs(levelXing->getLayoutBlockAC()));  // NOI18N
 editLevelXingBlock2NameComboBox->setEnabled(!hasNxSensorPairs(levelXing->getLayoutBlockBD()));  // NOI18N
 editLevelXingFrame->addWindowListener(new LevelXingEditWindowListener(this));
// {
//    @Override
//    /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//        editLevelXingCancelPressed( nullptr);
//    }
// });

 editLevelXingFrame->pack();
 editLevelXingFrame->setVisible(true);
 editLevelXingOpen = true;
 editLevelXingNeedsBlockUpdate = false;

 showSensorMessage();
#endif
}   // editLevelXing

/*private*/ void LayoutTrackEditors::editLevelXingBlockACPressed(/*ActionEvent a*/) {
// check if a block name has been entered
QString newName = editLevelXingBlock1NameComboBox->getSelectedItemDisplayName();
if (levelXing->getBlockNameAC() != (newName)) {
    // get new block, or  nullptr if block has been removed
    if (!newName.isEmpty()) {
        try {
            levelXing->setLayoutBlockAC( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            levelXing->setLayoutBlockAC( nullptr);
            editLevelXingBlock1NameComboBox->setSelectedItemByName("");
            editLevelXingBlock1NameComboBox->setCurrentIndex(-1);
        }
    } else {
        levelXing->setLayoutBlockAC( nullptr);
    }
    editLevelXingNeedsRedraw = true;
     layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
    editLevelXingNeedsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (levelXing->getLayoutBlockAC() ==  nullptr) {
     JOptionPane::showMessageDialog(editLevelXingFrame,
             tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),  // NOI18N
             tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
     return;
 }
 levelXing->getLayoutBlockAC()->editLayoutBlock(editLevelXingFrame);
 editLevelXingNeedsRedraw = true;
}   // editLevelXingBlockACPressed

/*private*/ void LayoutTrackEditors::editLevelXingBlockBDPressed(/*ActionEvent a*/) {
// check if a block name has been entered
QString newName = editLevelXingBlock2NameComboBox->getSelectedItemDisplayName();
if (-1 != editLevelXingBlock2NameComboBox->currentIndex()) {
    newName = editLevelXingBlock2NameComboBox->currentText();
} else {
    newName = (newName !=  nullptr) ? NamedBean::normalizeUserName(newName) : "";
}
if (levelXing->getBlockNameBD() != (newName)) {
    // get new block, or  nullptr if block has been removed
    if (!newName.isEmpty()) {
        try {
            levelXing->setLayoutBlockBD( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            levelXing->setLayoutBlockBD( nullptr);
            editLevelXingBlock2NameComboBox->setSelectedItemByName("");
            editLevelXingBlock2NameComboBox->setCurrentIndex(-1);
        }
    } else {
        levelXing->setLayoutBlockBD( nullptr);
    }
    editLevelXingNeedsRedraw = true;
     layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
    editLevelXingNeedsBlockUpdate = true;
 }
 // check if a block exists to edit
 if (levelXing->getLayoutBlockBD() ==  nullptr) {
     JOptionPane::showMessageDialog(editLevelXingFrame,
             tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),  // NOI18N
             tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
     return;
 }
 levelXing->getLayoutBlockBD()->editLayoutBlock(editLevelXingFrame);
 editLevelXingNeedsRedraw = true;
}   // editLevelXingBlockBDPressed

/*private*/ void LayoutTrackEditors::editLevelXingDonePressed(/*ActionEvent a*/) {
 // check if Blocks changed
 QString newName = editLevelXingBlock1NameComboBox->getSelectedItemDisplayName();
 if (levelXing->getBlockNameAC() != (newName)) {
    // get new block, or  nullptr if block has been removed
    if (!newName.isEmpty()) {
        try {
            levelXing->setLayoutBlockAC( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            levelXing->setLayoutBlockAC( nullptr);
            editLevelXingBlock1NameComboBox->setSelectedItemByName("");
            editLevelXingBlock1NameComboBox->setCurrentIndex(-1);
        }
    } else {
        levelXing->setLayoutBlockAC( nullptr);
    }
    editLevelXingNeedsRedraw = true;
     layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
    editLevelXingNeedsBlockUpdate = true;
 }
 newName = editLevelXingBlock2NameComboBox->getSelectedItemDisplayName();
 if (levelXing->getBlockNameBD() != (newName)) {
    // get new block, or  nullptr if block has been removed
    if (!newName.isEmpty()) {
        try {
            levelXing->setLayoutBlockBD( layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            levelXing->setLayoutBlockBD( nullptr);
            editLevelXingBlock2NameComboBox->setSelectedItemByName("");
            editLevelXingBlock2NameComboBox->setCurrentIndex(-1);
        }
    } else {
        levelXing->setLayoutBlockBD( nullptr);
    }
    editLevelXingNeedsRedraw = true;
     layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
    editLevelXingNeedsBlockUpdate = true;
}

 // set hidden
 bool oldHidden = levelXing->isHidden();
 levelXing->setHidden(editLevelXingHiddenCheckBox->isChecked());
 if (oldHidden != levelXing->isHidden()) {
     editLevelXingNeedsRedraw = true;
 }

 editLevelXingOpen = false;
 editLevelXingFrame->setVisible(false);
 editLevelXingFrame->dispose();
 editLevelXingFrame =  nullptr;
 if (editLevelXingNeedsBlockUpdate) {
     levelXing->updateBlockInfo();
 }
 if (editLevelXingNeedsRedraw) {
      layoutEditor->redrawPanel();
      layoutEditor->setDirty();
     editLevelXingNeedsRedraw = false;
 }
}   // editLevelXingDonePressed

/*private*/ void LayoutTrackEditors::editLevelXingCancelPressed(/*ActionEvent a*/) {
 editLevelXingOpen = false;
 editLevelXingFrame->setVisible(false);
 editLevelXingFrame->dispose();
 editLevelXingFrame =  nullptr;
 if (editLevelXingNeedsBlockUpdate) {
     levelXing->updateBlockInfo();
 }
 if (editLevelXingNeedsRedraw) {
      layoutEditor->redrawPanel();
      layoutEditor->setDirty();
     editLevelXingNeedsRedraw = false;
 }
}

/*==============*\
| Edit Turntable |
\*==============*/

/**
* Edit a Turntable
*/
/*protected*/ void LayoutTrackEditors::editLayoutTurntable(LayoutTurntable* layoutTurntable) {
this->layoutTurntable = layoutTurntable;
#if 1
if (editLayoutTurntableOpen) {
    editLayoutTurntableFrame->setVisible(true);
} else // Initialize if needed
if (editLayoutTurntableFrame ==  nullptr) {
    editLayoutTurntableFrame = new JmriJFrameX(tr("Edit Turntable"), false, true);  // NOI18N
    editLayoutTurntableFrame->addHelpMenu("package.jmri.jmrit.display.EditTurntable", true);  // NOI18N
    editLayoutTurntableFrame->setLocation(50, 30);

    QWidget* contentPane = editLayoutTurntableFrame->getContentPane();
    QWidget* headerPane = new QWidget();
    QWidget* footerPane = new QWidget();
    headerPane->setLayout(new QVBoxLayout());//headerPane, BoxLayout.Y_AXIS));
    footerPane->setLayout(new QVBoxLayout());//footerPane, BoxLayout.Y_AXIS));
    QVBoxLayout* contentPaneLayout;
    contentPane->setLayout(new QVBoxLayout());//BorderLayout());
    contentPaneLayout->addWidget(headerPane, 0, Qt::AlignTop);//BorderLayout.NORTH);
    contentPaneLayout->addWidget(footerPane,0, Qt::AlignBottom);// BorderLayout.SOUTH);

    // setup radius
    QWidget* panel1 = new QWidget();
    FlowLayout* panel1Layout;
    panel1->setLayout(panel1Layout =new FlowLayout());
    QLabel* radiusLabel = new QLabel(tr("TurntableRadius"));  // NOI18N
    panel1Layout->addWidget(radiusLabel);
    panel1Layout->addWidget(editLayoutTurntableRadiusTextField);
    editLayoutTurntableRadiusTextField->setToolTip(tr("TurntableRadiusHint"));  // NOI18N
    headerPane->layout()->addWidget(panel1);

    // setup add ray track
    QWidget* panel2 = new QWidget();
    FlowLayout* panel2Layout;
    panel2->setLayout(panel2Layout = new FlowLayout());
    QLabel* rayAngleLabel = new QLabel(tr("RayAngle"));  // NOI18N
    panel2Layout->addWidget(rayAngleLabel);
    panel2Layout->addWidget(editLayoutTurntableAngleTextField);
    editLayoutTurntableAngleTextField->setToolTip(tr("RayAngleHint"));  // NOI18N
    headerPane->layout()->addWidget(panel2);

    QWidget* panel3 = new QWidget();
    FlowLayout* panel3Layout;
    panel3->setLayout(panel3Layout = new FlowLayout());
    panel3Layout->addWidget(editLayoutTurntableAddRayTrackButton = new QPushButton(tr("AddRayTrack")));  // NOI18N
    editLayoutTurntableAddRayTrackButton->setToolTip(tr("AddRayTrackHint"));  // NOI18N
//    editLayoutTurntableAddRayTrackButton.addActionListener((ActionEvent e) -> {
//        addRayTrackPressed(e);
//        updateRayPanel();
//    });
    connect(editLayoutTurntableAddRayTrackButton, SIGNAL(clicked(bool)), this, SLOT(onEditLayoutTurntableAddRayTrackButton()));
    panel3Layout->addWidget(editLayoutTurntableDccControlledCheckBox = new QCheckBox(tr("DCC Controlled Turntable")));  // NOI18N
    headerPane->layout()->addWidget(panel3);

    // set up Done and Cancel buttons
    QWidget* panel5 = new QWidget();
    FlowLayout* panel5Layout;
    panel5->setLayout(panel5Layout = new FlowLayout());
    panel5Layout->addWidget(editLayoutTurntableDoneButton = new QPushButton(tr("ButtonDone")));  // NOI18N
//    editLayoutTurntableDoneButton.addActionListener((ActionEvent e) -> {
//        editLayoutTurntableDonePressed(e);
//    });
    connect(editLayoutTurntableDoneButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurntableDonePressed()));

    // make this button the default button (return or enter activates)
    // Note: We have to invoke this later because we don't currently have a root pane
//    SwingUtilities.invokeLater(() -> {
//        JRootPane rootPane = SwingUtilities.getRootPane(editLayoutTurntableDoneButton);
//        rootPane.setDefaultButton(editLayoutTurntableDoneButton);
//    });
    editLayoutTurntableDoneButton->setDefault(true);

    editLayoutTurntableDoneButton->setToolTip(tr("Click [{0}] to accept any changes made above and close this dialog.").arg(tr("Done")));  // NOI18N
    // Cancel
    panel5Layout->addWidget(editLayoutTurntableCancelButton = new QPushButton(tr("Cancel")));  // NOI18N
//    editLayoutTurntableCancelButton.addActionListener((ActionEvent e) -> {
//        turntableEditCancelPressed(e);
//    });
    connect(editLayoutTurntableCancelButton, SIGNAL(clicked(bool)), this, SLOT(turntableEditCancelPressed()));
    editLayoutTurntableCancelButton->setToolTip(tr("Click [%1] to dismiss this dialog without making changes.").arg(tr("Cancel")));  // NOI18N
    footerPane->layout()->addWidget(panel5);

    editLayoutTurntableRayPanel = new QWidget();
    editLayoutTurntableRayPanel->setLayout(new QVBoxLayout());//editLayoutTurntableRayPanel, BoxLayout.Y_AXIS));
    QScrollArea* rayScrollPane = new QScrollArea();//editLayoutTurntableRayPanel, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
    rayScrollPane->setWidget(editLayoutTurntableRayPanel);
    rayScrollPane->setWidgetResizable(true);
    contentPaneLayout->addWidget(rayScrollPane, 0, Qt::AlignCenter);//BorderLayout.CENTER);
 }
 editLayoutTurntableDccControlledCheckBox->setChecked(layoutTurntable->isTurnoutControlled());
// editLayoutTurntableDccControlledCheckBox.addActionListener((ActionEvent e) -> {
//     layoutTurntable.setTurnoutControlled(editLayoutTurntableDccControlledCheckBox->isChecked());

//     for (Component comp : editLayoutTurntableRayPanel.getComponents()) {
//         if (comp instanceof TurntableRayPanel) {
//             TurntableRayPanel trp = (TurntableRayPanel) comp;
//             trp.showTurnoutDetails();
//         }
//     }
//     editLayoutTurntableFrame.pack();
// });
 connect(editLayoutTurntableDccControlledCheckBox, SIGNAL(clicked(bool)), this, SLOT(onEditLayoutTurntableDccControlledCheckBox()));
 updateRayPanel();
 // Set up for Edit
 editLayoutTurntableRadiusTextField->setText(" " + QString::number(layoutTurntable->getRadius()));
 editLayoutTurntableOldRadius = editLayoutTurntableRadiusTextField->text();
 editLayoutTurntableAngleTextField->setText("0");
 editLayoutTurntableFrame->addWindowListener(new TurntableEditWindowListener(this));
// {
//     @Override
//     /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//         turntableEditCancelPressed( nullptr);
//     }
// });
 editLayoutTurntableFrame->pack();
 editLayoutTurntableFrame->setVisible(true);
 editLayoutTurntableOpen = true;
#endif
}   // editLayoutTurntable

//Remove old rays and add them back in
/*private*/ void LayoutTrackEditors::updateRayPanel() {
 for (QWidget* comp : editLayoutTurntableRayPanel->findChildren<QWidget*>()) {
     editLayoutTurntableRayPanel->layout()->removeWidget(comp);
 }

 editLayoutTurntableRayPanel->setLayout(new QVBoxLayout());//editLayoutTurntableRayPanel, BoxLayout.Y_AXIS));
 for (RayTrack* rt : layoutTurntable->getRayList()) {
     editLayoutTurntableRayPanel->layout()->addWidget(new TurntableRayPanel(rt, this));
 }
 editLayoutTurntableRayPanel->update();
 editLayoutTurntableRayPanel->repaint();
 editLayoutTurntableFrame->pack();
}

void LayoutTrackEditors::onEditLayoutTurntableAddRayTrackButton()
{
  addRayTrackPressed();
  updateRayPanel();
}
/*private*/ void LayoutTrackEditors::saveRayPanelDetail() {
 for (QWidget* comp : editLayoutTurntableRayPanel->findChildren<QWidget*>()) {
     if (qobject_cast<TurntableRayPanel*>(comp)) {
         TurntableRayPanel* trp = (TurntableRayPanel*) comp;
         trp->updateDetails();
     }
 }
}

void LayoutTrackEditors::onEditLayoutTurntableDccControlledCheckBox()
{
 for (QWidget* comp : editLayoutTurntableRayPanel->findChildren<QWidget*>())
 {
    if (qobject_cast<TurntableRayPanel*>(comp)) {
        TurntableRayPanel* trp = (TurntableRayPanel*) comp;
        trp->showTurnoutDetails();
    }
    editLayoutTurntableFrame->pack();
 }
}

/*private*/ void LayoutTrackEditors::addRayTrackPressed(/*ActionEvent a*/) {
double ang = 0.0;
bool bok;
    ang = editLayoutTurntableAngleTextField->text().toFloat(&bok);
 if(!bok) {
    JOptionPane::showMessageDialog(editLayoutTurntableFrame, tr("Error in entry") + ": "  // NOI18N
            + "angle" + tr("Please reenter or Cancel."), tr("Error"),  // NOI18N
            JOptionPane::ERROR_MESSAGE);
    return;
}
layoutTurntable->addRay(ang);
 layoutEditor->redrawPanel();
 layoutEditor->setDirty();
editLayoutTurntableNeedsRedraw = false;
}

//TODO: find where/when this was used and re-implement or dead-code strip
//note: commented out to fix findbugs
///*private*/ void deleteRayTrackPressed(ActionEvent a) {
//    double ang = 0.0;
//    try {
//        ang = Float.parseFloat(editLayoutTurntableAngleTextField.getText());
//    } catch (Exception e) {
//        JOptionPane.showMessageDialog(editLayoutTurntableFrame, tr("EntryError") + ": "
//                + e + tr("TryAgain"), tr("ErrorTitle"),
//                JOptionPane.ERROR_MESSAGE);
//        return;
//    }
//    // scan rays to find the one to delete
//    LayoutTurntable.RayTrack closest =  nullptr;
//    double bestDel = 360.0;
//    for (LayoutTurntable.RayTrack rt : layoutTurntable.getRayList()) {
//        double del = MathUtil::absDiffAngleDEG(rt.getAngle(), ang);
//        if (del < bestDel) {
//            bestDel = del;
//            closest = rt;
//        }
//    }
//    if (bestDel > 30.0) {
//        JOptionPane.showMessageDialog(editLayoutTurntableFrame, tr("Error13"),
//                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);
//        return;
//    }
//    layoutTurntable.deleteRay(closest);
//}

/*private*/ void LayoutTrackEditors::editLayoutTurntableDonePressed(/*ActionEvent a*/) {
 // check if new radius was entered
 QString str = editLayoutTurntableRadiusTextField->text();
 if (str != (editLayoutTurntableOldRadius)) {
    double rad = 0.0;
    bool bok;
        rad = str.toFloat(&bok);
    if(!bok) {
        JOptionPane::showMessageDialog(editLayoutTurntableFrame, tr("Error in entry") + ": "  // NOI18N
                + "radius" + tr("Please reenter or Cancel."), tr("Error"),  // NOI18N
                JOptionPane::ERROR_MESSAGE);
        return;
    }
    layoutTurntable->setRadius(rad);
    editLayoutTurntableNeedsRedraw = true;
 }
 // clean up
 editLayoutTurntableOpen = false;
 editLayoutTurntableFrame->setVisible(false);
 editLayoutTurntableFrame->dispose();
 editLayoutTurntableFrame =  nullptr;
 saveRayPanelDetail();
 if (editLayoutTurntableNeedsRedraw) {
      layoutEditor->redrawPanel();
      layoutEditor->setDirty();
     editLayoutTurntableNeedsRedraw = false;
 }
}   // editLayoutTurntableDonePressed

/*private*/ void LayoutTrackEditors::turntableEditCancelPressed(/*ActionEvent a*/) {
 editLayoutTurntableOpen = false;
 editLayoutTurntableFrame->setVisible(false);
 editLayoutTurntableFrame->dispose();
 editLayoutTurntableFrame =  nullptr;
 if (editLayoutTurntableNeedsRedraw) {
      layoutEditor->redrawPanel();
      layoutEditor->setDirty();
     editLayoutTurntableNeedsRedraw = false;
 }
}

/*===================*\
| Turntable Ray Panel |
\*===================*/

/**
 * constructor method
 */
/*public*/ TurntableRayPanel::TurntableRayPanel(/*@Non nullptr*/ RayTrack* rayTrack, LayoutTrackEditors *layoutTrackeditors) {
    this->rayTrack = rayTrack;
  rayTurnoutStateValues = QVector<int>() <<Turnout::CLOSED << Turnout::THROWN;
 this->layoutTrackEditors = layoutTrackeditors;
  twoDForm = new DecimalFormat("#.00");

    QWidget* top = new QWidget();
top->setLayout(new QHBoxLayout());
    /*QLabel* lbl = new QLabel("Index :"+connectionIndex);
         top.add(lbl);*/
    top->layout()->addWidget(new QLabel(tr("RayAngle") + " : "));  // NOI18N
    top->layout()->addWidget(rayAngleTextField = new JTextField(5));
//    rayAngleTextField.addFocusListener(new FocusListener() {
//        @Override
//        /*public*/ void focusGained(FocusEvent e) {
//        }

//        @Override
//        /*public*/ void focusLost(FocusEvent e) {
//            try {
//                Float.parseFloat(rayAngleTextField.getText());
//            } catch (Exception ex) {
//                JOptionPane.showMessageDialog(editLayoutTurntableFrame, tr("EntryError") + ": "  // NOI18N
//                        + ex + tr("TryAgain"), tr("ErrorTitle"),  // NOI18N
//                        JOptionPane.ERROR_MESSAGE);
//                return;
//            }
//        }
//    }
//    );
    connect(rayAngleTextField, SIGNAL(editingFinished()), this, SLOT(rayAngleTextFieldEditingFinished()));
    this->setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
    this->layout()->addWidget(top);

    turnoutNameComboBox = new NamedBeanComboBox(
            InstanceManager::turnoutManagerInstance(),
            rayTrack->getTurnout(),
            NamedBean::DisplayOptions::DISPLAYNAME);
     layoutTrackeditors->layoutEditor->setupComboBox(turnoutNameComboBox, false, true, false);
    turnoutNameComboBox->findText(rayTrack->getTurnout()->getDisplayName());

    QString turnoutStateThrown = InstanceManager::turnoutManagerInstance()->getThrownText();
    QString turnoutStateClosed = InstanceManager::turnoutManagerInstance()->getClosedText();
    QStringList turnoutStates = QStringList() << turnoutStateClosed<< turnoutStateThrown;

    rayTurnoutStateComboBox = new QComboBox(/*turnoutStates*/);
    rayTurnoutStateComboBox->addItems(turnoutStates);
    rayTurnoutStateLabel = new QLabel(tr("TurnoutState"));  // NOI18N
    rayTurnoutPanel = new QWidget();

//    rayTurnoutPanel.setBorder(new EtchedBorder());
    rayTurnoutPanel->layout()->addWidget(turnoutNameComboBox);
    rayTurnoutPanel->layout()->addWidget(rayTurnoutStateLabel);
    rayTurnoutPanel->layout()->addWidget(rayTurnoutStateComboBox);
    if (rayTrack->getTurnoutState() == Turnout::CLOSED) {
        //rayTurnoutStateComboBox->setCheckedItem(turnoutStateClosed);
     rayTurnoutStateComboBox->findText(turnoutStateClosed);
    } else {
        rayTurnoutStateComboBox->findText(turnoutStateThrown);
    }
    this->layout()->addWidget(rayTurnoutPanel);

    QPushButton* deleteRayButton;
    top->layout()->addWidget(deleteRayButton = new QPushButton(tr("Delete")));  // NOI18N
    deleteRayButton->setToolTip(tr("Delete Ray Track"));  // NOI18N
//    deleteRayButton.addActionListener((ActionEvent e) -> {
//        delete();
//        updateRayPanel();
//    });
    connect(deleteRayButton, SIGNAL(clicked(bool)), this, SLOT(onDelete()));
//    rayTitledBorder = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));

    //this.setBorder(rayTitledBorder);

    showTurnoutDetails();

    rayAngleTextField->setText(twoDForm->format(rayTrack->getAngle()));
    rayTitledBorder->setTitle(tr("Ray") + " : " + rayTrack->getConnectionIndex());  // NOI18N
    if (rayTrack->getConnect() ==  nullptr) {
        rayTitledBorder->setTitle(tr("Unconnected") + " : " + rayTrack->getConnectionIndex());  // NOI18N
    } else if (rayTrack->getConnect()->getLayoutBlock() !=  nullptr) {
        rayTitledBorder->setTitle(tr("Connected") + " : " + rayTrack->getConnect()->getLayoutBlock()->getDisplayName());  // NOI18N
    }
}

void TurntableRayPanel::rayAngleTextFieldEditingFinished()
{
 bool bok;
     rayAngleTextField->text().toFloat(&bok);
 if(!bok) {
     JOptionPane::showMessageDialog(layoutTrackEditors->editLayoutTurntableFrame, tr("Error in entry") + ": "  // NOI18N
             + "invalid float value" + tr("Please reenter or Cancel."), tr("Error"),  // NOI18N
             JOptionPane::ERROR_MESSAGE);
     return;
 }
}
 void TurntableRayPanel::onDelete()
 {
  _delete();
  layoutTrackEditors->updateRayPanel();

 }
/*private*/ void TurntableRayPanel::_delete() {
    int n = JOptionPane::showConfirmDialog( nullptr,
            tr("Are you sure you want to remove this ray from the turntable, along with any connected Track Segments?"),  // NOI18N
            tr("Warning"),  // NOI18N
            JOptionPane::YES_NO_OPTION);
    if (n == JOptionPane::YES_OPTION) {
        layoutTrackEditors->layoutTurntable->deleteRay(rayTrack);
    }
}

/*private*/ void TurntableRayPanel::updateDetails() {
    if (turnoutNameComboBox ==  nullptr || rayTurnoutStateComboBox ==  nullptr) {
        return;
    }
    rayTrack->setTurnout(turnoutNameComboBox->getSelectedItemDisplayName(), rayTurnoutStateValues[rayTurnoutStateComboBox->currentIndex()]);
    if (rayAngleTextField->text() != (twoDForm->format(rayTrack->getAngle()))) {
        bool bok;
            double ang = rayAngleTextField->text().toFloat(&bok);
            rayTrack->setAngle(ang);
        if(!bok) {
            layoutTrackEditors->log->error("Angle is not in correct format so will skip " + rayAngleTextField->text());  // NOI18N
        }
    }
}

/*private*/ void TurntableRayPanel::showTurnoutDetails() {
    bool vis = layoutTrackEditors->layoutTurntable->isTurnoutControlled();
    rayTurnoutPanel->setVisible(vis);
    turnoutNameComboBox->setVisible(vis);
    rayTurnoutStateComboBox->setVisible(vis);
    rayTurnoutStateLabel->setVisible(vis);
}
//}   // class TurntableRayPanel

/*private*/ /*final*/ /*static*/ Logger* LayoutTrackEditors::log = LoggerFactory::getLogger("LayoutTrackEditors");


