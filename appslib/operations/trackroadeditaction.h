#ifndef TRACKROADEDITACTION_H
#define TRACKROADEDITACTION_H

#include "abstractaction.h"

namespace Operations
{
 class TrackEditFrame;
 class TrackRoadEditFrame;
 class TrackRoadEditAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ TrackRoadEditAction(TrackEditFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* /*e*/);
 private:
  /*private*/ TrackEditFrame* _frame;
  /*private*/ TrackRoadEditFrame* tref;// = null;

 };
}
#endif // TRACKROADEDITACTION_H
