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
 /*public*/ int getXMLOrder();
 /*public*/ QString getSystemPrefix() ;
 /*public*/ char typeLetter();
 /*public*/ Portal* createNewPortal(QString sName, QString userName);
 /*public*/ QString generateSystemName();
 /*public*/ Portal* getPortal(QString name);
 /*public*/ NamedBean* getBySystemName(QString name);
 /*public*/ NamedBean* getByUserName(QString key) ;
 /*public*/ Portal* providePortal(QString name);
 static /*public*/ PortalManager* instance();
 /*public*/ QString getBeanTypeHandled();
 /*public*/ bool isAssignableFromType() {return true;}

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
