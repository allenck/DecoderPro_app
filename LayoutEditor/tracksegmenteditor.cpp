#include "tracksegmenteditor.h"
#include "loggerfactory.h"
#include "joptionpane.h"
#include "tracksegment.h"

/**
 * MVC Editor component for TrackSegment objects.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class TrackSegmentEditor extends LayoutTrackEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ TrackSegmentEditor::TrackSegmentEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTrackEditor(layoutEditor) {
        //super(layoutEditor);
     setObjectName("TrackSegmentEditor");
    }

    // ********** Members and methods from LayoutTrackEditors
    // ********** specific to TrackSegment




    /**
     * Edit a Track Segment.
     */
    //@InvokeOnGuiThread
    //@Override
    /*public*/ void TrackSegmentEditor::editLayoutTrack(/*@Nonnull*/ LayoutTrackView *layoutTrackView) {
        if (qobject_cast<TrackSegmentView*>(layoutTrackView) ) {
         this->trackSegmentView = (TrackSegmentView*) layoutTrackView;
         this->trackSegment = this->trackSegmentView->getTrackSegment();
        } else {
            log->error(tr("editLayoutTrack received type %1 content %2").arg(
                    layoutTrackView->metaObject()->className()).arg(layoutTrackView->objectName()),
                    Exception("traceback"));
        }
        sensorList.clear();

        if (editTrackSegmentOpen) {
            editTrackSegmentFrame->setVisible(true);
        } else if (editTrackSegmentFrame == nullptr) { // Initialize if needed
            editTrackSegmentFrame = new JmriJFrameX(tr("Edit TrackSegment"), false, true); // key moved to DisplayBundle to be found by CircuitBuilder.java   // NOI18N
            editTrackSegmentFrame->addHelpMenu("package.jmri.jmrit.display.EditTrackSegment", true);  // NOI18N
            editTrackSegmentFrame->setLocation(50, 30);
            QWidget* contentPane = editTrackSegmentFrame->getContentPane();
            contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

            // add dashed choice
            JPanel* panel31 = new JPanel();
            panel31->setLayout(new FlowLayout());
            editTrackSegmentDashedComboBox->clear();
            editTrackSegmentDashedComboBox->addItem(tr("Solid"));  // NOI18N
            editTrackSegmentSolidIndex = 0;
            editTrackSegmentDashedComboBox->addItem(tr("Dashed"));  // NOI18N
            editTrackSegmentDashedIndex = 1;
            editTrackSegmentDashedComboBox->setToolTip(tr("Select style for track segment."));  // NOI18N
            JLabel* label31a = new JLabel(tr("%1:").arg(tr("Style")));
            panel31->layout()->addWidget(label31a);
            label31a->setLabelFor(editTrackSegmentDashedComboBox);
            panel31->layout()->addWidget(editTrackSegmentDashedComboBox);
            contentPane->layout()->addWidget(panel31);

            // add mainline choice
            JPanel* panel32 = new JPanel();
            panel32->setLayout(new FlowLayout());

            editTrackSegmentMainlineComboBox->clear();
            editTrackSegmentMainlineComboBox->addItem(tr("Mainline"));  // NOI18N
            editTrackSegmentMainlineTrackIndex = 0;
            editTrackSegmentMainlineComboBox->addItem(tr("NotMainline"));  // NOI18N
            editTrackSegmentSideTrackIndex = 1;
            editTrackSegmentMainlineComboBox->setToolTip(tr("Select whether track segment is part of a mainline, or is a side track."));  // NOI18N
            editTrackSegmentMainlineComboBox->setObjectName(tr("Mainline"));
            panel32->layout()->addWidget(editTrackSegmentMainlineComboBox);
            contentPane->layout()->addWidget(panel32);

            // add hidden choice
            JPanel* panel33 = new JPanel();
            panel33->setLayout(new FlowLayout());
            editTrackSegmentHiddenCheckBox->setToolTip(tr("Check to hide this track segment when not in edit mode."));  // NOI18N
            panel33->layout()->addWidget(editTrackSegmentHiddenCheckBox);
            contentPane->layout()->addWidget(panel33);

            // setup block name
            JPanel* panel2 = new JPanel();
            panel2->setLayout(new FlowLayout());
            JLabel* blockNameLabel = new JLabel(tr("Block Name:"));  // NOI18N
            panel2->layout()->addWidget(blockNameLabel);
            blockNameLabel->setLabelFor(editTrackSegmentBlockNameComboBox);
            LayoutEditor::setupComboBox(editTrackSegmentBlockNameComboBox, false, true, true);
            editTrackSegmentBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N

            panel2->layout()->addWidget(editTrackSegmentBlockNameComboBox);

            contentPane->layout()->addWidget(panel2);

            JPanel* panel20 = new JPanel();
            panel20->setLayout(new FlowLayout());
            JLabel* arcLabel = new JLabel(tr("Set Arc Angle"));  // NOI18N
            panel20->layout()->addWidget(arcLabel);
            arcLabel->setLabelFor(editTrackSegmentArcTextField);
            panel20->layout()->addWidget(editTrackSegmentArcTextField);
            editTrackSegmentArcTextField->setToolTip(tr("Set Arc Angle"));  // NOI18N
            contentPane->layout()->addWidget(panel20);

            // set up Edit Block, Done and Cancel buttons
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());

            // Edit Block
            panel5->layout()->addWidget(editTrackSegmentSegmentEditBlockButton = new QPushButton(tr("Edit Block", "")));  // NOI18N
            //editTrackSegmentSegmentEditBlockButton.addActionListener(this::editTrackSegmentEditBlockPressed);
            connect(editTrackSegmentSegmentEditBlockButton, &QPushButton::clicked, [=]{
             editTrackSegmentEditBlockPressed();
            });
            editTrackSegmentSegmentEditBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.").arg("")); // empty value for block 1  // NOI18N
            TSE_editTracksegmentDonePressed* _editTracksegmentDonePressed = new TSE_editTracksegmentDonePressed(this);
            TSE_editTracksegmentCancelPressed* _editTrackSegmentCancelPressed = new TSE_editTracksegmentCancelPressed(this);
            addDoneCancelButtons(panel5, editTrackSegmentFrame->getRootPane(),
                    _editTracksegmentDonePressed, _editTrackSegmentCancelPressed);
            contentPane->layout()->addWidget(panel5);
        }
        // Set up for Edit
        if (trackSegment->isMainline()) {
            editTrackSegmentMainlineComboBox->setCurrentIndex(editTrackSegmentMainlineTrackIndex);
        } else {
            editTrackSegmentMainlineComboBox->setCurrentIndex(editTrackSegmentSideTrackIndex);
        }
        if (trackSegmentView->isDashed()) {
            editTrackSegmentDashedComboBox->setCurrentIndex(editTrackSegmentDashedIndex);
        } else {
            editTrackSegmentDashedComboBox->setCurrentIndex(editTrackSegmentSolidIndex);
        }
        editTrackSegmentHiddenCheckBox->setChecked(trackSegmentView->isHidden());
        Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(trackSegment->getBlockName());
        //editTrackSegmentBlockNameComboBox.getEditor().setItem(block);   // Select the item via the editor, empty text field if null
        //editTrackSegmentBlockNameComboBox->setCurrentIndex(editTrackSegmentBlockNameComboBox->findData(VPtr<Block>::asQVariant(block)));
        editTrackSegmentBlockNameComboBox->setCurrentIndex(editTrackSegmentBlockNameComboBox->findText(block->getDisplayName(editTrackSegmentBlockNameComboBox->getDisplayOrder())));
        editTrackSegmentBlockNameComboBox->setEnabled(!hasNxSensorPairs(trackSegment->getLayoutBlock()));

        if (trackSegmentView->isArc() && trackSegmentView->isCircle()) {
            editTrackSegmentArcTextField->setText(QString::number(trackSegmentView->getAngle()));
            editTrackSegmentArcTextField->setEnabled(true);
        } else {
            editTrackSegmentArcTextField->setEnabled(false);
        }

        editTrackSegmentFrame->addWindowListener(new TSE_windowListener(this));
//        {
//            @Override
//            /*public*/ void windowClosing(java.awt.event.WindowEvent e) {
//                editTrackSegmentCancelPressed(null);
//            }
//        });

        editTrackSegmentFrame->pack();
        editTrackSegmentFrame->setVisible(true);
        editTrackSegmentOpen = true;

        showSensorMessage();
    }   // editTrackSegment

    //@InvokeOnGuiThread
    /*private*/ void TrackSegmentEditor::editTrackSegmentEditBlockPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editTrackSegmentBlockNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if ((trackSegment->getBlockName().isEmpty())
                || trackSegment->getBlockName()!=(newName)) {
            // get new block, or null if block has been removed
            trackSegment->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
            editTrackSegmentNeedsRedraw = true;
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
            trackSegment->updateBlockInfo();
        }
        // check if a block exists to edit
        if (trackSegment->getLayoutBlock() == nullptr) {
            JOptionPane::showMessageDialog(editTrackSegmentFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                    tr("ErrorTitle"), JOptionPane::ERROR_MESSAGE);  // NOI18N
            return;
        }
        trackSegment->getLayoutBlock()->editLayoutBlock(editTrackSegmentFrame);
        layoutEditor->setDirty();
        editTrackSegmentNeedsRedraw = true;
    }

    //@InvokeOnGuiThread
    /*private*/ void TrackSegmentEditor::editTracksegmentDonePressed(/*ActionEvent a*/) {
        // set dashed
        bool oldDashed = trackSegmentView->isDashed();
        trackSegmentView->setDashed(editTrackSegmentDashedComboBox->currentText() == editTrackSegmentDashedIndex);

        // set mainline
        bool oldMainline = trackSegment->isMainline();
        trackSegment->setMainline(editTrackSegmentMainlineComboBox->currentIndex() == editTrackSegmentMainlineTrackIndex);

        // set hidden
        bool oldHidden = trackSegmentView->isHidden();
        trackSegmentView->setHidden(editTrackSegmentHiddenCheckBox->isChecked());

        if (trackSegmentView->isArc()) {
            bool ok;
                double newAngle = editTrackSegmentArcTextField->text().toDouble(&ok);
                trackSegmentView->setAngle(newAngle);
                editTrackSegmentNeedsRedraw = true;
            if(!ok) {
                editTrackSegmentArcTextField->setText(QString::number(trackSegmentView->getAngle()));
            }
        }
        // check if anything changed
        if ((oldDashed != trackSegmentView->isDashed())
                || (oldMainline != trackSegment->isMainline())
                || (oldHidden != trackSegmentView->isHidden())) {
            editTrackSegmentNeedsRedraw = true;
        }
        // check if Block changed
        QString newName = editTrackSegmentBlockNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if ((trackSegment->getBlockName().isEmpty())
                || trackSegment->getBlockName() != (newName)) {
            // get new block, or null if block has been removed
            trackSegment->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
            editTrackSegmentNeedsRedraw = true;
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
            trackSegment->updateBlockInfo();
        }
        editTrackSegmentOpen = false;

        editTrackSegmentFrame->setVisible(false);
        editTrackSegmentFrame->dispose();
        editTrackSegmentFrame = nullptr;

        if (editTrackSegmentNeedsRedraw) {
            layoutEditor->redrawPanel();
            editTrackSegmentNeedsRedraw = false;
        }
        layoutEditor->setDirty();
    }

    //@InvokeOnGuiThread
    /*private*/ void TrackSegmentEditor::editTrackSegmentCancelPressed(/*ActionEvent a*/) {
        editTrackSegmentOpen = false;
        editTrackSegmentFrame->setVisible(false);
        editTrackSegmentFrame->dispose();
        editTrackSegmentFrame = nullptr;
        if (editTrackSegmentNeedsRedraw) {
            layoutEditor->setDirty();
            layoutEditor->redrawPanel();
            editTrackSegmentNeedsRedraw = false;
        }
    }


    /*private*/ /*final*/ /*static*/ Logger* TrackSegmentEditor::log = LoggerFactory::getLogger("TrackSegmentEditor");
