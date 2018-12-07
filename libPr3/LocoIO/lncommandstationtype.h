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
    enum LnCommandStationTypes
    {
     COMMAND_STATION_UNKNOWN = -1,
     COMMAND_STATION_DCS100, //      ("DCS100 (Chief)",              true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_DCS200, //      ("DCS200",                      true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
     COMMAND_STATION_DCS050,//      ("DCS50 (Zephyr)",              true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
            COMMAND_STATION_DCS051,//      ("DCS51 (Zephyr Xtra)",         true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
            COMMAND_STATION_DB150,//       ("DB150 (Empire Builder)",      false,  true,   "LnThrottleManager",    "SlotManager"),  // NOI18N
            COMMAND_STATION_LBPS,//        ("LocoBuffer (PS)",             true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
            COMMAND_STATION_MM,//          ("Mix-Master",                  false,  true,   "LnThrottleManager",    "SlotManager"),  // NOI18N
            COMMAND_STATION_IBX_TYPE_1,//  ("Intellibox-I",                true,   true,   "Ib1ThrottleManager",   "SlotManager"), // NOI18N
            COMMAND_STATION_IBX_TYPE_2,//  ("Intellibox-II",               true,   true,   "Ib2ThrottleManager",   "UhlenbrockSlotManager"), // NOI18N
            COMMAND_STATION_LOCOCENTRAL, // "LocoCentral"

            COMMAND_STATION_PR3_ALONE,//   ("PR3 standalone programmer",   true,   false,  "LnThrottleManager",    "SlotManager"),  // NOI18N
            COMMAND_STATION_PR2_ALONE, //"PR2 standalone programmer", true, false, "LnThrottleManager", "SlotManager"), // NOI18N
            COMMAND_STATION_STANDALONE  //("Stand-alone LocoNet",         false,  false,  "LnThrottleManager",    "SlotManager");  // NOI18N
    };
    //explicit LnCommandStationType(QObject *parent = 0);
    LnCommandStationType(QString name, bool canRead, bool progEndOp, QString throttleClassName, QString slotManagerClassName, LnCommandStationTypes type = COMMAND_STATION_UNKNOWN, QObject *parent = 0);
    /*public*/ QString getName();
    /*public*/ bool getCanRead();
    /*public*/ QString toString();
    /*public*/ bool getProgPowersOff();
    static /*public*/ LnCommandStationType* getByName(QString name);
    static /*public*/ LnCommandStationType* getByType(LnCommandStationTypes type);
    /*public*/ ThrottleManager* getThrottleManager(LocoNetSystemConnectionMemo* memo);
    /*public*/ SlotManager* getSlotManager(LnTrafficController* tc);
    static QStringList commandStationNames();
signals:

public slots:
private:
    QString name;
    bool canRead;
    bool progEndOp;
    QString throttleClassName;
    QString slotManagerClassName;
    Logger* log;
    LnCommandStationTypes type;
    static QList<LnCommandStationType*> values;

};

#endif // LNCOMMANDSTATIONTYPE_H
