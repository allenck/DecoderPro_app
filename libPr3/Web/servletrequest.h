#ifndef SERVLETREQUEST_H
#define SERVLETREQUEST_H
#include <QObject>
#include <QTextStream>
#include "exceptions.h"
#include "servletresponse.h"
#include <QStringListIterator>
#include <QStringList>
#include <QString>

class UnsupportedEncodingException : Exception
{
 UnsupportedEncodingException() : Exception() {}
 ~UnsupportedEncodingException () throw() {}
 UnsupportedEncodingException(QString msg) : Exception(msg) {}
};

class DispatcherType;
class ServletContext;
class AsyncContext;
class RequestDispatcher;
/*public*/ /*interface*/class ServletRequest  : public QObject
{
 Q_OBJECT
public:
    ServletRequest();

    /*public*/ virtual QVariant getAttribute(QString /*string*/) {return QVariant();}

    /*public*/ virtual QStringListIterator getAttributeNames() { QStringList l; return QStringListIterator(l);}
    /*public*/ virtual QString getCharacterEncoding() { return "";}

    /*public*/ virtual void setCharacterEncoding(QString /*string*/) throw (UnsupportedEncodingException) {}

    /*public*/ virtual int getContentLength() {return 0;}

    /*public*/ virtual long getContentLengthLong() {return 0;}

    /*public*/ virtual QString getContentType() { return "";}

    /*public*/ virtual QTextStream* getInputStream() /*throw (IOException)*/ {return NULL;}

    /*public*/ virtual QString getParameter(QString /*string*/) { return "";}

    /*public*/ virtual QStringListIterator getParameterNames() { QStringList l; return QStringListIterator(l);}

    /*public*/ virtual QStringList getParameterValues(QString /*string*/) {return QStringList();}

    /*public*/ virtual QMap<QString, QStringList*>* getParameterMap() {return  NULL;}

    /*public*/ virtual QString getProtocol() { return "";}

    /*public*/ virtual QString getScheme() { return "";}

    /*public*/ virtual QString getServerName() { return "";}

    /*public*/ virtual int getServerPort() {return 0;}

    /*public*/ virtual QTextStream* getReader() /*throw (IOException)*/ {return NULL;}

    /*public*/ virtual QString getRemoteAddr() { return "";}

    /*public*/ virtual QString getRemoteHost() { return "";}

    /*public*/ virtual void setAttribute(QString /*string*/, QVariant /*o*/) {}

    /*public*/ virtual void removeAttribute(QString /*string*/) {}

    /*public*/ virtual QLocale getLocale() {return QLocale();}

    /*public*/ virtual QListIterator<QLocale> getLocales() { QList<QLocale> l; return QListIterator<QLocale>(l);}

    /*public*/ virtual bool isSecure() {return false;}

    /*public*/ virtual RequestDispatcher* getRequestDispatcher(QString /*string*/) {return NULL;}

    /*public*/ virtual QString getRealPath(QString /*string*/) { return "";}

    /*public*/ virtual int getRemotePort() {return 0;}

    /*public*/ virtual QString getLocalName() { return "";}

    /*public*/ virtual QString getLocalAddr() { return "";}

    /*public*/ virtual int getLocalPort() {return 0;}

    /*public*/ virtual ServletContext* getServletContext() {return NULL;}

    /*public*/ virtual AsyncContext* startAsync() throw (IllegalStateException) {return NULL;}

    /*public*/ virtual AsyncContext* startAsync(ServletRequest* /*sr*/, ServletResponse* /*sr1*/) throw (IllegalStateException) {return NULL;}

    /*public*/ virtual bool isAsyncStarted() {return false;}

    /*public*/ virtual bool isAsyncSupported() {return false;}

    /*public*/ virtual AsyncContext* getAsyncContext() {return NULL;}

    /*public*/ virtual DispatcherType* getDispatcherType() {return NULL;}


 friend class HttpServlet;
 friend class RosterServlet;
};
#endif // SERVLETREQUEST_H
