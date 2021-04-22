#ifndef LAYOUTMODELS_H
#define LAYOUTMODELS_H
#include "layoutturnoutview.h"
//#include "layouteditorauxtools.h"
//#include "path.h"
//#include "layoutslip.h"
//#include "tracksegmentview.h"
//#include "levelxingview.h"
//#include "layouttrack.h"
//#include "layouttrackview.h"
//#include "layoutturntableview.h"
//#include "positionablepointview.h"
//#include "layoutshape.h"
//#include "tracksegmentview.h"
#include <QList>
#include "path.h"


class LayoutShape;
//class LayoutTurnoutView;
class LayoutTurntableView;
class LayoutTrack;
class LayoutTrackView;
class LayoutTurntable;
class LevelXing;
class LayoutTurnout;
class TrackSegment;
class LayoutSlip;
class LayoutEditorAuxTools;
class PositionablePointView;
class PositionablePoint;
class LevelXingView;
class TrackSegmentView;
/**
 * This interface serves as a manager for the overall layout model via
 * collections of i.e. LayoutTurnout, LayoutBlock,
 * PositionablePoint, Track Segment, LayoutSlip and LevelXing objects
 * along with their corresponding *View objects.
 * (Having *View objects here, which are specific to a panel, may
 * only be here as a temporary measure)
 * <p>
 * Provides a temporary setDirty()/isDirty() and redrawPanel() mechanism
 * for marking changes. That may have to grow and/or change. For
 * example, redrawPanel()  (which could be renamed) might fire listeners to cause repaints.
 *
 *
 * @see LayoutEditorFindItems
 * @see LayoutEditorAuxTools
 *
 * @author Bob Jacobsen Copyright: (c) 2020
 */
/*public*/ /*interface*/class LayoutModels {

 public:
    /**
     * Check the dirty state
     *
     * @return true if contents of models have changed,
     */
    /*public*/ virtual bool isDirty()=0;

    /*public*/ virtual void setDirty() =0;

    /**
     * A change has happen that might not need to be stored,
     * but should cause the presentation to be updated.
     */
    /*public*/ virtual void redrawPanel() =0;

    // ====================================
    // Access to related navigation objects
    // ====================================

    ///*@Nonnull*/
    /*public*/ virtual LayoutEditorAuxTools* getLEAuxTools() =0;


    // ====================================
    // Access to (lists of) model objects
    // ====================================

    //
    // General access. (temporary) Is this actually preferred to all those specific ones?
    //
#if 0
    /*@Nonnull*/
    Stream<LayoutTrack> getLayoutTracksOfClass(Class<? extends LayoutTrack> layoutTrackClass);

    //
    // General access. (temporary) Is this actually preferred to all those specific ones?
    //

    /*@Nonnull*/
    Stream<LayoutTrackView> getLayoutTrackViewsOfClass(Class<? extends LayoutTrackView> layoutTrackViewClass);
#endif
    /*@Nonnull*/
    virtual QList<PositionablePointView*> getPositionablePointViews() {};

    /*@Nonnull*/
    virtual QList<PositionablePoint*> getPositionablePoints() = 0;

    /*@Nonnull*/
    virtual QList<LayoutSlip*> getLayoutSlips() = 0;

    /*@Nonnull*/
    virtual QList<TrackSegmentView*> getTrackSegmentViews() = 0;

    /*@Nonnull*/
    virtual QList<TrackSegment*> getTrackSegments() = 0;

    /*@Nonnull*/
    virtual QList<LayoutTurnout*> getLayoutTurnouts() = 0;

    /*@Nonnull*/
    virtual QList<LayoutTurntable*> getLayoutTurntables() = 0;

    /*@Nonnull*/
    virtual QList<LevelXing*> getLevelXings() = 0;

    /*@Nonnull*/
    virtual QList<LevelXingView*> getLevelXingViews() = 0;

    /**
     * Read-only access to the list of LayoutTrack family objects.
     * The returned list will throw UnsupportedOperationException
     * if you attempt to modify it.
     * @return unmodifiable copy of layout track list.
     */
    /*@Nonnull*/
    virtual QList<LayoutTrack*> getLayoutTracks() = 0;

    /**
     * Read-only access to the list of LayoutTrackView family objects.
     * The returned list will throw UnsupportedOperationException
     * if you attempt to modify it.
     * @return unmodifiable copy of track views.
     */
    /*@Nonnull*/
    virtual QList<LayoutTrackView*> getLayoutTrackViews() = 0;

    // temporary
    virtual LayoutTrackView* getLayoutTrackView(LayoutTrack* trk) = 0;

    // temporary
    virtual LevelXingView* getLevelXingView(LevelXing* xing) = 0;

    // temporary
    virtual LayoutTurnoutView* getLayoutTurnoutView(LayoutTurnout* to) = 0;

    // temporary
    virtual LayoutTurntableView* getLayoutTurntableView(LayoutTurntable* to) = 0;

    // temporary
    virtual TrackSegmentView* getTrackSegmentView(TrackSegment* to);

    // temporary
    virtual PositionablePointView* getPositionablePointView(const PositionablePoint* to) = 0;

    /**
     * Add a LayoutTrack and LayoutTrackView to the list of
     * LayoutTrack family objects.
     * @param trk to be stored
     * @param v corresponding view
     */
    virtual void addLayoutTrack(/*@Nonnull*/ LayoutTrack* trk, /*@Nonnull*/ LayoutTrackView* v) = 0;

    /**
     * If item present, delete from the list of LayoutTracks
     * and force a dirty redraw.
     * @param trk the layout track to remove.
     */
    virtual void removeLayoutTrack(/*@Nonnull*/ LayoutTrack* trk) = 0;

    /*@Nonnull*/
    virtual QList<LayoutTurnout*> getLayoutTurnoutsAndSlips() = 0;

    /*@Nonnull*/
    virtual QList<LayoutShape*> getLayoutShapes() = 0;

    /**
     * Compute octagonal direction of vector from p1 to p2.
     * <p>
     * The octagonal (8) directions are: North, North-East, East,
     * South-East, South, South-West, West and North-West; see
     * {@link jmri.Path} for more on this.
     *
     * <p>
     * This method must eventually be in terms _other_ than
     * the screen geometry of the associated LayoutTrackView objects,
     * as it's meant to be the track connectivity direction not the
     * on the screen implementation.
     *
     * @param trk1 track at "from" end
     * @param h1 the hit point for "from" end
     * @param trk2 the track at the "to" end
     * @param h2 the hit at the "to" end
     * @return the octagonal direction from p1 to p2
     */
    /*public*/ virtual int computeDirection(/*@Nonnull*/ LayoutTrack* trk1, /*@Nonnull*/ HitPointType::TYPES h1,
                                /*@Nonnull*/ LayoutTrack* trk2, /*@Nonnull*/ HitPointType::TYPES h2) =0;

    /*public*/ virtual int computeDirectionToCenter( /*@Nonnull*/ LayoutTrack* trk1, /*@Nonnull*/ HitPointType::TYPES h1, /*@Nonnull*/ PositionablePoint* p)=0;

    /*public*/ virtual int computeDirectionFromCenter(const /*@Nonnull*/ PositionablePoint* p, /*@Nonnull*/ LayoutTrack* trk1, /*@Nonnull*/ HitPointType::TYPES h1)=0;

    /*default*/ /*public*/ virtual int computeDirectionAB( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsA(), tv->getCoordsB());
    }

    /*default*/ /*public*/ virtual int computeDirectionAC( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsA(), tv->getCoordsC());
    }

    /*default*/ /*public*/ virtual int computeDirectionAD( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsA(), tv->getCoordsD());
    }

    /*default*/ /*public*/ virtual int computeDirectionBC( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsB(), tv->getCoordsC());
    }

    /*default*/ /*public*/ virtual int computeDirectionBD( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsB(), tv->getCoordsD());
    }

    /*default*/ /*public*/ virtual int computeDirectionCD( /*@Nonnull*/ LayoutTurnout* track) {
        LayoutTurnoutView* tv = getLayoutTurnoutView(track);
        return Path::computeDirection(tv->getCoordsC(), tv->getCoordsD());
    }

    /**
     * Invoked to display a warning about removal.
     * Lists the attached items that prevent removing the layout track item.
     * <p>
     * The default implementation refers this to a View object for displaying a Dialog.
     *
     * @param track The involved track
     * @param itemList A list of the attached heads, masts and/or sensors.
     * @param typeKey  The object type such as Turnout, Level Crossing, etc.
     */
    /*default*/ /*public*/ virtual void displayRemoveWarning(LayoutTrack* track, QList<QString> itemList, QString typeKey) {
        getLayoutTrackView(track)->displayRemoveWarningDialog(itemList, typeKey);
    }
};
Q_DECLARE_INTERFACE(LayoutModels, "LayoutModels")
#endif // LAYOUTMODELS_H
