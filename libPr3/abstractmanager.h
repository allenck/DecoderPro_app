#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H
#include "logger.h"
//#include "instancemanager.h"
#include "manager.h"
//#include "propertychangesupport.h"
#include "libPr3_global.h"
#include "propertyvetoexception.h"
#include "namedbeancomparator.h"
#include <QAtomicInteger>
#include "decimalformat.h"
/**
 * Abstract partial implementation for all Manager-type classes.
 * <P>
 * Note that this does not enforce any particular system naming convention
 * at the present time.  They're just names...
 *
 * @author      Bob Jacobsen Copyright (C) 2003
 * @version	$Revision: 19272 $
 */
//class Manager;
class VetoableChangeSupport;
class PropertyChangeSupport;
class PropertyChangeListener;
class PropertyChangeEvent;
class LIBPR3SHARED_EXPORT AbstractManager : public  Manager
{
    Q_OBJECT
public:
    AbstractManager(QObject *parent = 0);
    AbstractManager(SystemConnectionMemo* memo, QObject *parent = 0);
//    virtual int getXMLOrder();
    // abstract methods to be extended by subclasses
    // to free resources when no longer used
     void dispose() override;
    /*public*/ int getObjectCount() override;
     QStringList getSystemNameArray() override;
     QStringList getSystemNameList() override;
    QStringList getUserNameList();
    QHash<QString, NamedBean*>* getSystemNameHash();
    /**
     * Locate an instance based on a system name.  Returns NULL if no
     * instance already exists.
     * @param systemName System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/  NamedBean* getBeanBySystemName(QString systemName) const override;

    /**
     * Locate an instance based on a user name.  Returns NULL if no
     * instance already exists.
     * @param userName System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
//    /*public*/  NamedBean* getBeanByUserName(QString userName)const override;
//    /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString userName) const override;

    /**
     * Locate an instance based on a name.  Returns NULL if no
     * instance already exists.
     * @param name System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/  NamedBean* getNamedBean(QString name)const override;
    /**
     * Remember a NamedBean Object created outside the manager.
     * <P>
     * The non-system-specific SignalHeadManagers
     * use this method extensively.
     */
    /*public*/  void Register(NamedBean* s) const override;
    /**
     * Forget a NamedBean Object created outside the manager.
     * <P>
     * The non-system-specific RouteManager
     * uses this method.
     */
    /*public*/  void deregister(NamedBean* s) const override;
    /**
     * The PropertyChangeListener interface in this class is
     * intended to keep track of user name changes to individual NamedBeans.
     * It is not completely implemented yet. In particular, listeners
     * are not added to newly registered objects.
     */
    //virtual /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public synchronized */ void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public synchronized*/  void removePropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName) override;
    /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;

    /**
     * Get all {@link java.beans.PropertyChangeListener}s currently attached to
     * this object.
     *
     * @return An array of PropertyChangeListeners.
     */
    //@Nonnull
    /*public*/  QVector<PropertyChangeListener *> getPropertyChangeListeners() override;

    /**
     * By default, register this manager to store as configuration
     * information.  Override to change that.
     **/
    QT_DEPRECATED /*public*/ QList<NamedBean*> *getNamedBeanList() override;
    /*public*/ /*SortedSet<E>*/QSet<NamedBean*> getNamedBeanSet() override;

    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    /*public*/ QString normalizeSystemName(/*@Nonnull*/ QString inputName)const override; //throws NamedBean.BadSystemNameException
    VetoableChangeSupport* vcs;// = new VetoableChangeSupport(this);
    /*public*/ /*synchronized*/ void addVetoableChangeListener(VetoableChangeListener* l) override;
    /*public*/ /*synchronized*/ void addVetoableChangeListener(QString propertyName, VetoableChangeListener* l) override;
    /*public*/ /*synchronized*/ void removeVetoableChangeListener(VetoableChangeListener* l) override;
    /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners() override;
    /*public*/ QVector<VetoableChangeListener*> getVetoableChangeListeners(QString propertyName) override;
    /*public*/ void removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener);
    /*public*/ /*final*/ QString getSystemPrefix() const override;
    /*public*/ Manager::NameValidity validSystemNameFormat(QString systemName)const override;
    /*public*/ void setDataListenerMute(bool m);
    /*public*/ void addDataListener(/*ManagerDataListener<E>*/QObject* e) override;
    /*public*/ void removeDataListener(/*ManagerDataListener<E>*/QObject* e) override;
//    /*public*/ QString makeSystemName(/*@Nonnull*/ QString s);
//    /*public*/ QString makeSystemName(/*@Nonnull*/ QString s, bool logErrors);
    /*public*/ QString makeSystemName(/*@Nonnull*/ QString s, bool logErrors = true, QLocale locale = QLocale()) const override;
    /*public*/ virtual SystemConnectionMemo* getMemo() const;
//    /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString systemName) const override;
    /*public*/ void updateAutoNumber(QString systemName) const;
    /*public*/ QString getAutoSystemName()const;


signals:
//    void beanDeleted(NamedBean* s);
//    void beanCreated(NamedBean* s);
    //void propertyChange(PropertyChangeEvent* e);
    void vetoablePropertyChange(PropertyChangeEvent *evt);
    void notifyContentsChanged(ManagerDataEvent* e);
    void notifyIntervalAdded(ManagerDataEvent* e);
    void notifyIntervalRemoved(ManagerDataEvent* e);

public slots:
    virtual void propertyChange(PropertyChangeEvent* e);
    /*public*/ virtual void vetoableChange(PropertyChangeEvent* evt); //throw PropertyVetoException
protected:
    /*protected*/void registerSelf();
    /*protected*/ void registerUserName(NamedBean* s)const;
    /*protected*/ void fireDataListenersAdded(int start, int end, NamedBean* changedBean);
    /*protected*/ void fireDataListenersRemoved(int start, int end, NamedBean* changedBean);

private:
    mutable QSet<NamedBean*> _beans;
    /*private*/ int getPosition(NamedBean* s) const ;
    /*private*/ bool muted = false;
    Logger* log;
    /*final*/ QList</*ManagerDataListener<E>>*/QObject*> listeners;// = new ArrayList<>();
    SystemConnectionMemo* memo = nullptr;
    //QAtomicInteger<int> lastAutoNamedBeanRef;
    mutable int lastAutoNamedBeanRef = 0;
    DecimalFormat paddedNumber = DecimalFormat("0000");

friend class SectionTableDataModel;
friend class ReporterPickModel;
friend class TurnoutTableDataModel;
friend class AudioTableDataModel;
friend class TurnoutTableWidget;
friend class OBlockTableModel;
friend class SensorTableModel;
friend class RpsReporterManager;
friend class RpsSensorManager;
friend class InternalLightManager;
friend class InternalReporterManager;
friend class InternalMeterManager;
friend class DefaultRouteManager;
friend class SignalGroupManager;
friend class DefaultSignalGroupManager;
protected:
/**
 * Locate an instance based on a system name.  Returns NULL if no
 * instance already exists.  This is intended to be used by
 * concrete classes to implement their getBySystemName method.
 * We can't call it that here because Java doesn't have polymorphic
 * return types.
 * @return requested Turnout object or NULL if none exists
 */
QObject* getInstanceBySystemName(QString systemName);
/**
 * Locate an instance based on a user name.  Returns NULL if no
 * instance already exists. This is intended to be used by
 * concrete classes to implement their getBySystemName method.
 * We cant call it that here because Java doesn't have polymorphic
 * return types.
 * @return requested Turnout object or NULL if none exists
 */
QT_DEPRECATED QObject* getInstanceByUserName(QString userName);


void firePropertyChange(QString p, QVariant old, QVariant n) const;
void fireIndexedPropertyChange(QString p, int pos, QVariant old, QVariant n) const;

/*protected*/ void fireVetoableChange(QString p, QVariant old, QVariant n) /*throws PropertyVetoException*/;
/*protected*/ void handleUserNameUniqueness(NamedBean* s) const;
/*protected Hashtable*/mutable QHash<QString, NamedBean*>* _tsys; // = new Hashtable<String, NamedBean>();   // stores known Turnout instances by system name
/*protected Hashtable*/mutable QHash<QString, NamedBean*>* _tuser; // = new Hashtable<String, NamedBean>();   // stores known Turnout instances by user name

protected slots:

 //friend class AbstractProxyManager;
 friend class PropertyChangeSupport;
 friend class BeanTableDataModel;
 friend class SGBeanTableDataModel;
 friend class SensorTableDataModel;
 friend class InternalSensorManager;
};

#endif // ABSTRACTMANAGER_H
