#ifndef HTTPSERVLET_H
#define HTTPSERVLET_H
#include "genericservlet.h"
#include "httpservletresponse.h"
#include "httpservletrequest.h"
#include "servletoutputstream.h"

class ClassCastException : Exception
{
 ClassCastException(QString msg = "") : Exception(msg) {}
};

class HttpServletRequest;
class HttpServletResponse;
//class NoBodyOutputStream;
class HttpServlet : public GenericServlet
{
 Q_OBJECT
public:
 HttpServlet();

private:
 /*private*/ static /*final*/ QString METHOD_DELETE;// = "DELETE";
 /*private*/ static /*final*/ QString METHOD_HEAD;// = "HEAD";
 /*private*/ static /*final*/ QString METHOD_GET;// = "GET";
 /*private*/ static /*final*/ QString METHOD_OPTIONS;// = "OPTIONS";
 /*private*/ static /*final*/ QString METHOD_POST;// = "POST";
 /*private*/ static /*final*/ QString METHOD_PUT;// = "PUT";
 /*private*/ static /*final*/ QString METHOD_TRACE;// = "TRACE";

 /*private*/ static /*final*/ QString HEADER_IFMODSINCE;// = "If-Modified-Since";
 /*private*/ static /*final*/ QString HEADER_LASTMOD;// = "Last-Modified";

 /*private*/ static /*final*/ QString LSTRING_FILE;// = "javax.servlet.http.LocalStrings";
 /*private*/ QList<QMetaMethod> getAllDeclaredMethods(/*Class*/QString c);
 /*private*/ void maybeSetLastModified(HttpServletResponse* resp, long lastModified);

protected:
 /*protected*/ void doGet(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException);
 /*protected*/ long getLastModified(HttpServletRequest* req);
 /*protected*/ void doHead(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException);
 /*protected*/ void doPost(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException);
 /*protected*/ void doPut(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException);
 /*protected*/ void doDelete(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException);
 /*protected*/ void doOptions(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException);
 /*protected*/ void doTrace(HttpServletRequest* req, HttpServletResponse* resp)
 throw (ServletException, IOException);
 /*protected*/ void service(ServletRequest* req, ServletResponse* resp)
 throw (ServletException, IOException);
 /*protected*/ virtual void doList(HttpServletRequest* req, HttpServletResponse* resp)
 throw (ServletException, IOException);
friend class RequestHandler;
friend class ServletController;
};
#if 0
class NoBodyResponse : public HttpServletResponse
{
 Q_OBJECT
    /*private*/ HttpServletResponse*		resp;
    /*private*/ NoBodyOutputStream*		noBody;
    /*private*/ PrintWriter*			writer;
    /*private*/ bool			didSetContentLength;
HttpServlet* hs;
    // file /*private*/
public:
    NoBodyResponse(HttpServletResponse* r, HttpServlet* hs) ;
    void setContentLength();
    // SERVLET RESPONSE interface methods

    /*public*/ void setContentLength(int len);
    /*public*/ void setCharacterEncoding(QString charset);
    /*public*/ void setContentType(QString type);
    /*public*/ QString getContentType();
    /*public*/ ServletOutputStream* getOutputStream() throw (IOException);
    /*public*/ QString getCharacterEncoding();
    /*public*/ PrintWriter* getWriter() throw ( IOException);
    /*public*/ void setBufferSize(int size) throw (IllegalStateException);
    /*public*/ int getBufferSize();
    /*public*/ void reset() throw (IllegalStateException);
      /*public*/ void resetBuffer() throw (IllegalStateException);
    /*public*/ bool isCommitted();
    /*public*/ void flushBuffer() throw (IOException);
    /*public*/ void setLocale(QLocale loc);
    /*public*/ QLocale getLocale();
    // HTTP SERVLET RESPONSE interface methods

    /*public*/ void addCookie(stefanfrings::HttpCookie* cookie);
    /*public*/ bool containsHeader(QString name);
    /*public*/ void setStatus(int sc, QString sm);
    /*public*/ void setStatus(int sc);
    /*public*/ void setHeader(QString name, QString value);
    /*public*/ void setIntHeader(QString name, int value);
    /*public*/ void setDateHeader(QString name, long date);
    /*public*/ void sendError(int sc, QString msg) throw (IOException);
    /*public*/ void sendError(int sc) throw (IOException);
    /*public*/ void sendRedirect(QString location) throw (IOException);
    /*public*/ QString encodeURL(QString url);
    /*public*/ QString encodeRedirectURL(QString url);
    /*public*/ void addHeader(QString name, QString value);
    /*public*/ void addDateHeader(QString name, long value);
    /*public*/ void addIntHeader(QString name, int value);
    /*public*/ QT_DEPRECATED QString encodeUrl(QString url);
    /*public*/ QT_DEPRECATED QString encodeRedirectUrl(QString url);
};


/*
 * Servlet output stream that gobbles up all its data.
 */

// file /*private*/
class NoBodyOutputStream : public  ServletOutputStream
{
 Q_OBJECT
//    /*private*/ static ResourceBundle lStrings =
// ResourceBundle.getBundle(LSTRING_FILE);

    /*private*/ int		contentLength = 0;
public:
    // file /*private*/
    NoBodyOutputStream() ;
    int getContentLength() ;
    /*public*/ void write(int b) ;
    /*public*/ void write(QByteArray, int offset, int len)
 throw (IOException);
};
#endif
#endif // HTTPSERVLET_H
