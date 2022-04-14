#ifndef ANDTESTACTION_H
#define ANDTESTACTION_H

#include <abstractaction.h>

class AndTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit AndTestAction(QObject *parent = nullptr);

 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // ANDTESTACTION_H
