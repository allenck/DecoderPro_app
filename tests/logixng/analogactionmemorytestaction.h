#ifndef ANALOGACTIONMEMORYTESTACTION_H
#define ANALOGACTIONMEMORYTESTACTION_H

#include <abstractaction.h>

class AnalogActionMemoryTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit AnalogActionMemoryTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ANALOGACTIONMEMORYTESTACTION_H
