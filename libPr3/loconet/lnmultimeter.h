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
 /*public*/ void initializeHardwareMeter();
 /*public*/ QString getHardwareMeterName();
 /*public*/ bool hasCurrent();
 /*public*/ bool hasVoltage();
 /*public*/ CurrentUnits getCurrentUnits();
 QObject* self() {return (QObject*)this;}

public slots:
 /*public*/ void message(LocoNetMessage* msg);


private:
 static Logger* log;
 /*private*/ SlotManager* sm = nullptr;
 /*private*/ LnTrafficController* tc = nullptr;

protected:
 /*protected*/ void requestUpdateFromLayout();

};

#endif // LNMULTIMETER_H
