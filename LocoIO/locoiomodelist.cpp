#include "locoiomodelist.h"
#include "lnconstants.h"

LocoIOModeList::LocoIOModeList(QObject *parent) :
    QObject(parent)
{
    /** Initialize various configuration modes...
     * TODO: Need to tag these with which firmware rev supports them
     *       and only allow choices that match.
     *
     * Inputs...
     */

//                                 output          opcode         SV0   SV2    Mode
    modeList.append(new LocoIOMode(0, 0,                          0x00, 0x00, tr("Not Used")));

//    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REQ,    0x0F, 0x00, tr("Toggle Switch, LocoIO 1.3.2")));

    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x5B, 0x00, tr("Block Detector, Active High")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x5B, 0x20, tr("Block Detector, Active High")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x5F, 0x00, tr("Block Detector, Active High, Block Detection Delay")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x5F, 0x20, tr("Block Detector, Active High, Block Detection Delay")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x1B, 0x10, tr("Block Detector, Active Low")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x1B, 0x30, tr("Block Detector, Active Low")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x1F, 0x10, tr("Block Detector, Active Low, Block Detection Delay")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_INPUT_REP, 0x1F, 0x30, tr("Block Detector, Active Low, Block Detection Delay")));

    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REQ,    0x0F, 0x10, tr("Toggle Switch, Direct Control")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REP,    0x07, 0x10, tr("Toggle Switch, Indirect Control")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REQ,    0x6F, 0x00, tr("Push Button, Active High, Direct Control")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REP,    0x67, 0x00, tr("Push Button, Active High, Indirect Control")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REQ,    0x2F, 0x10, tr("Push Button, Active Low, Direct Control")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REP,    0x27, 0x10, tr("Push Button, Active Low, Indirect Control")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REP,    0x17, 0x70, tr("Turnout Feedback, single sensor")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REP,    0x37, 0x70, tr("Turnout Feedback, dual sensor, #1")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_SW_REP,    0x37, 0x60, tr("Turnout Feedback, dual sensor, #2")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_IDLE,      0x2c, 0x00, tr("Special Port - Idle")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_GPON,      0x2d, 0x00, tr("Special Port - Go")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_GPOFF,     0x2e, 0x00, tr("Special Port - Stop")));

    /**
     * and Outputs...
     */

    modeList.append(new LocoIOMode(1, LnConstants::OPC_INPUT_REP, 0xC0, 0x00, tr("Block Occupied Indication")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_INPUT_REP, 0xD0, 0x00, tr("Block Occupied Indication, Blinking")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x81, 0x10, tr("Steady State, single output, On at Power up")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x80, 0x10, tr("Steady State, single output, Off at Power up")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x81, 0x30, tr("Steady State, paired output, On at Power up")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x80, 0x30, tr("Steady State, paired output, Off at Power up")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x91, 0x10, tr("Steady State, single output, On at Power up, Blinking")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x90, 0x10, tr("Steady State, single output, Off at Power up, Blinking")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x91, 0x30, tr("Steady State, paired output, On at Power up, Blinking")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x90, 0x30, tr("Steady State, paired output, Off at Power up, Blinking")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xA1, 0x10, tr("Steady State, single output, On at Power up, 4Way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xA0, 0x10, tr("Steady State, single output, Off at Power up, 4Way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xA1, 0x30, tr("Steady State, paired output, On at Power up, 4way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xA0, 0x30, tr("Steady State, paired output, Off at Power up, 4Way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xB1, 0x10, tr("Steady State, single output, On at Power up, Blinking, 4 Way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xB0, 0x10, tr("Steady State, single output, Off at Power up, Blinking, 4 way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xB1, 0x30, tr("Steady State, paired output, On at Power up, Blinking, 4 Way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0xB0, 0x30, tr("Steady State, paired output, Off at Power up, Blinking, 4 Way")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x88, 0x20, tr("Pulsed, software controlled on time, single output")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x8C, 0x20, tr("Pulsed, firmware controlled on time, single output")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x88, 0x00, tr("Pulsed, software controlled on time, paired output")));
    modeList.append(new LocoIOMode(1, LnConstants::OPC_SW_REQ,    0x8C, 0x00, tr("Pulsed, firmware controlled on time, paired output")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_IDLE,      0x82, 0x00, tr("Special Port - Status")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_GPOFF,     0xc2, 0x00, tr("Special Port - Status")));
    modeList.append(new LocoIOMode(0, LnConstants::OPC_GPON,      0xc3, 0x00, tr("Special Port - Status")));

    validmodes<<tr("<none>");
    for (int i=0; i <= modeList.size()-1; i++) {
        LocoIOMode* m = modeList.at(i);
        validmodes.append(m->getFullMode());
    }
}
/*
 * LocoIOModeList.java
 *
 * Created on January 30, 2007, 9:13 PM
 *
 * Manage the set of valid modes for a particular LocoIO port,
 * as well as the conversions between addresses and SV values.
 */

//package jmri.jmrix.loconet.locoio;

//import java.util.Vector;
//import jmri.jmrix.loconet.LnConstants;


/**
 *
 * @author plocher
 */
//public class LocoIOModeList {
//    private Vector<LocoIOMode> modeList = new Vector<LocoIOMode>();
//    private String[] validmodes;

    /**
     * Creates a new instance of LocoIOModeList
     */
//    public LocoIOModeList() {



    //@SuppressWarnings("unused")
/*private*/ void LocoIOModeList::test()
{
 /**
  * This should go into a JUnit test
  */
 log.debug("Starting test sequence");
 for (int i=0; i <= modeList.size()-1; i++)
 {
  LocoIOMode* m = modeList.at(i);

  int haderror = 0;
  for (i = 1; i <= 2047; i++)
  {
   int svA = m->getSV();
   int v1A = addressToValue1(m, i);
   int v2A = addressToValue2(m, i);

   log.debug(m->getFullMode() + "=> Address " + QString("0x%1").arg(i,0,16) +
               " encodes into " +
               LnConstants::OPC_NAME(m->getOpcode()) + " " +
               QString("0x%1").arg(svA, 0,16) + " " +
               QString("0x%1").arg(v1A,0,16) + " " +
               QString("0x%1").arg(v2A, 0, 16));

   LocoIOMode* lim = getLocoIOModeFor(svA, v1A, v2A);
   if (lim == NULL)
   {
    if (haderror == 0) log.error("Testing " + m->getFullMode() + "      ERROR:");
    QString err =
            "    Could Not find mode for Packet: " +
            QString("0x%1").arg(svA,0,16) + " " +
            QString("0x%1").arg(v1A,0,16) + " " +
            QString("0x%1").arg(v2A,0,16) + " <CHK>\n";
    log.error(err);
    haderror++;
   }
   else
   {
    int decodedaddress = valuesToAddress(lim->getOpcode(), svA, v1A, v2A);
    if ((i) != decodedaddress)
    {
     if (haderror == 0) log.error("Testing " + m->getFullMode() + "      ERROR:");
     QString err =
         "    Could Not Match Address: (" +
         QString("0x%1").arg(i - 1,0,16) + "=>" +
         QString("0x%1").arg(decodedaddress,0,16) + ") from " +
         LnConstants::OPC_NAME(lim->getOpcode()) + " " +
         QString("0x%1").arg(svA,0,16) + " " +
         QString("0x%1").arg(v1A,0,16) + " " +
         QString("0x%1").arg(v2A,0,16) + "[mask="+QString("0x%1").arg(lim->getV2(),0,16) + "]\n";
    log.error(err);
    haderror++;
    }
   }
  }
  if (haderror == 0) {
      log.debug("Testing " + m->getFullMode() + "      **OK**");
  }
 }
 log.debug("Finished test sequence\n");
}

/*protected*/ QStringList LocoIOModeList::getValidModes() {
    return validmodes;
}
/*protected*/ bool LocoIOModeList::isValidModeValue(QVariant value) {
    if (value.canConvert<QString>()) {
        QString sValue = value.toString();
        for (int i=0; i<validmodes.length(); i++) {
            if (sValue==(validmodes[i])) return true;
        }
    }
    return false;
}

/*protected*/ LocoIOMode* LocoIOModeList::getLocoIOModeFor(QString s) {
   for (int i=0; i <= modeList.size()-1; i++) {
        LocoIOMode* m = modeList.at(i);
        QString ms = m->getFullMode();
        if (ms==(s)) {
            return m;
        }
    }
    return NULL;
}
/*protected*/ LocoIOMode* LocoIOModeList::getLocoIOModeFor(int cv, int v1, int v2)
{
 // v2 &= 0x0F;
 for (int i=0; i <= modeList.size()-1; i++)
 {
  LocoIOMode* m = modeList.at(i);
  if (m->getSV() == cv)
  {
//   if ( (m->getOpcode() == LnConstants::OPC_INPUT_REP) && (m->getV2() == (v2 & 0xD0) ) )
   if ( (m->getOpcode() == LnConstants::OPC_INPUT_REP || m->getOpcode() == LnConstants::OPC_SW_REP || m->getOpcode() == LnConstants::OPC_SW_REQ) && (m->getV2() == (v2 & 0xC0) ) )
   {
    return m;
   }
   else if ( ((cv == 0x6F) || (cv == 0x67) || (cv == 0x2F) || (cv == 0x27))
                    && (m->getV2() == (v2 & 0x50) ) )
   {
    return m;
   }
   else if ( (m->getV2() == (v2 & 0xB0) ) )
   {
    return m;
   }
   else if ( ((cv & 0x90) == 0x10)
                   && ((cv & 0x80) == 0)
                   && (m->getV2() == (v2 & 0x70) ) )
   {
    return m;
   }
  }
 }
 qDebug() << QString("getLocoIOMode for cv: 0x%1, v1= 0x%2, v2=0x%3 failed!").arg(cv,0,16).arg(v1,0,16).arg(v2,0,16);
 return NULL;
}
/**
 * Low bits
 */
/*protected*/ int LocoIOModeList::addressToValue1(LocoIOMode* lim, int address)
{
 if (lim == NULL)
 {
  return 0;
 }
 return addressToValues(lim->getOpcode(), lim->getSV(), lim->getV2(), address) & 0x7F;
}
/**
 * High bits...
 */
/*protected*/ int LocoIOModeList::addressToValue2(LocoIOMode* lim, int address)
{
 if (lim == NULL)
 {
  return 0;
 }
 return (addressToValues(lim->getOpcode(), lim->getSV(), lim->getV2(), address)/256)&0x7F;
}

/**
 * Convert bytes from LocoNet packet into a 1-based address for
 * a sensor or turnout.
 * @param a1 Byte containing the upper bits
 * @param a2 Byte containing the lower bits
 * @return 1-4096 address
 */
/*static private*/ int LocoIOModeList::SENSOR_ADR(int a1, int a2) { return (((a2 & 0x0f) * 128) + (a1 & 0x7f)) + 1; }

/*protected*/ int LocoIOModeList::addressToValues(int opcode, int sv, int v2mask, int address)
{
 Q_UNUSED(sv)
 int v1 = 0;
 int v2 = 0;

 address--;

 if (opcode == LnConstants::OPC_INPUT_REP)
 {
  v1 = ((address/2) & 0x7F);
  v2 = ((address/256) & 0x0F);
  if ( (address & 0x01)== 0x01)
  {
   v2 |= LnConstants::OPC_INPUT_REP_SW;
  }
  v2 |= v2mask;
 }
 else if (opcode == LnConstants::OPC_SW_REQ)
 {
  v1 = (address & 0x7F);
  v2 = (address / 128) & 0x0F;
  v2 &= ~(0x40);
  v2 |= v2mask;
 }
 else if (opcode == LnConstants::OPC_SW_REP)
 {
  v1 = (address & 0x7F);
  v2 = (address / 128) & 0x0F;
  v2 &= ~(0x40);
  v2 |= v2mask;
 }
 return v2*256 + v1;
}

/*protected*/ int LocoIOModeList::valuesToAddress(int opcode, int sv, int v1, int v2)
{
 Q_UNUSED(sv)
 //int hi = 0;
 //int lo = 0;
 if (opcode == LnConstants::OPC_INPUT_REP)
 {  /* return 1-4096 address */
  return ((SENSOR_ADR(v1, v2)-1)*2+((v2 & LnConstants::OPC_INPUT_REP_SW)!=0?2:1));
 }
 else if (opcode == LnConstants::OPC_SW_REQ)
 {
    // if ( ((v2 & 0xCF) == 0x0F)  && ((v1 & 0xFC) == 0x78) ) { // broadcast address LPU V1.0 page 12
        // "Request Switch to broadcast address with bits "+
        // "a="+ ((sw2&0x20)>>5)+((sw2 & LnConstants::OPC_SW_REQ_DIR)!=0 ? " (Closed)" : " (Thrown)")+
        // " c="+ ((sw1 & 0x02)>>1) +
        // " b="+ ((sw1 & 0x01)) +
        // "\n\tOutput "+
        // ((sw2 & LnConstants::OPC_SW_REQ_OUT)!=0 ? "On"     : "Off")+"\n";
    // } else if ( ((v2 & 0xCF) == 0x07)  && ((v1 & 0xFC) == 0x78) ) { // broadcast address LPU V1.0 page 13
        // "Request switch command is Interrogate LocoNet with bits "+
        // "a="+ ((sw2 & 0x20)>>5) +
        // " c="+ ((sw1&0x02)>>1) +
        // " b="+ ((sw1&0x01)) +
        // "\n\tOutput "+
        // ((sw2 & LnConstants::OPC_SW_REQ_OUT)!=0 ? "On"     : "Off")+"\n"+
        // ( ( (sw2&0x10) == 0 ) ? "" : "\tNote 0x10 bit in sw2 is unexpectedly 0\n");
    // } else { // normal command
  return (SENSOR_ADR(v1, v2));
    //}
 }
 else if (opcode == LnConstants::OPC_SW_REP)
 {
  return (SENSOR_ADR(v1, v2));
 }
 return 1;
}

/*protected*/ int LocoIOModeList::valuesToAddress(LocoIOMode* lim, int sv, int v1, int v2)
{
 if (lim == NULL)
 {
  return 0;
 }
 return valuesToAddress(lim->getOpcode(), sv, v1, v2);
}


    //static org.apache.log4j.Logger log = org.apache.log4j.Logger.getLogger(LocoIOModeList.class.getName());
