#include "layoutlhturnoutview.h"
#include "layoutlhturnout.h"

/**
 * MVC View component for the LayoutLHTurnout class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutLHTurnoutView extends LayoutTurnoutView {

    /**
     * Constructor method.
     * @param turnout the layout left hand turnout to create view for.
     */
    /*public*/ LayoutLHTurnoutView::LayoutLHTurnoutView(/*@Nonnull*/ LayoutLHTurnout* turnout,
                                /*@Nonnull*/ QPointF c, double rot,
                                double xFactor, double yFactor,
                                /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTurnoutView(turnout, c, rot, xFactor, yFactor, layoutEditor) {
                            //super(turnout, c, rot, xFactor, yFactor, layoutEditor);

        // this.turnout = turnout;
    }

    // final private LayoutLHTurnout turnout;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutLHTurnoutView.class);
