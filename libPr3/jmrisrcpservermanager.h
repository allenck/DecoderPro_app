#ifndef JMRISRCPSERVERMANAGER_H
#define JMRISRCPSERVERMANAGER_H

#include <QObject>

class JmriSRCPServer;
class JmriSRCPServerPreferences;
class JmriSRCPServerManager : public QObject
{
 Q_OBJECT
public:
 /*synchronized*/ /*public*/ static JmriSRCPServerManager* getInstance();
 /*public*/ JmriSRCPServerPreferences *getPreferences();
 /*public*/ static JmriSRCPServerPreferences* getJmriSRCPServerPreferences();
 /*public*/ JmriSRCPServer* getServer();
 /*public*/ static JmriSRCPServer* getJmriSRCPServer();

signals:

public slots:

private:
 static /*private*/ JmriSRCPServerManager* instance;// = nullptr;
 /*private*/ JmriSRCPServerPreferences* preferences;
 /*private*/ JmriSRCPServer* server;
 explicit JmriSRCPServerManager(QObject *parent = nullptr);

};

#endif // JMRISRCPSERVERMANAGER_H
