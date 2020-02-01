#ifndef JSONCONSISTMANAGER_H
#define JSONCONSISTMANAGER_H
#include "bean.h"
#include "consistmanager.h"

class Logger;
class JsonConsistManager : public Bean, public ConsistManager
{
 Q_OBJECT
 Q_INTERFACES(ConsistManager)
public:
 JsonConsistManager(QObject* parent = 0);
 /*public*/ DccConsist* getConsist(DccLocoAddress* address);
 /*public*/ void delConsist(DccLocoAddress* address);
 /*public*/ bool isCommandStationConsistPossible();
 /*public*/ bool csConsistNeedsSeparateAddress();
 /*public*/ DccLocoAddressList* getConsistList();
 /*public*/ QString decodeErrorCode(int errorCode);
 /*public*/ void requestUpdateFromLayout();
 /*public*/ void addConsistListListener(ConsistListListener* listener);
 /*public*/ void removeConsistListListener(ConsistListListener* listener);
 /*public*/ bool isConsistManager();
 /*public*/ QObject* self() {return (QObject*)this;}

public slots:
 void propertyChange(PropertyChangeEvent* evt);
 /*public*/ void notifyConsistListChanged();

signals:
 void consistListChanged();

private:
 /*private*/ ConsistManager* manager;// = NULL;
 /*private*/ QSet<ConsistListListener*>* listeners;// = new HashSet<>();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("JsonConsistManager");

};
#endif // JSONCONSISTMANAGER_H
