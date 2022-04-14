#ifndef ACTIONMEMORYTESTACTION_H
#define ACTIONMEMORYTESTACTION_H

#include <abstractaction.h>

class ActionMemoryTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit ActionMemoryTestAction(QObject *parent = nullptr);

 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ACTIONMEMORYTESTACTION_H
