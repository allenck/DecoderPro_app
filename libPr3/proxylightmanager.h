#ifndef PROXYLIGHTMANAGER_H
#define PROXYLIGHTMANAGER_H
#include "abstractprovidingproxymanager.h"
#include "lightmanager.h"
#include "libPr3_global.h"

class Meter;
class LIBPR3SHARED_EXPORT ProxyLightManager : public AbstractProvidingProxyManager, public LightManager
{
  Q_OBJECT
  Q_INTERFACES(LightManager)
public:
  ProxyLightManager(QObject *parent = 0);
 /*public*/ int getXMLOrder() const override;
 /*public*/ Light* getLight(QString name)override;
 /*public*/ Light* provideLight(QString name)override;
// /*public*/ NamedBean* getBySystemName(QString systemName) const override;
 /*public*/ NamedBean* getByUserName(QString userName) override;
 /*public*/ Light* newLight(QString systemName, QString userName)override;
// /*public*/ NameValidity validSystemNameFormat(QString systemName);
 /*public*/ bool validSystemNameConfig(QString systemName) override;
// /*public*/ QString normalizeSystemName(QString systemName);
 /*public*/ QString convertSystemNameToAlternate(QString systemName)override;
 /*public*/ void activateAllLights()override;
 /*public*/ bool supportsVariableLights(QString systemName)override;
 /*public*/ bool allowMultipleAdditions(QString systemName)override;
  /*public*/ QString getNextValidAddress(/*@Nonnull*/ QString curAddress, /*@Nonnull*/ QString prefix, bool ignoreInitialExisting) /*throws jmri.JmriException*/ override;
 /*public*/ QString getEntryToolTip()override;
 /*public*/ QString getBeanTypeHandled(bool plural)const override;
 /*public*/ NamedBean* provide(/*@Nonnull*/ QString name) /*throw (IllegalArgumentException)*/override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Light";
 }
  /*public*/ QString toString() override {return "ProxyLightManager";}

  QObject* self() override {return (QObject*)this;}
  QObject* vself() override {return (QObject*)this;}
  QObject* mself() override {return (QObject*)this;}
  QObject* pself() override{return (QObject*)this;}

  /*public*/ SystemConnectionMemo* getMemo() override {return AbstractProxyManager::getMemo();}
  /*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractProxyManager::getNamedBeanSet();}
  /*public*/ Light* getBySystemName(QString name) override {return (Light*)AbstractProxyManager::getBySystemName(name);}
  /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{AbstractProxyManager::addPropertyChangeListener(l);}
  /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{AbstractProxyManager::removePropertyChangeListener(l);}

signals:

public slots:
private:
 static Logger* log;
protected:
 /*protected*/ AbstractManager *makeInternalManager() const override;
 /*protected*/ NamedBean* makeBean(AbstractManager* manager, QString systemName, QString userName)override;
 friend class AbstractProxyManager;
};

#endif // PROXYLIGHTMANAGER_H
