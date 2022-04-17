#ifndef ANALOGACTIONMANAGERTESTACTION_H
#define ANALOGACTIONMANAGERTESTACTION_H

#include <abstractaction.h>

class AnalogActionManagerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit AnalogActionManagerTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed(JActionEvent* =0)override;

 private:
  static Logger* log;
};

#endif // ANALOGACTIONMANAGERTESTACTION_H
