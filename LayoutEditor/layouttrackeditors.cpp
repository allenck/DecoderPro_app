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
 editTrackSegmentHiddenCheckBox = new QCheckBox(tr("HideTrack"));  // NOI18N
 editTrackSegmentBlockNameComboBox = new JmriBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
 editTrackSegmentArcTextField = new JTextField(5);

 editLayoutTurnoutBlockNameComboBox = new JmriBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutBlockBNameComboBox = new JmriBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutBlockCNameComboBox = new JmriBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutBlockDNameComboBox = new JmriBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
 editLayoutTurnoutStateComboBox = new QComboBox();
 editLayoutTurnoutHiddenCheckBox = new QCheckBox(tr("HideTurnout"));  // NOI18N
 editLayoutTurnout2ndTurnoutCheckBox = new QCheckBox(tr("SupportingTurnout"));  // NOI18N
 editLayoutTurnout2ndTurnoutInvertCheckBox = new QCheckBox(tr("SecondTurnoutInvert"));  // NOI18N

 editLayoutSlipHiddenBox = new QCheckBox(tr("HideSlip"));
 editLayoutSlipBlockNameComboBox = new JmriBeanComboBox(static_cast<BlockManager*>(
         InstanceManager::getDefault("BlockManager")),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);

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
            tr("BlockSensorTitle"),  // NOI18N
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
#if 1
    if (editTrackSegmentOpen) {
        editTrackSegmentFrame->setVisible(true);
    } else if (editTrackSegmentFrame ==  nullptr) { // Initialize if needed
        editTrackSegmentFrame = new JmriJFrame(tr("EditTrackSegment"), false, true); // key moved to DisplayBundle to be found by CircuitBuilder.java   // NOI18N
        editTrackSegmentFrame->addHelpMenu("package.jmri.jmrit.display.EditTrackSegment", true);  // NOI18N
        editTrackSegmentFrame->setLocation(50, 30);
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
        editTrackSegmentHiddenCheckBox->setToolTip(tr("HiddenToolTip"));  // NOI18N
        panel33Layout->addWidget(editTrackSegmentHiddenCheckBox);
        contentPane->layout()->addWidget(panel33);

        // setup block name
        QWidget* panel2 = new QWidget();
        FlowLayout* panel2Layout;
        panel2->setLayout(panel2Layout = new FlowLayout());
        QLabel* blockNameLabel = new QLabel(tr("BlockID"));  // NOI18N
        panel2Layout->addWidget(blockNameLabel);
        LayoutEditor::setupComboBox(editTrackSegmentBlockNameComboBox, false, true);
        editTrackSegmentBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
        panel2Layout->addWidget(editTrackSegmentBlockNameComboBox);

        contentPane->layout()->addWidget(panel2);

        QWidget* panel20 = new QWidget();
        FlowLayout* panel20Layout;
        panel20->setLayout(panel20Layout = new FlowLayout());
        QLabel* arcLabel = new QLabel(tr("Set Arc Angle"));  // NOI18N
        panel20Layout->addWidget(arcLabel);
        panel20Layout->addWidget(editTrackSegmentArcTextField);
        editTrackSegmentArcTextField->setToolTip(tr("SetArcAngleHint"));  // NOI18N
        contentPane->layout()->addWidget(panel20);

        // set up Edit Block, Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        FlowLayout* panel5Layout;
        panel5->setLayout(panel5Layout = new FlowLayout());

        // Edit Block
        panel5Layout->addWidget(editTrackSegmentSegmentEditBlockButton = new QPushButton(tr("Create/Edit Block {%1").arg("")));  // NOI18N
//        editTrackSegmentSegmentEditBlockButton.addActionListener((ActionEvent e) -> {
//            editTrackSegmentEditBlockPressed(e);
//        });
        connect(editTrackSegmentSegmentEditBlockButton, SIGNAL(clicked(bool)), this, SLOT(editTrackSegmentEditBlockPressed()));
        editTrackSegmentSegmentEditBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.").arg("")); // empty value for block 1  // NOI18N
        panel5Layout->addWidget(editTrackSegmentSegmentEditDoneButton = new QPushButton(tr("ButtonDone")));  // NOI18N
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
    editTrackSegmentBlockNameComboBox->setText(trackSegment->getBlockName());
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
#endif

}   // editTrackSegment
#if 1
//@InvokeOnGuiThread
/*private*/ void LayoutTrackEditors::editTrackSegmentEditBlockPressed(/*ActionEvent a*/) {
    // check if a block name has been entered
    QString newName = editTrackSegmentBlockNameComboBox->getUserName();
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
    QString newName = editTrackSegmentBlockNameComboBox->getUserName();
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
#endif
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
        editLayoutTurnoutFrame = new JmriJFrame(tr("EditTurnout"), false, true);  // NOI18N
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
        editLayoutTurnout1stTurnoutComboBox = new JmriBeanComboBox(
                InstanceManager::turnoutManagerInstance(),
                layoutTurnout->getTurnout(),
                JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
         layoutEditor->setupComboBox(editLayoutTurnout1stTurnoutComboBox, true, true);
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
        editLayoutTurnout1stTurnoutComboBox->addPopupMenuListener(pml = new TurnoutPopupMenuListener(this));
        editLayoutTurnout1stTurnoutComboBox->setEnabledColor(Qt::darkGreen);
        editLayoutTurnout1stTurnoutComboBox->setDisabledColor(Qt::red);

        panel1Layout->addWidget(editLayoutTurnout1stTurnoutComboBox);
        contentPane->layout()->addWidget(panel1);

        QWidget* panel1a = new QWidget();
        QVBoxLayout* panel1aLayout;
        panel1a->setLayout(panel1aLayout = new QVBoxLayout());//panel1a, BoxLayout.Y_AXIS));

        editLayoutTurnout2ndTurnoutComboBox = new JmriBeanComboBox(
                InstanceManager::turnoutManagerInstance(),
                layoutTurnout->getSecondTurnout(),
                JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
         layoutEditor->setupComboBox(editLayoutTurnout2ndTurnoutComboBox, true, false);

        editLayoutTurnout2ndTurnoutComboBox->addPopupMenuListener(pml);
        editLayoutTurnout2ndTurnoutComboBox->setEnabledColor(Qt::darkGreen);
        editLayoutTurnout2ndTurnoutComboBox->setDisabledColor(Qt::red);

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
//        border.setTitle(tr("BeanNameBlock"));  // NOI18N
        // setup block name
        QGroupBox* panel2 = new QGroupBox();
        //panel2.setBorder(border);
        panel2->setTitle(tr("Block"));
        FlowLayout* panel2Layout;
        panel2->setLayout(panel2Layout = new FlowLayout());
        panel2Layout->addWidget(editLayoutTurnoutBlockNameComboBox);
         layoutEditor->setupComboBox(editLayoutTurnoutBlockNameComboBox, false, true);
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
             layoutEditor->setupComboBox(editLayoutTurnoutBlockBNameComboBox, false, true);
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
             layoutEditor->setupComboBox(editLayoutTurnoutBlockCNameComboBox, false, true);
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
             layoutEditor->setupComboBox(editLayoutTurnoutBlockDNameComboBox, false, true);
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
        editLayoutTurnoutDoneButton->setToolTip(tr("DoneHint %1").arg(tr("Done")));  // NOI18N
        // Cancel
        panel5Layout->addWidget(editLayoutTurnoutCancelButton = new QPushButton(tr("ButtonCancel")));  // NOI18N
//        editLayoutTurnoutCancelButton.addActionListener((ActionEvent e) -> {
//            editLayoutTurnoutCancelPressed(e);
//        });
        connect(editLayoutTurnoutCancelButton, SIGNAL(clicked(bool)), this, SLOT(editLayoutTurnoutCancelPressed()));
        editLayoutTurnoutCancelButton->setToolTip(tr("Click %1 to dismiss this dialog without making changes.").arg(tr("Cancel")));  // NOI18N
        contentPane->layout()->addWidget(panel5);
    }

    editLayoutTurnout1stTurnoutComboBox->setText(layoutTurnout->getTurnoutName());

    editLayoutTurnoutHiddenCheckBox->setChecked(layoutTurnout->isHidden());

    // Set up for Edit
    editLayoutTurnoutBlockNameComboBox->setText(layoutTurnout->getBlockName());
    editLayoutTurnoutBlockNameComboBox->setEnabled(!hasNxSensorPairs(layoutTurnout->getLayoutBlock()));
    if ((layoutTurnout->getTurnoutType() == LayoutTurnout::DOUBLE_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::RH_XOVER)
            || (layoutTurnout->getTurnoutType() == LayoutTurnout::LH_XOVER)) {
        editLayoutTurnoutBlockBNameComboBox->setText(layoutTurnout->getBlockBName());
        editLayoutTurnoutBlockCNameComboBox->setText(layoutTurnout->getBlockCName());
        editLayoutTurnoutBlockDNameComboBox->setText(layoutTurnout->getBlockDName());
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
        editLayoutTurnout2ndTurnoutComboBox->setText(layoutTurnout->getSecondTurnoutName());
    } else {
        editLayoutTurnout2ndTurnoutInvertCheckBox->setChecked(false);
        editLayoutTurnout2ndTurnoutComboBox->setText("");
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
    QString newName = editLayoutTurnoutBlockNameComboBox->getUserName();
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
    QString newName = editLayoutTurnoutBlockBNameComboBox->getUserName();
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
    QString newName = editLayoutTurnoutBlockCNameComboBox->getUserName();
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
    QString newName = editLayoutTurnoutBlockDNameComboBox->getUserName();
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
    QString newName = editLayoutTurnout1stTurnoutComboBox->getDisplayName();
    if (layoutTurnout->getTurnoutName() != (newName)) {
        // turnout has changed
        if ( layoutEditor->validatePhysicalTurnout(
                newName, editLayoutTurnoutFrame)) {
            layoutTurnout->setTurnout(newName);
        } else {
            layoutTurnout->setTurnout( nullptr);
            editLayoutTurnout1stTurnoutComboBox->setText("");
        }
        editLayoutTurnoutNeedRedraw = true;
    }

    if (editLayoutTurnout2ndTurnoutCheckBox->isChecked()) {
        newName = editLayoutTurnout2ndTurnoutComboBox->getDisplayName();
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
                    editLayoutTurnout2ndTurnoutComboBox->setText("");
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
    newName = editLayoutTurnoutBlockNameComboBox->getUserName();
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
        newName = editLayoutTurnoutBlockBNameComboBox->getUserName();
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
        newName = editLayoutTurnoutBlockCNameComboBox->getUserName();
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
        newName = editLayoutTurnoutBlockDNameComboBox->getUserName();
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
/*protected*/ void LayoutTrackEditors::editLayoutSlip(LayoutSlip* layoutSlip) {
    sensorList.clear();

    this->layoutSlip = layoutSlip;
    if (editLayoutSlipOpen) {
        editLayoutSlipFrame->setVisible(true);
    } else if (editLayoutSlipFrame ==  nullptr) {   // Initialize if needed
        editLayoutSlipFrame = new JmriJFrame(tr("EditSlip"), false, true);  // NOI18N
        editLayoutSlipFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutSlip", true);  // NOI18N
        editLayoutSlipFrame->setLocation(50, 30);

        QWidget* contentPane = editLayoutSlipFrame->getContentPane();
        contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

        QWidget* panel1 = new QWidget();
        panel1->setLayout(new FlowLayout());
        QLabel* turnoutNameLabel = new QLabel(tr("BeanNameTurnout") + " A " + tr("Name"));  // NOI18N
        panel1->layout()->addWidget(turnoutNameLabel);
        editLayoutSlipTurnoutAComboBox = new JmriBeanComboBox(
                InstanceManager::turnoutManagerInstance(),
                layoutSlip->getTurnout(),
                JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
        LayoutEditor::setupComboBox(editLayoutSlipTurnoutAComboBox, true, true);

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

        editLayoutSlipTurnoutAComboBox->addPopupMenuListener(pml);
        editLayoutSlipTurnoutAComboBox->setEnabledColor(QColor(Qt::darkGreen));
        editLayoutSlipTurnoutAComboBox->setDisabledColor(QColor(Qt::red));

        panel1->layout()->addWidget(editLayoutSlipTurnoutAComboBox);
        contentPane->layout()->addWidget(panel1);

        QWidget* panel1a = new QWidget();
        panel1a->setLayout(new FlowLayout());
        QLabel* turnoutBNameLabel = new QLabel(tr("BeanNameTurnout") + " B " + tr("Name"));  // NOI18N
        panel1a->layout()->addWidget(turnoutBNameLabel);

        editLayoutSlipTurnoutBComboBox = new JmriBeanComboBox(
                InstanceManager::turnoutManagerInstance(),
                layoutSlip->getTurnoutB(),
                JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
        LayoutEditor::setupComboBox(editLayoutSlipTurnoutBComboBox, true, true);

        editLayoutSlipTurnoutBComboBox->addPopupMenuListener(pml);
        editLayoutSlipTurnoutBComboBox->setEnabledColor(QColor(Qt::darkGreen));
        editLayoutSlipTurnoutBComboBox->setDisabledColor(QColor(Qt::red));

        panel1a->layout()->addWidget(editLayoutSlipTurnoutBComboBox);

        contentPane->layout()->addWidget(panel1a);

        QWidget* panel2 = new QWidget();
        QGridLayout* panel2Layout;
        panel2->setLayout(panel2Layout = new QGridLayout()); //GridLayout(0, 3, 2, 2));

        panel2Layout->addWidget(new QLabel("   "),0, 0, 1, 1);
        panel2Layout->addWidget(new QLabel(tr("Turnout") + " A:"),0, 1, 1,1);  // NOI18N
        panel2Layout->addWidget(new QLabel(tr("Turnout") + " B:"), 0,2, 1,1);  // NOI18N
        //for (Map.Entry<Integer, LayoutSlip.TurnoutState> ts : layoutSlip.getTurnoutStates().entrySet())
        QHashIterator<int, TurnoutState*> entry(layoutSlip->getTurnoutStates());
        while(entry.hasNext())
        {
         entry.hasNext();
#if 0
            SampleStates draw = new SampleStates(ts.getKey());
            draw.repaint();
            draw.setPreferredSize(new Dimension(40, 40));
            panel2.add(draw);

            panel2.add(ts.getValue().getComboA());
            panel2.add(ts.getValue().getComboB());
#endif
        }
#if 0
        testPanel = new TestState();
        testPanel.setSize(40, 40);
        testPanel.setPreferredSize(new Dimension(40, 40));
        panel2.add(testPanel);
        QPushButton* testButton = new QPushButton("Test");  // NOI18N
        testButton.addActionListener((ActionEvent e) -> {
            toggleStateTest();
        });
        panel2.add(testButton);
        contentPane->layout()->addWidget(panel2);

        QWidget* panel33 = new QWidget();
        panel33.setLayout(new FlowLayout());
        editLayoutSlipHiddenBox->setToolTip(tr("HiddenToolTip"));  // NOI18N
        panel33.add(editLayoutSlipHiddenBox);
        contentPane->layout()->addWidget(panel33);

        // setup block name
        QWidget* panel3 = new QWidget();
        panel3.setLayout(new FlowLayout());
        QLabel* block1NameLabel = new QLabel(tr("BlockID"));  // NOI18N
        panel3.add(block1NameLabel);
        panel3.add(editLayoutSlipBlockNameComboBox);
         layoutEditor->setupComboBox(editLayoutSlipBlockNameComboBox, false, true);
        editLayoutSlipBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N

        contentPane->layout()->addWidget(panel3);
        // set up Edit Block buttons
        QWidget* panel4 = new QWidget();
        panel4.setLayout(new FlowLayout());
        // Edit Block
        panel4.add(editLayoutSlipBlockButton = new QPushButton(tr("EditBlock", "")));  // NOI18N
        editLayoutSlipBlockButton.addActionListener(
                (ActionEvent event) -> {
                    editLayoutSlipEditBlockPressed(event);
                }
        );
        editLayoutSlipBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "")); // empty value for block 1  // NOI18N

        contentPane->layout()->addWidget(panel4);
        // set up Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        panel5.setLayout(new FlowLayout());
        panel5Layout->addWidget(editLayoutSlipDoneButton = new QPushButton(tr("Done")));  // NOI18N

        // make this button the default button (return or enter activates)
        // Note: We have to invoke this later because we don't currently have a root pane
        SwingUtilities.invokeLater(() -> {
            JRootPane rootPane = SwingUtilities.getRootPane(editLayoutSlipDoneButton);
            rootPane.setDefaultButton(editLayoutSlipDoneButton);
        }
        );

        editLayoutSlipDoneButton.addActionListener((ActionEvent event) -> {
            editLayoutSlipDonePressed(event);
        });
        editLayoutSlipDoneButton->setToolTip(tr("DoneHint", tr("ButtonDone")));  // NOI18N
        // Cancel
        panel5Layout->addWidget(editLayoutSlipCancelButton = new QPushButton(tr("ButtonCancel")));  // NOI18N
        editLayoutSlipCancelButton.addActionListener((ActionEvent event) -> {
            editLayoutSlipCancelPressed(event);
        });
        editLayoutSlipCancelButton->setToolTip(tr("CancelHint", tr("ButtonCancel")));  // NOI18N
        contentPane->layout()->addWidget(panel5);
#endif
    }

    editLayoutSlipHiddenBox->setChecked(layoutSlip->isHidden());

    // Set up for Edit
    editLayoutSlipTurnoutAComboBox->setText(layoutSlip->getTurnoutName());
    editLayoutSlipTurnoutBComboBox->setText(layoutSlip->getTurnoutBName());
    editLayoutSlipBlockNameComboBox->setText(layoutSlip->getBlockName());
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
     this->layoutTrackEditors = layoutTrackEditors;
    }

    /*public*/ void SlipPopupMenuListener::popupMenuWillBecomeVisible(/*PopupMenuEvent e*/) {
        // This method is called before the popup menu becomes visible.
        layoutTrackEditors->log->debug("PopupMenuWillBecomeVisible");  // NOI18N
        QObject* o = sender();//e.getSource();
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
#if 0
                    jbcb->setItemEnabled(idx++, layoutTrackEditors->layoutEditor->validatePhysicalTurnout(systemName,  nullptr));
#endif
                }
            }
        }
    }

    //@Override
    /*public*/ void SlipPopupMenuListener::popupMenuWillBecomeInvisible(/*PopupMenuEvent e*/) {
        // This method is called before the popup menu becomes invisible
        layoutTrackEditors->log->debug("PopupMenuWillBecomeInvisible");  // NOI18N
    }

    //@Override
    /*public*/ void SlipPopupMenuListener::popupMenuCanceled(/*PopupMenuEvent e*/) {
        // This method is called when the popup menu is canceled
        layoutTrackEditors->log->debug("PopupMenuCanceled");  // NOI18N
    }
//};
#if 0
/*private*/ void SlipPopupMenuListener::drawSlipState(EditScene* g2, int state) {
    QPointF cenP = layoutSlip.getCoordsCenter();
    QPointF A = MathUtil::subtract(layoutSlip.getCoordsA(), cenP);
    QPointF B = MathUtil::subtract(layoutSlip.getCoordsB(), cenP);
    QPointF C = MathUtil::subtract(layoutSlip.getCoordsC(), cenP);
    QPointF D = MathUtil::subtract(layoutSlip.getCoordsD(), cenP);

    QPointF ctrP = new QPointF.Double(20.0, 20.0);
    A = MathUtil::add(MathUtil::normalize(A, 18.0), ctrP);
    B = MathUtil::add(MathUtil::normalize(B, 18.0), ctrP);
    C = MathUtil::add(MathUtil::normalize(C, 18.0), ctrP);
    D = MathUtil::add(MathUtil::normalize(D, 18.0), ctrP);

    g2.setColor(Color.black);
    g2.setStroke(new BasicStroke(2, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND));

    g2.draw(new Line2D.Double(A, MathUtil::oneThirdPoint(A, C)));
    g2.draw(new Line2D.Double(C, MathUtil::oneThirdPoint(C, A)));

    if (state == LayoutTurnout::STATE_AC || state == LayoutTurnout::STATE_BD || state == LayoutTurnout::UNKNOWN) {
        g2.draw(new Line2D.Double(A, MathUtil::oneThirdPoint(A, D)));
        g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, A)));

        if (layoutSlip.getSlipType() == LayoutTurnout::DOUBLE_SLIP) {
            g2.draw(new Line2D.Double(B, MathUtil::oneThirdPoint(B, C)));
            g2.draw(new Line2D.Double(C, MathUtil::oneThirdPoint(C, B)));
        }
    } else {
        g2.draw(new Line2D.Double(B, MathUtil::oneThirdPoint(B, D)));
        g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, B)));
    }

    if (layoutSlip.getSlipType() == LayoutTurnout::DOUBLE_SLIP) {
        if (state == LayoutTurnout::STATE_AC) {
            g2.draw(new Line2D.Double(B, MathUtil::oneThirdPoint(B, D)));
            g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, B)));

            g2.setColor(Color.red);
            g2.draw(new Line2D.Double(A, C));
        } else if (state == LayoutTurnout::STATE_BD) {
            g2.setColor(Color.red);
            g2.draw(new Line2D.Double(B, D));
        } else if (state == LayoutTurnout::STATE_AD) {
            g2.draw(new Line2D.Double(B, MathUtil::oneThirdPoint(B, C)));

            g2.draw(new Line2D.Double(C, MathUtil::oneThirdPoint(C, B)));

            g2.setColor(Color.red);
            g2.draw(new Line2D.Double(A, D));
        } else if (state == LayoutTurnout::STATE_BC) {
            g2.draw(new Line2D.Double(A, MathUtil::oneThirdPoint(A, D)));

            g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, A)));
            g2.setColor(Color.red);
            g2.draw(new Line2D.Double(B, C));
        } else {
            g2.draw(new Line2D.Double(B, MathUtil::oneThirdPoint(B, D)));
            g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, B)));
        }
    } else {
        g2.draw(new Line2D.Double(A, MathUtil::oneThirdPoint(A, D)));
        g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, A)));

        if (state == LayoutTurnout::STATE_AD) {
            g2.setColor(Color.red);
            g2.draw(new Line2D.Double(A, D));
        } else if (state == LayoutTurnout::STATE_AC) {
            g2.draw(new Line2D.Double(B, MathUtil::oneThirdPoint(B, D)));
            g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, B)));

            g2.setColor(Color.red);
            g2.draw(new Line2D.Double(A, C));
        } else if (state == LayoutTurnout::STATE_BD) {
            g2.setColor(Color.red);
            g2.draw(new Line2D.Double(B, D));
        } else {
            g2.draw(new Line2D.Double(B, MathUtil::oneThirdPoint(B, D)));
            g2.draw(new Line2D.Double(D, MathUtil::oneThirdPoint(D, B)));
        }
    }
}   // drawSlipState

class SampleStates extends QWidget* {

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

    if (editLayoutSlipTurnoutAComboBox->getSelectedBean() !=  nullptr) {
        ((Turnout*) editLayoutSlipTurnoutAComboBox->getSelectedBean())->setCommandedState(turnAState);
    }
    if (editLayoutSlipTurnoutBComboBox->getSelectedBean() !=  nullptr) {
        ((Turnout*) editLayoutSlipTurnoutBComboBox->getSelectedBean())->setCommandedState(turnBState);
    }
//    if (testPanel !=  nullptr) {
//        testPanel->repaint();
//    }
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
    QString newName = editLayoutSlipBlockNameComboBox->getUserName();
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
    QString newName = editLayoutSlipTurnoutAComboBox->getDisplayName();
    if (layoutSlip->getTurnoutName() != (newName)) {
        if (layoutEditor->validatePhysicalTurnout(newName, editLayoutSlipFrame)) {
            layoutSlip->setTurnout(newName);
        } else {
            layoutSlip->setTurnout("");
        }
        editLayoutSlipNeedsRedraw = true;
    }

    newName = editLayoutSlipTurnoutBComboBox->getDisplayName();
    if (layoutSlip->getTurnoutBName() != (newName)) {
        if (layoutEditor->validatePhysicalTurnout(newName, editLayoutSlipFrame)) {
            layoutSlip->setTurnoutB(newName);
        } else {
            layoutSlip->setTurnoutB("");
        }
        editLayoutSlipNeedsRedraw = true;
    }

    newName = editLayoutSlipBlockNameComboBox->getUserName();
    if (layoutSlip->getBlockName() !=(newName)) {
        // get new block, or  nullptr if block has been removed
        try {
            layoutSlip->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
        } catch (IllegalArgumentException ex) {
            layoutSlip->setLayoutBlock( nullptr);
            editLayoutSlipBlockNameComboBox->setText("");
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
// variables for Edit Track Segment pane
/*private*/ LevelXing levelXing;

// variables for Edit Level Crossing pane
/*private*/ JmriJFrame* editLevelXingFrame =  nullptr;
/*private*/ QCheckBox* editLevelXingHiddenCheckBox = new JCheckBox(tr("HideCrossing"));  // NOI18N

/*private*/ JmriBeanComboBox* editLevelXingBlock1NameComboBox = new JmriBeanComboBox(
        InstanceManager::getDefault(BlockManager.class),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
/*private*/ JmriBeanComboBox* editLevelXingBlock2NameComboBox = new JmriBeanComboBox(
        InstanceManager::getDefault(BlockManager.class),  nullptr, JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
/*private*/ QPushButton* editLevelXingDoneButton;
/*private*/ QPushButton* editLevelXingCancelButton;
/*private*/ QPushButton* editLevelXingBlock1Button;
/*private*/ QPushButton* editLevelXingBlock2Button;

/*private*/ bool editLevelXingOpen = false;
/*private*/ bool editLevelXingNeedsRedraw = false;
/*private*/ bool editLevelXingNeedsBlockUpdate = false;
#endif
/**
 * Edit a Level Crossing
 */
/*protected*/ void LayoutTrackEditors::editLevelXing(LevelXing* levelXing) {
#if 0
    sensorList.clear();

    this.levelXing = levelXing;
    if (editLevelXingOpen) {
        editLevelXingFrame->setVisible(true);
    } else // Initialize if needed
    if (editLevelXingFrame ==  nullptr) {
        editLevelXingFrame = new JmriJFrame(tr("EditXing"), false, true);  // NOI18N
        editLevelXingFrame.addHelpMenu("package.jmri.jmrit.display.EditLevelXing", true);  // NOI18N
        editLevelXingFrame.setLocation(50, 30);
        Container contentPane = editLevelXingFrame.getContentPane();
        contentPane.setLayout(new BoxLayout(contentPane, BoxLayout.Y_AXIS));

        QWidget* panel33 = new QWidget();
        panel33.setLayout(new FlowLayout());
        editLevelXingHiddenCheckBox->setToolTip(tr("HiddenToolTip"));  // NOI18N
        panel33.add(editLevelXingHiddenCheckBox);
        contentPane->layout()->addWidget(panel33);

        // setup block 1 name
        QWidget* panel1 = new QWidget();
        panel1.setLayout(new FlowLayout());
        QLabel* block1NameLabel = new QLabel(tr("Block_ID", 1));  // NOI18N
        panel1.add(block1NameLabel);
        panel1.add(editLevelXingBlock1NameComboBox);
         layoutEditor->setupComboBox(editLevelXingBlock1NameComboBox, false, true);
        editLevelXingBlock1NameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
        contentPane->layout()->addWidget(panel1);

        // setup block 2 name
        QWidget* panel2 = new QWidget();
        panel2.setLayout(new FlowLayout());
        QLabel* block2NameLabel = new QLabel(tr("Block_ID", 2));  // NOI18N
        panel2.add(block2NameLabel);
        panel2.add(editLevelXingBlock2NameComboBox);
         layoutEditor->setupComboBox(editLevelXingBlock2NameComboBox, false, true);
        editLevelXingBlock2NameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
        contentPane->layout()->addWidget(panel2);

        // set up Edit 1 Block and Edit 2 Block buttons
        QWidget* panel4 = new QWidget();
        panel4.setLayout(new FlowLayout());
        // Edit 1 Block
        panel4.add(editLevelXingBlock1Button = new QPushButton(tr("EditBlock", 1)));  // NOI18N
        editLevelXingBlock1Button.addActionListener((ActionEvent e) -> {
            editLevelXingBlockACPressed(e);
        });
        editLevelXingBlock1Button->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "")); // empty value for block 1  // NOI18N
        // Edit 2 Block
        panel4.add(editLevelXingBlock2Button = new QPushButton(tr("EditBlock", 2)));  // NOI18N
        editLevelXingBlock2Button.addActionListener((ActionEvent e) -> {
            editLevelXingBlockBDPressed(e);
        });
        editLevelXingBlock2Button->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "")); // empty value for block 1  // NOI18N
        contentPane->layout()->addWidget(panel4);
        // set up Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        panel5.setLayout(new FlowLayout());
        panel5Layout->addWidget(editLevelXingDoneButton = new QPushButton(tr("ButtonDone")));  // NOI18N
        editLevelXingDoneButton.addActionListener((ActionEvent e) -> {
            editLevelXingDonePressed(e);
        });
        editLevelXingDoneButton->setToolTip(tr("DoneHint", tr("ButtonDone")));  // NOI18N

        // make this button the default button (return or enter activates)
        // Note: We have to invoke this later because we don't currently have a root pane
        SwingUtilities.invokeLater(() -> {
            JRootPane rootPane = SwingUtilities.getRootPane(editLevelXingDoneButton);
            rootPane.setDefaultButton(editLevelXingDoneButton);
        });

        // Cancel
        panel5Layout->addWidget(editLevelXingCancelButton = new QPushButton(tr("ButtonCancel")));  // NOI18N
        editLevelXingCancelButton.addActionListener((ActionEvent e) -> {
            editLevelXingCancelPressed(e);
        });
        editLevelXingCancelButton->setToolTip(tr("CancelHint", tr("ButtonCancel")));  // NOI18N
        contentPane->layout()->addWidget(panel5);
    }

    editLevelXingHiddenCheckBox->setChecked(levelXing.isHidden());

    // Set up for Edit
    editLevelXingBlock1NameComboBox->setText(levelXing.getBlockNameAC());
    editLevelXingBlock2NameComboBox->setText(levelXing.getBlockNameBD());
    editLevelXingBlock1NameComboBox->setEnabled(!hasNxSensorPairs(levelXing.getLayoutBlockAC()));  // NOI18N
    editLevelXingBlock2NameComboBox->setEnabled(!hasNxSensorPairs(levelXing.getLayoutBlockBD()));  // NOI18N
    editLevelXingFrame.addWindowListener(new java.awt.event.WindowAdapter() {
        @Override
        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
            editLevelXingCancelPressed( nullptr);
        }
    });
    editLevelXingFrame.pack();
    editLevelXingFrame->setVisible(true);
    editLevelXingOpen = true;
    editLevelXingNeedsBlockUpdate = false;

    showSensorMessage();
#endif
}   // editLevelXing
#if 0
/*private*/ void editLevelXingBlockACPressed(ActionEvent a) {
    // check if a block name has been entered
    String newName = editLevelXingBlock1NameComboBox.getUserName();
    if (!levelXing.getBlockNameAC() == (newName)) {
        // get new block, or  nullptr if block has been removed
        if (!newName.isEmpty()) {
            try {
                levelXing.setLayoutBlockAC( layoutEditor->provideLayoutBlock(newName));
            } catch (IllegalArgumentException ex) {
                levelXing.setLayoutBlockAC( nullptr);
                editLevelXingBlock1NameComboBox->setText("");
                editLevelXingBlock1NameComboBox->setCurrentIndex(-1);
            }
        } else {
            levelXing.setLayoutBlockAC( nullptr);
        }
        editLevelXingNeedsRedraw = true;
         layoutEditor->getLEAuxTools().setBlockConnectivityChanged();
        editLevelXingNeedsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (levelXing.getLayoutBlockAC() ==  nullptr) {
        JOptionPane.showMessageDialog(editLevelXingFrame,
                tr("Error1"),  // NOI18N
                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);  // NOI18N
        return;
    }
    levelXing.getLayoutBlockAC().editLayoutBlock(editLevelXingFrame);
    editLevelXingNeedsRedraw = true;
}   // editLevelXingBlockACPressed

/*private*/ void editLevelXingBlockBDPressed(ActionEvent a) {
    // check if a block name has been entered
    String newName = editLevelXingBlock2NameComboBox.getUserName();
    if (-1 != editLevelXingBlock2NameComboBox->currentIndex()) {
        newName = editLevelXingBlock2NameComboBox.getSelectedDisplayName();
    } else {
        newName = (newName !=  nullptr) ? NamedBean.normalizeUserName(newName) : "";
    }
    if (!levelXing.getBlockNameBD() == (newName)) {
        // get new block, or  nullptr if block has been removed
        if (!newName.isEmpty()) {
            try {
                levelXing.setLayoutBlockBD( layoutEditor->provideLayoutBlock(newName));
            } catch (IllegalArgumentException ex) {
                levelXing.setLayoutBlockBD( nullptr);
                editLevelXingBlock2NameComboBox->setText("");
                editLevelXingBlock2NameComboBox->setCurrentIndex(-1);
            }
        } else {
            levelXing.setLayoutBlockBD( nullptr);
        }
        editLevelXingNeedsRedraw = true;
         layoutEditor->getLEAuxTools().setBlockConnectivityChanged();
        editLevelXingNeedsBlockUpdate = true;
    }
    // check if a block exists to edit
    if (levelXing.getLayoutBlockBD() ==  nullptr) {
        JOptionPane.showMessageDialog(editLevelXingFrame,
                tr("Error1"),  // NOI18N
                tr("ErrorTitle"), JOptionPane.ERROR_MESSAGE);  // NOI18N
        return;
    }
    levelXing.getLayoutBlockBD().editLayoutBlock(editLevelXingFrame);
    editLevelXingNeedsRedraw = true;
}   // editLevelXingBlockBDPressed

/*private*/ void editLevelXingDonePressed(ActionEvent a) {
    // check if Blocks changed
    String newName = editLevelXingBlock1NameComboBox.getUserName();
    if (!levelXing.getBlockNameAC() == (newName)) {
        // get new block, or  nullptr if block has been removed
        if (!newName.isEmpty()) {
            try {
                levelXing.setLayoutBlockAC( layoutEditor->provideLayoutBlock(newName));
            } catch (IllegalArgumentException ex) {
                levelXing.setLayoutBlockAC( nullptr);
                editLevelXingBlock1NameComboBox->setText("");
                editLevelXingBlock1NameComboBox->setCurrentIndex(-1);
            }
        } else {
            levelXing.setLayoutBlockAC( nullptr);
        }
        editLevelXingNeedsRedraw = true;
         layoutEditor->getLEAuxTools().setBlockConnectivityChanged();
        editLevelXingNeedsBlockUpdate = true;
    }
    newName = editLevelXingBlock2NameComboBox.getUserName();
    if (!levelXing.getBlockNameBD() == (newName)) {
        // get new block, or  nullptr if block has been removed
        if (!newName.isEmpty()) {
            try {
                levelXing.setLayoutBlockBD( layoutEditor->provideLayoutBlock(newName));
            } catch (IllegalArgumentException ex) {
                levelXing.setLayoutBlockBD( nullptr);
                editLevelXingBlock2NameComboBox->setText("");
                editLevelXingBlock2NameComboBox->setCurrentIndex(-1);
            }
        } else {
            levelXing.setLayoutBlockBD( nullptr);
        }
        editLevelXingNeedsRedraw = true;
         layoutEditor->getLEAuxTools().setBlockConnectivityChanged();
        editLevelXingNeedsBlockUpdate = true;
    }

    // set hidden
    bool oldHidden = levelXing.isHidden();
    levelXing.setHidden(editLevelXingHiddenCheckBox->isChecked());
    if (oldHidden != levelXing.isHidden()) {
        editLevelXingNeedsRedraw = true;
    }

    editLevelXingOpen = false;
    editLevelXingFrame->setVisible(false);
    editLevelXingFrame.dispose();
    editLevelXingFrame =  nullptr;
    if (editLevelXingNeedsBlockUpdate) {
        levelXing.updateBlockInfo();
    }
    if (editLevelXingNeedsRedraw) {
         layoutEditor->redrawPanel();
         layoutEditor->setDirty();
        editLevelXingNeedsRedraw = false;
    }
}   // editLevelXingDonePressed

/*private*/ void editLevelXingCancelPressed(ActionEvent a) {
    editLevelXingOpen = false;
    editLevelXingFrame->setVisible(false);
    editLevelXingFrame.dispose();
    editLevelXingFrame =  nullptr;
    if (editLevelXingNeedsBlockUpdate) {
        levelXing.updateBlockInfo();
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
// variables for Edit Turntable pane
/*private*/ LayoutTurntable layoutTurntable =  nullptr;

/*private*/ JmriJFrame* editLayoutTurntableFrame =  nullptr;
/*private*/ JTextField editLayoutTurntableRadiusTextField = new JTextField(8);
/*private*/ JTextField editLayoutTurntableAngleTextField = new JTextField(8);
/*private*/ QPushButton* editLayoutTurntableDoneButton;
/*private*/ QPushButton* editLayoutTurntableCancelButton;

/*private*/ QWidget* editLayoutTurntableRayPanel;
/*private*/ QPushButton* editLayoutTurntableAddRayTrackButton;
///*private*/ QPushButton* editLayoutTurntableDeleteRayTrackButton;
/*private*/ QCheckBox* editLayoutTurntableDccControlledCheckBox;

/*private*/ QString editLayoutTurntableOldRadius = "";
/*private*/ bool editLayoutTurntableOpen = false;
/*private*/ bool editLayoutTurntableNeedsRedraw = false;
#endif
/**
 * Edit a Turntable
 */
/*protected*/ void LayoutTrackEditors::editLayoutTurntable(LayoutTurntable* layoutTurntable) {
    this->layoutTurntable = layoutTurntable;
#if 0
    if (editLayoutTurntableOpen) {
        editLayoutTurntableFrame->setVisible(true);
    } else // Initialize if needed
    if (editLayoutTurntableFrame ==  nullptr) {
        editLayoutTurntableFrame = new JmriJFrame(tr("EditTurntable"), false, true);  // NOI18N
        editLayoutTurntableFrame.addHelpMenu("package.jmri.jmrit.display.EditTurntable", true);  // NOI18N
        editLayoutTurntableFrame.setLocation(50, 30);

        Container contentPane = editLayoutTurntableFrame.getContentPane();
        QWidget* headerPane = new QWidget();
        QWidget* footerPane = new QWidget();
        headerPane.setLayout(new BoxLayout(headerPane, BoxLayout.Y_AXIS));
        footerPane.setLayout(new BoxLayout(footerPane, BoxLayout.Y_AXIS));
        contentPane.setLayout(new BorderLayout());
        contentPane->layout()->addWidget(headerPane, BorderLayout.NORTH);
        contentPane->layout()->addWidget(footerPane, BorderLayout.SOUTH);

        // setup radius
        QWidget* panel1 = new QWidget();
        panel1.setLayout(new FlowLayout());
        QLabel* radiusLabel = new QLabel(tr("TurntableRadius"));  // NOI18N
        panel1.add(radiusLabel);
        panel1.add(editLayoutTurntableRadiusTextField);
        editLayoutTurntableRadiusTextField->setToolTip(tr("TurntableRadiusHint"));  // NOI18N
        headerPane.add(panel1);

        // setup add ray track
        QWidget* panel2 = new QWidget();
        panel2.setLayout(new FlowLayout());
        QLabel* rayAngleLabel = new QLabel(tr("RayAngle"));  // NOI18N
        panel2.add(rayAngleLabel);
        panel2.add(editLayoutTurntableAngleTextField);
        editLayoutTurntableAngleTextField->setToolTip(tr("RayAngleHint"));  // NOI18N
        headerPane.add(panel2);

        QWidget* panel3 = new QWidget();
        panel3.setLayout(new FlowLayout());
        panel3.add(editLayoutTurntableAddRayTrackButton = new QPushButton(tr("AddRayTrack")));  // NOI18N
        editLayoutTurntableAddRayTrackButton->setToolTip(tr("AddRayTrackHint"));  // NOI18N
        editLayoutTurntableAddRayTrackButton.addActionListener((ActionEvent e) -> {
            addRayTrackPressed(e);
            updateRayPanel();
        });

        panel3.add(editLayoutTurntableDccControlledCheckBox = new JCheckBox(tr("TurntableDCCControlled")));  // NOI18N
        headerPane.add(panel3);

        // set up Done and Cancel buttons
        QWidget* panel5 = new QWidget();
        panel5.setLayout(new FlowLayout());
        panel5Layout->addWidget(editLayoutTurntableDoneButton = new QPushButton(tr("ButtonDone")));  // NOI18N
        editLayoutTurntableDoneButton.addActionListener((ActionEvent e) -> {
            editLayoutTurntableDonePressed(e);
        });

        // make this button the default button (return or enter activates)
        // Note: We have to invoke this later because we don't currently have a root pane
        SwingUtilities.invokeLater(() -> {
            JRootPane rootPane = SwingUtilities.getRootPane(editLayoutTurntableDoneButton);
            rootPane.setDefaultButton(editLayoutTurntableDoneButton);
        });

        editLayoutTurntableDoneButton->setToolTip(tr("DoneHint", tr("ButtonDone")));  // NOI18N
        // Cancel
        panel5Layout->addWidget(editLayoutTurntableCancelButton = new QPushButton(tr("ButtonCancel")));  // NOI18N
        editLayoutTurntableCancelButton.addActionListener((ActionEvent e) -> {
            turntableEditCancelPressed(e);
        });
        editLayoutTurntableCancelButton->setToolTip(tr("CancelHint", tr("ButtonCancel")));  // NOI18N
        footerPane.add(panel5);

        editLayoutTurntableRayPanel = new QWidget();
        editLayoutTurntableRayPanel.setLayout(new BoxLayout(editLayoutTurntableRayPanel, BoxLayout.Y_AXIS));
        JScrollPane rayScrollPane = new JScrollPane(editLayoutTurntableRayPanel, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
        contentPane->layout()->addWidget(rayScrollPane, BorderLayout.CENTER);
    }
    editLayoutTurntableDccControlledCheckBox->setChecked(layoutTurntable.isTurnoutControlled());
    editLayoutTurntableDccControlledCheckBox.addActionListener((ActionEvent e) -> {
        layoutTurntable.setTurnoutControlled(editLayoutTurntableDccControlledCheckBox->isChecked());

        for (Component comp : editLayoutTurntableRayPanel.getComponents()) {
            if (comp instanceof TurntableRayPanel) {
                TurntableRayPanel trp = (TurntableRayPanel) comp;
                trp.showTurnoutDetails();
            }
        }
        editLayoutTurntableFrame.pack();
    });
    updateRayPanel();
    // Set up for Edit
    editLayoutTurntableRadiusTextField->setText(" " + layoutTurntable.getRadius());
    editLayoutTurntableOldRadius = editLayoutTurntableRadiusTextField.getText();
    editLayoutTurntableAngleTextField->setText("0");
    editLayoutTurntableFrame.addWindowListener(new java.awt.event.WindowAdapter() {
        @Override
        /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
            turntableEditCancelPressed( nullptr);
        }
    });
    editLayoutTurntableFrame.pack();
    editLayoutTurntableFrame->setVisible(true);
    editLayoutTurntableOpen = true;
#endif
}   // editLayoutTurntable
#if 0
//Remove old rays and add them back in
/*private*/ void updateRayPanel() {
    for (Component comp : editLayoutTurntableRayPanel.getComponents()) {
        editLayoutTurntableRayPanel.remove(comp);
    }

    editLayoutTurntableRayPanel.setLayout(new BoxLayout(editLayoutTurntableRayPanel, BoxLayout.Y_AXIS));
    for (LayoutTurntable.RayTrack rt : layoutTurntable.getRayList()) {
        editLayoutTurntableRayPanel.add(new TurntableRayPanel(rt));
    }
    editLayoutTurntableRayPanel.revalidate();
    editLayoutTurntableRayPanel.repaint();
    editLayoutTurntableFrame.pack();
}

/*private*/ void saveRayPanelDetail() {
    for (Component comp : editLayoutTurntableRayPanel.getComponents()) {
        if (comp instanceof TurntableRayPanel) {
            TurntableRayPanel trp = (TurntableRayPanel) comp;
            trp.updateDetails();
        }
    }
}

/*private*/ void addRayTrackPressed(ActionEvent a) {
    double ang = 0.0;
    try {
        ang = Float.parseFloat(editLayoutTurntableAngleTextField.getText());
    } catch (Exception e) {
        JOptionPane.showMessageDialog(editLayoutTurntableFrame, tr("EntryError") + ": "  // NOI18N
                + e + tr("TryAgain"), tr("ErrorTitle"),  // NOI18N
                JOptionPane.ERROR_MESSAGE);
        return;
    }
    layoutTurntable.addRay(ang);
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

/*private*/ void editLayoutTurntableDonePressed(ActionEvent a) {
    // check if new radius was entered
    String str = editLayoutTurntableRadiusTextField.getText();
    if (!str == (editLayoutTurntableOldRadius)) {
        double rad = 0.0;
        try {
            rad = Float.parseFloat(str);
        } catch (Exception e) {
            JOptionPane.showMessageDialog(editLayoutTurntableFrame, tr("EntryError") + ": "  // NOI18N
                    + e + tr("TryAgain"), tr("ErrorTitle"),  // NOI18N
                    JOptionPane.ERROR_MESSAGE);
            return;
        }
        layoutTurntable.setRadius(rad);
        editLayoutTurntableNeedsRedraw = true;
    }
    // clean up
    editLayoutTurntableOpen = false;
    editLayoutTurntableFrame->setVisible(false);
    editLayoutTurntableFrame.dispose();
    editLayoutTurntableFrame =  nullptr;
    saveRayPanelDetail();
    if (editLayoutTurntableNeedsRedraw) {
         layoutEditor->redrawPanel();
         layoutEditor->setDirty();
        editLayoutTurntableNeedsRedraw = false;
    }
}   // editLayoutTurntableDonePressed

/*private*/ void turntableEditCancelPressed(ActionEvent a) {
    editLayoutTurntableOpen = false;
    editLayoutTurntableFrame->setVisible(false);
    editLayoutTurntableFrame.dispose();
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
/*public*/ class TurntableRayPanel extends QWidget* {

    // variables for Edit Turntable ray pane
    /*private*/ RayTrack rayTrack =  nullptr;
    /*private*/ QWidget* rayTurnoutPanel;
    /*private*/ transient JmriBeanComboBox* turnoutNameComboBox;
    /*private*/ TitledBorder rayTitledBorder;
    /*private*/ QComboBox* rayTurnoutStateComboBox;
    /*private*/ QLabel* rayTurnoutStateLabel;
    /*private*/ JTextField rayAngleTextField;
    /*private*/ final int[] rayTurnoutStateValues = new int[]{Turnout.CLOSED, Turnout.THROWN};
    /*private*/ final DecimalFormat twoDForm = new DecimalFormat("#.00");

    /**
     * constructor method
     */
    /*public*/ TurntableRayPanel(@Non nullptr RayTrack rayTrack) {
        this.rayTrack = rayTrack;

        QWidget* top = new QWidget();

        /*QLabel* lbl = new QLabel("Index :"+connectionIndex);
             top.add(lbl);*/
        top.add(new QLabel(tr("RayAngle") + " : "));  // NOI18N
        top.add(rayAngleTextField = new JTextField(5));
        rayAngleTextField.addFocusListener(new FocusListener() {
            @Override
            /*public*/ void focusGained(FocusEvent e) {
            }

            @Override
            /*public*/ void focusLost(FocusEvent e) {
                try {
                    Float.parseFloat(rayAngleTextField.getText());
                } catch (Exception ex) {
                    JOptionPane.showMessageDialog(editLayoutTurntableFrame, tr("EntryError") + ": "  // NOI18N
                            + ex + tr("TryAgain"), tr("ErrorTitle"),  // NOI18N
                            JOptionPane.ERROR_MESSAGE);
                    return;
                }
            }
        }
        );
        this.setLayout(new BoxLayout(this, BoxLayout.Y_AXIS));
        this.add(top);

        turnoutNameComboBox = new JmriBeanComboBox(
                InstanceManager::turnoutManagerInstance(),
                rayTrack.getTurnout(),
                JmriBeanComboBox::DisplayOptions::DISPLAYNAME);
         layoutEditor->setupComboBox(turnoutNameComboBox, true, true);
        turnoutNameComboBox->setCheckedBean(rayTrack.getTurnout());

        String turnoutStateThrown = InstanceManager::turnoutManagerInstance().getThrownText();
        String turnoutStateClosed = InstanceManager::turnoutManagerInstance().getClosedText();
        String[] turnoutStates = new String[]{turnoutStateClosed, turnoutStateThrown};

        rayTurnoutStateComboBox = new QComboBox(turnoutStates);
        rayTurnoutStateLabel = new QLabel(tr("TurnoutState"));  // NOI18N
        rayTurnoutPanel = new QWidget();

        rayTurnoutPanel.setBorder(new EtchedBorder());
        rayTurnoutPanel.add(turnoutNameComboBox);
        rayTurnoutPanel.add(rayTurnoutStateLabel);
        rayTurnoutPanel.add(rayTurnoutStateComboBox);
        if (rayTrack.getTurnoutState() == Turnout.CLOSED) {
            rayTurnoutStateComboBox->setCheckedItem(turnoutStateClosed);
        } else {
            rayTurnoutStateComboBox->setCheckedItem(turnoutStateThrown);
        }
        this.add(rayTurnoutPanel);

        QPushButton* deleteRayButton;
        top.add(deleteRayButton = new QPushButton(tr("ButtonDelete")));  // NOI18N
        deleteRayButton->setToolTip(tr("DeleteRayTrack"));  // NOI18N
        deleteRayButton.addActionListener((ActionEvent e) -> {
            delete();
            updateRayPanel();
        });
        rayTitledBorder = BorderFactory.createTitledBorder(BorderFactory.createLineBorder(Color.black));

        this.setBorder(rayTitledBorder);

        showTurnoutDetails();

        rayAngleTextField->setText(twoDForm.format(rayTrack.getAngle()));
        rayTitledBorder.setTitle(tr("Ray") + " : " + rayTrack.getConnectionIndex());  // NOI18N
        if (rayTrack.getConnect() ==  nullptr) {
            rayTitledBorder.setTitle(tr("Unconnected") + " : " + rayTrack.getConnectionIndex());  // NOI18N
        } else if (rayTrack.getConnect().getLayoutBlock() !=  nullptr) {
            rayTitledBorder.setTitle(tr("Connected") + " : " + rayTrack.getConnect().getLayoutBlock().getDisplayName());  // NOI18N
        }
    }

    /*private*/ void delete() {
        int n = JOptionPane.showConfirmDialog( nullptr,
                tr("Question7"),  // NOI18N
                tr("WarningTitle"),  // NOI18N
                JOptionPane.YES_NO_OPTION);
        if (n == JOptionPane.YES_OPTION) {
            layoutTurntable.deleteRay(rayTrack);
        }
    }

    /*private*/ void updateDetails() {
        if (turnoutNameComboBox ==  nullptr || rayTurnoutStateComboBox ==  nullptr) {
            return;
        }
        rayTrack.setTurnout(turnoutNameComboBox.getDisplayName(), rayTurnoutStateValues[rayTurnoutStateComboBox->currentIndex()]);
        if (!rayAngleTextField.getText() == (twoDForm.format(rayTrack.getAngle()))) {
            try {
                double ang = Float.parseFloat(rayAngleTextField.getText());
                rayTrack.setAngle(ang);
            } catch (Exception e) {
                log.error("Angle is not in correct format so will skip " + rayAngleTextField.getText());  // NOI18N
            }
        }
    }

    /*private*/ void showTurnoutDetails() {
        bool vis = layoutTurntable.isTurnoutControlled();
        rayTurnoutPanel->setVisible(vis);
        turnoutNameComboBox->setVisible(vis);
        rayTurnoutStateComboBox->setVisible(vis);
        rayTurnoutStateLabel->setVisible(vis);
    }
}   // class TurntableRayPanel
#endif
/*private*/ /*final*/ /*static*/ Logger* LayoutTrackEditors::log = LoggerFactory::getLogger("LayoutTrackEditors");


