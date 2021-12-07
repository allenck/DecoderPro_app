#ifndef HTTPSERVLETREQUEST_H
#define HTTPSERVLETREQUEST_H
#include "servletrequest.h"
#include "httpservletresponse.h"
#include "servletexception.h"
#include "../QtWebApp//QtWebApp/httpserver/httprequest.h"
#include "requesthandler.h"
#include "fileutil.h"

class HttpServletResponse;
class RequestHandler;
class HttpSession;
class Principal;
class Cookie;
/*public*/ /*interface*/class  HttpServletRequest : public ServletRequest
{
Q_OBJECT
public:
 HttpServletRequest();
    HttpServletRequest(stefanfrings::HttpRequest* req);
    /*public*/ static /*final*/ QString BASIC_AUTH;// = "BASIC";
    /*public*/ static /*final*/ QString FORM_AUTH;// = "FORM";
    /*public*/ static /*final*/ QString CLIENT_CERT_AUTH;// = "CLIENT_CERT";
    /*public*/ static /*final*/ QString DIGEST_AUTH;// = "DIGEST";

    /*public*/ virtual QString getAuthType() {return "";}

    /*public*/ virtual QList<stefanfrings::HttpCookie*>* getCookies() {return NULL;}

    /*public*/ virtual long getDateHeader(QString /*string*/) {return 0;}

    /*public*/ virtual QString getHeader(QString /*string*/) {return "";}

    /*public*/ virtual QStringListIterator getHeaders(QString /*string*/)
    {
     QStringList list;
     return QStringListIterator (list);
    }

    /*public*/ virtual QStringListIterator getHeaderNames() { QStringList l; return QStringListIterator(l);}

    /*public*/ virtual int getIntHeader(QString /*string*/) {return 0;}

    /*public*/ virtual QString getMethod() {return "";}

    /*public*/ virtual QString getPathInfo()
    {
     QString path = req->getPath();
     QStringList sl = path.mid(1).split("/");
     if(sl.size() >=2)
     {
      QString pathInfo = path.mid(sl.at(0).length() + 1);
      return pathInfo;
     }
     return "";
    }

    /*public*/ virtual QString getPathTranslated() {return "";}

    /*Returns the portion of the request URI that indicates the context of the request. The context path always comes first in a request URI. The path starts with a "/" character but does not end with a "/" character. For servlets in the default (root) context, this method returns "". The container does not decode this string.*/
    /*public*/ virtual QString getContextPath()
    {
     QString path = req->getPath();
     QStringList sl = path.split("/");
     if(sl.size() >=2)
     {
      QString context= sl.at(1);
      return context + "/";
     }
     return "";
    }

    /*public*/ virtual QString getQueryString() {return "";}

    /*public*/ virtual QString getRemoteUser() {return "";}

    /*public*/ virtual bool isUserInRole(QString /*string*/) {return false;}

    /*public*/ virtual Principal* getUserPrincipal() {return NULL;}

    /*public*/ virtual QString getRequestedSessionId() {return "";}

    /*public*/ virtual QString getRequestURI()
    {
     return req->getPath();
    }

    /*public*/ virtual QString getRequestURL() {return "";}

    /*public*/ virtual QString getServletPath() {return "";}

    /*public*/ virtual HttpSession* getSession(bool /*bln*/) {return NULL;}

    /*public*/ virtual HttpSession* getSession()  {return NULL;}

    /*public*/ virtual QString changeSessionId() {return "";}

    /*public*/ virtual bool isRequestedSessionIdValid() {return false;}

    /*public*/ virtual bool isRequestedSessionIdFromCookie() {return false;}

    /*public*/ virtual bool isRequestedSessionIdFromURL() {return false;}

    /*public*/ virtual bool isRequestedSessionIdFromUrl() {return false;}

    /*public*/ virtual bool authenticate(HttpServletResponse* /*hsr*/) throw (IOException, ServletException) {return false;}

    /*public*/ virtual void login(QString /*string*/, QString /*string1*/) throw (ServletException()) {}

    /*public*/ virtual void logout() throw (ServletException()) {}
#if 0
    /*public*/ virtual Collection<Part> getParts() throw IOException, ServletException;

    /*public*/ virtual Part getPart(String string) throw IOException, ServletException;

    /*public*/ virtual <T extends HttpUpgradeHandler> T upgrade(Class<T> type) throws IOException, ServletException;
#endif
    /********************************************************************/
    QString getContentType();
    QMap<QString, QStringList*>* getParameterMap();
    QString getParameter(QString);
    QLocale getLocale();
    QTextStream* getReader() throw (IOException)
    {
     QByteArray ba = req->getBody();
     QTextStream* stream = new QTextStream(&ba, QIODevice::ReadOnly);
     return stream;
    }
private:
    stefanfrings::HttpRequest* req;
 friend class HttpServlet;
 friend class RosterServlet;
 friend class JmriJFrameServlet;
 friend class JsonServlet;
 friend class OperationsServlet;
 friend class DefaultServletContext;
};
#endif // HTTPSERVLETREQUEST_H
