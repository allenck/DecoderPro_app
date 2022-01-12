#ifndef PROXYLIGHTMANAGER_H
#define PROXYLIGHTMANAGER_H
#include "abstractprovidingproxymanager.h"
#include "lightmanager.h"

class Meter;
class LIBPR3SHARED_EXPORT ProxyLightManager : public QObject, public AbstractProvidingProxyManager, public LightManager
{
    Q_OBJECT
  Q_INTERFACES(AbstractProvidingProxyManager LightManager)
public:
 explicit ProxyLightManager(QObject *parent = 0);
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
 /*public*/ Light* provide(/*@Nonnull*/ QString name) /*throw (IllegalArgumentException)*/override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Light";
 }
  /*public*/ QString toString() {return "ProxyLightManager";}
  QObject* self() override {return (QObject*)this;}

signals:

public slots:
private:
 Logger* log;
protected:
 /*protected*/ AbstractManager *makeInternalManager()  override;
 /*protected*/ NamedBean* makeBean(Manager* manager, QString systemName, QString userName)override;
 friend class AbstractProxyManager;
};

#endif // PROXYLIGHTMANAGER_H
