#ifndef ABSTRACTPROXYMANAGER_H
#define ABSTRACTPROXYMANAGER_H
#include "manager.h"
#include "abstractmanager.h"
#include "logger.h"
#include "libPr3_global.h"
#include <QSet>
#include "idtagmanager.h"
#include "proxymanager.h"


class LIBPR3SHARED_EXPORT AbstractProxyManager :   public VetoableChangeSupport, public ProxyManager, public PropertyChangeListener, public Manager::ManagerDataListener, public VetoableChangeListener
{
    Q_OBJECT
    Q_INTERFACES( ProxyManager PropertyChangeListener Manager::ManagerDataListener VetoableChangeListener)
 public:
    AbstractProxyManager(QObject* parent = nullptr );
    /*public*/  QList<AbstractManager/*<E>*/*> getManagerList() const override;
    /*public*/  QList<AbstractManager/*<E>*/*> getDisplayOrderManagerList() override;
    /*public*/  AbstractManager *getInternalManager() const; //not override!
    /*public*/  AbstractManager *getDefaultManager() const override;
    /*public*/  void addManager(/*@Nonnull*/ AbstractManager *m) override;
    /*public*/  /*E*/NamedBean* getNamedBean(/*@Nonnull*/ QString name) override;
    /*public*/  /*E*/NamedBean* getBySystemName(/*@Nonnull*/ QString systemName) const override;
    /*public*/  /*E*/NamedBean* getByUserName(/*@Nonnull*/ QString userName) const override;
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
    /*public*/  virtual /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l) override;
    /*public*/  virtual /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l)override;
    /*public*/  virtual void addPropertyChangeListener(QString propertyName, PropertyChangeListener* listener) override;
    /*public*/  virtual void removePropertyChangeListener(QString propertyName, PropertyChangeListener* listener)override;
    /*public*/  /*synchronized*/ void addVetoableChangeListener(VetoableChangeListener* l)override;
    /*public*/  /*synchronized*/ void removeVetoableChangeListener(VetoableChangeListener* l)override;
    /*public*/  void addVetoableChangeListener(QString propertyName, VetoableChangeListener* listener) override;
    /*public*/  void removeVetoableChangeListener(QString propertyName, VetoableChangeListener* listener)override;
    /*public*/  SystemConnectionMemo* getMemo()override;
    /*public*/  QString getSystemPrefix() const override;
    /*public*/  QChar typeLetter() const /*final*/  override;
    /*public*/  QString makeSystemName(/*@Nonnull*/ QString s) override;
    /*public*/  int getObjectCount()override ;
    QT_DEPRECATED/*public*/  QStringList getSystemNameList()  override;
    /*public*/  QList<NamedBean*>* getNamedBeanList() override;
    /*public*/  QSet<NamedBean*> getNamedBeanSet()  override;
    /*public*/  void setPropertyChangesSilenced(QString propertyName, bool silenced) override;
    /*public*/  void addDataListener(Manager::ManagerDataListener/*<E>*/* e)override;
    /*public*/  void removeDataListener(Manager::ManagerDataListener/*<E>*/* e)override;
    QT_DEPRECATED /*public*/  void contentsChanged(Manager::ManagerDataEvent* e)override;
    /*public*/  void intervalAdded(AbstractProxyManager::ManagerDataEvent/*<E>*/* e)override;
    QT_DEPRECATED /*public*/  void intervalRemoved(AbstractProxyManager::ManagerDataEvent/*<E>*/* e)override;
    QT_DEPRECATED /*public*/  void setDataListenerMute(bool m) override;

    QObject* mself() override {return (QObject*)this;}

 public slots:
    /*public*/  void propertyChange(PropertyChangeEvent* event)override;

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
    /*private*/ /*final*/ QSet<AbstractManager/*<E>*/*> mgrs = QSet<AbstractManager*>();//new TreeSet<>((Manager/*<E>*/* e1, Manager/*<E>*/* e2) -> e1.getSystemPrefix().compareTo(e2.getSystemPrefix()));
    /*private*/ mutable AbstractManager/*<E>*/* internalManager = nullptr;
    QString createSystemName(QString curAddress, QString prefix, QString beanType) /*throws JmriException */;
    virtual /*private*/ Manager/*<E>*/* createSystemManager(/*@Nonnull*/ QString systemPrefix);
    /*private*/ mutable QSet<NamedBean*>* namedBeanSet = nullptr;
    /*final*/ QList<Manager::ManagerDataListener/*<E>*/*> listeners = QList<Manager::ManagerDataListener/*<E>*/*>();

protected:
    /*protected*/ /*final*/ QMap<QString, bool> silencedProperties = QMap<QString, bool>();
    /*protected*/ /*final*/ QSet<QString> silenceableProperties = QSet<QString>();
    /*protected*/ AbstractManager/*<E>*/* initInternal() const; // no override!
    /*protected*/ mutable AbstractManager/*<E>*/* defaultManager = nullptr;
    /*abstract*/virtual /*protected*/ AbstractManager/*<E>*/* makeInternalManager()  const {return nullptr;}
    /*protected*/ AbstractManager *getManager(/*@Nonnull*/ QString systemName) const ; // not override!
    /*protected*/ AbstractManager/*<E>*/* getManagerOrDefault(/*@Nonnull*/ QString systemName);
    virtual /*protected*/ AbstractManager/*<E>*/* createSystemManager(/*@Nonnull*/ SystemConnectionMemo* memo) ;
    /*protected*/ void recomputeNamedBeanSet() const;

};
//Q_DECLARE_INTERFACE(AbstractProxyManager, "AbstractProxyManager")
#endif // ABSTRACTPROXYMANAGER_H
