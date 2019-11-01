#ifndef MODIFYLOCATIONSCARLOADSACTION_H
#define MODIFYLOCATIONSCARLOADSACTION_H

#include "abstractaction.h"

namespace Operations
{
 class LocationsByCarLoadFrame;
 class Location;
 class ModifyLocationsCarLoadsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ ModifyLocationsCarLoadsAction(Location* location, QObject* parent);
  ModifyLocationsCarLoadsAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  Location* _location;
  LocationsByCarLoadFrame* f;// = null;

  void common();
 };
}
#endif // MODIFYLOCATIONSCARLOADSACTION_H
