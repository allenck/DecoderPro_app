#ifndef LNCOMMANDSTATIONTYPE_H
#define LNCOMMANDSTATIONTYPE_H

#include <QObject>
#include "logger.h"
#include <QMap>
#include "libPr3_global.h"

class SlotManager;
class LnTrafficController;
class ThrottleManager;
class LocoNetSystemConnectionMemo;
class LIBPR3SHARED_EXPORT LnCommandStationType : public QObject
{
    Q_OBJECT
public:
    /*protected*/ enum ReadsFromServiceModeTrack {
        NO_SVC_MODE_READS, CAN_READ_ON_SVC_TRACK
    };

    /*protected*/ enum ProgDepowersTrack {
        TRACK_OFF_WHEN_PROGRAMMING, TRACK_ALIVE_WHEN_PROGRAMMING
    };

    /*protected*/ enum IdleSupport {
        NO_OPC_IDLE_SUPPORT, SUPPORTS_OPC_IDLE
    };

    /*protected*/ enum MultiMeterSupport {
        NO_MULTIMETER_SUPPORT, SUPPORTS_MULTIMETER_FUNCTION
    };

    /*protected*/ enum LocoResetSupport {
        NO_LOCO_RESET_SUPPORT, SUPPORTS_LOCO_RESET_FUNCTION
    };
public:
    enum LnCommandStationTypes
    {
     COMMAND_STATION_UNKNOWN = -1,
     COMMAND_STATION_DCS100, //      ("DCS100 (Chief)",              true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_DCS200, //      ("DCS200",                      true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_DCS240, //      ("DCS240 (Advanced Command Station)", true, false, "LnThrottleManager", "SlotManager", true, true), // NOI18N
     COMMAND_STATION_DCS210, //      ("DCS210 (Evolution Command Station)", true, false, "LnThrottleManager", "SlotManager", true, true), // NOI18N
     COMMAND_STATION_DCS050,//      ("DCS50 (Zephyr)",              true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_DCS051,//      ("DCS51 (Zephyr Xtra)",         true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_DCS052,
     COMMAND_STATION_DB150,//       ("DB150 (Empire Builder)",      false,  true,   "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_LBPS,//        ("LocoBuffer (PS)",             true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_MM,//          ("Mix-Master",                  false,  true,   "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_IBX_TYPE_1,//  ("Intellibox-I",                true,   true,   "Ib1ThrottleManager",   "SlotManager"), // NOI18N
     COMMAND_STATION_IBX_TYPE_2,//  ("Intellibox-II",               true,   true,   "Ib2ThrottleManager",   "UhlenbrockSlotManager"), // NOI18N
     COMMAND_STATION_LOCOCENTRAL, // "LocoCentral"

     COMMAND_STATION_PR3_ALONE,//   ("PR3 standalone programmer",   true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_PR2_ALONE, //"PR2 standalone programmer", true, false, "LnThrottleManager", "SlotManager"), // NOI18N
     COMMAND_STATION_STANDALONE,  //("Stand-alone LocoNet",         false,  false,  "LnThrottleManager",    "SlotManager");  // NOI18N
     COMMAND_STATION_PR4_ALONE,    //("PR4 standalone programmer,
     COMMAND_STATION_USB_DCS240_ALONE,
     COMMAND_STATION_USB_DCS52_ALONE
    };
    //explicit LnCommandStationType(QObject *parent = 0);
    LnCommandStationType(LnCommandStationTypes type, QString name, ReadsFromServiceModeTrack canRead,
            ProgDepowersTrack progEndOp,
            QString throttleClassName, QString slotManagerClassName,
            IdleSupport supportsIdle, MultiMeterSupport supportMultiMeter,
            LocoResetSupport supportsLocoReset);
    /*public*/ QString getName();
    /*public*/ bool getCanRead();
    /*public*/ QString toString();
    /*public*/ bool getProgPowersOff();
    static /*public*/ LnCommandStationType* getByName(QString name);
    static /*public*/ LnCommandStationType* getByType(LnCommandStationTypes type);
    /*public*/ ThrottleManager* getThrottleManager(LocoNetSystemConnectionMemo* memo);
    /*public*/ SlotManager* getSlotManager(LnTrafficController* tc);
    static QStringList commandStationNames();
    /*public*/ bool getImplementsIdle();
    /*public*/ bool getSupportsMultimeter();
    /*public*/ LnCommandStationTypes getType();
    /**
     * Returns whether CS supports a Loco Reset feature.
     *
     * For this purpose "supports" means that the command station will send
     * OPC_RE_LOCO_RESET when it clears all slots.
     *
     * @return true if command station supports OPC_RE_LOCO_RESET message
     */
    /*public*/ bool getSupportsLocoReset();

signals:

public slots:
private:
    QString name;
    bool canRead;
    bool progEndOp;
    bool supportsMultiMeter;
    bool supportsIdle;
    QString throttleClassName;
    QString slotManagerClassName;
    Logger* log;
    LnCommandStationTypes type;
    static QList<LnCommandStationType*> values;
    LocoResetSupport supportsLocoReset;
    friend class HexFileServer;
    friend class LoconetSystemConnectionMemoTest;
};

#endif // LNCOMMANDSTATIONTYPE_H
