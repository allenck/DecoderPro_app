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

class LnTurnoutManager;
class LnSensorManager;
//class LnReporterManager;
//class LnReporter;
class LIBPR3SHARED_EXPORT LlnMon : public QObject
{
    Q_OBJECT
public:
    explicit LlnMon(QObject *parent = 0);
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
    /*public*/ void setLocoNetTurnoutManager (LnTurnoutManager* loconetTurnoutManager);

    /*public*/ void setLocoNetReporterManager (LnReporterManager* loconetReporterManager);

    /**
     * sets the loconet sensor manager which is used to find sensor "user names" from
     * sensor "system names"
     * @param loconetSensorManager
     */
    /*public*/ void setLocoNetSensorManager (LnSensorManager* loconetSensorManager);
    static int SENSOR_ADR(int a1, int a2);


signals:

public slots:
private:
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
    QString locoNetTurnoutPrefix;
    QString locoNetSensorPrefix;
    QString locoNetReporterPrefix;
    LnTurnoutManager* turnoutManager;
#if 1
    LnReporterManager* reporterManager;
#endif

    LnSensorManager* sensorManager;
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

};

#endif // LLNMON_H
