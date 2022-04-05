#ifndef ACTIONFACTORY_LOCONET_H
#define ACTIONFACTORY_LOCONET_H

#include "digitalactionfactory.h"

class ActionFactory_LocoNet : public QObject, public DigitalActionFactory
{
  Q_OBJECT
  Q_INTERFACES(DigitalActionFactory)
 public:
  ActionFactory_LocoNet(QObject* parent = nullptr) : QObject(parent) {setObjectName("ActionFactory_LocoNet");}
  /*public*/  void init()override;
  /*public*/  QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> getActionClasses()override;

};

#endif // ACTIONFACTORY_LOCONET_H
