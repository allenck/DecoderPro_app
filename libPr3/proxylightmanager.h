#ifndef PROXYLIGHTMANAGER_H
#define PROXYLIGHTMANAGER_H
#include "abstractproxymanager.h"

class Light;
class LIBPR3SHARED_EXPORT ProxyLightManager : public AbstractProxyManager
{
    Q_OBJECT
public:
 explicit ProxyLightManager(QObject *parent = 0);
 /*public*/ int getXMLOrder();
 /*public*/ Light* getLight(QString name);
 /*public*/ Light* provideLight(QString name);
 /*public*/ Light* getBySystemName(QString systemName);
 /*public*/ Light* getByUserName(QString userName);
 /*public*/ Light* newLight(QString systemName, QString userName);
 /*public*/ bool validSystemNameFormat(QString systemName);
 /*public*/ bool validSystemNameConfig(QString systemName);
 /*public*/ QString normalizeSystemName(QString systemName);
 /*public*/ QString convertSystemNameToAlternate(QString systemName);
 /*public*/ void activateAllLights();
 /*public*/ bool supportsVariableLights(QString systemName);
 /*public*/ bool allowMultipleAdditions(QString systemName);
 /*public*/ NamedBean* newNamedBean(QString systemName, QString userName);

signals:

public slots:
private:
 Logger* log;
protected:
 /*protected*/ Manager* makeInternalManager() const;
 /*protected*/ NamedBean* makeBean(int i, QString systemName, QString userName) ;
 friend class AbstractProxyManager;
};

#endif // PROXYLIGHTMANAGER_H
