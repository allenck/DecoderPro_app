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
}
void PR3SystemConnectionMemo::configureManagersPR2()
{
 mode = PR3MODE;
 InstanceManager::setPowerManager((PowerManager*)
  getPowerManager());

 InstanceManager::setThrottleManager(
  getThrottleManager());

 InstanceManager::setProgrammerManager(
  getProgrammerManager());

}
/**
  * Configure the subset of LocoNet managers valid for the PR3 in MS100 mode.
  */
 void PR3SystemConnectionMemo::configureManagersMS100()
 {
  mode = MS100MODE;

  tm = new LocoNetThrottledTransmitter(getLnTrafficController(), mTurnoutExtraSpace);
  log->debug(QString("ThrottleTransmitted configured with :")+(mTurnoutExtraSpace?"true":"false"));

  InstanceManager::setPowerManager((PowerManager*)LocoNetSystemConnectionMemo::getPowerManager());

  InstanceManager::setTurnoutManager((TurnoutManager*)getTurnoutManager());

  InstanceManager::setLightManager((LightManager*)getLightManager());

  InstanceManager::setSensorManager(getSensorManager());

  InstanceManager::setThrottleManager(LocoNetSystemConnectionMemo::getThrottleManager());

  InstanceManager::setProgrammerManager(getProgrammerManager());

  InstanceManager::setReporterManager((ReporterManager*)getReporterManager());

  InstanceManager::addClockControl((ClockControl*)getClockControl());

 }
 /*public*/ void PR3SystemConnectionMemo::dispose()
 {
  InstanceManager::deregister(this, "PR3SystemConnectionMemo");
  LocoNetSystemConnectionMemo::dispose();
 }
