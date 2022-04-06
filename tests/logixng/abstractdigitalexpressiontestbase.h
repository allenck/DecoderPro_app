#ifndef ABSTRACTDIGITALEXPRESSIONTESTBASE_H
#define ABSTRACTDIGITALEXPRESSIONTESTBASE_H

#include "abstractbasetestbase.h"

class AbstractDigitalExpressionTestBase : public AbstractBaseTestBase
{
 public:
  explicit AbstractDigitalExpressionTestBase(QObject *parent = nullptr) : AbstractBaseTestBase(parent) {}
  /*public*/  /*abstract*/virtual NamedBean* createNewBean(QString systemName) /*throws Exception*/=0;

 public slots:
  /*public*/  void testBadSystemName() /*throws Exception*/;
  /*public*/  void testGetBeanType();
  /*public*/  void testEnableAndEvaluate() /*throws Exception*/;
  /*public*/  void testDebugConfig() /*throws Exception*/;

};

#endif // ABSTRACTDIGITALEXPRESSIONTESTBASE_H
