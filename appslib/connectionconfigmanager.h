#ifndef CONNECTIONCONFIGMANAGER_H
#define CONNECTIONCONFIGMANAGER_H
#include "abstractpreferencesmanager.h"
#include <QtXml>
#include "errorhandler.h"
#include "hasconnectionbutunabletoconnectexception.h"
#include "connectionconfig.h"

class ProxyConnectionTypeList;
class ConnectionTypeList;
class ConnectionTypeManager;
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
 Q_INVOKABLE/*public*/ void initialize(Profile* profile) override/*throw (InitializationException)*/;
 /*public*/ QSet<QString>* getRequires() override;
 /*public*/ void savePreferences(Profile* profile)override;
 /*public*/ bool add(/*@Nonnull*/ ConnectionConfig* c) /*throw (NullPointerException)*/;
 /*public*/ bool remove(/*@NonNULL*/ ConnectionConfig* c);
 /*public*/ QVector<ConnectionConfig*> getConnections();
 /*public*/ ConnectionConfig* getConnections(int index);
 /*public*/ QListIterator<ConnectionConfig*> iterator();
 /*public*/ QStringList getConnectionTypes(/*@NonNULL*/ QString manufacturer);
 /*public*/ QStringList getConnectionManufacturers();
 /*public*/ QString getConnectionManufacturer(/*@NonNULL*/ QString connectionType);
 /*public*/ QStringList getConnectionManufacturers(/*@NonNULL*/ QString connectionType);

 QObject* self() override {return (QObject*)this;}

private:
 /*private*/ /*final*/ QList<ConnectionConfig*> connections;// = new QList<ConnectionConfig*>();
 /*private*/ /*final*/ QString NAMESPACE;// = "http://jmri.org/xml/schema/auxiliary-configuration/connections-2-9-6.xsd"; // NOI18N
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger("ConnectionConfigManager");
 /*private*/ /*synchronized*/ void savePreferences(Profile* profile, bool shared);
 /*private*/ void setPortNamePattern();
 /*private*/ ConnectionTypeManager* getDefaultConnectionTypeManager();

};
Q_DECLARE_METATYPE(ConnectionConfigManager)
#if 0
/*private*/ /*static*/ class ConnectionTypeManager :QObject
{
Q_OBJECT
    /*private*/ /*final*/ QMap<QString, ConnectionTypeList*> connectionTypeLists;// = new HashMap<>();
public:
    /*public*/ ConnectionTypeManager();
    /*public*/ QStringList getConnectionTypes(QString manufacturer);
    /*public*/ QStringList getConnectionManufacturers() ;
private:
 static Logger* log;
};

/*private*/ /*static*/ class ProxyConnectionTypeList : public  ConnectionTypeList
{
Q_OBJECT
    /*private*/ /*final*/QList<ConnectionTypeList*> connectionTypeLists;// = new ArrayList<>();
public:
    /*public*/ ProxyConnectionTypeList(/*@NonNULL*/ ConnectionTypeList connectionTypeList);
    /*public*/ /*final*/ void add(/*@NonNULL*/ ConnectionTypeList connectionTypeList);
    //@Override
    /*public*/ QStringList getAvailableProtocolClasses() ;
    /*public*/ QStringList getManufacturers();
private:
 static Logger*log;
};
#endif
#if 1
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
