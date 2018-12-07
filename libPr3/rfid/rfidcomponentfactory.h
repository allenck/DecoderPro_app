#ifndef RFIDCOMPONENTFACTORY_H
#define RFIDCOMPONENTFACTORY_H
#include "componentfactory.h"

class RfidSystemConnectionMemo;
class RfidComponentFactory : public ComponentFactory
{
public:
 /*public*/ RfidComponentFactory(RfidSystemConnectionMemo* memo, QObject* parnt = nullptr);
 /*public*/ QMenu* getMenu();


private:
 RfidSystemConnectionMemo* memo;

};

#endif // RFIDCOMPONENTFACTORY_H
