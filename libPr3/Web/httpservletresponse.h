#ifndef HTTPSERVLETRESPONSE_H
#define HTTPSERVLETRESPONSE_H
#include "exceptions.h"
#include "servletresponse.h"
#include "../QtWebApp//QtWebApp/httpserver/httpcookie.h"
#include "../QtWebApp//QtWebApp//httpserver/httpresponse.h"
#include "requesthandler.h"

class RequestHandler;

/*public*/ /*interface*/ class HttpServletResponse : public ServletResponse
{
 //Q_OBJECT
public:
 HttpServletResponse(stefanfrings::HttpResponse* resp);
    /*public*/ const static  /*final*/ int SC_CONTINUE = 100;
    /*public*/ const static  /*final*/ int SC_SWITCHING_PROTOCOLS = 101;
    /*public*/ const static  /*final*/ int SC_OK = 200;
    /*public*/ const static  /*final*/ int SC_CREATED = 201;
    /*public*/ const static  /*final*/ int SC_ACCEPTED = 202;
    /*public*/ const static  /*final*/ int SC_NON_AUTHORITATIVE_INFORMATION = 203;
    /*public*/ const static  /*final*/ int SC_NO_CONTENT = 204;
    /*public*/ const static  /*final*/ int SC_RESET_CONTENT = 205;
    /*public*/ const static  /*final*/ int SC_PARTIAL_CONTENT = 206;
    /*public*/ const static  /*final*/ int SC_MULTIPLE_CHOICES = 300;
    /*public*/ const static  /*final*/ int SC_MOVED_PERMANENTLY = 301;
    /*public*/ const static  /*final*/ int SC_MOVED_TEMPORARILY = 302;
    /*public*/ const static  /*final*/ int SC_FOUND = 302;
    /*public*/ const static  /*final*/ int SC_SEE_OTHER = 303;
    /*public*/ const static  /*final*/ int SC_NOT_MODIFIED = 304;
    /*public*/ const static  /*final*/ int SC_USE_PROXY = 305;
    /*public*/ const static  /*final*/ int SC_TEMPORARY_REDIRECT = 307;
    /*public*/ const static  /*final*/ int SC_BAD_REQUEST = 400;
    /*public*/ const static  /*final*/ int SC_UNAUTHORIZED = 401;
    /*public*/ const static  /*final*/ int SC_PAYMENT_REQUIRED = 402;
    /*public*/ const static  /*final*/ int SC_FORBIDDEN = 403;
    /*public*/ const static  /*final*/ int SC_NOT_FOUND = 404;
    /*public*/ const static  /*final*/ int SC_METHOD_NOT_ALLOWED = 405;
    /*public*/ const static  /*final*/ int SC_NOT_ACCEPTABLE = 406;
    /*public*/ const static  /*final*/ int SC_PROXY_AUTHENTICATION_REQUIRED = 407;
    /*public*/ const static  /*final*/ int SC_REQUEST_TIMEOUT = 408;
    /*public*/ const static  /*final*/ int SC_CONFLICT = 409;
    /*public*/ const static  /*final*/ int SC_GONE = 410;
    /*public*/ const static  /*final*/ int SC_LENGTH_REQUIRED = 411;
    /*public*/ const static  /*final*/ int SC_PRECONDITION_FAILED = 412;
    /*public*/ const static  /*final*/ int SC_REQUEST_ENTITY_TOO_LARGE = 413;
    /*public*/ const static  /*final*/ int SC_REQUEST_URI_TOO_LONG = 414;
    /*public*/ const static  /*final*/ int SC_UNSUPPORTED_MEDIA_TYPE = 415;
    /*public*/ const static  /*final*/ int SC_REQUESTED_RANGE_NOT_SATISFIABLE = 416;
    /*public*/ const static  /*final*/ int SC_EXPECTATION_FAILED = 417;
    /*public*/ const static  /*final*/ int SC_INTERNAL_SERVER_ERROR = 500;
    /*public*/ const static  /*final*/ int SC_NOT_IMPLEMENTED = 501;
    /*public*/ const static  /*final*/ int SC_BAD_GATEWAY = 502;
    /*public*/ const static  /*final*/ int SC_SERVICE_UNAVAILABLE = 503;
    /*public*/ const static  /*final*/ int SC_GATEWAY_TIMEOUT = 504;
    /*public*/ const static  /*final*/ int SC_HTTP_VERSION_NOT_SUPPORTED = 505;

    /*public*/ virtual void addCookie(stefanfrings::HttpCookie* /*cookie*/) {}

    /*public*/ virtual bool containsHeader(QString /*string*/) {return false;}

    /*public*/ virtual QString encodeURL(QString /*string*/) {return "";}

    /*public*/ virtual QString encodeRedirectURL(QString /*string*/) {return "";}

    /*public*/ virtual QString encodeUrl(QString /*string*/) {return "";}

    /*public*/ virtual QString encodeRedirectUrl(QString /*string*/) {return "";}

    /*public*/ virtual void sendError(int /*i*/, QString /*string*/) /*throw (IOException)*/
    {
     // TODO:
    }

    /*public*/ virtual void sendError(int /*i*/) /*throw (IOException)*/ {}

    /*public*/ virtual void sendRedirect(QString /*string*/) /*throw (IOException)*/ {}

    /*public*/ virtual void setDateHeader(QString name, long value)
    {
     resp->setHeader(name.toLocal8Bit(), QString::number(value).toLocal8Bit());
    }

    /*public*/ virtual void addDateHeader(QString /*string*/, long /*l*/) {}

    /*public*/ virtual void setHeader(QString name, QString value)
    {
     resp->setHeader(name.toLocal8Bit(), value.toLocal8Bit());
 }

    /*public*/ virtual void addHeader(QString /*string*/, QString /*string1*/) {}

    /*public*/ virtual void setIntHeader(QString /*string*/, int /*i*/) {}

    /*public*/ virtual void addIntHeader(QString /*string*/, int /*i*/) {}

    /*public*/ virtual void setStatus(int i)
    {
     resp->setStatus(i, "??");
    }

    /*public*/ virtual void setStatus(int i, QString string)
    {
     resp->setStatus(i, string.toLocal8Bit());
    }

    /*public*/ virtual int getStatus()
    {
     return resp->getStatusCode();
    }

    /*public*/ virtual QString getHeader(QString /*string*/) {return "";}

    /*public*/ virtual QList<QString> getHeaders(QString /*string*/) {return QList<QString>();}

    /*public*/ virtual QList<QString> getHeaderNames() {return QList<QString>();}

    PrintWriter* getWriter() /*throw (IOException)*/;
    void setContentType(QString);
    stefanfrings::HttpResponse* resp;
    void setContentLength(int);

private:
};

#endif // HTTPSERVLETRESPONSE_H
