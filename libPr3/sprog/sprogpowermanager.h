#ifndef SPROGPOWERMANAGER_H
#define SPROGPOWERMANAGER_H
#include "abstractpowermanager.h"
#include "sprogsystemconnectionmemo.h"
#include "sprogtrafficcontroller.h"
#include "sprogmessage.h"
#include "exceptions.h"

class AbstractPowerManager;
namespace Sprog
{
 class SprogSystemConnectionMemo;
 class SprogTrafficController;
 class SprogPowerManager : public AbstractPowerManager
 {
  Q_OBJECT
 public:
  SprogPowerManager(SprogSystemConnectionMemo* memo, QObject* parent = 0);
  /*public*/ void setPower(int v) throw (JmriException);
  /*public*/ void notePowerState(int v);
  /*public*/ int getPower();
  /*public*/ void dispose() throw (JmriException);

 public slots:
  /*public*/ void notify(AbstractMessage* m);
  /*public*/ void notifyReply(SprogReply* m);
  /*public*/ void notifyMessage(SprogMessage* m);


 private:
  SprogTrafficController* trafficController;// = null;
  int power;// = UNKNOWN;

  bool waiting;// = false;
  int onReply;// = UNKNOWN;
  /*private*/ void checkTC() throw (JmriException);

 };
}
#endif // SPROGPOWERMANAGER_H
