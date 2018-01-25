#ifndef DEFAULTSERVLETCONFIG_H
#define DEFAULTSERVLETCONFIG_H
#include "servletconfig.h"
#include "httpservletrequest.h"
#include "defaultservletcontext.h"

class DefaultServletConfig : public ServletConfig
{
public:
 DefaultServletConfig();
 DefaultServletConfig(QString servletName, HttpServletRequest* request);
 /*public*/ QString getServletName();
 /*public*/ ServletContext* getServletContext();
 /*public*/ QString getInitParameter(QString string);
 /*public*/ QStringListIterator getInitParameterNames();

private:
 QString servletName;
 QStringList parameterNames;
 HttpServletRequest* request;
 ServletContext* servletContext;
};

#endif // DEFAULTSERVLETCONFIG_H
