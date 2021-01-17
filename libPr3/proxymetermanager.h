#ifndef PROXYMETERMANAGER_H
#define PROXYMETERMANAGER_H
#include "abstractproxymetermanager.h"
#include <QList>

class Manager;
class ProxyMeterManager : public AbstractProxyMeterManager
{
  Q_OBJECT
 public:
  ProxyMeterManager(QObject *parent = 0);
  /*public*/ int getXMLOrder() const override;
  /*public*/ QString getBeanTypeHandled(bool plural);
  /*public*/ QString getNamedBeanClass();
  /*public*/ NamedBean* getBySystemName(/*@Nonnull*/ QString systemName) const ;
  /*public*/ NamedBean* getByUserName(/*@Nonnull*/ QString userName) const ;
  /*public*/ void dispose();
  /*public*/ QString getNamedBeanClass() const override {return "jmri.managers.ProxyMeterManager";}
  QObject* self() {(QObject*)this;}
 public slots:
  /*public*/ void propertyChange(PropertyChangeEvent* e);

 private:
  /*private*/ bool muteUpdates = false;
//  /*private*/ /*final*/ List<Class<? extends Meter>> registerBeans = new ArrayList<>();
    /*private*/ /*final*/ QList<QString> registerBeans = QList<QString>();
//  /*private*/ /*final*/ List<Manager<? extends NamedBean>> registerBeanManagers = new ArrayList<>();
    /*private*/ /*final*/ QList<Manager*> registerBeanManagers = QList<Manager*>();


 protected:
  /*protected*/ ProxyMeterManager* makeInternalManager() const;
  /*protected*/ MeterManager* createSystemManager(/*@Nonnull*/ SystemConnectionMemo* memo) const override;

};

#endif // PROXYMETERMANAGER_H
