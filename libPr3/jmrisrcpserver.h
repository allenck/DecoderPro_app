#ifndef JMRISRCPSERVER_H
#define JMRISRCPSERVER_H
#include "jmriserver.h"

class JmriSRCPServer : public JmriServer
{
public:
 JmriSRCPServer(QObject* parent = nullptr);
 /*synchronized*/ /*public*/ static JmriServer* instance();
 /*public*/ JmriSRCPServer(int port, QObject* parent = nullptr);


private:
 /*private*/ static JmriServer* _instance;// = nullptr;
 static Logger* log;

protected:
 /*protected*/ void advertise();

};

#endif // JMRISRCPSERVER_H
