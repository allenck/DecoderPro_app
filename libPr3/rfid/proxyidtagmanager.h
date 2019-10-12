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
 ~ProxyIdTagManager() {}
 ProxyIdTagManager(const ProxyIdTagManager& ) : AbstractProxyIdTagManager() {}
 /*public*/ int getXMLOrder();
 /*public*/ void init();
 /*public*/ bool isInitialised();
 /*public*/ IdTag* getIdTag(QString name);
 /*public*/ IdTag* provide(/*@Nonnull */QString name) throw (IllegalArgumentException);
 /*public*/ IdTag* provideIdTag(QString name) throw (IllegalArgumentException);
 /*public*/ IdTag* getBySystemName(QString systemName);
 /*public*/ IdTag* getByUserName(QString userName);
 /*public*/ IdTag* newIdTag(QString systemName, QString userName);
 /*public*/ IdTag* getByTagID(QString tagID);
 /*public*/ QString getEntryToolTip();
 /*public*/ QString getBeanTypeHandled(bool plural);
 /*public*/ void setStateStored(bool state);
 /*public*/ bool isStateStored();
 /*public*/ void setFastClockUsed(bool fastClock);
 /*public*/ bool isFastClockUsed();
 /*public*/ QList<IdTag*>* getTagsForReporter(Reporter* reporter, long threshold);

private:
/*private*/ bool useFastClock = false;
 /*private*/ bool stateSaved = false;

protected:
/*protected*/ AbstractManager* makeInternalManager();
/*protected*/ NamedBean* makeBean(int i, QString systemName, QString userName);

};
Q_DECLARE_METATYPE(ProxyIdTagManager)
#endif // PROXYIDTAGMANAGER_H
