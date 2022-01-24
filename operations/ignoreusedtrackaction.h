#ifndef IGNOREUSEDTRACKACTION_H
#define IGNOREUSEDTRACKACTION_H

#include "abstractaction.h"
#include "trackeditframe.h"

namespace Operations
{
 class IgnoreUsedTrackFrame;
 class IgnoreUsedTrackAction : public AbstractAction
 {
  Q_OBJECT
 public:
  IgnoreUsedTrackAction(TrackEditFrame* tef);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);
 private:
  /*private*/ QPointer<TrackEditFrame> _tef;
  /*private*/ QPointer<IgnoreUsedTrackFrame> _iutf;

 };
}
#endif // IGNOREUSEDTRACKACTION_H
