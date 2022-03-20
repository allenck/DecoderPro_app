#ifndef DIGITALEXPRESSIONSTESTACTION_H
#define DIGITALEXPRESSIONSTESTACTION_H

#include <abstractaction.h>

class DigitalExpressionsTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit DigitalExpressionsTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // DIGITALEXPRESSIONSTESTACTION_H
