#ifndef TRACKLOADEDITACTION_H
#define TRACKLOADEDITACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrackEditFrame;
 class TrackLoadEditFrame;
 class TrackLoadEditAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrackLoadEditAction(TrackEditFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);

 private:
  /*private*/ TrackEditFrame* _frame;
  /*private*/ TrackLoadEditFrame* tlef;// = null;

 };
}
#endif // TRACKLOADEDITACTION_H
