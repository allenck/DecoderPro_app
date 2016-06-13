#ifndef LOCATIONSTABLEACTION_H
#define LOCATIONSTABLEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

namespace Operations
{
 class LocationsTableFrame;
 class APPSLIBSHARED_EXPORT LocationsTableAction : public AbstractAction
 {
  Q_OBJECT
 public:
  LocationsTableAction(QObject* parent);
  static LocationsTableFrame* f;// = null;
  /*public*/ LocationsTableAction(QString s, QObject* parent);

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  void common();
 };
}
#endif // LOCATIONSTABLEACTION_H
