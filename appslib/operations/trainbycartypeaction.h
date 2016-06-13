#ifndef TRAINBYCARTYPEACTION_H
#define TRAINBYCARTYPEACTION_H

#include "abstractaction.h"
namespace Operations
{
 class Train;
 class TrainByCarTypeAction : public AbstractAction
 {
  Q_OBJECT
 public:
  TrainByCarTypeAction(QString s, Train* train,QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);

 private:
  Train* _train;

 };
}
#endif // TRAINBYCARTYPEACTION_H
