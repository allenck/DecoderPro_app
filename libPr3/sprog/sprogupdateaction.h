#ifndef SPROGUPDATEACTION_H
#define SPROGUPDATEACTION_H
#include "abstractaction.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogUpdateAction : public AbstractAction
 {
 public:
  /*public*/ SprogUpdateAction(QString s,SprogSystemConnectionMemo* memo, QWidget* frame);


 protected:
  /*protected*/ SprogSystemConnectionMemo* _memo;// = null;

 };
}
#endif // SPROGUPDATEACTION_H
