#ifndef SIMPLESERVERMANAGER_H
#define SIMPLESERVERMANAGER_H

#include <QObject>

class SimpleServerPreferences;
class SimpleServer;
class SimpleServerManager : public QObject
{
 Q_OBJECT
public:
 explicit SimpleServerManager(QObject *parent = nullptr);
 /*public*/ static SimpleServerManager* getInstance();
 /*public*/ SimpleServerPreferences* getPreferences();
 /*public*/ static SimpleServerPreferences* getSimpleServerPreferences();
 /*public*/ SimpleServer* getServer();

signals:

public slots:

private:
 /*private*/ SimpleServerPreferences* preferences;
 /*private*/ SimpleServer* server;

};

#endif // SIMPLESERVERMANAGER_H
