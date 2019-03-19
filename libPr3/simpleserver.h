#ifndef SIMPLESERVER_H
#define SIMPLESERVER_H
#include "jmriserver.h"

class SimpleServer : public JmriServer
{
public:
 SimpleServer(QObject *parent = nullptr);
 QT_DEPRECATED /*public*/ static JmriServer* instance();
 /*public*/ SimpleServer(int port, QObject *parent = nullptr);

private:
 static Logger* log;
 void common(int port);

protected:
 /*protected*/ void advertise();

};

#endif // SIMPLESERVER_H
