#ifndef DCCCONSISTMANAGER_H
#define DCCCONSISTMANAGER_H
#include "abstractconsistmanager.h"
#include <QHash>
#include "dccconsist.h"

class DccConsistManager : public AbstractConsistManager
{
    Q_OBJECT
public:
    explicit DccConsistManager(QObject *parent = 0);
    /*public*/ Consist* getConsist(DccLocoAddress* address);
    /*public*/ void delConsist(DccLocoAddress* address);
    /*public*/ bool isCommandStationConsistPossible();
    /*public*/ bool csConsistNeedsSeperateAddress();
    /*public*/ QList<DccLocoAddress*>* getConsistList();
    /*public*/ QString decodeErrorCode(int ErrorCode);
    /*public*/ void requestUpdateFromLayout();
    /*public*/ void addConsistListListener(ConsistListListener* l);
    /*public*/ void removeConsistListListener(ConsistListListener* l);
    /*public*/ void notifyConsistListChanged();

signals:
    
public slots:
private:
 /*private*/ QHash<DccLocoAddress*, DccConsist*>* ConsistTable;// = NULL;

 /*private*/ QList<DccLocoAddress*>* ConsistList;// = NULL;

 /*private*/ QList<ConsistListListener*>* ChangeListeners;// = NULL;

    
};

#endif // DCCCONSISTMANAGER_H
