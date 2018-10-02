#ifndef LLNMON_H
#define LLNMON_H

//#define EXTENDED

#include <QObject>
#include "lnconstants.h"
#include "loconetmessage.h"
#include "turnoutmanager.h"
#include "lnreportermanager.h"
#include "lnreporter.h"
#include "lnsensormanager.h"
#include "lnturnoutmanager.h"
#include "lnturnout.h"
#include "lnsensor.h"
#include "lnsensormanager.h"

class TurnoutManager;
class SensorManager;
//class LnReporterManager;
//class LnReporter;
class LIBPR3SHARED_EXPORT LlnMon : public QObject
{
    Q_OBJECT
public:
    QT_DEPRECATED /*public*/explicit LlnMon(QObject *parent = 0);
    QT_DEPRECATED /*public*/ LlnMon(LocoNetSystemConnectionMemo* memo, QObject *parent = 0);
    QT_DEPRECATED /*public*/ LlnMon(/*@Nonnull*/ TurnoutManager* turnoutManager,
         /*@Nonnull*/ SensorManager* sensorManager,
         /*@Nonnull*/ ReporterManager* reporterManager, QObject *parent = 0);
    QT_DEPRECATED /*public*/ LlnMon(/*@Nonnull*/ QString prefix, QObject *parent = 0);


    static QString getDeviceNameFromIPLInfo(int manuf, int type);
    static QString getSlaveNameFromIPLInfo(int manuf, int slaveNum);
    /**
     * This function creates a string representation of a LocoNet buffer. The
     * string may be more than one line, and is terminated with a newline.
     *
     * @return The created string representation.
     */
    QString displayMessage(LocoNetMessage l);
    /**
     * sets the loconet turnout manager which is used to find turnout "user names" from
     * turnout "system names"
     * @param loconetTurnoutManager
     */
    QT_DEPRECATED /*public*/ void setLocoNetTurnoutManager (TurnoutManager* loconetTurnoutManager);

    QT_DEPRECATED /*public*/ void setLocoNetReporterManager (ReporterManager* loconetReporterManager);

    /**
     * sets the loconet sensor manager which is used to find sensor "user names" from
     * sensor "system names"
     * @param loconetSensorManager
     */
    QT_DEPRECATED /*public*/ void setLocoNetSensorManager (SensorManager* loconetSensorManager);
    static int SENSOR_ADR(int a1, int a2);



signals:

public slots:
private:
    void common(QString prefix);
    /**
     * Flag that determines if we print loconet opcodes
     */
    bool showOpCode;

    /**
     * Flag that determines if we show track status on every slot read
     */
    bool showTrackStatus;

    /**
     * Most recent track status value
     */
    int trackStatus;
    /**
     * Convert bytes from LocoNet packet into a locomotive address.
     *
     * @param a1
     *            Byte containing the upper bits.
     * @param a2
     *            Byte containting the lower bits.
     * @return 1-4096 address
     */
    static int LOCO_ADR(int a1, int a2);
    /**
     * Convert bytes from LocoNet packet into a 1-based address for a sensor or
     * turnout.
     *
     * @param a1
     *            Byte containing the upper bits
     * @param a2
     *            Byte containing the lower bits
     * @return 1-4096 address
     */
//    static int SENSOR_ADR(int a1, int a2);
    /**
     * Take the LocoIO version number and convert to human friendly format.
     *
     * @param val
     *            The LocoIO version.
     * @return String with human readable format.
     */
    static QString dotme(int val);
    /**
     * Convert throttle ID to a human friendly format.
     *
     * @param id1
     *            Byte #1 of the ID.
     * @param id2
     *            Byte #2 of the ID.
     * @return String with human friendly format.
     */
    QString idString(int id1, int id2);
    /**
     * This function creates a string representation of the loco address in
     * addressLow & addressHigh in a form appropriate for the type of address (2
     * or 4 digit) using the Digitrax 'mixed mode' if necessary.
     *
     * @param addressLow
     * @param addressHigh
     * @return
     */
    static QString convertToMixed(int addressLow, int addressHigh);

    /*private*/ QString trackStatusByteToString(int trackStatusByte);
    /*private*/ QString figureAddressIncludingAliasing(int adr, int adr2, int ss2, int id1, int id2);
    /*private*/ QString getAlmTaskType(int taskTypeByte) ;
    QString turnoutPrefix;
    QString sensorPrefix;
    QString reporterPrefix;
    TurnoutManager* turnoutManager;
    ReporterManager* reporterManager;
    SensorManager* sensorManager;

    /*private*/ QString interpretOpcPeerXfer20_1(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20_2(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20_3(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20_4(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20_7(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20_10(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20_8(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20_0f(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer20Sub10(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer16(LocoNetMessage l);
    /*private*/ QString interpretSV1Message(LocoNetMessage l) ;
    /*private*/ QString interpretSV0Message(LocoNetMessage l);
    /*private*/ QString interpretSV2Message(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer10(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer9(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer7(LocoNetMessage l);
    /*private*/ QString interpretOpcPeerXfer(LocoNetMessage l);
    /*private*/ QString interpretLongAck(LocoNetMessage l);
    /*private*/ QString interpretPm4xPowerEvent(LocoNetMessage l);
    /*private*/ QString interpretOpSws(LocoNetMessage l);
    /*private*/ QString interpretDeviceType(LocoNetMessage l);
    /*private*/ QString interpretOpcMultiSense(LocoNetMessage l);
    /*private*/ QString interpretOpcMultiSenseTranspPresence(LocoNetMessage l);
    /*private*/ QString interpretOpcWrSlDataOpcSlRdData(LocoNetMessage l);
    /*private*/ QString interpretOpcInputRep(LocoNetMessage l);
    /*private*/ QString interpretOpcSwRep(LocoNetMessage l);
    /*private*/ QString interpretOpcSwAck(LocoNetMessage l);
    /*private*/ QString interpretOpcSwState(LocoNetMessage l);
    /*private*/ QString interpretOpcRqSlData(LocoNetMessage l);
    /*private*/ QString interpretOpcMoveSlots(LocoNetMessage l);
    /*private*/ QString interpretOpcConsistFunc(LocoNetMessage l);
    /*private*/ QString interpretOpcLocoSnd(LocoNetMessage l);
    /*private*/ QString interpretOpcLocoDirf(LocoNetMessage l);
    /*private*/ QString interpretOpcLocoSpd(LocoNetMessage l);
    /*private*/ QString interpretOpcPanelQuery(LocoNetMessage l);
    /*private*/ QString interpretOpcSwReq(LocoNetMessage l);
    /*private*/ QString interpretFastClockSlot(LocoNetMessage l, QString mode, int id1, int id2);
    /*private*/ QString interpretProgSlot(LocoNetMessage l, QString mode, int id1, int id2, int command);
    /*private*/ QString interpretCmdStnCfgSlotRdWr(LocoNetMessage l, int command);
    /*private*/ QString interpretCmdStnExtCfgSlotRdWr(LocoNetMessage l, int command);
    /*private*/ QString interpretStandardSlotRdWr(LocoNetMessage l, int id1, int id2, int command, int slot);
    /*private*/ QString interpretOpcPanelResponse(LocoNetMessage l);
#if 0
    /*private*/ QString interpretOpcLissyUpdate(LocoNetMessage l);
    /*private*/ QString interpretOpcImmPacket(LocoNetMessage l);
#endif
    /*private*/ QString interpretOpcPr3Mode(LocoNetMessage l);
#if 0
    /*private*/ QString interpretIb2Special(LocoNetMessage l);
    /*private*/ QString interpretIb2F9_to_F12(LocoNetMessage l);
#endif
    /*private*/ static /*final*/ QList<QString> ds54sensors; //[] = {"AuxA", "SwiA", "AuxB", "SwiB", "AuxC", "SwiC", "AuxD", "SwiD"};    // NOI18N
    /*private*/ static /*final*/ QList<QString> ds64sensors;//[] = {"A1", "S1", "A2", "S2", "A3", "S3", "A4", "S4"};                    // NOI18N
    /*private*/ static /*final*/ QList<QString> se8csensors;//[] = {"DS01", "DS02", "DS03", "DS04", "DS05", "DS06", "DS07", "DS08"};    // NOI18N

    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("Llnmon");
    /*private*/ QString fcTimeToString(int hour, int minute);

protected:
    /**
     * Global flag to indicate the message was not fully parsed, so the hex
     * should be included.
     */
    bool forceHex;
    /**
     * Format the message into a text string.  If forceHex is set
     * upon return, the message was not fully parsed.
     * @param l Message to parse
     * @return String representation
     */
    QString format(LocoNetMessage l);
    /*protected*/ QString interpretDIRF(int dirf);
    /*protected*/ QVector<QString> interpretF0_F4toStrings(int dirf);
    /*protected*/ QString directionOfTravelString(bool isForward);
    /*protected*/ QVector<QString> interpretF5_F8toStrings(int snd);

};

#endif // LLNMON_H
