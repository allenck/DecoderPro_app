#ifndef DEFAULTMALEANALOGACTIONSOCKETTESTACTION_H
#define DEFAULTMALEANALOGACTIONSOCKETTESTACTION_H

#include <abstractaction.h>

class Logger;
class DefaultMaleAnalogActionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultMaleAnalogActionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTMALEANALOGACTIONSOCKETTESTACTION_H
