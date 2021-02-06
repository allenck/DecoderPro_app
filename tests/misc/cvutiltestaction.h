#ifndef CVUTILTESTACTION_H
#define CVUTILTESTACTION_H
#include "abstractaction.h"

class Logger;
class CvUtilTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  CvUtilTestAction(QObject* parent);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // CVUTILTESTACTION_H
