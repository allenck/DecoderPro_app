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
 /*public*/ static SimpleServer* getSimpleServer();

signals:

public slots:

private:
 /*private*/ SimpleServerPreferences* preferences;
 /*private*/ SimpleServer* server = nullptr;

};

#endif // SIMPLESERVERMANAGER_H
