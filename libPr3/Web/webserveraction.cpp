#include "webserveraction.h"
#include "loggerfactory.h"
#include <QApplication>
#ifndef QTWEBAPP
#include "webserver.h"
#else
#include <../QtWebApp/QtWebApp/httpserver/httplistener.h>
//#include <logging/filelogger.h>
#include "requesthandler.h"
//#include "logging/logmessage.h"
#endif
#include "webserverpreferences.h"
#include "json.h"
#include "zeroconfservice.h"

/**
 * Action to start a web server. Doesn't show a panel.
 *
 * @author	Randall Wood Copyright (C) 2012
 */
///*public*/ class WebServerAction extends JmriAbstractAction {

    /*private*/ /*final*/ /*static*/ Logger* WebServerAction::log = LoggerFactory::getLogger("WebServerAction");

/*public*/ WebServerAction::WebServerAction(QString s, WindowInterface* wi) : JmriAbstractAction(s,wi)
{
    //super(s, wi);
common();

}

/*public*/ WebServerAction::WebServerAction(QString s, QIcon i, WindowInterface* wi) : JmriAbstractAction(s, i, wi) {
    //super(s, i, wi);
 common();
}

/*public*/ WebServerAction::WebServerAction(QObject* parent) : JmriAbstractAction("Start JMRI Web Server", parent)
{
    //super(Bundle.getMessage("MenuWebServerAction"));
common();
}

void WebServerAction::common()
{
 //serverThread = NULL;
 setObjectName("WebServerAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

//@Override
/*public*/ void WebServerAction::actionPerformed(ActionEvent* ev)
{
#if 0
    synchronized (this) {
        if (serverThread == null) {
            serverThread = new ServerThread();
            serverThread.start();
        } else {
            log.info("Web Server already running");
        }
    }
#endif
#ifndef QTWEBAPP
  WebServer* server = WebServer::getDefault();
  if(server != NULL)
  {
   if(!server->isListening())
    server->start();
   else
    qDebug() << "server is already listening on port " << server->getPort();
  }
#else
   // Configure and start the TCP listener
   //QSettings* listenerSettings=new QSettings(configFileName,QSettings::IniFormat,&app);
    QSettings* listenerSettings = new QSettings(QApplication::organizationName(), QApplication::applicationName());
   listenerSettings->beginGroup("listener");
   listenerSettings->setValue("port", WebServerPreferences::getDefault()->getPort());
   new stefanfrings::HttpListener(listenerSettings,(stefanfrings::HttpRequestHandler*)new RequestHandler(this),this);

   QMap<QString, QVariant> properties = QMap<QString, QVariant>();
   properties.insert("path", "/"); // NOI18N
   properties.insert(JSON::_JSON, JSON::JSON_PROTOCOL_VERSION);
   log->info(tr("Starting ZeroConfService _http._tcp.local for Web Server with properties %1").arg(properties.keys().at(0)));
   zeroConfService = ZeroConfService::create("_http._tcp.local.", WebServerPreferences::getDefault()->getPort(), properties); // NOI18N
   zeroConfService->publish();
   log->debug("Web Server finished starting");

#endif
}

//@Override
/*public*/ JmriPanel* WebServerAction::makePanel() { return NULL; } // not used by this classes actionPerformed, as it doesn't show anything
#if 0
/*private*/ static class ServerThread extends Thread {

    //@Override
    /*public*/ void run() {
        WebServer.getDefault().start();
    }
}
#endif
