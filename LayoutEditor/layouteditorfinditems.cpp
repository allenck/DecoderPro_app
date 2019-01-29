#include "layouteditorfinditems.h"
#include "tracksegment.h"
#include "layouteditor.h"
#include "layoutturntable.h"
#include "signalmastmanager.h"

/**
 * A collection of tools to find various object on the layout editor panel.
 *
*/
///*public*/ class LayoutEditorFindItems {


    /*public*/ LayoutEditorFindItems::LayoutEditorFindItems(LayoutEditor* editor) {
        layoutEditor = editor;
    }

    /*public*/ TrackSegment* LayoutEditorFindItems::findTrackSegmentByName(QString name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor->trackList->size(); i++) {
            TrackSegment* t = layoutEditor->trackList->at(i);
            if (t->getID()==(name)) {
                return t;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByName(QString name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor->pointList->size(); i++) {
            PositionablePoint* p = layoutEditor->pointList->at(i);
            if (p->getID()==(name)) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointAtTrackSegments(TrackSegment* tr1, TrackSegment* tr2) {
        for (int i = 0; i < layoutEditor->pointList->size(); i++) {
            PositionablePoint* p = layoutEditor->pointList->at(i);
            if (((p->getConnect1() == tr1) && (p->getConnect2() == tr2))
                    || ((p->getConnect1() == tr2) && (p->getConnect2() == tr1))) {
                return p;
            }
        }
        return nullptr;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionableLinkPoint(LayoutBlock* blk1) {
        for (PositionablePoint* p : *layoutEditor->pointList) {
            if (p->getType() == PositionablePoint::EDGE_CONNECTOR) {
                if ((p->getConnect1() != NULL && p->getConnect1()->getLayoutBlock() == blk1)
                        || (p->getConnect2() != NULL && p->getConnect2()->getLayoutBlock() == blk1)) {
                    return p;
                }
            }
        }
        return nullptr;
    }

    /**
     * Returns an array list of track segments matching the block name.
     */
    /*public*/ QList<TrackSegment*> LayoutEditorFindItems::findTrackSegmentByBlock(QString name) {
        if (name.length() <= 0) {
            return QList<TrackSegment*>();
        }
        QList<TrackSegment*> ts = QList<TrackSegment*>();
        for (int i = 0; i < layoutEditor->trackList->size(); i++) {
            TrackSegment* t = layoutEditor->trackList->at(i);
            if (t->getBlockName()==(name)) {
                ts.append(t);
            }
        }
        return ts;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByEastBoundSignal(QString signalName) {
        for (int i = 0; i < layoutEditor->pointList->size(); i++) {
            PositionablePoint* p = layoutEditor->pointList->at(i);
            if (p->getEastBoundSignal()==(signalName)) {
                return p;
            }
        }
        return nullptr;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByWestBoundSignal(QString signalName) {
        for (int i = 0; i < layoutEditor->pointList->size(); i++) {
            PositionablePoint* p = layoutEditor->pointList->at(i);
            if (p->getWestBoundSignal()==(signalName)) {
                return p;
            }
        }
        return nullptr;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByWestBoundBean(NamedBean* bean) {
        if (qobject_cast<SignalMast*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getWestBoundSignalMast() == bean) {
                    return p;
                }
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getWestBoundSensor() == bean) {
                    return p;
                }
            }
        } else if (qobject_cast<SignalHead*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getWestBoundSignal()==(bean->getSystemName())
                        || p->getWestBoundSignal()==(bean->getSystemName())) {
                    return p;
                }
            }
        }
        return nullptr;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByEastBoundBean(NamedBean* bean) {
        if (qobject_cast<SignalMast*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getEastBoundSignalMast() == bean) {
                    return p;
                }
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getEastBoundSensor() == bean) {
                    return p;
                }
            }
        } else if (qobject_cast<SignalHead*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getEastBoundSignal()==(bean->getSystemName())
                        || p->getEastBoundSignal()==(bean->getSystemName())) {
                    return p;
                }
            }
        }
        return nullptr;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByWestBoundSignalMast(QString signalMastName) {
        for (int i = 0; i < layoutEditor->pointList->size(); i++) {
            PositionablePoint* p = layoutEditor->pointList->value(i);
            if (p->getWestBoundSignalMastName()==(signalMastName)) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByBean(NamedBean* bean) {
        if (qobject_cast<SignalMast*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getWestBoundSignalMast() == bean
                        || p->getEastBoundSignalMast() == bean) {
                    return p;
                }
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getWestBoundSensor() == bean
                        || p->getEastBoundSensor() == bean) {
                    return p;
                }
            }
        } else if (qobject_cast<SignalHead*>(bean)) {
            for (PositionablePoint* p : *layoutEditor->pointList) {
                if (p->getEastBoundSignal()==(bean->getSystemName())
                        || p->getWestBoundSignal()==(bean->getSystemName())) {

                    return p;
                }
                if (bean->getUserName() != NULL && (p->getEastBoundSignal()==(bean->getSystemName())
                        || p->getWestBoundSignal()==(bean->getSystemName()))) {
                    return p;
                }
            }
        }
        return nullptr;

    }

    /*public*/ LayoutTurnout* LayoutEditorFindItems::findLayoutTurnoutBySignalMast(QString signalMastName) {
        return findLayoutTurnoutByBean(static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(signalMastName));
    }

    /*public*/ LayoutTurnout* LayoutEditorFindItems::findLayoutTurnoutByBean(NamedBean* bean) {
        if (qobject_cast<SignalMast*>(bean)) {
            for (LayoutTurnout* t : *layoutEditor->turnoutList) {
                if (t->getSignalAMast() == bean
                        || t->getSignalBMast() == bean
                        || t->getSignalCMast() == bean
                        || t->getSignalDMast() == bean) {
                    return t;
                }
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            for (LayoutTurnout* t : *layoutEditor->turnoutList) {
                if (t->getSensorA() == bean
                        || t->getSensorB() == bean
                        || t->getSensorC() == bean
                        || t->getSensorD() == bean) {
                    return t;
                }
            }
        } else if (qobject_cast<SignalHead*>(bean)) {
            for (LayoutTurnout* t : *layoutEditor->turnoutList) {
                if (t->getSignalA1Name()==(bean->getSystemName())
                        || t->getSignalA2Name()==(bean->getSystemName())
                        || t->getSignalA3Name()==(bean->getSystemName())) {
                    return t;
                }

                if (t->getSignalB1Name()==(bean->getSystemName())
                        || t->getSignalB2Name()==(bean->getSystemName())) {
                    return t;
                }
                if (t->getSignalC1Name()==(bean->getSystemName())
                        || t->getSignalC2Name()==(bean->getSystemName())) {
                    return t;
                }
                if (t->getSignalD1Name()==(bean->getSystemName())
                        || t->getSignalD2Name()==(bean->getSystemName())) {
                    return t;
                }
                if (bean->getUserName() != NULL) {
                    if (t->getSignalA1Name()==(bean->getUserName())
                            || t->getSignalA2Name()==(bean->getUserName())
                            || t->getSignalA3Name()==(bean->getUserName())) {
                        return t;
                    }

                    if (t->getSignalB1Name()==(bean->getUserName())
                            || t->getSignalB2Name()==(bean->getUserName())) {
                        return t;
                    }
                    if (t->getSignalC1Name()==(bean->getUserName())
                            || t->getSignalC2Name()==(bean->getUserName())) {
                        return t;
                    }
                    if (t->getSignalD1Name()==(bean->getUserName())
                            || t->getSignalD2Name()==(bean->getUserName())) {
                        return t;
                    }
                }
            }
        } else if (qobject_cast<Turnout*>(bean)) {
            for (LayoutTurnout* t : *layoutEditor->turnoutList) {
                if (bean==(t->getTurnout())) {
                    return t;
                }
            }
        }
        return nullptr;
    }

    /*public*/ LayoutTurnout* LayoutEditorFindItems::findLayoutTurnoutBySensor(QString sensorName) {
        return findLayoutTurnoutByBean(InstanceManager::sensorManagerInstance()->provideSensor(sensorName));
    }

    /*public*/ LevelXing* LayoutEditorFindItems::findLevelXingBySignalMast(QString signalMastName) {
        return findLevelXingByBean(static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(signalMastName));
    }

    /*public*/ LevelXing* LayoutEditorFindItems::findLevelXingBySensor(QString sensorName) {
        return findLevelXingByBean(InstanceManager::sensorManagerInstance()->provideSensor(sensorName));
    }

    /*public*/ LevelXing* LayoutEditorFindItems::findLevelXingByBean(NamedBean* bean) {
        if (qobject_cast<SignalMast*>(bean)) {
            for (LevelXing* l : *layoutEditor->xingList) {
                if (l->getSignalAMast() == bean
                        || l->getSignalBMast() == bean
                        || l->getSignalCMast() == bean
                        || l->getSignalDMast() == bean) {
                    return l;
                }
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            for (LevelXing* l : *layoutEditor->xingList) {
                if (l->getSensorA() == bean
                        || l->getSensorB() == bean
                        || l->getSensorC() == bean
                        || l->getSensorD() == bean) {
                    return l;
                }
            }

        } else if (qobject_cast<SignalHead*>(bean)) {
            for (LevelXing* l : *layoutEditor->xingList) {
                if (l->getSignalAName()==(bean->getSystemName())
                        || l->getSignalBName()==(bean->getSystemName())
                        || l->getSignalCName()==(bean->getSystemName())
                        || l->getSignalDName()==(bean->getSystemName())) {
                    return l;
                }
                if (bean->getUserName() != NULL && (l->getSignalAName()==(bean->getUserName())
                        || l->getSignalBName()==(bean->getUserName())
                        || l->getSignalCName()==(bean->getUserName())
                        || l->getSignalDName()==(bean->getUserName()))) {
                    return l;
                }
            }
        }
        return NULL;
    }

    /*public*/ LayoutSlip* LayoutEditorFindItems::findLayoutSlipByBean(NamedBean* bean) {
        if (qobject_cast< SignalMast*>(bean)) {
            for (LayoutSlip* l : *layoutEditor->slipList) {
                if (l->getSignalAMast() == bean
                        || l->getSignalBMast() == bean
                        || l->getSignalCMast() == bean
                        || l->getSignalDMast() == bean) {
                    return l;
                }
            }
        } else if (qobject_cast<Sensor*>(bean)) {
            for (LayoutSlip* l : *layoutEditor->slipList) {
                if (l->getSensorA() == bean
                        || l->getSensorB() == bean
                        || l->getSensorC() == bean
                        || l->getSensorD() == bean) {
                    return l;
                }
            }
        } else if (qobject_cast<SignalHead*>(bean)) {
            for (LayoutSlip* l : *layoutEditor->slipList) {
                if (l->getSignalA1Name()==(bean->getSystemName())
                        || l->getSignalA2Name()==(bean->getSystemName())
                        || l->getSignalA3Name()==(bean->getSystemName())) {
                    return l;
                }

                if (l->getSignalB1Name()==(bean->getSystemName())
                        || l->getSignalB2Name()==(bean->getSystemName())) {
                    return l;
                }
                if (l->getSignalC1Name()==(bean->getSystemName())
                        || l->getSignalC2Name()==(bean->getSystemName())) {
                    return l;
                }
                if (l->getSignalD1Name()==(bean->getSystemName())
                        || l->getSignalD2Name()==(bean->getSystemName())) {
                    return l;
                }
                if (l->getSignalA1Name()==(bean->getUserName())
                        || l->getSignalA2Name()==(bean->getUserName())
                        || l->getSignalA3Name()==(bean->getUserName())) {
                    return l;
                }
                if (bean->getUserName() != NULL) {
                    if (l->getSignalB1Name()==(bean->getUserName())
                            || l->getSignalB2Name()==(bean->getUserName())) {
                        return l;
                    }
                    if (l->getSignalC1Name()==(bean->getUserName())
                            || l->getSignalC2Name()==(bean->getUserName())) {
                        return l;
                    }
                    if (l->getSignalD1Name()==(bean->getUserName())
                            || l->getSignalD2Name()==(bean->getUserName())) {
                        return l;
                    }
                }
            }
        } else if (qobject_cast<Turnout*>(bean)) {
            for (LayoutSlip* l : *layoutEditor->slipList) {
                if (bean==(l->getTurnout())) {
                    return l;
                }
                if (bean==(l->getTurnoutB())) {
                    return l;
                }
            }
        }
        return NULL;
    }

    /*public*/ LayoutSlip* LayoutEditorFindItems::findLayoutSlipBySignalMast(QString signalMastName) {
        return findLayoutSlipByBean(static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->provideSignalMast(signalMastName));
    }

    /*public*/ LayoutSlip* LayoutEditorFindItems::findLayoutSlipBySensor(QString sensorName) {
        return findLayoutSlipByBean(InstanceManager::sensorManagerInstance()->provideSensor(sensorName));
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByEastBoundSensor(QString sensorName) {
        for (int i = 0; i < layoutEditor->pointList->size(); i++) {
            PositionablePoint* p = layoutEditor->pointList->at(i);
            if (p->getEastBoundSensorName()==(sensorName)) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint* LayoutEditorFindItems::findPositionablePointByWestBoundSensor(QString sensorName) {
        for (int i = 0; i < layoutEditor->pointList->size(); i++) {
            PositionablePoint* p = layoutEditor->pointList->at(i);
            if (p->getWestBoundSensorName()==(sensorName)) {
                return p;
            }

        }
        return NULL;
    }

    /*public*/ LayoutTurnout* LayoutEditorFindItems::findLayoutTurnoutByName(QString name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor->turnoutList->size(); i++) {
            LayoutTurnout* t = layoutEditor->turnoutList->value(i);
            if (t->getName()==(name)) {
                return t;
            }
        }
        return nullptr;
    }

    /*public*/ LayoutTurnout* LayoutEditorFindItems::findLayoutTurnoutByTurnoutName(QString name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor->turnoutList->size(); i++) {
            LayoutTurnout* t = layoutEditor->turnoutList->at(i);
            if (t->getTurnoutName()==(name)) {
                return t;
            }
        }
        return NULL;
    }

    /*public*/ LevelXing* LayoutEditorFindItems::findLevelXingByName(QString name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor->xingList->size(); i++) {
            LevelXing* x = layoutEditor->xingList->at(i);
            if (x->getID()==(name)) {
                return x;
            }
        }
        return NULL;
    }

    /*public*/ LayoutSlip* LayoutEditorFindItems::findLayoutSlipByName(QString name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor->slipList->size(); i++) {
            LayoutSlip* x = layoutEditor->slipList->at(i);
            if (x->getName()==(name)) {
                return x;
            }
        }
        return NULL;
    }

    /*public*/ LayoutTurntable* LayoutEditorFindItems::findLayoutTurntableByName(QString name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor->turntableList->size(); i++) {
            LayoutTurntable* x = layoutEditor->turntableList->at(i);
            if (x->getID()==(name)) {
                return x;
            }
        }
        return NULL;
    }
#if 0
    /*public*/ Object findObjectByTypeAndName(int type, String name) {
        if (name.length() <= 0) {
            return NULL;
        }
        switch (type) {
            case LayoutEditor.NONE:
                return NULL;
            case LayoutEditor.POS_POINT:
                return findPositionablePointByName(name);
            case LayoutEditor.TURNOUT_A:
            case LayoutEditor.TURNOUT_B:
            case LayoutEditor.TURNOUT_C:
            case LayoutEditor.TURNOUT_D:
                return findLayoutTurnoutByName(name);
            case LayoutEditor.LEVEL_XING_A:
            case LayoutEditor.LEVEL_XING_B:
            case LayoutEditor.LEVEL_XING_C:
            case LayoutEditor.LEVEL_XING_D:
                return findLevelXingByName(name);
            case LayoutEditor.SLIP_A:
            case LayoutEditor.SLIP_B:
            case LayoutEditor.SLIP_C:
            case LayoutEditor.SLIP_D:
                return findLayoutSlipByName(name);
            case LayoutEditor.TRACK:
                return findTrackSegmentByName(name);
            default:
                if (type >= LayoutEditor.TURNTABLE_RAY_OFFSET) {
                    return findLayoutTurntableByName(name);
                }
        }
        log.error("did not find Object '" + name + "' of type " + type);
        return NULL;
    }
#endif
