#ifndef TRACKDESTINATIONEDITACTION_H
#define TRACKDESTINATIONEDITACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrackEditFrame;
 class TrackDestinationEditFrame;
 class TrackDestinationEditAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrackDestinationEditAction(TrackEditFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  /*private*/ TrackEditFrame* _frame;
  /*private*/ TrackDestinationEditFrame* tdef;// = null;

 };
}
#endif // TRACKDESTINATIONEDITACTION_H
