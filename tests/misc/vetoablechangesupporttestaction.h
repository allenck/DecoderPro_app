#ifndef VETOABLECHANGESUPPORTTESTACTION_H
#define VETOABLECHANGESUPPORTTESTACTION_H

#include <abstractaction.h>

class VetoableChangeSupportTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit VetoableChangeSupportTestAction(QObject *parent = nullptr);
 public slots:

  void actionPerformed();
 private:
  static Logger* log;
};

#endif // VETOABLECHANGESUPPORTTESTACTION_H
