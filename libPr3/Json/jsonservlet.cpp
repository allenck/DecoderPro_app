#include "jsonservlet.h"
#include "loggerfactory.h"
#include "jsonservicefactory.h"
#include "servletutil.h"
#include "jsonservicefactory.h"
#include "jsonhttpservice.h"
#include "websocketservletfactory.h"
#include "json.h"
#include <QUrl>
#include <QStringList>
#include "jsonblockservicefactory.h"
#include "jsonpowerservicefactory.h"
#include "jsonrosterservicefactory.h"
#include "jsonsensorservicefactory.h"
#include "jsonthrottleservicefactory.h"
#include "jsontimeservicefactory.h"
#include "jsonturnoutservicefactory.h"
#include "jsonutilservicefactory.h"
#include "jsonlightservicefactory.h"
#include "jsonclienthandler.h"
#include "jsonmemoryservicefactory.h"
#include "jsonsignalheadservicefactory.h"
#include "jsonsignalmastservicefactory.h"
#include "jsonreporterservicefactory.h"

JsonServlet::JsonServlet(QObject* parent) : WebSocketServlet()
{

}
/**
 * Provide JSON formatted responses for requests to requests for information
 * from the JMRI Web Server.
 *
 * This server supports long polling in some GET requests, but also provides a
 * WebSocket to provide a more extensive control and monitoring capability.
 *
 * This server responds to HTTP requests for objects in following manner:
 * <table>
 * <caption>HTTP methods handled by this servlet.</caption>
 * <tr><th>Method</th><th>List</th><th>Object</th></tr>
 * <tr><th>GET</th><td>Returns the list</td><td>Returns the object <em>if it
 * already exists</em></td></tr>
 * <tr><th>POST</th><td>Invalid</td><td>Modifies the object <em>if it already
 * exists</em></td></tr>
 * <tr><th>PUT</th><td>Invalid</td><td>Modifies the object, creating it if
 * required</td></tr>
 * </table>
 *
 * @author Randall Wood Copyright (C) 2012, 2013, 2016
 */
//@WebServlet(name = "JsonServlet",
//        urlPatterns = {"/json"})
///*public*/ class JsonServlet extends WebSocketServlet {

/*private*/ /*static*/ /*final*/ Logger* JsonServlet::log = LoggerFactory::getLogger("JsonServlet");

//@Override
/*public*/ void JsonServlet::init() throw (ServletException)  {
    WebSocketServlet::init();

    this->mapper =  ObjectMapper();
    QList<JsonServiceFactory*> factories = QList<JsonServiceFactory*>();
    factories << new JsonLightServiceFactory() << new JsonBlockServiceFactory() <<
                 new JsonPowerServiceFactory() << new JsonRosterServiceFactory() <<
                 new JsonSensorServiceFactory() <<
                 new JsonThrottleServiceFactory() << new JsonTimeServiceFactory() <<
                 new JsonTurnoutServiceFactory() << new JsonUtilServiceFactory() <<
                 new JsonMemoryServiceFactory() << new JsonSignalHeadServiceFactory() <<
                 new JsonSignalMastServiceFactory() << new JsonReporterServiceFactory();
#if 1
    //foreach (JsonServiceFactory* factory, ServiceLoader.load(JsonServiceFactory.class))
    foreach(JsonServiceFactory* factory,  factories)
    {
        JsonHttpService* service = factory->getHttpService(this->mapper);
        if (service != NULL) {
            foreach (QString type, factory->getTypes()) {
                QSet<JsonHttpService*>* set = this->services->value(type);
                if (set == NULL) {
                    this->services->insert(type, new QSet<JsonHttpService*>());
                    set = this->services->value(type);
                }
                set->insert(factory->getHttpService(this->mapper));
            }
        }
    }
#endif
}

//@Override
/*public*/ void JsonServlet::destroy() {
    WebSocketServlet::destroy();
}

//@Override
/*public*/ void configure(WebSocketServletFactory* factory) {
    factory->_register("JsonWebSocket");
}

/**
 * Handle HTTP get requests for JSON data. Examples:
 * <ul>
 * <li>/json/sensor/IS22 (return data for sensor with system name
 * "IS22")</li>
 * <li>/json/sensors (returns a list of all sensors known to JMRI)</li>
 * </ul>
 * sample responses:
 * <ul>
 * <li>{"type":"sensor","data":{"name":"IS22","userName":"FarEast","comment":NULL,"inverted":false,"state":4}}</li>
 * <li>[{"type":"sensor","data":{"name":"IS22","userName":"FarEast","comment":NULL,"inverted":false,"state":4}}]</li>
 * </ul>
 * Note that data will vary for each type.
 *
 * @param request  an HttpServletRequest object that contains the request
 *                 the client has made of the servlet
 * @param response an HttpServletResponse object that contains the response
 *                 the servlet sends to the client
 * @throw java.io.IOException if an input or output error is detected when
 *                             the servlet handles the GET request
 */
//@Override
/*protected*/ void JsonServlet::doGet(/*final*/ HttpServletRequest* request, HttpServletResponse* response) throw (IOException)
{
 response->setStatus(HttpServletResponse::SC_OK);
 response->setHeader("Connection", "Keep-Alive"); // NOI18N

 if (request->getAttribute("result") != QVariant())
 {
  QJsonObject result = request->getAttribute("result").toJsonObject();
  int code = result.value(JSON::DATA).toObject().value(JSON::CODE).toInt(HttpServletResponse::SC_OK); // use HTTP error codes when possible
  if (code == HttpServletResponse::SC_OK)
  {
      //response->getWriter().write(this->mapper.writeValueAsString(result));
   response->resp->write(QJsonDocument(result).toJson(), true);
  } else {
      this->sendError(response, code, QJsonDocument(result).toJson());
  }
  return;
 }

 QStringList rest = request->getPathInfo().split("/"); // NOI18N
 QString type = (rest.length() > 1) ? rest[1] : NULL;
 if (type != NULL)
 {
  response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
  ServletUtil::getInstance()->setNonCachingHeaders(response);
//        /*final*/ QString name = (rest.length() > 2) ? URLDecoder.decode(rest[2], StandardCharsets.UTF_8.name()) : NULL;
  QString name = QUrl::fromEncoded(rest.at(2).toLocal8Bit()).toString();
  QJsonObject parameters = QJsonObject(); //this->mapper.createObjectNode();
  //for (Map.Entry<QString, QStringList> entry : request->getParameterMap().entrySet())
  QMapIterator<QString, QStringList*> entry(*request->getParameterMap());
  while (entry.hasNext())
  {
   entry.next();
   parameters.insert(entry.key(), QUrl::fromEncoded(entry.value()->at(0).toLocal8Bit()).toString());
  }
  QJsonValue reply = QJsonValue();
  try
  {
   if (name == NULL)
   {
    if (this->services->value(type) != NULL)
    {
     QJsonArray array = QJsonArray(); //this->mapper.createObjectNode();
     JsonException* exception = NULL;
     try
     {
      foreach (JsonHttpService* service, *this->services->value(type))
      {
       array.append(service->doGetList(type, request->getLocale()));
      }
     }
     catch (JsonException ex)
     {
      exception = &ex;
     }
     switch (array.size())
     {
      case 0:
       if (exception != NULL)
       {
           throw exception;
       }
       reply = QJsonValue(array);
       break;
      case 1:
       reply = array.at(0);
       break;
      default:
       reply = QJsonValue(array);
       break;
     }
    }
    if (reply == QJsonObject())
    {
     log->warn(tr("Type %1 unknown.").arg(type));
     throw  JsonException(HttpServletResponse::SC_NOT_FOUND, tr(/*request->getLocale(), */"Unknown object type %1 was requested.").arg(type));
    }
   }
   else
   {
    if (this->services->value(type) != NULL)
    {
     QJsonArray array = QJsonArray();//this->mapper.createObjectNode();
     JsonException* exception = NULL;
     try
     {
      foreach (JsonHttpService* service, *this->services->value(type)) {
          array.append(service->doGet(type, name, request->getLocale()));
      }
     } catch (JsonException ex) {
         exception = &ex;
     }
     switch (array.size())
     {
      case 0:
       if (exception != NULL) {
           throw exception;
       }
       reply = array;
       break;
      case 1:
       reply = array.at(0);
       break;
      default:
       reply = array;
       break;
     }
    }
    if (reply == QJsonValue())
    {
     log->warn(tr("Requested type '%1' unknown.").arg(type));
     throw  JsonException(HttpServletResponse::SC_NOT_FOUND, tr(/*request->getLocale(),*/ "Unknown object type %1 was requested.").arg(type));
    }
   }
  } catch (JsonException ex) {
      reply = ex.getJsonMessage();
  }
  int code = reply.toObject().value(JSON::DATA).toObject().value(JSON::CODE).toInt(HttpServletResponse::SC_OK); // use HTTP error codes when possible
  if (code == HttpServletResponse::SC_OK)
  {
      //response->getWriter().write(this->mapper.writeValueAsString(reply));
   response->resp->write(QJsonDocument(reply.toObject()).toJson(),true);
  } else {
      //this->sendError(response, code, this->mapper.writeValueAsString(reply));
   this->sendError(response, code, QJsonDocument(reply.toObject()).toJson());
  }
} else {
  response->setContentType(ServletUtil::UTF8_TEXT_HTML); // NOI18N
#if 0
  response->getWriter().print(String.format(request->getLocale(),
          FileUtil::readURL(FileUtil::findURL(tr(request->getLocale(), "Json.html"))),
          String.format(request->getLocale(),
                  tr(request->getLocale(), "HtmlTitle"),
                  ServletUtil::getInstance().getRailroadName(false),
                  tr(request->getLocale(), "JsonTitle")
          ),
          ServletUtil::getInstance().getNavBar(request->getLocale(), request->getContextPath()),
          ServletUtil::getInstance().getRailroadName(false),
          ServletUtil::getInstance().getFooter(request->getLocale(), request->getContextPath())
  ));
#endif
  QString html = FileUtil::readURL(FileUtil::findURL(tr(/*request->getLocale(),*/ "web/servlet/json/Json.html")));
  QString title = tr("%2$s | %1$s");
  title= title.replace( "%1$s", ServletUtil::getInstance()->getRailroadName(false));
  title.replace("%2$s", tr("Json Console"));
  html = html.replace("%1$s", title);
  html = html.replace("%2$s", ServletUtil::getInstance()->getNavBar(request->getLocale(), request->getContextPath()));
  html = html.replace("%3$s", ServletUtil::getInstance()->getRailroadName(false));
  html = html.replace("%4$s", ServletUtil::getInstance()->getFooter(request->getLocale(), request->getContextPath()));
  response->resp->write(html.toLocal8Bit(),true);
 }
}

//@Override
/*protected*/ void JsonServlet::doPost(HttpServletRequest* request, HttpServletResponse* response) throw (IOException)
{
 response->setStatus(HttpServletResponse::SC_OK);
 response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
 response->setHeader("Connection", "Keep-Alive"); // NOI18N
 ServletUtil::getInstance()->setNonCachingHeaders(response);

 QStringList rest = request->getPathInfo().split("/"); // NOI18N
 QString type = (rest .length() > 1) ? rest[1] : NULL;
 QString name = (rest .length() > 2) ? rest[2] : NULL;
 QJsonObject data;
 QJsonValue reply = QJsonValue();
 try
 {
  if (request->getContentType().contains(ServletUtil::APPLICATION_JSON))
  {
   //data = this->mapper.readTree(request->getReader());
   data =  QJsonDocument::fromJson(request->req->getBody()).object();  //QJsonDocument::fromJson(string.toUtf8());
   data = data.value(JSON::DATA).toObject();
  }
  else {
      data = QJsonObject(); //this->mapper.createObjectNode();
      if (request->getParameter(JSON::STATE) != NULL) {
          ( data).insert(JSON::STATE, (request->getParameter(JSON::STATE).toInt()));
      } else if (request->getParameter(JSON::LOCATION) != NULL) {
          ( data).insert(JSON::LOCATION, request->getParameter(JSON::LOCATION));
      } else if (request->getParameter(JSON::VALUE) != NULL) {
          // values other than Strings should be sent in a JSON object
          ( data).insert(JSON::VALUE, request->getParameter(JSON::VALUE));
      }
  }
  if (type != NULL) {
      // for historical reasons, set the name to POWER on a power request
      if (type == (JSON::POWER)) {
          name = JSON::POWER;
      } else if (name == NULL) {
          name = data.value(JSON::NAME).toString();
      }
      log->debug(tr("POST operation for %1/%2 with %3").arg(type).arg(name).arg(QString(QJsonDocument(data).toJson())));
      if (name != NULL)
      {
       if (this->services->value(type) != NULL)
       {
        log->debug(tr("Using data: %1").arg(QString(QJsonDocument(data).toJson())));
        QJsonArray array = QJsonArray(); //this->mapper.createObjectNode();
        JsonException* exception = NULL;
        try {
            foreach (JsonHttpService* service, *this->services->value(type)) {
                array.append(service->doPost(type, name, data, request->getLocale()));
            }
        } catch (JsonException ex) {
            exception = &ex;
        }
        switch (array.size())
        {
         case 0:
             if (exception != NULL) {
                 throw exception;
             }
             reply = array;
             break;
         case 1:
             reply = array.at(0);
             break;
         default:
             reply = array;
             break;
        }
       }
       if (reply == QJsonObject()) {
           log->warn(tr("Type %1 unknown.").arg(type));
           throw  JsonException(HttpServletResponse::SC_NOT_FOUND, tr(/*request->getLocale(),*/ "Unknown object type %1 was requested.").arg(type));
       }
   } else {
       log->error("Name must be defined.");
       throw JsonException(HttpServletResponse::SC_BAD_REQUEST, "Name must be defined."); // Need to I18N
   }
  } else {
      log->warn("Type not specified.");
      throw JsonException(HttpServletResponse::SC_BAD_REQUEST, "Type must be specified."); // Need to I18N
  }
 } catch (JsonException ex) {
     reply = ex.getJsonMessage();
 }
 int code = reply.toObject().value(JSON::DATA).toObject().value(JSON::CODE).toInt(HttpServletResponse::SC_OK); // use HTTP error codes when possible
 if (code == HttpServletResponse::SC_OK) {
     response->resp->write(QJsonDocument(reply.toObject()).toJson(),true);
 } else {
     this->sendError(response, code, QJsonDocument(reply.toObject()).toJson());
 }
}

//@Override
/*protected*/ void JsonServlet::doPut(HttpServletRequest* request, HttpServletResponse* response) throw (IOException) {
    response->setStatus(HttpServletResponse::SC_OK);
    response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
    response->setHeader("Connection", "Keep-Alive"); // NOI18N
    ServletUtil::getInstance()->setNonCachingHeaders(response);

    QStringList rest = request->getPathInfo().split("/"); // NOI18N
    QString type = (rest .length() > 1) ? rest[1] : NULL;
    QString name = (rest .length() > 2) ? rest[2] : NULL;
    QJsonObject data;
    QJsonValue reply = QJsonValue();
    try {
        if (request->getContentType().contains(ServletUtil::APPLICATION_JSON)) {
            data =  QJsonDocument::fromJson(request->req->getBody()).object();  //this->mapper->readTree(request->getReader());
            if (!data.value(JSON::DATA).isNull()) {
                data = data.value(JSON::DATA).toObject();
            }
        } else {
            throw JsonException(HttpServletResponse::SC_BAD_REQUEST, "PUT request must be a JSON object"); // need to I18N
        }
        if (type != NULL) {
            // for historical reasons, set the name to POWER on a power request
            if (type == (JSON::POWER)) {
                name = JSON::POWER;
            } else if (name == NULL) {
                name = data.value(JSON::NAME).toString();
            }
            if (name != NULL) {
                if (this->services->value(type) != NULL) {
                    QJsonArray array = QJsonArray(); //this->mapper.createObjectNode();
                    JsonException* exception = NULL;
                    try {
                        foreach (JsonHttpService* service, *this->services->value(type)) {
                            array.append(service->doPut(type, name, data, request->getLocale()));
                        }
                    } catch (JsonException ex) {
                        exception = &ex;
                    }
                    switch (array.size()) {
                        case 0:
                            if (exception != NULL) {
                                throw exception;
                            }
                            reply = array;
                            break;
                        case 1:
                            reply = array.at(0);
                            break;
                        default:
                            reply = array;
                            break;
                    }
                }
                if (reply == QJsonValue()) {
                    // not a creatable item
                    throw JsonException(HttpServletResponse::SC_BAD_REQUEST, type + " is not a creatable type"); // need to I18N
                }
            } else {
                log->warn(tr("Type %1 unknown.").arg(type));
                throw  JsonException(HttpServletResponse::SC_NOT_FOUND, tr(/*request->getLocale(),*/ "Unknown object type %1 was requested.").arg(type));
            }
        } else {
            log->warn("Type not specified.");
            throw  JsonException(HttpServletResponse::SC_BAD_REQUEST, "Type must be specified."); // Need to I18N
        }
    } catch (JsonException ex) {
        reply = ex.getJsonMessage();
    }
    int code = reply.toObject().value(JSON::DATA).toObject().value(JSON::CODE).toInt(HttpServletResponse::SC_OK); // use HTTP error codes when possible
    if (code == HttpServletResponse::SC_OK) {
        response->resp->write(QJsonDocument(reply.toObject()).toJson(),true);
    } else {
        this->sendError(response, code, QString(QJsonDocument(reply.toObject()).toJson()));
    }
}

//@Override
/*protected*/ void JsonServlet::doDelete(HttpServletRequest* request, HttpServletResponse* response) throw (ServletException, IOException) {
    response->setStatus(HttpServletResponse::SC_OK);
    response->setContentType(ServletUtil::UTF8_APPLICATION_JSON);
    response->setHeader("Connection", "Keep-Alive"); // NOI18N
    ServletUtil::getInstance()->setNonCachingHeaders(response);

    QStringList rest = request->getPathInfo().split("/"); // NOI18N
    QString type = (rest .length() > 1) ? rest[1] : NULL;
    QString name = (rest .length() > 2) ? rest[2] : NULL;
    QJsonObject reply = QJsonObject(); //mapper.createObjectNode();
    try {
        if (type != NULL) {
            if (name == NULL) {
                throw JsonException(HttpServletResponse::SC_BAD_REQUEST, "name must be specified"); // need to I18N
            }
            foreach (JsonHttpService* service, *this->services->value(type)) {
                service->doDelete(type, name, request->getLocale());
            }
        } else {
            log->warn("Type not specified.");
            throw JsonException(HttpServletResponse::SC_BAD_REQUEST, "Type must be specified."); // Need to I18N
        }
    } catch (JsonException ex) {
        reply = ex.getJsonMessage();
    }
    int code = reply.value(JSON::DATA).toObject().value(JSON::CODE).toInt(HttpServletResponse::SC_OK); // use HTTP error codes when possible
    // only include a response body if something went wrong
    if (code != HttpServletResponse::SC_OK) {
        this->sendError(response, code, QJsonDocument(reply).toJson());
    }
}

/*public*/ void JsonServlet::sendError(HttpServletResponse* response, int code, QString message) throw (IOException) {
    response->setStatus(code);
    //response->getWriter().write(message);
    response->resp->write(message.toLocal8Bit());
}
