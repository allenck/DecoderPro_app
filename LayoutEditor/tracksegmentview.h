#ifndef TRACKSEGMENTVIEW_H
#define TRACKSEGMENTVIEW_H
#include "layouttrackview.h"
#include "tracksegment.h"

class TrackSegmentView : public LayoutTrackView
{
  Q_OBJECT
 public:
  /*public*/ TrackSegmentView(/*@Nonnull*/ TrackSegment* track);


 private:
  /*final*/ /*private*/ TrackSegment* trackSegment;

 protected:
  /*protected*/ bool isDashed();
friend class LayoutEditorComponent;
};

#endif // TRACKSEGMENTVIEW_H
