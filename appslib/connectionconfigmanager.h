#ifndef CONNECTIONCONFIGMANAGER_H
#define CONNECTIONCONFIGMANAGER_H
#include "abstractpreferencesmanager.h"
#include <QtXml>
#include "errorhandler.h"
#include "hasconnectionbutunabletoconnectexception.h"

class ConnectionConfig;
class Logger;
class ConnectionConfigManager : public AbstractPreferencesManager
{
 Q_OBJECT
public:
 ConnectionConfigManager();
 ~ConnectionConfigManager() {}
 ConnectionConfigManager(const ConnectionConfigManager&) : AbstractPreferencesManager() {}
 /*public*/ /*final*/ static QString CONNECTIONS;// = "connections"; // NOI18N
 /*public*/ /*final*/ static QString CONNECTION;// = "connection"; // NOI18N
 /*public*/ /*final*/ static QString CLASS;// = "class"; // NOI18N
 /*public*/ /*final*/ static QString USER_NAME;// = "userName"; // NOI18N
 /*public*/ /*final*/ static QString SYSTEM_NAME;// = "systemPrefix"; // NOI18N
 /*public*/ /*final*/ static QString MANUFACTURER;// = "manufacturer"; // NOI18N
 /*public*/ void initialize(Profile* profile)throw (InitializationException);
 /*public*/ QSet<QString>* getRequires();
 /*public*/ void savePreferences(Profile* profile);
 /*public*/ bool add(/*@Nonnull*/ ConnectionConfig* c) throw (NullPointerException);
 /*public*/ bool remove(/*@NonNULL*/ ConnectionConfig* c);
 /*public*/ QVector<ConnectionConfig*> getConnections();
 /*public*/ ConnectionConfig* getConnections(int index);
 /*public*/ QListIterator<ConnectionConfig*> iterator();

private:
 /*private*/ /*final*/ QList<ConnectionConfig*> connections;// = new QList<ConnectionConfig*>();
 /*private*/ /*final*/ QString NAMESPACE;// = "http://jmri.org/xml/schema/auxiliary-configuration/connections-2-9-6.xsd"; // NOI18N
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("ConnectionConfigManager");
 /*private*/ /*synchronized*/ void savePreferences(Profile* profile, bool shared);
 /*private*/ void setPortNamePattern();

};
Q_DECLARE_METATYPE(ConnectionConfigManager)

#if 0
/*private*/ /*static*/ class ConnectionConfigManagerErrorHandler : public ErrorHandler
{
 Q_OBJECT
public:
    QList<HasConnectionButUnableToConnectException> exceptions;// = new ArrayList<>();

    /*public*/ ConnectionConfigManagerErrorHandler();
    /*public*/ void handle(ErrorMemo* memo);
};
#endif
#endif // CONNECTIONCONFIGMANAGER_H
