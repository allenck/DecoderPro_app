#ifndef PROXYIDTAGMANAGER_H
#define PROXYIDTAGMANAGER_H
#include "abstractprovidingproxymanager.h"
#include "exceptions.h"

class Reporter;
class IdTag;
class ProxyIdTagManager : public AbstractProvidingProxyManager, public IdTagManager
{
 Q_OBJECT
  Q_INTERFACES(IdTagManager )
public:
 ProxyIdTagManager(QObject *parent = nullptr);
 ~ProxyIdTagManager()  override{}
 ProxyIdTagManager(const ProxyIdTagManager& ) : AbstractProvidingProxyManager() {}
 /*public*/ int getXMLOrder()const  override;
 /*public*/ void init()  override;
 /*public*/ bool isInitialised() override;
 /*public*/ AbstractManager/*<IdTag>*/* getDefaultManager() const override;
 /*public*/ DefaultIdTag* getIdTag(QString name)override;
 /*public*/ /*SortedSet<IdTag>*/QSet<NamedBean*> getNamedBeanSet() override;
 /*public*/ DefaultIdTag* provide(/*@Nonnull */QString name) /*throw (IllegalArgumentException)*/ override;
 /*public*/ DefaultIdTag* provideIdTag(QString name) throw (IllegalArgumentException) override;
 /*public*/ DefaultIdTag* getBySystemName(QString systemName) override;
 /*public*/ DefaultIdTag* getByUserName(QString userName) override;
 /*public*/ DefaultIdTag* newIdTag(QString systemName, QString userName) override;
 /*public*/ DefaultIdTag *getByTagID(QString tagID) override;
 /*public*/ QString getEntryToolTip() override;
 /*public*/ QString getBeanTypeHandled(bool plural)const override;
 /*public*/ void setStateStored(bool state) override;
 /*public*/ bool isStateStored() override;
 /*public*/ void setFastClockUsed(bool fastClock) override;
 /*public*/ bool isFastClockUsed() override;
 /*public*/ QList<IdTag*>* getTagsForReporter(Reporter* reporter, long threshold) override;
 /*public*/ QString getNamedBeanClass()const override {
     return "ProxyIdTag";
 }
 /*public*/ SystemConnectionMemo* getMemo() override {return AbstractProxyManager::getMemo();}
 /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{AbstractProxyManager::addPropertyChangeListener(l);}
 /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{AbstractProxyManager::removePropertyChangeListener(l);}


 QObject* self() override {return (QObject*)this;}
 QObject* vself() override {return (QObject*)this;}

private:
/*private*/ bool useFastClock = false;
 /*private*/ bool stateSaved = false;

protected:
/*protected*/ AbstractManager* makeInternalManager() const override;
/*protected*/ DefaultIdTag* makeBean(AbstractManager* m, QString systemName, QString userName)override;

};
Q_DECLARE_METATYPE(ProxyIdTagManager)
#endif // PROXYIDTAGMANAGER_H
