#include "layoutslipeditor.h"
#include "loggerfactory.h"
#include <QGridLayout>
#include "joptionpane.h"
#include "jmrijframe.h"
#include "layouteditor.h"
#include "layouttrack.h"

/**
 * MVC Editor component for LayoutSlip objects.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutSlipEditor extends LayoutTurnoutEditor {

    /**
     * constructor method.
     * @param layoutEditor main layout editor.
     */
    /*public*/ LayoutSlipEditor::LayoutSlipEditor(/*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTurnoutEditor(layoutEditor){
        //super(layoutEditor);
    }

    /*================*\
    | Edit Layout Slip |
    \*================*/

    /**
     * Edit a Slip.
     */
    //@Override
    /*public*/ void LayoutSlipEditor::editLayoutTrack(/*@Nonnull*/ LayoutTrackView* layoutTrackView) {
    if ( qobject_cast<LayoutSlipView*>(layoutTrackView) ) {
        this->layoutSlipView = (LayoutSlipView*) layoutTrackView;
        this->layoutSlip = this->layoutSlipView->getSlip();
    } else {
        log->error(tr("editLayoutTrack called with wrong type %1").arg(layoutTrackView->getName()), new Exception("traceback"));
    }
        sensorList.clear();

        if (editLayoutSlipOpen) {
            editLayoutSlipFrame->setVisible(true);
        } else if (editLayoutSlipFrame == nullptr) {   // Initialize if needed
            editLayoutSlipFrame = new JmriJFrameX(tr("Edit Slip"), false, true);  // NOI18N
            editLayoutSlipFrame->addHelpMenu("package.jmri.jmrit.display.EditLayoutSlip", true);  // NOI18N
            editLayoutSlipFrame->setLocation(50, 30);

            JPanel* contentPane = editLayoutSlipFrame->getContentPane();
            contentPane->setLayout(new QVBoxLayout());//contentPane, BoxLayout.Y_AXIS));

            // Setup turnout A
            JPanel* panel1 = new JPanel();
            panel1->setLayout(new FlowLayout());
            JLabel* turnoutNameLabel = new JLabel(tr("Turnout") + " A");  // NOI18N
            panel1->layout()->addWidget(turnoutNameLabel);
            editLayoutSlipTurnoutAComboBox = new NamedBeanComboBox((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"));
            editLayoutSlipTurnoutAComboBox->setToolTip(tr("Select a turnout, used turnouts are excluded from the list."));
            LayoutEditor::setupComboBox(editLayoutSlipTurnoutAComboBox, false, true, false);
            turnoutNameLabel->setLabelFor(editLayoutSlipTurnoutAComboBox);
            panel1->layout()->addWidget(editLayoutSlipTurnoutAComboBox);
            contentPane->layout()->addWidget(panel1);

            // Setup turnout B
            JPanel* panel1a = new JPanel();
            panel1a->setLayout(new FlowLayout());
            JLabel* turnoutBNameLabel = new JLabel(tr("BeanNameTurnout") + " B");  // NOI18N
            panel1a->layout()->addWidget(turnoutBNameLabel);
            editLayoutSlipTurnoutBComboBox = new NamedBeanComboBox((TurnoutManager*)InstanceManager::getDefault("TurnoutManager"));
            editLayoutSlipTurnoutBComboBox->setToolTip(tr("Select a turnout, used turnouts are excluded from the list."));
            LayoutEditor::setupComboBox(editLayoutSlipTurnoutBComboBox, false, true, false);
            turnoutBNameLabel->setLabelFor(editLayoutSlipTurnoutBComboBox);
            panel1a->layout()->addWidget(editLayoutSlipTurnoutBComboBox);

            contentPane->layout()->addWidget(panel1a);

            JPanel* panel2 = new JPanel();
            QGridLayout* panel2Layout;
            panel2->setLayout(panel2Layout = new QGridLayout());//0, 3, 2, 2));
            panel2Layout->setColumnMinimumWidth(0, 40);
            panel2Layout->addWidget(new QLabel("   "), 0, 0, 1, 1);
            panel2Layout->addWidget(new QLabel(tr("Turnout") + " A:"), 0, 1, 1, 1);  // NOI18N
            panel2Layout->addWidget(new QLabel(tr("Turnout") + " B:"), 0, 2, 1, 1);  // NOI18N
            //for (Map.Entry<Integer, LayoutSlip.TurnoutState> ts : layoutSlip.getTurnoutStates().entrySet())
            QHashIterator<int, TurnoutState*> ts(layoutSlip->getTurnoutStates());
            int row = 1;
            while(ts.hasNext())
            {
             ts.next();
             SampleStates* draw = new SampleStates(ts.key(),this);
             draw->repaint();
             draw->resize(QSize(40, 40));
             panel2Layout->setRowMinimumHeight(row, 40);

             panel2Layout->addWidget(draw, row, 0, 1, 1);

             panel2Layout->addWidget(ts.value()->getComboA(),row, 1, 1, 1);
             panel2Layout->addWidget(ts.value()->getComboB(), row, 2, 1, 1);
             ++row;
            }

            testPanel = new TestState(this);
            testPanel->resize(40, 40);
            //testPanel->sets(new Dimension(40, 40));
            panel2Layout->setRowMinimumHeight(row, 40);
            panel2Layout->addWidget(testPanel);
            QPushButton* testButton = new QPushButton("Test");  // NOI18N
            //testButton.addActionListener((ActionEvent e) -> toggleStateTest());
            connect(testButton, &QPushButton::clicked, [=]{
             toggleStateTest();
            });
            panel2Layout->addWidget(testButton);
            contentPane->layout()->addWidget(panel2);

            JPanel* panel33 = new JPanel();
            panel33->setLayout(new FlowLayout());
            editLayoutSlipHiddenBox->setToolTip(tr("Check to hide this track segment when not in edit mode."));  // NOI18N
            panel33->layout()->addWidget(editLayoutSlipHiddenBox);
            contentPane->layout()->addWidget(panel33);

            // setup block name
            JPanel* panel3 = new JPanel();
            panel3->setLayout(new FlowLayout());
            JLabel* block1NameLabel = new JLabel(tr("Block Name:"));  // NOI18N
            panel3->layout()->addWidget(block1NameLabel);
            block1NameLabel->setLabelFor(editLayoutSlipBlockNameComboBox);
            panel3->layout()->addWidget(editLayoutSlipBlockNameComboBox);
            LayoutEditor::setupComboBox(editLayoutSlipBlockNameComboBox, false, true, true);
            editLayoutSlipBlockNameComboBox->setToolTip(tr("Edit Block name to change the linked block. If new name, block will be created."));  // NOI18N

            contentPane->layout()->addWidget(panel3);
            // set up Edit Block buttons
            JPanel* panel4 = new JPanel();
            panel4->setLayout(new FlowLayout());
            // Edit Block
            panel4->layout()->addWidget(editLayoutSlipBlockButton = new QPushButton(tr("Create/Edit Block %1").arg( "")));  // NOI18N
            //editLayoutSlipBlockButton.addActionListener(this::editLayoutSlipEditBlockPressed
            connect(editLayoutSlipBlockButton, &QPushButton::clicked, [=]{
             editLayoutSlipEditBlockPressed();
            });
            editLayoutSlipBlockButton->setToolTip(tr("Click here to create/edit information for Block %1 shown above.", "")); // empty value for block 1  // NOI18N

            contentPane->layout()->addWidget(panel4);

            // set up Done and Cancel buttons
            JPanel* panel5 = new JPanel();
            panel5->setLayout(new FlowLayout());
            ActionListenerDone* al_editLayoutSlipDonePressed = new ActionListenerDone(this);
            ActionListenerCancel* al_editLayoutSlipCancelPressed = new ActionListenerCancel(this);
            addDoneCancelButtons(panel5, editLayoutSlipFrame->getRootPane(),
                    al_editLayoutSlipDonePressed, al_editLayoutSlipCancelPressed);
            contentPane->layout()->addWidget(panel5);
        }

        editLayoutSlipHiddenBox->setChecked(layoutSlipView->isHidden());

        // Set up for Edit
        QList<Turnout*> currentTurnouts = QList<Turnout*>();
        currentTurnouts.append(layoutSlip->getTurnout());
        currentTurnouts.append(layoutSlip->getTurnoutB());

        editLayoutSlipTurnoutAComboBox->setSelectedItem(layoutSlip->getTurnout());
#if 0
        editLayoutSlipTurnoutAComboBox->addPopupMenuListener(
                layoutEditor->newTurnoutComboBoxPopupMenuListener(editLayoutSlipTurnoutAComboBox, currentTurnouts));
#endif
        editLayoutSlipTurnoutBComboBox->setSelectedItem(layoutSlip->getTurnoutB());
#if 0
        editLayoutSlipTurnoutBComboBox->addPopupMenuListener(
                layoutEditor->newTurnoutComboBoxPopupMenuListener(editLayoutSlipTurnoutBComboBox, currentTurnouts));
#endif
        BlockManager* bm = (BlockManager*)InstanceManager::getDefault("BlockManager");
#if 0
        editLayoutSlipBlockNameComboBox->getEditor().setItem(bm->getBlock(layoutSlip->getBlockName()));
#endif
        editLayoutSlipBlockNameComboBox->setEnabled(!hasNxSensorPairs(layoutSlip->getLayoutBlock()));

        editLayoutSlipFrame->addWindowListener(new LSEWindowListener(this));
//        {
//            @Override
//            public void windowClosing(WindowEvent e) {
//                editLayoutSlipCancelPressed(null);
//            }
//        });
        editLayoutSlipFrame->pack();
        editLayoutSlipFrame->setVisible(true);
        editLayoutSlipOpen = true;
        editLayoutSlipNeedsBlockUpdate = false;

        showSensorMessage();
    }   // editLayoutSlip

    /*
     * draw the current state (STATE_AC, STATE_BD  et al)
     * with fixed geometry
     */
    /*private*/ void LayoutSlipEditor::drawSlipState(QPainter* g2, int state)
    {
     QPointF cenP = layoutSlipView->getCoordsCenter();
     QPointF A = MathUtil::subtract(layoutSlipView->getCoordsA(), cenP);
     QPointF B = MathUtil::subtract(layoutSlipView->getCoordsB(), cenP);
     QPointF C = MathUtil::subtract(layoutSlipView->getCoordsC(), cenP);
     QPointF D = MathUtil::subtract(layoutSlipView->getCoordsD(), cenP);

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

         drawSlipStatePart1A(g2,state, A,B,C,D);
     }
     else
     {
         g2->drawLine(QLine(B.toPoint(), MathUtil::oneThirdPoint(B, D).toPoint()));
         g2->drawLine(QLine(D.toPoint(), MathUtil::oneThirdPoint(D, B).toPoint()));
     }

     if(layoutSlip->getTurnoutType() == LayoutTurnout::DOUBLE_SLIP )
      drawSlipStatePart2B(g2,state, A,B,C,D);
     else
      drawSlipStatePart2A(g2,state, A,B,C,D);
}

    /*protected*/ void LayoutSlipEditor::drawSlipStatePart1A(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D) {
    }

    /*protected*/ void LayoutSlipEditor::drawSlipStatePart1B(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D) {
        g2->drawLine(QLineF(B, MathUtil::oneThirdPoint(B, C)));
        g2->drawLine(QLineF(C, MathUtil::oneThirdPoint(C, B)));
    }

    // all others implementation
    /*protected*/ void LayoutSlipEditor::drawSlipStatePart2A(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D) {
        g2->drawLine(QLineF(A, MathUtil::oneThirdPoint(A, D)));
        g2->drawLine(QLineF(D, MathUtil::oneThirdPoint(D, A)));

        QPen pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);

        if (state == LayoutTurnout::STATE_AD)
        {
            //g2.setColor(Color.red);
         pen.setColor(Qt::red);
         g2->setPen(pen);
         g2->drawLine(QLineF(A, D));
        }
        else if (state == LayoutTurnout::STATE_AC)
        {
            g2->drawLine(QLineF(B, MathUtil::oneThirdPoint(B, D)));
            g2->drawLine(QLineF(D, MathUtil::oneThirdPoint(D, B)));

            //g2.setColor(Color.red);
            pen.setColor(Qt::red);
            g2->setPen(pen);
            g2->drawLine(QLineF(A, C));
        }
        else if (state == LayoutTurnout::STATE_BD)
        {
            //g2.setColor(Color.red);
         pen.setColor(Qt::red);
         g2->setPen(pen);
            g2->drawLine(QLineF(B, D));
        }
        else
        {
            g2->drawLine(QLineF(B, MathUtil::oneThirdPoint(B, D)));
            g2->drawLine(QLineF(D, MathUtil::oneThirdPoint(D, B)));
        }
    }

    // DOUBLE_SLIP implementation
    /*protected*/ void LayoutSlipEditor::drawSlipStatePart2B(QPainter* g2, int state, QPointF A, QPointF B, QPointF C, QPointF D) {
      QPen pen = QPen(Qt::black, 2, Qt::SolidLine, Qt::FlatCap, Qt::RoundJoin);

        if (state == LayoutTurnout::STATE_AC)
        {
            g2->drawLine(QLineF(B, MathUtil::oneThirdPoint(B, D)));
            g2->drawLine(QLineF(D, MathUtil::oneThirdPoint(D, B)));

            //g2.setColor(Color.red);
            pen.setColor(Qt::red);
            g2->setPen(pen);
            g2->drawLine(QLineF(A, C));
        }
        else if (state == LayoutTurnout::STATE_BD)
        {
            //g2.setColor(Color.red);
         pen.setColor(Qt::red);
         g2->setPen(pen);
            g2->drawLine(QLineF(B, D));
        }
        else if (state == LayoutTurnout::STATE_AD)
        {
            g2->drawLine(QLineF(B, MathUtil::oneThirdPoint(B, C)));

            g2->drawLine(QLineF(C, MathUtil::oneThirdPoint(C, B)));

            //g2.setColor(Color.red);
            pen.setColor(Qt::red);
            g2->setPen(pen);
            g2->drawLine(QLineF(A, D));
        }
        else if (state == LayoutTurnout::STATE_BC)
        {
            g2->drawLine(QLineF(A, MathUtil::oneThirdPoint(A, D)));

            g2->drawLine(QLineF(D, MathUtil::oneThirdPoint(D, A)));
            //g2.setColor(Color.red);
            pen.setColor(Qt::red);
            g2->setPen(pen);
            g2->drawLine(QLineF(B, C));
        }
        else
        {
            g2->drawLine(QLineF(B, MathUtil::oneThirdPoint(B, D)));
            g2->drawLine(QLineF(D, MathUtil::oneThirdPoint(D, B)));
        }
    }



//    class SampleStates extends JPanel {

//        // Methods, constructors, fields.
//        SampleStates(int state) {
//            super();
//            this.state = state;
//        }
//        int state;

//        @Override
//        public void paintComponent(Graphics g) {
//            super.paintComponent(g);    // paints background
//            if (g instanceof Graphics2D) {
//                drawSlipState((Graphics2D) g, state);
//            }
//        }
//    }

    /**
     * Toggle slip states if clicked on, physical turnout exists, and not
     * disabled.
     */
    /*public*/ void LayoutSlipEditor::toggleStateTest() {
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

        if (editLayoutSlipTurnoutAComboBox->getSelectedItem() != nullptr) {
            ((Turnout*)editLayoutSlipTurnoutAComboBox->getSelectedItem())->setCommandedState(turnAState);
        }
        if (editLayoutSlipTurnoutBComboBox->getSelectedItem() != nullptr) {
            ((Turnout*)editLayoutSlipTurnoutBComboBox->getSelectedItem())->setCommandedState(turnBState);
        }
        if (testPanel != nullptr) {
            testPanel->repaint();
        }
    }

//    class TestState extends JPanel {

//        @Override
//        public void paintComponent(Graphics g) {
//            super.paintComponent(g);
//            if (g instanceof Graphics2D) {
//                drawSlipState((Graphics2D) g, testState);
//            }
//        }
//    }


    /*private*/ void LayoutSlipEditor::editLayoutSlipEditBlockPressed(/*ActionEvent a*/) {
        // check if a block name has been entered
        QString newName = editLayoutSlipBlockNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutSlip->getBlockName() != (newName)) {
            // get new block, or null if block has been removed
            layoutSlip->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
            editLayoutSlipNeedsRedraw = true;
            editLayoutSlipNeedsBlockUpdate = true;
        }
        // check if a block exists to edit
        if (layoutSlip->getLayoutBlock() == nullptr) {
            JOptionPane::showMessageDialog(editLayoutSlipFrame,
                    tr("Error - Cannot create or edit a block without a name.\nPlease enter a block name and try again."),
                    tr("Error"), JOptionPane::ERROR_MESSAGE);
            return;
        }
        layoutSlip->getLayoutBlock()->editLayoutBlock(editLayoutSlipFrame);
        editLayoutSlipNeedsRedraw = true;
        layoutEditor->setDirty();
    }

    /*private*/ void LayoutSlipEditor::editLayoutSlipDonePressed(/*ActionEvent a*/) {
        QString newName = editLayoutSlipTurnoutAComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutSlip->getTurnoutName() != (newName)) {
            if (layoutEditor->validatePhysicalTurnout(newName, editLayoutSlipFrame)) {
                layoutSlip->setTurnout(newName);
            } else {
                layoutSlip->setTurnout("");
            }
            editLayoutSlipNeedsRedraw = true;
        }

        newName = editLayoutSlipTurnoutBComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutSlip->getTurnoutBName()!=(newName)) {
            if (layoutEditor->validatePhysicalTurnout(newName, editLayoutSlipFrame)) {
                layoutSlip->setTurnoutB(newName);
            } else {
                layoutSlip->setTurnoutB("");
            }
            editLayoutSlipNeedsRedraw = true;
        }

        newName = editLayoutSlipBlockNameComboBox->getSelectedItemDisplayName();
        if (newName.isNull()) {
            newName = "";
        }
        if (layoutSlip->getBlockName() != (newName)) {
            // get new block, or null if block has been removed
            layoutSlip->setLayoutBlock(layoutEditor->provideLayoutBlock(newName));
            editLayoutSlipNeedsRedraw = true;
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
            editLayoutSlipNeedsBlockUpdate = true;
        }
        for (TurnoutState* ts : layoutSlip->getTurnoutStates().values()) {
            ts->updateStatesFromCombo();
        }

        // set hidden
        bool oldHidden = layoutSlipView->isHidden();
        layoutSlip->setHidden(editLayoutSlipHiddenBox->isChecked());
        if (oldHidden != layoutSlipView->isHidden()) {
            editLayoutSlipNeedsRedraw = true;
        }

        editLayoutSlipOpen = false;
        editLayoutSlipFrame->setVisible(false);
        editLayoutSlipFrame->dispose();
        editLayoutSlipFrame = nullptr;
        if (editLayoutSlipNeedsBlockUpdate) {
            layoutSlip->updateBlockInfo();
        }
        if (editLayoutSlipNeedsRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLayoutSlipNeedsRedraw = false;
        }
    }

    /*private*/ void LayoutSlipEditor::editLayoutSlipCancelPressed(/*ActionEvent a*/) {
        editLayoutSlipOpen = false;
        editLayoutSlipFrame->setVisible(false);
        editLayoutSlipFrame->dispose();
        editLayoutSlipFrame = nullptr;
        if (editLayoutSlipNeedsBlockUpdate) {
            layoutSlip->updateBlockInfo();
        }
        if (editLayoutSlipNeedsRedraw) {
            layoutEditor->redrawPanel();
            layoutEditor->setDirty();
            editLayoutSlipNeedsRedraw = false;
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* LayoutSlipEditor::log = LoggerFactory::getLogger("LayoutSlipEditor");
