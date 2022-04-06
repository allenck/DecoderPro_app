#ifndef ABSTRACTSTRINGACTIONTESTBASE_H
#define ABSTRACTSTRINGACTIONTESTBASE_H

#include "abstractbasetestbase.h"

class AbstractStringActionTestBase : public AbstractBaseTestBase
{
 public:
  explicit AbstractStringActionTestBase(QObject *parent = nullptr) : AbstractBaseTestBase(parent) {}
  /*public*/  /*abstract*/ virtual NamedBean* createNewBean(QString systemName) /*throws Exception*/=0;

 public slots:
  /*public*/  void testBadSystemName();
  /*public*/  void testGetBeanType();
  /*public*/  void testState() /*throws JmriException*/;

};

#endif // ABSTRACTSTRINGACTIONTESTBASE_H
