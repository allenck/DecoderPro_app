#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include "exceptions.h"
#include "logger.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT SerialPort : public QObject
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    QSerialPortInfo info;
    QDataStream* istream;
    QDataStream* ostream;
    QDataStream* getOutputStream(){return ostream;}
    QDataStream* getInputStream(){return istream;}
    QSerialPort* getSerialPort() { return serial;}
    qint32 getBaudRate();
    void setSerialPortParams(int i, int i1, int i2, int i3) throw(UnsupportedCommOperationException);

    bool isDTR(){QSerialPort::PinoutSignals sig = serial->pinoutSignals(); return sig & serial->DataTerminalReadySignal;}
    bool isRTS(){QSerialPort::PinoutSignals sig = serial->pinoutSignals(); return sig & serial->RequestToSendSignal;}
    bool isDSR(){QSerialPort::PinoutSignals sig = serial->pinoutSignals(); return sig & serial->DataSetReadySignal;}
    bool isCTS(){QSerialPort::PinoutSignals sig = serial->pinoutSignals(); return sig & serial->ClearToSendSignal;}
    bool isCD(){QSerialPort::PinoutSignals sig = serial->pinoutSignals(); return sig & serial->DataCarrierDetectSignal;}
    int baudRate() {return serial->baudRate();}
    int databits();
    QString parity();
    QString stopBits();
    QSerialPort* device();
    qint32 getReceiveTimeout();
    void enableReceiveTimeout(qint32);
    bool isReceiveTimeoutEnabled();
    QSerialPort::SerialPortError lastError();


    static const int DATABITS_8 =  QSerialPort::Data8;
    static const int STOPBITS_1 =  QSerialPort::OneStop;
    static const int PARITY_NONE = QSerialPort::NoParity;
    static const int FLOWCONTROL_RTSCTS_OUT = QSerialPort::HardwareControl;
    static const int FLOWCONTROL_RTSCTS_IN = QSerialPort::HardwareControl;
    static const int FLOWCONTROL_NONE = QSerialPort::NoFlowControl;
    void setRTS(bool bRts);
    void setDTR(bool bDTR);
    void setFlowControlMode(int flow) throw(UnsupportedCommOperationException);
    int getFlowControlMode();
    void setPortName(QString portName);
    QString errorString();
    void clear();
    bool flush();
    QString flowControl();
    bool open(QString portName, QIODevice::OpenMode mode);
    bool open(QIODevice::OpenMode mode);

signals:
    void error(QString s);

public slots:
//    void dataReady();
//    void xmtTimer();
    void OnError();
    void OnDataReady();
private:
 Logger* log;
 QByteArray* rcvBuffer;
 QByteArray* xmtBuffer;
 QSerialPort* serial;
 QString portName;
 bool bOpened;
 qint32 rcvTimeout;
};

#endif // SERIALPORT_H
