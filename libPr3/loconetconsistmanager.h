#ifndef LOCONETCONSISTMANAGER_H
#define LOCONETCONSISTMANAGER_H
#include "abstractconsistmanager.h"
#include "loconetsystemconnectionmemo.h"
//#include "loconetconsist.h"

class LIBPR3SHARED_EXPORT LocoNetConsistManager : public virtual AbstractConsistManager
{
    Q_OBJECT
public:
    explicit LocoNetConsistManager(LocoNetSystemConnectionMemo* lm, QObject *parent = 0);
    /**
     *    This implementation does support command station assisted
     *     consists, so return true.
     **/
    /*public*/ bool isCommandStationConsistPossible() override;
    /**
     *    Does a CS consist require a seperate consist address?
     **/
    /*public*/ bool csConsistNeedsSeparateAddress() override;
    /**
     *    Add a new LocoNetConsist with the given address to
     *    consistTable/consistList
     */
    /*public*/ DccConsist *addConsist(DccLocoAddress* address) override;
    /* request an update from the layout, loading
     * Consists from the command station.
     *
     * On a LocoNet command station, the consists are stored in the
     * slots in an array based tree.  Each node in a consist contains
     * a pointer to the "top" slot in the consist.  A top slot is
     * allowed to be a member of another consist.  When this occurs,
     * it is labeled as a "mid" locomotive.
     *
     * This function updates the list of consists by scanning the
     * slots and adding new "top" slot addresses and removing address
     * that are no longer "top" locomotives.
     */
    /*public*/ void requestUpdateFromLayout() override;

signals:
    
public slots:
private:
    Logger log;
    /*private*/ LocoNetSystemConnectionMemo* memo;

};

#endif // LOCONETCONSISTMANAGER_H
