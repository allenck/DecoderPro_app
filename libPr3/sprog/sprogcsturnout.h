#ifndef SPROGCSTURNOUT_H
#define SPROGCSTURNOUT_H
#include "abstractturnout.h"
#include "sprogsystemconnectionmemo.h"
#include "sprogslotlistener.h"

namespace Sprog
{
 class SprogCSTurnout : public AbstractTurnout
 {
 public:
  SprogCSTurnout(int number, SprogSystemConnectionMemo* memo, QObject* parent = 0);
  /*public*/ int getNumber();
  /*public*/ void setCommandStation(SprogCommandStation* command);
  /*public*/ bool canInvert();

 private:
  /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("SprogCSTurnout");
  /*private*/ SprogSystemConnectionMemo* _memo;// = null;
  /*private*/ SprogCommandStation* commandStation;
  int _number; // turnout number

 protected:
  /*protected*/ void forwardCommandChangeToLayout(int s);
  /*protected*/ void turnoutPushbuttonLockout(bool _pushButtonLockout);

 };
}
#endif // SPROGCSTURNOUT_H
