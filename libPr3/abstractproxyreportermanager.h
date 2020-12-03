#ifndef ABSTRACTPROXYREPORTERMANAGER_H
#define ABSTRACTPROXYREPORTERMANAGER_H
#include "manager.h"
#include "abstractmanager.h"
#include "logger.h"
#include "libPr3_global.h"
#include <QSet>
#include "idtagmanager.h"
#include "reportermanager.h"
#include "proxymanager.h"

// NOTE: This class is a replacement for AbstractProxyManager that
// implements SensorManager instead of AbstractManager

class LIBPR3SHARED_EXPORT AbstractProxyReporterManager :  public ReporterManager, public ProxyManager
{
    Q_OBJECT
    Q_INTERFACES(ProxyManager)
public:
    explicit AbstractProxyReporterManager(QObject *parent = 0);
    /**
     * Returns a list of all managers, including the
     * internal manager.  This is not a live list.
     */
    /*public*/ QList<Manager*> getManagerList() const override;
    /*public*/ QList<Manager*> getDisplayOrderManagerList() const override;
    /*public*/ Manager* getInternalManager() const ;
    /*public*/ Manager* getDefaultManager()const override;
    /*public*/ void addManager(Manager* m) override;
    /**
     * Locate via user name, then system name if needed.
     * Subclasses use this to provide e.g. getSensor, getTurnout, etc
     * via casts.
     *
     * @param name
     * @return Null if nothing by that name exists
     */
    /*public*/ NamedBean* getNamedBean(QString name) const override;
    /*public*/ /*@Nonnull*/ QString normalizeSystemName(/*@Nonnull*/ QString inputName)const  override/*throw (NamedBean::BadSystemNameException)*/;

    /*public*/ NamedBean* getBeanBySystemName(QString systemName) const override;
    /*public*/ NamedBean* getBeanByUserName(QString userName) const override;

    /**
     * Return an instance with the specified system and user names.
     * Note that two calls with the same arguments will get the same instance;
     * there is only one Sensor object representing a given physical turnout
     * and therefore only one with a specific system or user name.
     *<P>
     * This will always return a valid object reference for a valid request;
     * a new object will be
     * created if necessary. In that case:
     *<UL>
     *<LI>If a null reference is given for user name, no user name will be associated
     *    with the NamedBean object created; a valid system name must be provided
     *<LI>If a null reference is given for the system name, a system name
     *    will _somehow_ be inferred from the user name.  How this is done
     *    is system specific.  Note: a future extension of this interface
     *    will add an exception to signal that this was not possible.
     *<LI>If both names are provided, the system name defines the
     *    hardware access of the desired turnout, and the user address
     *    is associated with it.
     *</UL>
     * Note that it is possible to make an inconsistent request if both
     * addresses are provided, but the given values are associated with
     * different objects.  This is a problem, and we don't have a
     * good solution except to issue warnings.
     * This will mostly happen if you're creating NamedBean when you should
     * be looking them up.
     * @return requested NamedBean object (never null)
     */
    /*public*/ NamedBean* newNamedBean(QString systemName, QString userName);

    /*public*/ void dispose() override;
    /**
     * Remember a NamedBean Object created outside the manager.
     * <P>
     * Forwards the register request to the matching system
     */
    /*public*/ void Register(NamedBean* s) const override;
    /**
     * Forget a NamedBean Object created outside the manager.
     * <P>
     * Forwards the deregister request to the matching system
     */
    /*public*/ void deregister(NamedBean* s) const override;
    /*public synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l) override;
    /**
     * @return The system-specific prefix letter for the primary implementation
     */
    /*public*/ QString getSystemPrefix() const override;
    /**
     * @return The type letter for turnouts
     */
    /*public*/ char typeLetter() const override;
    /**
     * @return A system name from a user input, typically a number,
     * from the primary system.
     */
    /*public*/ QString makeSystemName(QString s) const override;
    /*public*/ int getObjectCount() override;
    /*public*/ QStringList getSystemNameArray() override;
    /**
     * Get a list of all system names.
     */
    /*public*/ virtual QStringList getSystemNameList() override;
//    /*public*/ virtual QStringList getUserNameList();
    QT_DEPRECATED/*public*/ QList<NamedBean*>* getNamedBeanList()  override;
    QT_DEPRECATED /*public*/ QStringList getSystemNameAddedOrderList() override;
    /*public*/ /*SortedSet<E>*/QSet<NamedBean*> getNamedBeanSet() override;
    /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners() override;
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName) override;
    /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    /*public*/ /*synchronized*/ void addVetoableChangeListener(VetoableChangeListener* l) override;
    /*public*/ /*synchronized*/ void removeVetoableChangeListener(VetoableChangeListener* l) override;
    /*public*/ void addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) override;
    /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners() override;
    /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners(QString propertyName) override;
    /*public*/ void removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) override;

signals:
    //virtual void propertyChange(PropertyChangeEvent *e);
public slots:
    virtual void propertyChange(PropertyChangeEvent *e) override;

private:
    /*private*/ /*final*/ static Logger* log;// = LoggerFactory::getLogger("AbstractProxyManager");
    /*private*/ Manager* initInternal() const;
    /*private*/ mutable Manager* internalManager; //= null;
    /*private*/ Manager* defaultManager;
    /*private*/ QStringList addedOrderList;// = QStringList();
    /*private*/ QSet<NamedBean*>* namedBeanSet = nullptr;
    /*private java.util.ArrayList*/QList<Manager*> mgrs;// = new /*java.util.ArrayList*/QList<AbstractManager>();
    QVector<PropertyChangeListener*> propertyListenerList;// = new ArrayList<>();
    QMap<QString, QVector<PropertyChangeListener*>*> namedPropertyListenerMap;// = new HashMap<>();
    QVector<VetoableChangeListener*> propertyVetoListenerList;// = new ArrayList<>();
    QMap<QString, QVector<VetoableChangeListener*>*> namedPropertyVetoListenerMap;// = new HashMap<>();

protected:
    /**
     * Number of managers available through
     * getManager(i) and getManagerList(),
     * including the Internal manager
     */
    /*protected*/ virtual int nMgrs() const;
    /*protected*/ virtual Manager* getMgr(int index) const;
    virtual /*abstract protected*/ Manager* makeInternalManager() const /*=0*/;
    /**
     * Locate via user name, then system name if needed.
     * If that fails, create a new NamedBean: If the name
     * is a valid system name, it will be used for the new
     * NamedBean.  Otherwise, the makeSystemName method
     * will attempt to turn it into a valid system name.
     * Subclasses use this to provide e.g. getSensor, getTurnout, etc
     * via casts.
     *
     * @param name
     * @return Never null under normal circumstances
     */
    /*protected*/ virtual NamedBean* provideNamedBean(QString name);
    /**
     * Defer creation of the proper type to the subclass
     * @param index Which manager to invoke
     */
    virtual/*abstract protected*/ NamedBean* makeBean(int, QString /*systemName*/, QString /*userName*/) const /*=0*/;

    /*public*/ Reporter* getBySystemName(/*@Nonnull */ QString systemName) const override;
    /*public*/ Reporter *getByUserName(/*@Nonnull*/ QString userName) const override;

    /**
     * Find the index of a matching manager.
     * Returns -1 if there is no match, which is not considered an
     * error
     */
    /*protected*/ virtual int matchTentative(QString /*systemname*/) const;
    /**
     * Find the index of a matching manager.
     * Throws IllegalArgumentException if there is no match,
     * here considered to be an error that must be reported.
     */
    /*protected*/ virtual int match(QString systemname)const ;
    /*protected*/ void updateOrderList();
    /*protected*/ void recomputeNamedBeanSet();

 friend class ProxyReporterManager;
 friend class ProxySensorManager;
 friend class ProxyTurnoutManager;
 friend class SensorTableWidget;
 friend class MemoryWidget;
 //friend class ReporterWidget; now uses getManagerList!
 friend class LayoutTurnout;
 friend class LayoutBlock;
 friend class SensorWidget;
 friend class LightWidget;
 friend class LightTableWidget;
 friend class AddPanelIconDialog;
 friend class SaveXml;
 friend class MultiSensorIconWidget;
 friend class AddEditLightDialog;
 friend class ReporterPickModel;
 friend class RegistersWidget;
 friend class PythonQtWrapper_AbstractProxyManager;
};

#endif // ABSTRACTPROXYREPORTERMANAGER_H
