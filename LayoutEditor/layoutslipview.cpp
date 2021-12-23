#include "layoutslipview.h"
#include "layoutslipeditor.h"
#include "mathutil.h"
#include "layouteditor.h"
#include "loggerfactory.h"
#include <QMenu>
#include "joptionpane.h"
#include "layouteditortoolbarpanel.h"

/**
 * MVC View component for the LayoutSlip class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class LayoutSlipView extends LayoutTurnoutView {

    /**
     * Constructor method.
     * @param slip the layout sip to create view for.
     */
/*public*/ LayoutSlipView::LayoutSlipView(/*@Nonnull*/  LayoutSlip* slip,
            QPointF c, double rot,
            /*@Nonnull*/  LayoutEditor* layoutEditor) : LayoutTurnoutView(slip, c, rot, layoutEditor){
        //super(slip, c, rot, layoutEditor);
        this->slip = slip;

        dispA =  QPointF(-20.0, 0.0);
        pointA = MathUtil::add(getCoordsCenter(), dispA);
        pointC = MathUtil::subtract(getCoordsCenter(), dispA);
        dispB =  QPointF(-14.0, 14.0);
        pointB = MathUtil::add(getCoordsCenter(), dispB);
        pointD = MathUtil::subtract(getCoordsCenter(), dispB);

        rotateCoords(rot);

        editor = new LayoutSlipEditor(layoutEditor);
    }



    /*public*/ LayoutSlip* LayoutSlipView::getSlip() {return slip; }
    // this should only be used for debugging...
    //@Override
    /*public*/ QString LayoutSlipView::toString() {
     return tr("LayoutSlip %1 (%2)").arg(getId(), getSlipStateString(getSlipState()));
    }

    /*public*/ LayoutTurnout::TurnoutType LayoutSlipView::getSlipType() {
        return slip->getSlipType();
    }

    /*public*/ int LayoutSlipView::getSlipState() {
        return slip->getSlipState();
    }

    /*public*/ QString LayoutSlipView::getTurnoutBName() {
       return slip->getTurnoutBName();
    }

    /*public*/ Turnout* LayoutSlipView::getTurnoutB() {
       return slip->getTurnoutB();
    }

    /*public*/ void LayoutSlipView::setTurnoutB(/*@CheckForNull*/   QString tName) {
        slip->setTurnoutB(tName);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ LayoutTrack* LayoutSlipView::getConnection(HitPointType::TYPES connectionType) /*throw (JmriException)*/ {
        return slip->getConnection(connectionType);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LayoutSlipView::setConnection(HitPointType::TYPES connectionType, /*@CheckForNull*/  LayoutTrack* o, HitPointType::TYPES type) /*throw (JmriException)*/ {
        slip->setConnection(connectionType, o, type);
    }

    /*public*/ QString LayoutSlipView::getDisplayName() {
        QString name = "Slip " + getId();
        QString tnA = getTurnoutName();
        QString tnB = getTurnoutBName();
        if ((tnA != "") && !tnA.isEmpty()) {
            name += " (" + tnA;
        }
        if ((tnB != "") && !tnB.isEmpty()) {
            if (name.contains(" (")) {
                name += ", ";
            } else {
                name += "(";
            }
            name += tnB;
        }
        if (name.contains("(")) {
            name += ")";
        }
        return name;
    }

    /*private*/ QString LayoutSlipView::getSlipStateString(int slipState) {
       return slip->getSlipStateString(slipState);
    }

    /**
     * Toggle slip states if clicked on, physical turnout exists, and not
     * disabled
     * @param selectedPointType See {@link LayoutSlip#toggleState} for definition
     */
    /*public*/ void LayoutSlipView::toggleState(HitPointType::TYPES selectedPointType) {
       slip->toggleState(selectedPointType);
    }

    /**
     * is this turnout occupied?
     *
     * @return true if occupied
     */
    /*private*/ bool LayoutSlipView::isOccupied() {
       return slip->isOccupied();
    }

    //@Override
    /*public*/ QPointF LayoutSlipView::getCoordsA() {
        return pointA;
    }

    //@Override
    /*public*/ QPointF LayoutSlipView::getCoordsB() {
        return pointB;
    }

    //@Override
    /*public*/ QPointF LayoutSlipView::getCoordsC() {
        return pointC;
    }

    //@Override
    /*public*/ QPointF LayoutSlipView::getCoordsD() {
        return pointD;
    }

    QPointF LayoutSlipView::getCoordsLeft() {
        QPointF leftCenter = MathUtil::midPoint(getCoordsA(), getCoordsB());
        double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
        double leftFract = circleRadius / MathUtil::distance(getCoordsCenter(),leftCenter);
        return MathUtil::lerp(getCoordsCenter(), leftCenter, leftFract);
    }

    QPointF LayoutSlipView::getCoordsRight() {
        QPointF rightCenter = MathUtil::midPoint(getCoordsC(), getCoordsD());
        double circleRadius = layoutEditor->SIZE * layoutEditor->getTurnoutCircleSize();
        double rightFract = circleRadius / MathUtil::distance(getCoordsCenter(),rightCenter);
        return MathUtil::lerp(getCoordsCenter(), rightCenter, rightFract);
    }

    /**
     * return the coordinates for the specified connection type
     *
     * @param connectionType the connection type
     * @return the QPointF coordinates
     */
    //@Override
    /*public*/ QPointF LayoutSlipView::getCoordsForConnectionType(HitPointType::TYPES connectionType) {
        QPointF result = getCoordsCenter();
        switch (connectionType) {
            case HitPointType::SLIP_A:
                result = getCoordsA();
                break;
            case HitPointType::SLIP_B:
                result = getCoordsB();
                break;
            case HitPointType::SLIP_C:
                result = getCoordsC();
                break;
            case HitPointType::SLIP_D:
                result = getCoordsD();
                break;
            case HitPointType::SLIP_LEFT:
                result = getCoordsLeft();
                break;
            case HitPointType::SLIP_RIGHT:
                result = getCoordsRight();
                break;
            default:
                log->error(tr("%1.getCoordsForConnectionType(%2); Invalid Connection Type").arg(getName(), HitPointType::toString(connectionType))); // I18IN
        }
        return result;
    }

    /**
     * {@inheritDoc}
     */
    // just here for testing; should be removed when I'm done...
    //@Override
    /*public*/ QRectF LayoutSlipView::getBounds() {
        return LayoutTurnoutView::getBounds();
    }

    //@Override
    /*public*/ void LayoutSlipView::updateBlockInfo() {
        slip->updateBlockInfo();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ HitPointType::TYPES LayoutSlipView::findHitPointType(/*@Nonnull*/  QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
        HitPointType::TYPES result = HitPointType::NONE;  // assume point not on connection

        if (!requireUnconnected) {
            // calculate radius of turnout control circle
            double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();

            // get left and right centers
            QPointF leftCenter = getCoordsLeft();
            QPointF rightCenter = getCoordsRight();

            if (useRectangles) {
                // calculate turnout's left control rectangle
                QRectF leftRectangle = layoutEditor->layoutEditorControlCircleRectAt(leftCenter);
                if (leftRectangle.contains(hitPoint)) {
                    // point is in this turnout's left control rectangle
                    result = HitPointType::SLIP_LEFT;
                }
                QRectF rightRectangle = layoutEditor->layoutEditorControlCircleRectAt(rightCenter);
                if (rightRectangle.contains(hitPoint)) {
                    // point is in this turnout's right control rectangle
                    result = HitPointType::SLIP_RIGHT;
                }
            } else {
                // check east/west turnout control circles
                double leftDistance = MathUtil::distance(hitPoint,leftCenter);
                double rightDistance = MathUtil::distance(hitPoint,rightCenter);

                if ((leftDistance <= circleRadius) || (rightDistance <= circleRadius)) {
                    // mouse was pressed on this slip
                    result = (leftDistance < rightDistance) ? HitPointType::SLIP_LEFT : HitPointType::SLIP_RIGHT;
                }
            }
        }

        // have we found anything yet?
        if (result == HitPointType::NONE) {
            // rather than create rectangles for all the points below and
            // see if the passed in point is in one of those rectangles
            // we can create a rectangle for the passed in point and then
            // test if any of the points below are in that rectangle instead.
            QRectF r = layoutEditor->layoutEditorControlRectAt(hitPoint);

            if (!requireUnconnected || (getConnectA() == nullptr)) {
                // check the A connection point
                if (r.contains(getCoordsA())) {
                    result = HitPointType::SLIP_A;
                }
            }

            if (!requireUnconnected || (getConnectB() == nullptr)) {
                // check the B connection point
                if (r.contains(getCoordsB())) {
                    result = HitPointType::SLIP_B;
                }
            }

            if (!requireUnconnected || (getConnectC() == nullptr)) {
                // check the C connection point
                if (r.contains(getCoordsC())) {
                    result = HitPointType::SLIP_C;
                }
            }

            if (!requireUnconnected || (getConnectD() == nullptr)) {
                // check the D connection point
                if (r.contains(getCoordsD())) {
                    result = HitPointType::SLIP_D;
                }
            }
        }
        return result;
    }   // findHitPointType

    /*
    * Modify coordinates methods
     */
    /**
     * set center coordinates
     *
     * @param p the coordinates to set
     */
    //@Override
    /*public*/ void LayoutSlipView::setCoordsCenter(/*@Nonnull*/  QPointF p) {
        LayoutTurnoutView::setCoordsCenter(p);
        pointA = MathUtil::add(getCoordsCenter(), dispA);
        pointB = MathUtil::add(getCoordsCenter(), dispB);
        pointC = MathUtil::subtract(getCoordsCenter(), dispA);
        pointD = MathUtil::subtract(getCoordsCenter(), dispB);
    }

    //@Override
    /*public*/ void LayoutSlipView::setCoordsA(/*@Nonnull*/  QPointF p) {
        pointA = p;
        dispA = MathUtil::subtract(pointA, getCoordsCenter());
        pointC = MathUtil::subtract(getCoordsCenter(), dispA);
    }

    //@Override
    /*public*/ void LayoutSlipView::setCoordsB(/*@Nonnull*/  QPointF p) {
        pointB = p;
        dispB = MathUtil::subtract(pointB, getCoordsCenter());
        pointD = MathUtil::subtract(getCoordsCenter(), dispB);
    }

    //@Override
    /*public*/ void LayoutSlipView::setCoordsC(/*@Nonnull*/  QPointF p) {
        pointC = p;
        dispA = MathUtil::subtract(getCoordsCenter(), pointC);
        pointA = MathUtil::add(getCoordsCenter(), dispA);
    }

    //@Override
    /*public*/ void LayoutSlipView::setCoordsD(/*@Nonnull*/  QPointF p) {
        pointD = p;
        dispB = MathUtil::subtract(getCoordsCenter(), pointD);
        pointB = MathUtil::add(getCoordsCenter(), dispB);
    }


    /**
     * {@inheritDoc}
     */
    //@Override
    /*@Nonnull*/
    /*protected*/ QMenu* LayoutSlipView:: showPopup(/*@CheckForNull*/  QGraphicsSceneMouseEvent* mouseEvent) {
        if (popup != nullptr) {
            popup->clear();
        } else {
            popup = new QMenu();
        }
        QMetaEnum mett = QMetaEnum::fromType<LayoutTurnout::TurnoutType>();
#if 1
        if (layoutEditor->isEditable()) {
            QString slipStateString = getSlipStateString(getSlipState());
            slipStateString = tr(" (%1)").arg(slipStateString);

            QAction* jmi = nullptr;
            switch (getSlipType()) {
                case LayoutTurnout::TurnoutType::SINGLE_SLIP: {
                    jmi = popup->addAction(tr("%1:").arg(tr("Single Slip")) + getId() + slipStateString);
                    break;
                }
                case LayoutTurnout::TurnoutType::DOUBLE_SLIP: {
                    jmi = popup->addAction(tr("%1:").arg(tr("Double Slip")) + getId() + slipStateString);
                    break;
                }
                default: {
                    log->error(tr("%1.showPopup(<mouseEvent>); Invalid slip type: %2").arg(getName(), mett.valueToKey(getSlipType()))); // I18IN
                }
            }
            if (jmi != nullptr) {
                jmi->setEnabled(false);
            }

            if (getTurnout() == nullptr) {
                jmi = popup->addSection(tr("No Turnout Set"));
            } else {
                QString stateString = getTurnoutStateString(getTurnout()->getKnownState());
                stateString = tr(" (%1)").arg(stateString);
                jmi = popup->addAction(tr("Turnout") + ": " + getTurnoutName() + stateString);
            }
             jmi->setEnabled(false);

            if (getTurnoutB() == nullptr) {
                jmi = popup->addSection(tr("No Turnout Set"));
            } else {
                QString stateString = getTurnoutStateString(getTurnoutB()->getKnownState());
                stateString = tr(" (%1)").arg(stateString);
                jmi = popup->addAction(tr("Turnout") + ": " + getTurnoutBName() + stateString);
            }
             jmi->setEnabled(false);

            bool blockAssigned = false;
            if (getBlockName().isEmpty()) {
                jmi = popup->addAction(tr("No Block Set"));
                 jmi->setEnabled(false);
            } else {
                blockAssigned = true;

                jmi = popup->addAction(tr("%1:").arg(tr("Block %1").arg("A") + getLayoutBlock()->getDisplayName()));
                 jmi->setEnabled(false);

                // check if extra blocks have been entered
                if ((getLayoutBlockB() != nullptr) && (getLayoutBlockB() != getLayoutBlock())) {
                    jmi = popup->addAction(tr("%1:").arg(tr("Block %1").arg("B") + getLayoutBlockB()->getDisplayName()));
                     jmi->setEnabled(false);
                }
                if ((getLayoutBlockC() != nullptr) && (getLayoutBlockC() != getLayoutBlock())) {
                    jmi = popup->addAction(tr("%1:").arg(tr("Block %1").arg("C") + getLayoutBlockC()->getDisplayName()));
                     jmi->setEnabled(false);
                }
                if ((getLayoutBlockD() != nullptr) && (getLayoutBlockD() != getLayoutBlock())) {
                    jmi = popup->addAction(tr("%1:").arg(tr("Block %1").arg("D") + getLayoutBlockD()->getDisplayName()));
                     jmi->setEnabled(false);
                }
            }

            // if there are any track connections
            QAction* act = nullptr;
            if ((getConnectA() != nullptr) || (getConnectB() != nullptr)
                    || (getConnectC() != nullptr) || (getConnectD() != nullptr)) {
                QMenu* connectionsMenu = new QMenu(tr("Connections")); // there is no pane opening (which is what ... implies)
                if (getConnectA() != nullptr) {
                    connectionsMenu->addAction(act = new AbstractAction(tr("%1:").arg("A") + getConnectA()->getName(),this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
                    connect(act, &QAction::triggered, [=]{
                            LayoutEditorFindItems* lf = layoutEditor->getFinder();
                            LayoutTrack* lt = lf->findObjectByName(getConnectA()->getName());
                            // this shouldn't ever be null... however...
                            if (lt != nullptr) {
                                LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv->getBounds());
                                ltv->showPopup();
                            }
//                        }
                    });
                }
                if (getConnectB() != nullptr) {
                    connectionsMenu->addAction(act = new AbstractAction(tr("%1:").arg("B") + getConnectB()->getName(),this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
                    connect(act, &QAction::triggered, [=]{
                            LayoutEditorFindItems* lf = layoutEditor->getFinder();
                            LayoutTrack* lt = lf->findObjectByName(getConnectB()->getName());
                            // this shouldn't ever be null... however...
                            if (lt != nullptr) {
                                LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv->getBounds());
                                ltv->showPopup();
                            }
//                        }
                    });
                }
                if (getConnectC() != nullptr) {
                    connectionsMenu->addAction(act =new AbstractAction(tr("%1:").arg("C") + getConnectC()->getName(), this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
                    connect(act, &QAction::triggered, [=]{
                            LayoutEditorFindItems* lf = layoutEditor->getFinder();
                            LayoutTrack* lt = lf->findObjectByName(getConnectC()->getName());
                            // this shouldn't ever be null... however...
                            if (lt != nullptr) {
                                LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv->getBounds());
                                ltv->showPopup();
                            }
//                        }
                    });
                }
                if (getConnectD() != nullptr) {
                    connectionsMenu->addAction(act =new AbstractAction(tr("%1:", "D") + getConnectD()->getName(), this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
                    connect(act, &QAction::triggered, [=]{
                            LayoutEditorFindItems* lf = layoutEditor->getFinder();
                            LayoutTrack* lt = lf->findObjectByName(getConnectD()->getName());
                            // this shouldn't ever be null... however...
                            if (lt != nullptr) {
                                LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv->getBounds());
                                ltv->showPopup();
                            }
//                        }
                    });
                }
                popup->addMenu(connectionsMenu);
            }

            popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));

            JCheckBoxMenuItem* hiddenCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Hidden"),this);
            hiddenCheckBoxMenuItem->setChecked(isHidden());
            popup->addAction(hiddenCheckBoxMenuItem);
//            hiddenCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e1) -> {
//                JCheckBoxMenuItem o = (JCheckBoxMenuItem) e1.getSource();
            connect(hiddenCheckBoxMenuItem, &QAction::triggered, [=]{
                setHidden(hiddenCheckBoxMenuItem->isChecked());
            });

            JCheckBoxMenuItem* cbmi = new JCheckBoxMenuItem(tr("Disabled"), this);
            cbmi->setChecked(isDisabled());
            popup->addAction(cbmi);
//            cbmi.addActionListener((java.awt.event.ActionEvent e2) -> {
//                JCheckBoxMenuItem o = (JCheckBoxMenuItem) e2.getSource();
            connect(cbmi, &QAction::triggered, [=]{
                setDisabled(cbmi->isChecked());
            });

            cbmi = new JCheckBoxMenuItem(tr("Disabled When Occupied"), this);
            cbmi->setChecked(isDisabledWhenOccupied());
            popup->addAction(cbmi);
//            cbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
//                JCheckBoxMenuItem o = (JCheckBoxMenuItem) e3.getSource();
            connect(cbmi, &QAction::triggered, [=]{
                setDisableWhenOccupied(cbmi->isChecked());
            });

            popup->addAction(act = new AbstractAction(tr("Edit"),this));
//            {
//                //@Override
//                /*public*/ void actionPerformed(ActionEvent e) {
            connect(act, &QAction::triggered, [=]{
                    editor->editLayoutTrack(this);
//                }
            });
            popup->addAction(act = new AbstractAction(tr("Delete"), this));
//            {
//                //@Override
//                /*public*/ void actionPerformed(ActionEvent e) {
            connect(act, &QAction::triggered, [=]{
                    if (canRemove() && layoutEditor->removeLayoutSlip(slip)) {
                        // Returned true if user did not cancel
                        remove();
                        dispose();
                    }
//                }
            });
            if ((getConnectA() == nullptr) && (getConnectB() == nullptr)
                    && (getConnectC() == nullptr) && (getConnectD() == nullptr)) {
                QAction* rotateItem = new QAction(tr("Rotate") + "...", this);
                popup->addAction(rotateItem);
//                rotateItem.addActionListener(
//                        (ActionEvent event) -> {
                connect(rotateItem, &QAction::triggered, [=]{
                            bool entering = true;
                            bool error = false;
                            QString newAngle = "";
                            while (entering) {
                                // prompt for rotation angle
                                error = false;
                                newAngle = JOptionPane::showInputDialog(layoutEditor,
                                        tr("%1:").arg(tr("Enter Rotation Angle (degrees CW)")));
                                if (newAngle.isEmpty()) {
                                    return;  // cancelled
                                }
                                double rot = 0.0;
                                bool ok;
                                    rot =newAngle.toDouble(&ok);
                                if(!ok) {
                                    JOptionPane::showMessageDialog(layoutEditor, tr("Error in rotation entry:")
                                            + " " /*+ e1*/, tr("Error"), JOptionPane::ERROR_MESSAGE);
                                    error = true;
                                    newAngle = "";
                                }
                                if (!error) {
                                    entering = false;
                                    if (rot != 0.0) {
                                        rotateCoords(rot);
                                        layoutEditor->redrawPanel();
                                    }
                                }
                            }
                        }
                );
            }
            if ((getTurnout() != nullptr) && (getTurnoutB() != nullptr)) {
                if (blockAssigned) {
                    AbstractAction* ssaa = new AbstractAction(tr("Set Signal Heads..."),this);
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
                    connect(ssaa, &QAction::triggered, [=]{
                            layoutEditor->getLETools()->setSignalsAtSlipFromMenu(
                                    slip,
                                    getLayoutEditorToolBarPanel()->signalIconEditor,
                                    getLayoutEditorToolBarPanel()->signalFrame);
//                        }
                    });
                    QMenu* jm = new QMenu(tr("Set Signal Heads..."));
                    if (layoutEditor->getLETools()->addLayoutSlipSignalHeadInfoToMenu(
                            slip, jm)) {
                        jm->addAction(ssaa);
                        popup->addMenu(
                           jm);
                    } else {
                        popup->addAction(ssaa);
                    }

                }

                /*final*/ QStringList boundaryBetween = getBlockBoundaries();
                bool blockBoundaries = false;

                for (int i = 0; i < 4; i++) {
                    if (boundaryBetween[i] != "") {
                        blockBoundaries = true;
                    }
                }
                if (blockBoundaries) {
                    popup->addAction(act = new AbstractAction(tr("Set Signal Masts..."),this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
                    connect(act, &QAction::triggered, [=]{
                            layoutEditor->getLETools()->setSignalMastsAtSlipFromMenu(
                                    slip,
                                    boundaryBetween.toVector(),
                                    getLayoutEditorToolBarPanel()->signalFrame);
//                        }
                    });
                    popup->addAction(act = new AbstractAction(tr("Set Sensors..."),this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent e) {
                    connect(act, &QAction::triggered, [=]{
                            layoutEditor->getLETools()->setSensorsAtSlipFromMenu(
                                    slip, boundaryBetween.toVector(),
                                    getLayoutEditorToolBarPanel()->sensorIconEditor,
                                    getLayoutEditorToolBarPanel()->sensorFrame);
//                        }
                    });
                }

                if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"))->isAdvancedRoutingEnabled()
                        && blockAssigned) {
                    popup->addAction(act = new AbstractAction(tr("ViewBlockRouting"),this));
//                    {
//                        //@Override
//                        /*public*/ void actionPerformed(ActionEvent event) {
                    connect(act, &QAction::triggered, [=]{
                            AbstractAction* routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
                            routeTableAction->actionPerformed(/*event*/);
//                        }
                    });
                }
            }
            setAdditionalEditPopUpMenu(popup);
            layoutEditor->setShowAlignmentMenu(popup);
//            popup->show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
            popup->exec(QCursor::pos());
        } else if (!viewAdditionalMenu.isEmpty()) {
            setAdditionalViewPopUpMenu(popup);
//            popup->show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
            popup->exec(QCursor::pos());
        }
#endif
        return popup;
    }   // showPopup

    //@Override
    /*public*/ QList<QString> LayoutSlipView::getBlockBoundaries() {
        return slip->getBlockBoundaries()->toList();
    }

    /**
     * Clean up when this object is no longer needed. Should not be called while
     * the object is still displayed; see remove()
     */
    //@Override
    /*public*/ void LayoutSlipView::dispose() {
        if (popup != nullptr) {
            popup->clear();
        }
        popup = nullptr;
    }

    /**
     * Removes this object from display and persistance
     */
    //@Override
    /*public*/ void LayoutSlipView::remove() {
        slip->remove();
    }


    /*public*/ int LayoutSlipView::getTurnoutState(/*@Nonnull*/  Turnout* turn, int state) {
       return slip->getTurnoutState(turn, state);
    }

    /*public*/ int LayoutSlipView::getTurnoutState(int state) {
       return slip->getTurnoutState(state);
    }

    /*public*/ int LayoutSlipView::getTurnoutBState(int state) {
       return slip->getTurnoutBState(state);
    }

    /*public*/ void LayoutSlipView::setTurnoutStates(int state, /*@Nonnull*/  QString turnStateA, /*@Nonnull*/  QString turnStateB) {
        slip->setTurnoutStates(state, turnStateA, turnStateB);
    }

    /**
     * Check if either turnout is inconsistent. This is used to create an
     * alternate slip image.
     *
     * @return true if either turnout is inconsistent.
     */
    /*private*/ bool LayoutSlipView::isTurnoutInconsistent() {
       return slip->isTurnoutInconsistent();
    }

    //@Override
    /*protected*/ void LayoutSlipView::draw1(EditScene* g2, bool drawMain, bool isBlock) {
         if (isBlock && getLayoutBlock() == nullptr) {
             // Skip the block layer since there is no block assigned.
             return;
         }

         QPointF pA = getCoordsA();
         QPointF pB = getCoordsB();
         QPointF pC = getCoordsC();
         QPointF pD = getCoordsD();

         bool mainlineA = isMainlineA();
         bool mainlineB = isMainlineB();
         bool mainlineC = isMainlineC();
         bool mainlineD = isMainlineD();

         bool drawUnselectedLeg = layoutEditor->isTurnoutDrawUnselectedLeg();

         QColor color = layoutEditor->drawingStroke.color(); //g2.getColor();

         // if this isn't a block line all these will be the same color
         QColor colorA = color;
         QColor colorB = color;
         QColor colorC = color;
         QColor colorD = color;

         if (isBlock) {
             LayoutBlock* lb = getLayoutBlock();
             colorA = (lb == nullptr) ? color : lb->getBlockColor();
             lb = getLayoutBlockB();
             colorB = (lb == nullptr) ? color : lb->getBlockColor();
             lb = getLayoutBlockC();
             colorC = (lb == nullptr) ? color : lb->getBlockColor();
             lb = getLayoutBlockD();
             colorD = (lb == nullptr) ? color : lb->getBlockColor();
         }

         QPointF oneForthPointAC = MathUtil::oneFourthPoint(pA, pC);
         QPointF oneThirdPointAC = MathUtil::oneThirdPoint(pA, pC);
         QPointF midPointAC = MathUtil::midPoint(pA, pC);
         QPointF twoThirdsPointAC = MathUtil::twoThirdsPoint(pA, pC);
         QPointF threeFourthsPointAC = MathUtil::threeFourthsPoint(pA, pC);

         QPointF oneForthPointBD = MathUtil::oneFourthPoint(pB, pD);
         QPointF oneThirdPointBD = MathUtil::oneThirdPoint(pB, pD);
         QPointF midPointBD = MathUtil::midPoint(pB, pD);
         QPointF twoThirdsPointBD = MathUtil::twoThirdsPoint(pB, pD);
         QPointF threeFourthsPointBD = MathUtil::threeFourthsPoint(pB, pD);

         QPointF midPointAD = MathUtil::midPoint(oneThirdPointAC, twoThirdsPointBD);
         QPointF midPointBC = MathUtil::midPoint(oneThirdPointBD, twoThirdsPointAC);


     //    invalidateItemType(drawMain);
     //    if(itemMain)
     //     itemGroup = itemMain;
     //    else

         if(itemGroup == nullptr)
         {
          itemGroup = new QGraphicsItemGroup();
          itemGroup->setZValue(Editor::HANDLES+1);
          g2->addItem(itemGroup);
         }

         if (isTurnoutInconsistent())
         {
             // If either turnout is inconsistent, draw an alternate slip image
             // draw A<= =>C
             if (drawMain == mainlineA) {
                 //g2.setColor(colorA);
              layoutEditor->drawingStroke.setColor(colorA);
                 //g2.draw(new Line2D.Double(pA, oneForthPointAC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pA.x(), pA.y(), oneForthPointAC.x(), oneForthPointAC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(threeFourthsPointAC, pC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(threeFourthsPointAC.x(), threeFourthsPointAC.y(), pC.x(), pC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             // draw B<= =>D
             if (drawMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(pB, oneForthPointBD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pB.x(), pB.y(), oneForthPointBD.x(), oneForthPointBD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.setColor(colorD);
              layoutEditor->drawingStroke.setColor(colorD);
                 //g2.draw(new Line2D.Double(threeFourthsPointBD, pD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(threeFourthsPointBD.x(), threeFourthsPointBD.y(), pD.x(), pD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             return;
         }

         int slipState = getSlipState();

         if (slipState == STATE_AD)
         {
             // draw A<===>D
             if (drawMain == mainlineA) {
                 //g2.setColor(colorA);
              layoutEditor->drawingStroke.setColor(colorA);
                 //g2.draw(new Line2D.Double(pA, oneThirdPointAC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pA.x(), pA.y(), oneThirdPointAC.x(), oneThirdPointAC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 //g2.draw(new Line2D.Double(oneThirdPointAC, midPointAD));
              lineItem = new QGraphicsLineItem(oneThirdPointAC.x(), oneThirdPointAC.y(), midPointAD.x(), midPointAD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.setColor(colorD);
              layoutEditor->drawingStroke.setColor(colorD);
                 //g2.draw(new Line2D.Double(midPointAD, twoThirdsPointBD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(midPointAD.x(), midPointAD.y(), twoThirdsPointBD.x(), twoThirdsPointBD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 //g2.draw(new Line2D.Double(twoThirdsPointBD, pD));
              lineItem = new QGraphicsLineItem(twoThirdsPointBD.x(), twoThirdsPointBD.y(), pD.x(), pD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }
         else if (slipState == STATE_AC)
         {
             // draw A<===>C
             if (drawMain == mainlineA) {
                 //g2.setColor(colorA);
              layoutEditor->drawingStroke.setColor(colorA);
                 //.draw(new Line2D.Double(pA, midPointAC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pA.x(), pA.y(), midPointAC.x(), midPointAC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(midPointAC, pC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(midPointAC.x(), midPointAC.y(), pC.x(), pC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }
         else if (!isBlock || drawUnselectedLeg)
         {
             // draw A<= =>C
             if (drawMain == mainlineA) {
                 //g2.setColor(colorA);
              layoutEditor->drawingStroke.setColor(colorA);
                 //g2.draw(new Line2D.Double(pA, oneForthPointAC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pA.x(), pA.y(), oneForthPointAC.x(), oneForthPointAC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(threeFourthsPointAC, pC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(threeFourthsPointAC.x(), threeFourthsPointAC.y(), pC.x(), pC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }

         if (slipState == STATE_BD)
         {
             // draw B<===>D
             if (drawMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(pB, midPointBD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pB.x(), pB.y(), midPointBD.x(), midPointBD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.setColor(colorD);
              layoutEditor->drawingStroke.setColor(colorD);
                 //g2.draw(new Line2D.Double(midPointBD, pD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(midPointBD.x(), midPointBD.y(), pD.x(), pD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }
         else if (!isBlock || drawUnselectedLeg)
         {
             // draw B<= =>D
             if (drawMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(pB, oneForthPointBD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pB.x(), pB.y(), oneForthPointBD.x(), oneForthPointBD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.setColor(colorD);
              layoutEditor->drawingStroke.setColor(colorD);
                 //g2.draw(new Line2D.Double(threeFourthsPointBD, pD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(threeFourthsPointBD.x(), threeFourthsPointBD.y(), pD.x(), pD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }

         if (slipState == STATE_BC) {
             if (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_SLIP) {
                 // draw B<===>C
                 if (drawMain == mainlineB) {
                     //g2.setColor(colorB);
                  layoutEditor->drawingStroke.setColor(colorB);
                     //g2.draw(new Line2D.Double(pB, oneThirdPointBD));
                  QGraphicsLineItem* lineItem = new QGraphicsLineItem(pB.x(), pB.y(), oneThirdPointBD.x(), oneThirdPointBD.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                     //g2.draw(new Line2D.Double(oneThirdPointBD, midPointBC));
                  lineItem = new QGraphicsLineItem(oneThirdPointBD.x(), oneThirdPointBD.y(), midPointBC.x(), midPointBC.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
                 if (drawMain == mainlineC) {
                     //g2.setColor(colorC);
                  layoutEditor->drawingStroke.setColor(colorC);
                     //g2.draw(new Line2D.Double(midPointBC, twoThirdsPointAC));
                  QGraphicsLineItem* lineItem = new QGraphicsLineItem(midPointBC.x(), midPointBC.y(), twoThirdsPointAC.x(), twoThirdsPointAC.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                     //g2.draw(new Line2D.Double(twoThirdsPointAC, pC));
                  lineItem = new QGraphicsLineItem(twoThirdsPointAC.x(), twoThirdsPointAC.y(), pC.x(), pC.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }   // DOUBLE_SLIP
         }
         else if (!isBlock || drawUnselectedLeg)
         {
             // draw B<= =>C
             if (drawMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(pB, oneForthPointBD));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pB.x(), pB.y(), oneForthPointBD.x(), oneForthPointBD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(threeFourthsPointAC, pC));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(threeFourthsPointAC.x(), threeFourthsPointAC.y(), pC.x(), pC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }
     //    if(drawMain)
     //    {
     //     itemMain = itemGroup;
     //     g2->addItem(itemMain);
     //    }
     //    else
     //    {
     //     itemSide = itemGroup;
     //     g2->addItem(itemSide);
     //    }
         g2->addItem(itemGroup);
    }   // draw1

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ void LayoutSlipView::draw2(EditScene* g2, bool drawMain, float railDisplacement) {
         QPointF pA = getCoordsA();
         QPointF pB = getCoordsB();
         QPointF pC = getCoordsC();
         QPointF pD = getCoordsD();
         QPointF pM = getCoordsCenter();

         QPointF vAC = MathUtil::normalize(MathUtil::subtract(pC, pA), railDisplacement);
         double dirAC_DEG = MathUtil::computeAngleDEG(pA, pC);
         QPointF vACo = MathUtil::orthogonal(vAC);
         QPointF pAL = MathUtil::subtract(pA, vACo);
         QPointF pAR = MathUtil::add(pA, vACo);
         QPointF pCL = MathUtil::subtract(pC, vACo);
         QPointF pCR = MathUtil::add(pC, vACo);

         QPointF vBD = MathUtil::normalize(MathUtil::subtract(pD, pB), railDisplacement);
         double dirBD_DEG = MathUtil::computeAngleDEG(pB, pD);
         QPointF vBDo = MathUtil::orthogonal(vBD);
         QPointF pBL = MathUtil::subtract(pB, vBDo);
         QPointF pBR = MathUtil::add(pB, vBDo);
         QPointF pDL = MathUtil::subtract(pD, vBDo);
         QPointF pDR = MathUtil::add(pD, vBDo);

         double deltaDEG = MathUtil::absDiffAngleDEG(dirAC_DEG, dirBD_DEG);
         double deltaRAD = qDegreesToRadians(deltaDEG);

         double hypotV = railDisplacement / qCos((M_PI - deltaRAD) / 2.0);
         double hypotK = railDisplacement / qCos(deltaRAD / 2.0);

         log->debug(tr("dir AC: %1, BD: %2, diff: %3").arg(dirAC_DEG).arg(dirBD_DEG).arg(deltaDEG));

         QPointF vDisK = MathUtil::normalize(MathUtil::subtract(vAC, vBD), hypotK);
         QPointF vDisV = MathUtil::normalize(MathUtil::orthogonal(vDisK), hypotV);
         QPointF pKL = MathUtil::subtract(pM, vDisK);
         QPointF pKR = MathUtil::add(pM, vDisK);
         QPointF pVL = MathUtil::add(pM, vDisV);
         QPointF pVR = MathUtil::subtract(pM, vDisV);

         // this is the vector (rail gaps) for the diamond parts
         double railGap = 2.0 / qSin(deltaRAD);
         QPointF vAC2 = MathUtil::normalize(vAC, railGap);
         QPointF vBD2 = MathUtil::normalize(vBD, railGap);
         // KR and VR toward A, KL and VL toward C
         QPointF pKRtA = MathUtil::subtract(pKR, vAC2);
         QPointF pVRtA = MathUtil::subtract(pVR, vAC2);
         QPointF pKLtC = MathUtil::add(pKL, vAC2);
         QPointF pVLtC = MathUtil::add(pVL, vAC2);

         // VR and KL toward B, KR and VL toward D
         QPointF pVRtB = MathUtil::subtract(pVR, vBD2);
         QPointF pKLtB = MathUtil::subtract(pKL, vBD2);
         QPointF pKRtD = MathUtil::add(pKR, vBD2);
         QPointF pVLtD = MathUtil::add(pVL, vBD2);

         // outer (closed) switch points
         QPointF pAPL = MathUtil::add(pAL, MathUtil::subtract(pVL, pAR));
         QPointF pBPR = MathUtil::add(pBR, MathUtil::subtract(pVL, pBL));
         QPointF pCPR = MathUtil::add(pCR, MathUtil::subtract(pVR, pCL));
         QPointF pDPL = MathUtil::add(pDL, MathUtil::subtract(pVR, pDR));

         // this is the vector (rail gaps) for the inner (open) switch points
         QPointF vACo2 = MathUtil::normalize(vACo, 2.0);
         QPointF vBDo2 = MathUtil::normalize(vBDo, 2.0);
         QPointF pASL = MathUtil::add(pAPL, vACo2);
         QPointF pBSR = MathUtil::subtract(pBPR, vBDo2);
         QPointF pCSR = MathUtil::subtract(pCPR, vACo2);
         QPointF pDSL = MathUtil::add(pDPL, vBDo2);

         QPointF pVLP = MathUtil::add(pVLtD, vAC2);
         QPointF pVRP = MathUtil::subtract(pVRtA, vBD2);

         QPointF pKLH = MathUtil::midPoint(pM, pKL);
         QPointF pKRH = MathUtil::midPoint(pM, pKR);

         bool mainlineA = isMainlineA();
         bool mainlineB = isMainlineB();
         bool mainlineC = isMainlineC();
         bool mainlineD = isMainlineD();

     //    invalidateItemType(drawMain);
     //    if(type)
     //     itemGroup = type;
     //    else
         if(itemGroup == nullptr)
         {
          itemGroup = new QGraphicsItemGroup();
          itemGroup->setZValue(Editor::HANDLES+1);
          g2->addItem(itemGroup);
         }

         if (drawMain == mainlineA) {
             //g2.draw(new Line2D.Double(pAR, pVL));
          QGraphicsLineItem* lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pVL.x(), pVL.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pVLtD, pKLtB));
          lineItem = new QGraphicsLineItem(pVLtD.x(), pVLtD.y(), pKLtB.x(), pKLtB.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
             QPainterPath path =  QPainterPath();
             path.moveTo(pAL.x(), pAL.y());
             path.lineTo(pAPL.x(), pAPL.y());
             path.quadTo(pKL.x(), pKL.y(), pDPL.x(), pDPL.y());
             //g2.draw(path);
             QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
             pathItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(pathItem);
         }

         if (drawMain == mainlineB) {
             //g2.draw(new Line2D.Double(pBL, pVL));
          QGraphicsLineItem* lineItem = new QGraphicsLineItem(pBL.x(), pBL.y(), pVL.x(), pVL.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pVLtC, pKRtA));
          lineItem = new QGraphicsLineItem(pVLtC.x(), pVLtC.y(), pKRtA.x(), pKRtA.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
             if (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_SLIP) {
                 QPainterPath path = QPainterPath();
                 path.moveTo(pBR.x(), pBR.y());
                 path.lineTo(pBPR.x(), pBPR.y());
                 path.quadTo(pKR.x(), pKR.y(), pCPR.x(), pCPR.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
             } else {
                 //g2.draw(new Line2D.Double(pBR, pKR));
              QGraphicsLineItem* lineItem = new QGraphicsLineItem(pBR.x(), pBR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }
         if (drawMain == mainlineC) {
             //g2.draw(new Line2D.Double(pCL, pVR));
          QGraphicsLineItem* lineItem = new QGraphicsLineItem(pCL.x(), pCL.y(), pVR.x(), pVR.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
          //g2.draw(new Line2D.Double(pVRtB, pKRtD));
          lineItem = new QGraphicsLineItem(pVRtB.x(), pVRtB.y(), pKRtD.x(), pKRtD.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);   if (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_SLIP) {
                 QPainterPath path = QPainterPath();
                 path.moveTo(pCR.x(), pCR.y());
                 path.lineTo(pCPR.x(), pCPR.y());
                 path.quadTo(pKR.x(), pKR.y(), pBPR.x(), pBPR.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
          } else {
                 //g2.draw(new Line2D.Double(pCR, pKR));
           lineItem = new QGraphicsLineItem(pCR.x(), pCR.y(), pKR.x(), pKR.y());
           lineItem->setPen(layoutEditor->drawingStroke);
           itemGroup->addToGroup(lineItem);
          }
         }

         if (drawMain == mainlineD) {
             //g2.draw(new Line2D.Double(pDR, pVR));
             QGraphicsLineItem* lineItem = new QGraphicsLineItem(pDR.x(), pDR.y(), pVR.x(), pVR.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             //g2.draw(new Line2D.Double(pVRtA, pKLtC));
             lineItem = new QGraphicsLineItem(pVRtA.x(), pVRtA.y(), pKLtC.x(), pKLtC.y());
             lineItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(lineItem);
             QPainterPath path = QPainterPath();
             path.moveTo(pDL.x(), pDL.y());
             path.lineTo(pDPL.x(), pDPL.y());
             path.quadTo(pKL.x(), pKL.y(), pAPL.x(), pAPL.y());
             //g2.draw(path);
             QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
             pathItem->setPen(layoutEditor->drawingStroke);
             itemGroup->addToGroup(pathItem);
         }
     #if 1
         int slipState = getSlipState();
         QGraphicsLineItem* lineItem;
         if (slipState == STATE_AD) {
             if (drawMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pASL, pKL));
              lineItem = new QGraphicsLineItem(pASL.x(), pASL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLP, pKLH));
              lineItem = new QGraphicsLineItem(pVLP.x(), pVLP.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineB) {
                 //g2.draw(new Line2D.Double(pBPR, pKR));
              lineItem = new QGraphicsLineItem(pBPR.x(), pBPR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLtC, pKRH));
              lineItem = new QGraphicsLineItem(pVLtC.x(), pVLtC.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.draw(new Line2D.Double(pCPR, pKR));
              lineItem = new QGraphicsLineItem(pCPR.x(), pCPR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRtB, pKRH));
              lineItem = new QGraphicsLineItem(pVRtB.x(), pVRtB.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.draw(new Line2D.Double(pDSL, pKL));
              lineItem = new QGraphicsLineItem(pDSL.x(), pDSL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRP, pKLH));
              lineItem = new QGraphicsLineItem(pVRP.x(), pVRP.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         } else if (slipState == STATE_AC) {
             if (drawMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pAPL, pKL));
              lineItem = new QGraphicsLineItem(pAPL.x(), pAPL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLtD, pKLH));
              lineItem = new QGraphicsLineItem(pVLtD.x(), pVLtD.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineB) {
                 //g2.draw(new Line2D.Double(pBSR, pKR));
              lineItem = new QGraphicsLineItem(pBSR.x(), pBSR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLP, pKRH));
              lineItem = new QGraphicsLineItem(pVLP.x(), pVLP.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.draw(new Line2D.Double(pCPR, pKR));
              lineItem = new QGraphicsLineItem(pCPR.x(), pCPR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRtB, pKRH));
              lineItem = new QGraphicsLineItem(pVRtB.x(), pVRtB.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.draw(new Line2D.Double(pDSL, pKL));
              lineItem = new QGraphicsLineItem(pDSL.x(), pDSL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRP, pKLH));
              lineItem = new QGraphicsLineItem(pVRP.x(), pVRP.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         } else if (slipState == STATE_BD) {
             if (drawMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pASL, pKL));
              lineItem = new QGraphicsLineItem(pASL.x(), pASL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLP, pKLH));
              lineItem = new QGraphicsLineItem(pVLP.x(), pVLP.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineB) {
                // g2.draw(new Line2D.Double(pBPR, pKR));
              lineItem = new QGraphicsLineItem(pBPR.x(), pBPR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLtC, pKRH));
              lineItem = new QGraphicsLineItem(pVLtC.x(), pVLtC.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.draw(new Line2D.Double(pCSR, pKR));
              lineItem = new QGraphicsLineItem(pCSR.x(), pCSR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRP, pKRH));
              lineItem = new QGraphicsLineItem(pVRP.x(), pVRP.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.draw(new Line2D.Double(pDPL, pKL));
              lineItem = new QGraphicsLineItem(pDPL.x(), pDPL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRtA, pKLH));
              lineItem = new QGraphicsLineItem(pVRtA.x(), pVRtA.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         } else if ((getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_SLIP)
                 && (slipState == STATE_BC)) {
             if (drawMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pAPL, pKL));
              lineItem = new QGraphicsLineItem(pAPL.x(), pAPL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLtD, pKLH));
              lineItem = new QGraphicsLineItem(pVLtD.x(), pVLtD.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineB) {
                 //g2.draw(new Line2D.Double(pBSR, pKR));
              lineItem = new QGraphicsLineItem(pBSR.x(), pBSR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVLP, pKRH));
              lineItem = new QGraphicsLineItem(pVLP.x(), pVLP.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineC) {
                 //g2.draw(new Line2D.Double(pCSR, pKR));
              lineItem = new QGraphicsLineItem(pCSR.x(), pCSR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRP, pKRH));
              lineItem = new QGraphicsLineItem(pVRP.x(), pVRP.y(), pKRH.x(), pKRH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (drawMain == mainlineD) {
                 //g2.draw(new Line2D.Double(pDPL, pKL));
              lineItem = new QGraphicsLineItem(pDPL.x(), pDPL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRtA, pKLH));
              lineItem = new QGraphicsLineItem(pVRtA.x(), pVRtA.y(), pKLH.x(), pKLH.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);}
         }   // DOUBLE_SLIP
     #endif
         if(drawMain)
         {
          itemMain = itemGroup;
          g2->addItem(itemMain);
         }
         else
         {
          itemSide = itemGroup;
          g2->addItem(itemSide);
         }
    }   // draw2

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ void LayoutSlipView::highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) {
      QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();

      invalidateItem(g2,rects);

      if (((specificType == HitPointType::NONE) || (specificType == HitPointType::SLIP_A))
                 && (getConnectA() == nullptr)) {
             //g2.fill(layoutEditor->trackControlCircleAt(getCoordsA()));
          QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsA());
          ellipseItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(ellipseItem);
         }

         if (((specificType == HitPointType::NONE) || (specificType == HitPointType::SLIP_B))
                 && (getConnectB() == nullptr)) {
             //g2.fill(layoutEditor->trackControlCircleAt(getCoordsB()));
          QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsB());
          ellipseItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(ellipseItem);
         }

         if (((specificType == HitPointType::NONE) || (specificType == HitPointType::SLIP_C))
                 && (getConnectC() == nullptr)) {
             //g2.fill(layoutEditor->trackControlCircleAt(getCoordsC()));
         }
         QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsC());
         ellipseItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(ellipseItem);

         if (((specificType == HitPointType::NONE) || (specificType == HitPointType::SLIP_D))
                 && (getConnectD() == nullptr)) {
             //g2.fill(layoutEditor->trackControlCircleAt(getCoordsD()));
          QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsD());
          ellipseItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(ellipseItem);
         }

         rects = itemGroup;
         g2->addItem(rects);
    }

    //@Override
    /*protected*/ void LayoutSlipView::drawTurnoutControls(EditScene* g2) {
      // drawHidden left/right turnout control circles
      QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
      QPointF leftCircleCenter = getCoordsLeft();

      invalidateItem(g2,circles);

      //g2.draw(layoutEditor->trackControlCircleAt(leftCircleCenter));
      QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(leftCircleCenter);
      ellipseItem->setPen(layoutEditor->drawingStroke);
      if (layoutEditor->isTurnoutFillControlCircles()) {
       QBrush brush = QBrush(layoutEditor->drawingStroke.color());
       ellipseItem->setBrush(brush);
      }
      itemGroup->addToGroup(ellipseItem);

      QPointF rightCircleCenter = getCoordsRight();
      //g2.draw(layoutEditor->trackControlCircleAt(rightCircleCenter));
      ellipseItem = trackControlCircleAt(rightCircleCenter);
      ellipseItem->setPen(layoutEditor->drawingStroke);
      if (layoutEditor->isTurnoutFillControlCircles()) {
       QBrush brush = QBrush(layoutEditor->drawingStroke.color());
       ellipseItem->setBrush(brush);
      }

      itemGroup->addToGroup(ellipseItem);

      circles = itemGroup;
      g2->addItem(circles);
    } // drawTurnoutControls
#if 0
    /*public*/ static class TurnoutState {

        /*private*/ int turnoutA = Turnout.CLOSED;
        /*private*/ int turnoutB = Turnout.CLOSED;
        /*private*/ JComboBox<String> turnoutABox;
        /*private*/ JComboBox<String> turnoutBBox;

        TurnoutState(int turnoutA, int turnoutB) {
            this.turnoutA = turnoutA;
            this.turnoutB = turnoutB;
        }

        /*public*/ int getTurnoutAState() {
            return turnoutA;
        }

        /*public*/ int getTurnoutBState() {
            return turnoutB;
        }

        /*public*/ void setTurnoutAState(int state) {
            turnoutA = state;
        }

        /*public*/ void setTurnoutBState(int state) {
            turnoutB = state;
        }

        /*public*/ JComboBox<String> getComboA() {
            if (turnoutABox == null) {
                String[] state = new String[]{InstanceManager.turnoutManagerInstance().getClosedText(),
                    InstanceManager.turnoutManagerInstance().getThrownText()};
                turnoutABox = new JComboBox<>(state);
                if (turnoutA == Turnout.THROWN) {
                    turnoutABox.setSelectedIndex(1);
                }
            }
            return turnoutABox;
        }

        /*public*/ JComboBox<String> getComboB() {
            if (turnoutBBox == null) {
                String[] state = new String[]{InstanceManager.turnoutManagerInstance().getClosedText(),
                    InstanceManager.turnoutManagerInstance().getThrownText()};
                turnoutBBox = new JComboBox<>(state);
                if (turnoutB == Turnout.THROWN) {
                    turnoutBBox.setSelectedIndex(1);
                }
            }
            return turnoutBBox;
        }

        /*public*/ int getTestTurnoutAState() {
            int result = Turnout.THROWN;
            if (turnoutABox != null) {
                if (turnoutABox.getSelectedIndex() == 0) {
                    result = Turnout.CLOSED;
                }
            }
            return result;
        }

        /*public*/ int getTestTurnoutBState() {
            int result = Turnout.THROWN;
            if (turnoutBBox != null) {
                if (turnoutBBox.getSelectedIndex() == 0) {
                    result = Turnout.CLOSED;
                }
            }
            return result;
        }

        /*public*/ void updateStatesFromCombo() {
            if ((turnoutABox != null) && (turnoutBBox != null)) {
                turnoutA = getTestTurnoutAState();
                turnoutB = getTestTurnoutBState();
            }
        }

        //@Override
        /*public*/ bool equals(Object object) {
            if (this == object) {
                return true;
            }
            if (object == null) {
                return false;
            }
            if (!(object instanceof TurnoutState)) {
                return false;
            }
            TurnoutState tso = (TurnoutState) object;

            return ((getTurnoutAState() == tso.getTurnoutAState())
                    && (getTurnoutBState() == tso.getTurnoutBState()));
        }

        /**
         * Hash on the header
         */
        //@Override
        /*public*/ int hashCode() {
            int result = 7;
            result = (37 * result) + getTurnoutAState();
            result = (37 * result) + getTurnoutBState();

            return result;
        }

    }   // class TurnoutState
#endif
    /*
    this is used by ConnectivityUtil to determine the turnout state necessary to get from prevLayoutBlock ==> currLayoutBlock ==> nextLayoutBlock
     */
    //@Override
    /*protected*/ int LayoutSlipView::getConnectivityStateForLayoutBlocks(
            /*@CheckForNull*/  LayoutBlock* thisLayoutBlock,
            /*@CheckForNull*/  LayoutBlock* prevLayoutBlock,
            /*@CheckForNull*/  LayoutBlock* nextLayoutBlock,
            bool suppress) {

        return slip->getConnectivityStateForLayoutBlocks(thisLayoutBlock,
                                                        prevLayoutBlock, nextLayoutBlock,
                                                        suppress);
    }

    /*
    * {@inheritDoc}
     */
    //@Override
    /*public*/ void LayoutSlipView::reCheckBlockBoundary() {
        slip->reCheckBlockBoundary();
    }

    /*
    * {@inheritDoc}
     */
    //@Override
    /*@Nonnull*/
    /*protected*/ QList<LayoutConnectivity*> LayoutSlipView::getLayoutConnectivity() {
        return slip->getLayoutConnectivity();
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ QList<HitPointType::TYPES> LayoutSlipView::checkForFreeConnections() {
        return slip->checkForFreeConnections();
    }

    // NOTE: LayoutSlip uses the checkForNonContiguousBlocks
    //      and collectContiguousTracksNamesInBlockNamed methods
    //      inherited from LayoutTurnout
    //
    /*private*/ /*final*/ /*static*/ Logger* LayoutSlipView::log = LoggerFactory::getLogger("LayoutSlipView");
