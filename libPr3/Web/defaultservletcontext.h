#ifndef DEFAULTSERVLETCONTEXT_H
#define DEFAULTSERVLETCONTEXT_H
#include "servletcontext.h"
#include "httpservletrequest.h"

class DefaultServletContext : public ServletContext
{
public:
 DefaultServletContext();
 DefaultServletContext(HttpServletRequest* request);

private:
 QString path;
 HttpServletRequest* request;
};

#endif // DEFAULTSERVLETCONTEXT_H
