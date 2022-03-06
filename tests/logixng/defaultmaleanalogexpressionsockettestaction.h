#ifndef DEFAULTMALEANALOGEXPRESSIONSOCKETTESTACTION_H
#define DEFAULTMALEANALOGEXPRESSIONSOCKETTESTACTION_H

#include <abstractaction.h>

class Logger;
class DefaultMaleAnalogExpressionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultMaleAnalogExpressionSocketTestAction(QObject *parent = nullptr);

 public slots:
  void actionPerformed();
 private:
  static Logger* log;

};

#endif // DEFAULTMALEANALOGEXPRESSIONSOCKETTESTACTION_H
