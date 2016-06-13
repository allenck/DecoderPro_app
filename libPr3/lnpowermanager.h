#ifndef LNPOWERMANAGER_H
#define LNPOWERMANAGER_H
#include "abstractpowermanager.h"
#include "loconetsystemconnectionmemo.h"
#include <QThread>
#include "logger.h"
#include "loconetmessage.h"
#include "lntrafficcontroller.h"
#include "sleeperthread.h"

class LNConstants;
class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LnPowerManager : public AbstractPowerManager
{
 Q_OBJECT
public:
//    explicit LnPowerManager(QObject *parent = 0);
 explicit LnPowerManager(LocoNetSystemConnectionMemo* memo, QObject *parent = 0);
 void setPower(int v); // throws JmriException
 int getPower();
 // these next three public methods have been added so that other classes
 // do not need to reference the static final values "ON", "OFF", and "UKNOWN".
 bool isPowerOn() {return (power == ON);}
 bool isPowerOff() {return (power == OFF);}
 bool isPowerUnknown() {return (power == UNKNOWN);}
 void dispose();
 //void message(LocoNetMessage* m); // move to slots

signals:
    
public slots:
 void message(LocoNetMessage* m);

protected:
 int power;
private:
 LnTrafficController* tc;
 Logger log;
 void checkTC(); // throws JmriException
 /**
  * Creates a thread which delays and then queries slot 0 to get the current
  * track status.  The LnListener will see the slot read data and use the
  * current track status to update the LnPowerManager's internal track
  * power state info.
  */
 void updateTrackPowerStatus();
};

/**
 * Class providing a thread to delay then query slot 0.  The LnPowerManager
 * can use the resulting OPC_SL_RD_DATA message to update its view of the
 * current track status.
 */
class LnTrackStatusUpdateThread : public QThread
{
  Q_OBJECT
 private:
  LnTrafficController* tc;

/**
 * Constructs the thread
 * <param> tc - LocoNetTrafficController which can be used to send the LocoNet message.
 */
 public:
  LnTrackStatusUpdateThread(LnTrafficController* tc)
  {
   this->tc = tc;
  }

/**
 * Runs the thread - Waits a while (to allow the managers to initialize)
 * then sends a query of slot 0 so that the power manager can
 * inspect the "<trk>" byte.
 */
 void run()
 {
        // wait a little bit to allow power manager to be initialized
//        try {
            // Delay 200 mSec to allow init of traffic controller, listeners.
  SleeperThread::msleep(200);
//        } catch (InterruptedException e) {
//            currentThread().interrupt(); // retain if needed later
//        }
  LocoNetMessage* msg = new LocoNetMessage(4);
  msg->setOpCode(LnConstants::OPC_RQ_SL_DATA);
  msg->setElement(1, 0);
  msg->setElement(2, 0);
  tc->sendLocoNetMessage(msg);
 }
};
#endif // LNPOWERMANAGER_H
