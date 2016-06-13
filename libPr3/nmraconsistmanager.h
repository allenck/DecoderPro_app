#ifndef NMRACONSISTMANAGER_H
#define NMRACONSISTMANAGER_H
#include "dccconsistmanager.h"

class Consist;
class DccLocoAddress;
class NmraConsistManager : public DccConsistManager
{
    Q_OBJECT
public:
    explicit NmraConsistManager(QObject *parent = 0);
    /*public*/ Consist* addConsist(DccLocoAddress* address);

signals:

public slots:

};

#endif // NMRACONSISTMANAGER_H
