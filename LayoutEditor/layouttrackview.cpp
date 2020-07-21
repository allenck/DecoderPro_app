#include "layouttrackview.h"
#include "loggerfactory.h"
#include "layoutrhturnout.h"
#include "layoutlhturnout.h"
#include "layoutwye.h"
#include "layoutxover.h"
#include "layoutrhxover.h"
#include "layoutlhxover.h"
#include "layoutrhturnoutview.h"
#include "layoutlhturnoutview.h"
#include "layoutwyeview.h"
#include "layoutrhxoverview.h"
#include "layoutdoublexover.h"
#include "layoutxoverview.h"
#include "layoutlhxoverview.h"
#include "layoutdoublexoverview.h"
#include "layoutslip.h"
#include "layoutsingleslip.h"
#include "layoutdoubleslip.h"
#include "layoutslipview.h"
#include "layoutsingleslipview.h"
#include "layoutdoubleslipview.h"
#include "tracksegment.h"
#include "tracksegmentview.h"
#include "tracksegmentview.h"
#include "levelxingview.h"
#include "positionablepointview.h"
#include "layoutturntableview.h"

/**
 * MVC View component for the LayoutTrack hierarchy.
 *
 * @author Bob Jacobsen  Copyright (c) 2020
 *
 */
// /*public*/ class LayoutTrackView {

    /**
     * Constructor method.
     * @param track the layout track to view.
     */
    /*public*/ LayoutTrackView::LayoutTrackView(/*@Nonnull*/ LayoutTrack* track) {
         this->layoutTrack = track;
    }

    // temporary method to get a correct-type *View or subclass.
    // Eventually, this will go away once *View's are created
    // in a type-specific way with their underlying model objects
    // @Deprecated // should be made not necessary
    /*@Nonnull*/
    /*static*/ /*public*/ LayoutTrackView* LayoutTrackView::makeTrackView(/*@Nonnull*/ LayoutTrack* trk) {

        if (qobject_cast<LayoutTurnout*>(trk)) {

            if (qobject_cast<LayoutRHTurnout*>(trk)) { return new LayoutRHTurnoutView((LayoutRHTurnout*)trk); }
            if (qobject_cast<LayoutLHTurnout*>(trk)) { return new LayoutLHTurnoutView((LayoutLHTurnout*)trk); }
            if (qobject_cast<LayoutWye*>(trk)) { return new LayoutWyeView((LayoutWye*)trk); }

            if (qobject_cast<LayoutXOver*>(trk)) {
                if (qobject_cast<LayoutRHXOver*>(trk)) { return new LayoutRHXOverView((LayoutRHXOver*)trk); }
                if (qobject_cast<LayoutLHXOver*>(trk)) { return new LayoutLHXOverView((LayoutLHXOver*)trk); }
                if (qobject_cast<LayoutDoubleXOver*>(trk)) { return new LayoutDoubleXOverView((LayoutDoubleXOver*)trk); }

                return new LayoutXOverView((LayoutXOver*)trk);
            }

            if (qobject_cast<LayoutSlip*>(trk)) {
                if (qobject_cast<LayoutSingleSlip*>(trk)) { return new LayoutSingleSlipView((LayoutSingleSlip*)trk); }
                if (qobject_cast<LayoutDoubleSlip*>(trk)) { return new LayoutDoubleSlipView((LayoutDoubleSlip*)trk); }

                return new LayoutSlipView((LayoutSlip*)trk);
            }

            return new LayoutTurnoutView((LayoutTurnout*)trk);
        }
        if (qobject_cast<TrackSegment*>(trk)) { return new TrackSegmentView((TrackSegment*)trk); }
        if (qobject_cast<PositionablePoint*>(trk)) { return new PositionablePointView((PositionablePoint*)trk); }
        if (qobject_cast<LevelXing*>(trk)) { return new LevelXingView((LevelXing*)trk); }
        if (qobject_cast<LayoutTurntable*>(trk)) { return new LayoutTurntableView((LayoutTurntable*)trk); }

        log->error(tr("makeTrackView did not match type of %1").arg(trk->metaObject()->className()),  Exception("traceback"));
        return new LayoutTrackView(trk);
    }


    // These now reflect to code in the base class; eventually this heirarchy will
    // expand and the code will be brought here

    /*public*/ bool LayoutTrackView::hasDecorations() {
        return layoutTrack->hasDecorations();
    }
    /*final*/ /*public*/ QPointF LayoutTrackView::getCoordsCenter() { // final for efficiency
        return layoutTrack->getCoordsCenter();
    }
    /*@Nonnull*/
    /*final*/ /*public*/ QString LayoutTrackView::getId() {
        return layoutTrack->getId();
    }
    /*@Nonnull*/
    /*final*/ /*public*/ QString LayoutTrackView::getName() {
        return layoutTrack->getName();
    }
    /*public*/ QMap<QString, QString>* LayoutTrackView::getDecorations() {
        return layoutTrack->getDecorations();
    }
    /*public*/ bool LayoutTrackView::isMainline() {
        return layoutTrack->isMainline();
    }

    /*protected*/ void LayoutTrackView::drawEditControls(EditScene* g2) {
        layoutTrack->drawEditControls(g2);
    }

    /*protected*/ void LayoutTrackView::draw1(EditScene *g2, bool isMain, bool isBlock) {
        layoutTrack->draw1(g2, isMain, isBlock);
    }

    /*protected*/ void LayoutTrackView::draw2(EditScene* g2, bool isMain, float railDisplacement) {
        layoutTrack->draw2(g2, isMain, railDisplacement);
    }

    /*protected*/ void LayoutTrackView::drawDecorations(EditScene* g2) {
        layoutTrack->drawDecorations(g2);
    }

    /*public*/ bool LayoutTrackView::isHidden() {
        return layoutTrack->isHidden();
    }

    /*private*/ /*final*/ /*static*/ Logger* LayoutTrackView::log = LoggerFactory::getLogger("LayoutTrackView");
