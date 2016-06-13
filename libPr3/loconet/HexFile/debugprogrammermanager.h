#ifndef DEBUGPROGRAMMERMANAGER_H
#define DEBUGPROGRAMMERMANAGER_H
#include "defaultprogrammermanager.h"
#include "libPr3_global.h"

class ProgDebugger;
class LIBPR3SHARED_EXPORT DebugProgrammerManager : public DefaultProgrammerManager
{
    Q_OBJECT
public:
    explicit DebugProgrammerManager(QObject *parent = 0);
    /*public*/ DebugProgrammerManager(SystemConnectionMemo* memo, QObject *parent = 0);
    /*public*/ AddressedProgrammer* getAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ AddressedProgrammer* reserveAddressedProgrammer(bool pLongAddress, int pAddress);
    /*public*/ bool isAddressedModePossible();

signals:

public slots:
private:
    /**
     * Save the mapping from addresses to Programmer objects.
     * Short addresses are saved as negative numbers.
     */
    QHash<int,ProgDebugger*> opsProgrammers;// =  QHash<int,ProgDebugger*>();
    void common();
    Logger* log;
};

#endif // DEBUGPROGRAMMERMANAGER_H
