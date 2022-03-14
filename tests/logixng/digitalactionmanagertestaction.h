#ifndef DIGITALACTIONMANAGERTESTACTION_H
#define DIGITALACTIONMANAGERTESTACTION_H

#include <abstractaction.h>

class DigitalActionManagerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DigitalActionManagerTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed(JActionEvent* =0)override;

 private:
  static Logger* log;
};

#endif // DIGITALACTIONMANAGERTESTACTION_H
