#ifndef ABSTRACTANALOGEXPRESSIONTESTBASE_H
#define ABSTRACTANALOGEXPRESSIONTESTBASE_H

#include "abstractbasetestbase.h"

class AbstractAnalogExpressionTestBase : public AbstractBaseTestBase
{
 public:
  explicit AbstractAnalogExpressionTestBase(QObject *parent = nullptr) : AbstractBaseTestBase(parent) {}
  /*public*/  /*abstract*/virtual NamedBean* createNewBean(QString systemName) /*throws Exception*/=0;

 public slots:
  /*public*/  void testBadSystemName() /*throws Exception*/;
  /*public*/  void testGetBeanType();
  /*public*/  void testState();
  /*public*/  void testEnableAndEvaluate() /*throws Exception*/;
  /*public*/  void testDebugConfig() /*throws Exception*/;
};

#endif // ABSTRACTANALOGEXPRESSIONTESTBASE_H
