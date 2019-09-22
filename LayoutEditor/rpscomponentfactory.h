#ifndef RPSCOMPONENTFACTORY_H
#define RPSCOMPONENTFACTORY_H
#include "componentfactory.h"

class RpsSystemConnectionMemo;
class RpsComponentFactory : public ComponentFactory
{
public:
 /*public*/ RpsComponentFactory(RpsSystemConnectionMemo* memo);
 /*public*/ QMenu* getMenu();


private:
 RpsSystemConnectionMemo* memo;

};

#endif // RPSCOMPONENTFACTORY_H
