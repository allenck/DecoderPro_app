#ifndef EXPORTCARROSTERACTION_H
#define EXPORTCARROSTERACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ExportCarRosterAction : public AbstractAction
 {
 public:
  ExportCarRosterAction(QString actionName, QWidget* frame);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae = 0);

 };
}
#endif // EXPORTCARROSTERACTION_H
