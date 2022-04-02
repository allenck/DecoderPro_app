#ifndef DEFAULTFEMALEGENERICEXPRESSIONSOCKET2_TESTACTION_H
#define DEFAULTFEMALEGENERICEXPRESSIONSOCKET2_TESTACTION_H

#include <abstractaction.h>

class DefaultFemaleGenericExpressionSocket2_TestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultFemaleGenericExpressionSocket2_TestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTFEMALEGENERICEXPRESSIONSOCKET2_TESTACTION_H
