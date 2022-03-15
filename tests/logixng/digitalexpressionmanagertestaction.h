#ifndef DIGITALEXPRESSIONMANAGERTESTACTION_H
#define DIGITALEXPRESSIONMANAGERTESTACTION_H

#include <abstractaction.h>

class DigitalExpressionManagerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DigitalExpressionManagerTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed(JActionEvent* =0)override;

 private:
  static Logger* log;
};

#endif // DIGITALEXPRESSIONMANAGERTESTACTION_H
