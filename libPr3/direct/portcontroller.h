#ifndef PORTCONTROLLER_H
#define PORTCONTROLLER_H

#include "abstractserialportcontroller.h"
#include "directsystemconnectionmemo.h"

class PortController : public AbstractSerialPortController
{
  Q_OBJECT
 protected:
  /*protected*/ PortController(DirectSystemConnectionMemo* memo, QObject* parent = 0);
  /*protected*/ PortController(QObject *parent = 0);

};

#endif // PORTCONTROLLER_H
