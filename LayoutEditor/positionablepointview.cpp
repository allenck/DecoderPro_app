#include "positionablepointview.h"

/**
 * MVC View component for the PositionablePoint class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//public class PositionablePointView extends LayoutTrackView {

    /**
     * constructor method.
     * @param point the positionable point.
     */
    /*public*/ PositionablePointView::PositionablePointView(/*@Nonnull*/ PositionablePoint* point) : LayoutTrackView(point) {
        //super(point);
        this->positionablePoint = point;
    }


    // These now reflect to code in the base class; eventually this heirarchy will
    // expand and the code will be brought here

    //@Override
    /*protected*/ void PositionablePointView::draw1(EditScene* g2, bool isMain, bool isBlock) {
        positionablePoint->draw1(g2, isMain, isBlock, LayoutTrack::ITEMTYPE::points);
    }

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(PositionablePointView.class);
