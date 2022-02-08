#ifndef DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H
#define DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H

#include <QObject>
#include "femalesocketfactory.h"

class DefaultFemaleStringActionSocketFactory : public QObject, FemaleSocketFactory
{
  Q_OBJECT
 public:
  explicit DefaultFemaleStringActionSocketFactory(QObject *parent = nullptr);

 signals:

};

#endif // DEFAULTFEMALESTRINGACTIONSOCKETFACTORY_H
