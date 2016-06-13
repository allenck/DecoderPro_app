#ifndef ABSTRACTCONSISTMANAGER_H
#define ABSTRACTCONSISTMANAGER_H
#include "consistmanager.h"
#include <QHash>
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT AbstractConsistManager : public virtual ConsistManager
{
    Q_OBJECT
public:
    explicit AbstractConsistManager(QObject *parent = 0);
    /**
    *    Find a Consist with this consist address, and return it.
    **/
    /*public*/ virtual Consist* getConsist(DccLocoAddress* address);
    /**
    *     Add a new Consist with the given address to the consistTable/consistList
    **/
    /*abstract public*/ virtual Consist* addConsist(DccLocoAddress* /*address*/) {return NULL;}
    // remove the old Consist
    /*public*/ virtual void delConsist(DccLocoAddress* address);
    /**
     *    Does this implementation support a command station consist?
     **/
    /*abstract public*/ virtual bool isCommandStationConsistPossible() = 0;
    /**
     *    Does a CS consist require a seperate consist address?
    *    (or is the lead loco to be used for the consist address)
     **/
    /*abstract public*/ virtual bool csConsistNeedsSeperateAddress() = 0;
    /**
    *  Return the list of consists we know about.
    **/
    /*public*/ virtual QList<DccLocoAddress*>* getConsistList();
    /*public*/ virtual QString decodeErrorCode(int ErrorCode);
    /* request an update from the layout, loading
    * Consists from the command station.
    */
    /*public*/ virtual void requestUpdateFromLayout();
    /*
     * register a ConsistListListener object with this Consist
     * Manager
     * @param listener a Consist List Listener object.
     */
    /*public*/ virtual void addConsistListListener(ConsistListListener* l);
    /*
     * remove a ConsistListListener object with this Consist
     * Manager
     * @param listener a Consist List Listener object.
     */
    /*public*/ virtual void removeConsistListListener(ConsistListListener* l);
    /*
     * Notify the registered Consist List Listener objects that the
     * Consist List has changed.
     */
    /*public*/ virtual void notifyConsistListChanged();

signals:
    
public slots:
private:
    /*private*/ QList<ConsistListListener*>* ChangeListeners ;

protected:
    /*protected*/ QHash<DccLocoAddress*,Consist*>* consistTable;

    /*protected*/ QList<DccLocoAddress*>* consistList ;

};

#endif // ABSTRACTCONSISTMANAGER_H
