#ifndef STRINGFACTORY_H
#define STRINGFACTORY_H

#include "../stringexpressionfactory.h"
//#include <QDeclarativeItem>

namespace Expressions
{
class StringFactory : public QObject, public StringExpressionFactory
{
  Q_OBJECT
  Q_INTERFACES(StringExpressionFactory)
 public:
  StringFactory() {}
  /*public*/ QSet<QHash<Category, /*Class<? extends Base>*/QString>> getClasses() override;
 };
}
#endif // STRINGFACTORY_H
