#ifndef PROXYREPORTERMANAGER_H
#define PROXYREPORTERMANAGER_H
#include "abstractproxyreportermanager.h"
#include "reportermanager.h"
#include "reporter.h"

class LIBPR3SHARED_EXPORT ProxyReporterManager : public  AbstractProxyReporterManager/*, public ReporterManager*/
{
    friend class AbstractProxyManager;
    Q_OBJECT
public:
    explicit ProxyReporterManager(QObject *parent = 0);
    /*public*/ int getXMLOrder()const  override;
    /**
     * Locate via user name, then system name if needed.
     *
     * @param name
     * @return Null if nothing by that name exists
     */
    /*public*/ Reporter* getReporter(QString name) const override;
    /*public*/ Reporter* provideReporter(QString sName) override;
    /*public*/ Reporter* provide(/*@Nonnull*/ QString name) throw (IllegalArgumentException) override;
    /**
     * Locate an instance based on a system name.  Returns null if no
     * instance already exists.
     * @return requested Reporter object or null if none exists
     */
    /*public*/ Reporter* getBySystemName(QString sName)const override;
    /**
     * Locate an instance based on a user name.  Returns null if no
     * instance already exists.
     * @return requested Reporter object or null if none exists
     */
    /*public*/ Reporter* getByUserName(QString userName)const override;
    /*public*/ Reporter* getByDisplayName(QString key)const override;
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
    /*public*/ Reporter* newReporter(QString systemName, QString userName)const override;
    /*public*/ bool allowMultipleAdditions(QString systemName)const override;
    /*public*/ QString getNextValidAddress(QString curAddress, QString prefix)const override;
    /*public*/ NamedBean* newNamedBean(QString systemName, QString userName) const;
    /*public*/ QString getEntryToolTip() override;
    /*public*/ QString getBeanTypeHandled(bool plural)const override;
    /*public*/ QString getNamedBeanClass()const override {
        return "Reporter";
    }
    /*public*/ QString toString() {return "ProxyReporterManager";}

signals:
    
public slots:
private:
 Logger log;
protected:
 virtual /*protected*/ Manager* makeInternalManager() const override;
 virtual /*protected*/ NamedBean* makeBean(int i, QString systemName, QString userName) const override;

};

#endif // PROXYREPORTERMANAGER_H
