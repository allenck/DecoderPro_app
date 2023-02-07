#ifndef ANALOGEXPRESSIONCONSTANTTESTACTION_H
#define ANALOGEXPRESSIONCONSTANTTESTACTION_H

#include <abstractaction.h>

class AnalogExpressionConstantTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  AnalogExpressionConstantTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ANALOGEXPRESSIONCONSTANTTESTACTION_H
