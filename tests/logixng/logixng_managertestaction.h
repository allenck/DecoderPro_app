#ifndef LOGIXNG_MANAGERTESTACTION_H
#define LOGIXNG_MANAGERTESTACTION_H

#include <abstractaction.h>

class LogixNG_ManagerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit LogixNG_ManagerTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // LOGIXNG_MANAGERTESTACTION_H
