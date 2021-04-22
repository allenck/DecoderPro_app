#include "layoutlhxoverview.h"
#include "layoutlhxovereditor.h"

/**
 * MVC View component for the LayoutLHXOver class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//public class LayoutLHXOverView extends LayoutXOverView {

    /**
     * Constructor method.
     * @param xover the layout left hand crossover to view.
     */
     /*public*/ LayoutLHXOverView::LayoutLHXOverView(/*@Nonnull*/ LayoutLHXOver* xover,
            /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor,
            /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutXOverView(xover, c, rot, xFactor, yFactor, layoutEditor) {
        //super(xover, c, rot, xFactor, yFactor, layoutEditor);
       // this.xover = xover;

        editor = new LayoutLHXOverEditor(layoutEditor);

    }

    // final private LayoutLHXOver xover;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutLHXOverView.class);
