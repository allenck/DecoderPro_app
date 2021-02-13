#ifndef FILEUTILSUPPORTTESTACTION_H
#define FILEUTILSUPPORTTESTACTION_H
#include "abstractaction.h"

class Logger;
class FileUtilSupportTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  FileUtilSupportTestAction(QObject *parent);

 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // FILEUTILSUPPORTTESTACTION_H
