#ifndef RFIDSERIALDRIVERADAPTER_H
#define RFIDSERIALDRIVERADAPTER_H
#include "rfidportcontroller.h".h"

class SerialPort;
class RfidSerialDriverAdapter : public RfidPortController //SerialPortAdapter
{
public:
 RfidSerialDriverAdapter(QObject *parent = nullptr);
 /*public*/ QString openPort(QString portName, QString appName);
 /*public*/ bool okToSend();
 /*public*/ void configure();
 /*public*/ QDataStream* getInputStream();
 /*public*/ QDataStream* getOutputStream();
 /*public*/ bool status();
 /*public*/ QStringList validBaudRates();
 /*public*/ void configureBaudRate(QString rate);

private:
 SerialPort* activeSerialPort = nullptr;
 static Logger* log;
 // private control members
 /*private*/ bool opened = false;
 QDataStream* serialStream = nullptr;

protected:
 /*protected*/ QStringList validSpeeds;// = new String[]{"(automatic)"};
 /*protected*/ QVector<int> validSpeedValues;// = new int[]{9600};
 /*protected*/ QString selectedSpeed;// = validSpeeds[0];
 /*protected*/ void setSerialPort() throw (UnsupportedCommOperationException);

};

#endif // RFIDSERIALDRIVERADAPTER_H
