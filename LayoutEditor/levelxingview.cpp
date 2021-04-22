#include "levelxingview.h"
#include "loggerfactory.h"
#include "levelxingeditor.h"
#include "mathutil.h"
/**
 * MVC View component for the LevelXing class
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class LevelXingView extends LayoutTrackView {

/**
     * Constructor method.
     * @param xing the level crossing.
     * @param layoutEditor for access to tools
     */
    /*public*/ LevelXingView::LevelXingView(/*@Nonnull*/  LevelXing* xing, /*@Nonnull*/  LayoutEditor* layoutEditor)
       : LayoutTrackView(xing, layoutEditor)
    {
        //super(xing, layoutEditor);

        this->xing = xing;
        editor = new LevelXingEditor(layoutEditor);
    }

    /**
     * constructor method
     * @param xing the level crossing.
     * @param c display location
     * @param layoutEditor for access to tools
     */
    /*public*/ LevelXingView::LevelXingView(/*@Nonnull*/  LevelXing* xing, /*@Nonnull*/  QPointF c, /*@Nonnull*/  LayoutEditor* layoutEditor)
        : LayoutTrackView(xing, c, layoutEditor)
    {
        //super(xing, c, layoutEditor);

        this->xing = xing;
        editor = new LevelXingEditor(layoutEditor);
    }



    // temporary?
    /*@Nonnull*/
    /*public*/ LevelXing* LevelXingView::getLevelXing() { return xing; }

    // this should only be used for debugging
    //@Override
    /*public*/ QString LevelXingView::toString() {
        return "LevelXing " + getName();
    }

    /*
    * Accessor methods
     */
    /*@Nonnull*/
    /*public*/ QString LevelXingView::getBlockNameAC() {
        return xing->getBlockNameAC();
    }

    /*@Nonnull*/
    /*public*/ QString LevelXingView::getBlockNameBD() {
        return xing->getBlockNameBD();
    }

    /*public*/ SignalHead* LevelXingView::getSignalHead(int loc) {
        return xing->getSignalHead(loc);
    }

    /*public*/ SignalMast* LevelXingView::getSignalMast(int loc) {
        return xing->getSignalMast((LevelXing::Geometry)loc);
    }

    /*public*/ Sensor* LevelXingView::getSensor(int loc) {
        return xing->getSensor((LevelXing::Geometry)loc);
    }

    /*@Nonnull*/
    /*public*/ QString LevelXingView::getSignalAName() {
        return xing->getSignalAName();
    }

    /*public*/ void LevelXingView::setSignalAName(QString signalHead) {
        xing->setSignalAName(signalHead);
    }

    /*@Nonnull*/
    /*public*/ QString LevelXingView::getSignalBName() {
        return xing->getSignalBName();
    }

    /*public*/ void LevelXingView::setSignalBName(QString signalHead) {
        xing->setSignalBName(signalHead);
    }

    /*@Nonnull*/
    /*public*/ QString LevelXingView::getSignalCName() {
        return xing->getSignalCName();
    }

    /*public*/ void LevelXingView::setSignalCName(QString signalHead) {
        xing->setSignalCName(signalHead);
    }

    /*@Nonnull*/
    /*public*/ QString LevelXingView::getSignalDName() {
        return xing->getSignalDName();
    }

    /*public*/ void LevelXingView::setSignalDName(QString signalHead) {
        xing->setSignalDName(signalHead);
    }

    /*public*/ void LevelXingView::removeBeanReference(NamedBean* nb) {
        xing->removeBeanReference(nb);
    }

    /*public*/ QString LevelXingView::getSignalAMastName() {
        return xing->getSignalAMastName();
    }

    /*public*/ SignalMast* LevelXingView::getSignalAMast() {
        return xing->getSignalAMast();
    }

    /*public*/ void LevelXingView::setSignalAMast(QString signalMast) {
        xing->setSignalAMast(signalMast);
    }

    /*public*/ QString LevelXingView::getSignalBMastName() {
        return xing->getSignalBMastName();
    }

    /*public*/ SignalMast* LevelXingView::getSignalBMast() {
        return xing->getSignalBMast();
    }

    /*public*/ void LevelXingView::setSignalBMast(QString signalMast) {
        xing->setSignalBMast(signalMast);
    }

    /*public*/ QString LevelXingView::getSignalCMastName() {
        return xing->getSignalCMastName();
    }

    /*public*/ SignalMast* LevelXingView::getSignalCMast() {
        return xing->getSignalCMast();
    }

    /*public*/ void LevelXingView::setSignalCMast(QString signalMast) {
        xing->setSignalCMast(signalMast);
    }

    /*public*/ QString LevelXingView::getSignalDMastName() {
        return xing->getSignalDMastName();
    }

    /*public*/ SignalMast* LevelXingView::getSignalDMast() {
        return xing->getSignalDMast();
    }

    /*public*/ void LevelXingView::setSignalDMast(QString signalMast) {
        xing->setSignalDMast(signalMast);
    }

    /*public*/ QString LevelXingView::getSensorAName() {
        return xing->getSensorAName();
    }

    /*public*/ Sensor* LevelXingView::getSensorA() {
        return xing->getSensorA();
    }

    /*public*/ void LevelXingView::setSensorAName(QString sensorName) {
        xing->setSensorAName(sensorName);
    }

    /*public*/ QString LevelXingView::getSensorBName() {
        return xing->getSensorBName();
    }

    /*public*/ Sensor*LevelXingView:: getSensorB() {
        return xing->getSensorB();
    }

    /*public*/ void LevelXingView::setSensorBName(QString sensorName) {
        xing->setSensorBName(sensorName);
    }

    /*public*/ QString LevelXingView::getSensorCName() {
        return xing->getSensorCName();
    }

    /*public*/ Sensor* LevelXingView::getSensorC() {
        return xing->getSensorC();
    }

    /*public*/ void LevelXingView::setSensorCName(QString sensorName) {
        xing->setSensorCName(sensorName);
    }

    /*public*/ QString LevelXingView::getSensorDName() {
        return xing->getSensorDName();
    }

    /*public*/ Sensor* LevelXingView::getSensorD() {
        return xing->getSensorD();
    }

    /*public*/ void LevelXingView::setSensorDName(QString sensorName) {
        xing->setSensorDName(sensorName);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ LayoutTrack* LevelXingView::getConnection(HitPointType::TYPES connectionType) throw (JmriException) {
        return xing->getConnection(connectionType);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LevelXingView::setConnection(HitPointType::TYPES connectionType, LayoutTrack* o, HitPointType::TYPES type) throw (JmriException) {
        xing->setConnection(connectionType, o, type);
    }

    /*public*/ LayoutTrack* LevelXingView::getConnectA() {
        return xing->getConnectA();
    }

    /*public*/ LayoutTrack* LevelXingView::getConnectB() {
        return xing->getConnectB();
    }

    /*public*/ LayoutTrack* LevelXingView::getConnectC() {
        return xing->getConnectC();
    }

    /*public*/ LayoutTrack* LevelXingView::getConnectD() {
        return xing->getConnectD();
    }

    /*public*/ void LevelXingView::setConnectA(LayoutTrack* o, HitPointType::TYPES type) {
        xing->setConnectA(o, type);
    }

    /*public*/ void LevelXingView::setConnectB(LayoutTrack* o, HitPointType::TYPES type) {
        xing->setConnectB(o, type);
    }

    /*public*/ void LevelXingView::setConnectC(LayoutTrack* o, HitPointType::TYPES type) {
        xing->setConnectC(o, type);
    }

    /*public*/ void LevelXingView::setConnectD(LayoutTrack* o, HitPointType::TYPES type) {
        xing->setConnectD(o, type);
    }

    /*public*/ LayoutBlock* LevelXingView::getLayoutBlockAC() {
        return xing->getLayoutBlockAC();
    }

    /*public*/ LayoutBlock* LevelXingView::getLayoutBlockBD() {
        return xing->getLayoutBlockBD();
    }



    /*public*/ QPointF LevelXingView::getCoordsA() {
        return MathUtil::add(getCoordsCenter(), dispA);
    }

    /*public*/ QPointF LevelXingView::getCoordsB() {
        return MathUtil::add(getCoordsCenter(), dispB);
    }

    /*public*/ QPointF LevelXingView::getCoordsC() {
        return MathUtil::subtract(getCoordsCenter(), dispA);
    }

    /*public*/ QPointF LevelXingView::getCoordsD() {
        return MathUtil::subtract(getCoordsCenter(), dispB);
    }

    /**
     * Get the coordinates for a specified connection type.
     *
     * @param connectionType the connection type
     * @return the coordinates for the specified connection type
     */
    //@Override
    /*public*/ QPointF LevelXingView::getCoordsForConnectionType(HitPointType::TYPES connectionType) {
        QPointF result = getCoordsCenter();
        switch (connectionType) {
            case HitPointType::LEVEL_XING_CENTER:
                break;
            case HitPointType::LEVEL_XING_A:
                result = getCoordsA();
                break;
            case HitPointType::LEVEL_XING_B:
                result = getCoordsB();
                break;
            case HitPointType::LEVEL_XING_C:
                result = getCoordsC();
                break;
            case HitPointType::LEVEL_XING_D:
                result = getCoordsD();
                break;
            default:
                log->error(tr("%1.getCoordsForConnectionType(%2); Invalid connection type ").arg(
                        getName(), HitPointType::toString(connectionType))); //I18IN
        }
        return result;
    }

    /**
     * @return the bounds of this crossing
     */
    //@Override
    /*public*/ QRectF LevelXingView::getBounds() {
        QRectF result;

        QPointF pointA = getCoordsA();
        result = QRectF(pointA.x(), pointA.y(), 0, 0);
        MathUtil::add(result,getCoordsB());
        MathUtil::add(result,getCoordsC());
        MathUtil::add(result,getCoordsD());
        return result;
    }

    /**
     * Add Layout Blocks.
     */
//     @SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Null is accepted as a valid value")
//     /*public*/ void setLayoutBlockAC(LayoutBlock newLayoutBlock) {
//         LayoutBlock blockAC = getLayoutBlockAC();
//         LayoutBlock blockBD = getLayoutBlockBD();
//         if (blockAC != newLayoutBlock) {
//             // block 1 has changed, if old block exists, decrement use
//             if ((blockAC != null) && (blockAC != blockBD)) {
//                 blockAC.decrementUse();
//             }
//             blockAC = newLayoutBlock;
//             if (newLayoutBlock != null) {
//                 namedLayoutBlockAC = InstanceManager.getDefault(jmri.NamedBeanHandleManager.class).getNamedBeanHandle(newLayoutBlock.getUserName(), newLayoutBlock);
//             } else {
//                 namedLayoutBlockAC = null;
//             }
//
//             // decrement use if block was previously counted
//             if ((blockAC != null) && (blockAC == blockBD)) {
//                 blockAC.decrementUse();
//             }
//         }
//     }

//     @SuppressFBWarnings(value = "NP_NULL_ON_SOME_PATH_FROM_RETURN_VALUE", justification = "Null is accepted as a valid value")
//     /*public*/ void setLayoutBlockBD(LayoutBlock newLayoutBlock) {
//         LayoutBlock blockAC = getLayoutBlockAC();
//         LayoutBlock blockBD = getLayoutBlockBD();
//         if (blockBD != newLayoutBlock) {
//             // block 1 has changed, if old block exists, decrement use
//             if ((blockBD != null) && (blockBD != blockAC)) {
//                 blockBD.decrementUse();
//             }
//             blockBD = newLayoutBlock;
//             if (newLayoutBlock != null) {
//                 namedLayoutBlockBD = InstanceManager.getDefault(jmri.NamedBeanHandleManager.class).getNamedBeanHandle(newLayoutBlock.getUserName(), newLayoutBlock);
//             } else {
//                 namedLayoutBlockBD = null;
//             }
//             // decrement use if block was previously counted
//             if ((blockBD != null) && (blockBD == blockAC)) {
//                 blockBD.decrementUse();
//             }
//         }
//
//     }
//
//     /*public*/ void updateBlockInfo() {
//         LayoutBlock blockAC = getLayoutBlockAC();
//         LayoutBlock blockBD = getLayoutBlockBD();
//         LayoutBlock b1 = null;
//         LayoutBlock b2 = null;
//         if (blockAC != null) {
//             blockAC.updatePaths();
//         }
//         if (connectA != null) {
//             b1 = ((TrackSegment) connectA).getLayoutBlock();
//             if ((b1 != null) && (b1 != blockAC)) {
//                 b1.updatePaths();
//             }
//         }
//         if (connectC != null) {
//             b2 = ((TrackSegment) connectC).getLayoutBlock();
//             if ((b2 != null) && (b2 != blockAC) && (b2 != b1)) {
//                 b2.updatePaths();
//             }
//         }
//         if (blockBD != null) {
//             blockBD.updatePaths();
//         }
//         if (connectB != null) {
//             b1 = ((TrackSegment) connectB).getLayoutBlock();
//             if ((b1 != null) && (b1 != blockBD)) {
//                 b1.updatePaths();
//             }
//         }
//         if (connectD != null) {
//             b2 = ((TrackSegment) connectD).getLayoutBlock();
//             if ((b2 != null) && (b2 != blockBD) && (b2 != b1)) {
//                 b2.updatePaths();
//             }
//         }
//         reCheckBlockBoundary();
//     }
//
//     void removeSML(SignalMast signalMast) {
//         if (signalMast == null) {
//             return;
//         }
//         if (jmri.InstanceManager.getDefault(LayoutBlockManager.class).isAdvancedRoutingEnabled() && InstanceManager.getDefault(jmri.SignalMastLogicManager.class).isSignalMastUsed(signalMast)) {
//             SignallingGuiTools.removeSignalMastLogic(null, signalMast);
//         }
//     }

    /**
     * Test if mainline track or not.
     *
     * @return true if either connecting track segment is mainline; Defaults to
     *         not mainline if connecting track segments are missing
     */
    /*public*/ bool LevelXingView::isMainlineAC() {
        return xing->isMainlineAC();
    }

    /*public*/ bool LevelXingView::isMainlineBD() {
        return xing->isMainlineBD();
    }

    /*
    * Modify coordinates methods.
     */
    /*public*/ void LevelXingView::setCoordsA(QPointF p) {
        dispA = MathUtil::subtract(p, getCoordsCenter());
    }

    /*public*/ void LevelXingView::setCoordsB(QPointF p) {
        dispB = MathUtil::subtract(p, getCoordsCenter());
    }

    /*public*/ void LevelXingView::setCoordsC(QPointF p) {
        dispA = MathUtil::subtract(getCoordsCenter(), p);
    }

    /*public*/ void LevelXingView::setCoordsD(QPointF p) {
        dispB = MathUtil::subtract(getCoordsCenter(), p);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LevelXingView::scaleCoords(double xFactor, double yFactor) {
        QPointF factor = QPointF(xFactor, yFactor);
        LayoutTrackView::setCoordsCenter(MathUtil::granulize(MathUtil::multiply(getCoordsCenter(), factor), 1.0));
        dispA = MathUtil::granulize(MathUtil::multiply(dispA, factor), 1.0);
        dispB = MathUtil::granulize(MathUtil::multiply(dispB, factor), 1.0);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LevelXingView::translateCoords(double xFactor, double yFactor) {
        QPointF factor = QPointF(xFactor, yFactor);
        LayoutTrackView::setCoordsCenter(MathUtil::add(getCoordsCenter(), factor));
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LevelXingView::rotateCoords(double angleDEG) {
        // rotate coordinates
        double rotRAD = qDegreesToRadians(angleDEG);
        double sineRot = qSin(rotRAD);
        double cosineRot = qCos(rotRAD);

        // rotate displacements around origin {0, 0}
        QPointF center_temp = getCoordsCenter();
        LayoutTrackView::setCoordsCenter(MathUtil::zeroPoint2D);
        dispA = rotatePoint(dispA, sineRot, cosineRot);
        dispB = rotatePoint(dispB, sineRot, cosineRot);
        LayoutTrackView::setCoordsCenter(center_temp);

    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ HitPointType::TYPES LevelXingView::findHitPointType(QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
        HitPointType::TYPES result = HitPointType::NONE;  // assume point not on connection
        //note: optimization here: instead of creating rectangles for all the
        // points to check below, we create a rectangle for the test point
        // and test if the points below are in that rectangle instead.
        QGraphicsRectItem* r = trackControlCircleRectAt(hitPoint);
        QPointF p, minPoint = MathUtil::zeroPoint2D;

        double circleRadius = LayoutEditor::SIZE * layoutEditor->getTurnoutCircleSize();
        double distance, minDistance = INFINITY;

        //check the center point
        if (!requireUnconnected) {
            p = getCoordsCenter();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::LEVEL_XING_CENTER;
            }
        }

        //check the A connection point
        if (!requireUnconnected || (getConnectA() == nullptr)) {
            p = getCoordsA();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::LEVEL_XING_A;
            }
        }

        //check the B connection point
        if (!requireUnconnected || (getConnectB() == nullptr)) {
            p = getCoordsB();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::LEVEL_XING_B;
            }
        }

        //check the C connection point
        if (!requireUnconnected || (getConnectC() == nullptr)) {
            p = getCoordsC();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::LEVEL_XING_C;
            }
        }

        //check the D connection point
        if (!requireUnconnected || (getConnectD() == nullptr)) {
            p = getCoordsD();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::LEVEL_XING_D;
            }
        }
        if ((useRectangles && !r->contains(minPoint))
                || (!useRectangles && (minDistance > circleRadius))) {
            result = HitPointType::NONE;
        }
        return result;
    }   // findHitPointType

    // initialization instance variables (used when loading a LayoutEditor)
//     /*public*/ String connectAName = "";
//     /*public*/ String connectBName = "";
//     /*public*/ String connectCName = "";
//     /*public*/ String connectDName = "";
//
//     /*public*/ String tLayoutBlockNameAC = "";
//     /*public*/ String tLayoutBlockNameBD = "";

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool LevelXingView::canRemove() {
        return xing->canRemove();
    }

//     *
//      * Build a list of sensors, signal heads, and signal masts attached to a
//      * level crossing point.
//      *
//      * @param pointName Specify the point (A-D) or all (All) points.
//      * @return a list of bean reference names.
//      */
//     /*public*/ ArrayList<String> getBeanReferences(String pointName) {
//         ArrayList<String> references = new ArrayList<>();
//         if (pointName.equals("A") || pointName.equals("All")) {  // NOI18N
//             if (!getSignalAMastName().isEmpty()) {
//                 references.add(getSignalAMastName());
//             }
//             if (!getSensorAName().isEmpty()) {
//                 references.add(getSensorAName());
//             }
//             if (!getSignalAName().isEmpty()) {
//                 references.add(getSignalAName());
//             }
//         }
//         if (pointName.equals("B") || pointName.equals("All")) {  // NOI18N
//             if (!getSignalBMastName().isEmpty()) {
//                 references.add(getSignalBMastName());
//             }
//             if (!getSensorBName().isEmpty()) {
//                 references.add(getSensorBName());
//             }
//             if (!getSignalBName().isEmpty()) {
//                 references.add(getSignalBName());
//             }
//         }
//         if (pointName.equals("C") || pointName.equals("All")) {  // NOI18N
//             if (!getSignalCMastName().isEmpty()) {
//                 references.add(getSignalCMastName());
//             }
//             if (!getSensorCName().isEmpty()) {
//                 references.add(getSensorCName());
//             }
//             if (!getSignalCName().isEmpty()) {
//                 references.add(getSignalCName());
//             }
//         }
//         if (pointName.equals("D") || pointName.equals("All")) {  // NOI18N
//             if (!getSignalDMastName().isEmpty()) {
//                 references.add(getSignalDMastName());
//             }
//             if (!getSensorDName().isEmpty()) {
//                 references.add(getSensorDName());
//             }
//             if (!getSignalDName().isEmpty()) {
//                 references.add(getSignalDName());
//             }
//         }
//         return references;
//     }


    /**
     * {@inheritDoc}
     */
    //@Override
    /*@Nonnull*/
    /*protected*/ QMenu* LevelXingView::showPopup(/*@CheckForNull*/ QGraphicsSceneMouseEvent* mouseEvent) {
        if (popup != nullptr) {
            popup->clear();
        } else {
            popup = new QMenu();
        }
#if 0
        if (layoutEditor->isEditable()) {
            JMenuItem jmi = popup.add(Bundle.getMessage("MakeLabel", Bundle.getMessage("LevelCrossing")) + getName());
            jmi.setEnabled(false);

            bool blockACAssigned = false;
            bool blockBDAssigned = false;
            if (getLayoutBlockAC() == null) {
                jmi = popup.add(Bundle.getMessage("NoBlockX", "AC"));
            } else {
                jmi = popup.add(Bundle.getMessage("MakeLabel", Bundle.getMessage("Block_ID", "AC")) + getLayoutBlockAC().getDisplayName());
                blockACAssigned = true;
            }
            jmi.setEnabled(false);

            if (getLayoutBlockBD() == null) {
                jmi = popup.add(Bundle.getMessage("NoBlockX", "BD"));
            } else {
                jmi = popup.add(Bundle.getMessage("MakeLabel", Bundle.getMessage("Block_ID", "BD")) + getLayoutBlockBD().getDisplayName());
                blockBDAssigned = true;
            }
            jmi.setEnabled(false);

            // if there are any track connections
            if ((getConnectA() != null) || (getConnectB() != null)
                    || (getConnectC() != null) || (getConnectD() != null)) {
                JMenu connectionsMenu = new JMenu(Bundle.getMessage("Connections")); // there is no pane opening (which is what ... implies)
                if (getConnectA() != null) {
                    connectionsMenu.add(new AbstractAction(Bundle.getMessage("MakeLabel", "A") + getConnectA().getName()) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            LayoutEditorFindItems lf = layoutEditor->getFinder();
                            LayoutTrack lt = lf.findObjectByName(getConnectA().getName());
                            // this shouldn't ever be null... however...
                            if (lt != null) {
                                LayoutTrackView ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv.getBounds());
                                ltv.showPopup();
                            }
                        }
                    });
                }
                if (getConnectB() != null) {
                    connectionsMenu.add(new AbstractAction(Bundle.getMessage("MakeLabel", "B") + getConnectB().getName()) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            LayoutEditorFindItems lf = layoutEditor->getFinder();
                            LayoutTrack lt = lf.findObjectByName(getConnectB().getName());
                            // this shouldn't ever be null... however...
                            if (lt != null) {
                                LayoutTrackView ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv.getBounds());
                                ltv.showPopup();
                            }
                        }
                    });
                }
                if (getConnectC() != null) {
                    connectionsMenu.add(new AbstractAction(Bundle.getMessage("MakeLabel", "C") + getConnectC().getName()) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            LayoutEditorFindItems lf = layoutEditor->getFinder();
                            LayoutTrack lt = lf.findObjectByName(getConnectC().getName());
                            // this shouldn't ever be null... however...
                            if (lt != null) {
                                LayoutTrackView ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv.getBounds());
                                ltv.showPopup();
                            }
                        }
                    });
                }
                if (getConnectD() != null) {
                    connectionsMenu.add(new AbstractAction(Bundle.getMessage("MakeLabel", "D") + getConnectD().getName()) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            LayoutEditorFindItems lf = layoutEditor->getFinder();
                            LayoutTrack lt = lf.findObjectByName(getConnectD().getName());
                            // this shouldn't ever be null... however...
                            if (lt != null) {
                                LayoutTrackView ltv = layoutEditor->getLayoutTrackView(lt);
                                layoutEditor->setSelectionRect(ltv.getBounds());
                                ltv.showPopup();
                            }
                        }
                    });
                }
                popup.add(connectionsMenu);
            }

            popup.add(new JSeparator(JSeparator.HORIZONTAL));

            JCheckBoxMenuItem hiddenCheckBoxMenuItem = new JCheckBoxMenuItem(Bundle.getMessage("Hidden"));
            hiddenCheckBoxMenuItem.setSelected(isHidden());
            popup.add(hiddenCheckBoxMenuItem);
            hiddenCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e3) -> setHidden(hiddenCheckBoxMenuItem.isSelected()));

            popup.add(new AbstractAction(Bundle.getMessage("ButtonEdit")) {
                //@Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    editor.editLayoutTrack(LevelXingView.this);
                }
            });
            popup.add(new AbstractAction(Bundle.getMessage("ButtonDelete")) {
                //@Override
                /*public*/ void actionPerformed(ActionEvent e) {
                    if (canRemove() && layoutEditor->removeLevelXing(xing)) {
                        // Returned true if user did not cancel
                        xing->remove();
                        dispose();
                    }
                }
            });
            if (blockACAssigned && blockBDAssigned) {
                AbstractAction ssaa = new AbstractAction(Bundle.getMessage("SetSignals")) {
                    //@Override
                    /*public*/ void actionPerformed(ActionEvent e) {
                        // bring up signals at level crossing tool dialog
                        LayoutEditorToolBarPanel letbp = getLayoutEditorToolBarPanel();
                        layoutEditor->getLETools().
                                setSignalsAtLevelXingFromMenu(xing,
                                        letbp.signalIconEditor,
                                        letbp.signalFrame);
                    }
                };
                JMenu jm = new JMenu(Bundle.getMessage("SignalHeads"));
                if (layoutEditor->getLETools().
                        addLevelXingSignalHeadInfoToMenu(xing, jm)) {
                    jm.add(ssaa);
                    popup.add(jm);
                } else {
                    popup.add(ssaa);
                }
            }

            /*final*/  String[] boundaryBetween = xing->getBlockBoundaries();
            bool blockBoundaries = false;
            if (jmri.InstanceManager.getDefault(LayoutBlockManager.class).isAdvancedRoutingEnabled()) {
                if (blockACAssigned && !blockBDAssigned) {
                    popup.add(new AbstractAction(Bundle.getMessage("ViewBlockRouting")) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            AbstractAction routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockAC());
                            routeTableAction.actionPerformed(e);
                        }
                    });
                } else if (!blockACAssigned && blockBDAssigned) {
                    popup.add(new AbstractAction(Bundle.getMessage("ViewBlockRouting")) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            AbstractAction routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlockBD());
                            routeTableAction.actionPerformed(e);
                        }
                    });
                } else if (blockACAssigned && blockBDAssigned) {
                    JMenu viewRouting = new JMenu(Bundle.getMessage("ViewBlockRouting"));
                    viewRouting.add(new AbstractAction(getLayoutBlockAC().getDisplayName()) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            AbstractAction routeTableAction = new LayoutBlockRouteTableAction(getLayoutBlockAC().getDisplayName(), getLayoutBlockAC());
                            routeTableAction.actionPerformed(e);
                        }
                    });

                    viewRouting.add(new AbstractAction(getLayoutBlockBD().getDisplayName()) {
                        //@Override
                        /*public*/ void actionPerformed(ActionEvent e) {
                            AbstractAction routeTableAction = new LayoutBlockRouteTableAction(getLayoutBlockBD().getDisplayName(), getLayoutBlockBD());
                            routeTableAction.actionPerformed(e);
                        }
                    });

                    popup.add(viewRouting);
                }
            }

            for (int i = 0; i < 4; i++) {
                if (boundaryBetween[i] != null) {
                    blockBoundaries = true;
                }
            }
            if (blockBoundaries) {
                popup.add(new AbstractAction(Bundle.getMessage("SetSignalMasts")) {
                    //@Override
                    /*public*/ void actionPerformed(ActionEvent e) {
                        LayoutEditorToolBarPanel letbp = getLayoutEditorToolBarPanel();
                        layoutEditor->getLETools().
                                setSignalMastsAtLevelXingFromMenu(
                                        xing, boundaryBetween,
                                        letbp.signalFrame);
                    }
                });
                popup.add(new AbstractAction(Bundle.getMessage("SetSensors")) {
                    //@Override
                    /*public*/ void actionPerformed(ActionEvent e) {
                        LayoutEditorToolBarPanel letbp = getLayoutEditorToolBarPanel();
                        layoutEditor->getLETools().setSensorsAtLevelXingFromMenu(
                                xing, boundaryBetween,
                                letbp.sensorIconEditor,
                                letbp.sensorFrame);
                    }
                });
            }

            layoutEditor->setShowAlignmentMenu(popup);
            popup.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
        } else if (!viewAdditionalMenu.isEmpty()) {
            setAdditionalViewPopUpMenu(popup);
            popup.show(mouseEvent.getComponent(), mouseEvent.getX(), mouseEvent.getY());
        }
#endif
        return popup;
    }   // showPopup

//     /*public*/ String[] getBlockBoundaries() {
//         /*final*/  String[] boundaryBetween = new String[4];
//
//         String blockNameAC = getBlockNameAC();
//         String blockNameBD = getBlockNameBD();
//
//         LayoutBlock blockAC = getLayoutBlockAC();
//         LayoutBlock blockBD = getLayoutBlockAC();
//
//         if (!blockNameAC.isEmpty() && (blockAC != null)) {
//             if ((connectA instanceof TrackSegment) && (((TrackSegment) connectA).getLayoutBlock() != blockAC)) {
//                 try {
//                     boundaryBetween[0] = (((TrackSegment) connectA).getLayoutBlock().getDisplayName() + " - " + blockAC.getDisplayName());
//                 } catch (java.lang.NullPointerException e) {
//                     //Can be considered normal if tracksegement hasn't yet been allocated a block
//                     log.debug("TrackSegement at connection A doesn't contain a layout block");
//                 }
//             }
//             if ((connectC instanceof TrackSegment) && (((TrackSegment) connectC).getLayoutBlock() != blockAC)) {
//                 try {
//                     boundaryBetween[2] = (((TrackSegment) connectC).getLayoutBlock().getDisplayName() + " - " + blockAC.getDisplayName());
//                 } catch (java.lang.NullPointerException e) {
//                     //Can be considered normal if tracksegement hasn't yet been allocated a block
//                     log.debug("TrackSegement at connection C doesn't contain a layout block");
//                 }
//             }
//         }
//         if (!blockNameBD.isEmpty() && (blockBD != null)) {
//             if ((connectB instanceof TrackSegment) && (((TrackSegment) connectB).getLayoutBlock() != blockBD)) {
//                 try {
//                     boundaryBetween[1] = (((TrackSegment) connectB).getLayoutBlock().getDisplayName() + " - " + blockBD.getDisplayName());
//                 } catch (java.lang.NullPointerException e) {
//                     //Can be considered normal if tracksegement hasn't yet been allocated a block
//                     log.debug("TrackSegement at connection B doesn't contain a layout block");
//                 }
//             }
//             if ((connectD instanceof TrackSegment) && (((TrackSegment) connectD).getLayoutBlock() != blockBD)) {
//                 try {
//                     boundaryBetween[3] = (((TrackSegment) connectD).getLayoutBlock().getDisplayName() + " - " + blockBD.getDisplayName());
//                 } catch (java.lang.NullPointerException e) {
//                     //Can be considered normal if tracksegement hasn't yet been allocated a block
//                     log.debug("TrackSegement at connection D doesn't contain a layout block");
//                 }
//             }
//         }
//         return boundaryBetween;
//     }

    /**
     * Clean up when this object is no longer needed. Should not be called while
     * the object is still displayed; see remove().
     */
    /*public*/ void LevelXingView::dispose() {
        if (popup != nullptr) {
            popup->clear();
        }
        popup = nullptr;
    }

    /**
     * Remove this object from display and persistance.
     */
//     /*public*/ void remove() {
//         // remove from persistance by flagging inactive
//         active = false;
//     }
//
//     bool active = true;
//
//     *
//      * "active" means that the object is still displayed, and should be stored.
//      */
//     /*public*/ bool isActive() {
//         return active;
//     }

//     ArrayList<SignalMast> sml = new ArrayList<>();
//
//     /*public*/ void addSignalMastLogic(SignalMast sm) {
//         if (sml.contains(sm)) {
//             return;
//         }
//         if (sml.isEmpty()) {
//             sml.add(sm);
//             return;
//         }
//         SignalMastLogic sl = InstanceManager.getDefault(jmri.SignalMastLogicManager.class).getSignalMastLogic(sm);
//         for (SignalMast signalMast : sml) {
//             SignalMastLogic s = InstanceManager.getDefault(SignalMastLogicManager.class).getSignalMastLogic(signalMast);
//             if (s != null) {
//                 s.setConflictingLogic(sm, xing);
//             }
//             sl.setConflictingLogic(signalMast, xing);
//         }
//         sml.add(sm);
//     }
//
//     /*public*/ void removeSignalMastLogic(SignalMast sm) {
//         if (!sml.contains(sm)) {
//             return;
//         }
//         sml.remove(sm);
//         if (sml.isEmpty()) {
//             return;
//         }
//         for (int i = 0; i < sml.size(); i++) {
//             SignalMastLogic s = InstanceManager.getDefault(jmri.SignalMastLogicManager.class).getSignalMastLogic(sm);
//             if (s != null) {
//                 s.removeConflictingLogic(sm, xing);
//             }
//         }
//     }

    /*public*/ void LevelXingView::addEditPopUpMenu(QAction* menu) {
        if (!editAdditionalMenu.contains(menu)) {
            editAdditionalMenu.append(menu);
        }
    }

    /*public*/ void LevelXingView::addViewPopUpMenu(QAction* menu) {
        if (!viewAdditionalMenu.contains(menu)) {
            viewAdditionalMenu.append(menu);
        }
    }

    /*public*/ void LevelXingView::setAdditionalEditPopUpMenu(QMenu* popup) {
        if (editAdditionalMenu.isEmpty()) {
            return;
        }
        popup->addSeparator();
        for (QAction* mi : editAdditionalMenu) {
            popup->addAction(mi);
        }
    }

    /*public*/ void LevelXingView::setAdditionalViewPopUpMenu(QMenu* popup) {
        if (viewAdditionalMenu.isEmpty()) {
            return;
        }
        popup->addSeparator();
        for (QAction* mi : viewAdditionalMenu) {
            popup->addAction(mi);
        }
    }

    /**
     * Draw track decorations.
     *
     * This type of track has none, so this method is empty.
     */
    //@Override
    /*protected*/ void drawDecorations(EditScene* g2) {}

    /**
     * Draw this level crossing.
     *
     * @param g2 the graphics port to draw to
     */
    //@Override
    /*protected*/ void LevelXingView::draw1(EditScene* g2, bool isMain, bool isBlock) {
  invalidateItem(g2,itemGroup);
  if(itemGroup == nullptr)
  {
   itemGroup = new QGraphicsItemGroup();
   itemGroup->setZValue(Editor::HANDLES+1);
   g2->addItem(itemGroup);
  }

  if (isMain == isMainlineAC()) {
   if (isBlock) {
       layoutEditor->drawingStroke.setColor(setColorForTrackBlock(g2, getLayoutBlockAC()));
   }
   //g2.draw(new Line2D.Double(getCoordsA(), getCoordsC()));
   QGraphicsLineItem* lineItem = new QGraphicsLineItem(getCoordsA().x(), getCoordsA().y(), getCoordsC().x(), getCoordsC().y());
   lineItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(lineItem);
  }
  if (isMain == isMainlineBD())
  {
   if (isBlock) {
       layoutEditor->drawingStroke.setColor(setColorForTrackBlock(g2, getLayoutBlockBD()));
   }
   //g2.draw(new Line2D.Double(getCoordsB(), getCoordsD()));
   QGraphicsLineItem* lineItem = new QGraphicsLineItem(getCoordsB().x(), getCoordsB().y(), getCoordsD().x(), getCoordsD().y());
   lineItem->setPen(layoutEditor->drawingStroke);
   itemGroup->addToGroup(lineItem);
  }
}

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ void LevelXingView::draw2(EditScene* g2, bool isMain, float railDisplacement) {
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

     double hypotK = railDisplacement / qCos((M_PI - deltaRAD) / 2.0);
     double hypotV = railDisplacement / qCos(deltaRAD / 2.0);

     log->debug(tr("dir AC: %1, BD: %2, diff: %3").arg(dirAC_DEG).arg(dirBD_DEG).arg(deltaDEG));

     QPointF vDisK = MathUtil::normalize(MathUtil::add(vAC, vBD), hypotK);
     QPointF vDisV = MathUtil::normalize(MathUtil::orthogonal(vDisK), hypotV);
     QPointF pKL = MathUtil::subtract(pM, vDisK);
     QPointF pKR = MathUtil::add(pM, vDisK);
     QPointF pVL = MathUtil::subtract(pM, vDisV);
     QPointF pVR = MathUtil::add(pM, vDisV);

     invalidateItem(g2,itemGroup);
     if(itemGroup == nullptr)
     {
      itemGroup = new QGraphicsItemGroup();
      itemGroup->setZValue(Editor::HANDLES+1);
      g2->addItem(itemGroup);
     }

     if (isMain == isMainlineAC()) {
         // this is the *2.0 vector (rail gap) for the AC diamond parts
         QPointF vAC2 = MathUtil::normalize(vAC, 2.0);
         // KL toward C, VR toward A, VL toward C and KR toward A
         QPointF pKLtC = MathUtil::add(pKL, vAC2);
         QPointF pVRtA = MathUtil::subtract(pVR, vAC2);
         QPointF pVLtC = MathUtil::add(pVL, vAC2);
         QPointF pKRtA = MathUtil::subtract(pKR, vAC2);

         // draw right AC rail: AR====KL == VR====CR
         //g2.draw(new Line2D.Double(pAR, pKL));
         QGraphicsLineItem* lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pKL.x(), pKL.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
         //g2.draw(new Line2D.Double(pKLtC, pVRtA));
         lineItem = new QGraphicsLineItem(pKLtC.x(), pKLtC.y(), pVRtA.x(), pVRtA.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
         //g2.draw(new Line2D.Double(pVR, pCR));
         lineItem = new QGraphicsLineItem(pVR.x(), pVR.y(), pCR.x(), pCR.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);

         // draw left AC rail: AL====VL == KR====CL
         //g2.draw(new Line2D.Double(pAL, pVL));
         lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pVL.x(), pVL.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
         //g2.draw(new Line2D.Double(pVLtC, pKRtA));
         lineItem = new QGraphicsLineItem(pVLtC.x(), pVLtC.y(), pKRtA.x(), pKRtA.y());
         //g2.draw(new Line2D.Double(pKR, pCL));
     lineItem = new QGraphicsLineItem(pKR.x(), pKR.y(), pCL.x(), pCL.y());
     }
     if (isMain == isMainlineBD())
     {
      // this is the *2.0 vector (rail gap) for the BD diamond parts
      QPointF vBD2 = MathUtil::normalize(vBD, 2.0);
      // VR toward D, KR toward B, KL toward D and VL toward B
      QPointF pVRtD = MathUtil::add(pVR, vBD2);
      QPointF pKRtB = MathUtil::subtract(pKR, vBD2);
      QPointF pKLtD = MathUtil::add(pKL, vBD2);
      QPointF pVLtB = MathUtil::subtract(pVL, vBD2);

      // draw right BD rail: BR====VR == KR====DR
      //g2.draw(new Line2D.Double(pBR, pVR));
      QGraphicsLineItem* lineItem = new QGraphicsLineItem(pBR.x(), pBR.y(), pVR.x(), pVR.y());
      lineItem->setPen(layoutEditor->drawingStroke);
      itemGroup->addToGroup(lineItem);
      //g2.draw(new Line2D.Double(pVRtD, pKRtB));
      lineItem = new QGraphicsLineItem(pVRtD.x(), pVRtD.y(), pKRtB.x(), pKRtB.y());
      //g2.draw(new Line2D.Double(pKR, pDR));
      lineItem = new QGraphicsLineItem(pKR.x(), pKR.y(), pDR.x(), pDR.y());

      // draw left BD rail: BL====KL == VL====DL
      //g2.draw(new Line2D.Double(pBL, pKL));
      lineItem = new QGraphicsLineItem(pBL.x(), pBL.y(), pKL.x(), pKL.y());
      //g2.draw(new Line2D.Double(pKLtD, pVLtB));
      lineItem = new QGraphicsLineItem(pKLtD.x(), pKLtD.y(), pVLtB.x(), pVLtB.y());
      //g2.draw(new Line2D.Double(pVL, pDL));
      lineItem = new QGraphicsLineItem(pVL.x(), pVL.y(), pDL.x(), pDL.y());
     }
 //    if(isMain)
 //    {
 //     itemMain = itemGroup;
 //     g2->addItem(itemMain);
 //    }
 //    else
 //    {
 //     itemSide = itemGroup;
 //     g2->addItem(itemSide);
 //    }
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*protected*/ void LevelXingView::highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) {
  QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
   QPen stroke = QPen(layoutEditor->defaultTrackColor, 1);

     if (((specificType == HitPointType::NONE) || (specificType ==HitPointType:: LEVEL_XING_A))
             && (getConnectA() == nullptr)) {
         //g2.fill(layoutEditor.trackControlCircleAt(getCoordsA()));
      QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsA());
      ellipseItem->setPen(stroke);
      itemGroup->addToGroup(ellipseItem);
     }

     if (((specificType == HitPointType::NONE) || (specificType == HitPointType::LEVEL_XING_B))
             && (getConnectB() == nullptr)) {
         //g2.fill(layoutEditor.trackControlCircleAt(getCoordsB()));
      QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsB());
      ellipseItem->setPen(stroke);
      itemGroup->addToGroup(ellipseItem);
     }

     if (((specificType == HitPointType::NONE) || (specificType == HitPointType::LEVEL_XING_C))
             && (getConnectC() == nullptr)) {
         //g2.fill(layoutEditor.trackControlCircleAt(getCoordsC()));
      QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsC());
      ellipseItem->setPen(stroke);
      itemGroup->addToGroup(ellipseItem);
     }

     if (((specificType == HitPointType::NONE) || (specificType == HitPointType::LEVEL_XING_D))
             && (getConnectD() == nullptr)) {
         //g2.fill(layoutEditor.trackControlCircleAt(getCoordsD()));
      QGraphicsEllipseItem* ellipseItem = trackControlCircleAt(getCoordsD());
      ellipseItem->setPen(stroke);
      itemGroup->addToGroup(ellipseItem);
     }

     ((QGraphicsItemGroup*)item)->addToGroup(itemGroup);
    }

    //@Override
    /*protected*/ void LevelXingView::drawEditControls(EditScene* g2) {
 QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
 if(rects!=nullptr && rects->scene()!=nullptr)
 {
  g2->removeItem(rects);
  rects = nullptr;
 }
    //g2.setColor(defaultTrackColor);
 QPen stroke = layoutEditor->drawingStroke;

    //TODO:uncomment this line g2.draw(layoutEditor->trackEditControlCircleAt(getCoordsCenter()));

    if (getConnectA() == nullptr) {
        //g2.setColor(Color.magenta);
     stroke.setColor(Qt::magenta);
    } else {
        //g2.setColor(Color.blue);
     stroke.setColor(Qt::blue);
    }
    //g2.draw(layoutEditor->trackEditControlRectAt(getCoordsA()));
    QGraphicsRectItem* rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsA()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    if (getConnectB() == nullptr) {
        //g2.setColor(Color.red);
    stroke.setColor(Qt::red);
    } else {
        //g2.setColor(Color.green);
     stroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor->trackEditControlRectAt(getCoordsB()));
    rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsB()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    if (getConnectC() == nullptr) {
        //g2.setColor(Color.red);
     stroke.setColor(Qt::red);
    } else {
        //g2.setColor(Color.green);
     stroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor->trackEditControlRectAt(getCoordsC()));
    rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsC()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    if (getConnectD() == nullptr) {
        //g2.setColor(Color.red);
     stroke.setColor(Qt::red);
    } else {
        //g2.setColor(Color.green);
     stroke.setColor(Qt::green);
    }
    //g2.draw(layoutEditor->trackEditControlRectAt(getCoordsD()));
    rectItem = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(getCoordsB()));
    rectItem->setPen(stroke);
    itemGroup->addToGroup(rectItem);

    rects = itemGroup;
    g2->addItem(rects);
}

    //@Override
    /*protected*/ void LevelXingView::drawTurnoutControls(EditScene* g2) {
        // LevelXings don't have turnout controls...
        // nothing to see here... move along...
    }

    /*
    * {@inheritDoc}
     */
    //@Override
    /*public*/ void LevelXingView::reCheckBlockBoundary() {
        // nothing to see here... move along...
    }

    /*
    * {@inheritDoc} temporary
     */
    //@Override
    /*protected*/ QList<LayoutConnectivity*> LevelXingView::getLayoutConnectivity() {
        // nothing to see here... move along...
        return QList<LayoutConnectivity*>();
    }

    /**
     * {@inheritDoc}
     */
     //@Override
     /*public*/ QList<HitPointType::TYPES> LevelXingView::checkForFreeConnections() {
        throw new IllegalArgumentException("should have called Object instead of view temporary");
//         List<HitPointType> result = new ArrayList<>();
//
//         //check the A connection point
//         if (getConnectA() == null) {
//             result.add(HitPointType::LEVEL_XING_A);
//         }
//
//         //check the B connection point
//         if (getConnectB() == null) {
//             result.add(HitPointType::LEVEL_XING_B);
//         }
//
//         //check the C connection point
//         if (getConnectC() == null) {
//             result.add(HitPointType::LEVEL_XING_C);
//         }
//
//         //check the D connection point
//         if (getConnectD() == null) {
//             result.add(HitPointType::LEVEL_XING_D);
//         }
//         return result;
     }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ bool LevelXingView::checkForUnAssignedBlocks() {
//         return ((getLayoutBlockAC() != null) && (getLayoutBlockBD() != null));
        throw new IllegalArgumentException("should have called Object instead of View temporary");
   }

    /**
     * {@inheritDoc}
     */
    //@Override
    /*public*/ void LevelXingView::checkForNonContiguousBlocks(/*@Nonnull*/  QMap<QString, QList<QSet<QString> *> *> blockNamesToTrackNameSetsMap) {
        throw new IllegalArgumentException("should have called Object instead of View temporary");

        /*
        * For each (non-null) blocks of this track do:
        * #1) If it's got an entry in the blockNamesToTrackNameSetMap then
        * #2) If this track is already in the TrackNameSet for this block
        *     then return (done!)
        * #3) else add a new set (with this block/track) to
        *     blockNamesToTrackNameSetMap and check all the connections in this
        *     block (by calling the 2nd method below)
        * <p>
        *     Basically, we're maintaining contiguous track sets for each block found
        *     (in blockNamesToTrackNameSetMap)
         */

        // We're only using a map here because it's convient to
        // use it to pair up blocks and connections
//         Map<LayoutTrack, String> blocksAndTracksMap = new HashMap<>();
//         if ((getLayoutBlockAC() != null) && (connectA != null)) {
//             blocksAndTracksMap.put(connectA, getLayoutBlockAC().getDisplayName());
//         }
//         if ((getLayoutBlockAC() != null) && (connectC != null)) {
//             blocksAndTracksMap.put(connectC, getLayoutBlockAC().getDisplayName());
//         }
//         if ((getLayoutBlockBD() != null) && (connectB != null)) {
//             blocksAndTracksMap.put(connectB, getLayoutBlockBD().getDisplayName());
//         }
//         if ((getLayoutBlockBD() != null) && (connectD != null)) {
//             blocksAndTracksMap.put(connectD, getLayoutBlockBD().getDisplayName());
//         }
//
//         List<Set<String>> TrackNameSets = null;
//         Set<String> TrackNameSet = null;
//         for (Map.Entry<LayoutTrack, String> entry : blocksAndTracksMap.entrySet()) {
//             LayoutTrack theConnect = entry.getKey();
//             String theBlockName = entry.getValue();
//
//             TrackNameSet = null;    // assume not found (pessimist!)
//             TrackNameSets = blockNamesToTrackNameSetsMap.get(theBlockName);
//             if (TrackNameSets != null) { // (#1)
//                 for (Set<String> checkTrackNameSet : TrackNameSets) {
//                     if (checkTrackNameSet.contains(getName())) { // (#2)
//                         TrackNameSet = checkTrackNameSet;
//                         break;
//                     }
//                 }
//             } else {    // (#3)
//                 log.debug("*New block ('{}') trackNameSets", theBlockName);
//                 TrackNameSets = new ArrayList<>();
//                 blockNamesToTrackNameSetsMap.put(theBlockName, TrackNameSets);
//             }
//             if (TrackNameSet == null) {
//                 TrackNameSet = new LinkedHashSet<>();
//                 TrackNameSets.add(TrackNameSet);
//             }
//             if (TrackNameSet.add(getName())) {
//                 log.debug("*    Add track ''{}'' to trackNameSet for block ''{}''", getName(), theBlockName);
//             }
//             theConnect.collectContiguousTracksNamesInBlockNamed(theBlockName, TrackNameSet);
//         }
    }   // collectContiguousTracksNamesInBlockNamed

    /**
     * {@inheritDoc}
     */
     //@Override
     /*public*/ void LevelXingView::collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/  QString blockName,
            /*@Nonnull*/  QSet<QString>* TrackNameSet) {
        throw new IllegalArgumentException("should have called Object instead of View temporary");
//         if (!TrackNameSet.contains(getName())) {
//             // check all the matching blocks in this track and...
//             //  #1) add us to TrackNameSet and...
//             //  #2) flood them
//             //check the AC blockName
//             if (getBlockNameAC().equals(blockName)) {
//                 // if we are added to the TrackNameSet
//                 if (TrackNameSet.add(getName())) {
//                     log.debug("*    Add track ''{}'for block ''{}''", getName(), blockName);
//                 }
//                 // it's time to play... flood your neighbours!
//                 if (connectA != null) {
//                     connectA.collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
//                 }
//                 if (connectC != null) {
//                     connectC.collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
//                 }
//             }
//             //check the BD blockName
//             if (getBlockNameBD().equals(blockName)) {
//                 // if we are added to the TrackNameSet
//                 if (TrackNameSet.add(getName())) {
//                     log.debug("*    Add track ''{}''for block ''{}''", getName(), blockName);
//                 }
//                 // it's time to play... flood your neighbours!
//                 if (connectB != null) {
//                     connectB.collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
//                 }
//                 if (connectD != null) {
//                     connectD.collectContiguousTracksNamesInBlockNamed(blockName, TrackNameSet);
//                 }
//             }
//         }
    }

    /**
     * {@inheritDoc}
     */
     //@Override
     /*public*/ void LevelXingView::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
        throw  IllegalArgumentException("should have called Object instead of View temporary");
//         setLayoutBlockAC(layoutBlock);
//         setLayoutBlockBD(layoutBlock);
     }

    /*private*/ /*final*/  /*static*/ Logger* LevelXingView::log = LoggerFactory::getLogger("LevelXingView");

