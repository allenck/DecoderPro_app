#ifndef EXPORTCARROSTERACTION_H
#define EXPORTCARROSTERACTION_H

#include "abstractaction.h"
#include "carstableframe.h"

namespace Operations
{
 class ExportCarRosterAction : public AbstractAction
 {
 public:
  ExportCarRosterAction(CarsTableFrame* carsTableFrame);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* ae = 0);

  private:
  CarsTableFrame* _carsTableFrame;
 };
}
#endif // EXPORTCARROSTERACTION_H
