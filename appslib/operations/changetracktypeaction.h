#ifndef CHANGETRACKTYPEACTION_H
#define CHANGETRACKTYPEACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrackEditFrame;
 class ChangeTrackTypeAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ChangeTrackTypeAction(TrackEditFrame* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  /*private*/ TrackEditFrame* _tef;

 };
}
#endif // CHANGETRACKTYPEACTION_H
