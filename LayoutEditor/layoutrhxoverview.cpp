#include "layoutrhxoverview.h"
#include "layoutrhxovereditor.h"

/**
 * MVC View component for the LayoutRHXOver class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutRHXOverView extends LayoutXOverView {

    /**
     * Constructor method.
     * @param xover the layout right hand crossover to view.
     */
     /*public*/ LayoutRHXOverView::LayoutRHXOverView(/*@Nonnull*/ LayoutRHXOver* xover,
            /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor,
            /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutXOverView(xover, c, rot, xFactor, yFactor, layoutEditor) {
       // super(xover, c, rot, xFactor, yFactor, layoutEditor);
        // this.xover = xover;
    editor = new LayoutRHXOverEditor(layoutEditor);

    }

    // final private LayoutRHXOver xover;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutRHXOverView.class);
