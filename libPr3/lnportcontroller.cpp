#include "lnportcontroller.h"
#include "dccmanufacturerlist.h"

LnPortController::LnPortController(LocoNetSystemConnectionMemo* connectionMemo, QObject *parent)
 : AbstractSerialPortController(connectionMemo, parent)
{
 log = new Logger("LnPortController");
 setManufacturer(DCCManufacturerList::DIGITRAX);
 //setManufacturer("Digitrax");
 mCanRead = true;
 mProgPowersOff = false;
 commandStationName = "<unknown>";
 commandStationType = NULL;
 mTurnoutNoRetry = false;
 mTurnoutExtraSpace = false;

 commandStationNames << "DCS100 (Chief)"<<
                        "DCS200"<<
                        "DCS50 (Zephyr)"<<
                        "DCS51 (Zephyr Xtra)"<<
                        "DB150 (Empire Builder)"<<
                        "Intellibox"<<
                        "LocoBuffer (PS)"<<
                        "Mix-Master";
 commandStationTypes .append(LnCommandStationType::getByType( LnCommandStationType::COMMAND_STATION_DCS100));
 commandStationTypes .append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS200));
 commandStationTypes .append(LnCommandStationType::getByType( LnCommandStationType::COMMAND_STATION_DCS050));
 commandStationTypes .append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_DCS051));
 commandStationTypes .append(LnCommandStationType::getByType( LnCommandStationType::COMMAND_STATION_DB150));
 commandStationTypes .append(LnCommandStationType::getByType( LnCommandStationType::COMMAND_STATION_IBX_TYPE_1));
 commandStationTypes .append(LnCommandStationType::getByType(LnCommandStationType::COMMAND_STATION_IBX_TYPE_2));
 commandStationTypes .append(LnCommandStationType::getByType( LnCommandStationType::COMMAND_STATION_LBPS));
 commandStationTypes .append(LnCommandStationType::getByType( LnCommandStationType::COMMAND_STATION_MM));
 // There are also "PR3 standalone programmer" and "Stand-alone LocoNet"
 // in pr3/PR3Adapter
 adaptermemo = NULL;
 commandStationName = "<unknown>";
}
/**
 * Set config info from a name, which needs to be one of the valid
 * ones.
 */
/*public*/ void LnPortController::setCommandStationType(QString name) {
    setCommandStationType(LnCommandStationType::getByName(name));
}
/**
 * Set config info from the command station type enum.
 */
/*public*/ void LnPortController::setCommandStationType(LnCommandStationType* value)
{
 if (value == NULL) return;  // can happen while switching protocols
 log->debug("setCommandStationType: "+value->getName());
 commandStationType = value;
}

bool LnPortController::okToSend()
{
 QSerialPort* port = getSerialPort();
 if(port == NULL)
  return false;
 if(getSerialPort()->bytesToWrite() > 0)
  return false;
 return true;
}

 /**
  * Base for classes representing a LocoNet communications port
  * @author		Bob Jacobsen    Copyright (C) 2001, 2002
  * @version             $Revision: 20788 $
  */
 //public abstract class LnPortController extends jmri.jmrix.AbstractSerialPortController {
     // base class. Implementations will provide InputStream and OutputStream
     // objects to LnTrafficController classes, who in turn will deal in messages.

// /**
//  * Set config info from the command station type name.
//  */
// /*public*/ void LnPortController::setCommandStationType(QString value) {
//     if (value == null) return;  // can happen while switching protocols
//     log->debug("setCommandStationType: "+value);
//     if (value.equals("DB150 (Empire Builder)") || value.equals("Mix-Master")) {
//         mCanRead = false;
//         mProgPowersOff = true;
//     }
//     else {
//         mCanRead = true;
//         mProgPowersOff = false;
//     }
//     commandStationName = value;
// }
 /*public*/ void LnPortController::setTurnoutHandling(QString value) {
     if (value==("One Only") || value==("Both")) mTurnoutNoRetry = true;
     if (value==("Spread") || value==("Both")) mTurnoutExtraSpace = true;
     if( log->isDebugEnabled()) log->debug("turnout no retry: "+QString("%1").arg(mTurnoutNoRetry?"true":"false"));
     if( log->isDebugEnabled()) log->debug("turnout extra space: "+QString("%1").arg(mTurnoutExtraSpace?"true":"false"));
 }
 /*public*/ void  LnPortController::setDisabled(bool disabled) {
     mDisabled = disabled;
     if(adaptermemo!=NULL)
         adaptermemo->setDisabled(disabled);
 }
     //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LnPortController.class.getName());
 bool LnPortController::status()
 {
  return true;

 }
 //@Override
 /*public*/ SystemConnectionMemo* LnPortController::getSystemConnectionMemo()
 {
  return (SystemConnectionMemo*) AbstractSerialPortController::getSystemConnectionMemo();
 }
