#ifndef SERVLET_H
#define SERVLET_H
#include <QObject>
#include "servletexception.h"
#include "servletrequest.h"
#include "servletresponse.h"
#include "servletconfig.h"

/*public*/ /*interface*/ class Servlet : public QObject{

    /*public*/ virtual void init(ServletConfig* /*sc*/) throw (ServletException) {}

    /*public*/ virtual ServletConfig* getServletConfig() {return NULL;}

    /*public*/ virtual void service(ServletRequest* /*sr*/, ServletResponse* /*sr1*/) throw (ServletException, IOException) {}

    /*public*/ QString getServletInfo();

    /*public*/ void destroy();
};
#endif // SERVLET_H
