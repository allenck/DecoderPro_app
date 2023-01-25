#ifndef ANALOGFACTORY_H
#define ANALOGFACTORY_H

#include "analogexpressionfactory.h"
#include <QSet>

class Base;
class Category;
class AnalogFactory : public QObject, public AnalogExpressionFactory
{
  Q_OBJECT
  Q_INTERFACES(AnalogExpressionFactory)
 public:
  AnalogFactory(QObject* parent = nullptr) : QObject(parent) { setObjectName("AnalogFactory");}
  /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString> > getClasses()override;

  QObject* self() override {return (QObject*)this;}

};

#endif // ANALOGFACTORY_H
