#ifndef STRINGFACTORY_H
#define STRINGFACTORY_H

#include "stringexpressionfactory.h"
#include <QObject>

class StringFactory : public QObject, public StringExpressionFactory
{
  Q_OBJECT
  Q_INTERFACES(StringExpressionFactory)
 public:
  StringFactory(QObject* parent = nullptr) : QObject(parent) {setObjectName("StringFactory");}
  /*public*/ QSet<QHash<Category*, /*Class<? extends Base>*/QString>> getClasses();

};

#endif // STRINGFACTORY_H
