#ifndef ABSTRACTMANAGER_H
#define ABSTRACTMANAGER_H
#include "logger.h"
//#include "instancemanager.h"
#include "manager.h"
//#include "propertychangesupport.h"
#include "javaqt_global.h"
#include "propertyvetoexception.h"

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
class JAVAQTSHARED_EXPORT AbstractManager : public  Manager
{
    Q_OBJECT
public:
    AbstractManager(QObject *parent = 0);
//    virtual int getXMLOrder();
    virtual QString makeSystemName(QString s);
    // abstract methods to be extended by subclasses
    // to free resources when no longer used
    virtual void dispose();
    virtual QStringList getSystemNameArray();
    virtual QStringList getSystemNameList();
    QStringList getUserNameList();
    QHash<QString, NamedBean*>* getSystemNameHash();
    /**
     * Locate an instance based on a system name.  Returns NULL if no
     * instance already exists.
     * @param systemName System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ virtual NamedBean* getBeanBySystemName(QString systemName);

    /**
     * Locate an instance based on a user name.  Returns NULL if no
     * instance already exists.
     * @param userName System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ virtual NamedBean* getBeanByUserName(QString userName);
    /**
     * Locate an instance based on a name.  Returns NULL if no
     * instance already exists.
     * @param name System Name of the required NamedBean
     * @return requested NamedBean object or NULL if none exists
     */
    /*public*/ virtual NamedBean* getNamedBean(QString name);
    /**
     * Remember a NamedBean Object created outside the manager.
     * <P>
     * The non-system-specific SignalHeadManagers
     * use this method extensively.
     */
    /*public*/ virtual void Register(NamedBean* s);
    /**
     * Forget a NamedBean Object created outside the manager.
     * <P>
     * The non-system-specific RouteManager
     * uses this method.
     */
    /*public*/ virtual void deregister(NamedBean* s);
    /**
     * The PropertyChangeListener interface in this class is
     * intended to keep track of user name changes to individual NamedBeans.
     * It is not completely implemented yet. In particular, listeners
     * are not added to newly registered objects.
     */
    //virtual /*public*/ void propertyChange(PropertyChangeEvent* e);
    /*public synchronized */virtual void addPropertyChangeListener(PropertyChangeListener* l);
    /*public synchronized*/ virtual void removePropertyChangeListener(PropertyChangeListener* l);
    /**
     * By default, register this manager to store as configuration
     * information.  Override to change that.
     **/
    QT_DEPRECATED /*public*/ QList<NamedBean*>* getNamedBeanList();
    /*public*/ /*SortedSet<E>*/QSet<NamedBean*> getNamedBeanSet();

    PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
    /*public*/ QString normalizeSystemName(/*@Nonnull*/ QString inputName); //throws NamedBean.BadSystemNameException
    VetoableChangeSupport* vcs;// = new VetoableChangeSupport(this);
    /*public*/ /*synchronized*/ void addVetoableChangeListener(VetoableChangeListener* l);
    /*public*/ /*synchronized*/ void removeVetoableChangeListener(VetoableChangeListener* l);

signals:
    void beanDeleted(NamedBean* s);
    void beanCreated(NamedBean* s);
    //void propertyChange(PropertyChangeEvent* e);
    void vetoablePropertyChange(PropertyChangeEvent *evt);

public slots:
    virtual void propertyChange(PropertyChangeEvent* e);
    /*public*/ virtual void vetoableChange(PropertyChangeEvent* evt); //throw PropertyVetoException
protected:
    /*protected*/void registerSelf();

private:
friend class SectionTableDataModel;
friend class ReporterPickModel;
friend class TurnoutTableDataModel;
friend class AudioTableDataModel;
friend class TurnoutTableWidget;
friend class OBlockTableModel;
friend class SensorTableModel;

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
QObject* getInstanceByUserName(QString userName);
void firePropertyChange(QString p, QVariant old, QVariant n);
/*protected*/ void fireVetoableChange(QString p, QVariant old, QVariant n) /*throws PropertyVetoException*/;

protected slots:

friend class AbstractProxyManager;
friend class PropertyChangeSupport;
friend class BeanTableDataModel;
friend class SGBeanTableDataModel;
friend class SensorTableDataModel;

private:
 Logger* log;
protected:
     /*protected Hashtable*/QHash<QString, NamedBean*>* _tsys; // = new Hashtable<String, NamedBean>();   // stores known Turnout instances by system name
     /*protected Hashtable*/QHash<QString, NamedBean*>* _tuser; // = new Hashtable<String, NamedBean>();   // stores known Turnout instances by user name

};

#endif // ABSTRACTMANAGER_H
