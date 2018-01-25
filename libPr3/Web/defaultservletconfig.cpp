#include "defaultservletconfig.h"

DefaultServletConfig::DefaultServletConfig()
{

}

DefaultServletConfig::DefaultServletConfig(QString servletName, HttpServletRequest* request)
{
 this->servletName = servletName;
 this->request = request;
 servletContext = (ServletContext*)(new DefaultServletContext(request));
 parameterNames = request->getParameterMap()->keys();
}

/*public*/ QString DefaultServletConfig::getServletName()
{
 return this->servletName;
}

/*public*/ ServletContext* DefaultServletConfig::getServletContext()
{
 return this->servletContext;
}

/*public*/ QString DefaultServletConfig::getInitParameter(QString string)
{
 return request->getParameter(string);
}
/*public*/ QStringListIterator DefaultServletConfig::getInitParameterNames()
{
 return QStringListIterator(parameterNames);
}
