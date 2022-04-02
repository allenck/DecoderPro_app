#ifndef DEFAULTFEMALEGENERICEXPRESSIONSOCKET1_TESTACTION_H
#define DEFAULTFEMALEGENERICEXPRESSIONSOCKET1_TESTACTION_H

#include <abstractaction.h>

class DefaultFemaleGenericExpressionSocket1_TestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultFemaleGenericExpressionSocket1_TestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTFEMALEGENERICEXPRESSIONSOCKET1_TESTACTION_H
