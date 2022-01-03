#ifndef TRAINCOPYACTION_H
#define TRAINCOPYACTION_H

#include "abstractaction.h"
#include "traincopyframe.h"
#include <QPointer>

namespace Operations
{
 class Train;
 class TrainCopyFrame;
 class TrainCopyAction : public AbstractAction
 {
 public:
  TrainCopyAction(QString s, QObject* parent);
  TrainCopyAction(QString, Train*, QObject*);
 public slots:
  /*public*/ void actionPerformed(JActionEvent *e = 0);

 private:
  QPointer<TrainCopyFrame> f;// = null;
  void common();
  Train* _train;// = null;
 };
}
#endif // TRAINCOPYACTION_H
