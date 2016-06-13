#ifndef FTDITHREAD_H
#define FTDITHREAD_H

#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include "ftdilib_global.h"
#include <QObject>

#ifdef WIN32
#include <WINDOWS.H>
#include <WINDOWS.H>
//Missing from windows.h
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

struct ftdiMsg
{
 QString serial;
 QString rfid;
};

class FTDILIBSHARED_EXPORT ftdithread : public QThread
{
 Q_OBJECT
public:
 explicit ftdithread(QObject *parent = 0);
 ~ftdithread();
 bool openFtdiPort(QString serial);
 void run();
 void setQuit();
 bool isOpen();
 QString currPort();
 ftdiMsg* lastMsg();

signals:
 void error(QString err);
 void rfidMsgRcvd(ftdiMsg* msg);
public slots:
 void on_finished();

private:
 FT_HANDLE ftHandle;
 QMutex mutex;
 QWaitCondition cond;
 bool quit;
 QString serial;
 QByteArray baRfid;
 bool bIsOpen;
 ftdiMsg msg;

};

#endif // FTDITHREAD_H
