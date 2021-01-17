#ifndef PROXYLIGHTMANAGER_H
#define PROXYLIGHTMANAGER_H
#include "abstractproxylightmanager.h"

class Meter;
class LIBPR3SHARED_EXPORT ProxyLightManager : public AbstractProxyLightManager
{
    Q_OBJECT
public:
 explicit ProxyLightManager(QObject *parent = 0);
 /*public*/ int getXMLOrder() const override;
 /*public*/ Light* getLight(QString name)override;
 /*public*/ Light* provideLight(QString name)override;
 /*public*/ Light* getBySystemName(QString systemName) const override;
 /*public*/ Light* getByUserName(QString userName) const override;
 /*public*/ Light* newLight(QString systemName, QString userName)override;
// /*public*/ NameValidity validSystemNameFormat(QString systemName);
 /*public*/ bool validSystemNameConfig(QString systemName)const override;
// /*public*/ QString normalizeSystemName(QString systemName);
 /*public*/ QString convertSystemNameToAlternate(QString systemName)override;
 /*public*/ void activateAllLights()override;
 /*public*/ bool supportsVariableLights(QString systemName)override;
 /*public*/ bool allowMultipleAdditions(QString systemName)override;
// /*public*/ NamedBean* newNamedBean(QString systemName, QString userName);
 /*public*/ QString getEntryToolTip()override;
 /*public*/ QString getBeanTypeHandled(bool plural)const override;
 /*public*/ Light* provide(/*@Nonnull*/ QString name) throw (IllegalArgumentException)override;
 /*public*/ QString getNamedBeanClass()const override {
     return "Light";
 }
  /*public*/ QString toString() {return "ProxyLightManager";}

signals:

public slots:
private:
 Logger* log;
protected:
 /*protected*/ Manager* makeInternalManager() const override;
 /*protected*/ NamedBean* makeBean(int i, QString systemName, QString userName) override;
 friend class AbstractProxyManager;
};

#endif // PROXYLIGHTMANAGER_H
