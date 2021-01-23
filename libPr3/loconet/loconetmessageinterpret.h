#ifndef LOCONETMESSAGEINTERPRET_H
#define LOCONETMESSAGEINTERPRET_H

#include <QObject>
#include "lnconstants.h"

class LocoNetMessage;
class Logger;
class LocoNetMessageInterpret : public QObject
{
 Q_OBJECT
public:
 explicit LocoNetMessageInterpret(QObject *parent = nullptr);
 /*public*/ static QString interpretMessage(LocoNetMessage* l, QString turnoutPrefix, QString sensorPrefix, QString reporterPrefix);
 static /*public*/ int SENSOR_ADR(int a1, int a2);


 /*public*/ static QString getDeviceNameFromIPLInfo(int manuf, int type);
 /*public*/ static QString getSlaveNameFromIPLInfo(int manuf, int slaveNum);
 /*public*/ static QString interpretAlm(LocoNetMessage* l);

signals:

public slots:

private:
 static /*private*/ int LOCO_ADR(int a1, int a2);
 static QString convertToMixed(int addressLow, int addressHigh);
 /*private*/ static QString interpretOpcPeerXfer20_1(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20_2(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20_3(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20_4(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20_7(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20_10(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20_8(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20_0f(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer20Sub10(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer16(LocoNetMessage* l);
 /*private*/ static QString interpretSV1Message(LocoNetMessage* l);
 /*private*/ static QString interpretSV0Message(LocoNetMessage* l);
 /*private*/ static QString interpretSV2Message(LocoNetMessage* l);
 /*private*/ static QString interpretLncvMessage(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer10(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer9(LocoNetMessage* l, QString reporterPrefix);
 /*private*/ static QString interpretOpcPeerXfer7(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPeerXfer(LocoNetMessage* l, QString reporterPrefix);
 /*private*/ static QString interpretLongAck(LocoNetMessage* l);
 /*private*/ static QString interpretPm4xPowerEvent(LocoNetMessage* l);
 /*private*/ static QString interpretOpSws(LocoNetMessage* l);
 /*private*/ static QString interpretDeviceType(LocoNetMessage* l);
 /*private*/ static QString interpretOpcMultiSense(LocoNetMessage* l, QString reporterPrefix);
 /*private*/ static QString interpretOpcMultiSenseTranspPresence(LocoNetMessage* l, QString reporterPrefix);
 /*private*/ static QString interpretOpcWrSlDataOpcSlRdData(LocoNetMessage* l);
 /*private*/ static QString interpretOpcInputRep(LocoNetMessage* l, QString sensorPrefix);
 /*private*/ static QString interpretOpcSwRep(LocoNetMessage* l, QString turnoutPrefix);
 /*private*/ static QString interpretOpcSwAck(LocoNetMessage* l, QString turnoutPrefix);
 /*private*/ static QString interpretOpcSwState(LocoNetMessage* l, QString turnoutPrefix);
 /*private*/ static QString interpretOpcRqSlData(LocoNetMessage* l);
 /*private*/ static QString interpretOpcMoveSlots(LocoNetMessage* l);
 /*private*/ static QString interpretOpcConsistFunc(LocoNetMessage* l);
 /*private*/ static QString interpretOpcLocoSnd(LocoNetMessage* l);
 /*private*/ static QString interpretOpcLocoDirf(LocoNetMessage* l);
 /*private*/ static QString interpretOpcLocoSpd(LocoNetMessage* l);
 /*private*/ static QString interpretOpcPanelQuery(LocoNetMessage* l);
 /*private*/ static QString interpretOpcSwReq(LocoNetMessage* l, QString turnoutPrefix);
 /*private*/ static QString interpretFastClockSlot(LocoNetMessage* l, QString mode, int id1, int id2);
 /*private*/ static QString interpretProgSlot(LocoNetMessage* l, QString mode, int id1, int id2, int command);
 /*private*/ static QString interpretCmdStnCfgSlotRdWr(LocoNetMessage* l, int command);
 /*private*/ static QString interpretCmdStnExtCfgSlotRdWr(LocoNetMessage* l, int command);
 /*private*/ static QString interpretStandardSlotRdWr(LocoNetMessage* l, int id1, int id2, int command, int slot);
 /*private*/ static QString interpretOpcPanelResponse(LocoNetMessage* l);
 /*private*/ static QString interpretOpcLissyUpdate(LocoNetMessage* l);
 /*private*/ static QString interpretOpcImmPacket(LocoNetMessage* l);
 /*private*/ static QString trackStatusByteToString(int trackStatusByte);
 /*private*/ static QString fcTimeToString(int hour, int minute);
 /*private*/ static QString figureAddressIncludingAliasing(int adr, int adr2, int ss2, int id1, int id2);
 /*private*/ static QString interpretOpcPr3Mode(LocoNetMessage* l);
 /*private*/ static QString interpretIb2Special(LocoNetMessage* l);
 /*private*/ static QString interpretIb2F9_to_F12(LocoNetMessage* l);
 /*public*/ static QString dotme(int val);
 /*private*/ static QString idString(int id1, int id2);
 /*private*/ static QString getAlmTaskType(int taskTypeByte);
 /*private*/ static QString interpretOpcExpMoveSlots(LocoNetMessage* l);
 /*private*/ static QString interpretPocExpLocoSpdDirFunction(LocoNetMessage* l);
 /*private*/ static QString interpretExtendedSlotRdWr(LocoNetMessage* l, int slot);
 /*private*/ static QString interpretExtendedSlot_StatusData(LocoNetMessage* l, int slot);
 /*private*/ static QString interpretExtendedSlot_StatusData_Base(LocoNetMessage* l, int slot);
 /*private*/ static QString interpretExtendedSlot_StatusData_Base_Detail(LocoNetMessage* l, int slot);
 /*private*/ static QString interpretExtendedSlot_StatusData_Electric(LocoNetMessage* l, int slot);
 /*private*/ static QString interpretExtendedSlot_StatusData_LocoNet(LocoNetMessage* l, int slot);
 /*private*/ static QString interpretExtendedSlot_StatusData_Flags(LocoNetMessage* l, int slot);
 /*private*/ static QString interpretExtendedSlot_StatusData_Slots(LocoNetMessage* l, int slot);


 /*private*/ static /*final*/ QList<QString> ds54sensors; //[] = {"AuxA", "SwiA", "AuxB", "SwiB", "AuxC", "SwiC", "AuxD", "SwiD"};    // NOI18N
 /*private*/ static /*final*/ QList<QString> ds64sensors;//[] = {"A1", "S1", "A2", "S2", "A3", "S3", "A4", "S4"};                    // NOI18N
 /*private*/ static /*final*/ QList<QString> se8csensors;//[] = {"DS01", "DS02", "DS03", "DS04", "DS05", "DS06", "DS07", "DS08"};    // NOI18N

 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("LocoNetMessageInterpret");

protected:
 /*protected*/ static QString interpretDIRF(int dirf);
 /*protected*/ static QVector<QString> interpretF0_F4toStrings(int dirf);
 /*protected*/ static QString directionOfTravelString(bool isForward);
 /*protected*/ static QVector<QString> interpretF5_F8toStrings(int snd);

friend class LnSensor;
};

#endif // LOCONETMESSAGEINTERPRET_H
