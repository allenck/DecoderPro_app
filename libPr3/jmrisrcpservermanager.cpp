#include "jmrisrcpservermanager.h"
#include "instancemanager.h"
#include "jmrisrcpserverpreferences.h"
#include "file.h"
#include "fileutil.h"
#include "jmrisrcpserver.h"

///*public*/ class JmriSRCPServerManager {

/*static*/ /*private*/ JmriSRCPServerManager* JmriSRCPServerManager::instance = nullptr;

/*private*/ JmriSRCPServerManager::JmriSRCPServerManager(QObject* parent) : QObject(parent){
    if (InstanceManager::getNullableDefault("JmriSRCPServerPreferences") == nullptr) {
        QString fileName = FileUtil::getUserFilesPath() + "networkServices" + File::separator + "JmriSRCPServerPreferences.xml";
        if ((new File(fileName))->exists()) {
            InstanceManager::store(new JmriSRCPServerPreferences(fileName), "JmriSRCPServerPreferences"); // NOI18N
        } else {
            InstanceManager::store(new JmriSRCPServerPreferences(), "JmriSRCPServerPreferences"); // NOI18N
        }
    }
}

/*synchronized*/ /*public*/ /*static*/ JmriSRCPServerManager* JmriSRCPServerManager::getInstance() {
    if (instance == nullptr) {
        instance = new JmriSRCPServerManager();
    }
    return instance;
}

/*public*/ JmriSRCPServerPreferences* JmriSRCPServerManager::getPreferences() {
    if (preferences == nullptr) {
        preferences = new JmriSRCPServerPreferences();
    }
    return preferences;
}

/*public*/ /*static*/ JmriSRCPServerPreferences* JmriSRCPServerManager::getJmriSRCPServerPreferences() {
    return getInstance()->getPreferences();
}

/*public*/ JmriSRCPServer* JmriSRCPServerManager::getServer() {
    if (server == nullptr) {
        server = new JmriSRCPServer(this->getPreferences()->getPort());
    }
    return server;
}

/*public*/ /*static*/ JmriSRCPServer* JmriSRCPServerManager::getJmriSRCPServer() {
    return getInstance()->getServer();
}
