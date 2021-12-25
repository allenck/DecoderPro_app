#include "httpservletresponse.h"
#include "printwriter.h"

HttpServletResponse::HttpServletResponse(stefanfrings::HttpResponse* resp)
{
 this->resp = resp;
}

PrintWriter* HttpServletResponse::getWriter() /*throw (IOException)*/
{
// QTextStream* out = new QTextStream(resp->socket);
// PrintWriter* writer = new PrintWriter(out);
 return NULL;
}
void HttpServletResponse::setContentType(QString type)
{
 resp->setHeader("content-type", type.toLocal8Bit());
}

void HttpServletResponse::setContentLength(int)
{
 //resp->set
}
