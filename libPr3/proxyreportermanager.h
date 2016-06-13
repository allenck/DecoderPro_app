#ifndef PROXYREPORTERMANAGER_H
#define PROXYREPORTERMANAGER_H
#include "abstractproxymanager.h"
#include "reportermanager.h"
#include "reporter.h"

class LIBPR3SHARED_EXPORT ProxyReporterManager : public  AbstractProxyManager/*, public ReporterManager*/
{
    friend class AbstractProxyManager;
    Q_OBJECT
public:
    explicit ProxyReporterManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /**
     * Locate via user name, then system name if needed.
     *
     * @param name
     * @return Null if nothing by that name exists
     */
    /*public*/ Reporter* getReporter(QString name);
    /*public*/ Reporter* provideReporter(QString sName);
    /**
     * Locate an instance based on a system name.  Returns null if no
     * instance already exists.
     * @return requested Reporter object or null if none exists
     */
    /*public*/ Reporter* getBySystemName(QString sName);
    /**
     * Locate an instance based on a user name.  Returns null if no
     * instance already exists.
     * @return requested Reporter object or null if none exists
     */
    /*public*/ Reporter* getByUserName(QString userName);
    /*public*/ Reporter* getByDisplayName(QString key);
    /**
     * Return an instance with the specified system and user names.
     * Note that two calls with the same arguments will get the same instance;
     * there is only one Reporter object representing a given physical Reporter
     * and therefore only one with a specific system or user name.
     *<P>
     * This will always return a valid object reference for a valid request;
     * a new object will be
     * created if necessary. In that case:
     *<UL>
     *<LI>If a NULL reference is given for user name, no user name will be associated
     *    with the Reporter object created; a valid system name must be provided
     *<LI>If a NULL reference is given for the system name, a system name
     *    will _somehow_ be inferred from the user name.  How this is done
     *    is system specific.  Note: a future extension of this interface
     *    will add an exception to signal that this was not possible.
     *<LI>If both names are provided, the system name defines the
     *    hardware access of the desired Reporter, and the user address
     *    is associated with it.
     *</UL>
     * Note that it is possible to make an inconsistent request if both
     * addresses are provided, but the given values are associated with
     * different objects.  This is a problem, and we don't have a
     * good solution except to issue warnings.
     * This will mostly happen if you're creating Reporters when you should
     * be looking them up.
     * @return requested Reporter object (never NULL)
     */
    /*public*/ Reporter* newReporter(QString systemName, QString userName);
    /*public*/ bool allowMultipleAdditions(QString systemName);
    /*public*/ QString getNextValidAddress(QString curAddress, QString prefix);
    /*public*/ NamedBean* newNamedBean(QString systemName, QString userName);
signals:
    
public slots:
private:
 Logger log;
protected:
 virtual /*protected*/ AbstractManager* makeInternalManager();
 virtual /*protected*/ NamedBean* makeBean(int i, QString systemName, QString userName);

};

#endif // PROXYREPORTERMANAGER_H
