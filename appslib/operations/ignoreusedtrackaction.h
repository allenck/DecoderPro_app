#ifndef IGNOREUSEDTRACKACTION_H
#define IGNOREUSEDTRACKACTION_H

#include "abstractaction.h"

namespace Operations
{
 class TrackEditFrame;
 class IgnoreUsedTrackFrame;
 class IgnoreUsedTrackAction : public AbstractAction
 {
  Q_OBJECT
 public:
  IgnoreUsedTrackAction(TrackEditFrame* tef);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  /*private*/ TrackEditFrame* _tef;
  /*private*/ IgnoreUsedTrackFrame* _iutf;

 };
}
#endif // IGNOREUSEDTRACKACTION_H
