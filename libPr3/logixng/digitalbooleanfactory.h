#ifndef DIGITALBOOLEANFACTORY_H
#define DIGITALBOOLEANFACTORY_H

#include "digitalbooleanactionfactory.h"
#include "category.h"

class DigitalBooleanFactory : public QObject, public DigitalBooleanActionFactory
{
  Q_OBJECT
  Q_INTERFACES(DigitalBooleanActionFactory)
 public:
  DigitalBooleanFactory(QObject* parent = nullptr) : QObject(parent) {}
  /*public*/ QSet<QHash<Category*, /*Class<? extends Base>*/QString>> getClasses()override;

};

#endif // DIGITALBOOLEANFACTORY_H
