#ifndef LNSENSORADDRESS_H
#define LNSENSORADDRESS_H

#include <QObject>
#include "logger.h"
#include "loconetmessage.h"

class LnSensorAddress : public QObject
{
    Q_OBJECT
public:
    /*public*/ LnSensorAddress(int sw1, int sw2, QString prefix);
    /*public*/ LnSensorAddress(QString s, QString prefix);
    void reportParseError(QString s);
    /**
     * Update a LocoNet message to have this address.
     * @param m
     */
    /*public*/ void insertAddress(LocoNetMessage* m);
    // convenient calculations
    /*public*/ bool matchAddress(int a1, int a2); // a1 is byte 1 of ln msg, a2 is byte 2
    // accessors for parsed data
    /*public*/ int getLowBits();
    /*public*/ int getHighBits();
    /**
     * The bit representing the Aux or Sensor input
     * @return 0x20 for aux input, 0x00 for switch input
     */
    /*public*/ int getASBit();
    /*public*/ bool isValid();

    /*public*/ QString toString();
    /**
     * Name in the 1-4096 space
     * @return LSnnn
     */
    /*public*/ QString getNumericAddress();
    /**
     * Name in the DS54 space
     * @return LSnnnA or LSnnnS, depending on Aux or Switch input
     */
    /*public*/ QString getDS54Address();
    /**
     * Name in the BDL16 space
     * @return e.g. LSnnnA3, with nnn the BDL16 number,
     *              A the section number, and 3 the channel number
     */
    /*public*/ QString getBDL16Address();

    
signals:
    
public slots:

private:
    Logger log;
    int _low;
    int _high;
    int _as;
    QString prefix;

    bool _valid;
protected:
    /**
     * @return integer value of this address in 0-4095 space
     */
    /*protected*/ int asInt();

};

#endif // LNSENSORADDRESS_H
