#ifndef SERVLETUTIL_H
#define SERVLETUTIL_H

#include <QObject>
#include "httpservletresponse.h"
#include "file.h"
class ServletUtil : public QObject
{
 Q_OBJECT
public:
 explicit ServletUtil(QObject *parent = 0);
 ~ServletUtil() {}
 ServletUtil(const ServletUtil&) : QObject()  {}
 /*public*/ static /*final*/ QString UTF8;// = "UTF-8"; // NOI18N
 // media types
 /*public*/ static /*final*/ QString APPLICATION_JSON;// = "application/json"; // NOI18N
 /*public*/ static /*final*/ QString APPLICATION_XML;// = "application/xml"; // NOI18N
 /*public*/ static /*final*/ QString IMAGE_PNG;// = "image/png"; // NOI18N
 /*public*/ static /*final*/ QString TEXT_HTML;// = "text/html"; // NOI18N
 /*public*/ static /*final*/ QString UTF8_APPLICATION_JSON;// = APPLICATION_JSON + "; charset=utf-8"; // NOI18N
 /*public*/ static /*final*/ QString UTF8_APPLICATION_XML;// = APPLICATION_XML + "; charset=utf-8"; // NOI18N
 /*public*/ static /*final*/ QString UTF8_TEXT_HTML;// = TEXT_HTML + "; charset=utf-8"; // NOI18N
 /*public*/ QString getRailroadName(bool inComments);
 /*public*/ QString getFooter(QLocale locale, QString context) /*throw (IOException)*/;
 /*public*/ QString getNavBar(QLocale locale, QString context) /*throw (IOException)*/;
 /*public*/ static ServletUtil* getInstance();
 /*public*/ void setNonCachingHeaders(HttpServletResponse* response);
 /*public*/ void writeFile(HttpServletResponse* response, File* file, QString contentType) /*throw (IOException)*/;
 /*public*/ QString getTitle(QLocale locale, QString title);


signals:

public slots:
};
Q_DECLARE_METATYPE(ServletUtil)
#endif // SERVLETUTIL_H
