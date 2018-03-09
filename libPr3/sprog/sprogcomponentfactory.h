#ifndef SPROGCOMPONENTFACTORY_H
#define SPROGCOMPONENTFACTORY_H
#include "componentfactory.h"
#include "sprogsystemconnectionmemo.h"
#include <QMenu>

namespace Sprog
{
 class SprogComponentFactory : public ComponentFactory
 {
 public:
  SprogComponentFactory(SprogSystemConnectionMemo *memo, QObject* parent = 0);
  /*public*/ QMenu* getMenu(QWidget* frame);

 private:
  SprogSystemConnectionMemo* memo;

 };
}
#endif // SPROGCOMPONENTFACTORY_H
