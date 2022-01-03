#ifndef LOCATIONTRACKBLOCKINGORDERACTION_H
#define LOCATIONTRACKBLOCKINGORDERACTION_H

#include "abstractaction.h"
#include "locationtrackblockingorderframe.h"
#include <QPointer>
namespace Operations
{
 class Location;
 class LocationTrackBlockingOrderFrame;
 class LocationTrackBlockingOrderAction : public AbstractAction
 {
  Q_OBJECT
 public:
  LocationTrackBlockingOrderAction(QObject* parent);
  /*public*/ LocationTrackBlockingOrderAction(Location* location, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  Location* _location;

  QPointer<LocationTrackBlockingOrderFrame> _frame;// = null;
  void common();

 };
}
#endif // LOCATIONTRACKBLOCKINGORDERACTION_H
