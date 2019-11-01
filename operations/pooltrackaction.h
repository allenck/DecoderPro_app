#ifndef POOLTRACKACTION_H
#define POOLTRACKACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrackEditFrame;
 class PoolTrackFrame;
 class PoolTrackAction : public AbstractAction
 {
  Q_OBJECT
 public:
  PoolTrackAction(TrackEditFrame* _tef);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  /*private*/ TrackEditFrame* _tef;
  /*private*/ PoolTrackFrame* _ptf;

 };
}
#endif // POOLTRACKACTION_H
