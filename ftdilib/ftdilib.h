#ifndef FTDILIB_H
#define FTDILIB_H

#include "ftdilib_global.h"
#include <QObject>
#include <QStringList>
#include <QMap>

#ifdef WIN32
//Missing from windows.h
#include <WINDOWS.H>
#ifndef PVOID
typedef VOID *PVOID;
#endif
#endif
extern "C"
{
#ifdef WIN32
#include "win32/ftd2xx.h"
#else
#include <ftd2xx.h>
#endif

}
#include "ftdithread.h"

class FTDILIBSHARED_EXPORT Ftdilib : public QObject
{
 Q_OBJECT
public:
 Ftdilib(QObject *parent=0);
 ~Ftdilib();
 void loadDeviceList();
// ftdithread* thread();
 bool openPort(QString serial);
// bool isOpen();
 void closeSerialPort();
 QStringList availPorts;
 QString serial();
signals:
 void rfidMsg(ftdiMsg* msg);
private:
 FT_DEVICE_LIST_INFO_NODE *devInfo;
// ftdithread* _thread;
 QMap<QString, ftdithread*> threadMap;
// bool bIsOpen;
 QString _serial;
private slots:
 void OnRfidRcvd(ftdiMsg* msg);
};

#endif // FTDILIB_H
