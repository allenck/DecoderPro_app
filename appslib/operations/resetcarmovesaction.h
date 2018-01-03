#ifndef RESETCARMOVESACTION_H
#define RESETCARMOVESACTION_H
#include "abstractaction.h"

class Logger;
namespace Operations
{
 class CarManager;
 class ResetCarMovesAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ResetCarMovesAction(QString actionName, QWidget* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae = 0);
 private:
  CarManager* manager;// = CarManager.instance();
  Logger* log;
 };
}
#endif // RESETCARMOVESACTION_H
