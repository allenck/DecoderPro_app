#ifndef DCCCONSISTMANAGER_H
#define DCCCONSISTMANAGER_H
#include "abstractconsistmanager.h"
#include <QHash>
#include "dccconsist.h"

class DccConsistManager : public AbstractConsistManager
{
    Q_OBJECT
public:
    explicit DccConsistManager(AddressedProgrammerManager* apm, QObject *parent = 0);
//    /*public*/ Consist* getConsist(DccLocoAddress* address);
//    /*public*/ void delConsist(DccLocoAddress* address);
    /*public*/ bool isCommandStationConsistPossible();
    /*public*/ bool csConsistNeedsSeparateAddress();
//    /*public*/ QList<DccLocoAddress*>* getConsistList();
//    /*public*/ QString decodeErrorCode(int ErrorCode);
//    /*public*/ void requestUpdateFromLayout();
//    /*public*/ void addConsistListListener(ConsistListListener* l);
//    /*public*/ void removeConsistListListener(ConsistListListener* l);
//    /*public*/ void notifyConsistListChanged();
    /*public*/ DccConsist *addConsist(DccLocoAddress* address) override;


signals:

public slots:
private:
// /*private*/ QHash<DccLocoAddress*, DccConsist*>* consistTable;// = NULL;

// /*private*/ QList<DccLocoAddress*>* consistList;// = NULL;

// /*private*/ QList<ConsistListListener*>* changeListeners;// = NULL;

 /*private*/ AddressedProgrammerManager* opsProgManager = nullptr;

};

#endif // DCCCONSISTMANAGER_H
