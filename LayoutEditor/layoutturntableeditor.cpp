#include "layoutturntableeditor.h"
#include "loggerfactory.h"
#include "layoutturntable.h"
#include "joptionpane.h"
#include "etchedborder.h"
#include "borderlayout.h"
#include "layouteditor.h"
#include "borderfactory.h"

/**
 * MVC Editor component for PositionablePoint objects.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutTurntableEditor extends LayoutTrackEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutTurntableEditor::LayoutTurntableEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) :LayoutTrackEditor(layoutEditor) {
        //super(layoutEditor);
    }

    /*==============*\
    | Edit Turntable |
    \*==============*/


    /**
     * Edit a Turntable.
     */
    //@Override
    /*public*/ void LayoutTurntableEditor::editLayoutTrack(/*@Nonnull*/ LayoutTrackView *layoutTrack) {
        if (qobject_cast<LayoutTurntable*>(layoutTrack) ) {
            this->layoutTurntable = (LayoutTurntable*) layoutTrack;
        } else {
            log->error(tr("editLayoutTrack called with wrong type %1").arg(layoutTrack->metaObject()->className()), new  Exception("traceback"));
        }
        sensorList.clear();

        if (editLayoutTurntableOpen) {
            editLayoutTurntableFrame->setVisible(true);
        } else // Initialize if needed
        if (editLayoutTurntableFrame == nullptr) {
            editLayoutTurntableFrame = new JmriJFrameX(tr("Edit Turntable"), false, true);  // NOI18N
            editLayoutTurntableFrame->addHelpMenu("package.jmri.jmrit.display.EditTurntable", true);  // NOI18N
            editLayoutTurntableFrame->setLocation(50, 30);

            QWidget* contentPane = editLayoutTurntableFrame->getContentPane();
            JPanel* headerPane = new JPanel();
            JPanel* footerPane = new JPanel();
            headerPane->setLayout(new QVBoxLayout());//headerPane, BoxLayout.Y_AXIS));
            footerPane->setLayout(new QVBoxLayout());//footerPane, BoxLayout.Y_AXIS));
            contentPane->setLayout(new BorderLayout());
            ((BorderLayout*)contentPane->layout())->addWidget(headerPane, BorderLayout::North);
            ((BorderLayout*)contentPane->layout())->addWidget(footerPane, BorderLayout::South);

            // setup radius text field
            JPanel* panel1 = new JPanel();
            panel1->setLayout(new FlowLayout());
            JLabel* radiusLabel = new JLabel(tr("Turntable Radius"));  // NOI18N
            panel1->layout()->addWidget(radiusLabel);
            radiusLabel->setLabelFor(editLayoutTurntableRadiusTextField);
            panel1->layout()->addWidget(editLayoutTurntableRadiusTextField);
            editLayoutTurntableRadiusTextField->setToolTip(tr("Enter radius (screen units) of turntable circle."));  // NOI18N
            headerPane->layout()->addWidget(panel1);

            // setup ray track angle text field
            JPanel* panel2 = new JPanel();
            panel2->setLayout(new FlowLayout());
            JLabel* rayAngleLabel = new JLabel(tr("Ray Track Angle"));  // NOI18N
            panel2->layout()->addWidget(rayAngleLabel);
            rayAngleLabel->setLabelFor(editLayoutTurntableAngleTextField);
            panel2->layout()->addWidget(editLayoutTurntableAngleTextField);
            editLayoutTurntableAngleTextField->setToolTip(tr("Enter angle of Ray Track to add or delete (12 o'clock = 0, 3 o'clock = 90 degrees, etc.)."));  // NOI18N
            headerPane->layout()->addWidget(panel2);

            // setup block name
             JPanel* panel2a = new JPanel();
             panel2a->setLayout(new FlowLayout());
             JLabel* blockNameLabel = new JLabel(tr("Block Name:"));  // NOI18N
             panel2a->layout()->addWidget(blockNameLabel);
             blockNameLabel->setLabelFor(editLayoutTurntableBlockNameComboBox);
             LayoutEditor::setupComboBox(editLayoutTurntableBlockNameComboBox, false, true, true);
             editLayoutTurntableBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N
             panel2a->layout()->addWidget(editLayoutTurntableBlockNameComboBox);

             // Edit Block
             panel2a->layout()->addWidget(editLayoutTurntableSegmentEditBlockButton = new QPushButton(tr("Create/Edit Block %1").arg("")));  // NOI18N
             //editLayoutTurntableSegmentEditBlockButton.addActionListener(this::editLayoutTurntableEditBlockPressed);
             connect(editLayoutTurntableSegmentEditBlockButton, &QPushButton::clicked, [=]{
              editLayoutTurntableEditBlockPressed();
             });
             editLayoutTurntableSegmentEditBlockButton->setToolTip(tr("Click here to create/edit information for Block {0} shown above.", "")); // empty value for block 1  // NOI18N
             headerPane->layout()->addWidget(panel2a);

            // setup add ray track button
            JPanel* panel3 = new JPanel();
            panel3->setLayout(new FlowLayout());
            panel3->layout()->addWidget(editLayoutTurntableAddRayTrackButton = new QPushButton(tr("New Ray Track")));  // NOI18N
            editLayoutTurntableAddRayTrackButton->setToolTip(tr("Select to add a new Ray Track at the angle entered above."));  // NOI18N
            //editLayoutTurntableAddRayTrackButton.addActionListener((ActionEvent e) -> {
            connect(editLayoutTurntableAddRayTrackButton, &QPushButton::clicked, [=]{
                addRayTrackPressed(/*e*/);
                updateRayPanel();
            });

            panel3->layout()->addWidget(editLayoutTurntableDccControlledCheckBox = new JCheckBox(tr("DCC Controlled Turntable")));  // NOI18N
            headerPane->layout()->addWidget(panel3);

            // set up Done and Cancel buttons
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            LTTE_editLayoutTurntableDonePressed* _editLayoutTurntableDonePressed = new LTTE_editLayoutTurntableDonePressed(this);
            LTTE_turntableEditCancelPressed* _turntableEditCancelPressed = new LTTE_turntableEditCancelPressed(this);
            addDoneCancelButtons(panel5, editLayoutTurntableFrame->getRootPane(),
                    _editLayoutTurntableDonePressed, _turntableEditCancelPressed);
            footerPane->layout()->addWidget(panel5);

            editLayoutTurntableRayPanel = new JPanel();
            editLayoutTurntableRayPanel->setLayout(new QVBoxLayout());//editLayoutTurntableRayPanel, BoxLayout.Y_AXIS));
            //JScrollPane rayScrollPane = new JScrollPane(editLayoutTurntableRayPanel, JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_AS_NEEDED);
            QScrollArea* rayScrollPane = new QScrollArea();
            rayScrollPane->setWidget(editLayoutTurntableRayPanel);
            ((BorderLayout*)contentPane->layout())->addWidget(rayScrollPane, BorderLayout::Center);
        }
        editLayoutTurntableDccControlledCheckBox->setChecked(layoutTurntable->isTurnoutControlled());
        //editLayoutTurntableDccControlledCheckBox.addActionListener((ActionEvent e) -> {
        connect(editLayoutTurntableDccControlledCheckBox, &JCheckBox::clicked, [=]{
            layoutTurntable->setTurnoutControlled(editLayoutTurntableDccControlledCheckBox->isChecked());

            for (QWidget* comp : editLayoutTurntableRayPanel->findChildren<QWidget*>()) {
                if (qobject_cast<TurntableRayPanel*>(comp)) {
                    TurntableRayPanel* trp = (TurntableRayPanel*) comp;
                    trp->showTurnoutDetails();
                }
            }
            editLayoutTurntableFrame->pack();
        });
        updateRayPanel();
        // Set up for Edit
        editLayoutTurntableRadiusTextField->setText(QString::number(layoutTurntable->getRadius()));
        editLayoutTurntableOldRadius = editLayoutTurntableRadiusTextField->text();
        editLayoutTurntableAngleTextField->setText("0");
        editLayoutTurntableFrame->addWindowListener(new ELTTFWindowListener(this));
//        {
//            @Override
//            public void windowClosing(java.awt.event.WindowEvent e) {
//                turntableEditCancelPressed(null);
//            }
//        });
        editLayoutTurntableFrame->pack();
        editLayoutTurntableFrame->setVisible(true);
        editLayoutTurntableOpen = true;
    }   // editLayoutTurntable

    //@InvokeOnGuiThread
    /*private*/ void LayoutTurntableEditor::editLayoutTurntableEditBlockPressed(/*ActionEvent a*/) {
         // check if a block name has been entered
         QString newName = editLayoutTurntableBlockNameComboBox->getSelectedItemDisplayName();
         if (newName.isNull()) {
             newName = "";
         }
         if ((layoutTurntable->getBlockName().isEmpty())
                 || layoutTurntable->getBlockName() != (newName)) {
             // get new block, or null if block has been removed
             layoutTurntable->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
             editLayoutTurntableNeedsRedraw = true;
             ///layoutEditor.getLEAuxTools().setBlockConnectivityChanged();
             ///layoutTurntable.updateBlockInfo();
         }
         // check if a block exists to edit
         LayoutBlock* blockToEdit = layoutTurntable->getLayoutBlock();
         if (blockToEdit == nullptr) {
             JOptionPane::showMessageDialog(editLayoutTurntableFrame,
                     tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."), // NOI18N
                     tr("Error"), JOptionPane::ERROR_MESSAGE);  // NOI18N
             return;
         }
         blockToEdit->editLayoutBlock(editLayoutTurntableFrame);
         layoutEditor->setDirty();
         editLayoutTurntableNeedsRedraw = true;
     }

    // Remove old rays and add them back in
    /*private*/ void LayoutTurntableEditor::updateRayPanel() {
        for (QWidget* comp : editLayoutTurntableRayPanel->findChildren<QWidget*>()) {
            editLayoutTurntableRayPanel->layout()->removeWidget(comp);
        }

        // Create list of turnouts to be retained in the NamedBeanComboBox
        turntableTurnouts.clear();
        for (RayTrack* rt : layoutTurntable->getRayTrackList()) {
            turntableTurnouts.append(rt->getTurnout());
        }

        editLayoutTurntableRayPanel->setLayout(new QVBoxLayout());//editLayoutTurntableRayPanel, BoxLayout.Y_AXIS));
        for (RayTrack* rt : layoutTurntable->getRayTrackList()) {
            editLayoutTurntableRayPanel->layout()->addWidget(new TurntableRayPanel(rt, this));
        }
        editLayoutTurntableRayPanel->update();
        editLayoutTurntableRayPanel->repaint();
        editLayoutTurntableFrame->pack();
    }

    /*private*/ void LayoutTurntableEditor::saveRayPanelDetail() {
        for (QWidget* comp : editLayoutTurntableRayPanel->findChildren<QWidget*>()) {
            if (qobject_cast<TurntableRayPanel*>(comp)) {
                TurntableRayPanel* trp = (TurntableRayPanel*) comp;
                trp->updateDetails();
            }
        }
    }

    /*private*/ void LayoutTurntableEditor::addRayTrackPressed(/*ActionEvent a*/) {
        double ang = 0.0;
        bool ok;
            ang = editLayoutTurntableAngleTextField->text().toDouble(&ok);
        if(!ok) {
            JOptionPane::showMessageDialog(editLayoutTurntableFrame, tr("Error in entry") + ": " // NOI18N
                    /*+ e*/ + tr("Please reenter or Cancel."), tr("Error"), // NOI18N
                    JOptionPane::ERROR_MESSAGE);
            return;
        }
        layoutTurntable->addRay(ang);
        layoutEditor->redrawPanel();
        layoutEditor->setDirty();
        editLayoutTurntableNeedsRedraw = false;
    }

    /*private*/ void LayoutTurntableEditor::editLayoutTurntableDonePressed(/*ActionEvent a*/) {
        // check if Block changed
        QString newName = editLayoutTurntableBlockNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }

        if ((layoutTurntable->getBlockName().isEmpty()) || layoutTurntable->getBlockName() != newName) {
            // get new block, or null if block has been removed
            layoutTurntable->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
            editLayoutTurntableNeedsRedraw = true;
            ///layoutEditor.getLEAuxTools().setBlockConnectivityChanged();
            ///layoutTurntable.updateBlockInfo();
        }

        // check if new radius was entered
        QString str = editLayoutTurntableRadiusTextField->text();
        if (str != (editLayoutTurntableOldRadius)) {
            double rad = 0.0;
            bool ok;
                rad = str.toDouble(&ok);
            if(!ok) {
                JOptionPane::showMessageDialog(editLayoutTurntableFrame, tr("Error in entry") + ": " // NOI18N
                        /*+ e*/ + tr("Please reenter or Cancel."), tr("ErrorTitle"), // NOI18N
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
        editLayoutTurntableFrame = nullptr;
        saveRayPanelDetail();
        if (editLayoutTurntableNeedsRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLayoutTurntableNeedsRedraw = false;
        }
    }

    /*private*/ void LayoutTurntableEditor::turntableEditCancelPressed(/*ActionEvent a*/) {
        editLayoutTurntableOpen = false;
        editLayoutTurntableFrame->setVisible(false);
        editLayoutTurntableFrame->dispose();
        editLayoutTurntableFrame = nullptr;
        if (editLayoutTurntableNeedsRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLayoutTurntableNeedsRedraw = false;
        }
    }

    /*===================*\
    | Turntable Ray Panel |
    \*===================*/
//    public class TurntableRayPanel extends JPanel {

//        // variables for Edit Turntable ray pane
//        private LayoutTurntable.RayTrack rayTrack = null;
//        private final JPanel rayTurnoutPanel;
//        private final NamedBeanComboBox<Turnout> turnoutNameComboBox;
//        private final TitledBorder rayTitledBorder;
//        private final JComboBox<String> rayTurnoutStateComboBox;
//        private final JLabel rayTurnoutStateLabel;
//        private final JTextField rayAngleTextField;
//        private final int[] rayTurnoutStateValues = new int[]{Turnout.CLOSED, Turnout.THROWN};
//        private final DecimalFormat twoDForm = new DecimalFormat("#.00");

        /**
         * constructor method.
         * @param rayTrack the single ray track to edit.
         */
        /*public*/ TurntableRayPanel::TurntableRayPanel(/*@Nonnull*/ RayTrack* rayTrack, LayoutTurntableEditor *editor) {
            this->rayTrack = rayTrack;
            this->editor = editor;

            JPanel* top = new JPanel();

            JLabel* rayAngleLabel = new JLabel(tr("%1").arg(tr("Ray Track Angle")));
            top->layout()->addWidget(rayAngleLabel);
            top->layout()->addWidget(rayAngleTextField = new JTextField(5));
            rayAngleLabel->setLabelFor(rayAngleTextField);
#if 0
            rayAngleTextField.addFocusListener(new FocusListener() {
                @Override
                public void focusGained(FocusEvent e) {
                }

                @Override
                public void focusLost(FocusEvent e) {
                    try {
                        Float.parseFloat(rayAngleTextField.getText());
                    } catch (Exception ex) {
                        JOptionPane.showMessageDialog(editLayoutTurntableFrame, Bundle.getMessage("EntryError") + ": " // NOI18N
                                + ex + Bundle.getMessage("TryAgain"), Bundle.getMessage("ErrorTitle"), // NOI18N
                                JOptionPane.ERROR_MESSAGE);
                    }
                }
            }
            );
#endif
            this->setLayout(new QVBoxLayout());//this, BoxLayout.Y_AXIS));
            this->layout()->addWidget(top);

            turnoutNameComboBox = new NamedBeanComboBox((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"));
            turnoutNameComboBox->setToolTip(tr("Select a turnout, used turnouts are excluded from the list."));
            LayoutEditor::setupComboBox(turnoutNameComboBox, false, true, false);
            turnoutNameComboBox->setSelectedItem(rayTrack->getTurnout());
#if 0
            turnoutNameComboBox.addPopupMenuListener(
                    layoutEditor.newTurnoutComboBoxPopupMenuListener(turnoutNameComboBox, turntableTurnouts));
#endif
            QString turnoutStateThrown = InstanceManager::turnoutManagerInstance()->getThrownText();
            QString turnoutStateClosed = InstanceManager::turnoutManagerInstance()->getClosedText();
            QStringList turnoutStates = QStringList() << turnoutStateClosed <<turnoutStateThrown;

            rayTurnoutStateComboBox = new JComboBox(turnoutStates);
            rayTurnoutStateLabel = new JLabel(tr("Set State"));  // NOI18N
            rayTurnoutPanel = new JPanel();

            rayTurnoutPanel->setBorder(new EtchedBorder());
            rayTurnoutPanel->layout()->addWidget(turnoutNameComboBox);
            rayTurnoutPanel->layout()->addWidget(rayTurnoutStateLabel);
            rayTurnoutStateLabel->setLabelFor(rayTurnoutStateComboBox);
            rayTurnoutPanel->layout()->addWidget(rayTurnoutStateComboBox);
            if (rayTrack->getTurnoutState() == Turnout::CLOSED) {
                rayTurnoutStateComboBox->setCurrentText(turnoutStateClosed);
            } else {
                rayTurnoutStateComboBox->setCurrentText(turnoutStateThrown);
            }
            this->layout()->addWidget(rayTurnoutPanel);

            QPushButton* deleteRayButton;
            top->layout()->addWidget(deleteRayButton = new QPushButton(tr("Delete")));  // NOI18N
            deleteRayButton->setToolTip(tr("Delete Ray Track"));  // NOI18N
            //deleteRayButton.addActionListener((ActionEvent e) -> {
            connect(deleteRayButton, &QPushButton::clicked, [=]{
                _delete();
                editor->updateRayPanel();
            });
            rayTitledBorder = BorderFactory::createTitledBorder(BorderFactory::createLineBorder(Qt::black));

            this->setBorder(rayTitledBorder);

            showTurnoutDetails();

            rayAngleTextField->setText(twoDForm->format(rayTrack->getAngle()));
            rayTitledBorder->setTitle(tr("Ray") + " : " + QString::number(rayTrack->getConnectionIndex()));  // NOI18N
            if (rayTrack->getConnect() == nullptr) {
                rayTitledBorder->setTitle(tr("%1:").arg(
                        tr("Unconnected Ray")) + " "
                        + QString::number(rayTrack->getConnectionIndex()));  // NOI18N
            } else if (rayTrack->getConnect()->getLayoutBlock() != nullptr) {
                rayTitledBorder->setTitle(tr("%1:").arg(
                        tr("Connected Ray")) + " "
                        + rayTrack->getConnect()->getLayoutBlock()->getDisplayName());  // NOI18N
            }
        }

        /*private*/ void TurntableRayPanel::_delete() {
            int n = JOptionPane::showConfirmDialog(nullptr,
                    tr("Are you sure you want to remove this ray from the turntable, along with any connected Track Segments?"), // NOI18N
                    tr("Warning"), // NOI18N
                    JOptionPane::YES_NO_OPTION);
            if (n == JOptionPane::YES_OPTION) {
                editor->layoutTurntable->deleteRay(rayTrack);
            }
        }

        /*private*/ void TurntableRayPanel::updateDetails() {
            if (turnoutNameComboBox == nullptr || rayTurnoutStateComboBox == nullptr) {
                return;
            }
            QString turnoutName = turnoutNameComboBox->getSelectedItemDisplayName();
            if (turnoutName.isNull()) {
                turnoutName = "";
            }
            rayTrack->setTurnout(turnoutName, rayTurnoutStateValues[rayTurnoutStateComboBox->currentIndex()]);
            if (rayAngleTextField->text() != (twoDForm->format(rayTrack->getAngle()))) {
                bool ok;
                    double ang = rayAngleTextField->text().toDouble(&ok);
                    rayTrack->setAngle(ang);
                if(!ok) {
                    editor->log->error(tr("Angle is not in correct format so will skip %1").arg(rayAngleTextField->text()));  // NOI18N
                }
            }
        }

        /*private*/ void TurntableRayPanel::showTurnoutDetails() {
            bool vis = editor->layoutTurntable->isTurnoutControlled();
            rayTurnoutPanel->setVisible(vis);
            turnoutNameComboBox->setVisible(vis);
            rayTurnoutStateComboBox->setVisible(vis);
            rayTurnoutStateLabel->setVisible(vis);
        }
//    }


    /*private*/ /*final*/ /*static*/ Logger* LayoutTurntableEditor::log = LoggerFactory::getLogger("LayoutTurntableEditor");
