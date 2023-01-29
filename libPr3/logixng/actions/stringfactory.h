#ifndef STRINGFACTORY_H
#define STRINGFACTORY_H

#include "../stringactionfactory.h"
#include <QObject>
#include "../base.h"

namespace Actions
{

 class StringFactory : public QObject, public StringActionFactory
 {
   Q_OBJECT
   Q_INTERFACES(StringActionFactory)
  public:
   StringFactory(){}
   /*public*/ QSet<QHash<Category, QString> > getClasses();

 };
}
#endif // STRINGFACTORY_H
