#ifndef DIGITALFACTORY_EXPRESSIONS_H
#define DIGITALFACTORY_EXPRESSIONS_H

#include "../digitalexpressionfactory.h"
#include <QWidget>

class DigitalFactory_Expressions : public QObject, public DigitalExpressionFactory
{
  Q_OBJECT
  Q_INTERFACES(DigitalExpressionFactory)
 public:
  DigitalFactory_Expressions(QObject* parent = nullptr) : QObject(parent) {setObjectName("DigitalFactory");}
  /*public*/ QSet<QHash<Category*, /*Class<? extends DigitalActionBean>*/QString>> getExpressionClasses() override;

};

#endif // DIGITALFACTORY_EXPRESSIONS_H
