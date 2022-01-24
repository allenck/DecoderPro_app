#ifndef JMRISRCPSERVER_H
#define JMRISRCPSERVER_H
#include "jmriserver.h"

class JmriSRCPServer : public JmriServer
{
  Q_OBJECT
public:
 Q_INVOKABLE JmriSRCPServer(QObject* parent = nullptr);
 ~JmriSRCPServer() {}
 JmriSRCPServer(const JmriSRCPServer&) : JmriServer() {}
 /*synchronized*/ /*public*/ static JmriServer* instance();
 Q_INVOKABLE/*public*/ JmriSRCPServer(int port, QObject* parent = nullptr);


private:
 static Logger* log;

protected:
 /*protected*/ void advertise();

};
Q_DECLARE_METATYPE(JmriSRCPServer)
#endif // JMRISRCPSERVER_H
