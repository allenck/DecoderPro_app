#ifndef SPROGMONACTION_H
#define SPROGMONACTION_H
#include "abstractaction.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogMonAction : public AbstractAction
 {
 public:
  SprogMonAction(QString title, SprogSystemConnectionMemo* memo, QWidget* frame = 0);

 public slots:
  /*public*/ void actionPerformed();

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("SprogMonAction");
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;


 };
}
#endif // SPROGMONACTION_H
