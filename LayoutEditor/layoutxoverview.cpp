#include "layoutxoverview.h"
#include "layoutxovereditor.h"

/**
 * MVC View component for the LayoutXOver class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// public class LayoutXOverView extends LayoutTurnoutView {

    /**
     * Constructor method.
     * @param xover the layout crossover.
     */
     /*public*/ LayoutXOverView::LayoutXOverView(/*@Nonnull*/ LayoutXOver* xover,
            /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor,
            /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTurnoutView(xover, c, rot, xFactor, yFactor, layoutEditor) {
        //super(xover, c, rot, xFactor, yFactor, layoutEditor);
        // this.xover = xover;

        editor = new LayoutXOverEditor(layoutEditor);

    }

    // final private LayoutXOver xover;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutXOverView.class);
