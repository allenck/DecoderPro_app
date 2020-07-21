#include "layoutturnoutview.h"

/**
 * MVC View component for the LayoutTurnout class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class LayoutTurnoutView extends LayoutTrackView {

    /**
     * Constructor method.
     * @param turnout the layout turnout to create the view for.
     */
    /*public*/ LayoutTurnoutView::LayoutTurnoutView(/*@Nonnull*/ LayoutTurnout* turnout) : LayoutTrackView(turnout) {
        //super(turnout);
        this->turnout = turnout;
    }


    // These now reflect to code in the base class; eventually this heirarchy will
    // expand and the code will be brought here

    /*protected*/ bool LayoutTurnoutView::isDisabled() {
        return turnout->isDisabled();
    }
    /*public*/ QPointF LayoutTurnoutView::getCoordsA() {
        return turnout->getCoordsA();
    }
    /*public*/ QPointF LayoutTurnoutView::getCoordsB() {
        return turnout->getCoordsB();
    }
    /*public*/ QPointF LayoutTurnoutView::getCoordsC() {
        return turnout->getCoordsC();
    }
    /*public*/ QPointF LayoutTurnoutView::getCoordsD() {
        return turnout->getCoordsD();
    }
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

    /*protected*/ void LayoutTurnoutView::drawTurnoutControls(EditScene* g2) {
        turnout->drawTurnoutControls(g2);
    }

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutTurnoutView.class);
