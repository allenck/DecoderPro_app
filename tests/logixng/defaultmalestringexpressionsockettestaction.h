#ifndef DEFAULTMALESTRINGEXPRESSIONSOCKETTESTACTION_H
#define DEFAULTMALESTRINGEXPRESSIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultMaleStringExpressionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultMaleStringExpressionSocketTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DEFAULTMALESTRINGEXPRESSIONSOCKETTESTACTION_H
