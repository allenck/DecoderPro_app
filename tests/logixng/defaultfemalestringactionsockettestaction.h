#ifndef DEFAULTFEMALESTRINGACTIONSOCKETTESTACTION_H
#define DEFAULTFEMALESTRINGACTIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultFemaleStringActionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultFemaleStringActionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTFEMALESTRINGACTIONSOCKETTESTACTION_H
