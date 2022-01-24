#include "layoutsingleslipview.h"
#include "layoutsingleslipeditor.h"
/**
 * MVC View component for the LayoutSingleSlip class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
//public class LayoutSingleSlipView extends LayoutSlipView {

    /**
     * Constructor method.
     * @param slip the slip to create view for.
     */
     /*public*/ LayoutSingleSlipView::LayoutSingleSlipView(/*@Nonnull*/ LayoutSingleSlip* slip, QPointF c, double rot, /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutSlipView(slip, c, rot, layoutEditor) {
        //super(slip, c, rot, layoutEditor);
        // this.slip = slip;

        editor = new LayoutSingleSlipEditor(layoutEditor);

    }

    // final private LayoutSingleSlip slip;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutSingleSlipView.class);

