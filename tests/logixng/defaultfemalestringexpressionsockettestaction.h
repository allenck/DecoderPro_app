#ifndef DEFAULTFEMALESTRINGEXPRESSIONSOCKETTESTACTION_H
#define DEFAULTFEMALESTRINGEXPRESSIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultFemaleStringExpressionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultFemaleStringExpressionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTFEMALESTRINGEXPRESSIONSOCKETTESTACTION_H
