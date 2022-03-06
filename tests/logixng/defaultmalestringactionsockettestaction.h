#ifndef DEFAULTMALESTRINGACTIONSOCKETTESTACTION_H
#define DEFAULTMALESTRINGACTIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultMaleStringActionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultMaleStringActionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTMALESTRINGACTIONSOCKETTESTACTION_H
