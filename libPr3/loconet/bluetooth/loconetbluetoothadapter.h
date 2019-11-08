#ifndef LOCONETBLUETOOTHADAPTER_H
#define LOCONETBLUETOOTHADAPTER_H
#include "lnportcontroller.h"

class LocoNetBluetoothAdapter : public LnPortController
{
public:
 LocoNetBluetoothAdapter(QObject *parent = nullptr);
 /*public*/ LocoNetBluetoothAdapter(LocoNetSystemConnectionMemo* adapterMemo, QObject* parent = nullptr);
 /*public*/ QVector<QString> getPortNames();
 /*public*/ QString openPort(QString portName, QString appName);
 /*public*/ void configure();
 /*public*/ QDataStream* getInputStream();
 /*public*/ QDataStream* getOutputStream();
 /*public*/ bool status();
 /*public*/ QStringList validBaudRates();
 /*public*/ QVector<int> validBaudNumbers();

private:
 static Logger* log;
 QVector<QString> portNameVector;// = null;
 // private control members
 /*private*/ bool opened = false;
 /*private*/ QDataStream* in = nullptr;
 /*private*/ QDataStream* out = nullptr;

};

class BluetoothStateException : public IOException
{
 BluetoothStateException(QString msg = "") : IOException(msg) {}
};
#endif // LOCONETBLUETOOTHADAPTER_H
