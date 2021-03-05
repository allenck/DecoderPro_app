#ifndef PROXYIDTAGMANAGER_H
#define PROXYIDTAGMANAGER_H
#include "abstractproxyidtagmanager.h"
#include "exceptions.h"

class Reporter;
class IdTag;
class ProxyIdTagManager : public AbstractProxyIdTagManager
{
 Q_OBJECT
public:
 ProxyIdTagManager(QObject *parent = nullptr);
 ~ProxyIdTagManager()  override{}
 ProxyIdTagManager(const ProxyIdTagManager& ) : AbstractProxyIdTagManager() {}
 /*public*/ int getXMLOrder()const  override;
 /*public*/ void init();
 /*public*/ bool isInitialised()override;
 /*public*/ DefaultIdTag* getIdTag(QString name)override;
 /*public*/ DefaultIdTag* provide(/*@Nonnull */QString name) throw (IllegalArgumentException) override;
 /*public*/ DefaultIdTag* provideIdTag(QString name) throw (IllegalArgumentException) override;
 /*public*/ NamedBean* getBySystemName(QString systemName)const override;
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

private:
/*private*/ bool useFastClock = false;
 /*private*/ bool stateSaved = false;

protected:
/*protected*/ AbstractManager* makeInternalManager()const override;
/*protected*/ NamedBean* makeBean(int i, QString systemName, QString userName);

};
Q_DECLARE_METATYPE(ProxyIdTagManager)
#endif // PROXYIDTAGMANAGER_H
