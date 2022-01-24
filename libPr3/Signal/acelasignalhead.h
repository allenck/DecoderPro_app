#ifndef ACELASIGNALHEAD_H
#define ACELASIGNALHEAD_H

#include "defaultsignalhead.h"

class AcelaSystemConnectionMemo;
class AcelaSignalHead : public DefaultSignalHead
{
 public:
  AcelaSignalHead(QString systemName, AcelaSystemConnectionMemo* memo, QObject *parent = nullptr);
  /*public*/  AcelaSignalHead(QString systemName, QString userName, AcelaSystemConnectionMemo* memo, QObject *parent=nullptr);
  /*public*/  void startFlash() override;
  /*public*/  void stopFlash()override;

 private:
  static Logger* log;
  AcelaSystemConnectionMemo* _memo = nullptr;
  // data members
  QString tSystemName; // System Name of this signal head
  int addr;         // output address

 protected:
  /*protected*/ void updateOutput()override;

};

#endif // ACELASIGNALHEAD_H
