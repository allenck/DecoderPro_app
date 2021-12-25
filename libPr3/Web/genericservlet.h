#ifndef GENERICSERVLET_H
#define GENERICSERVLET_H
#include "servlet.h"
#include "servletconfig.h"

class ServletConfig;
class GenericServlet : public Servlet
{
 Q_OBJECT
public:
 GenericServlet(QObject* parent = 0);
 /*public*/ virtual void destroy();
 /*public*/ virtual QString getInitParameter(QString name);
 /*public*/ virtual QStringListIterator getInitParameterNames();
 /*public*/ ServletConfig* getServletConfig()override;
 /*public*/ virtual ServletContext* getServletContext();
 /*public*/ virtual QString getServletInfo() ;
 /*public*/ void init(ServletConfig* config) /*throw (ServletException)*/override;
 /*public*/ virtual void log(QString msg) ;
 /*public*/ virtual void log(QString message, Throwable t);
 /*public*/ /*abstract*/virtual void service(ServletRequest* req, ServletResponse* res)
 /*throw (ServletException, IOException)*/override;
 /*public*/ virtual QString getServletName();

//public slots:
 /*public*/ virtual void init() /*throw (ServletException)*/;

private:
 /*private*/ /*transient*/ ServletConfig* config;
 /*private*/ static /*final*/ QString LSTRING_FILE;// = "javax.servlet.LocalStrings";

};

#endif // GENERICSERVLET_H
