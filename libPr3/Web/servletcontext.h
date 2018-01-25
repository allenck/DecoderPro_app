#ifndef SERVLETCONTEXT_H
#define SERVLETCONTEXT_H
#include <QObject>
#include <QSet>
#include "exceptions.h"

/*public*/ /*interface*/ class ServletContext {

public:
    /*public*/ static /*final*/ QString TEMPDIR;// = "javax.servlet.context.tempdir";
    /*public*/ static /*final*/ QString ORDERED_LIBS;// = "javax.servlet.context.orderedLibs";

    /*public*/ virtual  QString getContextPath() {return "";}

 /**
      * Returns a <code>ServletContext</code> object that
      * corresponds to a specified URL on the server.
      *
      * <p>This method allows servlets to gain
      * access to the context for various parts of the server, and as
      * needed obtain {@link RequestDispatcher} objects from the context.
      * The given path must be begin with "/", is interpreted relative
      * to the server's document root and is matched against the context roots of
      * other web applications hosted on this container.
      *
      * <p>In a security conscious environment, the servlet container may
      * return <code>null</code> for a given URL.
      *
      * @param uripath a <code>String</code> specifying the context path of
      * another web application in the container.
      * @return the <code>ServletContext</code> object that
      * corresponds to the named URL, or null if either none exists or the
      * container wishes to restrict this access.
      *
      * @see RequestDispatcher
      */
      /*public*/ virtual  ServletContext* getContext(QString /*string*/) {return NULL;}

    /*public*/ virtual  int getMajorVersion() {return 0;}

    /*public*/ virtual  int getMinorVersion(){return 0;}

    /*public*/ virtual  int getEffectiveMajorVersion(){return 0;}

    /*public*/ virtual  int getEffectiveMinorVersion(){return 0;}

    /*public*/ virtual  QString getMimeType(QString /*string*/) {return "";}

    /*public*/ virtual  QSet<QString> getResourcePaths(QString /*string*/) {return QSet<QString>();}
#if 0
    /*public*/ virtual  URL getResource(QString string) throw (MalformedURLException);

    /*public*/ virtual  InputStream getResourceAsStream(String string);

    /*public*/ virtual  RequestDispatcher getRequestDispatcher(String string);

    /*public*/ virtual  RequestDispatcher getNamedDispatcher(String string);

    /*public*/ virtual  Servlet getServlet(String string) throws ServletException;

    /*public*/ virtual  Enumeration<Servlet> getServlets();

    /*public*/ virtual  Enumeration<String> getServletNames();
#endif
    /*public*/ virtual  void log(QString /*string*/) {}

    /*public*/ virtual  void log(Exception /*excptn*/, QString /*string*/) {}

    /*public*/ virtual  void log(QString /*string*/, Throwable /*thrwbl*/) {}

    /*public*/ virtual  QString getRealPath(QString /*string*/) {return "";}

    /*public*/ virtual  QString getServerInfo() {return "";}

 /*public*/ virtual  QString getInitParameter(QString string) {return "";}
#if 0
    /*public*/ virtual  Enumeration<String> getInitParameterNames();

    /*public*/ virtual  boolean setInitParameter(String string, String string1);

    /*public*/ virtual  Object getAttribute(String string);

    /*public*/ virtual  Enumeration<String> getAttributeNames();

    /*public*/ virtual  void setAttribute(String string, Object o);

    /*public*/ virtual  void removeAttribute(String string);

    /*public*/ virtual  String getServletContextName();

    /*public*/ virtual  ServletRegistration.Dynamic addServlet(String string, String string1);

    /*public*/ virtual  ServletRegistration.Dynamic addServlet(String string, Servlet srvlt);

    /*public*/ virtual  ServletRegistration.Dynamic addServlet(String string, Class<? extends Servlet> type);

    /*public*/ virtual  <T extends Servlet> T createServlet(Class<T> type) throws ServletException;

    /*public*/ virtual  ServletRegistration getServletRegistration(String string);

    /*public*/ virtual  Map<String, ? extends ServletRegistration> getServletRegistrations();

    /*public*/ virtual  FilterRegistration.Dynamic addFilter(String string, String string1);

    /*public*/ virtual  FilterRegistration.Dynamic addFilter(String string, Filter filter);

    /*public*/ virtual  FilterRegistration.Dynamic addFilter(String string, Class<? extends Filter> type);

    /*public*/ virtual  <T extends Filter> T createFilter(Class<T> type) throws ServletException;

    /*public*/ virtual  FilterRegistration getFilterRegistration(String string);

    /*public*/ virtual  Map<String, ? extends FilterRegistration> getFilterRegistrations();

    /*public*/ virtual  SessionCookieConfig getSessionCookieConfig();

    /*public*/ virtual  void setSessionTrackingModes(Set<SessionTrackingMode> set);

    /*public*/ virtual  Set<SessionTrackingMode> getDefaultSessionTrackingModes();

    /*public*/ virtual  Set<SessionTrackingMode> getEffectiveSessionTrackingModes();

    /*public*/ virtual  void addListener(String string);

    /*public*/ virtual  <T extends EventListener> void addListener(T t);

    /*public*/ virtual  void addListener(Class<? extends EventListener> type);

    /*public*/ virtual  <T extends EventListener> T createListener(Class<T> type) throws ServletException;

    /*public*/ virtual  JspConfigDescriptor getJspConfigDescriptor();

    /*public*/ virtual  ClassLoader getClassLoader();

    /*public*/ virtual  void declareRoles(String[] strings);

    /*public*/ virtual  String getVirtualServerName();
#endif
 friend class GenericServlet;
 friend class RosterServlet;
};
#endif // SERVLETCONTEXT_H
