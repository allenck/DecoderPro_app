#include "layoutwyeview.h"
#include "layoutwyeeditor.h"
/**
 * MVC View component for the LayoutWye class.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
///*public*/ class LayoutWyeView extends LayoutTurnoutView {

    /**
     * Constructor method.
     * @param wye the wye to base view on.
     */
     /*public*/ LayoutWyeView::LayoutWyeView(/*@Nonnull*/ LayoutWye* wye,
            /*@Nonnull*/ QPointF c, double rot,
            double xFactor, double yFactor,
            /*@Nonnull*/ LayoutEditor* layoutEditor) : LayoutTurnoutView(wye, c, rot, xFactor, yFactor, layoutEditor){
        //super(wye, c, rot, xFactor, yFactor, layoutEditor);
        // this.wye = wye;

        editor = new LayoutWyeEditor(layoutEditor);
    }
    // final private LayoutWye wye;

    // private final static org.slf4j.Logger log = org.slf4j.LoggerFactory.getLogger(LayoutWyeView.class);
