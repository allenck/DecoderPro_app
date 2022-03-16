#ifndef DIGITALBOOLEANACTIONMANAGERTESTACTION_H
#define DIGITALBOOLEANACTIONMANAGERTESTACTION_H

#include <abstractaction.h>

class DigitalBooleanActionManagerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DigitalBooleanActionManagerTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed(JActionEvent* =0)override;

 private:
  static Logger* log;
};

#endif // DIGITALBOOLEANACTIONMANAGERTESTACTION_H
