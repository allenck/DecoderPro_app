#ifndef LOCATIONCOPYACTION_H
#define LOCATIONCOPYACTION_H

#include "abstractaction.h"

namespace Operations
{
 class LocationCopyFrame;
 class LocationCopyAction : public AbstractAction
 {
  Q_OBJECT
 public:
  LocationCopyAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);
 private:
  LocationCopyFrame* f;// = null;

 };
}
#endif // LOCATIONCOPYACTION_H
