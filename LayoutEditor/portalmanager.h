#ifndef PORTALMANAGER_H
#define PORTALMANAGER_H

#include "abstractmanager.h"
#include "liblayouteditor_global.h"
#include "swingpropertychangesupport.h"
#include "instancemanagerautodefault.h"
#include "propertychangelistener.h"

class Portal;
class LIBLAYOUTEDITORSHARED_EXPORT PortalManager : public AbstractManager, public InstanceManagerAutoDefault
{
 Q_OBJECT
  Q_INTERFACES(InstanceManagerAutoDefault )
public:
     explicit PortalManager(QObject *parent = 0);
     ~PortalManager() {}
     PortalManager(const PortalManager &) : AbstractManager() {}
     /*public*/ int getPortalCount();
     /*public*/ Portal* getPortal(int idx);
     /*public*/ int getIndexOf(Portal* portal);
     /*public*/ int getXMLOrder()const override;
     /*public*/ QString getSystemPrefix() const override;
     /*public*/ QChar typeLetter() const override;
     /*public*/ Portal* createNewPortal(QString sName);
     /*public*/ QString generateSystemName();
     /*public*/ Portal* getPortal(QString name);
     /*public*/ NamedBean *getBySystemName(QString name)const ;
     /*public*/ NamedBean* getByUserName(QString key) const ;
     /*public*/ Portal* providePortal(QString name);
     static /*public*/ PortalManager* instance();
     /*public*/ QString getBeanTypeHandled();
     /*public*/ bool isAssignableFromType() {return true;}
     /*public*/ QString getNamedBeanClass()const override {
         return "Portal";
     }
    /*public*/ QSet<Portal*> getPortalSet();
    QObject* self() override{return (QObject*)this;}
    QObject* vself() override {return (QObject*)this;}
    QObject* pself() override{return (QObject*)this;}

    void addPropertyChangeListener(PropertyChangeListener* l) override {PropertyChangeSupport::addPropertyChangeListener(l);}

signals:

public slots:
private:
 /*private*/ static int _nextSName;// = 1;
 static PortalManager* _instance;// = NULL;
 /*private*/ SwingPropertyChangeSupport* pcs = new SwingPropertyChangeSupport(this, nullptr);
 /*private*/ QList<Portal*> _nameList =QList<Portal*>();          // stores Portal in loaded order
 /*private*/ QMap<QString, Portal*> _portalMap = QMap<QString, Portal*>(); // stores portal by current name
 /*private*/ int _nextIndex = 1;

protected:
 /*protected*/ void registerSelf();

};
Q_DECLARE_METATYPE(PortalManager)
#endif // PORTALMANAGER_H
