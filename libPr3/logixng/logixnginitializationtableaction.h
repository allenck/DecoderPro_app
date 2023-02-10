#ifndef LOGIXNGINITIALIZATIONTABLEACTION_H
#define LOGIXNGINITIALIZATIONTABLEACTION_H

#include <abstractaction.h>

class LogixNGInitializationTable;
class LogixNGInitializationTableAction : public AbstractAction
{
 public:
  explicit LogixNGInitializationTableAction(QObject *parent = nullptr);
  explicit LogixNGInitializationTableAction(QString s, QObject *parent = nullptr);

 public slots:
  /*public*/  void actionPerformed(JActionEvent* e =0)override;

 private:
  /*private*/ static QPointer<LogixNGInitializationTable> initializationTableFrame;// = null;

};

#endif // LOGIXNGINITIALIZATIONTABLEACTION_H
