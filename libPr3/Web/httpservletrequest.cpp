#include "httpservletrequest.h"
#include "../QtWebApp//QtWebApp/httpserver/httprequest.h"

/*public*/ /*static*/ /*final*/ QString HttpServletRequest::BASIC_AUTH = "BASIC";
/*public*/ /*static*/ /*final*/ QString HttpServletRequest::FORM_AUTH = "FORM";
/*public*/ /*static*/ /*final*/ QString HttpServletRequest::CLIENT_CERT_AUTH = "CLIENT_CERT";
/*public*/ /*static*/ /*final*/ QString HttpServletRequest::DIGEST_AUTH = "DIGEST";

HttpServletRequest::HttpServletRequest() : ServletRequest () {}
HttpServletRequest::HttpServletRequest(stefanfrings::HttpRequest* req) : ServletRequest() {this->req = req;}

/********************************************************************/
/*public*/ QString HttpServletRequest::getContentType()
{
 return req->getHeader("content-type");
}

QMap<QString,QStringList*>* HttpServletRequest::getParameterMap()
{
 QMultiMap<QByteArray,QByteArray> map =  req->getParameterMap();
 QMap<QString, QStringList*>* out = new QMap<QString, QStringList*>();
 QMapIterator<QByteArray,QByteArray> iter(map);
 while(iter.hasNext())
 {
  iter.next();
  QByteArray key = iter.key();
  QByteArray value = iter.value();
  if(out->contains(QString(key)))
  {
   out->value(QString(key))->append(QString(value));
  }
  else
  {
   QStringList* l = new QStringList();
   *l << QString(iter.value());

   out->insert(QString(iter.key()), l);
  }
 }
 return out;
}
QString HttpServletRequest::getParameter(QString p)
{
 return QString(req->getParameter(p.toLocal8Bit()));
}
QLocale HttpServletRequest::getLocale()
{
return QLocale();
}
