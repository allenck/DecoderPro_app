#ifndef EXPRESSIONFACTORY_H
#define EXPRESSIONFACTORY_H

#include <QObject>
#include "category.h"
#include "digitalexpressionfactory.h"

class ExpressionFactory : public QObject, public DigitalExpressionFactory
{
  Q_OBJECT
  Q_INTERFACES(DigitalExpressionFactory)
 public:
  explicit ExpressionFactory(QObject *parent = nullptr) : QObject(parent){setObjectName("ExpressionFactory");}
  /*public*/ /*static*/ /*final*/ class LocoNet : public Category {
      public:
      /*public*/ LocoNet() : Category("LOCONET", tr("LocoNet"), 1100){
          ;
      }
  };
  /*public*/ void init()override;
  /*public*/ QSet<QHash<Category, /*Class<? extends DigitalExpressionBean>*/QString>> getExpressionClasses()override;

 signals:

};

#endif // EXPRESSIONFACTORY_H
