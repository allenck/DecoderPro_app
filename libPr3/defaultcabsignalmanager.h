#ifndef DEFAULTCABSIGNALMANAGER_H
#define DEFAULTCABSIGNALMANAGER_H
#include "abstractcabsignalmanager.h"

class DefaultCabSignalManager : public AbstractCabSignalManager
{
 Q_OBJECT
public:
 DefaultCabSignalManager(QObject* parent = nullptr);
 QObject* self() {return (QObject*)this;}

protected:
 /*protected*/ CabSignal* createCabSignal(LocoAddress* address) override;

};

#endif // DEFAULTCABSIGNALMANAGER_H
