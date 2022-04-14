#ifndef STOREANDLOADTESTACTION_H
#define STOREANDLOADTESTACTION_H

#include <abstractaction.h>

class StoreAndLoadTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit StoreAndLoadTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();

 private:
  static Logger* log;
};

#endif // STOREANDLOADTESTACTION_H
