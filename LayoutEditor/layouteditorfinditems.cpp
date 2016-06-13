#include "layouteditorfinditems.h"
#include "tracksegment.h"
#include "layouteditor.h"
#include "layoutturntable.h"
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
#if 0
    /*public*/ PositionablePoint findPositionablePointAtTrackSegments(TrackSegment tr1, TrackSegment tr2) {
        for (int i = 0; i < layoutEditor.pointList.size(); i++) {
            PositionablePoint p = layoutEditor.pointList.get(i);
            if (((p.getConnect1() == tr1) && (p.getConnect2() == tr2))
                    || ((p.getConnect1() == tr2) && (p.getConnect2() == tr1))) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint findPositionableLinkPoint(LayoutBlock blk1) {
        for (PositionablePoint p : layoutEditor.pointList) {
            if (p.getType() == PositionablePoint.EDGE_CONNECTOR) {
                if ((p.getConnect1() != NULL && p.getConnect1().getLayoutBlock() == blk1)
                        || (p.getConnect2() != NULL && p.getConnect2().getLayoutBlock() == blk1)) {
                    return p;
                }
            }
        }
        return NULL;
    }

    /**
     * Returns an array list of track segments matching the block name.
     */
    /*public*/ ArrayList<TrackSegment> findTrackSegmentByBlock(String name) {
        if (name.length() <= 0) {
            return NULL;
        }
        ArrayList<TrackSegment> ts = new ArrayList<TrackSegment>();
        for (int i = 0; i < layoutEditor.trackList.size(); i++) {
            TrackSegment t = layoutEditor.trackList.get(i);
            if (t.getBlockName()==(name)) {
                ts.add(t);
            }
        }
        return ts;
    }

    /*public*/ PositionablePoint findPositionablePointByEastBoundSignal(String signalName) {
        for (int i = 0; i < layoutEditor.pointList.size(); i++) {
            PositionablePoint p = layoutEditor.pointList.get(i);
            if (p.getEastBoundSignal()==(signalName)) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint findPositionablePointByWestBoundSignal(String signalName) {
        for (int i = 0; i < layoutEditor.pointList.size(); i++) {
            PositionablePoint p = layoutEditor.pointList.get(i);
            if (p.getWestBoundSignal()==(signalName)) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint findPositionablePointByWestBoundBean(NamedBean bean) {
        if (bean instanceof SignalMast) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getWestBoundSignalMast() == bean) {
                    return p;
                }
            }
        } else if (bean instanceof Sensor) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getWestBoundSensor() == bean) {
                    return p;
                }
            }
        } else if (bean instanceof SignalHead) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getWestBoundSignal()==(bean.getSystemName())
                        || p.getWestBoundSignal()==(bean.getSystemName())) {
                    return p;
                }
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint findPositionablePointByEastBoundBean(NamedBean bean) {
        if (bean instanceof SignalMast) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getEastBoundSignalMast() == bean) {
                    return p;
                }
            }
        } else if (bean instanceof Sensor) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getEastBoundSensor() == bean) {
                    return p;
                }
            }
        } else if (bean instanceof SignalHead) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getEastBoundSignal()==(bean.getSystemName())
                        || p.getEastBoundSignal()==(bean.getSystemName())) {
                    return p;
                }
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint findPositionablePointByWestBoundSignalMast(String signalMastName) {
        for (int i = 0; i < layoutEditor.pointList.size(); i++) {
            PositionablePoint p = layoutEditor.pointList.get(i);
            if (p.getWestBoundSignalMastName()==(signalMastName)) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint findPositionablePointByBean(NamedBean bean) {
        if (bean instanceof SignalMast) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getWestBoundSignalMast() == bean
                        || p.getEastBoundSignalMast() == bean) {
                    return p;
                }
            }
        } else if (bean instanceof Sensor) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getWestBoundSensor() == bean
                        || p.getEastBoundSensor() == bean) {
                    return p;
                }
            }
        } else if (bean instanceof SignalHead) {
            for (PositionablePoint p : layoutEditor.pointList) {
                if (p.getEastBoundSignal()==(bean.getSystemName())
                        || p.getWestBoundSignal()==(bean.getSystemName())) {

                    return p;
                }
                if (bean.getUserName() != NULL && (p.getEastBoundSignal()==(bean.getSystemName())
                        || p.getWestBoundSignal()==(bean.getSystemName()))) {
                    return p;
                }
            }
        }
        return NULL;

    }

    /*public*/ LayoutTurnout findLayoutTurnoutBySignalMast(String signalMastName) {
        return findLayoutTurnoutByBean(jmri.InstanceManager.signalMastManagerInstance().provideSignalMast(signalMastName));
    }

    /*public*/ LayoutTurnout findLayoutTurnoutByBean(NamedBean bean) {
        if (bean instanceof SignalMast) {
            for (LayoutTurnout t : layoutEditor.turnoutList) {
                if (t.getSignalAMast() == bean
                        || t.getSignalBMast() == bean
                        || t.getSignalCMast() == bean
                        || t.getSignalDMast() == bean) {
                    return t;
                }
            }
        } else if (bean instanceof Sensor) {
            for (LayoutTurnout t : layoutEditor.turnoutList) {
                if (t.getSensorA() == bean
                        || t.getSensorB() == bean
                        || t.getSensorC() == bean
                        || t.getSensorD() == bean) {
                    return t;
                }
            }
        } else if (bean instanceof SignalHead) {
            for (LayoutTurnout t : layoutEditor.turnoutList) {
                if (t.getSignalA1Name()==(bean.getSystemName())
                        || t.getSignalA2Name()==(bean.getSystemName())
                        || t.getSignalA3Name()==(bean.getSystemName())) {
                    return t;
                }

                if (t.getSignalB1Name()==(bean.getSystemName())
                        || t.getSignalB2Name()==(bean.getSystemName())) {
                    return t;
                }
                if (t.getSignalC1Name()==(bean.getSystemName())
                        || t.getSignalC2Name()==(bean.getSystemName())) {
                    return t;
                }
                if (t.getSignalD1Name()==(bean.getSystemName())
                        || t.getSignalD2Name()==(bean.getSystemName())) {
                    return t;
                }
                if (bean.getUserName() != NULL) {
                    if (t.getSignalA1Name()==(bean.getUserName())
                            || t.getSignalA2Name()==(bean.getUserName())
                            || t.getSignalA3Name()==(bean.getUserName())) {
                        return t;
                    }

                    if (t.getSignalB1Name()==(bean.getUserName())
                            || t.getSignalB2Name()==(bean.getUserName())) {
                        return t;
                    }
                    if (t.getSignalC1Name()==(bean.getUserName())
                            || t.getSignalC2Name()==(bean.getUserName())) {
                        return t;
                    }
                    if (t.getSignalD1Name()==(bean.getUserName())
                            || t.getSignalD2Name()==(bean.getUserName())) {
                        return t;
                    }
                }
            }
        } else if (bean instanceof Turnout) {
            for (LayoutTurnout t : layoutEditor.turnoutList) {
                if (bean==(t.getTurnout())) {
                    return t;
                }
            }
        }
        return NULL;
    }

    /*public*/ LayoutTurnout findLayoutTurnoutBySensor(String sensorName) {
        return findLayoutTurnoutByBean(jmri.InstanceManager.sensorManagerInstance().provideSensor(sensorName));
    }

    /*public*/ LevelXing findLevelXingBySignalMast(String signalMastName) {
        return findLevelXingByBean(jmri.InstanceManager.signalMastManagerInstance().provideSignalMast(signalMastName));
    }

    /*public*/ LevelXing findLevelXingBySensor(String sensorName) {
        return findLevelXingByBean(jmri.InstanceManager.sensorManagerInstance().provideSensor(sensorName));
    }

    /*public*/ LevelXing findLevelXingByBean(NamedBean bean) {
        if (bean instanceof SignalMast) {
            for (LevelXing l : layoutEditor.xingList) {
                if (l.getSignalAMast() == bean
                        || l.getSignalBMast() == bean
                        || l.getSignalCMast() == bean
                        || l.getSignalDMast() == bean) {
                    return l;
                }
            }
        } else if (bean instanceof Sensor) {
            for (LevelXing l : layoutEditor.xingList) {
                if (l.getSensorA() == bean
                        || l.getSensorB() == bean
                        || l.getSensorC() == bean
                        || l.getSensorD() == bean) {
                    return l;
                }
            }

        } else if (bean instanceof SignalHead) {
            for (LevelXing l : layoutEditor.xingList) {
                if (l.getSignalAName()==(bean.getSystemName())
                        || l.getSignalBName()==(bean.getSystemName())
                        || l.getSignalCName()==(bean.getSystemName())
                        || l.getSignalDName()==(bean.getSystemName())) {
                    return l;
                }
                if (bean.getUserName() != NULL && (l.getSignalAName()==(bean.getUserName())
                        || l.getSignalBName()==(bean.getUserName())
                        || l.getSignalCName()==(bean.getUserName())
                        || l.getSignalDName()==(bean.getUserName()))) {
                    return l;
                }
            }
        }
        return NULL;
    }

    /*public*/ LayoutSlip findLayoutSlipByBean(NamedBean bean) {
        if (bean instanceof SignalMast) {
            for (LayoutSlip l : layoutEditor.slipList) {
                if (l.getSignalAMast() == bean
                        || l.getSignalBMast() == bean
                        || l.getSignalCMast() == bean
                        || l.getSignalDMast() == bean) {
                    return l;
                }
            }
        } else if (bean instanceof Sensor) {
            for (LayoutSlip l : layoutEditor.slipList) {
                if (l.getSensorA() == bean
                        || l.getSensorB() == bean
                        || l.getSensorC() == bean
                        || l.getSensorD() == bean) {
                    return l;
                }
            }
        } else if (bean instanceof SignalHead) {
            for (LayoutSlip l : layoutEditor.slipList) {
                if (l.getSignalA1Name()==(bean.getSystemName())
                        || l.getSignalA2Name()==(bean.getSystemName())
                        || l.getSignalA3Name()==(bean.getSystemName())) {
                    return l;
                }

                if (l.getSignalB1Name()==(bean.getSystemName())
                        || l.getSignalB2Name()==(bean.getSystemName())) {
                    return l;
                }
                if (l.getSignalC1Name()==(bean.getSystemName())
                        || l.getSignalC2Name()==(bean.getSystemName())) {
                    return l;
                }
                if (l.getSignalD1Name()==(bean.getSystemName())
                        || l.getSignalD2Name()==(bean.getSystemName())) {
                    return l;
                }
                if (l.getSignalA1Name()==(bean.getUserName())
                        || l.getSignalA2Name()==(bean.getUserName())
                        || l.getSignalA3Name()==(bean.getUserName())) {
                    return l;
                }
                if (bean.getUserName() != NULL) {
                    if (l.getSignalB1Name()==(bean.getUserName())
                            || l.getSignalB2Name()==(bean.getUserName())) {
                        return l;
                    }
                    if (l.getSignalC1Name()==(bean.getUserName())
                            || l.getSignalC2Name()==(bean.getUserName())) {
                        return l;
                    }
                    if (l.getSignalD1Name()==(bean.getUserName())
                            || l.getSignalD2Name()==(bean.getUserName())) {
                        return l;
                    }
                }
            }
        } else if (bean instanceof Turnout) {
            for (LayoutSlip l : layoutEditor.slipList) {
                if (bean==(l.getTurnout())) {
                    return l;
                }
                if (bean==(l.getTurnoutB())) {
                    return l;
                }
            }
        }
        return NULL;
    }

    /*public*/ LayoutSlip findLayoutSlipBySignalMast(String signalMastName) {
        return findLayoutSlipByBean(jmri.InstanceManager.signalMastManagerInstance().provideSignalMast(signalMastName));
    }

    /*public*/ LayoutSlip findLayoutSlipBySensor(String sensorName) {
        return findLayoutSlipByBean(jmri.InstanceManager.sensorManagerInstance().provideSensor(sensorName));
    }

    /*public*/ PositionablePoint findPositionablePointByEastBoundSensor(String sensorName) {
        for (int i = 0; i < layoutEditor.pointList.size(); i++) {
            PositionablePoint p = layoutEditor.pointList.get(i);
            if (p.getEastBoundSensorName()==(sensorName)) {
                return p;
            }
        }
        return NULL;
    }

    /*public*/ PositionablePoint findPositionablePointByWestBoundSensor(String sensorName) {
        for (int i = 0; i < layoutEditor.pointList.size(); i++) {
            PositionablePoint p = layoutEditor.pointList.get(i);
            if (p.getWestBoundSensorName()==(sensorName)) {
                return p;
            }

        }
        return NULL;
    }

    /*public*/ LayoutTurnout findLayoutTurnoutByName(String name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor.turnoutList.size(); i++) {
            LayoutTurnout t = layoutEditor.turnoutList.get(i);
            if (t.getName()==(name)) {
                return t;
            }
        }
        return NULL;
    }

    /*public*/ LayoutTurnout findLayoutTurnoutByTurnoutName(String name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor.turnoutList.size(); i++) {
            LayoutTurnout t = layoutEditor.turnoutList.get(i);
            if (t.getTurnoutName()==(name)) {
                return t;
            }
        }
        return NULL;
    }

    /*public*/ LevelXing findLevelXingByName(String name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor.xingList.size(); i++) {
            LevelXing x = layoutEditor.xingList.get(i);
            if (x.getID()==(name)) {
                return x;
            }
        }
        return NULL;
    }

    /*public*/ LayoutSlip findLayoutSlipByName(String name) {
        if (name.length() <= 0) {
            return NULL;
        }
        for (int i = 0; i < layoutEditor.slipList.size(); i++) {
            LayoutSlip x = layoutEditor.slipList.get(i);
            if (x.getName()==(name)) {
                return x;
            }
        }
        return NULL;
    }
#endif
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
