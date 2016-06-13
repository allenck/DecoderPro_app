#ifndef RFIDUSB_H
#define RFIDUSB_H

#include <QObject>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include "libPr3_global.h"
#include <QList>


struct rfidMsg
{
 QString portName;
 QString rfid;
};

class  RfidUsb : public QObject
{
 Q_OBJECT
public:
 explicit RfidUsb(QWidget *parent = 0);
 ~RfidUsb();
 bool openPort(QString portName = "ttyUSB0");
 bool isOpen();
 void closeSerialPort();
 //QList<QSerialPortInfo>* ports();
 QList<QSerialPortInfo> availPorts;
 QString portName();\
 QSerialPortInfo portInfo();

signals:
 void rfidMsgRcvd(rfidMsg* msg);
private slots:
 void dataReady();
 void handleError(QSerialPort::SerialPortError error);

private:
 QString _portName;
 QSerialPortInfo _portInfo;
 QSerialPort* serial;
 bool bIsOpen;
 QWidget *parent;
 QByteArray baRfid;
};

#endif // RFIDUSB_H
