#ifndef DIRECTCOMPONENTFACTORY_H
#define DIRECTCOMPONENTFACTORY_H

#include <componentfactory.h>
#include <QObject>
#include "directsystemconnectionmemo.h"

class DirectComponentFactory : public ComponentFactory
{
 public:
  explicit DirectComponentFactory(DirectSystemConnectionMemo* memo);
  /*public*/ QMenu* getMenu() override;

 private:
  DirectSystemConnectionMemo* memo;
};

#endif // DIRECTCOMPONENTFACTORY_H
