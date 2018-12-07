#ifndef RFIDPORTCONTROLLER_H
#define RFIDPORTCONTROLLER_H
#include "abstractserialportcontroller.h"

class RfidSystemConnectionMemo;
class RfidPortController : public AbstractSerialPortController
{
public:
 /*public*/ SystemConnectionMemo* getSystemConnectionMemo();

protected:
 /*protected*/ RfidPortController(RfidSystemConnectionMemo* connectionMemo, QObject* parent = nullptr);

};

#endif // RFIDPORTCONTROLLER_H
