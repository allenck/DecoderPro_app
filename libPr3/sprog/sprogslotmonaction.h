#ifndef SPROGSLOTMONACTION_H
#define SPROGSLOTMONACTION_H
#include "abstractaction.h"
#include "sprogsystemconnectionmemo.h"

namespace Sprog
{
 class SprogSlotMonAction : public AbstractAction
 {
 public:
  SprogSlotMonAction(SprogSystemConnectionMemo* _memo, QWidget* parent);
  /*public*/ SprogSlotMonAction(QString s, SprogSystemConnectionMemo* memo, QWidget* parent);

 public slots:
  void actionPerformed();

 private:
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;

 };
}
#endif // SPROGSLOTMONACTION_H
