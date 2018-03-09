#ifndef SPROGPORTCONTROLLER_H
#define SPROGPORTCONTROLLER_H
#include "abstractserialportcontroller.h"
#include "sprogsystemconnectionmemo.h"
namespace Sprog {

 class SprogPortController : public AbstractSerialPortController
 {
  Q_OBJECT
 public:
  /*public*/ SprogSystemConnectionMemo* getSystemConnectionMemo();

 protected:
  /*protected*/ SprogPortController(SprogSystemConnectionMemo* connectionMemo,QObject* parent = 0);

 };
}
#endif // SPROGPORTCONTROLLER_H
