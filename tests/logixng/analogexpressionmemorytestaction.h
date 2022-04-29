#ifndef ANALOGEXPRESSIONMEMORYTESTACTION_H
#define ANALOGEXPRESSIONMEMORYTESTACTION_H

#include <abstractaction.h>

class AnalogExpressionMemoryTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit AnalogExpressionMemoryTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ANALOGEXPRESSIONMEMORYTESTACTION_H
