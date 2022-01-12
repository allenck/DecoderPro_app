#ifndef PROXYIDTAGMANAGER_H
#define PROXYIDTAGMANAGER_H
#include "abstractprovidingproxymanager.h"
#include "exceptions.h"

class Reporter;
class IdTag;
class ProxyIdTagManager : public QObject, public AbstractProvidingProxyManager, public IdTagManager
{
 Q_OBJECT
  Q_INTERFACES(IdTagManager AbstractProvidingProxyManager)
public:
 ProxyIdTagManager(QObject *parent = nullptr);
 ~ProxyIdTagManager()  override{}
 ProxyIdTagManager(const ProxyIdTagManager& ) : QObject() {}
 /*public*/ int getXMLOrder()const  override;
 /*public*/ void init() override;
 /*public*/ bool isInitialised()  override;
 /*public*/ DefaultIdTag* getIdTag(QString name)override;
 /*public*/ DefaultIdTag* provide(/*@Nonnull */QString name) /*throw (IllegalArgumentException)*/ override;
 /*public*/ DefaultIdTag* provideIdTag(QString name) throw (IllegalArgumentException) override;
 /*public*/ DefaultIdTag *getBySystemName(QString systemName)const override;
 /*public*/ NamedBean* getByUserName(QString userName)const override;
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
 QObject* self() override {return (QObject*)this;}

private:
/*private*/ bool useFastClock = false;
 /*private*/ bool stateSaved = false;

protected:
/*protected*/ AbstractManager* makeInternalManager() override;
/*protected*/ NamedBean* makeBean(Manager* m, QString systemName, QString userName)override;

};
Q_DECLARE_METATYPE(ProxyIdTagManager)
#endif // PROXYIDTAGMANAGER_H
