#ifndef PORTALMANAGER_H
#define PORTALMANAGER_H

#include "abstractmanager.h"
#include "liblayouteditor_global.h"
#include "propertychangesupport.h"

class Portal;
class LIBLAYOUTEDITORSHARED_EXPORT PortalManager : public AbstractManager
{
 Q_OBJECT
public:
 explicit PortalManager(QObject *parent = 0);
 ~PortalManager() {}
 PortalManager(const PortalManager &) : AbstractManager() {}
 /*public*/ int getPortalCount();
 /*public*/ Portal* getPortal(int idx);
 /*public*/ int getIndexOf(Portal* portal);
 /*public*/ int getXMLOrder()const override;
 /*public*/ QString getSystemPrefix() const override;
 /*public*/ char typeLetter() const override;
 /*public*/ Portal* createNewPortal(QString sName);
 /*public*/ QString generateSystemName();
 /*public*/ Portal* getPortal(QString name);
 /*public*/ Portal *getBySystemName(QString name)const ;
 /*public*/ Portal* getByUserName(QString key) const ;
 /*public*/ Portal* providePortal(QString name);
 static /*public*/ PortalManager* instance();
 /*public*/ QString getBeanTypeHandled();
 /*public*/ bool isAssignableFromType() {return true;}
 /*public*/ QString getNamedBeanClass()const override {
     return "Portal";
 }
 /*public*/ QSet<Portal*> getPortalSet();

signals:

public slots:
private:
 /*private*/ static int _nextSName;// = 1;
 static PortalManager* _instance;// = NULL;
 /*private*/ PropertyChangeSupport* pcs = new PropertyChangeSupport(this);
 /*private*/ QList<Portal*> _nameList =QList<Portal*>();          // stores Portal in loaded order
 /*private*/ QMap<QString, Portal*> _portalMap = QMap<QString, Portal*>(); // stores portal by current name
 /*private*/ int _nextIndex = 1;

protected:
 /*protected*/ void registerSelf();

};
Q_DECLARE_METATYPE(PortalManager)
#endif // PORTALMANAGER_H
