#ifndef CONSISTCONTROLLER_H
#define CONSISTCONTROLLER_H

#include "abstractcontroller.h"

class DccLocoAddress;
class Consist;
class Logger;
class AbstractConsistManager;
class ConsistFile;
class ConsistController : public AbstractController
{
 Q_OBJECT
public:
 explicit ConsistController(QObject *parent = 0);
 /*public*/ void sendConsistListType();
 /*public*/ void sendAllConsistData();
 /*public*/ void sendDataForConsist(Consist* con);
 /*public*/ void setIsConsistAllowed(bool b);
 /*public*/ void programmingOpReply(int value, int status);
 /*public*/ DccLocoAddress* stringToDcc(QString s);
 /*public*/ bool checkForBroadcastAddress(DccLocoAddress* addr);

signals:

public slots:
 void handleMessage(QString message);

private:
 /*private*/ AbstractConsistManager* manager;
 /*private*/ ConsistFile* file;
 /*private*/ bool isConsistAllowed;
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(ConsistController.class.getName());
 /*private*/ void reorderConsist(QString message);
 /*private*/ void removeConsist(QString message);
 /*private*/ void addLoco(QString message);
 /*private*/ void removeLoco(QString message);
 /*private*/ void setConsistCVs(QString message);
 bool verifyCreation();
 void _register();
 /*private*/ void writeFile();
friend class DeviceServer;
};

#endif // CONSISTCONTROLLER_H
