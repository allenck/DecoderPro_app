#ifndef ANALOGEXPRESSIONMANAGERTESTACTION_H
#define ANALOGEXPRESSIONMANAGERTESTACTION_H

#include <abstractaction.h>

class AnalogExpressionManagerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit AnalogExpressionManagerTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed(JActionEvent* =0)override;

 private:
  static Logger* log;
};

#endif // ANALOGEXPRESSIONMANAGERTESTACTION_H
