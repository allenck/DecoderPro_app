#ifndef ANALOGFACTORY_H
#define ANALOGFACTORY_H

#include "analogexpressionfactory.h"
#include <QSet>

class Base;
class Category;
class AnalogFactory : public AnalogExpressionFactory
{
  Q_INTERFACES(AnalogExpressionFactory)
 public:
  AnalogFactory();
  /*public*/ const QSet<QMap<Category*, /*Class<? extends Base>*/Base*> > getClasses();
};

#endif // ANALOGFACTORY_H
