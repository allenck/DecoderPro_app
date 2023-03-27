#ifndef ACTIONSANDEXPRESSIONSTESTACTION_H
#define ACTIONSANDEXPRESSIONSTESTACTION_H

#include <abstractaction.h>

class ActionsAndExpressionsTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  ActionsAndExpressionsTestAction(QObject *parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;};

#endif // ACTIONSANDEXPRESSIONSTESTACTION_H
