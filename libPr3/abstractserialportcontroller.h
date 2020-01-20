#ifndef ABSTRACTSERIALPORTCONTROLLER_H
#define ABSTRACTSERIALPORTCONTROLLER_H

#include "abstractportcontroller.h"
#include <QHash>
#include <QVector>
#include <QStringList>
#include "exceptions.h"
//#include "systemconnectionmemo.h"
#include "serialportadapter.h"

class SerialPort;
class LIBPR3SHARED_EXPORT AbstractSerialPortController : public  SerialPortAdapter
{
    Q_OBJECT
public:
 explicit AbstractSerialPortController(SystemConnectionMemo* connectionMemo, QObject *parent = 0);
    ~AbstractSerialPortController(){}
     QString getOptionState(QString option);
 /**
  * Standard error handling for port-busy case
  */
 /*public*/ QString handlePortBusy(PortInUseException p,
                       QString portName,
                       Logger* log);
 /**
  * Standard error handling for port-not-found case
  */
 /*public*/ virtual QString handlePortNotFound(NoSuchPortException p,
                         QString portName,
                         Logger* log);
    /*public*/ void _connect(); // throw( Exception);
 /*public*/ virtual void setPort(QString port);
    /*public*/  QString getCurrentPortName();
 /*public*/ QVector<QString> getPortNames();
 /**
  * Set the baud rate.  This records it for later.
  */
 /*public*/ void configureBaudRate(QString rate);
 /*public*/ QString getCurrentBaudRate();
 /**
  * Get an array of valid baud rates as integers. This allows subclasses
  * to change the arrays of speeds.
  *
  * This method need not be reimplemented unless the subclass is using
  * currentBaudNumber, which requires it.
  */
    /*public*/ virtual QVector<int> validBaudNumbers();
 /**
  * Convert a baud rate string to a number.
  *
  * Uses the validBaudNumber and validBaudRates methods to do this.
  * @return -1 if no match (configuration system should prevent this)
  */
 /*public*/ virtual int currentBaudNumber(QString currentBaudRate);
 /*This in place here until all systems are converted over to the systemconnection memo
 this will then become abstract, once all the code has been refactored*/
// /*public*/ SystemConnectionMemo* getSystemConnectionMemo();
 /*Set disable should be handled by the local port controller in each connection
 this is abstract in the Portcontroller and can be removed once all the other codes has
 been refactored */
 /*public*/  void setDisabled(bool disabled);
 /*Dispose should be handled by the port adapters and this should be abstract
 However this is in place until all the other code has been refactored */
 /*public*/  void dispose();
/**
 * This is called when a connection is initially lost.  It closes the client side
 * socket connection, resets the open flag and attempts a reconnection.
 */
/*public*/ void recover();
 /**
  * Attempts to reconnect to a failed Server
  */
 /*public*/ void reconnect();
 virtual QStringList validBaudRates();

signals:
    
public slots:
private:
 QVector<QString> portNameVector;
Logger* log;
protected:
 //QMap<QString, Option> options;
 /*protected*/ QString mPort;
 /*protected*/ QString mBaudRate;
 /*Each serial port adapter should handle this and it should be abstract.
  However this is in place until all the other code has been refactored */
 /*protected*/ virtual void closeConnection() throw( Exception);// { System.out.println("crap Called"); }
 /*Each port adapter should handle this and it should be abstract.
  However this is in place until all the other code has been refactored */
 /*protected*/ virtual void resetupConnection();
/*protected*/ void configureLeadsAndFlowControl(SerialPort* serialPort, int flow, bool rts, bool dtr);
/*protected*/ void configureLeadsAndFlowControl(SerialPort* serialPort, int flow);
/*protected*/ void setPortEventLogging(SerialPort* port);

};

#endif // ABSTRACTSERIALPORTCONTROLLER_H
