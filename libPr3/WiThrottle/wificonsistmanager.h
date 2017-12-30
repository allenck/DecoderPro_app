#ifndef WIFICONSISTMANAGER_H
#define WIFICONSISTMANAGER_H
#include "abstractconsistmanager.h"

class ControllerInterface;
class Logger;
class WiFiConsistManager : public AbstractConsistManager
{
public:
 WiFiConsistManager();
 /*public*/ DccLocoAddress* stringToDcc(QString s);
 /*public*/ bool checkForBroadcastAddress(DccLocoAddress* addr);
 /*public*/ Consist* addConsist(DccLocoAddress* address);
 /*public*/ bool isCommandStationConsistPossible();
 /*public*/ bool csConsistNeedsSeperateAddress();
 /*public*/ void addControllerListener(ControllerInterface* listener);
 /*public*/ void removeControllerListener(ControllerInterface* listener);

private:
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(WiFiConsistManager.class.getName());
 QVector<ControllerInterface*>* listeners;// = NULL;
 bool isValid = false;

};

#endif // WIFICONSISTMANAGER_H
