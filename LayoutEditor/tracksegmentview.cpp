#include "tracksegmentview.h"

/**
 * MVC View component for the TrackSegment class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//public class TrackSegmentView extends LayoutTrackView {

    /**
     * constructor method.
     * @param track the track segment to view.
     */
    /*public*/ TrackSegmentView::TrackSegmentView(/*@Nonnull*/ TrackSegment* track) :  LayoutTrackView(track){
        //super(track);
        this->trackSegment = track;
    }


    /*protected*/ bool TrackSegmentView::isDashed() {
        return trackSegment->isDashed();
    }

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(TrackSegmentView.class);
