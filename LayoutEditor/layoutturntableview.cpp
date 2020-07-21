#include "layoutturntableview.h"

/**
 * MVC View component for the LayoutTurntable class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//public class LayoutTurntableView extends LayoutTrackView {

    /**
     * Constructor method.
     * @param turntable the layout turntable to create view for.
     */
    /*public*/ LayoutTurntableView::LayoutTurntableView(/*@Nonnull*/ LayoutTurntable* turntable) : LayoutTrackView(turntable) {
        //super(turntable);
        this->turntable = turntable;
    }


    /*protected*/ void LayoutTurntableView::drawTurnoutControls(EditScene* g2) {
        turntable->drawTurnoutControls(g2);
    }

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutTurntableView.class);
