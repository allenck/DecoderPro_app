#include "pr3systemconnectionmemo.h"
#include "instancemanager.h"
#include "loconetthrottledtransmitter.h"

PR3SystemConnectionMemo::PR3SystemConnectionMemo(QObject *parent) :
    LocoNetSystemConnectionMemo(parent)
{
 PR3MODE = 0x00;
 MS100MODE = 0x01;

 mode = PR3MODE;
 log = new Logger("PR3SystemConnectionMemo");
 restoreToLocoNetInterfaceModeTask = NULL;

}
void PR3SystemConnectionMemo::configureManagersPR2()
{
 mode = PR3MODE;
 InstanceManager::store((QObject*)getPowerManager(), "PowerManager");

 InstanceManager::setThrottleManager(
  getThrottleManager());


 if (getProgrammerManager()->isAddressedModePossible()) {
     InstanceManager::setAddressedProgrammerManager(getProgrammerManager());
 }
 if (getProgrammerManager()->isGlobalProgrammerAvailable()) {
     InstanceManager::store(getProgrammerManager(), "GlobalProgrammerManager");
 }

 // Establish a ShutDownTask so that the PR3 should be be returned to
 // LocoNet Interface mode at shutdown
         // Finally, create and register a shutdown task to ensure clean exit
 if (restoreToLocoNetInterfaceModeTask == NULL)
 {
     restoreToLocoNetInterfaceModeTask = new Pr3ShutDownTask("Restore PR3 to LocoNet Interface Mode", this);
//     {    // NOI18N
//         @Override
//         public boolean execute() {


//             if (mode == PR3MODE) {
//                 // try to change from "standalone programmer" to "LocoNet interface" mode
//                 LnTrafficController tc;
//                 tc = getLnTrafficController();
//                 if (tc != null) {
//                     LocoNetMessage msg = new LocoNetMessage(6);
//                     msg.setOpCode(0xD3);
//                     msg.setElement(1, 0x10);
//                     msg.setElement(2, 0);  // set MS100, no power
//                     msg.setElement(3, 0);
//                     msg.setElement(4, 0);
//                     tc.sendLocoNetMessage(msg);
//                     log.info("Configuring PR3 for 'LocoNet Interface' mode"); // NOI18N
//                 }
//             }
//             return true;
//         }
//     };

     if (InstanceManager::getNullableDefault("ShutDownManager") != NULL) {
         ((ShutDownManager*)InstanceManager::getDefault("ShutDownManager"))->_register(restoreToLocoNetInterfaceModeTask);
     } else {
         log->warn("The PR3 will not be automatically returned to 'LocoNet interface' mode upon quit!"); // NOI18N
     }

 }
}

/*public*/ Pr3ShutDownTask::Pr3ShutDownTask(QString text,PR3SystemConnectionMemo *pr3SystemConnectionMemo) : QuietShutDownTask(text)
{
 this->pr3SystemConnectionMemo = pr3SystemConnectionMemo;
 log = new Logger("Pr3ShutDownTask");
}

/*public*/ bool Pr3ShutDownTask::execute()
{
    if (pr3SystemConnectionMemo->mode == pr3SystemConnectionMemo->PR3MODE) {
        // try to change from "standalone programmer" to "LocoNet interface" mode
        LnTrafficController* tc;
        tc = pr3SystemConnectionMemo->getLnTrafficController();
        if (tc != NULL) {
            LocoNetMessage* msg = new LocoNetMessage(6);
            msg->setOpCode(0xD3);
            msg->setElement(1, 0x10);
            msg->setElement(2, 0);  // set MS100, no power
            msg->setElement(3, 0);
            msg->setElement(4, 0);
            tc->sendLocoNetMessage(msg);
            log->info("Configuring PR3 for 'LocoNet Interface' mode"); // NOI18N
        }
    }
    return true;
}

/**
  * Configure the subset of LocoNet managers valid for the PR3 in MS100 mode.
  */
 void PR3SystemConnectionMemo::configureManagersMS100()
 {
  mode = MS100MODE;

  tm = new LocoNetThrottledTransmitter(getLnTrafficController(), mTurnoutExtraSpace);
  log->debug(QString("ThrottleTransmitted configured with :")+(mTurnoutExtraSpace?"true":"false"));

  InstanceManager::store((QObject*)LocoNetSystemConnectionMemo::getPowerManager(), "PowerManager");

  InstanceManager::setTurnoutManager((TurnoutManager*)getTurnoutManager());

  InstanceManager::setLightManager((LightManager*)getLightManager());

  InstanceManager::setSensorManager(getSensorManager());

  InstanceManager::setThrottleManager(LocoNetSystemConnectionMemo::getThrottleManager());

  if (getProgrammerManager()->isAddressedModePossible())
  {
      InstanceManager::setAddressedProgrammerManager(getProgrammerManager());
  }
  if (getProgrammerManager()->isGlobalProgrammerAvailable()) {
      InstanceManager::store(getProgrammerManager(), "GlobalProgrammerManager");
  }

  InstanceManager::setReporterManager((ReporterManager*)getReporterManager());

  InstanceManager::addClockControl((ClockControl*)getClockControl());

 }
 /*public*/ void PR3SystemConnectionMemo::dispose()
 {
  InstanceManager::deregister(this, "PR3SystemConnectionMemo");
  LocoNetSystemConnectionMemo::dispose();
 }
