#include "webserver.h"
#include "loggerfactory.h"
#include "webserverpreferences.h"
#include "instancemanager.h"
#include "fileutil.h"
#include "QtWebSockets/QWebSocket"
#include <QtCore/QDebug>
#include "rosterservlet.h"

/**
 * An HTTP server that handles requests for HTTPServlets.
 *
 * This server loads HttpServlets registered as
 * {@link javax.servlet.http.HttpServlet} service providers and annotated with
 * the {@link javax.servlet.annotation.WebServlet} annotation. It also loads the
 * registered {@link jmri.server.web.spi.WebServerConfiguration} objects to get
 * configuration for file handling, redirection, and denial of access to
 * resources.
 *
 * When there is a conflict over how a path should be handled, denials take
 * precedence, followed by servlets, redirections, and lastly direct access to
 * files.
 *
 * @author Bob Jacobsen Copyright 2005, 2006
 * @author Randall Wood Copyright 2012, 2016
 */
///*public*/ final class WebServer implements LifeCycle.Listener {

/*private*/ /*final*/ /*static*/ Logger* WebServer::log = LoggerFactory::getLogger("WebServer");

/**
 * Create a WebServer instance with the default preferences.
 */
/*public*/ WebServer::WebServer(QObject* parent) : QTcpServer(parent) {
 common();
 preferences = WebServerPreferences::getDefault();

    //this(WebServerPreferences::getDefault());
}

void WebServer::common()
{
 preferences = NULL;
 shutDownTask = NULL;
 registeredUrls = new QMap<QString, Registration>();
}

/**
 * Create a WebServer instance with the specified preferences.
 *
 * @param preferences the preferences
 */
/*protected*/ WebServer::WebServer(WebServerPreferences* preferences, QObject* parent) : QTcpServer( parent) {
 common();
 this->preferences = preferences;
}

WebServer::~WebServer()
{
 close();
 qDeleteAll(m_clients.begin(), m_clients.end());
}

/**
 * Get the default web server instance.
 *
 * @return a WebServer instance, either the existing instance or a new
 *         instance created with the default constructor.
 */
//@NonNULL
/*public*/ /*static*/ WebServer* WebServer::getDefault() {
//    return InstanceManager.getOptionalDefault("WebServer").orElseGet(() -> {
//        return InstanceManager.setDefault(WebServer.class, new WebServer());
//    });
 WebServer* server = (WebServer*)InstanceManager::getOptionalDefault("WebServer");
 if(server ==  NULL)
 {
  server = (WebServer*)InstanceManager::setDefault("WebServer", new WebServer());
 }
 return server;
}

/**
 * Start the web server.
 */
/*public*/ void WebServer::start()
 {
#if 0
    if (server == NULL) {
        QueuedThreadPool threadPool = new QueuedThreadPool();
        threadPool.setName("WebServer");
        threadPool.setMaxThreads(1000);
        server = new Server(threadPool);
        ServerConnector connector = new ServerConnector(server);
        connector.setIdleTimeout(5 * 60 * 1000); // 5 minutes
        connector.setSoLingerTime(-1);
        connector.setPort(preferences.getPort());
        server.setConnectors(new Connector[]{connector});
        server.setHandler(new ContextHandlerCollection());

        // Load all path handlers
        ServiceLoader.load(WebServerConfiguration.class).forEach((configuration) -> {
            configuration.getFilePaths().entrySet().forEach((resource) -> {
                this->registerResource(resource.getKey(), resource.getValue());
            });
            configuration.getRedirectedPaths().entrySet().forEach((redirection) -> {
                this->registerRedirection(redirection.getKey(), redirection.getValue());
            });
            configuration.getForbiddenPaths().forEach((denial) -> {
                this->registerDenial(denial);
            });
        });
        // Load all classes that provide the HttpServlet service.
        ServiceLoader.load(HttpServlet.class).forEach((servlet) -> {
            this->registerServlet(servlet.getClass(), servlet);
        });
        server.addLifeCycleListener(this);

        Thread serverThread = new ServerThread(server);
        serverThread.setName("WebServer"); // NOI18N
        serverThread.start();

    }
#endif
    if(listen(QHostAddress::Any, preferences->getPort()))
    {
      connect(this, SIGNAL(newConnection()), this, SLOT(on_newConnection()));
      qDebug() << "server listening on port " << preferences->getPort();
    }
    qRegisterMetaType<RosterServlet>("RosterServlet");

}

/**
 * Stop the server.
 *
 * @throws Exception if there is an error stopping the server
 */
/*public*/ void WebServer::stop() throw (Exception) {
    server->stop();
}

/**
 * Get the public URI for a portable path. This method returns public URIs
 * for only some portable paths, and does not check that the portable path
 * is actually sane. Note that this refuses to return portable paths that
 * are outside of {@link jmri.util.FileUtil#PREFERENCES},
 * {@link jmri.util.FileUtil#PROFILE},
 * {@link jmri.util.FileUtil#SETTINGS}, or
 * {@link jmri.util.FileUtil#PROGRAM}.
 *
 * @param path the JMRI portable path
 * @return The servable URI or NULL
 * @see jmri.util.FileUtil#getPortableFilename(java.io.File)
 */
/*public*/ /*static*/ QString WebServer::URIforPortablePath(QString path) {
    if (path.startsWith(FileUtil::PREFERENCES)) {
        return path.replace(FileUtil::PREFERENCES, "/prefs/"); // NOI18N
    } else if (path.startsWith(FileUtil::PROFILE)) {
        return path.replace(FileUtil::PROFILE, "/project/"); // NOI18N
    } else if (path.startsWith(FileUtil::SETTINGS)) {
        return path.replace(FileUtil::SETTINGS, "/settings/"); // NOI18N
    } else if (path.startsWith(FileUtil::PROGRAM)) {
        return path.replace(FileUtil::PROGRAM, "/dist/"); // NOI18N
    } else {
        return NULL;
    }
}

/*public*/ int WebServer::getPort() {
    return preferences->getPort();
}

/*public*/ WebServerPreferences* WebServer::getPreferences() {
    return preferences;
}

/**
 * Register a URL pattern to be denied access.
 *
 * @param urlPattern the pattern to deny access to
 */
/*public*/ void WebServer::registerDenial(QString urlPattern) {
#if 0
    this->registeredUrls->insert(urlPattern, Registration::DENIAL);
    ServletContextHandler* servletContext = new ServletContextHandler(ServletContextHandler::NO_SECURITY);
    servletContext.setContextPath(urlPattern);
    DenialServlet servlet = new DenialServlet();
    servletContext.addServlet(new ServletHolder(servlet), "/*"); // NOI18N
    ((ContextHandlerCollection) this->server.getHandler()).addHandler(servletContext);
#endif
}

/**
 * Register a URL pattern to return resources from the file system. The
 * filePath may start with any of the following:
 * <ol>
 * <li>{@link jmri.util.FileUtil#PREFERENCES}
 * <li>{@link jmri.util.FileUtil#PROFILE}
 * <li>{@link jmri.util.FileUtil#SETTINGS}
 * <li>{@link jmri.util.FileUtil#PROGRAM}
 * </ol>
 * Note that the filePath can be overridden by an otherwise identical
 * filePath starting with any of the portable paths above it in the
 * preceding list.
 *
 * @param urlPattern the pattern to get resources for
 * @param filePath   the portable path for the resources
 * @throws IllegalArgumentException if urlPattern is already registered to
 *                                  deny access or for a servlet or if
 *                                  filePath is not allowed
 */
/*public*/ void WebServer::registerResource(QString urlPattern, QString filePath) throw (IllegalArgumentException) {
    if (this->registeredUrls->value(urlPattern) != NULL) {
        throw new IllegalArgumentException("urlPattern \"" + urlPattern + "\" is already registered.");
    }
    this->registeredUrls->insert(urlPattern, RESOURCE);
#if 0
    ServletContextHandler servletContext = new ServletContextHandler(ServletContextHandler.NO_SECURITY);
    servletContext.setContextPath(urlPattern);

    HandlerList handlers = new HandlerList();
    if (filePath.startsWith(FileUtil::PROGRAM) && !filePath==(FileUtil::PROGRAM)) {
        // make it possible to override anything under program: with an identical path under preference:, profile:, or settings:
        log->debug("Setting up handler chain for {}", urlPattern);
        ResourceHandler preferenceHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath.replace(FileUtil::PROGRAM, FileUtil::PREFERENCES)));
        ResourceHandler projectHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath.replace(FileUtil::PROGRAM, FileUtil::PROFILE)));
        ResourceHandler settingsHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath.replace(FileUtil::PROGRAM, FileUtil::SETTINGS)));
        ResourceHandler programHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath));
        handlers.setHandlers(new Handler[]{preferenceHandler, projectHandler, settingsHandler, programHandler, new DefaultHandler()});
    } else if (filePath.startsWith(FileUtil::SETTINGS) && !filePath==(FileUtil::SETTINGS)) {
        // make it possible to override anything under settings: with an identical path under preference: or profile:
        log->debug("Setting up handler chain for {}", urlPattern);
        ResourceHandler preferenceHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath.replace(FileUtil::SETTINGS, FileUtil::PREFERENCES)));
        ResourceHandler projectHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath.replace(FileUtil::PROGRAM, FileUtil::PROFILE)));
        ResourceHandler settingsHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath));
        handlers.setHandlers(new Handler[]{preferenceHandler, projectHandler, settingsHandler, new DefaultHandler()});
    } else if (filePath.startsWith(FileUtil::PROFILE) && !filePath==(FileUtil::PROFILE)) {
        // make it possible to override anything under profile: with an identical path under preference:
        log->debug("Setting up handler chain for {}", urlPattern);
        ResourceHandler preferenceHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath.replace(FileUtil::SETTINGS, FileUtil::PREFERENCES)));
        ResourceHandler projectHandler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath.replace(FileUtil::PROGRAM, FileUtil::PROFILE)));
        handlers.setHandlers(new Handler[]{preferenceHandler, projectHandler, new DefaultHandler()});
    } else if (FileUtil::isPortableFilename(filePath)) {
        log->debug("Setting up handler chain for {}", urlPattern);
        ResourceHandler handler = new DirectoryHandler(FileUtil::getAbsoluteFilename(filePath));
        handlers.setHandlers(new Handler[]{handler, new DefaultHandler()});
    } else if (URIforPortablePath(filePath) == NULL) {
        throw new IllegalArgumentException("\"" + filePath + "\" is not allowed.");
    }
    ContextHandler handlerContext = new ContextHandler();
    handlerContext.setContextPath(urlPattern);
    handlerContext.setHandler(handlers);
    ((ContextHandlerCollection) this->server.getHandler()).addHandler(handlerContext);
#endif
}

/**
 * Register a URL pattern to be redirected to another resource.
 *
 * @param urlPattern  the pattern to be redirected
 * @param redirection the path to which the pattern is redirected
 * @throws IllegalArgumentException if urlPattern is already registered for
 *                                  any other purpose
 */
/*public*/ void WebServer::registerRedirection(QString urlPattern, QString redirection) throw (IllegalArgumentException) {
    Registration registered = this->registeredUrls->value(urlPattern);
    if (registered != NULL && registered != REDIRECTION) {
        throw new IllegalArgumentException("\"" + urlPattern + "\" registered to " + registered);
    }
    this->registeredUrls->insert(urlPattern, REDIRECTION);
#if 0
    ServletContextHandler servletContext = new ServletContextHandler(ServletContextHandler.NO_SECURITY);
    servletContext.setContextPath(urlPattern);
    RedirectionServlet servlet = new RedirectionServlet(urlPattern, redirection);
    servletContext.addServlet(new ServletHolder(servlet), ""); // NOI18N
    ((ContextHandlerCollection) this->server.getHandler()).addHandler(servletContext);
#endif
}

/**
 * Register a {@link javax.servlet.http.HttpServlet } that is annotated with
 * the {@link javax.servlet.annotation.WebServlet } annotation.
 *
 * This method calls
 * {@link #registerServlet(java.lang.Class, javax.servlet.http.HttpServlet)}
 * with a NULL HttpServlet.
 *
 * @param type The actual class of the servlet.
 */
/*public*/ void WebServer::registerServlet(/*Class<? extends HttpServlet>*/QString type) {
    this->registerServlet(type, NULL);
}

/**
 * Register a {@link javax.servlet.http.HttpServlet } that is annotated with
 * the {@link javax.servlet.annotation.WebServlet } annotation.
 *
 * Registration reads the WebServlet annotation to get the list of paths the
 * servlet should handle and creates instances of the Servlet to handle each
 * path.
 *
 * Note that all HttpServlets registered using this mechanism must have a
 * default constructor.
 *
 * @param type     The actual class of the servlet.
 * @param instance An un-initialized, un-registered instance of the servlet.
 */
/*public*/ void WebServer::registerServlet(/*Class<? extends HttpServlet>*/QString type, HttpServlet* instance) {
#if 0
    try {
        for (ServletContextHandler handler : this->registerServlet(
                ServletContextHandler.NO_SECURITY,
                type,
                instance
        )) {
            ((ContextHandlerCollection) this->server.getHandler()).addHandler(handler);
        }
    } catch (InstantiationException | IllegalAccessException | InvocationTargetException | NoSuchMethodException ex) {
        log->error("Unable to register servlet", ex);
    }
#endif
}
#if 0
/*private*/ QList<ServletContextHandler*> WebServer::registerServlet(int options, /*Class<? extends HttpServlet> */QString type, HttpServlet* instance)
        throw (InstantiationException, IllegalAccessException, InvocationTargetException, NoSuchMethodException) {

    WebServlet info = type.getAnnotation(WebServlet.class);
    List<ServletContextHandler> handlers = new ArrayList<>(info.urlPatterns().length);
    for (String pattern : info.urlPatterns()) {
        if (this->registeredUrls.get(pattern) != Registration.DENIAL) {
            // DenialServlet gets special handling
            if (info.name()==("DenialServlet")) { // NOI18N
                this->registeredUrls.put(pattern, Registration.DENIAL);
            } else {
                this->registeredUrls.put(pattern, Registration.SERVLET);
            }
            ServletContextHandler context = new ServletContextHandler(options);
            context.setContextPath(pattern);
            log->debug("Creating new {} for URL pattern {}", type.getName(), pattern);
            context.addServlet(type, "/*"); // NOI18N
            handlers.add(context);
        } else {
            log->error("Unable to register servlet \"{}\" to provide denied URL {}", info.name(), pattern);
        }
    }
    return handlers;
}
//@Override
/*public*/ void lifeCycleStarting(LifeCycle lc) {
    shutDownTask = new ServerShutDownTask(this);
    InstanceManager.getOptionalDefault(ShutDownManager.class).ifPresent(manager -> {
        manager.register(shutDownTask);
    });
    log->info("Starting Web Server on port {}", preferences.getPort());
}

//@Override
/*public*/ void lifeCycleStarted(LifeCycle lc) {
    HashMap<String, String> properties = new HashMap<>();
    properties.put("path", "/"); // NOI18N
    properties.put(JSON.JSON, JSON.JSON_PROTOCOL_VERSION);
    log->info("Starting ZeroConfService _http._tcp.local for Web Server with properties {}", properties);
    zeroConfService = ZeroConfService.create("_http._tcp.local.", preferences.getPort(), properties); // NOI18N
    zeroConfService.publish();
    log->debug("Web Server finished starting");
}

//@Override
/*public*/ void lifeCycleFailure(LifeCycle lc, Throwable thrwbl) {
    log->error("Web Server failed", thrwbl);
}

//@Override
/*public*/ void lifeCycleStopping(LifeCycle lc) {
    if (zeroConfService != NULL) {
        zeroConfService.stop();
    }
    log->info("Stopping Web Server");
}

//@Override
/*public*/ void lifeCycleStopped(LifeCycle lc) {
    InstanceManager.getOptionalDefault(ShutDownManager.class).ifPresent(manager -> {
        manager.deregister(shutDownTask);
    });
    log->debug("Web Server stopped");
}
#endif
#if 0
static /*private*/ class ServerThread extends Thread {

    /*private*/ final Server server;

    /*public*/ ServerThread(Server server) {
        this->server = server;
    }

    //@Override
    /*public*/ void run() {
        try {
            server.start();
            server.join();
        } catch (Exception ex) {
            log->error("Exception starting Web Server", ex);
        }
    }
}
#endif

//static /*private*/ class ServerShutDownTask extends QuietShutDownTask {

//    /*private*/ final WebServer server;
//    /*private*/ bool isComplete = false;

    /*public*/ ServerShutDownTask::ServerShutDownTask(WebServer* server) :QuietShutDownTask("Stop Web Server"){
        //super("Stop Web Server"); // NOI18N
        this->server = server;
    }

    //@Override
    /*public*/ bool ServerShutDownTask::execute() {
#if 0
        new Thread(() -> {
            try {
                server.stop();
            } catch (Exception ex) {
                // Error without stack trace
                log->warn("Error shutting down WebServer: {}", ex);
                // Full stack trace
                log->debug("Details follow: ", ex);
            }
            this->isComplete = true;
        }).start();
#endif
        return true;
    }

    //@Override
    /*public*/ bool ServerShutDownTask::isParallel() {
        return true;
    }

    //@Override
    /*public*/ bool ServerShutDownTask::isComplete() {
        return this->_isComplete;
    }

void WebServer::on_newConnection()
{
    QTcpSocket *pSocket = this->nextPendingConnection();

    connect(pSocket, SIGNAL(readyRead()), this, SLOT(processMessage()));
    //connect(pSocket, &QWebSocket::binaryMessageReceived, this, &WebServer::processBinaryMessage);
//    connect(pSocket, &QWebSocket::disconnected, this, &WebServer::socketDisconnected);

    m_clients << pSocket;
}

void WebServer::processMessage()
{
 QTcpSocket *pSender = qobject_cast<QTcpSocket *>(sender());
 QStringList tokens;
 while (pSender->canReadLine())
 {
   tokens = QString(pSender->readLine()).split(QRegExp("[ \r\n][ \r\n]*"));

     qDebug() << "QStringList ---------";
     for (QList<QString>::iterator i = tokens.begin(); i != tokens.end(); ++i)
         qDebug() << (*i);

 if(tokens.at(0) == "GET")
 {
  QFile* f = new QFile(FileUtil::getProgramPath() + "web" + tokens.at(1));
  qDebug() << "file " << f->fileName();
  if(f->exists())
  {
   if(f->open(QIODevice::ReadOnly))
   {
    QTextStream* in = new QTextStream(f);
    QString data;
    *in >> data;
    pSender->write(data.toLocal8Bit());
     f->close();
   }
  }
 }
}
}
void WebServer::processBinaryMessage(QByteArray message)
{
    QTcpSocket *pClient = qobject_cast<QTcpSocket *>(sender());
    if (m_debug)
        qDebug() << "Binary Message received:" << message;
//    if (pClient) {
//        pClient->sendBinaryMessage(message);
//    }
}
void WebServer::socketDisconnected()
{
    QTcpSocket *pClient = qobject_cast<QTcpSocket *>(sender());
    if (pClient)
    {
        m_clients.removeAll(pClient);
        pClient->deleteLater();
    }
}
