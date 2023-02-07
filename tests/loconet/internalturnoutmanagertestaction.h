#ifndef INTERNALTURNOUTMANAGERTESTACTION_H
#define INTERNALTURNOUTMANAGERTESTACTION_H

#include <abstractaction.h>
#include <QObject>

class Logger;
class InternalTurnoutManagerTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  InternalTurnoutManagerTestAction(QObject *parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // INTERNALTURNOUTMANAGERTESTACTION_H
