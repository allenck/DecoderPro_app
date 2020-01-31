#ifndef NMRACONSISTMANAGER_H
#define NMRACONSISTMANAGER_H
#include "dccconsistmanager.h"

class CommandStation;
class Consist;
class DccLocoAddress;
class NmraConsistManager : public AbstractConsistManager
{
    Q_OBJECT
public:
    explicit NmraConsistManager(CommandStation *cs, QObject *parent = 0);
    /*public*/ DccConsist *addConsist(DccLocoAddress* address);

signals:

public slots:

private:
 CommandStation* commandStation = nullptr;

};

#endif // NMRACONSISTMANAGER_H
