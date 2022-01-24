#ifndef MODIFYLOCATIONSACTION_H
#define MODIFYLOCATIONSACTION_H
#include "abstractaction.h"
#include "appslib_global.h"
#include "locationsbycartypeframe.h"
#include <QPointer>

namespace Operations
{
 class Location;
 class LocationsByCarTypeFrame;
 class APPSLIBSHARED_EXPORT ModifyLocationsAction : public AbstractAction
 {
  Q_OBJECT
 public:
  ModifyLocationsAction(QObject* parent);
  /*public*/ ModifyLocationsAction(QString s, Location* location, QObject* parent);
  /*public*/ ModifyLocationsAction(QString s, QObject* parent);

 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0)override;

 private:
  void common();
  QPointer<LocationsByCarTypeFrame> f;// = null;
  Location* l;
 };
}
#endif // MODIFYLOCATIONSACTION_H
