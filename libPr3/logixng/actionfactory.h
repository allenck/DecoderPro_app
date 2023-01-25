#ifndef ACTIONFACTORY_H
#define ACTIONFACTORY_H

#include "digitalactionfactory.h"

class ActionFactory : public QObject, public DigitalActionFactory
{
  Q_OBJECT
  Q_INTERFACES(DigitalActionFactory)
 public:
  ActionFactory(QObject* parent = nullptr) : QObject(parent){setObjectName("ActionFactory");}
  /*public*/  void init() override;
  /*public*/  QSet<QHash<Category, QString> > getActionClasses()override;

};

#endif // ACTIONFACTORY_H
