#ifndef EXPORTTRAINROSTERACTION_H
#define EXPORTTRAINROSTERACTION_H

#include "abstractaction.h"
namespace Operations
{
 class ExportTrainRosterAction : public AbstractAction
 {
 public:
  ExportTrainRosterAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* ae = 0);

 };
}
#endif // EXPORTTRAINROSTERACTION_H
