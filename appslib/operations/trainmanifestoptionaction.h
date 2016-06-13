#ifndef TRAINMANIFESTOPTIONACTION_H
#define TRAINMANIFESTOPTIONACTION_H

#include "abstractaction.h"
namespace Operations
{
 class TrainManifestOptionFrame;
 class TrainEditFrame;
 class TrainManifestOptionAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainManifestOptionAction(QString s, TrainEditFrame* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  TrainManifestOptionFrame* f;// = null;
  TrainEditFrame* frame;// = null;

 };
}
#endif // TRAINMANIFESTOPTIONACTION_H
