#ifndef ABSTRACTPROXYMANAGER_H
#define ABSTRACTPROXYMANAGER_H
#include "manager.h"
#include "abstractmanager.h"
#include "logger.h"
#include "libPr3_global.h"
#include <QSet>
#include "idtagmanager.h"
#include "proxymanager.h"

class LIBPR3SHARED_EXPORT AbstractProxyManager :  public VetoableChangeSupport, public ProxyManager, PropertyChangeListener, Manager::ManagerDataListener
{
    //Q_OBJECT
    Q_INTERFACES(VetoableChangeSupport ProxyManager PropertyChangeListener Manager::ManagerDataListener PropertyChangeSupport PropertyChangeProvider)
 public:
    /*public*/  QList<Manager/*<E>*/*> getManagerList() override;
    /*public*/  QList<Manager/*<E>*/*> getDisplayOrderManagerList() override;
    /*public*/  Manager/*<E>*/* getInternalManager(); //not override!
    /*public*/  Manager/*<E>*/* getDefaultManager() override;
    /*public*/  void addManager(/*@Nonnull*/ Manager/*<E>*/* m) override;
    /*public*/  /*E*/NamedBean* getNamedBean(/*@Nonnull*/ QString name) override;
    /*public*/  /*E*/NamedBean* getBySystemName(/*@Nonnull*/ QString systemName) override;
    /*public*/  /*E*/NamedBean* getByUserName(/*@Nonnull*/ QString userName)  override;
    /*public*/  QString validateSystemNameFormat(/*@Nonnull*/ QString systemName, /*@Nonnull*/ QLocale locale) override;
    /*public*/  Manager::NameValidity validSystemNameFormat(/*@Nonnull*/ QString systemName) override;
    /*public*/  void dispose()override;
    /*public*/  QString createSystemName(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix) /*throws jmri.JmriException*/ ;
    /*public*/  QString getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, QChar typeLetter)  /*throws jmri.JmriException*/;
    /*public*/  QString getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting, QChar typeLetter) /*throws jmri.JmriException*/;
    /*public*/  void deleteBean(/*@Nonnull*/ /*E*/NamedBean* s, /*@Nonnull*/ QString property) /*throws PropertyVetoException */ override;
    /*public*/  QString getEntryToolTip() override;
    /*public*/  void Register(/*@Nonnull*/ /*E*/NamedBean* s) override;
    /*public*/  void deregister(/*@Nonnull*/ /*E*/NamedBean* s) override;
    /*public*/  QList<NamedBeanPropertyDescriptor/*<?>*/*> getKnownBeanProperties() override;
    /*public*/  /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/  /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);
    /*public*/  void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    /*public*/  void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener);
    /*public*/  /*synchronized*/ void addVetoableChangeListener(VetoableChangeListener* l)override;
    /*public*/  /*synchronized*/ void removeVetoableChangeListener(VetoableChangeListener* l)override;
    /*public*/  void addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) override;
    /*public*/  void removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener)override;
    /*public*/  void propertyChange(PropertyChangeEvent* event)override;
    /*public*/  SystemConnectionMemo* getMemo() override;
    /*public*/  QString getSystemPrefix() override;
    /*public*/  QChar typeLetter()  override;
    /*public*/  QString makeSystemName(/*@Nonnull*/ QString s) override;
    /*public*/  int getObjectCount()override ;
    QT_DEPRECATED/*public*/  QStringList getSystemNameList()  override;
    /*public*/  QList<NamedBean*>* getNamedBeanList() override;
    /*public*/  QSet<NamedBean*> getNamedBeanSet();
    /*public*/  void setPropertyChangesSilenced(QString propertyName, bool silenced) override;
    /*public*/  void addDataListener(Manager::ManagerDataListener/*<E>*/* e);
    /*public*/  void removeDataListener(Manager::ManagerDataListener/*<E>*/* e);
    QT_DEPRECATED /*public*/  void contentsChanged(Manager::ManagerDataEvent* e);
    /*public*/  void intervalAdded(AbstractProxyManager::ManagerDataEvent/*<E>*/* e);
    QT_DEPRECATED /*public*/  void intervalRemoved(AbstractProxyManager::ManagerDataEvent/*<E>*/* e);
    QT_DEPRECATED /*public*/  void setDataListenerMute(bool m) override;


private:
    static Logger* log;
    /*private*/ bool muted = false;
    /**
     * List of names of bound properties requested to be listened to by
     * PropertyChangeListeners.
     */
    /*private*/ /*final*/ QList<QString> boundPropertyNames = QList<QString>();
    /**
     * List of names of bound properties requested to be listened to by
     * VetoableChangeListeners.
     */
    /*private*/ /*final*/ QList<QString> vetoablePropertyNames = QList<QString>();
    /*private*/ /*final*/ QSet<Manager/*<E>*/*> mgrs = QSet<Manager*>();//new TreeSet<>((Manager/*<E>*/* e1, Manager/*<E>*/* e2) -> e1.getSystemPrefix().compareTo(e2.getSystemPrefix()));
    /*private*/ Manager/*<E>*/* internalManager = nullptr;
    QString createSystemName(QString curAddress, QString prefix, QString beanType) /*throws JmriException */;
    virtual /*private*/ Manager/*<E>*/* createSystemManager(/*@Nonnull*/ QString systemPrefix);
    /*private*/ QSet<NamedBean*>* namedBeanSet = nullptr;
    /*final*/ QList<Manager::ManagerDataListener/*<E>*/*> listeners = QList<Manager::ManagerDataListener/*<E>*/*>();

protected:
    /*protected*/ /*final*/ QMap<QString, bool> silencedProperties = QMap<QString, bool>();
    /*protected*/ /*final*/ QSet<QString> silenceableProperties = QSet<QString>();
    /*protected*/ Manager/*<E>*/* initInternal(); // no override!
    /*protected*/ Manager/*<E>*/* defaultManager = nullptr;
    /*abstract*/virtual /*protected*/ Manager/*<E>*/* makeInternalManager()  {return nullptr;}
    /*protected*/ Manager/*<E>*/* getManager(/*@Nonnull*/ QString systemName) ; // not override!
    /*protected*/ Manager/*<E>*/* getManagerOrDefault(/*@Nonnull*/ QString systemName);
    virtual /*protected*/ Manager/*<E>*/* createSystemManager(/*@Nonnull*/ SystemConnectionMemo* memo) ;
    /*protected*/ void recomputeNamedBeanSet();

};
Q_DECLARE_INTERFACE(AbstractProxyManager, "AbstractProxyManager")
#endif // ABSTRACTPROXYMANAGER_H
