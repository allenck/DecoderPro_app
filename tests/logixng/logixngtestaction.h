#ifndef LOGIXNGTESTACTION_H
#define LOGIXNGTESTACTION_H

#include <abstractaction.h>

class LogixNGTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit LogixNGTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // LOGIXNGTESTACTION_H
