#include "segment.h"
#include "timetabledatamanager.h"
namespace TimeTable
{

/**
 * Define the content of a Segment record.
 *
 * @author Dave Sand Copyright (C) 2018
 */
// /*public*/ class Segment {

    /**
     * Create a new segment with default values.
     * @param layoutId The parent layout id.
     * @throws IllegalArgumentException SEGMENT_ADD_FAIL
     */
    /*public*/ Segment::Segment(int layoutId, QObject *parent) : QObject(parent) {
        _dm = TimeTableDataManager::getDataManager();
        if (_dm->getLayout(layoutId) == nullptr) {
            throw  IllegalArgumentException(TimeTableDataManager::SEGMENT_ADD_FAIL);
        }
        _segmentId = _dm->getNextId("Segment");  // NOI18N
        _layoutId = layoutId;
        _dm->addSegment(_segmentId, this);
    }

    /*public*/ Segment::Segment(int segmentId, int layoutId, QString segmentName, QObject *parent) : QObject(parent) {
       _dm = TimeTableDataManager::getDataManager();
       _segmentId = segmentId;
        _layoutId = layoutId;
        setSegmentName(segmentName);
    }


    /*public*/ int Segment::getSegmentId() {
        return _segmentId;
    }

    /*public*/ int Segment::getLayoutId() {
        return _layoutId;
    }

    /*public*/ QString Segment::getSegmentName() {
        return _segmentName;
    }

    /*public*/ void Segment::setSegmentName(QString newName) {
        _segmentName = newName;
    }

    //@Override
    /*public*/ QString Segment::toString() {
        return _segmentName;
    }
}
