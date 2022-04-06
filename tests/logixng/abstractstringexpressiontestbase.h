#ifndef ABSTRACTSTRINGEXPRESSIONTESTBASE_H
#define ABSTRACTSTRINGEXPRESSIONTESTBASE_H

#include "abstractbasetestbase.h"

class AbstractStringExpressionTestBase : public AbstractBaseTestBase
{
 public:
  explicit AbstractStringExpressionTestBase(QObject *parent = nullptr) : AbstractBaseTestBase(parent) {}
  /*public*/  /*abstract*/ virtual NamedBean* createNewBean(QString systemName) /*throws Exception*/=0;


 public slots:
  /*public*/  void testBadSystemName();
  /*public*/  void testGetBeanType();
  /*public*/  void testState() /*throws JmriException*/;
  /*public*/  void testEnableAndEvaluate() /*throws Exception*/;
  /*public*/  void testDebugConfig() /*throws Exception*/;

};

#endif // ABSTRACTSTRINGEXPRESSIONTESTBASE_H
