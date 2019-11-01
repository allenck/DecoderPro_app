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
  /*public*/ DeleteCarRosterAction(QString actionName, QWidget* frame);
  /*public*/ DeleteCarRosterAction(CarsTableFrame* carsTableFrame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae);

 private:
  Logger* log;
  CarsTableFrame* _carsTableFrame;
  void common();
 };
}
#endif // DELETECARROSTERACTION_H
