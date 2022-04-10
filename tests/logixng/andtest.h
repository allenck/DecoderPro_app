#ifndef ANDTEST_H
#define ANDTEST_H

#include "abstractdigitalexpressiontestbase.h"

class AndTest : public AbstractDigitalExpressionTestBase
{
  Q_OBJECT
 public:
  explicit AndTest(QObject *parent = nullptr);

 private:
  /*private*/ LogixNG* logixNG;
  /*private*/ ConditionalNG* conditionalNG;

};

#endif // ANDTEST_H
