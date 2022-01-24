#include "layoutdoubleslipview.h"
#include "layoutdoubleslipeditor.h"

/**
 * MVC View component for the LayoutDoubleSlipclass.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//public class LayoutDoubleSlipView extends LayoutSlipView {

    /**
     * Constructor method.
     * @param slip the layout double slip to view.
     */
     /*public*/ LayoutDoubleSlipView::LayoutDoubleSlipView(/*@Nonnull*/ LayoutDoubleSlip* slip, QPointF c, double rot, /*@Nonnull*/ LayoutEditor* layoutEditor)
       : LayoutSlipView(slip, c, rot, layoutEditor)
     {
        //super(slip, c, rot, layoutEditor);
        // this.slip = slip;

        editor = new LayoutDoubleSlipEditor(layoutEditor);
     }

    // final private LayoutDoubleSlip slip;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutDoubleSlipView.class);
