#ifndef STANDALONEMESSAGE_H
#define STANDALONEMESSAGE_H
#include "rfid/rfidmessage.h"

class StandaloneMessage : public RfidMessage
{
 Q_OBJECT
public:
 /*public*/ StandaloneMessage(int l, QObject *parent = nullptr);
 /*public*/ StandaloneMessage(QString m, int l, QObject * parent = nullptr);

};

#endif // STANDALONEMESSAGE_H
