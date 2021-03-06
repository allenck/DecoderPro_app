#include "simpleservermanager.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "simpleserver.h"
#include "simpleserverpreferences.h"

// /*public*/ class SimpleServerManager {


/*private*/ SimpleServerManager::SimpleServerManager(QObject *parent) : QObject(parent)
{
    if (InstanceManager::getNullableDefault("SimpleServerPreferences") == nullptr) {
        QString fileName = FileUtil::getUserFilesPath() + "networkServices" + File::separator + "SimpleServer.xml";
        SimpleServerPreferences* prefs;
        if ((File(fileName)).exists()) {
            InstanceManager::store((QObject*)(prefs =new SimpleServerPreferences(fileName)), "SimpleServerPreferences"); // NOI18N
        } else {
            InstanceManager::store((QObject*)(prefs =new SimpleServerPreferences()), "SimpleServerPreferences");
        }
        prefs->init();
    }
    preferences = static_cast<SimpleServerPreferences*>(InstanceManager::getDefault("SimpleServerPreferences"));
}

/*public*/ /*static*/ SimpleServerManager* SimpleServerManager::getInstance()
{
    if (InstanceManager::getNullableDefault("SimpleServerManager") == nullptr)
    {
        InstanceManager::store(new SimpleServerManager(), "SimpleServerManager"); // NOI18N
    }
    return static_cast<SimpleServerManager*>(InstanceManager::getDefault("SimpleServerManager"));
}

/*public*/ SimpleServerPreferences* SimpleServerManager::getPreferences() {
    if (preferences == nullptr) {
        preferences = new SimpleServerPreferences();
    }
    return preferences;
}

/*public*/ /*static*/ SimpleServerPreferences* SimpleServerManager::getSimpleServerPreferences() {
    return getInstance()->getPreferences();
}

/*public*/ SimpleServer* SimpleServerManager::getServer() {
    if (server == nullptr) {
        server = new SimpleServer(this->getPreferences()->getPort());
    }
    return server;
}

/*public*/ /*static*/ SimpleServer* SimpleServerManager::getSimpleServer() {
    return getInstance()->getServer();
}
