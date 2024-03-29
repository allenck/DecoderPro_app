#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H
#include "logger.h"
//#include "instancemanager.h"
#include "manager.h"
//#include "swingpropertychangesupport.h"
#include "libPr3_global.h"
#include <QAtomicInteger>
#include "decimalformat.h"
#include "vetoablechangelistener.h"
#include "vetoablechangesupport.h"

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
//class VetoableChangeSupport;
class SwingPropertyChangeSupport;
class PropertyChangeListener;
class PropertyChangeEvent;
class LIBPR3SHARED_EXPORT AbstractManager :  public VetoableChangeSupport, public virtual Manager, public VetoableChangeListener, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES( Manager VetoableChangeListener PropertyChangeListener)
public:
    AbstractManager(QObject *parent = 0);
    AbstractManager(SystemConnectionMemo* memo, QObject *parent = 0);
//    virtual int getXMLOrder();
    // abstract methods to be extended by subclasses
    // to free resources when no longer used
     void dispose() override;
    /*public*/ int getObjectCount() override;
     QStringList getSystemNameArray() override;
     QT_DEPRECATED QStringList getSystemNameList() override;
    QStringList getUserNameList();
    QMap<QString, NamedBean *> *getSystemNameHash();
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
    /*public*/  NamedBean* getNamedBean(QString name) override;
    /**
     * Remember a NamedBean Object created outside the manager.
     * <P>
     * The non-system-specific SignalHeadManagers
     * use this method extensively.
     */
    /*public*/  void Register(NamedBean* s)  override;
    /**
     * Forget a NamedBean Object created outside the manager.
     * <P>
     * The non-system-specific RouteManager
     * uses this method.
     */
    /*public*/  void deregister(NamedBean* s)  override;
    /**
     * The PropertyChangeListener interface in this class is
     * intended to keep track of user name changes to individual NamedBeans.
     * It is not completely implemented yet. In particular, listeners
     * are not added to newly registered objects.
     */
    //virtual /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public synchronized */ void addPropertyChangeListener(PropertyChangeListener* l) override;
//    /*public synchronized*/  void removePropertyChangeListener(PropertyChangeListener* l) override;
//    /*public*/ void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
//    /*public*/ QVector<PropertyChangeListener*> getPropertyChangeListeners(QString propertyName) override;
//    /*public*/ void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;

//    /**
//     * Get all {@link java.beans.PropertyChangeListener}s currently attached to
//     * this object.
//     *
//     * @return An array of PropertyChangeListeners.
//     */
//    //@Nonnull
//    /*public*/  QVector<PropertyChangeListener *> getPropertyChangeListeners() override;

    /**
     * By default, register this manager to store as configuration
     * information.  Override to change that.
     **/
    QT_DEPRECATED /*public*/ QList<NamedBean*> *getNamedBeanList() override;
    /*public*/ /*SortedSet<E>*/QSet<NamedBean*> getNamedBeanSet() override;

    /*public*/ QString normalizeSystemName(/*@Nonnull*/ QString inputName)const override; //throws NamedBean.BadSystemNameException
    /*public*/  QString getSystemPrefix() const /*final*/ override;
    /*public*/ void setPropertyChangesSilenced(/*@Nonnull*/ QString propertyName, bool silenced) override;
    /*public*/ Manager::NameValidity validSystemNameFormat(QString systemName)  override;
    QT_DEPRECATED/*public*/ void setDataListenerMute(bool m) override;
    QT_DEPRECATED/*public*/ void addDataListener(ManagerDataListener/*<E>*/* e) override;
    QT_DEPRECATED/*public*/ void removeDataListener(ManagerDataListener *e) override;
    /*public*/ QString makeSystemName(/*@Nonnull*/ QString s, bool logErrors = true, QLocale locale = QLocale())  override;
    /*public*/ SystemConnectionMemo* getMemo()  override;
    /*public*/ void updateAutoNumber(QString systemName);
    /*public*/ QString getAutoSystemName();

    QObject* mself() override{return (QObject*)this;}

    QString getNamedBeanClass() const override{return "AbstractManager";}
    int getXMLOrder() const override {return 0;}
    /*public*/ QString createSystemName(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix) /*throw (JmriException)*/;
    QT_DEPRECATED/*public*/ /*final*/ QString getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix) /*throw (JmriException)*/;
    QString getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting) /*throw (JmriException)*/;
    /*public*/ NamedBean *getBySystemName(/*@Nonnull*/ QString systemName) const override;
    /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString userName) const override;

 signals:
//    void beanDeleted(NamedBean* s);
//    void beanCreated(NamedBean* s);
    //void propertyChange(PropertyChangeEvent* e);
    void vetoablePropertyChange(PropertyChangeEvent *evt);
//    void notifyContentsChanged(ManagerDataEvent* e);
//    void notifyIntervalAdded(ManagerDataEvent* e);
//    void notifyIntervalRemoved(ManagerDataEvent* e);

public slots:
     void propertyChange(PropertyChangeEvent* e)override;
    /*public*/ void vetoableChange(PropertyChangeEvent* evt) /*throw (PropertyVetoException) */ override;

protected:
    /*protected*/void registerSelf();
    /*protected*/ void registerUserName(NamedBean* s)const;
    QT_DEPRECATED/*protected*/ void fireDataListenersAdded(int start, int end, NamedBean* changedBean);
    QT_DEPRECATED/*protected*/ void fireDataListenersRemoved(int start, int end, NamedBean* changedBean);
    /*protected*/ QString checkNumeric(/*@Nonnull*/ QString curAddress) /*throw (JmriException)*/;

private:
    mutable QSet<NamedBean*> _beans;
    /*private*/ int getPosition(NamedBean* s) const ;
    /*private*/ bool muted = false;
    static Logger* log;
    /*final*/ QList<Manager::ManagerDataListener/*<E>*/*> listeners;// = new ArrayList<>();
    SystemConnectionMemo* memo = nullptr;
    //QAtomicInteger<int> lastAutoNamedBeanRef;
    mutable int lastAutoNamedBeanRef = 0;
    DecimalFormat paddedNumber = DecimalFormat("0000");
    /*final*/ void setRegisterSelf();
    // caches
    /*private*/ QList<QString>* cachedSystemNameList = nullptr;
    /*private*/ QList<NamedBean*>* cachedNamedBeanList = nullptr;

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
friend class DefaultVariableLightManager;
friend class InternalAnalogIOManager;
friend class DefaultAnalogExpressionManager;

protected:
/**
 * Locate an instance based on a system name.  Returns NULL if no
 * instance already exists.  This is intended to be used by
 * concrete classes to implement their getBySystemName method.
 * We can't call it that here because Java doesn't have polymorphic
 * return types.
 * @return requested Turnout object or NULL if none exists
 */
NamedBean *getInstanceBySystemName(QString systemName);
/**
 * Locate an instance based on a user name.  Returns NULL if no
 * instance already exists. This is intended to be used by
 * concrete classes to implement their getBySystemName method.
 * We cant call it that here because Java doesn't have polymorphic
 * return types.
 * @return requested Turnout object or NULL if none exists
 */
QT_DEPRECATED NamedBean* getInstanceByUserName(QString userName);


//void firePropertyChange(QString p, QVariant old, QVariant n) const;
//void fireIndexedPropertyChange(QString p, int pos, QVariant old, QVariant n) const;

/*protected*/ void fireVetoableChange(QString p, QVariant old, QVariant n) /*throw (PropertyVetoException)*/override;
/*protected*/ void handleUserNameUniqueness(NamedBean* s) const;
/*protected Hashtable*/mutable QMap<QString, NamedBean*>* _tsys; // = new Hashtable<String, NamedBean>();   // stores known Turnout instances by system name
/*protected Hashtable*/mutable QMap<QString, NamedBean*>* _tuser; // = new Hashtable<String, NamedBean>();   // stores known Turnout instances by user name
/*protected*/ /*final*/ QMap<QString, bool> silencedProperties = QMap<QString, bool>();
/*protected*/ /*final*/ QSet<QString> silenceableProperties = QSet<QString>();
/*protected*/ QString getIncrement(QString curAddress, int increment) /*throw (JmriException)*/;
/*protected*/ QString getIncrementFromExistingNumber(QString curAddress, int increment) /*throw (JmriException)*/;

protected slots:

 friend class AbstractProxySensorManager;
 friend class SwingPropertyChangeSupport;
 friend class BeanTableDataModel;
 friend class SGBeanTableDataModel;
 friend class SensorTableDataModel;
 friend class InternalSensorManager;
 friend class LightTableDataModel;

};

#endif // ABSTRACTMANAGER_H
