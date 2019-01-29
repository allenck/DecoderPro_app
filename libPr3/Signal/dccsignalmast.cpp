#include "dccsignalmast.h"
#include "commandstation.h"
#include "instancemanager.h"
#include "signalmastmanager.h"
#include "nmrapacket.h"

//DccSignalMast::DccSignalMast(QObject *parent) :
//  AbstractSignalMast(parent)
//{
//}
/**
 * This class implements a SignalMast that use <B>Extended Accessory Decoder
 * Control Packet Format</B>
 * and outputs that packet to the DCC System via the generic CommandStation
 * interface
 * <P>
 * This implementation writes out to the physical signal when it's commanded to
 * change appearance, and updates its internal state when it hears commands from
 * other places.
 * <p>
 * System name specifies the creation information:
 * <pre>
 * IF$dsm:basic:one-searchlight:(123)
 * </pre> The name is a colon-separated series of terms:
 * <ul>
 * <li>IF$dsm - defines signal masts of this type
 * <li>basic - name of the signaling system
 * <li>one-searchlight - name of the particular aspect map
 * <li>(123) - DCC address for the decoder
 * </ul>
 * <p>
 * Based upon {@link jmri.implementation.DccSignalHead} by Alex Shepherd
 *
 * @author Kevin Dickerson Copyright (c) 2012
 * @version $Revision: 19173 $
 */
///*public*/ class DccSignalMast extends AbstractSignalMast {

/**
 *
 */
//private static final long serialVersionUID = 2711857995161461274L;

/*public*/ DccSignalMast::DccSignalMast(QString sys, QString user, QObject *parent) :
  AbstractSignalMast(sys, user, parent) {
    //super(sys, user);
 common();
 configureFromName(sys);
}

/*public*/ DccSignalMast::DccSignalMast(QString sys,QObject *parent) :
  AbstractSignalMast(sys, parent) {
    //super(sys);
 common();
    configureFromName(sys);
}

/*public*/ DccSignalMast::DccSignalMast(QString sys, QString user, QString mastSubType,QObject *parent) :
  AbstractSignalMast(sys, user, parent) {
    //super(sys, user);
 common();
    mastType = mastSubType;
    configureFromName(sys);
}
void DccSignalMast::common()
{
 mastType = "F$dsm";
 appearanceToOutput =  QMap<QString, int>();
 log = new Logger("DccSignalMast");
 packetRepeatCount = 3;
 unLitId = 31;
 c = NULL;
}


/*protected*/ void DccSignalMast::configureFromName(QString systemName)
{
 // split out the basic information
 QStringList parts = systemName.split(":");
 if (parts.length() < 3) {
     log->error("SignalMast system name needs at least three parts: " + systemName);
     throw new IllegalArgumentException("System name needs at least three parts: " + systemName);
 }
 if (!parts[0].endsWith(mastType))
 {
     log->warn("First part of signal mast is incorrect " + systemName + " : " + mastType);
 } else {
     QString commandStationPrefix = parts[0].mid(0, parts[0].indexOf("$") - 1);
     //QList<CommandStation*>* connList = InstanceManager::getList("CommandStation");
     QObjectList* connList = InstanceManager::getList("CommandStation");
     if (!connList->isEmpty())
     {
      for (int x = 0; x < connList->size(); x++)
      {
       CommandStation* station = (CommandStation*)connList->at(x);
       if (station->getSystemPrefix()==(commandStationPrefix))
       {
        c = station;
        break;
       }
      }
     }
     if (c == NULL)
     {
      c = static_cast<CommandStation*>(InstanceManager::getDefault("CommandStation"));
      log->error("No match against the command station for " + parts[0] + ", so will use the default");
     }
 }
 QString system = parts[1];
 QString mast = parts[2];

 mast = mast.mid(0, mast.indexOf("("));
 setMastType(mast);

 QString tmp = parts[2].mid(parts[2].indexOf("(") + 1, parts[2].indexOf(")"));
 //try {
 bool bok;
     dccSignalDecoderAddress = tmp.toInt(&bok);
 //} catch (NumberFormatException e) {
     if(!bok)
     {
     log->warn("DCC accessory address SystemName " + systemName + " is not in the correct format");
 }
 configureSignalSystemDefinition(system);
 configureAspectTable(system, mast);
}


/*public*/ void DccSignalMast::setOutputForAppearance(QString appearance, int number)
{
 if (appearanceToOutput.contains(appearance)) {
     log->debug("Appearance " + appearance + " is already defined as " + appearanceToOutput.value(appearance));
     appearanceToOutput.remove(appearance);
 }
 appearanceToOutput.insert(appearance, number);
}

/*public*/ int DccSignalMast::getOutputForAppearance(QString appearance) {
    if (!appearanceToOutput.contains(appearance)) {
        log->error("Trying to get appearance " + appearance + " but it has not been configured");
        return -1;
    }
    return appearanceToOutput.value(appearance);
}



/*public*/ void DccSignalMast::setAspect(QString aspect)
{

 if (appearanceToOutput.contains(aspect) && appearanceToOutput.value(aspect) != -1)
 {
     c->sendPacket(NmraPacket::altAccSignalDecoderPkt(dccSignalDecoderAddress, appearanceToOutput.value(aspect)), packetRepeatCount);
 } else {
     log->warn("Trying to set aspect (" + aspect + ") that has not been configured on mast " + getDisplayName());
 }
 AbstractSignalMast::setAspect(aspect);
}

/*public*/ void DccSignalMast::setLit(bool newLit)
{
 if (!allowUnLit() || newLit == getLit()) {
     return;
 }
 if (newLit) {
     setAspect(getAspect());
 } else {
     c->sendPacket(NmraPacket::altAccSignalDecoderPkt(dccSignalDecoderAddress, unLitId), packetRepeatCount);
 }
 AbstractSignalMast::setLit(newLit);
}


/*public*/ void DccSignalMast::setUnlitId(int i) {
    unLitId = i;
}

/*public*/ int DccSignalMast::getUnlitId() {
    return unLitId;
}

/*public*/ int DccSignalMast::getDccSignalMastAddress() {
    return dccSignalDecoderAddress;
}

/*public*/ CommandStation* DccSignalMast::getCommandStation() {
    return c;
}


/*public*/ /*static*/ QString DccSignalMast::isDCCAddressUsed(int addr)
{
 foreach (QString val, static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSystemNameList())
 {
  SignalMast* mast = static_cast<SignalMastManager*>(InstanceManager::getDefault("SignalMastManager"))->getSignalMast(val);
  //if (mast instanceof jmri.implementation.DccSignalMast)
  if(qobject_cast<DccSignalMast*>(mast)!= NULL)
  {
      if (((DccSignalMast*) mast)->getDccSignalMastAddress() == addr) {
          return ((DccSignalMast*) mast)->getDisplayName();
      }
  }
 }
 return NULL;
}
