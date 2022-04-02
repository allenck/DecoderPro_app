#ifndef ABSTRACTDIGITALACTIONTESTBASE_H
#define ABSTRACTDIGITALACTIONTESTBASE_H

#include "abstractbasetestbase.h"

class AbstractDigitalActionTestBase : public AbstractBaseTestBase
{
 public:
  explicit AbstractDigitalActionTestBase(QObject *parent = nullptr) : AbstractBaseTestBase(parent) {}
  /*public*/  /*abstract*/virtual NamedBean* createNewBean(QString systemName)=0;

 public slots:
  /*public*/  void testBadSystemName();
  /*public*/  void testGetBeanType();


};

#endif // ABSTRACTDIGITALACTIONTESTBASE_H
