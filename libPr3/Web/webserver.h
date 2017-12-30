#ifndef WEBSERVER_H
#define WEBSERVER_H
#include <QTcpServer>
#include "exceptions.h"
#include "quietshutdowntask.h"
#include <QtCore/QList>
#include <QtCore/QByteArray>


QT_FORWARD_DECLARE_CLASS(QTcpServer)
QT_FORWARD_DECLARE_CLASS(QTcpSoocket)
class ServletContextHandler;
class HttpServlet;
class ShutDownTask;
class WebServerPreferences;
class Logger;
class WebServer : public QTcpServer
{
 Q_OBJECT
public:
 WebServer(QObject* parent = 0);
 ~WebServer();
 /*public*/ static WebServer* getDefault();
 /*public*/ void start();
 /*public*/ void stop() throw (Exception);
 /*public*/ int getPort();
 /*public*/ WebServerPreferences* getPreferences();
 /*public*/ void registerDenial(QString urlPattern);
 /*public*/ void registerResource(QString urlPattern, QString filePath) throw (IllegalArgumentException) ;
 /*public*/ void registerRedirection(QString urlPattern, QString redirection) throw (IllegalArgumentException);
 /*public*/ void registerServlet(/*Class<? extends HttpServlet>*/QString type);
 /*public*/ void registerServlet(/*Class<? extends HttpServlet>*/QString type, HttpServlet* instance);
 /*public*/ static QString URIforPortablePath(QString path);

#if 0
 /*private*/ QList<ServletContextHandler*> registerServlet(int options, /*Class<? extends HttpServlet>*/ QString type, HttpServlet instance)
         throw (InstantiationException, IllegalAccessException, InvocationTargetException, NoSuchMethodException) ;
#endif
#if 0
 /*public*/ void lifeCycleStarting(LifeCycle lc) ;
 /*public*/ void lifeCycleStarted(LifeCycle lc);
 /*public*/ void lifeCycleFailure(LifeCycle lc, Throwable thrwbl);
 /*public*/ void lifeCycleStopping(LifeCycle lc);
 /*public*/ void lifeCycleStopped(LifeCycle lc);
#endif
#if 0
 static /*private*/ class ServerThread extends Thread {

     /*private*/ final Server server;

     /*public*/ ServerThread(Server server) {
         this.server = server;
     }

     //@Override
     /*public*/ void run() {
         try {
             server.start();
             server.join();
         } catch (Exception ex) {
             log.error("Exception starting Web Server", ex);
         }
     }
 }
#endif

private:
 /*private*/ /*static*/ enum Registration {
     DENIAL, REDIRECTION, RESOURCE, SERVLET
 };

 /*private*/ WebServer* server;
// /*private*/ ZeroConfService zeroConfService = null;
 /*private*/ WebServerPreferences* preferences;// = null;
 /*private*/ ShutDownTask* shutDownTask;// = null;
 /*private*/ /*final*/ QMap<QString, Registration>* registeredUrls;// = new HashMap<>();
 /*private*/ /*final*/ static Logger* log;// = LoggerFactory.getLogger(WebServer.class.getName());
 void common();
 QList<QTcpSocket *> m_clients;
 bool m_debug;

private slots:
 void on_newConnection();
 void processBinaryMessage(QByteArray message);
 void processMessage();
 void socketDisconnected();

protected:
 /*protected*/ WebServer(WebServerPreferences* preferences, QObject* parent = 0);

};


/*static*/ /*private*/ class ServerShutDownTask : public  QuietShutDownTask {

    /*private*/ /*final*/ WebServer* server;
    /*private*/ bool _isComplete = false;

    /*public*/ ServerShutDownTask(WebServer* server);
    /*public*/ bool execute();
    /*public*/ bool isParallel();
    /*public*/ bool isComplete();
};
#endif // WEBSERVER_H
