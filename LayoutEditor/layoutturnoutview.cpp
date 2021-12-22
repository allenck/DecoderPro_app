#include "layoutturnoutview.h"
#include "layouteditor.h"
#include <QtMath>
#include "mathutil.h"
#include <QGraphicsSceneMouseEvent>
#include "loggerfactory.h"
#include "layoutturnouteditor.h"
#include "layouteditortoolbarpanel.h"
#include "joptionpane.h"

/**
 * MVC View component for the LayoutTurnout class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutTurnoutView extends LayoutTrackView {

/*public*/ LayoutTurnoutView::LayoutTurnoutView(/*@Nonnull*/ LayoutTurnout* turnout,
        /*@Nonnull*/ QPointF c, double rot,
        /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTrackView(turnout, c, layoutEditor)
{
    common(turnout, c, rot, 1.0, 1.0, layoutEditor);
}

/**
 * Constructor method.
 *
 * @param turnout      the layout turnout to create the view for.
 * @param c            where to put it
 * @param rot          for display
 * @param xFactor      for display
 * @param yFactor      for display
 * @param layoutEditor what layout editor panel to put it in
 */
/*public*/ LayoutTurnoutView::LayoutTurnoutView(/*@Nonnull*/ LayoutTurnout* turnout,
        /*@Nonnull*/ QPointF c, double rot,
        double xFactor, double yFactor,
        /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTrackView(turnout, c, layoutEditor)
    //super(turnout, c, layoutEditor);
 {
  common(turnout, c, rot, xFactor, yFactor, layoutEditor);
 }

 void LayoutTurnoutView::common(/*@Nonnull*/ LayoutTurnout* turnout,
         /*@Nonnull*/ QPointF c, double rot,
         double xFactor, double yFactor,
         /*@Nonnull*/ LayoutEditor* layoutEditor)
 {

    this->turnout = turnout;

    setIdent(turnout->getName());

    int version = turnout->getVersion();

    // adjust initial coordinates
    if (turnout->getTurnoutType() == LayoutTurnout::TurnoutType::LH_TURNOUT) {
        dispB = QPointF(layoutEditor->getTurnoutBX(), 0.0);
        dispA = QPointF(layoutEditor->getTurnoutCX(), -layoutEditor->getTurnoutWid());
    } else if (turnout->getTurnoutType() == LayoutTurnout::TurnoutType::RH_TURNOUT) {
        dispB = QPointF(layoutEditor->getTurnoutBX(), 0.0);
        dispA = QPointF(layoutEditor->getTurnoutCX(), layoutEditor->getTurnoutWid());
    } else if (turnout->getTurnoutType() == LayoutTurnout::TurnoutType::WYE_TURNOUT) {
        dispB = QPointF(layoutEditor->getTurnoutBX(), 0.5 * layoutEditor->getTurnoutWid());
        dispA = QPointF(layoutEditor->getTurnoutBX(), -0.5 * layoutEditor->getTurnoutWid());
    } else if (turnout->getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER) {
        if (version == 2) {
            LayoutTrackView::setCoordsCenter(QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid()));
            pointB = QPointF(layoutEditor->getXOverLong() * 2, 0);
            pointC = QPointF(layoutEditor->getXOverLong() * 2, (layoutEditor->getXOverHWid() * 2));
            pointD = QPointF(0, (layoutEditor->getXOverHWid() * 2));
            LayoutTrackView::setCoordsCenter(c);
        } else {
            dispB = QPointF(layoutEditor->getXOverLong(), -layoutEditor->getXOverHWid());
            dispA = QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid());
        }
    } else if (turnout->getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
        if (version == 2) {
            LayoutTrackView::setCoordsCenter(QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid()));
            pointB = QPointF((layoutEditor->getXOverShort() + layoutEditor->getXOverLong()), 0);
            pointC = QPointF(layoutEditor->getXOverLong() * 2, (layoutEditor->getXOverHWid() * 2));
            pointD = QPointF((getCoordsCenter().x() - layoutEditor->getXOverShort()), (layoutEditor->getXOverHWid() * 2));
            LayoutTrackView::setCoordsCenter(c);
        } else {
            dispB = QPointF(layoutEditor->getXOverShort(), -layoutEditor->getXOverHWid());
            dispA = QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid());
        }
    } else if (turnout->getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
        if (version == 2) {
            LayoutTrackView::setCoordsCenter(QPointF(layoutEditor->getXOverLong(), layoutEditor->getXOverHWid()));

            pointA = QPointF((getCoordsCenter().x() - layoutEditor->getXOverShort()), 0);
            pointB = QPointF((layoutEditor->getXOverLong() * 2), 0);
            pointC = QPointF(layoutEditor->getXOverLong() + layoutEditor->getXOverShort(), (layoutEditor->getXOverHWid() * 2));
            pointD = QPointF(0, (layoutEditor->getXOverHWid() * 2));

            LayoutTrackView::setCoordsCenter(c);
        } else {
            dispB = QPointF(layoutEditor->getXOverLong(), -layoutEditor->getXOverHWid());
            dispA = QPointF(layoutEditor->getXOverShort(), layoutEditor->getXOverHWid());
        }
    }

    rotateCoords(rot);

    // adjust size of new turnout
    QPointF pt = QPointF(qRound(dispB.x() * xFactor),
            qRound(dispB.y() * yFactor));
    dispB = pt;
    pt = QPointF(qRound(dispA.x() * xFactor),
            qRound(dispA.y() * yFactor));
    dispA = pt;

    editor = new LayoutTurnoutEditor(layoutEditor);
}

/**
 * Returns true if this is a turnout (not a crossover or slip)
 *
 * @param type the turnout type
 * @return bool true if this is a turnout
 */
/*public*/ /*static*/ bool LayoutTurnoutView::isTurnoutTypeTurnout(LayoutTurnout::TurnoutType type) {
    return LayoutTurnout::isTurnoutTypeTurnout(type);
}

/**
 * Returns true if this is a turnout (not a crossover or slip)
 *
 * @return bool true if this is a turnout
 */
/*public*/ bool LayoutTurnoutView::isTurnoutTypeTurnout() {
    return turnout->isTurnoutTypeTurnout();
}

/**
 * Returns true if this is a crossover
 *
 * @param type the turnout type
 * @return bool true if this is a crossover
 */
/*public*/ /*static*/ bool LayoutTurnoutView::isTurnoutTypeXover(LayoutTurnout::TurnoutType type) {
    return LayoutTurnout::isTurnoutTypeXover(type);
}

/**
 * Returns true if this is a crossover
 *
 * @return bool true if this is a crossover
 */
/*public*/ bool LayoutTurnoutView::isTurnoutTypeXover() {
    return turnout->isTurnoutTypeXover();
}

/**
 * Returns true if this is a slip
 *
 * @param type the turnout type
 * @return bool true if this is a slip
 */
/*public*/ /*static*/ bool LayoutTurnoutView::isTurnoutTypeSlip(LayoutTurnout::TurnoutType type) {
    return LayoutTurnout::isTurnoutTypeSlip(type);
}

/**
 * Returns true if this is a slip
 *
 * @return bool true if this is a slip
 */
/*public*/ bool LayoutTurnoutView::isTurnoutTypeSlip() {
    return turnout->isTurnoutTypeSlip();
}

/**
 * Returns true if this has a single-track entrance end. (turnout or wye)
 *
 * @param type the turnout type
 * @return bool true if single track entrance
 */
/*public*/ /*static*/ bool LayoutTurnoutView::hasEnteringSingleTrack(LayoutTurnout::TurnoutType type) {
    return LayoutTurnout::hasEnteringSingleTrack(type);
}

/**
 * Returns true if this has a single-track entrance end. (turnout or wye)
 *
 * @return bool true if single track entrance
 */
/*public*/ bool LayoutTurnoutView::hasEnteringSingleTrack() {
    return LayoutTurnout::hasEnteringSingleTrack(getTurnoutType());
}

/**
 * Returns true if this has double track on the entrance end (crossover or
 * slip)
 *
 * @param type the turnout type
 * @return bool true if double track entrance
 */
/*public*/ /*static*/ bool LayoutTurnoutView::hasEnteringDoubleTrack(LayoutTurnout::TurnoutType type) {
    return LayoutTurnout::hasEnteringDoubleTrack(type);
}

/**
 * Returns true if this has double track on the entrance end (crossover or
 * slip)
 *
 * @return bool true if double track entrance
 */
/*public*/ bool LayoutTurnoutView::hasEnteringDoubleTrack() {
    return turnout->hasEnteringDoubleTrack();
}

/*public*/ /*final*/ LayoutTurnout* LayoutTurnoutView::getLayoutTurnout() {
    return turnout;
}  // getTurnout() gets the real Turnout in the LayoutTurnout

/**
 * {@inheritDoc}
 */
// this should only be used for debugging...
//@Override
/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::toString() {
    return "LayoutTurnout " + getName();
}

//
// Accessor methods
//
/*public*/ int LayoutTurnoutView::getVersion() {
    return version;
}

/*public*/ void LayoutTurnoutView::setVersion(int v) {
    version = v;
}

/*public*/ bool LayoutTurnoutView::useBlockSpeed() {
    return _useBlockSpeed;
}

// @CheckForNull - can this be null? or ""?
/*public*/ QString LayoutTurnoutView::getTurnoutName() {
    return turnout->getTurnoutName();
}

// @CheckForNull - can this be null? or ""?
/*public*/ QString LayoutTurnoutView::getSecondTurnoutName() {
    return turnout->getSecondTurnoutName();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getBlockName() {
    return turnout->getBlockName();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getBlockBName() {
    return turnout->getBlockBName();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getBlockCName() {
    return turnout->getBlockCName();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getBlockDName() {
    return turnout->getBlockDName();
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalHead(LayoutTurnout::Geometry loc) {
    return turnout->getSignalHead(loc);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalA1() {
    return turnout->getSignalA1();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalA1Name() {
    return turnout->getSignalA1Name();
}

/*public*/ void LayoutTurnoutView::setSignalA1Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalA1Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalA2() {
    return turnout->getSignalA2();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalA2Name() {
    return turnout->getSignalA2Name();
}

/*public*/ void LayoutTurnoutView::setSignalA2Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalA2Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalA3() {
    return turnout->getSignalA3();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalA3Name() {
    return turnout->getSignalA3Name();
}

/*public*/ void LayoutTurnoutView::setSignalA3Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalA3Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalB1() {
    return turnout->getSignalB1();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalB1Name() {
    return turnout->getSignalB1Name();
}

/*public*/ void LayoutTurnoutView::setSignalB1Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalB1Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalB2() {
    return turnout->getSignalB2();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalB2Name() {
    return turnout->getSignalB2Name();
}

/*public*/ void LayoutTurnoutView::setSignalB2Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalB2Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalC1() {
    return turnout->getSignalC1();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalC1Name() {
    return turnout->getSignalC1Name();
}

/*public*/ void LayoutTurnoutView::setSignalC1Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalC1Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalC2() {
    return turnout->getSignalC2();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalC2Name() {
    return turnout->getSignalC2Name();
}

/*public*/ void LayoutTurnoutView::setSignalC2Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalC2Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalD1() {
    return turnout->getSignalD1();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalD1Name() {
    return turnout->getSignalD1Name();
}

/*public*/ void LayoutTurnoutView::setSignalD1Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalD1Name(signalHead);
}

//@CheckForNull
/*public*/ SignalHead* LayoutTurnoutView::getSignalD2() {
    return turnout->getSignalD2();
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalD2Name() {
    return turnout->getSignalD2Name();
}

/*public*/ void LayoutTurnoutView::setSignalD2Name(/*@CheckForNull*/ QString signalHead) {
    turnout->setSignalD2Name(signalHead);
}

/*public*/ void LayoutTurnoutView::removeBeanReference(/*@CheckForNull*/ NamedBean* nb) {
    turnout->removeBeanReference(nb);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool LayoutTurnoutView::canRemove() {
    return turnout->canRemove();
}

/**
 * Build a list of sensors, signal heads, and signal masts attached to a
 * turnout point.
 *
 * @param pointName Specify the point (A-D) or all (All) points.
 * @return a list of bean reference names.
 */
/*@Nonnull*/
/*public*/ QList<QString> LayoutTurnoutView::getBeanReferences(QString /*pointName*/) {
    throw IllegalArgumentException("should be called on LayoutTurnout");
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalAMastName() {
    return turnout->getSignalAMastName();
}

//@CheckForNull
/*public*/ SignalMast* LayoutTurnoutView::getSignalAMast() {
    return turnout->getSignalAMast();
}

/*public*/ void LayoutTurnoutView::setSignalAMast(/*@CheckForNull*/ QString signalMast) {
    turnout->setSignalAMast(signalMast);
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalBMastName() {
    return turnout->getSignalBMastName();
}

//@CheckForNull
/*public*/ SignalMast* LayoutTurnoutView::getSignalBMast() {
    return turnout->getSignalBMast();
}

/*public*/ void LayoutTurnoutView::setSignalBMast(/*@CheckForNull*/ QString signalMast) {
    turnout->setSignalBMast(signalMast);
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalCMastName() {
    return turnout->getSignalCMastName();
}

//@CheckForNull
/*public*/ SignalMast* LayoutTurnoutView::getSignalCMast() {
    return turnout->getSignalCMast();
}

/*public*/ void LayoutTurnoutView::setSignalCMast(/*@CheckForNull*/ QString signalMast) {
    turnout->setSignalCMast(signalMast);
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSignalDMastName() {
    return turnout->getSignalDMastName();
}

//@CheckForNull
/*public*/ SignalMast* LayoutTurnoutView::getSignalDMast() {
    return turnout->getSignalDMast();
}

/*public*/ void LayoutTurnoutView::setSignalDMast(/*@CheckForNull*/ QString signalMast) {
    turnout->setSignalDMast(signalMast);
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSensorAName() {
    return turnout->getSensorAName();
}

//@CheckForNull
/*public*/ Sensor* LayoutTurnoutView::getSensorA() {
    return turnout->getSensorA();
}

/*public*/ void LayoutTurnoutView::setSensorA(/*@CheckForNull*/  QString sensorName) {
    turnout->setSensorA(sensorName);
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSensorBName() {
    return turnout->getSensorBName();
}

//@CheckForNull
/*public*/ Sensor* LayoutTurnoutView::getSensorB() {
    return turnout->getSensorB();
}

/*public*/ void LayoutTurnoutView::setSensorB(/*@CheckForNull*/  QString sensorName) {
    turnout->setSensorB(sensorName);
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSensorCName() {
    return turnout->getSensorCName();
}

//@CheckForNull
/*public*/ Sensor* LayoutTurnoutView::getSensorC() {
    return turnout->getSensorC();
}

/*public*/ void LayoutTurnoutView::setSensorC(/*@CheckForNull*/  QString sensorName) {
    turnout->setSensorC(sensorName);
}

/*@Nonnull*/
/*public*/ QString LayoutTurnoutView::getSensorDName() {
    return turnout->getSensorDName();
}

//@CheckForNull
/*public*/ Sensor* LayoutTurnoutView::getSensorD() {
    return turnout->getSensorD();
}

/*public*/ void LayoutTurnoutView::setSensorD(/*@CheckForNull*/  QString sensorName) {
    turnout->setSensorD(sensorName);
}

/*public*/ QString LayoutTurnoutView::getLinkedTurnoutName() {
    return turnout->getLinkedTurnoutName();
}

/*public*/ void LayoutTurnoutView::setLinkedTurnoutName(/*@Nonnull*/ QString s) {
    turnout->setSensorD(s);
}  // Could be done with changing over to a NamedBeanHandle

/*public*/ LayoutTurnout::LinkType LayoutTurnoutView::getLinkType() {
    return turnout->getLinkType();
}

/*public*/ void LayoutTurnoutView::setLinkType(LayoutTurnout::LinkType ltype) {
    turnout->setLinkType(ltype);
}

/*public*/ LayoutTurnout::TurnoutType LayoutTurnoutView::getTurnoutType() {
    return turnout->getTurnoutType();
}

/*public*/ LayoutTrack* LayoutTurnoutView::getConnectA() {
    return turnout->getConnectA();
}

/*public*/ LayoutTrack* LayoutTurnoutView::getConnectB() {
    return turnout->getConnectB();
}

/*public*/ LayoutTrack* LayoutTurnoutView::getConnectC() {
    return turnout->getConnectC();
}

/*public*/ LayoutTrack* LayoutTurnoutView::getConnectD() {
    return turnout->getConnectD();
}

/**
 * @return null if no turnout set // temporary? Might want to run all calls
 *         through this class; but this is getModel equiv
 */
// @CheckForNull  temporary
/*public*/ Turnout* LayoutTurnoutView::getTurnout() {
    return turnout->getTurnout();
}

/*public*/ int LayoutTurnoutView::getContinuingSense() {
    return turnout->getContinuingSense();
}

/**
 *
 * @return true is the continuingSense matches the known state
 */
/*public*/ bool LayoutTurnoutView::isInContinuingSenseState() {
    return turnout->isInContinuingSenseState();
}

/*public*/ void LayoutTurnoutView::setTurnout(/*@Nonnull*/ QString tName) {
    turnout->setTurnout(tName);
}

// @CheckForNull - need to have a better way to handle null case
/*public*/ Turnout* LayoutTurnoutView::getSecondTurnout() {
    return turnout->getSecondTurnout();
}

/*public*/ void LayoutTurnoutView::setSecondTurnout(/*@Nonnull*/ QString tName) {
    turnout->setSecondTurnout(tName);
}

/*public*/ void LayoutTurnoutView::setSecondTurnoutInverted(bool inverted) {
    turnout->setSecondTurnoutInverted(inverted);
}

/*public*/ void LayoutTurnoutView::setContinuingSense(int sense) {
    turnout->setContinuingSense(sense);
}

/*public*/ void LayoutTurnoutView::setDisabled(bool state) {
    turnout->setDisabled(state);
    if (layoutEditor != nullptr) {
        layoutEditor->redrawPanel();
    }
}

/*public*/ bool LayoutTurnoutView::isDisabled() {
    return turnout->isDisabled();
}

/*public*/ void LayoutTurnoutView::setDisableWhenOccupied(bool state) {
    turnout->setDisableWhenOccupied(state);
    if (layoutEditor != nullptr) {
        layoutEditor->redrawPanel();
    }
}

/*public*/ bool LayoutTurnoutView::isDisabledWhenOccupied() {
    return turnout->isDisabledWhenOccupied();
}

/**
 * {@inheritDoc}
 */
//@Override
//@CheckForNull
/*public*/ LayoutTrack* LayoutTurnoutView::getConnection(HitPointType::TYPES connectionType) throw (JmriException) {
    return turnout->getConnection(connectionType);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::setConnection(HitPointType::TYPES connectionType, /*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) throw (JmriException) {
    turnout->setConnection(connectionType, o, type);
}

/*public*/ void LayoutTurnoutView::setConnectA(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) {
    turnout->setConnectA(o, type);
}

/*public*/ void LayoutTurnoutView::setConnectB(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) {
    turnout->setConnectB(o, type);
}

/*public*/ void LayoutTurnoutView::setConnectC(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) {
    turnout->setConnectC(o, type);
}

/*public*/ void LayoutTurnoutView::setConnectD(/*@CheckForNull*/ LayoutTrack* o, HitPointType::TYPES type) {
    turnout->setConnectD(o, type);
}

// @CheckForNull - temporary while we work on centralized protection
/*public*/ LayoutBlock* LayoutTurnoutView::getLayoutBlock() {
    return turnout->getLayoutBlock();
}

// @CheckForNull - temporary while we work on centralized protection
/*public*/ LayoutBlock* LayoutTurnoutView::getLayoutBlockB() {
    return turnout->getLayoutBlockB();
}

// @CheckForNull - temporary while we work on centralized protection
/*public*/ LayoutBlock* LayoutTurnoutView::getLayoutBlockC() {
    return turnout->getLayoutBlockC();
}

// @CheckForNull - temporary while we work on centralized protection
/*public*/ LayoutBlock* LayoutTurnoutView::getLayoutBlockD() {
    return turnout->getLayoutBlockD();
}

/*@Nonnull*/
/*public*/ QPointF LayoutTurnoutView::getCoordsA() {
    if (isTurnoutTypeXover()) {
        if (version == 2) {
            return pointA;
        }
        return MathUtil::subtract(getCoordsCenter(), dispA);
    } else if (getTurnoutType() == LayoutTurnout::TurnoutType::WYE_TURNOUT) {
        return MathUtil::subtract(getCoordsCenter(), MathUtil::midPoint(dispB, dispA));
    } else {
        return MathUtil::subtract(getCoordsCenter(), dispB);
    }
}

/*@Nonnull*/
/*public*/ QPointF LayoutTurnoutView::getCoordsB() {
    if ((version == 2) && isTurnoutTypeXover()) {
        return pointB;
    }
    return MathUtil::add(getCoordsCenter(), dispB);
}

/*@Nonnull*/
/*public*/ QPointF LayoutTurnoutView::getCoordsC() {
    if ((version == 2) && isTurnoutTypeXover()) {
        return pointC;
    }
    return MathUtil::add(getCoordsCenter(), dispA);
}

/*@Nonnull*/
/*public*/ QPointF LayoutTurnoutView::getCoordsD() {
    if ((version == 2) && isTurnoutTypeXover()) {
        return pointD;
    }
    // only allowed for single and double crossovers
    return MathUtil::subtract(getCoordsCenter(), dispB);
}

/**
 * {@inheritDoc}
 */
//@Override
/*@Nonnull*/
/*public*/ QPointF LayoutTurnoutView::getCoordsForConnectionType(HitPointType::TYPES connectionType) {
    QPointF result = getCoordsCenter();
    switch (connectionType) {
        case HitPointType::TURNOUT_CENTER:
            break;
        case HitPointType::TURNOUT_A:
            result = getCoordsA();
            break;
        case HitPointType::TURNOUT_B:
            result = getCoordsB();
            break;
        case HitPointType::TURNOUT_C:
            result = getCoordsC();
            break;
        case HitPointType::TURNOUT_D:
            result = getCoordsD();
            break;
        default:
            log->error(tr("%1.getCoordsForConnectionType(%2); Invalid Connection Type").arg(
                    getName(), connectionType)); // NOI18N
    }
    return result;
}

/**
 * {@inheritDoc}
 */
//@Override
/*@Nonnull*/
/*public*/ QRectF LayoutTurnoutView::getBounds() {
    QRectF result;

    QPointF pointA = getCoordsA();
    result = QRectF(pointA.x(), pointA.y(), 0, 0);
    MathUtil::add(result, getCoordsB());
    MathUtil::add(result, getCoordsC());
    if (isTurnoutTypeXover() || isTurnoutTypeSlip()) {
        MathUtil::add(result, getCoordsD());
    }
    return result;
}

// updates connectivity for blocks assigned to this turnout and connected track segments
/*public*/ void LayoutTurnoutView::updateBlockInfo() {
    turnout->updateBlockInfo();
}

/**
 * Set default size parameters to correspond to this turnout's size.
 * <p>
 * note: only protected so LayoutTurnoutTest can call it
 */
/*protected*/ void LayoutTurnoutView::setUpDefaultSize() {
  // remove the overall scale factor
  double bX = dispB.x() / layoutEditor->gContext->getXScale();
  double bY = dispB.y() / layoutEditor->gContext->getYScale();
  double cX = dispA.x() / layoutEditor->gContext->getXScale();
  double cY = dispA.y() / layoutEditor->gContext->getYScale();
  // calculate default parameters according to type of turnout
  //double lenB = MathUtil::hypot(bX, bY);
  double lenB = qSqrt((bX*bX) + (bY*bY));
  double lenC = qSqrt((cX*cX) + (cY*cY));
  double distBC = qSqrt(((bX-cX)*(bX-cX)) + ((bY-cY)*(bY-cY)));
  if ((getTurnoutType() == LayoutTurnout::TurnoutType::LH_TURNOUT)
          || (getTurnoutType() == LayoutTurnout::TurnoutType::RH_TURNOUT)) {

      layoutEditor->setTurnoutBX(qRound(lenB + 0.1));
      double xc = ((bX * cX) + (bY * cY)) / lenB;
      layoutEditor->setTurnoutCX(qRound(xc + 0.1));
      layoutEditor->setTurnoutWid(qRound(qSqrt((lenC * lenC) - (xc * xc)) + 0.1));
  } else if (getTurnoutType() == LayoutTurnout::TurnoutType::WYE_TURNOUT) {
      double xx = qSqrt((lenB * lenB) - (0.25 * (distBC * distBC)));
      layoutEditor->setTurnoutBX(qRound(xx + 0.1));
      layoutEditor->setTurnoutCX(qRound(xx + 0.1));
      layoutEditor->setTurnoutWid(qRound(distBC + 0.1));
  } else {
      if (version == 2) {
          double aX = pointA.x() / layoutEditor->gContext->getXScale();
          double aY = pointA.y() / layoutEditor->gContext->getYScale();
          bX = pointB.x() / layoutEditor->gContext->getXScale();
          bY = pointB.y() / layoutEditor->gContext->getYScale();
          cX = pointC.x() / layoutEditor->gContext->getXScale();
          cY = pointC.y() / layoutEditor->gContext->getYScale();
          //double lenAB = MathUtil::hypot(bX - aX, bY - aY);
          double lenAB = qSqrt((bX - aX)*(bX - aX) - (bY - aY)*(bY - aY));
          if (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER) {
              double lenBC = MathUtil::hypot(bX - cX, bY - cY);
              layoutEditor->setXOverLong(qRound(lenAB / 2)); // set to half to be backwardly compatible
              layoutEditor->setXOverHWid(qRound(lenBC / 2));
              layoutEditor->setXOverShort(qRound((0.5 * lenAB) / 2));
          } else if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
              lenAB = lenAB / 3;
              layoutEditor->setXOverShort(qRound(lenAB));
              layoutEditor->setXOverLong(qRound(lenAB * 2));
              double opp = (aY - bY);
              double ang = qAsin(opp / (lenAB * 3));
              opp = qSin(ang) * lenAB;
              bY = bY + opp;
              double adj = qCos(ang) * lenAB;
              bX = bX + adj;
              double lenBC = MathUtil::hypot(bX - cX, bY - cY);
              layoutEditor->setXOverHWid(qRound(lenBC / 2));
          } else if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
              double dY = pointD.y() / layoutEditor->gContext->getYScale();
              lenAB = lenAB / 3;
              layoutEditor->setXOverShort(qRound(lenAB));
              layoutEditor->setXOverLong(qRound(lenAB * 2));
              double opp = (dY - cY);
              double ang = qAsin(opp / (lenAB * 3)); // Length of AB should be the same as CD
              opp = qSin(ang) * lenAB;
              cY = cY + opp;
              double adj = qCos(ang) * lenAB;
              cX = cX + adj;
              double lenBC = MathUtil::hypot(bX - cX, bY - cY);
              layoutEditor->setXOverHWid(qRound(lenBC / 2));
          }
      } else if (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER) {
          double lng = qSqrt((lenB * lenB) - (0.25 * (distBC * distBC)));
          layoutEditor->setXOverLong(qRound(lng + 0.1));
          layoutEditor->setXOverHWid(qRound((0.5 * distBC) + 0.1));
          layoutEditor->setXOverShort(qRound((0.5 * lng) + 0.1));
      } else if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
          double distDC = MathUtil::hypot(bX + cX, bY + cY);
          layoutEditor->setXOverShort(qRound((0.25 * distDC) + 0.1));
          layoutEditor->setXOverLong(qRound((0.75 * distDC) + 0.1));
          double hwid = qSqrt((lenC * lenC) - (0.5625 * distDC * distDC));
          layoutEditor->setXOverHWid(qRound(hwid + 0.1));
      } else if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
          double distDC = MathUtil::hypot(bX + cX, bY + cY);
          layoutEditor->setXOverShort(qRound((0.25 * distDC) + 0.1));
          layoutEditor->setXOverLong(qRound((0.75 * distDC) + 0.1));
          double hwid = qSqrt((lenC * lenC) - (0.0625 * distDC * distDC));
          layoutEditor->setXOverHWid(qRound(hwid + 0.1));
      }
  }
}

/**
 * Set up Layout Block(s) for this turnout->
 *
 * @param newLayoutBlock* See {@link LayoutTurnout#setLayoutBlock} for
 *                       definition
 */
/*public*/ void LayoutTurnoutView::setLayoutBlock(LayoutBlock* newLayoutBlock) {
    turnout->setLayoutBlock(newLayoutBlock);
    // correct any graphical artifacts
    setTrackSegmentBlocks();
}

/*public*/ void LayoutTurnoutView::setLayoutBlockB(LayoutBlock* newLayoutBlock) {
    turnout->setLayoutBlockB(newLayoutBlock);
    // correct any graphical artifacts
    setTrackSegmentBlocks();
}

/*public*/ void LayoutTurnoutView::setLayoutBlockC(LayoutBlock* newLayoutBlock) {
    turnout->setLayoutBlockC(newLayoutBlock);
    // correct any graphical artifacts
    setTrackSegmentBlocks();
}

/*public*/ void LayoutTurnoutView::setLayoutBlockD(LayoutBlock* newLayoutBlock) {
    turnout->setLayoutBlockD(newLayoutBlock);
    // correct any graphical artifacts
    setTrackSegmentBlocks();
}

/*public*/ void LayoutTurnoutView::setLayoutBlockByName(/*@Nonnull*/ QString name) {
    turnout->setLayoutBlockByName(name);
}

/*public*/ void LayoutTurnoutView::setLayoutBlockBByName(/*@Nonnull*/ QString name) {
    turnout->setLayoutBlockByName(name);
}

/*public*/ void LayoutTurnoutView::setLayoutBlockCByName(/*@Nonnull*/ QString name) {
    turnout->setLayoutBlockByName(name);
}

/*public*/ void LayoutTurnoutView::setLayoutBlockDByName(/*@Nonnull*/ QString name) {
    turnout->setLayoutBlockByName(name);
}

/**
 * Check each connection point and update the block value for very short
 * track segments.
 *
 * @since 4.11.6
 */
void LayoutTurnoutView::setTrackSegmentBlocks() {
    setTrackSegmentBlock(HitPointType::TURNOUT_A, false);
    setTrackSegmentBlock(HitPointType::TURNOUT_B, false);
    setTrackSegmentBlock(HitPointType::TURNOUT_C, false);
    if (hasEnteringDoubleTrack()) {
        setTrackSegmentBlock(HitPointType::TURNOUT_D, false);
    }
}

/**
 * Update the block for a track segment that provides a (graphically) short
 * connection between a turnout and another object, normally another
 * turnout-> These are hard to see and are frequently missed.
 * <p>
 * Skip block changes if signal heads, masts or sensors have been assigned.
 * Only track segments with a length less than the turnout circle radius
 * will be changed.
 *
 * @since 4.11.6
 * @param pointType   The point type which indicates which turnout
 *                    connection.
 * @param isAutomatic True for the automatically generated track segment
 *                    created by the drag-n-drop process. False for existing
 *                    connections which require a track segment length
 *                    calculation.
 */
void LayoutTurnoutView::setTrackSegmentBlock(HitPointType::TYPES pointType, bool isAutomatic) {
    TrackSegment* trkSeg;
    QPointF pointCoord;
    LayoutBlock* blockA = getLayoutBlock();
    LayoutBlock* blockB = getLayoutBlock();
    LayoutBlock* blockC = getLayoutBlock();
    LayoutBlock* blockD = getLayoutBlock();
    LayoutBlock* currBlk = blockA;

    switch (pointType) {
        case HitPointType::TURNOUT_A:
        case HitPointType::SLIP_A:
            if (signalA1HeadNamed != nullptr) {
                return;
            }
            if (signalA2HeadNamed != nullptr) {
                return;
            }
            if (signalA3HeadNamed != nullptr) {
                return;
            }
            if (getSignalAMast() != nullptr) {
                return;
            }
            if (getSensorA() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) getConnectA();
            pointCoord = getCoordsA();
            break;
        case HitPointType::TURNOUT_B:
        case HitPointType::SLIP_B:
            if (signalB1HeadNamed != nullptr) {
                return;
            }
            if (signalB2HeadNamed != nullptr) {
                return;
            }
            if (getSignalBMast() != nullptr) {
                return;
            }
            if (getSensorB() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) getConnectB();
            pointCoord = getCoordsB();
            if (isTurnoutTypeXover()) {
                currBlk = blockB != nullptr ? blockB : blockA;
            }
            break;
        case HitPointType::TURNOUT_C:
        case HitPointType::SLIP_C:
            if (signalC1HeadNamed != nullptr) {
                return;
            }
            if (signalC2HeadNamed != nullptr) {
                return;
            }
            if (getSignalCMast() != nullptr) {
                return;
            }
            if (getSensorC() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) getConnectC();
            pointCoord = getCoordsC();
            if (isTurnoutTypeXover()) {
                currBlk = blockC != nullptr ? blockC : blockA;
            }
            break;
        case HitPointType::TURNOUT_D:
        case HitPointType::SLIP_D:
            if (signalD1HeadNamed != nullptr) {
                return;
            }
            if (signalD2HeadNamed != nullptr) {
                return;
            }
            if (getSignalDMast() != nullptr) {
                return;
            }
            if (getSensorD() != nullptr) {
                return;
            }
            trkSeg = (TrackSegment*) getConnectD();
            pointCoord = getCoordsD();
            if (isTurnoutTypeXover()) {
                currBlk = blockD != nullptr ? blockD : blockA;
            }
            break;
        default:
            log->error(tr("%1.setTrackSegmentBlock(%2, %3); Invalid pointType").arg(
                    getName(), HitPointType::toString(pointType), isAutomatic ? "AUTO" : "NON-AUTO"));
            return;
    }
    if (trkSeg != nullptr) {
        double chkSize = layoutEditor->SIZE * layoutEditor->getTurnoutCircleSize();
        double segLength = 0;
        if (!isAutomatic) {
            QPointF segCenter = getCoordsCenter();
            segLength = MathUtil::distance(pointCoord, segCenter) * 2;
        }
        if (segLength < chkSize) {

            log->debug("Set block:");
            log->debug(tr("    seg: %1").arg(trkSeg->toString()));
            log->debug(tr("    cor: %1 %2").arg(pointCoord.x(), pointCoord.y()));
            log->debug(tr("    blk: %1").arg((currBlk == nullptr) ? "null" : currBlk->getDisplayName()));
            log->debug(tr("    len: %1").arg(segLength));

            trkSeg->setLayoutBlock(currBlk);
            layoutEditor->getLEAuxTools()->setBlockConnectivityChanged();
        }
    }
}

/**
 * Test if turnout legs are mainline track or not.
 *
 * @return true if connecting track segment is mainline; Defaults to not
 *         mainline if connecting track segment is missing
 */
/*public*/ bool LayoutTurnoutView::isMainlineA() {
    return turnout->isMainlineA();
}

/*public*/ bool LayoutTurnoutView::isMainlineB() {
    return turnout->isMainlineB();
}

/*public*/ bool LayoutTurnoutView::isMainlineC() {
    return turnout->isMainlineC();
}

/*public*/ bool LayoutTurnoutView::isMainlineD() {
    return turnout->isMainlineD();
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ HitPointType::TYPES LayoutTurnoutView::findHitPointType(/*@Nonnull*/ QPointF hitPoint, bool useRectangles, bool requireUnconnected) {
    HitPointType::TYPES result = HitPointType::NONE;  // assume point not on connection
    // note: optimization here: instead of creating rectangles for all the
    // points to check below, we create a rectangle for the test point
    // and test if the points below are in that rectangle instead.
    QRectF r = layoutEditor->layoutEditorControlCircleRectAt(hitPoint);
    QPointF p, minPoint = MathUtil::zeroPoint2D;

    double circleRadius = layoutEditor->SIZE * layoutEditor->getTurnoutCircleSize();
    double distance, minDistance = INFINITY;

    // check center coordinates
    if (!requireUnconnected) {
        p = getCoordsCenter();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = HitPointType::TURNOUT_CENTER;
        }
    }

    // check the A connection point
    if (!requireUnconnected || (getConnectA() == nullptr)) {
        p = getCoordsA();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = HitPointType::TURNOUT_A;
        }
    }

    // check the B connection point
    if (!requireUnconnected || (getConnectB() == nullptr)) {
        p = getCoordsB();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = HitPointType::TURNOUT_B;
        }
    }

    // check the C connection point
    if (!requireUnconnected || (getConnectC() == nullptr)) {
        p = getCoordsC();
        distance = MathUtil::distance(p, hitPoint);
        if (distance < minDistance) {
            minDistance = distance;
            minPoint = p;
            result = HitPointType::TURNOUT_C;
        }
    }

    // check the D connection point
    if (isTurnoutTypeXover()) {
        if (!requireUnconnected || (getConnectD() == nullptr)) {
            p = getCoordsD();
            distance = MathUtil::distance(p, hitPoint);
            if (distance < minDistance) {
                minDistance = distance;
                minPoint = p;
                result = HitPointType::TURNOUT_D;
            }
        }
    }
    if ((useRectangles && !r.contains(minPoint))
            || (!useRectangles && (minDistance > circleRadius))) {
        result = HitPointType::NONE;
    }
    return result;
}   // findHitPointType

/*
* Modify coordinates methods
 */
/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::setCoordsCenter(/*@Nonnull*/ QPointF p) {
    QPointF offset = MathUtil::subtract(p, getCoordsCenter());
    pointA = MathUtil::add(pointA, offset);
    pointB = MathUtil::add(pointB, offset);
    pointC = MathUtil::add(pointC, offset);
    pointD = MathUtil::add(pointD, offset);
    LayoutTrackView::setCoordsCenter(p);
}

// temporary should be private once LayoutTurnout no longer needs it
void LayoutTurnoutView::reCalculateCenter() {
    LayoutTrackView::setCoordsCenter(MathUtil::midPoint(pointA, pointC));
}

/*public*/ void LayoutTurnoutView::setCoordsA(/*@Nonnull*/ QPointF p) {
    pointA = p;
    if (version == 2) {
        reCalculateCenter();
    }
    double x = getCoordsCenter().x() - p.x();
    double y = getCoordsCenter().y() - p.y();
    if (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER) {
        dispA = QPointF(x, y);
        // adjust to maintain rectangle
        double oldLength = MathUtil::length(dispB);
        double newLength = MathUtil::hypot(x, y);
        dispB = MathUtil::multiply(dispB, newLength / oldLength);
    } else if ((getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
            || (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER)) {
        dispA = QPointF(x, y);
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = -y;
        double xi = 0.0;
        double yi = b;
        if ((dispB.x() + x) != 0.0) {
            a = (dispB.y() + y) / (dispB.x() + x);
            b = -y + (a * x);
            xi = -b / (a + (1.0 / a));
            yi = (a * xi) + b;
        }
        if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
            x = xi - (0.333333 * (-x - xi));
            y = yi - (0.333333 * (-y - yi));
        } else if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
            x = xi - (3.0 * (-x - xi));
            y = yi - (3.0 * (-y - yi));
        }
        dispB = QPointF(x, y);
    } else if (getTurnoutType() == LayoutTurnout::TurnoutType::WYE_TURNOUT) {
        // modify both to maintain same angle at wye
        double temX = (dispB.x() + dispA.x());
        double temY = (dispB.y() + dispA.y());
        double temXx = (dispB.x() - dispA.x());
        double temYy = (dispB.y() - dispA.y());
        double tan = qSqrt(((temX * temX) + (temY * temY))
                / ((temXx * temXx) + (temYy * temYy)));
        double xx = x + (y / tan);
        double yy = y - (x / tan);
        dispA = QPointF(xx, yy);
        xx = x - (y / tan);
        yy = y + (x / tan);
        dispB = QPointF(xx, yy);
    } else {
        dispB = QPointF(x, y);
    }
}

/*public*/ void LayoutTurnoutView::setCoordsB(QPointF p) {
    pointB = p;
    double x = getCoordsCenter().x() - p.x();
    double y = getCoordsCenter().y() - p.y();
    dispB = QPointF(-x, -y);
    if ((getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER)
            || (getTurnoutType() == LayoutTurnout::TurnoutType::WYE_TURNOUT)) {
        // adjust to maintain rectangle or wye shape
        double oldLength = MathUtil::length(dispA);
        double newLength = MathUtil::hypot(x, y);
        dispA = MathUtil::multiply(dispA, newLength / oldLength);
    } else if ((getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
            || (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER)) {
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = y;
        double xi = 0.0;
        double yi = b;
        if ((dispA.x() - x) != 0.0) {
            if ((-dispA.x() + x) == 0) {
                /* we can in some situations eg 90' vertical end up with a 0 value,
                so hence remove a small amount so that we
                don't have a divide by zero issue */
                x = x - 0.0000000001;
            }
            a = (dispA.y() - y) / (dispA.x() - x);
            b = y - (a * x);
            xi = -b / (a + (1.0 / a));
            yi = (a * xi) + b;
        }
        if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
            x = xi - (0.333333 * (x - xi));
            y = yi - (0.333333 * (y - yi));
        } else if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
            x = xi - (3.0 * (x - xi));
            y = yi - (3.0 * (y - yi));
        }
        dispA = QPointF(x, y);
    }
}

/*public*/ void LayoutTurnoutView::setCoordsC(QPointF p) {
    pointC = p;
    if (version == 2) {
        reCalculateCenter();
    }
    double x = getCoordsCenter().x() - p.x();
    double y = getCoordsCenter().y() - p.y();
    dispA = QPointF(-x, -y);
    if ((getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER)
            || (getTurnoutType() == LayoutTurnout::TurnoutType::WYE_TURNOUT)) {
        // adjust to maintain rectangle or wye shape
        double oldLength = MathUtil::length(dispB);
        double newLength = MathUtil::hypot(x, y);
        dispB = MathUtil::multiply(dispB, newLength / oldLength);
    } else if ((getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
            || (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER)) {
        double a = 0.0;
        double b = -y;
        double xi = 0.0;
        double yi = b;
        if ((dispB.x() + x) != 0.0) {
            if ((-dispB.x() + x) == 0) {
                /* we can in some situations eg 90' vertical end up with a 0 value,
                so hence remove a small amount so that we
                don't have a divide by zero issue */

                x = x - 0.0000000001;
            }
            a = (-dispB.y() + y) / (-dispB.x() + x);
            b = -y + (a * x);
            xi = -b / (a + (1.0 / a));
            yi = (a * xi) + b;
        }
        if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
            x = xi - (0.333333 * (-x - xi));
            y = yi - (0.333333 * (-y - yi));
        } else if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
            x = xi - (3.0 * (-x - xi));
            y = yi - (3.0 * (-y - yi));
        }
        dispB = QPointF(-x, -y);
    }
}

/*public*/ void LayoutTurnoutView::setCoordsD(QPointF p) {
    pointD = p;

    // only used for crossovers
    double x = getCoordsCenter().x() - p.x();
    double y = getCoordsCenter().y() - p.y();
    dispB = QPointF(x, y);
    if (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER) {
        // adjust to maintain rectangle
        double oldLength = MathUtil::length(dispA);
        double newLength = MathUtil::hypot(x, y);
        dispA = MathUtil::multiply(dispA, newLength / oldLength);
    } else if ((getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
            || (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER)) {
        // adjust to maintain the parallelogram
        double a = 0.0;
        double b = y;
        double xi = 0.0;
        double yi = b;
        if ((dispA.x() + x) != 0.0) {
            a = (dispA.y() + y) / (dispA.x() + x);
            b = -y + (a * x);
            xi = -b / (a + (1.0 / a));
            yi = (a * xi) + b;
        }
        if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
            x = xi - (0.333333 * (-x - xi));
            y = yi - (0.333333 * (-y - yi));
        } else if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
            x = xi - (3.0 * (-x - xi));
            y = yi - (3.0 * (-y - yi));
        }
        dispA = QPointF(x, y);
    }
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::scaleCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    LayoutTrackView::setCoordsCenter(MathUtil::granulize(MathUtil::multiply(getCoordsCenter(), factor), 1.0));

    dispA = MathUtil::granulize(MathUtil::multiply(dispA, factor), 1.0);
    dispB = MathUtil::granulize(MathUtil::multiply(dispB, factor), 1.0);

    pointA = MathUtil::granulize(MathUtil::multiply(pointA, factor), 1.0);
    pointB = MathUtil::granulize(MathUtil::multiply(pointB, factor), 1.0);
    pointC = MathUtil::granulize(MathUtil::multiply(pointC, factor), 1.0);
    pointD = MathUtil::granulize(MathUtil::multiply(pointD, factor), 1.0);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::translateCoords(double xFactor, double yFactor) {
    QPointF factor = QPointF(xFactor, yFactor);
    LayoutTrackView::setCoordsCenter(MathUtil::add(getCoordsCenter(), factor));
    pointA = MathUtil::add(pointA, factor);
    pointB = MathUtil::add(pointB, factor);
    pointC = MathUtil::add(pointC, factor);
    pointD = MathUtil::add(pointD, factor);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::rotateCoords(double angleDEG) {
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

    pointA = rotatePoint(pointA, sineRot, cosineRot);
    pointB = rotatePoint(pointB, sineRot, cosineRot);
    pointC = rotatePoint(pointC, sineRot, cosineRot);
    pointD = rotatePoint(pointD, sineRot, cosineRot);
}

/*public*/ double LayoutTurnoutView::getRotationDEG() {
    double result = 0;
    switch (getTurnoutType()) {
        case LayoutTurnout::TurnoutType::RH_TURNOUT:
        case LayoutTurnout::TurnoutType::LH_TURNOUT:
        case LayoutTurnout::TurnoutType::WYE_TURNOUT: {
            result = 90 - MathUtil::computeAngleDEG(getCoordsA(), getCoordsCenter());
            break;
        }
        case LayoutTurnout::TurnoutType::DOUBLE_XOVER:
        case LayoutTurnout::TurnoutType::RH_XOVER:
        case LayoutTurnout::TurnoutType::LH_XOVER: {
            result = 90 - MathUtil::computeAngleDEG(getCoordsA(), getCoordsB());
            break;
        }
        default: {
            break;
        }
    }
    return result;
}

/**
 * Toggle turnout if clicked on, physical turnout exists, and not disabled.
 */
/*public*/ void LayoutTurnoutView::toggleTurnout() {
    turnout->toggleTurnout();
}

/**
 * Set the LayoutTurnout state. Used for sending the toggle command Checks
 * not disabled, disable when occupied Also sets secondary Turnout commanded
 * state
 *
 * @param state New state to set, eg turnout->CLOSED
 */
/*public*/ void LayoutTurnoutView::setState(int state) {
    turnout->setState(state);
}

/**
 * Get the LayoutTurnout state
 * <p>
 * Ensures the secondary Turnout state matches the primary
 *
 * @return the state, eg turnout->CLOSED or turnout->INCONSISTENT
 */
/*public*/ int LayoutTurnoutView::getState() {
    return turnout->getState();
}

/**
 * Is this turnout occupied?
 *
 * @return true if occupied
 */
/*private*/ bool LayoutTurnoutView::isOccupied() {
    return turnout->isOccupied();
}

/**
 * {@inheritDoc}
 */
//@Override
/*@Nonnull*/
/*protected*/ QMenu* LayoutTurnoutView::showPopup(/*@CheckForNull*/ QGraphicsSceneMouseEvent* mouseEvent) {
    if (popup != nullptr) {
        popup->clear();
    } else {
        popup = new QMenu();
    }

    if (layoutEditor->isEditable()) {
        QString label = "";
        switch (getTurnoutType()) {
            case LayoutTurnout::TurnoutType::RH_TURNOUT:
                label = tr("Right Turnout");
                break;
            case LayoutTurnout::TurnoutType::LH_TURNOUT:
                label = tr("Left Turnout");
                break;
            case LayoutTurnout::TurnoutType::WYE_TURNOUT:
                label = tr("WYE Turnout");
                break;
            case LayoutTurnout::TurnoutType::DOUBLE_XOVER:
                label = tr("Double Crossover");
                break;
            case LayoutTurnout::TurnoutType::RH_XOVER:
                label = tr("Right Crossover");
                break;
            case LayoutTurnout::TurnoutType::LH_XOVER:
                label = tr("Left Crossover");
                break;
            default:
                break;
        }
        QAction* jmi = popup->addAction(tr("%1:").arg(label) + getName());
        jmi->setEnabled(false);

        if (getTurnout() == nullptr) {
            jmi = popup->addSection(tr("No Turnout Set"));
        } else {
            QString stateString = getTurnoutStateString(getTurnout()->getKnownState());
            stateString = tr(" (%1)").arg(stateString);
            jmi = popup->addSection(tr("Turnout")
                    + ": " + getTurnoutName() + stateString);
        }
        jmi->setEnabled(false);

        if (getSecondTurnout() != nullptr) {
            QString stateString = getTurnoutStateString(getSecondTurnout()->getKnownState());
            stateString = tr(" (%1)").arg(stateString);
            jmi = popup->addSection(tr("Supporting %1:").arg(
                    tr("Turnout"))
                    + ": " + getSecondTurnoutName() + stateString);
        }
        jmi->setEnabled(false);

        if (getBlockName().isEmpty()) {
            jmi = popup->addSection(tr("No Block Set"));
            jmi->setEnabled(false);
        } else {
            jmi = popup->addSection(tr("%1:").arg(tr("Block")) + getLayoutBlock()->getDisplayName());
            jmi->setEnabled(false);
            if (isTurnoutTypeXover()) {
                // check if extra blocks have been entered
                if ((getLayoutBlockB() != nullptr) && (getLayoutBlockB() != getLayoutBlock())) {
                    jmi = popup->addSection(tr("%1:").arg(tr("Block %1").arg("B")) + getLayoutBlockB()->getDisplayName());
                    jmi->setEnabled(false);
                }
                if ((getLayoutBlockC() != nullptr) && (getLayoutBlockC() != getLayoutBlock())) {
                    jmi = popup->addSection(tr("%1:").arg(tr("Block %1").arg("C")) + getLayoutBlockC()->getDisplayName());
                    jmi->setEnabled(false);
                }
                if ((getLayoutBlockD() != nullptr) && (getLayoutBlockD() != getLayoutBlock())) {
                    jmi = popup->addSection(tr("%1:").arg(tr("Block %1").arg("D")) + getLayoutBlockD()->getDisplayName());
                    jmi->setEnabled(false);
                }
            }
        }

        // if there are any track connections
        QAction*act;
        if ((getConnectA() != nullptr) || (getConnectB() != nullptr)
                || (getConnectC() != nullptr) || (getConnectD() != nullptr)) {
            QMenu* connectionsMenu = new QMenu(tr("Connections")); // there is no pane opening (which is what ... implies)
            if (getConnectA() != nullptr) {
                connectionsMenu->addAction(act =new AbstractAction(tr("%1:").arg("A") + getConnectA()->getName(),this));
//                {
//                    @Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
                connect(act, &QAction::triggered, [=]{
                        LayoutEditorFindItems* lf = layoutEditor->getFinder();
                        LayoutTrack* lt = lf->findObjectByName(getConnectA()->getName());
                        // this shouldn't ever be null... however...
                        if (lt != nullptr) {
                            LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                            layoutEditor->setSelectionRect(ltv->getBounds());
                            ltv->showPopup();
                        }
//                    }
                });
            }

            if (getConnectB() != nullptr) {
                connectionsMenu->addAction(act =new AbstractAction(tr("%1:").arg("B") + getConnectB()->getName(),this));
//                {
//                    @Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
                connect(act, &QAction::triggered, [=]{
                        LayoutEditorFindItems* lf = layoutEditor->getFinder();
                        LayoutTrack* lt = lf->findObjectByName(getConnectB()->getName());
                        // this shouldn't ever be null... however...
                        if (lt != nullptr) {
                            LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                            layoutEditor->setSelectionRect(ltv->getBounds());
                            ltv->showPopup();
                        }
//                    }
                });
            }
            if (getConnectC() != nullptr) {
                connectionsMenu->addAction(act = new AbstractAction(tr("%1:").arg("C") + getConnectC()->getName(),this));
//                {
//                    @Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
                connect(act, &QAction::triggered, [=]{
                        LayoutEditorFindItems* lf = layoutEditor->getFinder();
                        LayoutTrack* lt = lf->findObjectByName(getConnectC()->getName());
                        // this shouldn't ever be null... however...
                        if (lt != nullptr) {
                            LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                            layoutEditor->setSelectionRect(ltv->getBounds());
                            ltv->showPopup();
                        }
//                    }
                });
            }
            if (getConnectD() != nullptr) {
                connectionsMenu->addAction(act =new AbstractAction(tr("%1:").arg("D") + getConnectD()->getName(),this));
//                {
//                    @Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
                connect(act, &QAction::triggered, [=]{
                        LayoutEditorFindItems* lf = layoutEditor->getFinder();
                        LayoutTrack* lt = lf->findObjectByName(getConnectD()->getName());
                        // this shouldn't ever be null... however...
                        if (lt != nullptr) {
                            LayoutTrackView* ltv = layoutEditor->getLayoutTrackView(lt);
                            layoutEditor->setSelectionRect(ltv->getBounds());
                            ltv->showPopup();
                        }
//                    }
                });
            }
            popup->addMenu(connectionsMenu);
        }
        popup->addSeparator();//new JSeparator(JSeparator.HORIZONTAL));

        JCheckBoxMenuItem* hiddenCheckBoxMenuItem = new JCheckBoxMenuItem(tr("Hidden"),this);
        hiddenCheckBoxMenuItem->setChecked(isHidden());
        popup->addAction(hiddenCheckBoxMenuItem);
//        hiddenCheckBoxMenuItem.addActionListener((java.awt.event.ActionEvent e1) -> {
        connect(hiddenCheckBoxMenuItem, &JCheckBoxMenuItem::triggered, [=]{
            //JCheckBoxMenuItem* o = (JCheckBoxMenuItem) e1.getSource();
            setHidden(hiddenCheckBoxMenuItem->isChecked());
        });

        JCheckBoxMenuItem* cbmi = new JCheckBoxMenuItem(tr("Disabled"),this);
        cbmi->setChecked(isDisabled());
        popup->addAction(cbmi);
//        cbmi.addActionListener((java.awt.event.ActionEvent e2) -> {
        connect(cbmi, &QAction::triggered, [=]{
//            JCheckBoxMenuItem o = (JCheckBoxMenuItem) e2.getSource();
            setDisabled(cbmi->isChecked());
        });

        cbmi = new JCheckBoxMenuItem(tr("Disable When Occupied"), this);
        if (getTurnout() == nullptr || getBlockName().isEmpty()) {
            cbmi->setEnabled(false);
        }
        cbmi->setChecked(isDisabledWhenOccupied());
        popup->addAction(cbmi);
//        cbmi.addActionListener((java.awt.event.ActionEvent e3) -> {
        connect(cbmi, &QAction::triggered, [=]{
//            JCheckBoxMenuItem o = (JCheckBoxMenuItem) e3.getSource();
            setDisableWhenOccupied(cbmi->isChecked());
        });
#if 1
        // Rotate if there are no track connections
//            if ((getConnectA() == nullptr) && (getConnectB() == nullptr)
//                    && (getConnectC() == nullptr)
//                    && (getConnectD() == nullptr))
        {
            QAction* rotateItem = new QAction(tr("Rotate (%1°)").arg(
                    getRotationDEG(),0,'g') + "...", this);
            popup->addAction(rotateItem);
//            rotateItem.addActionListener((ActionEvent event) -> {
            connect(rotateItem, &QAction::triggered, [=]{
                bool entering = true;
                bool error = false;
                QString newAngle = "";
                while (entering) {
                    // prompt for rotation angle
                    error = false;
                    newAngle = JOptionPane::showInputDialog(layoutEditor,
                            tr("%1:").arg(("Enter Rotation Angle (degrees CW)")));
                    if (newAngle.isEmpty()) {
                        return;  // cancelled
                    }
                    double rot = 0.0;
                    bool ok;
                        rot = newAngle.toDouble(&ok);
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
            });
        }
#endif
        popup->addAction(act =new AbstractAction(tr("UseSizeAsDefault"), this));
//        {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(act, &QAction::triggered, [=]{
                setUpDefaultSize();
//            }
        });

        popup->addAction(act =new AbstractAction(tr("Edit"), this));
//        {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(act, &QAction::triggered, [=]{
                editor->editLayoutTrack(this);
//            }
        });
        popup->addAction(act =new AbstractAction(tr("Delete"), this));
//        {
//            @Override
//            /*public*/ void actionPerformed(ActionEvent e) {
        connect(act, &QAction::triggered, [=]{
                if (canRemove() && layoutEditor->removeLayoutTurnout(turnout)) {
                    // Returned true if user did not cancel
                    remove();
                    dispose();
                }
//            }
        });

        if (getTurnout() != nullptr) {
            AbstractAction* ssaa = new AbstractAction(tr("Set Signals..."),this);
//            {
//                @Override
//                /*public*/ void actionPerformed(ActionEvent e) {
            connect(ssaa, &QAction::triggered, [=]{
                    LayoutEditorTools* tools = layoutEditor->getLETools();
                    LayoutEditorToolBarPanel* letbp = getLayoutEditorToolBarPanel();
                    if (isTurnoutTypeXover()) {
                        tools->setSignalsAtXoverTurnoutFromMenu(turnout,
                                letbp->signalIconEditor, letbp->signalFrame);
                    } else if (linkType == LayoutTurnout::LinkType::NO_LINK) {
                        tools->setSignalsAtTurnoutFromMenu(turnout,
                                letbp->signalIconEditor, letbp->signalFrame);
                    } else if (linkType == LayoutTurnout::LinkType::THROAT_TO_THROAT) {
                        tools->setSignalsAtThroatToThroatTurnoutsFromMenu(turnout, linkedTurnoutName,
                                letbp->signalIconEditor, letbp->signalFrame);
                    } else if (linkType == LayoutTurnout::LinkType::FIRST_3_WAY) {
                        tools->setSignalsAt3WayTurnoutFromMenu(getTurnoutName(), linkedTurnoutName,
                                letbp->signalIconEditor, letbp->signalFrame);
                    } else if (linkType == LayoutTurnout::LinkType::SECOND_3_WAY) {
                        tools->setSignalsAt3WayTurnoutFromMenu(linkedTurnoutName, getTurnoutName(),
                                letbp->signalIconEditor, letbp->signalFrame);
                    }
//                }
            });

            QMenu* jm = new QMenu(tr("Signal Heads"));
            if (layoutEditor->getLETools()->addLayoutTurnoutSignalHeadInfoToMenu(
                    getTurnoutName(), linkedTurnoutName, jm)) {
                jm->addAction(ssaa);
                popup->addMenu(jm);
            } else {
                popup->addAction(ssaa);
            }
        }

        if (!getBlockName().isEmpty()) {
            /*final*/ QStringList boundaryBetween = getBlockBoundaries();
            bool blockBoundaries = false;
            for (int i = 0; i < 4; i++) {
                if (boundaryBetween[i] != nullptr) {
                    blockBoundaries = true;

                }
            }

            if (blockBoundaries) {
                popup->addAction(act = new AbstractAction(tr("Set Signal Masts..."),this));
//                {
//                    @Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
                connect(act, &QAction::triggered, [=]{
                        layoutEditor->getLETools()->setSignalMastsAtTurnoutFromMenu(turnout,
                                boundaryBetween);
//                    }
                });
                popup->addAction(act = new AbstractAction(tr("Set Sensors..."), this));
//                {
//                    @Override
//                    /*public*/ void actionPerformed(ActionEvent e) {
                connect(act, &QAction::triggered, [=]{
                        LayoutEditorToolBarPanel* letbp = getLayoutEditorToolBarPanel();
                        layoutEditor->getLETools()->setSensorsAtTurnoutFromMenu(
                                turnout,
                                boundaryBetween,
                                letbp->sensorIconEditor,
                                letbp->sensorFrame);
//                    }
                });

            }

            if (((LayoutBlockManager*)InstanceManager::getDefault("LayoutBlockManager"
            ))->isAdvancedRoutingEnabled()) {
                QMap<QString, LayoutBlock*> map = QMap<QString, LayoutBlock*>();
                if (!getBlockName().isEmpty()) {
                    map.insert(getBlockName(), getLayoutBlock());
                }
                if (!getBlockBName().isEmpty()) {
                    map.insert(getBlockBName(), getLayoutBlockB());
                }
                if (!getBlockCName().isEmpty()) {
                    map.insert(getBlockCName(), getLayoutBlockC());
                }
                if (!getBlockDName().isEmpty()) {
                    map.insert(getBlockDName(), getLayoutBlockD());
                }
                if (blockBoundaries) {
                    if (map.size() == 1) {
                        popup->addAction(act =new AbstractAction(tr("View Block Routing"),this));
//                        {
//                            @Override
//                            /*public*/ void actionPerformed(ActionEvent e) {
                        connect(act, &QAction::triggered, [=]{
                                AbstractAction* routeTableAction = new LayoutBlockRouteTableAction("ViewRouting", getLayoutBlock());
                                routeTableAction->actionPerformed(/*e*/);
//                            }
                        });
                    } else if (map.size() > 1) {
                        QMenu* viewRouting = new QMenu(tr("View Block Routing"));
//                        for (Map.Entry<String, LayoutBlock> entry : map.entrySet())
                        QMapIterator<QString, LayoutBlock*> entry(map);
                        while(entry.hasNext())
                        {
                         entry.next();
                            QString blockName = entry.key();
                            LayoutBlock* layoutBlock = entry.value();
                            viewRouting->addAction(act = new AbstractActionImpl(blockName, getBlockBName(), layoutBlock, this));
                        }
                        popup->addMenu(viewRouting);
                    }
                }   // if (blockBoundaries)
            }   // .isAdvancedRoutingEnabled()
        }   // getBlockName().isEmpty()
        setAdditionalEditPopUpMenu(popup);
        layoutEditor->setShowAlignmentMenu(popup);
        //popup->show(mouseEvent.getComponent(), mouseEvent.x(), mouseEvent.y());
        popup->exec(QCursor::pos());
    } else if (!viewAdditionalMenu.isEmpty()) {
        setAdditionalViewPopUpMenu(popup);
        //popup->show(mouseEvent.getComponent(), mouseEvent.x(), mouseEvent.y());
        popup->exec(QCursor::pos());

    }

    return popup;
} // showPopup

/*public*/ QList<QString> LayoutTurnoutView::getBlockBoundaries() {
    return turnout->getBlockBoundaries();
}

/*public*/ QList<LayoutBlock*> LayoutTurnoutView::getProtectedBlocks(NamedBean* bean) {
    return turnout->getProtectedBlocks(bean);
}

/*protected*/ void LayoutTurnoutView::removeSML(SignalMast* signalMast) {
    turnout->removeSML(signalMast);
}

/**
 * Clean up when this object is no longer needed. Should not be called while
 * the object is still displayed; see {@link #remove()}
 */
/*public*/ void LayoutTurnoutView::dispose() {
    if (popup != nullptr) {
        popup->clear();
    }
    popup = nullptr;
}

/**
 * Remove this object from display and persistance.
 */
/*public*/ void LayoutTurnoutView::remove() {
    turnout->remove();
}

/**
 * "active" means that the object is still displayed, and should be stored.
 *
 * @return true if active
 */
/*public*/ bool LayoutTurnoutView::isActive() {
    return turnout->isActive();
}

/*public*/ void LayoutTurnoutView::addEditPopUpMenu(QAction* menu) {
    if (!editAdditionalMenu.contains(menu)) {
        editAdditionalMenu.append(menu);
    }
}

/*public*/ void LayoutTurnoutView::addViewPopUpMenu(QAction* menu) {
    if (!viewAdditionalMenu.contains(menu)) {
        viewAdditionalMenu.append(menu);
    }
}

/*public*/ void LayoutTurnoutView::setAdditionalEditPopUpMenu(QMenu* popup) {
    if (editAdditionalMenu.isEmpty()) {
        return;
    }
    popup->addSeparator();
    for (QAction* mi : editAdditionalMenu) {
        popup->addAction(mi);
    }
}

/*public*/ void LayoutTurnoutView::setAdditionalViewPopUpMenu(QMenu* popup) {
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
 * <p>
 * This type of track has none, so this method is empty.
 */
//@Override
/*protected*/ void LayoutTurnoutView::drawDecorations(EditScene* g2) {
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnoutView::draw1(EditScene* g2, bool isMain, bool isBlock) {
    if (isBlock && getLayoutBlock() == nullptr) {
        // Skip the block layer if there is no block assigned.
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

    //Color color = g2.getColor();
    QColor color = layoutEditor->drawingStroke.color();

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

     // middles
     QPointF pM = getCoordsCenter();
     QPointF pABM = MathUtil::midPoint(pA, pB);
     QPointF pAM = MathUtil::lerp(pA, pABM, 5.0 / 8.0);
     QPointF pAMP = MathUtil::midPoint(pAM, pABM);
     QPointF pBM = MathUtil::lerp(pB, pABM, 5.0 / 8.0);
     QPointF pBMP = MathUtil::midPoint(pBM, pABM);

     QPointF pCDM = MathUtil::midPoint(pC, pD);
     QPointF pCM = MathUtil::lerp(pC, pCDM, 5.0 / 8.0);
     QPointF pCMP = MathUtil::midPoint(pCM, pCDM);
     QPointF pDM = MathUtil::lerp(pD, pCDM, 5.0 / 8.0);
     QPointF pDMP = MathUtil::midPoint(pDM, pCDM);

     QPointF pAF = MathUtil::midPoint(pAM, pM);
     QPointF pBF = MathUtil::midPoint(pBM, pM);
     QPointF pCF = MathUtil::midPoint(pCM, pM);
     QPointF pDF = MathUtil::midPoint(pDM, pM);

     int state = UNKNOWN;
     if (layoutEditor->isAnimating()) {
      state = getState();
     }

     if(log->isDebugEnabled())
      log->debug(tr("draw1 turnout %1 isMain = %2, state = %3").arg(getTurnoutName()).arg(isMain?"true":"false").arg(getTurnoutStateString(getState())));

     LayoutTurnout::TurnoutType toType = getTurnoutType();

     QGraphicsLineItem* lineItem;

     itemGroup = getLayoutTurnout()->invalidateItem(g2,itemGroup);
     if(itemGroup == nullptr)
     {
      itemGroup = new QGraphicsItemGroup();
      itemGroup->setZValue(Editor::HANDLES+1);
     }
     g2->addItem(itemGroup);

     if (toType == LayoutTurnout::TurnoutType::DOUBLE_XOVER)
     {
      if (state != Turnout::THROWN && state != Turnout::INCONSISTENT)
      { // unknown or continuing path - not crossed over
       if (isMain == mainlineA) {
           //g2.setColor(colorA);
        layoutEditor->drawingStroke.setColor(colorA);
           //g2.draw(new Line2D.Double(pA, pABM));
        lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pABM.x(), pABM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg)
        {
           // g2.draw(new Line2D.Double(pAF, pM));
         lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
       if (isMain == mainlineB)
       {
           //g2.setColor(colorB);
        layoutEditor->drawingStroke.setColor(colorB);
    //             g2.draw(new Line2D.Double(pB, pABM));
        lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pABM.x(), pABM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg) {
            //g2.draw(new Line2D.Double(pBF, pM));
         lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
       if (isMain == mainlineC)
       {
           //g2.setColor(colorC);
        layoutEditor->drawingStroke.setColor(colorC);
           //g2.draw(new Line2D.Double(pC, pCDM));
        lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCDM.x(), pCDM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg)
        {
         //g2.draw(new Line2D.Double(pCF, pM));
         lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
       if (isMain == mainlineD)
       {
        //g2.setColor(colorD);
        layoutEditor->drawingStroke.setColor(colorD);
        //g2.draw(new Line2D.Double(pD, pCDM));
        lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pCDM.x(), pCDM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg)
        {
               //g2.draw(new Line2D.Double(pDF, pM));
         lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
      }
      if (state != Turnout::CLOSED && state != Turnout::INCONSISTENT)
      { // unknown or diverting path - crossed over
       if (isMain == mainlineA)
       {
        //g2.setColor(colorA);
        layoutEditor->drawingStroke.setColor(colorA);
        //g2.draw(new Line2D.Double(pA, pAM));
        lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        //g2.draw(new Line2D.Double(pAM, pM));
        lineItem = new QGraphicsLineItem(pAM.x(), pAM.y(), pM.x(), pM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg) {
            //g2.draw(new Line2D.Double(pAMP, pABM));
         lineItem = new QGraphicsLineItem(pAMP.x(), pAMP.y(), pABM.x(), pABM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
       if (isMain == mainlineB) {
           //g2.setColor(colorB);
        layoutEditor->drawingStroke.setColor(colorB);
        //g2.draw(new Line2D.Double(pB, pBM));
        lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pBM.x(), pBM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        //g2.draw(new Line2D.Double(pBM, pM));
        lineItem = new QGraphicsLineItem(pBM.x(), pBM.y(), pM.x(), pM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg)
        {
         //g2.draw(new Line2D.Double(pBMP, pABM));
         lineItem = new QGraphicsLineItem(pBMP.x(), pBMP.y(), pABM.x(), pABM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
       if (isMain == mainlineC)
       {
        //g2.setColor(colorC);
        layoutEditor->drawingStroke.setColor(colorC);
        //g2.draw(new Line2D.Double(pC, pCM));
        lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        //g2.draw(new Line2D.Double(pCM, pM));
         lineItem = new QGraphicsLineItem(pCM.x(), pCM.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg) {
            //g2.draw(new Line2D.Double(pCMP, pCDM));
         lineItem = new QGraphicsLineItem(pCMP.x(), pCMP.y(), pCDM.x(), pCDM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
       if (isMain == mainlineD)
       {
           //g2.setColor(colorD);
        layoutEditor->drawingStroke.setColor(colorD);
           //g2.draw(new Line2D.Double(pD, pDM));
        lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pDM.x(), pDM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
           //g2.draw(new Line2D.Double(pDM, pM));
        lineItem = new QGraphicsLineItem(pDM.x(), pDM.y(), pM.x(), pM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
        if (!isBlock || drawUnselectedLeg)
        {
         //g2.draw(new Line2D.Double(pDMP, pCDM));
         lineItem = new QGraphicsLineItem(pDMP.x(), pDMP.y(), pCDM.x(), pCDM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
      }
      if (state == Turnout::INCONSISTENT)
      {
       if (isMain == mainlineA)
       {
           //g2.setColor(colorA);
        layoutEditor->drawingStroke.setColor(colorA);
           //g2.draw(new Line2D.Double(pA, pAM));
        lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);

       }
       if (isMain == mainlineB) {
           //g2.setColor(colorB);
        layoutEditor->drawingStroke.setColor(colorB);
    //      g2.draw(new Line2D.Double(pB, pBM));
        lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pBM.x(), pBM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
       }
       if (isMain == mainlineC) {
           //g2.setColor(colorC);
        layoutEditor->drawingStroke.setColor(colorC);
           //g2.draw(new Line2D.Double(pC, pCM));
        lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
       }
       if (isMain == mainlineD) {
           //g2.setColor(colorD);
        layoutEditor->drawingStroke.setColor(colorD);
           //g2.draw(new Line2D.Double(pD, pDM));
        lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pDM.x(), pDM.y());
        lineItem->setPen(layoutEditor->drawingStroke);
        itemGroup->addToGroup(lineItem);
       }
       if (!isBlock || drawUnselectedLeg)
       {
        if (isMain == mainlineA)
        {
    //           g2.setColor(colorA);
         layoutEditor->drawingStroke.setColor(colorA);
            //g2.draw(new Line2D.Double(pAF, pM));
         lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
        if (isMain == mainlineC) {
            //g2.setColor(colorC);
         layoutEditor->drawingStroke.setColor(colorC);
            //g2.draw(new Line2D.Double(pCF, pM));
         lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
        if (isMain == mainlineB) {
            //g2.setColor(colorB);
         layoutEditor->drawingStroke.setColor(colorB);
            //g2.draw(new Line2D.Double(pBF, pM));
         lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
        if (isMain == mainlineD) {
            //g2.setColor(colorD);
         layoutEditor->drawingStroke.setColor(colorD);
            //g2.draw(new Line2D.Double(pDF, pM));
         lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
         lineItem->setPen(layoutEditor->drawingStroke);
         itemGroup->addToGroup(lineItem);
        }
       }
      }
     }
     else if ((toType == LayoutTurnout::TurnoutType::RH_XOVER)
          || (toType == LayoutTurnout::TurnoutType::LH_XOVER))
     {    // draw (rh & lh) cross overs
      pAF = MathUtil::midPoint(pABM, pM);
      pBF = MathUtil::midPoint(pABM, pM);
      pCF = MathUtil::midPoint(pCDM, pM);
      pDF = MathUtil::midPoint(pCDM, pM);
      if (state != Turnout::THROWN && state != Turnout::INCONSISTENT)
      { // unknown or continuing path - not crossed over
             if (isMain == mainlineA) {
                 //g2.setColor(colorA);
              layoutEditor->drawingStroke.setColor(colorA);
                 //g2.draw(new Line2D.Double(pA, pABM));
              lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pABM.x(), pABM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineB) {
    //             g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
    //             g2.draw(new Line2D.Double(pABM, pB));
              lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(pC, pCDM));
              lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCDM.x(), pCDM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineD) {
                 //g2.setColor(colorD);
              layoutEditor->drawingStroke.setColor(colorD);
                 //g2.draw(new Line2D.Double(pCDM, pD));
              lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (!isBlock || drawUnselectedLeg) {
                 if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
                     if (isMain == mainlineA) {
                         //g2.setColor(colorA);
                      layoutEditor->drawingStroke.setColor(colorA);
                         //g2.draw(new Line2D.Double(pAF, pM));
                      lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                     if (isMain == mainlineC) {
                         //g2.setColor(colorC);
                      layoutEditor->drawingStroke.setColor(colorC);
                         //g2.draw(new Line2D.Double(pCF, pM));
                      lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                 } else if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
                     if (isMain == mainlineB) {
                         //g2.setColor(colorB);
                      layoutEditor->drawingStroke.setColor(colorB);
                         //g2.draw(new Line2D.Double(pBF, pM));
                      lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                     if (isMain == mainlineD) {
                         //g2.setColor(colorD);
                      layoutEditor->drawingStroke.setColor(colorD);
                         //g2.draw(new Line2D.Double(pDF, pM));
                      lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                 }
             }
         }
         if (state != Turnout::CLOSED && state != Turnout::INCONSISTENT) { // unknown or diverting path - crossed over
             if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
                 if (isMain == mainlineA) {
                     //g2.setColor(colorA);
                  layoutEditor->drawingStroke.setColor(colorA);
                     //g2.draw(new Line2D.Double(pA, pABM));
                  lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pABM.x(), pABM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                    //;g2.draw(new Line2D.Double(pABM, pM));
                    lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
                    lineItem->setPen(layoutEditor->drawingStroke);
                    itemGroup->addToGroup(lineItem);
                 }
                 if (!isBlock || drawUnselectedLeg) {
                     if (isMain == mainlineB) {
                         //g2.setColor(colorB);
                      layoutEditor->drawingStroke.setColor(colorB);
                         //g2.draw(new Line2D.Double(pBM, pB));
                      lineItem = new QGraphicsLineItem(pBM.x(), pBM.y(), pB.x(), pB.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                 }
                 if (isMain == mainlineC) {
                     //g2.setColor(colorC);
                  layoutEditor->drawingStroke.setColor(colorC);
                     //g2.draw(new Line2D.Double(pC, pCDM));
                  lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCDM.x(), pCDM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                  //g2.draw(new Line2D.Double(pCDM, pM));
                  lineItem = new QGraphicsLineItem(pCDM.x(), pCDM.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
                 if (!isBlock || drawUnselectedLeg) {
                     if (isMain == mainlineD) {
                         //g2.setColor(colorD);
                      layoutEditor->drawingStroke.setColor(colorD);
                         //g2.draw(new Line2D.Double(pDM, pD));
                      lineItem = new QGraphicsLineItem(pDM.x(), pDM.y(), pD.x(), pD.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                 }
             } else if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
                 if (!isBlock || drawUnselectedLeg) {
                     if (isMain == mainlineA) {
                         //g2.setColor(colorA);
                      layoutEditor->drawingStroke.setColor(colorA);
                         //g2.draw(new Line2D.Double(pA, pAM));
                      lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                 }
                 if (isMain == mainlineB) {
                     //g2.setColor(colorB);
                  layoutEditor->drawingStroke.setColor(colorB);
                     //g2.draw(new Line2D.Double(pB, pABM));
                  lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pABM.x(), pABM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                  //g2.draw(new Line2D.Double(pABM, pM));
                  lineItem = new QGraphicsLineItem(pABM.x(), pABM.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);}
                 if (!isBlock || drawUnselectedLeg) {
                     if (isMain == mainlineC) {
                         //g2.setColor(colorC);
                      layoutEditor->drawingStroke.setColor(colorC);
                         //g2.draw(new Line2D.Double(pC, pCM));
                      lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);}
                 }
                 if (isMain == mainlineD) {
                     //g2.setColor(colorD);
                  layoutEditor->drawingStroke.setColor(colorD);
                     //g2.draw(new Line2D.Double(pD, pCDM));
                  lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pCDM.x(), pCDM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                  //g2.draw(new Line2D.Double(pCDM, pM));
                  lineItem = new QGraphicsLineItem(pCDM.x(), pCDM.y(), pM.x(), pM.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);}
             }
         }
         if (state == Turnout::INCONSISTENT) {
             if (isMain == mainlineA) {
                 //g2.setColor(colorA);
              layoutEditor->drawingStroke.setColor(colorA);
                 //g2.draw(new Line2D.Double(pA, pAM));
              lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pAM.x(), pAM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(pB, pBM));
              lineItem = new QGraphicsLineItem(pB.x(), pB.y(), pBM.x(), pBM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(pC, pCM));
              lineItem = new QGraphicsLineItem(pC.x(), pC.y(), pCM.x(), pCM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineD) {
                 //g2.setColor(colorD);
              layoutEditor->drawingStroke.setColor(colorD);
                 //g2.draw(new Line2D.Double(pD, pDM));
              lineItem = new QGraphicsLineItem(pD.x(), pD.y(), pDM.x(), pDM.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (!isBlock || drawUnselectedLeg) {
                 if (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER) {
                     if (isMain == mainlineA) {
                         //g2.setColor(colorA);
                      layoutEditor->drawingStroke.setColor(colorA);
                         //g2.draw(new Line2D.Double(pAF, pM));
                      lineItem = new QGraphicsLineItem(pAF.x(), pAF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                     if (isMain == mainlineC) {
                         //g2.setColor(colorC);
                      layoutEditor->drawingStroke.setColor(colorC);
                         //g2.draw(new Line2D.Double(pCF, pM));
                      lineItem = new QGraphicsLineItem(pCF.x(), pCF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                 } else if (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER) {
                     if (isMain == mainlineB) {
                         //g2.setColor(colorB);
                      layoutEditor->drawingStroke.setColor(colorB);
                         //g2.draw(new Line2D.Double(pBF, pM));
                      lineItem = new QGraphicsLineItem(pBF.x(), pBF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                     if (isMain == mainlineD) {
                         //g2.setColor(colorD);
                      layoutEditor->drawingStroke.setColor(colorD);
                         //g2.draw(new Line2D.Double(pDF, pM));
                      lineItem = new QGraphicsLineItem(pDF.x(), pDF.y(), pM.x(), pM.y());
                      lineItem->setPen(layoutEditor->drawingStroke);
                      itemGroup->addToGroup(lineItem);
                     }
                 }
             }
         }
     }
     else if ((toType == LayoutTurnout::TurnoutType::SINGLE_SLIP) || (toType == LayoutTurnout::TurnoutType::DOUBLE_SLIP)) {
         log->error("slips should be being drawn by LayoutSlip sub-class");
     }
     else {    // LH, RH, or WYE Turnouts
         // draw A<===>center
         if (isMain == mainlineA) {
             //g2.setColor(colorA);
          layoutEditor->drawingStroke.setColor(colorA);
             //g2.draw(new Line2D.Double(pA, pM));
          lineItem = new QGraphicsLineItem(pA.x(), pA.y(), pM.x(), pM.y());
          lineItem->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(lineItem);
         }

         if (state == UNKNOWN || (continuingSense == state && state != Turnout::INCONSISTENT))
         { // unknown or continuing path
             // draw center<===>B
             if (isMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(pM, pB));
              lineItem = new QGraphicsLineItem(pM.x(), pM.y(), pB.x(), pB.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         } else if (!isBlock || drawUnselectedLeg) {
             // draw center<--=>B
             if (isMain == mainlineB) {
                 //g2.setColor(colorB);
              layoutEditor->drawingStroke.setColor(colorB);
                 //g2.draw(new Line2D.Double(MathUtil::twoThirdsPoint(pM, pB), pB));
              lineItem = new QGraphicsLineItem(MathUtil::twoThirdsPoint(pM, pB).x(), MathUtil::twoThirdsPoint(pM, pB).y(), pB.x(), pB.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }

         if (state == UNKNOWN || (continuingSense != state && state != Turnout::INCONSISTENT))
         { // unknown or diverting path
             // draw center<===>C
             if (isMain == mainlineC)
             {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(pM, pC));
              lineItem = new QGraphicsLineItem(pM.x(), pM.y(), pC.x(), pC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         } else if (!isBlock || drawUnselectedLeg) {
             // draw center<--=>C
             if (isMain == mainlineC) {
                 //g2.setColor(colorC);
              layoutEditor->drawingStroke.setColor(colorC);
                 //g2.draw(new Line2D.Double(MathUtil::twoThirdsPoint(pM, pC), pC));
              lineItem = new QGraphicsLineItem(MathUtil::twoThirdsPoint(pM, pC).x(), MathUtil::twoThirdsPoint(pM, pC).y(), pC.x(), pC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
         }
     }
}   // draw1

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnoutView::draw2(EditScene* g2, bool isMain, float railDisplacement) {
     int toType = getTurnoutType();

     QPointF pA = getCoordsA();
     QPointF pB = getCoordsB();
     QPointF pC = getCoordsC();
     QPointF pD = getCoordsD();
     QPointF pM = getCoordsCenter();

     QPointF vAM = MathUtil::normalize(MathUtil::subtract(pM, pA));
     QPointF vAMo = MathUtil::orthogonal(MathUtil::normalize(vAM, railDisplacement));

     QPointF pAL = MathUtil::subtract(pA, vAMo);
     QPointF pAR = MathUtil::add(pA, vAMo);

     QPointF vBM = MathUtil::normalize(MathUtil::subtract(pB, pM));
     double dirBM_DEG = MathUtil::computeAngleDEG(vBM);
     QPointF vBMo = MathUtil::normalize(MathUtil::orthogonal(vBM), railDisplacement);
     QPointF pBL = MathUtil::subtract(pB, vBMo);
     QPointF pBR = MathUtil::add(pB, vBMo);
     QPointF pMR = MathUtil::add(pM, vBMo);

     QPointF vCM = MathUtil::normalize(MathUtil::subtract(pC, pM));
     double dirCM_DEG = MathUtil::computeAngleDEG(vCM);

     QPointF vCMo = MathUtil::normalize(MathUtil::orthogonal(vCM), railDisplacement);
     QPointF pCL = MathUtil::subtract(pC, vCMo);
     QPointF pCR = MathUtil::add(pC, vCMo);
     QPointF pML = MathUtil::subtract(pM, vBMo);

     double deltaBMC_DEG = MathUtil::absDiffAngleDEG(dirBM_DEG, dirCM_DEG);
     double deltaBMC_RAD = qDegreesToRadians(deltaBMC_DEG);

     double hypotF = railDisplacement / qSin(deltaBMC_RAD / 2.0);

     QPointF vDisF = MathUtil::normalize(MathUtil::add(vAM, vCM), hypotF);
     if (toType == LayoutTurnout::TurnoutType::WYE_TURNOUT) {
         vDisF = MathUtil::normalize(vAM, hypotF);
     }
     QPointF pF = MathUtil::add(pM, vDisF);

     QPointF pFR = MathUtil::add(pF, MathUtil::multiply(vBMo, 2.0));
     QPointF pFL = MathUtil::subtract(pF, MathUtil::multiply(vCMo, 2.0));

     // QPointF pFPR = MathUtil::add(pF, MathUtil::normalize(vBMo, 2.0));
     // QPointF pFPL = MathUtil::subtract(pF, MathUtil::normalize(vCMo, 2.0));
     QPointF vDisAP = MathUtil::normalize(vAM, hypotF);
     QPointF pAP = MathUtil::subtract(pM, vDisAP);
     QPointF pAPR = MathUtil::add(pAP, vAMo);
     QPointF pAPL = MathUtil::subtract(pAP, vAMo);

     // QPointF vSo = MathUtil::normalize(vAMo, 2.0);
     // QPointF pSL = MathUtil::add(pAPL, vSo);
     // QPointF pSR = MathUtil::subtract(pAPR, vSo);

     bool mainlineA = isMainlineA();
     bool mainlineB = isMainlineB();
     bool mainlineC = isMainlineC();
     bool mainlineD = isMainlineD();

     int state = UNKNOWN;
     if (layoutEditor->isAnimating()) {
          Turnout* to = getTurnout();
         if (to != nullptr) {
             state = to->getKnownState();
         }
     }

     //if(!isMain && itemGroup)
      itemGroup = invalidateItem(g2,itemGroup);
     if(itemGroup == nullptr)
     {
      itemGroup = new QGraphicsItemGroup();
      itemGroup->setZValue(Editor::HANDLES+1);
      g2->addItem(itemGroup);
     }

     QGraphicsLineItem* lineItem;
     switch (toType) {
         case LayoutTurnout::TurnoutType::RH_TURNOUT: {
             if (isMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pAL, pML));
              lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pML.x(), pML.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 //g2.draw(new Line2D.Double(pAR, pAPR));
              lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pAPR.x(), pAPR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineB) {
                 //g2.draw(new Line2D.Double(pML, pBL));
              lineItem = new QGraphicsLineItem(pML.x(), pML.y(), pBL.x(), pBL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 //g2.draw(new Line2D.Double(pF, pBR));
              lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pBR.x(), pBR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);

                 if (continuingSense == state)
                 {  // unknown or diverting path
 //                         g2.draw(new Line2D.Double(pSR, pFPR));
 //                     } else {
                     //g2.draw(new Line2D.Double(pAPR, pF));
                  lineItem = new QGraphicsLineItem(pAPR.x(), pAPR.y(), pF.x(), pF.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }
             if (isMain == mainlineC) {
                 //g2.draw(new Line2D.Double(pF, pCL));
              lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pCL.x(), pCL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 //g2.draw(new Line2D.Double(pFR, pCR));
              lineItem = new QGraphicsLineItem(pFR.x(), pFR.y(), pCR.x(), pCR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);

                 QPainterPath* path = new QPainterPath();
                 path->moveTo(pAPR.x(), pAPR.y());
                 path->quadTo(pMR.x(), pMR.y(), pFR.x(), pFR.y());
                 path->lineTo(pCR.x(), pCR.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(*path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 if (continuingSense != state) {  // unknown or diverting path
                     path = new QPainterPath();
                     path->moveTo(pAPL.x(), pAPL.y());
                     path->quadTo(pML.x(), pML.y(), pF.x(), pF.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(*path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);//                     } else {
 //                         path = new QPainterPath();
 //                         path.moveTo(pSL.x(), pSL.y());
 //                         path.quadTo(pML.x(), pML.y(), pFPL.x(), pFPL.y());
 //                         g2.draw(path);
                 }
             }
             break;
         }   // case RH_TURNOUT

         case LayoutTurnout::TurnoutType::LH_TURNOUT: {
             if (isMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pAR, pMR));
              lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pMR.x(), pMR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 //g2.draw(new Line2D.Double(pAL, pAPL));
              lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pAPL.x(), pAPL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
             }
             if (isMain == mainlineB) {
                 //g2.draw(new Line2D.Double(pMR, pBR));
              lineItem = new QGraphicsLineItem(pMR.x(), pMR.y(), pBR.x(), pBR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 //g2.draw(new Line2D.Double(pF, pBL));
              lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pBL.x(), pBL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 if (continuingSense == state) {  // straight path
 //                         g2.draw(new Line2D.Double(pSL, pFPL));  Offset problem
 //                     } else {
                     //g2.draw(new Line2D.Double(pAPL, pF));
                  lineItem = new QGraphicsLineItem(pAPL.x(), pAPL.y(), pF.x(), pF.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                 }
             }
             if (isMain == mainlineC) {
                 //g2.draw(new Line2D.Double(pF, pCR));
              lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pCR.x(), pCR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                 QPainterPath path = QPainterPath();
                 path.moveTo(pAPL.x(), pAPL.y());
                 path.quadTo(pML.x(), pML.y(), pFL.x(), pFL.y());
                 path.lineTo(pCL.x(), pCL.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 //                     } else {
                 if (continuingSense != state) {  // unknown or diverting path
                     path =  QPainterPath();
                     path.moveTo(pAPR.x(), pAPR.y());
                     path.quadTo(pMR.x(), pMR.y(), pF.x(), pF.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);
 //                     } else {
 //                     } else {
 //                         path = new QPainterPath();
 //                         path.moveTo(pSR.x(), pSR.y());
 //                         path.quadTo(pMR.x(), pMR.y(), pFPR.x(), pFPR.y());
 //                         g2.draw(path);
                 }
             }
             break;
         }   // case LH_TURNOUT
         case LayoutTurnout::TurnoutType::WYE_TURNOUT: {
             if (isMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pAL, pAPL));
              lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pAPL.x(), pAPL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pAR, pAPR));
              lineItem = new QGraphicsLineItem(pAR.x(), pAR.y(), pAPR.x(), pAPR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);}
             if (isMain == mainlineB) {
                 //g2.draw(new Line2D.Double(pF, pBL));
              lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pBL.x(), pBL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              QPainterPath path = QPainterPath();
                 path.moveTo(pAPR.x(), pAPR.y());
                 path.quadTo(pMR.x(), pMR.y(), pFR.x(), pFR.x());
                 path.lineTo(pBR.x(), pBR.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 if (continuingSense != state) {  // unknown or diverting path
                     path = QPainterPath();
                     path.moveTo(pAPR.x(), pAPR.y());
                     path.quadTo(pMR.x(), pMR.y(), pF.x(), pF.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);
                     //                     } else {
 //                         path = new QPainterPath();
 //                         path.moveTo(pSR.x(), pSR.y());
 //                         path.quadTo(pMR.x(), pMR.y(), pFPR.x(), pFPR.y());
 //     bad                    g2.draw(path);
                 }
             }
             if (isMain == mainlineC) {
                 pML = MathUtil::subtract(pM, vCMo);
                 QPainterPath path = QPainterPath();
                 path.moveTo(pAPL.x(), pAPL.y());
                 path.quadTo(pML.x(), pML.y(), pFL.x(), pFL.y());
                 path.lineTo(pCL.x(), pCL.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 //g2.draw(new Line2D.Double(pF, pCR));
                 lineItem = new QGraphicsLineItem(pF.x(), pF.y(), pCR.x(), pCR.y());
                 lineItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(lineItem);
                 if (continuingSense != state) {  // unknown or diverting path
 //                         path = new QPainterPath();
 //                         path.moveTo(pSL.x(), pSL.y());
 //                         path.quadTo(pML.x(), pML.y(), pFPL.x(), pFPL.y());
 //           bad              g2.draw(path);
                 } else {
                     path = QPainterPath();
                     path.moveTo(pAPL.x(), pAPL.y());
                     path.quadTo(pML.x(), pML.y(), pF.x(), pF.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);}
             }
             break;
         }   // case WYE_TURNOUT

         case LayoutTurnout::TurnoutType::DOUBLE_XOVER: {
             // A, B, C, D end points (left and right)
             QPointF vAB = MathUtil::normalize(MathUtil::subtract(pB, pA), railDisplacement);
             double dirAB_DEG = MathUtil::computeAngleDEG(vAB);
             QPointF vABo = MathUtil::orthogonal(MathUtil::normalize(vAB, railDisplacement));
             pAL = MathUtil::subtract(pA, vABo);
             pAR = MathUtil::add(pA, vABo);
             pBL = MathUtil::subtract(pB, vABo);
             pBR = MathUtil::add(pB, vABo);
             QPointF vCD = MathUtil::normalize(MathUtil::subtract(pD, pC), railDisplacement);
             QPointF vCDo = MathUtil::orthogonal(MathUtil::normalize(vCD, railDisplacement));
             pCL = MathUtil::add(pC, vCDo);
             pCR = MathUtil::subtract(pC, vCDo);
             QPointF pDL = MathUtil::add(pD, vCDo);
             QPointF pDR = MathUtil::subtract(pD, vCDo);

             // AB, CD mid points (left and right)
             QPointF pABM = MathUtil::midPoint(pA, pB);
             QPointF pABL = MathUtil::midPoint(pAL, pBL);
             QPointF pABR = MathUtil::midPoint(pAR, pBR);
             QPointF pCDM = MathUtil::midPoint(pC, pD);
             QPointF pCDL = MathUtil::midPoint(pCL, pDL);
             QPointF pCDR = MathUtil::midPoint(pCR, pDR);

             // A, B, C, D mid points
             double halfParallelDistance = MathUtil::distance(pABM, pCDM) / 2.0;
             QPointF pAM = MathUtil::subtract(pABM, MathUtil::normalize(vAB, halfParallelDistance));
             QPointF pAML = MathUtil::subtract(pAM, vABo);
             QPointF pAMR = MathUtil::add(pAM, vABo);
             QPointF pBM = MathUtil::add(pABM, MathUtil::normalize(vAB, halfParallelDistance));
             QPointF pBML = MathUtil::subtract(pBM, vABo);
             QPointF pBMR = MathUtil::add(pBM, vABo);
             QPointF pCM = MathUtil::subtract(pCDM, MathUtil::normalize(vCD, halfParallelDistance));
             QPointF pCML = MathUtil::subtract(pCM, vABo);
             QPointF pCMR = MathUtil::add(pCM, vABo);
             QPointF pDM = MathUtil::add(pCDM, MathUtil::normalize(vCD, halfParallelDistance));
             QPointF pDML = MathUtil::subtract(pDM, vABo);
             QPointF pDMR = MathUtil::add(pDM, vABo);

             // crossing points
             QPointF vACM = MathUtil::normalize(MathUtil::subtract(pCM, pAM), railDisplacement);
             QPointF vACMo = MathUtil::orthogonal(vACM);
             QPointF vBDM = MathUtil::normalize(MathUtil::subtract(pDM, pBM), railDisplacement);
             QPointF vBDMo = MathUtil::orthogonal(vBDM);
             QPointF pBDR = MathUtil::add(pM, vACM);
             QPointF pBDL = MathUtil::subtract(pM, vACM);

             // crossing diamond point (no gaps)
             QPointF pVR = MathUtil::add(pBDL, vBDM);
             QPointF pKL = MathUtil::subtract(pBDL, vBDM);
             QPointF pKR = MathUtil::add(pBDR, vBDM);
             QPointF pVL = MathUtil::subtract(pBDR, vBDM);

             // crossing diamond points (with gaps)
             QPointF vACM2 = MathUtil::normalize(vACM, 2.0);
             QPointF vBDM2 = MathUtil::normalize(vBDM, 2.0);
             // (syntax of "pKLtC" is "point LK toward C", etc.)
             QPointF pKLtC = MathUtil::add(pKL, vACM2);
             QPointF pKLtD = MathUtil::add(pKL, vBDM2);
             QPointF pVLtA = MathUtil::subtract(pVL, vACM2);
             QPointF pVLtD = MathUtil::add(pVL, vBDM2);
             QPointF pKRtA = MathUtil::subtract(pKR, vACM2);
             QPointF pKRtB = MathUtil::subtract(pKR, vBDM2);
             QPointF pVRtB = MathUtil::subtract(pVR, vBDM2);
             QPointF pVRtC = MathUtil::add(pVR, vACM2);

             // A, B, C, D frog points
             vCM = MathUtil::normalize(MathUtil::subtract(pCM, pM));
             dirCM_DEG = MathUtil::computeAngleDEG(vCM);
             double deltaBAC_DEG = MathUtil::absDiffAngleDEG(dirAB_DEG, dirCM_DEG);
             double deltaBAC_RAD = qDegreesToRadians(deltaBAC_DEG);
             hypotF = railDisplacement / qSin(deltaBAC_RAD / 2.0);
             QPointF vACF = MathUtil::normalize(MathUtil::add(vACM, vAB), hypotF);
             QPointF pAFL = MathUtil::add(pAM, vACF);
             QPointF pCFR = MathUtil::subtract(pCM, vACF);
             QPointF vBDF = MathUtil::normalize(MathUtil::add(vBDM, vCD), hypotF);
             QPointF pBFL = MathUtil::add(pBM, vBDF);
             QPointF pDFR = MathUtil::subtract(pDM, vBDF);

             // A, B, C, D frog points
             QPointF pAFR = MathUtil::add(MathUtil::add(pAFL, vACMo), vACMo);
             QPointF pBFR = MathUtil::subtract(MathUtil::subtract(pBFL, vBDMo), vBDMo);
             QPointF pCFL = MathUtil::subtract(MathUtil::subtract(pCFR, vACMo), vACMo);
             QPointF pDFL = MathUtil::add(MathUtil::add(pDFR, vBDMo), vBDMo);

             // end of switch rails (closed)
             QPointF vABF = MathUtil::normalize(vAB, hypotF);
             pAP = MathUtil::subtract(pAM, vABF);
             pAPL = MathUtil::subtract(pAP, vABo);
             pAPR = MathUtil::add(pAP, vABo);
             QPointF pBP = MathUtil::add(pBM, vABF);
             QPointF pBPL = MathUtil::subtract(pBP, vABo);
             QPointF pBPR = MathUtil::add(pBP, vABo);

             QPointF vCDF = MathUtil::normalize(vCD, hypotF);
             QPointF pCP = MathUtil::subtract(pCM, vCDF);
             QPointF pCPL = MathUtil::add(pCP, vCDo);
             QPointF pCPR = MathUtil::subtract(pCP, vCDo);
             QPointF pDP = MathUtil::add(pDM, vCDF);
             QPointF pDPL = MathUtil::add(pDP, vCDo);
             QPointF pDPR = MathUtil::subtract(pDP, vCDo);

             // end of switch rails (open)
             QPointF vS = MathUtil::normalize(vABo, 2.0);
             QPointF pASL = MathUtil::add(pAPL, vS);
             // QPointF pASR = MathUtil::subtract(pAPR, vS);
             QPointF pBSL = MathUtil::add(pBPL, vS);
             // QPointF pBSR = MathUtil::subtract(pBPR, vS);
             QPointF pCSR = MathUtil::subtract(pCPR, vS);
             // QPointF pCSL = MathUtil::add(pCPL, vS);
             QPointF pDSR = MathUtil::subtract(pDPR, vS);
             // QPointF pDSL = MathUtil::add(pDPL, vS);

             // end of switch rails (open at frogs)
             QPointF pAFS = MathUtil::subtract(pAFL, vS);
             QPointF pBFS = MathUtil::subtract(pBFL, vS);
             QPointF pCFS = MathUtil::add(pCFR, vS);
             QPointF pDFS = MathUtil::add(pDFR, vS);

             // vSo = MathUtil::orthogonal(vS);
             // QPointF pAFSR = MathUtil::add(pAFL, vSo);
             // QPointF pBFSR = MathUtil::subtract(pBFL, vSo);
             // QPointF pCFSL = MathUtil::subtract(pCFR, vSo);
             // QPointF pDFSL = MathUtil::add(pDFR, vSo);

             if (isMain == mainlineA) {
                 //g2.draw(new Line2D.Double(pAL, pABL));
              lineItem = new QGraphicsLineItem(pAL.x(), pAL.y(), pABL.x(), pABL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pVRtB, pKLtD));
              lineItem = new QGraphicsLineItem(pVRtB.x(), pVRtB.y(), pKLtD.x(), pKLtD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pAFL, pABR));
              lineItem = new QGraphicsLineItem(pAFL.x(), pAFL.y(), pABR.x(), pABR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
                //g2.draw(new Line2D.Double(pAFL, pKL));
              lineItem = new QGraphicsLineItem(pAFL.x(), pAFL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              QPainterPath path = QPainterPath();
                 path.moveTo(pAR.x(), pAR.y());
                 path.lineTo(pAPR.x(), pAPR.y());
                 path.quadTo(pAMR.x(), pAMR.y(), pAFR.x(), pAFR.y());
                 path.lineTo(pVR.x(), pVR.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 if (state != Turnout::CLOSED) {  // unknown or diverting path
                     path = QPainterPath();
                     path.moveTo(pAPL.x(), pAPL.y());
                     path.quadTo(pAML.x(), pAML.y(), pAFL.x(), pAFL.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);//                         g2.draw(new Line2D.Double(pASR, pAFSR));
                 } else {                        // continuing path
                     //g2.draw(new Line2D.Double(pAPR, pAFL));
                  lineItem = new QGraphicsLineItem(pAPR.x(), pAPR.y(), pAFL.x(), pAFL.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                  path = QPainterPath();
                     path.moveTo(pASL.x(), pASL.y());
                     path.quadTo(pAML.x(), pAML.y(), pAFS.x(), pAFS.y());
 //                         g2.draw(path);
                 }
             }
             if (isMain == mainlineB) {
                 //g2.draw(new Line2D.Double(pABL, pBL));
              lineItem = new QGraphicsLineItem(pABL.x(), pABL.y(), pBL.x(), pBL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pKLtC, pVLtA));
              lineItem = new QGraphicsLineItem(pKLtC.x(), pKLtC.y(), pVLtA.x(), pVLtA.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pBFL, pABR));
              lineItem = new QGraphicsLineItem(pBFL.x(), pBFL.y(), pABR.x(), pABR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pBFL, pKL));
              lineItem = new QGraphicsLineItem(pBFL.x(), pBFL.y(), pKL.x(), pKL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              QPainterPath path =  QPainterPath();
                 path.moveTo(pBR.x(), pBR.y());
                 path.lineTo(pBPR.x(), pBPR.y());
                 path.quadTo(pBMR.x(), pBMR.y(), pBFR.x(), pBFR.y());
                 path.lineTo(pVL.x(), pVL.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 if (state != Turnout::CLOSED) {  // unknown or diverting path
                     path = QPainterPath();
                     path.moveTo(pBPL.x(), pBPL.y());
                     path.quadTo(pBML.x(), pBML.y(), pBFL.x(), pBFL.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);//                         g2.draw(new Line2D.Double(pBSR, pBFSR));
                 } else {
                     //g2.draw(new Line2D.Double(pBPR, pBFL));
                  lineItem = new QGraphicsLineItem(pBPR.x(), pBPR.y(), pBFL.x(), pBFL.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                  path = QPainterPath();
                     path.moveTo(pBSL.x(), pBSL.y());
                     path.quadTo(pBML.x(), pBML.y(), pBFS.x(), pBFS.y());
 //                         g2.draw(path);
                 }
             }
             if (isMain == mainlineC) {
                 //g2.draw(new Line2D.Double(pCR, pCDR));
              lineItem = new QGraphicsLineItem(pCR.x(), pCR.y(), pCR.x(), pCDR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pKRtB, pVLtD));
              lineItem = new QGraphicsLineItem(pKRtB.x(), pKRtB.y(), pVLtD.x(), pVLtD.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pCFR, pCDL));
              lineItem = new QGraphicsLineItem(pCFR.x(), pCFR.y(), pCDL.x(), pCDL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pCFR, pKR));
              lineItem = new QGraphicsLineItem(pCFR.x(), pCFR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              QPainterPath path = QPainterPath();
                 path.moveTo(pCL.x(), pCL.y());
                 path.lineTo(pCPL.x(), pCPL.y());
                 path.quadTo(pCML.x(), pCML.y(), pCFL.x(), pCFL.y());
                 path.lineTo(pVL.x(), pVL.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 if (state != Turnout::CLOSED) {  // unknown or diverting path
                     path = QPainterPath();
                     path.moveTo(pCPR.x(), pCPR.y());
                     path.quadTo(pCMR.x(), pCMR.y(), pCFR.x(), pCFR.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);
                     //                         g2.draw(new Line2D.Double(pCSL, pCFSL));
                 } else {
                     //g2.draw(new Line2D.Double(pCPL, pCFR));
                  lineItem = new QGraphicsLineItem(pCPL.x(), pCPL.y(), pCFR.x(), pCFR.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                  path = QPainterPath();
                     path.moveTo(pCSR.x(), pCSR.y());
                     path.quadTo(pCMR.x(), pCMR.y(), pCFS.x(), pCFS.y());
 //                         g2.draw(path);
                 }
             }
             if (isMain == mainlineD) {
                 //g2.draw(new Line2D.Double(pCDR, pDR));
              lineItem = new QGraphicsLineItem(pCDR.x(), pCDR.y(), pDR.x(), pDR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pKRtA, pVRtC));
              lineItem = new QGraphicsLineItem(pKRtA.x(), pKRtA.y(), pVRtC.x(), pVRtC.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pDFR, pCDL));
              lineItem = new QGraphicsLineItem(pDFR.x(), pDFR.y(), pCDL.x(), pCDL.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              //g2.draw(new Line2D.Double(pDFR, pKR));
              lineItem = new QGraphicsLineItem(pDFR.x(), pDFR.y(), pKR.x(), pKR.y());
              lineItem->setPen(layoutEditor->drawingStroke);
              itemGroup->addToGroup(lineItem);
              QPainterPath path = QPainterPath();
                 path.moveTo(pDL.x(), pDL.y());
                 path.lineTo(pDPL.x(), pDPL.y());
                 path.quadTo(pDML.x(), pDML.y(), pDFL.x(), pDFL.y());
                 path.lineTo(pVR.x(), pVR.y());
                 //g2.draw(path);
                 QGraphicsPathItem* pathItem = new QGraphicsPathItem(path);
                 pathItem->setPen(layoutEditor->drawingStroke);
                 itemGroup->addToGroup(pathItem);
                 if (state != Turnout::CLOSED) {  // unknown or diverting path
                     path = QPainterPath();
                     path.moveTo(pDPR.x(), pDPR.y());
                     path.quadTo(pDMR.x(), pDMR.y(), pDFR.x(), pDFR.y());
                     //g2.draw(path);
                     pathItem = new QGraphicsPathItem(path);
                     pathItem->setPen(layoutEditor->drawingStroke);
                     itemGroup->addToGroup(pathItem);
                     //                         g2.draw(new Line2D.Double(pDSL, pDFSL));
                 } else {
                     //g2.draw(new Line2D.Double(pDPL, pDFR));
                  lineItem = new QGraphicsLineItem(pDPL.x(), pDPL.y(), pDFR.x(), pDFR.y());
                  lineItem->setPen(layoutEditor->drawingStroke);
                  itemGroup->addToGroup(lineItem);
                  path = QPainterPath();
                     path.moveTo(pDSR.x(), pDSR.y());
                     path.quadTo(pDMR.x(), pDMR.y(), pDFS.x(), pDFS.y());
 //                         g2.draw(path);
                 }
             }
             break;
         }   // case DOUBLE_XOVER
 #if 0
         case LayoutTurnout::TurnoutType::RH_XOVER: {
             // A, B, C, D end points (left and right)
             QPointF vAB = MathUtil::normalize(MathUtil::subtract(pB, pA), railDisplacement);
             double dirAB_DEG = MathUtil::computeAngleDEG(vAB);
             QPointF vABo = MathUtil::orthogonal(MathUtil::normalize(vAB, railDisplacement));
             pAL = MathUtil::subtract(pA, vABo);
             pAR = MathUtil::add(pA, vABo);
             pBL = MathUtil::subtract(pB, vABo);
             pBR = MathUtil::add(pB, vABo);
             QPointF vCD = MathUtil::normalize(MathUtil::subtract(pD, pC), railDisplacement);
             QPointF vCDo = MathUtil::orthogonal(MathUtil::normalize(vCD, railDisplacement));
             pCL = MathUtil::add(pC, vCDo);
             pCR = MathUtil::subtract(pC, vCDo);
             QPointF pDL = MathUtil::add(pD, vCDo);
             QPointF pDR = MathUtil::subtract(pD, vCDo);

             // AB and CD mid points
             QPointF pABM = MathUtil::midPoint(pA, pB);
             QPointF pABL = MathUtil::subtract(pABM, vABo);
             QPointF pABR = MathUtil::add(pABM, vABo);
             QPointF pCDM = MathUtil::midPoint(pC, pD);
             QPointF pCDL = MathUtil::subtract(pCDM, vABo);
             QPointF pCDR = MathUtil::add(pCDM, vABo);

             // directions
             QPointF vAC = MathUtil::normalize(MathUtil::subtract(pCDM, pABM), railDisplacement);
             QPointF vACo = MathUtil::orthogonal(MathUtil::normalize(vAC, railDisplacement));
             double dirAC_DEG = MathUtil::computeAngleDEG(vAC);
             double deltaBAC_DEG = MathUtil::absDiffAngleDEG(dirAB_DEG, dirAC_DEG);
             double deltaBAC_RAD = Math.toRadians(deltaBAC_DEG);

             // AC mid points
             QPointF pACL = MathUtil::subtract(pM, vACo);
             QPointF pACR = MathUtil::add(pM, vACo);

             // frogs
             hypotF = railDisplacement / Math.sin(deltaBAC_RAD / 2.0);
             QPointF vF = MathUtil::normalize(MathUtil::add(vAB, vAC), hypotF);
             QPointF pABF = MathUtil::add(pABM, vF);
             QPointF pCDF = MathUtil::subtract(pCDM, vF);

             // frog primes
             QPointF pABFP = MathUtil::add(MathUtil::add(pABF, vACo), vACo);
             QPointF pCDFP = MathUtil::subtract(MathUtil::subtract(pCDF, vACo), vACo);

             // end of switch rails (closed)
             QPointF vABF = MathUtil::normalize(vAB, hypotF);
             pAP = MathUtil::subtract(pABM, vABF);
             pAPL = MathUtil::subtract(pAP, vABo);
             pAPR = MathUtil::add(pAP, vABo);
             QPointF pCP = MathUtil::add(pCDM, vABF);
             QPointF pCPL = MathUtil::add(pCP, vCDo);
             QPointF pCPR = MathUtil::subtract(pCP, vCDo);

             // end of switch rails (open)
             QPointF vS = MathUtil::normalize(vAB, 2.0);
             QPointF vSo = MathUtil::orthogonal(vS);
             QPointF pASL = MathUtil::add(pAPL, vSo);
             // QPointF pASR = MathUtil::subtract(pAPR, vSo);
             // QPointF pCSL = MathUtil::add(pCPL, vSo);
             QPointF pCSR = MathUtil::subtract(pCPR, vSo);

             // end of switch rails (open at frogs)
             QPointF pABFS = MathUtil::subtract(pABF, vSo);
             // QPointF pABFSP = MathUtil::subtract(pABF, vS);
             QPointF pCDFS = MathUtil::add(pCDF, vSo);
             // QPointF pCDFSP = MathUtil::add(pCDF, vS);

             if (isMain == mainlineA) {
                 g2.draw(new Line2D.Double(pAL, pABL));
                 QPainterPath path = new QPainterPath();
                 path.moveTo(pAR.x(), pAR.y());
                 path.lineTo(pAPR.x(), pAPR.y());
                 path.quadTo(pABR.x(), pABR.y(), pABFP.x(), pABFP.y());
                 path.lineTo(pACR.x(), pACR.y());
                 g2.draw(path);
                 g2.draw(new Line2D.Double(pABF, pACL));
                 if (state != Turnout.CLOSED) {  // unknown or diverting path
                     path = new QPainterPath();
                     path.moveTo(pAPL.x(), pAPL.y());
                     path.quadTo(pABL.x(), pABL.y(), pABF.x(), pABF.y());
                     g2.draw(path);
 //                         g2.draw(new Line2D.Double(pASR, pABFSP));
                 } else {                        // continuing path
                     g2.draw(new Line2D.Double(pAPR, pABF));
                     path = new QPainterPath();
                     path.moveTo(pASL.x(), pASL.y());
                     path.quadTo(pABL.x(), pABL.y(), pABFS.x(), pABFS.y());
 //                         g2.draw(path);
                 }
             }
             if (isMain == mainlineB) {
                 g2.draw(new Line2D.Double(pABL, pBL));
                 g2.draw(new Line2D.Double(pABF, pBR));
             }
             if (isMain == mainlineC) {
                 g2.draw(new Line2D.Double(pCR, pCDR));
                 QPainterPath path = new QPainterPath();
                 path.moveTo(pCL.x(), pCL.y());
                 path.lineTo(pCPL.x(), pCPL.y());
                 path.quadTo(pCDL.x(), pCDL.y(), pCDFP.x(), pCDFP.y());
                 path.lineTo(pACL.x(), pACL.y());
                 g2.draw(path);
                 g2.draw(new Line2D.Double(pCDF, pACR));
                 if (state != Turnout.CLOSED) {  // unknown or diverting path
                     path = new QPainterPath();
                     path.moveTo(pCPR.x(), pCPR.y());
                     path.quadTo(pCDR.x(), pCDR.y(), pCDF.x(), pCDF.y());
                     g2.draw(path);
 //                         g2.draw(new Line2D.Double(pCSL, pCDFSP));
                 } else {                        // continuing path
                     g2.draw(new Line2D.Double(pCPL, pCDF));
                     path = new QPainterPath();
                     path.moveTo(pCSR.x(), pCSR.y());
                     path.quadTo(pCDR.x(), pCDR.y(), pCDFS.x(), pCDFS.y());
 //                         g2.draw(path);
                 }
             }
             if (isMain == mainlineD) {
                 g2.draw(new Line2D.Double(pCDR, pDR));
                 g2.draw(new Line2D.Double(pCDF, pDL));
             }
             break;
         }   // case RH_XOVER

         case LH_XOVER: {
             // B, A, D, C end points (left and right)
             QPointF vBA = MathUtil::normalize(MathUtil::subtract(pA, pB), railDisplacement);
             double dirBA_DEG = MathUtil::computeAngleDEG(vBA);
             QPointF vBAo = MathUtil::orthogonal(MathUtil::normalize(vBA, railDisplacement));
             pBL = MathUtil::add(pB, vBAo);
             pBR = MathUtil::subtract(pB, vBAo);
             pAL = MathUtil::add(pA, vBAo);
             pAR = MathUtil::subtract(pA, vBAo);
             QPointF vDC = MathUtil::normalize(MathUtil::subtract(pC, pD), railDisplacement);
             QPointF vDCo = MathUtil::orthogonal(MathUtil::normalize(vDC, railDisplacement));
             QPointF pDL = MathUtil::subtract(pD, vDCo);
             QPointF pDR = MathUtil::add(pD, vDCo);
             pCL = MathUtil::subtract(pC, vDCo);
             pCR = MathUtil::add(pC, vDCo);

             // BA and DC mid points
             QPointF pBAM = MathUtil::midPoint(pB, pA);
             QPointF pBAL = MathUtil::add(pBAM, vBAo);
             QPointF pBAR = MathUtil::subtract(pBAM, vBAo);
             QPointF pDCM = MathUtil::midPoint(pD, pC);
             QPointF pDCL = MathUtil::add(pDCM, vBAo);
             QPointF pDCR = MathUtil::subtract(pDCM, vBAo);

             // directions
             QPointF vBD = MathUtil::normalize(MathUtil::subtract(pDCM, pBAM), railDisplacement);
             QPointF vBDo = MathUtil::orthogonal(MathUtil::normalize(vBD, railDisplacement));
             double dirBD_DEG = MathUtil::computeAngleDEG(vBD);
             double deltaABD_DEG = MathUtil::absDiffAngleDEG(dirBA_DEG, dirBD_DEG);
             double deltaABD_RAD = Math.toRadians(deltaABD_DEG);

             // BD mid points
             QPointF pBDL = MathUtil::add(pM, vBDo);
             QPointF pBDR = MathUtil::subtract(pM, vBDo);

             // frogs
             hypotF = railDisplacement / Math.sin(deltaABD_RAD / 2.0);
             QPointF vF = MathUtil::normalize(MathUtil::add(vBA, vBD), hypotF);
             QPointF pBFL = MathUtil::add(pBAM, vF);
             QPointF pBF = MathUtil::subtract(pBFL, vBDo);
             QPointF pBFR = MathUtil::subtract(pBF, vBDo);
             QPointF pDFR = MathUtil::subtract(pDCM, vF);
             QPointF pDF = MathUtil::add(pDFR, vBDo);
             QPointF pDFL = MathUtil::add(pDF, vBDo);

             // end of switch rails (closed)
             QPointF vBAF = MathUtil::normalize(vBA, hypotF);
             QPointF pBP = MathUtil::subtract(pBAM, vBAF);
             QPointF pBPL = MathUtil::add(pBP, vBAo);
             QPointF pBPR = MathUtil::subtract(pBP, vBAo);
             QPointF pDP = MathUtil::add(pDCM, vBAF);
             QPointF pDPL = MathUtil::subtract(pDP, vDCo);
             QPointF pDPR = MathUtil::add(pDP, vDCo);

             // end of switch rails (open)
             QPointF vS = MathUtil::normalize(vBA, 2.0);
             QPointF vSo = MathUtil::orthogonal(vS);
             QPointF pBSL = MathUtil::subtract(pBPL, vSo);
             // QPointF pBSR = MathUtil::add(pBPR, vSo);
             // QPointF pDSL = MathUtil::subtract(pDPL, vSo);
             QPointF pDSR = MathUtil::add(pDPR, vSo);

             // end of switch rails (open at frogs)
             QPointF pBAFS = MathUtil::add(pBFL, vSo);
             // QPointF pBAFSP = MathUtil::subtract(pBFL, vS);
             QPointF pDCFS = MathUtil::subtract(pDFR, vSo);
             // QPointF pDCFSP = MathUtil::add(pDFR, vS);

             if (isMain == mainlineA) {
                 g2.draw(new Line2D.Double(pBAL, pAL));
                 g2.draw(new Line2D.Double(pBFL, pAR));
             }
             if (isMain == mainlineB) {
                 g2.draw(new Line2D.Double(pBL, pBAL));
                 QPainterPath path = new QPainterPath();
                 path.moveTo(pBR.x(), pBR.y());
                 path.lineTo(pBPR.x(), pBPR.y());
                 path.quadTo(pBAR.x(), pBAR.y(), pBFR.x(), pBFR.y());
                 path.lineTo(pBDR.x(), pBDR.y());
                 g2.draw(path);
                 g2.draw(new Line2D.Double(pBFL, pBDL));
                 if (state != Turnout.CLOSED) {  // unknown or diverting path
                     path = new QPainterPath();
                     path.moveTo(pBPL.x(), pBPL.y());
                     path.quadTo(pBAL.x(), pBAL.y(), pBFL.x(), pBFL.y());
                     g2.draw(path);
 //                         g2.draw(new Line2D.Double(pBSR, pBAFSP));
                 } else {                        // continuing path
                     g2.draw(new Line2D.Double(pBPR, pBFL));
                     path = new QPainterPath();
                     path.moveTo(pBSL.x(), pBSL.y());
                     path.quadTo(pBAL.x(), pBAL.y(), pBAFS.x(), pBAFS.y());
 //                         g2.draw(path);
                 }
             }
             if (isMain == mainlineC) {
                 g2.draw(new Line2D.Double(pDCR, pCR));
                 g2.draw(new Line2D.Double(pDFR, pCL));
             }
             if (isMain == mainlineD) {
                 g2.draw(new Line2D.Double(pDR, pDCR));
                 QPainterPath path = new QPainterPath();
                 path.moveTo(pDL.x(), pDL.y());
                 path.lineTo(pDPL.x(), pDPL.y());
                 path.quadTo(pDCL.x(), pDCL.y(), pDFL.x(), pDFL.y());
                 path.lineTo(pBDL.x(), pBDL.y());
                 g2.draw(path);
                 g2.draw(new Line2D.Double(pDFR, pBDR));
                 if (state != Turnout.CLOSED) {  // unknown or diverting path
                     path = new QPainterPath();
                     path.moveTo(pDPR.x(), pDPR.y());
                     path.quadTo(pDCR.x(), pDCR.y(), pDFR.x(), pDFR.y());
                     g2.draw(path);
 //                         g2.draw(new Line2D.Double(pDSL, pDCFSP));
                 } else {                        // continuing path
                     g2.draw(new Line2D.Double(pDPL, pDFR));
                     path = new QPainterPath();
                     path.moveTo(pDSR.x(), pDSR.y());
                     path.quadTo(pDCR.x(), pDCR.y(), pDCFS.x(), pDCFS.y());
 //                         g2.draw(path);
                 }
             }
             break;
         }   // case LH_XOVER
 #endif
         case LayoutTurnout::TurnoutType::SINGLE_SLIP:
         case LayoutTurnout::TurnoutType::DOUBLE_SLIP: {
             log->error("slips should be being drawn by LayoutSlip sub-class");
             break;
         }
         default: {
             // this should never happen... but...
             log->error("Unknown turnout type: " + QString::number(toType));
             break;
         }
     }
          itemMain = itemGroup;
          g2->addItem(itemMain);
}   // draw2

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnoutView::highlightUnconnected(EditScene* g2, HitPointType::TYPES specificType) {
     if (((specificType == HitPointType::NONE) || (specificType == HitPointType::TURNOUT_A))
             && (getConnectA() == nullptr)) {
         //g2.fill(layoutEditor->trackControlCircleAt(getCoordsA()));
      QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsA());
      item->setPen(QPen(layoutEditor->defaultTrackColor, 1));
     }

     if (((specificType == HitPointType::NONE) || (specificType == HitPointType::TURNOUT_B))
             && (getConnectB() == nullptr)) {
         //g2.fill(layoutEditor->trackControlCircleAt(getCoordsB()));
      QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsB());
      item->setPen(QPen(layoutEditor->defaultTrackColor, 1));
     }

     if (((specificType == HitPointType::NONE) || (specificType ==HitPointType::TURNOUT_C))
             && (getConnectC() == nullptr)) {
         //g2.fill(layoutEditor->trackControlCircleAt(getCoordsC()));
      QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsC());
      item->setPen(QPen(layoutEditor->defaultTrackColor, 1));
     }
     if ((getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER)
             || (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
             || (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER)) {
         if (((specificType == HitPointType::NONE) || (specificType == HitPointType::TURNOUT_D))
                 && (getConnectD() == nullptr)) {
             //g2.fill(layoutEditor.trackControlCircleAt(getCoordsD()));
          QGraphicsEllipseItem* item = trackControlCircleAt(getCoordsD());
          item->setPen(QPen(layoutEditor->defaultTrackColor, 1));
         }
     }
     rects = item;
     g2->addItem(rects);
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnoutView::drawTurnoutControls(EditScene* g2) {
  if (!disabled && !(disableWhenOccupied && isOccupied()))
  {
   invalidateItem(g2,circles);
   if (!disabled && !(disableWhenOccupied && isOccupied()))
   {
    QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
    //QColor foregroundColor = g2.getColor();
    //if turnout is not continuing state
 //   if (getState() != continuingSense) {
 //       //then switch to background color
 //       g2.setColor(g2.getBackground());
 //   }

       //g2.draw(layoutEditor.trackControlCircleAt(center));
    QGraphicsEllipseItem* item = trackControlCircleAt(center);
    item->setPen(layoutEditor->drawingStroke);
    if (layoutEditor->isTurnoutFillControlCircles()) {
     QBrush brush = QBrush(layoutEditor->drawingStroke.color());
     item->setBrush(brush);
    }
    itemGroup->addToGroup(item);
    //if turnout is not continuing state
 //   if (getState() != continuingSense) {
 //       //then restore foreground color
 //       g2.setColor(foregroundColor);
 //   }
    circles = itemGroup;
    g2->addItem(circles);
   }
  }
}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ void LayoutTurnoutView::drawEditControls(EditScene* g2) {
  invalidateItem(g2,rects);
  QGraphicsItemGroup* itemGroup = new QGraphicsItemGroup();
  if(rects!=nullptr && rects->scene()!=nullptr)
  {
   g2->removeItem(rects);
   rects = nullptr;
  }

     QPointF pt = getCoordsA();
     if (getTurnoutType() >= LayoutTurnout::TurnoutType::DOUBLE_XOVER && getTurnoutType() <= LayoutTurnout::TurnoutType::DOUBLE_SLIP)
     {
         if (getConnectA() == nullptr) {
             //g2.setColor(Color.magenta);
          layoutEditor->drawingStroke.setColor(QColor(Qt::magenta));
         } else {
             //g2.setColor(Color.blue);
          layoutEditor->drawingStroke.setColor(Qt::blue);
         }
     } else {
         if (getConnectA() == nullptr) {
             //g2.setColor(Color.red);
          layoutEditor->drawingStroke.setColor(Qt::red);
         } else {
             //g2.setColor(Color.green);
          layoutEditor->drawingStroke.setColor(Qt::green);
         }
     }
     //g2.draw(layoutEditor.trackEditControlRectAt(pt));
     QGraphicsRectItem* item = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
     item->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(item);

     pt = getCoordsB();
     if (getConnectB() == nullptr) {
         //g2.setColor(Color.red);
      layoutEditor->drawingStroke.setColor(Qt::red);
     } else {
         //g2.setColor(Color.green);
      layoutEditor->drawingStroke.setColor(Qt::green);
     }
     //g2.draw(layoutEditor.trackEditControlRectAt(pt));
     item =  new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
     item->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(item);

     pt = getCoordsC();
     if (getConnectC() == nullptr) {
      //g2.setColor(Color.red);
      layoutEditor->drawingStroke.setColor(Qt::red);
     } else {
      //g2.setColor(Color.green);
      layoutEditor->drawingStroke.setColor(Qt::green);
     }
     //g2.draw(layoutEditor.trackEditControlRectAt(pt));
     item = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
     item->setPen(layoutEditor->drawingStroke);
     itemGroup->addToGroup(item);

     if ((getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_XOVER)
             || (getTurnoutType() == LayoutTurnout::TurnoutType::RH_XOVER)
             || (getTurnoutType() == LayoutTurnout::TurnoutType::LH_XOVER)
             || (getTurnoutType() == LayoutTurnout::TurnoutType::SINGLE_SLIP)
             || (getTurnoutType() == LayoutTurnout::TurnoutType::DOUBLE_SLIP)) {
         pt = getCoordsD();
         if (getConnectD() == nullptr) {
          //g2.setColor(Color.red);
          layoutEditor->drawingStroke.setColor(Qt::red);
         } else {
          //g2.setColor(Color.green);
          layoutEditor->drawingStroke.setColor(Qt::green);
         //g2.draw(layoutEditor.trackEditControlRectAt(pt));
          item = new QGraphicsRectItem(layoutEditor->trackEditControlRectAt(pt));
          item->setPen(layoutEditor->drawingStroke);
          itemGroup->addToGroup(item);
         }
         rects = itemGroup;
         g2->addItem(rects);
     }
}

/*
* Used by ConnectivityUtil to determine the turnout state necessary to get
* from prevLayoutBlock* ==> currLayoutBlock* ==> nextLayoutBlock
 */
/*protected*/ int LayoutTurnoutView::getConnectivityStateForLayoutBlocks(
        LayoutBlock* currLayoutBlock,
        LayoutBlock* prevLayoutBlock,
        LayoutBlock* nextLayoutBlock,
        bool suppress) {

    return turnout->getConnectivityStateForLayoutBlocks(currLayoutBlock,
            prevLayoutBlock,
            nextLayoutBlock,
            suppress);
}

/**
 * {@inheritDoc}
 */
// TODO: on the cross-overs, check the internal boundary details.
//@Override
/*public*/ void LayoutTurnoutView::reCheckBlockBoundary() {

    turnout->reCheckBlockBoundary();

}

/**
 * {@inheritDoc}
 */
//@Override
/*protected*/ QList<LayoutConnectivity*> LayoutTurnoutView::getLayoutConnectivity() {
    return turnout->getLayoutConnectivity();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ /*@Nonnull*/
QList<HitPointType::TYPES> LayoutTurnoutView::checkForFreeConnections() {
    return turnout->checkForFreeConnections();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ bool LayoutTurnoutView::checkForUnAssignedBlocks() {
    // because getLayoutBlock[BCD] will return block [A] if they're null
    // we only need to test block [A]
    return turnout->checkForUnAssignedBlocks();
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::checkForNonContiguousBlocks(/*@Nonnull*/ QMap<QString, QList<QSet<QString> *>* > blockNamesToTrackNameSetsMap) {

    turnout->checkForNonContiguousBlocks(blockNamesToTrackNameSetsMap);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::collectContiguousTracksNamesInBlockNamed(/*@Nonnull*/ QString blockName,
        /*@Nonnull*/ QSet<QString> *trackNameSet) {

    turnout->collectContiguousTracksNamesInBlockNamed(blockName, trackNameSet);
}

/**
 * {@inheritDoc}
 */
//@Override
/*public*/ void LayoutTurnoutView::setAllLayoutBlocks(LayoutBlock* layoutBlock) {
    turnout->setAllLayoutBlocks(layoutBlock);
}


/*private*/ /*final*/ /*static*/ Logger* LayoutTurnoutView::log = LoggerFactory::getLogger("LayoutTurnoutView");
