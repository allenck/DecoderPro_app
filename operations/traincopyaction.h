#ifndef TRAINCOPYACTION_H
#define TRAINCOPYACTION_H

#include "abstractaction.h"
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
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  TrainCopyFrame* f;// = null;
  void common();
  Train* _train;// = null;
 };
}
#endif // TRAINCOPYACTION_H
