#ifndef YARDMASTERFRAME_H
#define YARDMASTERFRAME_H

#include <QObject>
#include <operationsframe.h>
#include "appslib_global.h"

namespace Operations
{
 class Location;
 class APPSLIBSHARED_EXPORT YardmasterFrame : public OperationsFrame
 {
 public:
  YardmasterFrame(Location *location, QWidget* parent = 0);

 private:
  /*private*/ void initComponents(Location* location);

 };
}
#endif // YARDMASTERFRAME_H
