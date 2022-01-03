#ifndef TRAINMANIFESTOPTIONACTION_H
#define TRAINMANIFESTOPTIONACTION_H

#include "abstractaction.h"
#include "trainmanifestoptionframe.h"
#include <QPointer>
#include "traineditframe.h"

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
  /*public*/ void actionPerformed(JActionEvent* e = 0);

 private:
  QPointer<TrainManifestOptionFrame> f;// = null;
  QPointer<TrainEditFrame> frame;// = null;

 };
}
#endif // TRAINMANIFESTOPTIONACTION_H
