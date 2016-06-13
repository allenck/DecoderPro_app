#ifndef TRACKCOPYACTION_H
#define TRACKCOPYACTION_H

#include "abstractaction.h"

namespace Operations
{
 class LocationEditFrame;
 class TrackCopyFrame;
 class TrackCopyAction : public AbstractAction
 {
 public:
  TrackCopyAction(LocationEditFrame* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  /*private*/ LocationEditFrame* _lef;
  TrackCopyFrame* f;// = null;

 };
}
#endif // TRACKCOPYACTION_H
