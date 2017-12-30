#include "httpservlet.h"
#include <QTextStream>
#include <QMetaType>
#include <QMetaMethod>
#include "httpserver/httpcookie.h"
#include <QTextCodec>
/**
 *
 * Provides an abstract class to be subclassed to create
 * an HTTP servlet suitable for a Web site. A subclass of
 * <code>HttpServlet</code> must override at least
 * one method, usually one of these:
 *
 * <ul>
 * <li> <code>doGet</code>, if the servlet supports HTTP GET requests
 * <li> <code>doPost</code>, for HTTP POST requests
 * <li> <code>doPut</code>, for HTTP PUT requests
 * <li> <code>doDelete</code>, for HTTP DELETE requests
 * <li> <code>init</code> and <code>destroy</code>,
 * to manage resources that are held for the life of the servlet
 * <li> <code>getServletInfo</code>, which the servlet uses to
 * provide information about itself
 * </ul>
 *
 * <p>There's almost no reason to override the <code>service</code>
 * method. <code>service</code> handles standard HTTP
 * requests by dispatching them to the handler methods
 * for each HTTP request type (the <code>do</code><i>XXX</i>
 * methods listed above).
 *
 * <p>Likewise, there's almost no reason to override the
 * <code>doOptions</code> and <code>doTrace</code> methods.
 *
 * <p>Servlets typically run on multithreaded servers,
 * so be aware that a servlet must handle concurrent
 * requests and be careful to synchronize access to shared resources.
 * Shared resources include in-memory data such as
 * instance or class variables and external objects
 * such as files, database connections, and network
 * connections.
 * See the
 * <a href="http://java.sun.com/Series/Tutorial/java/threads/multithreaded.html">
 * Java Tutorial on Multithreaded Programming</a> for more
 * information on handling multiple threads in a Java program.
 *
 * @author	Various
 */



///*public*/ /*abstract*/ class HttpServlet : public GenericServlet
//    //implements java.io.Serializable
//{
    /*private*/ /*static*/ /*final*/ QString HttpServlet::METHOD_DELETE = "DELETE";
    /*private*/ /*static*/ /*final*/ QString HttpServlet::METHOD_HEAD = "HEAD";
    /*private*/ /*static*/ /*final*/ QString HttpServlet::METHOD_GET = "GET";
    /*private*/ /*static*/ /*final*/ QString HttpServlet::METHOD_OPTIONS = "OPTIONS";
    /*private*/ /*static*/ /*final*/ QString HttpServlet::METHOD_POST = "POST";
    /*private*/ /*static*/ /*final*/ QString HttpServlet::METHOD_PUT = "PUT";
    /*private*/ /*static*/ /*final*/ QString HttpServlet::METHOD_TRACE = "TRACE";

    /*private*/ /*static*/ /*final*/ QString HttpServlet::HEADER_IFMODSINCE = "If-Modified-Since";
    /*private*/ /*static*/ /*final*/ QString HttpServlet::HEADER_LASTMOD = "Last-Modified";

    /*private*/ /*static*/ /*final*/ QString HttpServlet::LSTRING_FILE =
 "javax.servlet.http.LocalStrings";
//    /*private*/ static ResourceBundle lStrings =
// ResourceBundle.getBundle(LSTRING_FILE);




/**
 * Does nothing, because this is an abstract class.
 *
 */

/*public*/ HttpServlet::HttpServlet() { }



/**
 *
 * Called by the server (via the <code>service</code> method) to
 * allow a servlet to handle a GET request.
 *
 * <p>Overriding this method to support a GET request also
 * automatically supports an HTTP HEAD request. A HEAD
 * request is a GET request that returns no body in the
 * response, only the request header fields.
 *
 * <p>When overriding this method, read the request data,
 * write the response headers, get the response's writer or
 * output stream object, and finally, write the response data.
 * It's best to include content type and encoding. When using
 * a <code>PrintWriter</code> object to return the response,
 * set the content type before accessing the
 * <code>PrintWriter</code> object.
 *
 * <p>The servlet container must write the headers before
 * committing the response, because in HTTP the headers must be sent
 * before the response body.
 *
 * <p>Where possible, set the Content-Length header (with the
 * {@link javax.servlet.ServletResponse#setContentLength} method),
 * to allow the servlet container to use a persistent connection
 * to return its response to the client, improving performance.
 * The content length is automatically set if the entire response fits
 * inside the response buffer.
 *
 * <p>When using HTTP 1.1 chunked encoding (which means that the response
 * has a Transfer-Encoding header), do not set the Content-Length header.
 *
 * <p>The GET method should be safe, that is, without
 * any side effects for which users are held responsible.
 * For example, most form queries have no side effects.
 * If a client request is intended to change stored data,
 * the request should use some other HTTP method.
 *
 * <p>The GET method should also be idempotent, meaning
 * that it can be safely repeated. Sometimes making a
 * method safe also makes it idempotent. For example,
 * repeating queries is both safe and idempotent, but
 * buying a product online or modifying data is neither
 * safe nor idempotent.
 *
 * <p>If the request is incorrectly formatted, <code>doGet</code>
 * returns an HTTP "Bad Request" message.
 *
 *
 * @param req	an {@link HttpServletRequest} object that
 *			contains the request the client has made
 *			of the servlet
 *
 * @param resp	an {@link HttpServletResponse} object that
 *			contains the response the servlet sends
 *			to the client
 *
 * @exception IOException	if an input or output error is
 *				detected when the servlet handles
 *				the GET request
 *
 * @exception ServletException	if the request for the GET
 *					could not be handled
 *
 *
 * @see javax.servlet.ServletResponse#setContentType
 *
 */

/*protected*/ void HttpServlet::doGet(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException)
{
 QString protocol = req->getProtocol();
 QString msg = tr("http.method_get_not_supported");
 if (protocol.endsWith("1.1"))
 {
  resp->sendError(HttpServletResponse::SC_METHOD_NOT_ALLOWED, msg);
 }
 else
 {
  resp->sendError(HttpServletResponse::SC_BAD_REQUEST, msg);
 }
}

/**
 *
 * Returns the time the <code>HttpServletRequest</code>
 * object was last modified,
 * in milliseconds since midnight January 1, 1970 GMT.
 * If the time is unknown, this method returns a negative
 * number (the default).
 *
 * <p>Servlets that support HTTP GET requests and can quickly determine
 * their last modification time should override this method.
 * This makes browser and proxy caches work more effectively,
 * reducing the load on server and network resources.
 *
 *
 * @param req	the <code>HttpServletRequest</code>
 *			object that is sent to the servlet
 *
 * @return		a <code>long</code> integer specifying
 *			the time the <code>HttpServletRequest</code>
 *			object was last modified, in milliseconds
 *			since midnight, January 1, 1970 GMT, or
 *			-1 if the time is not known
 *
 */

/*protected*/ long HttpServlet::getLastModified(HttpServletRequest* /*req*/)
{
 return -1;
}




/**
 *
 *
 * <p>Receives an HTTP HEAD request from the protected
 * <code>service</code> method and handles the
 * request.
 * The client sends a HEAD request when it wants
 * to see only the headers of a response, such as
 * Content-Type or Content-Length. The HTTP HEAD
 * method counts the output bytes in the response
 * to set the Content-Length header accurately.
 *
 * <p>If you override this method, you can avoid computing
 * the response body and just set the response headers
 * directly to improve performance. Make sure that the
 * <code>doHead</code> method you write is both safe
 * and idempotent (that is, protects itself from being
 * called multiple times for one HTTP HEAD request).
 *
 * <p>If the HTTP HEAD request is incorrectly formatted,
 * <code>doHead</code> returns an HTTP "Bad Request"
 * message.
 *
 *
 * @param req	the request object that is passed
 *			to the servlet
 *
 * @param resp	the response object that the servlet
 *			uses to return the headers to the clien
 *
 * @exception IOException		if an input or output error occurs
 *
 * @exception ServletException	if the request for the HEAD
 *					could not be handled
 */

/*protected*/ void HttpServlet::doHead(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException)
{
#if 0
NoBodyResponse* response = new NoBodyResponse(resp, this);

doGet(req, response);
response->setContentLength();
#endif
}





/**
 *
 * Called by the server (via the <code>service</code> method)
 * to allow a servlet to handle a POST request.
 *
 * The HTTP POST method allows the client to send
 * data of unlimited length to the Web server a single time
 * and is useful when posting information such as
 * credit card numbers.
 *
 * <p>When overriding this method, read the request data,
 * write the response headers, get the response's writer or output
 * stream object, and finally, write the response data. It's best
 * to include content type and encoding. When using a
 * <code>PrintWriter</code> object to return the response, set the
 * content type before accessing the <code>PrintWriter</code> object.
 *
 * <p>The servlet container must write the headers before committing the
 * response, because in HTTP the headers must be sent before the
 * response body.
 *
 * <p>Where possible, set the Content-Length header (with the
 * {@link javax.servlet.ServletResponse#setContentLength} method),
 * to allow the servlet container to use a persistent connection
 * to return its response to the client, improving performance.
 * The content length is automatically set if the entire response fits
 * inside the response buffer.
 *
 * <p>When using HTTP 1.1 chunked encoding (which means that the response
 * has a Transfer-Encoding header), do not set the Content-Length header.
 *
 * <p>This method does not need to be either safe or idempotent.
 * Operations requested through POST can have side effects for
 * which the user can be held accountable, for example,
 * updating stored data or buying items online.
 *
 * <p>If the HTTP POST request is incorrectly formatted,
 * <code>doPost</code> returns an HTTP "Bad Request" message.
 *
 *
 * @param req	an {@link HttpServletRequest} object that
 *			contains the request the client has made
 *			of the servlet
 *
 * @param resp	an {@link HttpServletResponse} object that
 *			contains the response the servlet sends
 *			to the client
 *
 * @exception IOException	if an input or output error is
 *				detected when the servlet handles
 *				the request
 *
 * @exception ServletException	if the request for the POST
 *					could not be handled
 *
 *
 * @see javax.servlet.ServletOutputStream
 * @see javax.servlet.ServletResponse#setContentType
 *
 *
 */

/*protected*/ void HttpServlet::doPost(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException)
{
 QString protocol = req->getProtocol();
 QString msg = tr("http.method_post_not_supported");
 if (protocol.endsWith("1.1"))
 {
  resp->sendError(HttpServletResponse::SC_METHOD_NOT_ALLOWED, msg);
 }
 else
 {
  resp->sendError(HttpServletResponse::SC_BAD_REQUEST, msg);
 }
}




/**
 * Called by the server (via the <code>service</code> method)
 * to allow a servlet to handle a PUT request.
 *
 * The PUT operation allows a client to
 * place a file on the server and is similar to
 * sending a file by FTP.
 *
 * <p>When overriding this method, leave intact
 * any content headers sent with the request (including
 * Content-Length, Content-Type, Content-Transfer-Encoding,
 * Content-Encoding, Content-Base, Content-Language, Content-Location,
 * Content-MD5, and Content-Range). If your method cannot
 * handle a content header, it must issue an error message
 * (HTTP 501 - Not Implemented) and discard the request.
 * For more information on HTTP 1.1, see RFC 2616
 * <a href="http://www.ietf.org/rfc/rfc2616.txt"></a>.
 *
 * <p>This method does not need to be either safe or idempotent.
 * Operations that <code>doPut</code> performs can have side
 * effects for which the user can be held accountable. When using
 * this method, it may be useful to save a copy of the
 * affected URL in temporary storage.
 *
 * <p>If the HTTP PUT request is incorrectly formatted,
 * <code>doPut</code> returns an HTTP "Bad Request" message.
 *
 *
 * @param req	the {@link HttpServletRequest} object that
 *			contains the request the client made of
 *			the servlet
 *
 * @param resp	the {@link HttpServletResponse} object that
 *			contains the response the servlet returns
 *			to the client
 *
 * @exception IOException	if an input or output error occurs
 *				while the servlet is handling the
 *				PUT request
 *
 * @exception ServletException	if the request for the PUT
 *					cannot be handled
 *
 */

/*protected*/ void HttpServlet::doPut(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException)
{
QString protocol = req->getProtocol();
QString msg = tr("http.method_put_not_supported");
if (protocol.endsWith("1.1")) {
 resp->sendError(HttpServletResponse::SC_METHOD_NOT_ALLOWED, msg);
} else {
 resp->sendError(HttpServletResponse::SC_BAD_REQUEST, msg);
}
}




/**
 *
 * Called by the server (via the <code>service</code> method)
 * to allow a servlet to handle a DELETE request.
 *
 * The DELETE operation allows a client to remove a document
 * or Web page from the server.
 *
 * <p>This method does not need to be either safe
 * or idempotent. Operations requested through
 * DELETE can have side effects for which users
 * can be held accountable. When using
 * this method, it may be useful to save a copy of the
 * affected URL in temporary storage.
 *
 * <p>If the HTTP DELETE request is incorrectly formatted,
 * <code>doDelete</code> returns an HTTP "Bad Request"
 * message.
 *
 *
 * @param req	the {@link HttpServletRequest} object that
 *			contains the request the client made of
 *			the servlet
 *
 *
 * @param resp	the {@link HttpServletResponse} object that
 *			contains the response the servlet returns
 *			to the client
 *
 *
 * @exception IOException	if an input or output error occurs
 *				while the servlet is handling the
 *				DELETE request
 *
 * @exception ServletException	if the request for the
 *					DELETE cannot be handled
 *
 */

/*protected*/ void HttpServlet::doDelete(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException)
{
 QString protocol = req->getProtocol();
 QString msg = tr("http.method_delete_not_supported");
 if (protocol.endsWith("1.1")) {
  resp->sendError(HttpServletResponse::SC_METHOD_NOT_ALLOWED, msg);
 } else {
  resp->sendError(HttpServletResponse::SC_BAD_REQUEST, msg);
 }
}





/*private*/ QList<QMetaMethod> HttpServlet::getAllDeclaredMethods(/*Class*/QString c)
{

 if (c ==("HttpServlet")) {
     return QList<QMetaMethod>();
 }
 QList<QMetaMethod> thisMethods = QList<QMetaMethod>();
 int iType = QMetaType::type(c.toLocal8Bit());
 QObject* o;
 if(iType != NULL)
 {
#if QT_VERSION < 0x050000
  o = (QObject*)QMetaType::construct(iType);
#else
  o = (QObject*)QMetaType::create(iType);
#endif
  if(o != NULL)
  {
   QList<QMetaMethod> parentMethods; //getAllDeclaredMethods(c.getSuperclass());
   for(int i = 0; i < o->metaObject()->superClass()->methodCount(); i++)
   {
    parentMethods.append(o->metaObject()->superClass()->method(i));
   }
    // Method[] thisMethods = c.getDeclaredMethods();
   for(int i=0; i < o->metaObject()->methodCount(); i++)
   {
    thisMethods.append(o->metaObject()->method(i));
   }

   if ((!parentMethods.isEmpty()) && (parentMethods.length() > 0))
   {
    QList<QMetaMethod> allMethods =
             QList<QMetaMethod>(/*parentMethods.length() + thisMethods.length()*/);
  //System.arraycopy(parentMethods, 0, allMethods, 0,
  //                         parentMethods.length);
    for(int i =0; i < parentMethods.count(); i++)
     allMethods.append(parentMethods.at(i));
  // System.arraycopy(thisMethods, 0, allMethods, parentMethods.length,
  //                         thisMethods.length);
    for(int i =0; i < parentMethods.count(); i++)
     allMethods.append(thisMethods.at(i));

     thisMethods = allMethods;
   }
  }
 }
 return thisMethods;
}






/**
 * Called by the server (via the <code>service</code> method)
 * to allow a servlet to handle a OPTIONS request.
 *
 * The OPTIONS request determines which HTTP methods
 * the server supports and
 * returns an appropriate header. For example, if a servlet
 * overrides <code>doGet</code>, this method returns the
 * following header:
 *
 * <p><code>Allow: GET, HEAD, TRACE, OPTIONS</code>
 *
 * <p>There's no need to override this method unless the
 * servlet implements new HTTP methods, beyond those
 * implemented by HTTP 1.1.
 *
 * @param req	the {@link HttpServletRequest} object that
 *			contains the request the client made of
 *			the servlet
 *
 *
 * @param resp	the {@link HttpServletResponse} object that
 *			contains the response the servlet returns
 *			to the client
 *
 *
 * @exception IOException	if an input or output error occurs
 *				while the servlet is handling the
 *				OPTIONS request
 *
 * @exception ServletException	if the request for the
 *					OPTIONS cannot be handled
 *
 */

/*protected*/ void HttpServlet::doOptions(HttpServletRequest* /*req*/, HttpServletResponse* resp)
throw (ServletException, IOException)
{
 QList<QMetaMethod> methods = getAllDeclaredMethods(this->metaObject()->className());

 bool ALLOW_GET = false;
 bool ALLOW_HEAD = false;
 bool ALLOW_POST = false;
 bool ALLOW_PUT = false;
 bool ALLOW_DELETE = false;
 bool ALLOW_TRACE = true;
 bool ALLOW_OPTIONS = true;

 for (int i=0; i<methods.length(); i++) {
     QMetaMethod m = methods.at(i);

     if (m.name()  == ("doGet")) {
  ALLOW_GET = true;
  ALLOW_HEAD = true;
     }
     if (m.name() == ("doPost"))
  ALLOW_POST = true;
     if (m.name() == ("doPut"))
  ALLOW_PUT = true;
     if (m.name() == ("doDelete"))
  ALLOW_DELETE = true;

 }

 QString allow = "";
 if (ALLOW_GET)
     if (allow== NULL) allow=METHOD_GET;
 if (ALLOW_HEAD)
     if (allow== NULL) allow=METHOD_HEAD;
     else allow += ", " + METHOD_HEAD;
 if (ALLOW_POST)
     if (allow== NULL) allow=METHOD_POST;
     else allow += ", " + METHOD_POST;
 if (ALLOW_PUT)
     if (allow== NULL) allow=METHOD_PUT;
     else allow += ", " + METHOD_PUT;
 if (ALLOW_DELETE)
     if (allow== NULL) allow=METHOD_DELETE;
     else allow += ", " + METHOD_DELETE;
 if (ALLOW_TRACE)
     if (allow== NULL) allow=METHOD_TRACE;
     else allow += ", " + METHOD_TRACE;
 if (ALLOW_OPTIONS)
     if (allow== NULL) allow=METHOD_OPTIONS;
     else allow += ", " + METHOD_OPTIONS;

 resp->setHeader("Allow", allow);
}




/**
 * Called by the server (via the <code>service</code> method)
 * to allow a servlet to handle a TRACE request.
 *
 * A TRACE returns the headers sent with the TRACE
 * request to the client, so that they can be used in
 * debugging. There's no need to override this method.
 *
 *
 *
 * @param req	the {@link HttpServletRequest} object that
 *			contains the request the client made of
 *			the servlet
 *
 *
 * @param resp	the {@link HttpServletResponse} object that
 *			contains the response the servlet returns
 *			to the client
 *
 *
 * @exception IOException	if an input or output error occurs
 *				while the servlet is handling the
 *				TRACE request
 *
 * @exception ServletException	if the request for the
 *					TRACE cannot be handled
 *
 */

/*protected*/ void HttpServlet::doTrace(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException)
{

 int responseLength;

 QString CRLF = "\r\n";
 QString responseString = "TRACE "+ req->getRequestURI()+
     " " + req->getProtocol();

 QStringListIterator reqHeaderEnum = req->getHeaderNames();

 while( reqHeaderEnum.hasNext() ) {
     QString headerName = reqHeaderEnum.next();
     responseString += CRLF + headerName + ": " +
  req->getHeader(headerName);
 }

 responseString += CRLF;

 responseLength = responseString.length();
#if 1
 resp->setContentType("message/http");
// resp->setContentLength(responseLength);
// ServletOutputStream* out = resp->getOutputStream(); //ServletOutputStream
// out->print(responseString);
// out->device()->close();
 resp->resp->write(responseString.toLocal8Bit(),true);
#endif
 return;
}





/**
 *
 * Receives standard HTTP requests from the public
 * <code>service</code> method and dispatches
 * them to the <code>do</code><i>XXX</i> methods defined in
 * this class. This method is an HTTP-specific version of the
 * {@link javax.servlet.Servlet#service} method. There's no
 * need to override this method.
 *
 *
 *
 * @param req	the {@link HttpServletRequest} object that
 *			contains the request the client made of
 *			the servlet
 *
 *
 * @param resp	the {@link HttpServletResponse} object that
 *			contains the response the servlet returns
 *			to the client
 *
 *
 * @exception IOException	if an input or output error occurs
 *				while the servlet is handling the
 *				HTTP request
 *
 * @exception ServletException	if the HTTP request
 *					cannot be handled
 *
 * @see 				javax.servlet.Servlet#service
 *
 */
#if 0
/*protected*/ void HttpServlet::service(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException)
{
 QString method = req->getMethod();

 if (method == (METHOD_GET)) {
     long lastModified = getLastModified(req);
     if (lastModified == -1) {
  // servlet doesn't support if-modified-since, no reason
  // to go through further expensive logic
  doGet(req, resp);
     } else {
  long ifModifiedSince = req->getDateHeader(HEADER_IFMODSINCE);
  if (ifModifiedSince < (lastModified / 1000 * 1000)) {
      // If the servlet mod time is later, call doGet()
                    // Round down to the nearest second for a proper compare
                    // A ifModifiedSince of -1 will always be less
      maybeSetLastModified(resp, lastModified);
      doGet(req, resp);
  } else {
      resp->setStatus(HttpServletResponse::SC_NOT_MODIFIED);
  }
     }

 } else if (method == (METHOD_HEAD)) {
     long lastModified = getLastModified(req);
     maybeSetLastModified(resp, lastModified);
     doHead(req, resp);

 } else if (method == (METHOD_POST)) {
     doPost(req, resp);

 } else if (method == (METHOD_PUT)) {
     doPut(req, resp);

 } else if (method == (METHOD_DELETE)) {
     doDelete(req, resp);

 } else if (method == (METHOD_OPTIONS)) {
     doOptions(req,resp);

 } else if (method == (METHOD_TRACE)) {
     doTrace(req,resp);

 } else {
     //
     // Note that this means NO servlet supports whatever
     // method was requested, anywhere on this server.
     //

     QString errMsg = ("http.method_not_implemented %1");
//     Object[] errArgs = new Object[1];
//     errArgs[0] = method;
     errMsg = errMsg.arg(/*errArgs*/method);

     resp->sendError(HttpServletResponse::SC_NOT_IMPLEMENTED, errMsg);
 }
    }

#endif



/*
 * Sets the Last-Modified entity header field, if it has not
 * already been set and if the value is meaningful.  Called before
 * doGet, to ensure that headers are set before response data is
 * written.  A subclass might have set this header already, so we
 * check.
 */

/*private*/ void HttpServlet::maybeSetLastModified(HttpServletResponse* resp, long lastModified) {
if (resp->containsHeader(HEADER_LASTMOD))
 return;
if (lastModified >= 0)
 resp->setDateHeader(HEADER_LASTMOD, lastModified);
}




/**
 *
 * Dispatches client requests to the protected
 * <code>service</code> method. There's no need to
 * override this method.
 *
 *
 * @param req	the {@link HttpServletRequest} object that
 *			contains the request the client made of
 *			the servlet
 *
 *
 * @param res	the {@link HttpServletResponse} object that
 *			contains the response the servlet returns
 *			to the client
 *
 *
 * @exception IOException	if an input or output error occurs
 *				while the servlet is handling the
 *				HTTP request
 *
 * @exception ServletException	if the HTTP request cannot
 *					be handled
 *
 *
 * @see javax.servlet.Servlet#service
 *
 */

/*public*/ void HttpServlet::service(ServletRequest* req, ServletResponse* res)
throw (ServletException, IOException)
{
 HttpServletRequest*	request;
 HttpServletResponse*	response;

 try
 {
  request = (HttpServletRequest*) req;
  response = (HttpServletResponse*) res;
 }
 catch (ClassCastException e)
 {
  throw new ServletException("non-HTTP request or response",NULL);
 }
#if 1
 service(request, response);
#endif
 }

/*protected*/ /*virtual*/ void HttpServlet::doList(HttpServletRequest* req, HttpServletResponse* resp)
throw (ServletException, IOException) {}



#if 0
/*
 * A response that includes no body, for use in (dumb) "HEAD" support.
 * This just swallows that body, counting the bytes in order to set
 * the content length appropriately.  All other methods delegate directly
 * to the HTTP Servlet Response object used to construct this one.
 */
// file /*private*/
//class NoBodyResponse implements HttpServletResponse
//{
//    /*private*/ HttpServletResponse		resp;
//    /*private*/ NoBodyOutputStream		noBody;
//    /*private*/ PrintWriter			writer;
//    /*private*/ bool			didSetContentLength;

//    // file /*private*/
   NoBodyResponse::NoBodyResponse(HttpServletResponse* r, HttpServlet* hs) {
    this->hs = hs;
resp = r;
#if 0
noBody = new NoBodyOutputStream();
#endif
   }

   // file /*private*/
   void NoBodyResponse::setContentLength()
   {
    if (!didSetContentLength)
    {
#if 0
  resp->setContentLength(noBody->getContentLength());
#endif
    }
   }


   // SERVLET RESPONSE interface methods

   /*public*/ void NoBodyResponse::setContentLength(int len) {
resp->setContentLength(len);
didSetContentLength = true;
   }

   /*public*/ void NoBodyResponse::setCharacterEncoding(QString charset)
     { resp->setCharacterEncoding(charset); }

   /*public*/ void NoBodyResponse::setContentType(QString type)
     { resp->setContentType(type); }

   /*public*/ QString NoBodyResponse::getContentType()
     { return resp->getContentType(); }

   /*public*/ ServletOutputStream* NoBodyResponse::getOutputStream() throw (IOException)
     { return /*noBody*/ NULL; }

   /*public*/ QString NoBodyResponse::getCharacterEncoding()
{ return resp->getCharacterEncoding(); }

   /*public*/ PrintWriter* NoBodyResponse::getWriter() throw ( IOException)
   {
if (writer ==  NULL)
{
    ServletOutputStream*	w;

    //w = new OutputStreamWriter(noBody, getCharacterEncoding());
#if 0 // TODO:

    w = noBody;
    w->setCodec(QTextCodec(resp->getCharacterEncoding()));
#endif
    writer = new PrintWriter(w);
}
return writer;
   }

   /*public*/ void NoBodyResponse::setBufferSize(int size) throw (IllegalStateException)
     { resp->setBufferSize(size); }

   /*public*/ int NoBodyResponse::getBufferSize()
     { return resp->getBufferSize(); }

   /*public*/ void NoBodyResponse::reset() throw (IllegalStateException)
     { resp->reset(); }

     /*public*/ void NoBodyResponse::resetBuffer() throw (IllegalStateException)
     { resp->resetBuffer(); }

   /*public*/ bool NoBodyResponse::isCommitted()
     { return resp->isCommitted(); }

   /*public*/ void NoBodyResponse::flushBuffer() throw (IOException)
     { resp->flushBuffer(); }

   /*public*/ void NoBodyResponse::setLocale(QLocale loc)
     { resp->setLocale(loc); }

   /*public*/ QLocale NoBodyResponse::getLocale()
     { return resp->getLocale(); }


   // HTTP SERVLET RESPONSE interface methods

   /*public*/ void NoBodyResponse::addCookie(stefanfrings::HttpCookie* cookie)
     { resp->addCookie(cookie); }

   /*public*/ bool NoBodyResponse::containsHeader(QString name)
     { return resp->containsHeader(name); }

   /** @deprecated */
   /*public*/ void NoBodyResponse::setStatus(int sc, QString sm)
     { resp->setStatus(sc, sm); }

   /*public*/ void NoBodyResponse::setStatus(int sc)
     { resp->setStatus(sc); }

   /*public*/ void NoBodyResponse::setHeader(QString name, QString value)
     { resp->setHeader(name, value); }

   /*public*/ void NoBodyResponse::setIntHeader(QString name, int value)
     { resp->setIntHeader(name, value); }

   /*public*/ void NoBodyResponse::setDateHeader(QString name, long date)
     { resp->setDateHeader(name, date); }

   /*public*/ void NoBodyResponse::sendError(int sc, QString msg) throw (IOException)
     { resp->sendError(sc, msg); }

   /*public*/ void NoBodyResponse::sendError(int sc) throw (IOException)
     { resp->sendError(sc); }

   /*public*/ void NoBodyResponse::sendRedirect(QString location) throw (IOException)
     { resp->sendRedirect(location); }

   /*public*/ QString NoBodyResponse::encodeURL(QString url)
     { return resp->encodeURL(url); }

   /*public*/ QString NoBodyResponse::encodeRedirectURL(QString url)
     { return resp->encodeRedirectURL(url); }

   /*public*/ void NoBodyResponse::addHeader(QString name, QString value)
     { resp->addHeader(name, value); }

   /*public*/ void NoBodyResponse::addDateHeader(QString name, long value)
     { resp->addDateHeader(name, value); }

   /*public*/ void NoBodyResponse::addIntHeader(QString name, int value)
     { resp->addIntHeader(name, value); }


   /**
    * @deprecated	As of Version 2.1, replaced by
    * 			{@link HttpServletResponse#encodeURL}.
    *
    */


   /*public*/ QString NoBodyResponse::encodeUrl(QString url)
     { return this->encodeURL(url); }

   /**
    * @deprecated	As of Version 2.1, replaced by
    *			{@link HttpServletResponse#encodeRedirectURL}.
    *
    */


   /*public*/ QString NoBodyResponse::encodeRedirectUrl(QString url)
     { return this->encodeRedirectURL(url); }
//};


/*
* Servlet output stream that gobbles up all its data.
*/

// file /*private*/
//class NoBodyOutputStream : public  /*ServletOutputStream*/ QTextStream{

//    /*private*/ static /*final*/ QString LSTRING_FILE =
// "javax.servlet.http.LocalStrings";
//    /*private*/ static ResourceBundle lStrings =
// ResourceBundle.getBundle(LSTRING_FILE);

//    /*private*/ int		contentLength = 0;

   // file /*private*/
   NoBodyOutputStream::NoBodyOutputStream() {}

   // file /*private*/
   int NoBodyOutputStream::getContentLength() {
return contentLength;
   }

   /*public*/ void NoBodyOutputStream::write(int b) {
contentLength++;
   }

/*public*/ void NoBodyOutputStream::write(QByteArray buf, int offset, int len)
throw (IOException)
{
 if (len >= 0)
 {
  contentLength += len;
 }
 else
 {
  // XXX
  // isn't this really an IllegalArgumentException?

  QString msg = tr("err.io.negativelength");
  throw new IOException("negative length");
 }
}
//};

#endif
