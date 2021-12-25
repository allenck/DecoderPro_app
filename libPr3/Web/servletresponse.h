#ifndef SERVLETRESPONSE_H
#define SERVLETRESPONSE_H
#include "exceptions.h"
#include"printwriter.h"
#include <QObject>
#include "servletoutputstream.h"

/*public*/ /*interface*/class ServletResponse : public QObject
{
 Q_OBJECT
public:
 ServletResponse() : QObject() {}
    /*public*/ virtual  QString getCharacterEncoding() {return "";}

    /*public*/ virtual  QString getContentType() {return "";}

    /*public*/ virtual  ServletOutputStream* getOutputStream() /*throw (IOException)*/ {return NULL;}

    /*public*/ virtual  PrintWriter* getWriter() /*throw (IOException)*/ {return NULL;}

    /*public*/ virtual  void setCharacterEncoding(QString /*string*/) {}

    /*public*/ virtual  void setContentLength(int /*i*/) {}

    /*public*/ virtual  void setContentLengthLong(long /*l*/) {}

    /*public*/ virtual  void setContentType(QString /*string*/) {}

    /*public*/ virtual  void setBufferSize(int /*i*/) {}

    /*public*/ virtual  int getBufferSize() {return 0;}

    /*public*/ virtual  void flushBuffer() /*throw (IOException)*/ {}

    /*public*/ virtual  void resetBuffer() {}

    /*public*/ virtual  bool isCommitted() {return false;}

    /*public*/ virtual  void reset() {}

    /*public*/ virtual  void setLocale(QLocale /*locale*/) {}

    /*public*/virtual  QLocale getLocale() {return QLocale();}
};

#endif // SERVLETRESPONSE_H
