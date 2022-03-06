#ifndef DEFAULTFEMALEANALOGEXPRESSIONSOCKETTESTACTION_H
#define DEFAULTFEMALEANALOGEXPRESSIONSOCKETTESTACTION_H

#include <abstractaction.h>

class DefaultFemaleAnalogExpressionSocketTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DefaultFemaleAnalogExpressionSocketTestAction(QObject *parent = nullptr);
  public slots:
   void actionPerformed();
  private:
   static Logger* log;
};

#endif // DEFAULTFEMALEANALOGEXPRESSIONSOCKETTESTACTION_H
