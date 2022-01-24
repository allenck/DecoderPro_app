#include "layoutrhturnoutview.h"
#include "layoutrhturnout.h"

/**
 * MVC View component for the LayoutRHTurnout class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutRHTurnoutView extends LayoutTurnoutView {

    /**
     * Constructor method.
     * @param turnout the turnout to view.
     */
    /*public*/ LayoutRHTurnoutView::LayoutRHTurnoutView(/*@Nonnull*/ LayoutRHTurnout* turnout,
      /*@Nonnull*/ QPointF c, double rot,
      double xFactor, double yFactor,
      /*@Nonnull*/ LayoutEditor* layoutEditor)
    : LayoutTurnoutView(turnout, c, rot, xFactor, yFactor, layoutEditor){
        //super(turnout);
        // this.turnout = turnout;
    }

    // final private LayoutRHTurnout turnout;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutRHTurnoutView.class);
