#ifndef PROXYMETERMANAGER_H
#define PROXYMETERMANAGER_H
#include "abstractproxymanager.h"
#include "metermanager.h"

#include <QList>

class Manager;
class ProxyMeterManager :  public AbstractProxyManager, public MeterManager
{
  Q_OBJECT
  Q_INTERFACES(MeterManager)
 public:
  ProxyMeterManager(QObject *parent = 0);
  /*public*/ int getXMLOrder() const override;
  /*public*/ QString getBeanTypeHandled(bool plural);
  /*public*/ QString getNamedBeanClass();
  /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString systemName) override;
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString userName) override;
  /*public*/ void dispose()override;
  /*public*/ QString getNamedBeanClass() const override {return "jmri.managers.ProxyMeterManager";}
  QObject* self() override{return (QObject*)this;}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e)override;
  /*public*/ SystemConnectionMemo* getMemo() override {return AbstractProxyManager::getMemo();}

 private:
  /*private*/ bool muteUpdates = false;
//  /*private*/ /*final*/ List<Class<? extends Meter>> registerBeans = new ArrayList<>();
    /*private*/ /*final*/ QList<QString> registerBeans = QList<QString>();
//  /*private*/ /*final*/ List<Manager<? extends NamedBean>> registerBeanManagers = new ArrayList<>();
    /*private*/ /*final*/ QList<Manager*> registerBeanManagers = QList<Manager*>();


 protected:
  /*protected*/ AbstractManager* makeInternalManager() const override;
  /*protected*/ AbstractManager *createSystemManager(/*@Nonnull*/ SystemConnectionMemo* memo)  override;

};

#endif // PROXYMETERMANAGER_H
