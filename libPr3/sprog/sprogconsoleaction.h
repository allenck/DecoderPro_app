#ifndef SPROGCONSOLEACTION_H
#define SPROGCONSOLEACTION_H
#include "abstractaction.h"
#include "sprogsystemconnectionmemo.h"
namespace Sprog
{
 class SprogConsoleAction : public AbstractAction
 {
  Q_OBJECT
 public:
  /*public*/ SprogConsoleAction(QString s, SprogSystemConnectionMemo *memo, QObject* parent);

 public slots:
  void actionPerformed();
 private:
  SprogSystemConnectionMemo* _memo;
  /*private*/ /*final*/ static Logger* log; //= LoggerFactory.getLogger(SprogConsoleAction.class);

 };
}
#endif // SPROGCONSOLEACTION_H
