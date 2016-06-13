#ifndef LOCOIOMODULES_H
#define LOCOIOMODULES_H

#include <QObject>
#include "locoiodata.h"
#include "locoioaddress.h"
#include "locoio_global.h"

class Logger;
class Sql;
class LocoIODialog;
class LocoNetMessage;
class QMenu;
class QSignalMapper;
class LocoIOData;
class LocoNetSystemConnectionMemo;

class LOCOIOSHARED_EXPORT LocoIOModules : public QObject
{
 Q_OBJECT
public:
 static LocoIOModules* instance();
 void startProbe();
 QMenu* getMenu();
 /*public*/ void setLBVersion(QString version);
 /*public*/ QString getLBVersion();
 QList<LocoIOAddress*> probedAddresses();

signals:
 void probeCompleted(QList<LocoIOAddress* > list);

public slots:
 void onMessageReceived(LocoNetMessage* msg);
 void onProbeCompleted(QList<LocoIOAddress*>);
 void onLocoIO_selected(int index);


private:
 static LocoIOModules* root;
 static void setRootInstance();
 LocoNetSystemConnectionMemo* memo;
 LocoIOData* data;
 QSignalMapper* signalMapper;
 QMenu* menu;
 QList<LocoIOAddress*> list;
 QVector<LocoIODialog*> moduleDlg;
 bool bHexValues;
 Sql* sql;
 void on_actionLocoIO_triggered(/*bool bNewAddress*/);
 Logger * log;
 QList<LocoIOAddress*> _probedAddresses;
 QTimer* probeTimer;
 static const int TIMEOUT=2000;    // ms
 /*private*/ int lastOpCv;// = -1;
 bool bProbing; // false
 LnTrafficController* tc;
 LocoIOAddress* address;
 /**
  * LocoBuffer is always address 0x01 0x50
  */
 /*private*/ static /*final*/ const int locoBufferAddress;//  = 0x0150;
 /*private*/ QString locoBufferVersion;// = "<unknown>";
 /*private*/ QString locoIOVersion;//     = "<unknown>";
 /*private*/ QString status;//            = "<unknown>";  // LocoIO activity status
 /*private*/ QString dotme(int val);
 int timeoutcounter;
 //bool compare(LocoIOAddress* a1, LocoIOAddress* a2);


private slots:
 void probeTimeout();


protected:
 explicit LocoIOModules(QObject *parent = 0);
 /*protected*/ int highPart(int value); // generally value 1
 /*protected*/ int lowPart(int value); // generally value 2

};

#endif // LOCOIOMODULES_H
