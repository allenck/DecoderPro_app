#ifndef ANALOGFACTORY_EXPRESSIONS_H
#define ANALOGFACTORY_EXPRESSIONS_H

#include "analogexpressionfactory.h"

class AnalogFactory_Expressions : public QObject, public AnalogExpressionFactory
{
  Q_OBJECT
  Q_INTERFACES(AnalogExpressionFactory)
 public:
  AnalogFactory_Expressions(QObject* parent = nullptr) : QObject(parent){ setObjectName("AnalogFactory_Expressions");}
  /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString>> getClasses()override;

  QObject* self() override{return (QObject*)this;}
};

#endif // ANALOGFACTORY_EXPRESSIONS_H
