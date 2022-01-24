#ifndef DELETECARROSTERACTION_H
#define DELETECARROSTERACTION_H

#include "abstractaction.h"
class Logger;
namespace Operations
{
 class CarsTableFrame;
 class DeleteCarRosterAction : public AbstractAction
 {
 public:
  /*public*/ DeleteCarRosterAction(CarsTableFrame* carsTableFrame);
 public slots:
  /*public*/ void actionPerformed(JActionEvent *ae =0);

 private:
  Logger* log;
  CarsTableFrame* _carsTableFrame;
  void common();
 };
}
#endif // DELETECARROSTERACTION_H
