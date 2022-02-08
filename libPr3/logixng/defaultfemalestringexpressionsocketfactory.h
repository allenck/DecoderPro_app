#ifndef DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H
#define DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"

class DefaultFemaleStringExpressionSocketFactory : public QObject, public FemaleSocketFactory
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketFactory)
 public:
  explicit DefaultFemaleStringExpressionSocketFactory(QObject *parent = nullptr);

 signals:

};

#endif // DEFAULTFEMALESTRINGEXPRESSIONSOCKETFACTORY_H
