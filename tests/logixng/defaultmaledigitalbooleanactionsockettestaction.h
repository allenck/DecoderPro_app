#ifndef DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTESTACTION_H
#define DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultMaleDigitalBooleanActionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultMaleDigitalBooleanActionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTMALEDIGITALBOOLEANACTIONSOCKETTESTACTION_H
