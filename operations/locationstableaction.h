#ifndef LOCATIONSTABLEACTION_H
#define LOCATIONSTABLEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"
#include "locationstableframe.h"
#include <QPointer>

namespace Operations
{
 class LocationsTableFrame;
 class APPSLIBSHARED_EXPORT LocationsTableAction : public AbstractAction
 {
  Q_OBJECT
 public:
  LocationsTableAction(QObject* parent);
  static QPointer<LocationsTableFrame> f;// = null;
  /*public*/ LocationsTableAction(QString s, QObject* parent);

 public slots:
  /*public*/ void actionPerformed(JActionEvent *e = 0);
 private:
  void common();
 };
}
#endif // LOCATIONSTABLEACTION_H
