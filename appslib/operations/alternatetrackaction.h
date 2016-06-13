#ifndef ALTERNATETRACKACTION_H
#define ALTERNATETRACKACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrackEditFrame;
 class AlternateTrackAction : public AbstractAction
 {
  Q_OBJECT
 public:
  AlternateTrackAction(TrackEditFrame* tef);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  /*private*/ TrackEditFrame* _tef;

 };
}
#endif // ALTERNATETRACKACTION_H
