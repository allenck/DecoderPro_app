#ifndef ACTIONSENSORTESTACTION_H
#define ACTIONSENSORTESTACTION_H

#include <abstractaction.h>

class ActionSensorTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit ActionSensorTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ACTIONSENSORTESTACTION_H
