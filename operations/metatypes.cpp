#include "metatypes.h"

#include "routemanager.h"
#include "routemanagerxml.h"
#include "carcolors.h"

namespace Operations
{
bool Metatypes::done = false;
 Metatypes::Metatypes(QObject *parent) : QObject(parent)
 {
  // operations
  qRegisterMetaType<RouteManager>("RouteManager>");
  qRegisterMetaType<RouteManagerXml>("RouteManagerXml>");
  qRegisterMetaType<CarColors>("CarColors");

  Metatypes::done = true;
 }
}
