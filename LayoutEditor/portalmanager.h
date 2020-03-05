#ifndef PORTALMANAGER_H
#define PORTALMANAGER_H

#include "abstractmanager.h"
#include "liblayouteditor_global.h"

class Portal;
class LIBLAYOUTEDITORSHARED_EXPORT PortalManager : public AbstractManager
{
 Q_OBJECT
public:
 explicit PortalManager(QObject *parent = 0);
 ~PortalManager() {}
 PortalManager(const PortalManager &) : AbstractManager() {}
 /*public*/ int getXMLOrder()const override;
 /*public*/ QString getSystemPrefix() const override;
 /*public*/ char typeLetter() const override;
 /*public*/ Portal* createNewPortal(QString sName, QString userName);
 /*public*/ QString generateSystemName();
 /*public*/ Portal* getPortal(QString name);
 /*public*/ NamedBean* getBySystemName(QString name)const override;
 /*public*/ NamedBean* getByUserName(QString key) const override;
 /*public*/ Portal* providePortal(QString name);
 static /*public*/ PortalManager* instance();
 /*public*/ QString getBeanTypeHandled();
 /*public*/ bool isAssignableFromType() {return true;}
 /*public*/ QString getNamedBeanClass()const override {
     return "Portal";
 }

signals:

public slots:
private:
 /*private*/ static int _nextSName;// = 1;
 static PortalManager* _instance;// = NULL;

protected:
 /*protected*/ void registerSelf();

};
Q_DECLARE_METATYPE(PortalManager)
#endif // PORTALMANAGER_H
