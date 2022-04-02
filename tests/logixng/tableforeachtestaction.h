#ifndef TABLEFOREACHTESTACTION_H
#define TABLEFOREACHTESTACTION_H

#include <abstractaction.h>

class TableForEachTestAction : public AbstractAction
{
  Q_OBJECT
 public:
  explicit TableForEachTestAction(QObject *parent = nullptr);
 public slots:
  void actionPerformed();
 private:
  static Logger* log;
};

#endif // TABLEFOREACHTESTACTION_H
