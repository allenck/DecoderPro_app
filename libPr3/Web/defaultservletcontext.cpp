#include "defaultservletcontext.h"

DefaultServletContext::DefaultServletContext()
{

}

DefaultServletContext::DefaultServletContext( HttpServletRequest* request) : ServletContext()
{
 this->request = request;
 this->path = request->req->getPath();
}
/*public*/ ServletContext* getContext(QString uripath)
{

}
