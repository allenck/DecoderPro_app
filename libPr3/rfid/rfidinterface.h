#ifndef RFIDINTERFACE_H
#define RFIDINTERFACE_H
#include "rfidmessage.h"
#include "rfidlistener.h"


/*public*/ class RfidInterface  //: public QObject
{
 //Q_OBJECT
public:
 //RfidInterface(QObject* parent = nullptr) : QObject(parent) {}
 /*public*/ virtual void addRfidListener( RfidListener* l) {}
 /*public*/ virtual void removeRfidListener( RfidListener* l) {}

 bool status();   // true if the implementation is operational

 virtual void sendRfidMessage(RfidMessage* m, RfidListener* l) {}  // 2nd arg gets the reply
};
Q_DECLARE_INTERFACE(RfidInterface, "RfidInterface")
#endif // RFIDINTERFACE_H
