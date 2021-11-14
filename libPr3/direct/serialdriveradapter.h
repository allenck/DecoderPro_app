#ifndef SERIALDRIVERADAPTER_H
#define SERIALDRIVERADAPTER_H

#include "portcontroller.h"

class SerialDriverAdapter : public PortController
{
 public:
  explicit SerialDriverAdapter(QObject *parent = nullptr);
  /*public*/ QVector<QString> getPortNames() override;

 private:
  QVector<QString>* portNameVector = nullptr;
  SerialPort* activeSerialPort = nullptr;

};

#endif // SERIALDRIVERADAPTER_H
