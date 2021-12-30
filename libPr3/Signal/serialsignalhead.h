#ifndef SERIALSIGNALHEAD_H
#define SERIALSIGNALHEAD_H

#include "defaultsignalhead.h"
#include <QMainWindow>

class GrapevineSystemConnectionMemo;
class SerialSignalHead : public DefaultSignalHead
{
 public:
  /*public*/ SerialSignalHead(QString systemName, GrapevineSystemConnectionMemo* _memo, QObject* parent= nullptr);
  /*public*/ SerialSignalHead(QString systemName, QString userName, GrapevineSystemConnectionMemo* _memo, QObject* parent= nullptr);


 private:
  GrapevineSystemConnectionMemo* memo = nullptr;
  static Logger* log;
  // data members
  QString tSystemName; // System Name of this signal head
  int output;         // output connector number, 0-23
  int bank;           // bank number, 0-3

 protected:
  /*protected*/ void updateOutput();

};

#endif // SERIALSIGNALHEAD_H
