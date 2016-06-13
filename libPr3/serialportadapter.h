#ifndef SERIALPORTADAPTER_H
#define SERIALPORTADAPTER_H

//#include "portadapter.h"
#include "exceptions.h"
#include "logger.h"
#include <QVector>
#include "abstractportcontroller.h"

class SerialPortAdapter : public AbstractPortController
{
    //Q_OBJECT
public:
    explicit SerialPortAdapter(SystemConnectionMemo* connectionMemo, QObject *parent = 0)
        : AbstractPortController(connectionMemo, parent) {}
    ~SerialPortAdapter() {}
    /** Provide a vector of valid port names, each a String. */
    virtual QVector<QString> getPortNames() {return QVector<QString>();}
    /** Open a specified port.  The appname argument is to be provided to the
     * underlying OS during startup so that it can show on status displays, etc
     */
    virtual QString openPort(QString /*portName*/, QString /*appName*/) {return "";}
    /** Configure all of the other jmrix widgets needed to work with this adapter
     */
     //void configure() {}
    /** Query the status of this connection.  If all OK, at least
     * as far as is known, return true */
     //bool status() {return false;}
    /**
     * Remember the associated port name
     * @param s
     */
    virtual void setPort(QString /*s*/) {}
     QString getCurrentPortName() {return "";}
    /**
     * Get an array of valid baud rates; used to display valid options.
     */
    virtual QStringList validBaudRates() { return QStringList();}

    /**
     * Set the baud rate.  Only to be used after construction, but
     * before the openPort call.
     */
    virtual void configureBaudRate(QString /*rate*/) {}

    virtual QString getCurrentBaudRate() {return "";}

    /**
     * Set the first port option.  Only to be used after construction, but
     * before the openPort call
     */
     //void configureOption1(QString /*value*/) {}

    /**
     * Set the second port option.  Only to be used after construction, but
     * before the openPort call
     */
     //void configureOption2(QString /*value*/) {}

    /**
     * Set the second port option.  Only to be used after construction, but
     * before the openPort call
     */
     //void configureOption3(QString /*value*/) {}

    /**
     * Set the second port option.  Only to be used after construction, but
     * before the openPort call
     */
     //void configureOption4(QString /*value*/) {}

    /**
     * Error handling for busy port at open.
     * @see jmri.jmrix.AbstractSerialPortController
     */
    virtual QString handlePortBusy(PortInUseException /*p*/,
                            QString /*portName*/,
                                   Logger /*log*/) {return "";}


     /**
     * Return the System Manufacturers Name
     */
     //QString getManufacturer() {return "";}

    /**
    * Set the System Manufacturers Name
    */
     //void setManufacturer(QString /*Manufacturer*/) {}
signals:
    
public slots:
    
};
//Q_DECLARE_INTERFACE(SerialPortAdapter, "Serial port adapter")
#endif // SERIALPORTADAPTER_H
