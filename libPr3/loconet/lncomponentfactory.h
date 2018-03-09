#ifndef LNCOMPONENTFACTORY_H
#define LNCOMPONENTFACTORY_H
#include "componentfactory.h"
#include "loconetsystemconnectionmemo.h"

class LnComponentFactory : public ComponentFactory
{
 Q_OBJECT
public:
 LnComponentFactory(LocoNetSystemConnectionMemo* memo);
 /*public*/ QMenu* getMenu(QWidget* frame);

private:
 LocoNetSystemConnectionMemo* memo;

};

#endif // LNCOMPONENTFACTORY_H
