#include "rawturnoutoperator.h"
#include "abstractturnout.h"
#include "instancemanager.h"
#include "nmrapacket.h"

//RawTurnoutOperator::RawTurnoutOperator(QObject *parent) :
//    TurnoutOperator(parent)
//{
//}
/**
 * Concrete subclass of TurnoutOperator for a turnout that has no feedback.
 * This operator sends raw NMRA accessory decoder packets to the layout
 * instead of using the built in turnout code.  It should be used only with
 * turnouts with DIRECT, ONESENSOR or TWOSENSOR feedback.
 * This class is based on the NoFeedbackTurnoutOperator class.
 *
 * @author	Paul Bender	Copyright 2008
 */
//package jmri.implementation;

//import jmri.*;

// /*public*/ class RawTurnoutOperator extends TurnoutOperator {


/*public*/ RawTurnoutOperator::RawTurnoutOperator(AbstractTurnout* t, long i, int mt, QObject *parent) : TurnoutOperator(t, parent)
{
 //super(t);
 tries = 0;
 address = 0;
 log = new Logger("RawTurnoutOperator");

 QString sysName = t->getSystemName();
 int startAddress = sysName.lastIndexOf("T");
 address= sysName.mid(startAddress+1, sysName.length()).toInt();
 QString prefix = t->getSystemName().mid(0, startAddress);
 QObjectList* connList = InstanceManager::getList("CommandStation");
 for(int x = 0; x < connList->size(); x++)
 {
  CommandStation* station = (CommandStation*) connList->at(x);
  if(station->getSystemPrefix()==(prefix))
  {
   c = station;
   break;
  }
 }
 if(c==NULL)
 {
  c = static_cast<CommandStation*>(InstanceManager::getDefault("CommandStation"));
  log->error("No match against the command station for " + sysName + ", so will use the default");
 }
 interval = i;
 maxTries = mt;
}

/*private*/ void RawTurnoutOperator::sendCommand()
{
 QByteArray pkt = NmraPacket::accDecoderPkt(address,myTurnout->getCommandedState()==Turnout::CLOSED);
    c->sendPacket(pkt,1);
}

/**
 * Do the autmation for a turnout with no feedback. This means try
 * maxTries times at an interval of interval. Note the call to
 * operatorCheck each time we're about to actually do something -
 * if we're no longer the current operator this throws
 * TurnoutOperatorException which just terminates the thread.
 */
/*public*/ void RawTurnoutOperator::run() {
    try {
        operatorCheck();
                    sendCommand();
        while (++tries < maxTries) {
            try {
                //QThread::sleep(interval);
                QThread::msleep(interval);
            } catch (InterruptedException e) {
                QThread::currentThread()->exit(); // retain if needed later
            }
            operatorCheck();
            sendCommand();
        }
        myTurnout->setKnownStateToCommanded();
    } catch (TurnoutOperatorException e) { }
}
