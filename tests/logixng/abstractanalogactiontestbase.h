#ifndef ABSTRACTANALOGACTIONTESTBASE_H
#define ABSTRACTANALOGACTIONTESTBASE_H

#include "abstractbasetestbase.h"

class AbstractAnalogActionTestBase : public AbstractBaseTestBase
{
 public:
  explicit AbstractAnalogActionTestBase(QObject *parent = nullptr) : AbstractBaseTestBase(parent) {}
  /*public*/ /*abstract*/ virtual  NamedBean* createNewBean(QString systemName) /*throws Exception*/=0;

 public slots:
  /*public*/ void testBadSystemName() /*throws Exception */;
  /*public*/ void testGetBeanType();
  /*public*/ void testState() /*throws JmriException*/;
};

#endif // ABSTRACTANALOGACTIONTESTBASE_H
