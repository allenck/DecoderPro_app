#ifndef CONNECTIONCONFIGMANAGER_H
#define CONNECTIONCONFIGMANAGER_H

#include "abstractpreferencesmanager.h"

class Logger;
class ConnectionConfig;
class ConnectionTypeList;
class ConnectionConfigManager : public AbstractPreferencesManager
{
public:
 ConnectionConfigManager();
 /*public*/ void initialize(Profile* profile);// //throws InitializationException
 /*public*/ /*final*/ static QString CONNECTION;// = "connection"; // NOI18N
 /*public*/ /*final*/ static QString CLASS;// = "class"; // NOI18N
 /*public*/ /*final*/ static QString USER_NAME;// = "userName"; // NOI18N
 /*public*/ /*final*/ static QString SYSTEM_NAME;// = "systemPrefix"; // NOI18N
 /*public*/ /*final*/ static QString MANUFACTURER;// = "manufacturer"; // NOI18N

private:
 Logger* log;
 /*private*/ /*final*/ QList<ConnectionConfig*> connections;// = new ArrayList<>();
 /*private*/ /*final*/ QString NAMESPACE;// = "http://jmri.org/xml/schema/auxiliary-configuration/connections-2-9-6.xsd"; // NOI18N
 /*private*/ /*final*/ QString CONNECTIONS;// = "connections"; // NOI18N
};

/*private*/ /*static*/ class ConnectionTypeManager
{

    /*private*/ /*final*/ QMap<QString, ConnectionTypeList*> connectionTypeLists;// = new HashMap<>();
public:
    /*public*/ ConnectionTypeManager();
    /*public*/ QStringList getConnectionTypes(QString manufacturer);
    /*public*/ QStringList getConnectionManufacturers();

};
#endif // CONNECTIONCONFIGMANAGER_H
