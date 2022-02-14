#ifndef LNMULTIMETER_H
#define LNMULTIMETER_H
#include "abstractmultimeter.h"
#include "lnconstants.h"

class LocoNetMessage;
class LocoNetSystemConnectionMemo;
class SlotManager;
class LnTrafficController;
class LnMultiMeter : public AbstractMultiMeter
{
 Q_OBJECT
public:
 LnMultiMeter(LocoNetSystemConnectionMemo* scm, QObject* parent = nullptr);
 ~LnMultiMeter() {}
 /*public*/ void initializeHardwareMeter()override;
 /*public*/ QString getHardwareMeterName()override;
 /*public*/ bool hasCurrent()override;
 /*public*/ bool hasVoltage()override;
 /*public*/ CurrentUnits getCurrentUnits()override;

 QObject* self() override{return (QObject*)this;}

public slots:
 /*public*/ void message(LocoNetMessage* msg);


private:
 static Logger* log;
 /*private*/ SlotManager* sm = nullptr;
 /*private*/ LnTrafficController* tc = nullptr;

protected:
 /*protected*/ void requestUpdateFromLayout()override;

};

#endif // LNMULTIMETER_H
