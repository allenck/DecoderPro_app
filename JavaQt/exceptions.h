#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <QObject>
#include <QString>
#include <QException>
#include "javaqt_global.h"
#include <QLocale>

class JAVAQTSHARED_EXPORT Throwable : public QException
{
 //Q_OBJECT
public:
 void raise() const { throw *this; }
   Throwable *clone() const { return new Throwable(*this); }

    Throwable(QString msg, QString localMsg, Throwable* cause)
    {
     this->msg = msg;
     this->localMsg = localMsg;
     this->cause = cause;
     this->name = "Throwable";
    }

    Throwable(QString msg, QString localMsg)
    {
     this->msg = msg;
     this->localMsg = localMsg;
     this->cause = NULL;
     this->name = "Throwable";
    }

    Throwable(QString msg, Throwable* cause)
    {
     this->msg = msg;
     this->localMsg = "";
     this->cause = cause;
    this->name = "Throwable";
    }
    Throwable(QString msg)
    {
     this->msg = msg;
     this->localMsg = "";
     this->cause = cause;
    this->name = "Throwable";
    }


    Throwable(Throwable* cause)
    {
     this->cause = cause;
     this->msg = cause->msg;
     this->localMsg = cause->getLocalizedMessage();
    this->name = "Throwable";
    }
    Throwable()
    {
     this->cause = NULL;
     this->msg = "";
     this->localMsg = "";
     this->name = "Throwable";
    }
    ~Throwable() throw(){}
    QString msg;
    QString localMsg;
    QString name;
    virtual QString getMessage() {return msg;}
    virtual QString getLocalizedMessage() {return localMsg;}
    virtual QString toString() {
     QString str = QString("exception %1: %2").arg(this->name).arg(msg);
     return str;
    }
    Throwable* cause;
};
class Exception : public Throwable
{
public:
 Exception() : Throwable() {}
 Exception(QString msg) : Throwable(msg) {}
 Exception(QString msg, Throwable* throwable) : Throwable(msg, throwable) {}
 Exception(QString msg, QString localMsg) : Throwable(msg, localMsg) {}
 Exception(QString msg, QString localMsg, Exception* exception) : Throwable(msg, localMsg, exception)
 {}
 Exception(Exception* exception) : Throwable(exception) {}
};

;
class JAVAQTSHARED_EXPORT EOFException : public Exception
{
public:
    EOFException(QString msg = "");
};

// base class for all following exceptions:
class JAVAQTSHARED_EXPORT IOException : public Exception
{
public:
    IOException(QString msg = "");
    ~IOException() throw()
    {
     name="IOException";
    }
QString getMessage();
    QString msg;
};
class JAVAQTSHARED_EXPORT IIOException : public Exception
{
public:
    IIOException(QString msg = "");
    ~IIOException() throw()
    {}
QString getMessage();
    QString msg;
};

class JAVAQTSHARED_EXPORT LocoNetMessageException : public Exception
{
public:
    LocoNetMessageException();
    ~LocoNetMessageException() throw() {}
};

class JAVAQTSHARED_EXPORT NoSuchElementException : public Exception
{
public:
    NoSuchElementException(QString s = "");
    ~NoSuchElementException() throw() {}

};

class JAVAQTSHARED_EXPORT UnsupportedCommOperationException : public Exception
{
public:
    UnsupportedCommOperationException(QString s = "");
    ~UnsupportedCommOperationException() throw() {}
};
class JAVAQTSHARED_EXPORT PortInUseException : public Exception
{
public:
    PortInUseException(QString s="");
    ~PortInUseException() throw() {}
};
class JAVAQTSHARED_EXPORT NoSuchPortException : public Exception
{
public:
    NoSuchPortException(QString s="");
    ~NoSuchPortException() throw() {}
};
class JAVAQTSHARED_EXPORT InterruptedException : public Exception
{
 public:
    InterruptedException();
    ~InterruptedException() throw() {}
};
class JAVAQTSHARED_EXPORT JmriException : public Exception
{
public:
    ~JmriException() throw() {}
    JmriException(QString s);
    JmriException(Exception ex) : Exception(ex) {}
    QString toString();
};
class JAVAQTSHARED_EXPORT LocoNetException : public JmriException
{
    //Q_OBJECT
public:
    /*explicit*/ LocoNetException( QString m=""/*, QObject *parent = 0*/);
    QString getText();
    ~LocoNetException() throw()
    {}
signals:

public slots:
private:
 QString text;

};
class JAVAQTSHARED_EXPORT IllegalArgumentException : public Exception
{
 public:
    IllegalArgumentException(QString s="");
    ~IllegalArgumentException() throw()
    {
     name="IllegalArgumentException";
    }
};
class JAVAQTSHARED_EXPORT NumberFormatException : public Exception
{
 public:
    NumberFormatException(QString s ="");
    ~NumberFormatException() throw() {}
};
class JAVAQTSHARED_EXPORT ProgrammerException : public Exception
{
 public:
    ProgrammerException(QString s ="");
    ~ProgrammerException() throw() {}
};
class JAVAQTSHARED_EXPORT TimebaseRateException : public Exception
{
 public:
    TimebaseRateException(QString s ="");
    ~TimebaseRateException() throw() {}
};

class JAVAQTSHARED_EXPORT UnsupportedOperationException : public Exception
{
 public:
    UnsupportedOperationException(QString s ="");
    ~UnsupportedOperationException() throw() {}
};
class JAVAQTSHARED_EXPORT NullPointerException : public Exception
{
 public:
    NullPointerException(QString s ="");
    ~NullPointerException() throw() {}
};
class JAVAQTSHARED_EXPORT TurnoutOperatorException : public Exception
{
 public:
    TurnoutOperatorException(QString s ="");
    ~TurnoutOperatorException() throw() {}
};
class JAVAQTSHARED_EXPORT JmriConfigureXmlException : public JmriException
{
 public:
    JmriConfigureXmlException(QString s ="");
    ~JmriConfigureXmlException() throw() {}
};
class JAVAQTSHARED_EXPORT DataConversionException : public Exception
{
 public:
    DataConversionException(QString s ="");
    ~DataConversionException() throw() {}
};
//class JAVAQTSHARED_EXPORT Throwable : public Exception
//{
// public:
//    Throwable(QString s ="");
//    ~Throwable() throw() {}
//};
class JAVAQTSHARED_EXPORT JDOMException : public Exception
{
 public:
    JDOMException(QString s = "");
    ~JDOMException() throw() {}
};
class JAVAQTSHARED_EXPORT FileNotFoundException : public Exception
{
 public:
    FileNotFoundException(QString s = "");
    ~FileNotFoundException() throw() {}
};
class JAVAQTSHARED_EXPORT ParseException : public Exception
{
 public:
    ParseException(QString s = "");
    ~ParseException() throw() {}
};
class JAVAQTSHARED_EXPORT ClassNotFoundException : public Exception
{
 public:
    ClassNotFoundException(QString s = "");
    ~ClassNotFoundException() throw() {}
};
class JAVAQTSHARED_EXPORT NoClassDefFoundError : public Exception
{
 public:
    NoClassDefFoundError(QString s = "");
    ~NoClassDefFoundError() throw() {}
};
class JAVAQTSHARED_EXPORT IllegalAccessException : public Exception
{
 public:
    IllegalAccessException(QString s = "");
    ~IllegalAccessException() throw() {}
};
class JAVAQTSHARED_EXPORT InstantiationException : public Exception
{
 public:
    InstantiationException(QString s = "");
    ~InstantiationException() throw() {}
};
class JAVAQTSHARED_EXPORT MalformedURLException : public Exception
{
 public:
    MalformedURLException(QString s = "");
    ~MalformedURLException() throw() {}
};
class JAVAQTSHARED_EXPORT IndexOutOfBoundsException : public Exception
{
 public:
    IndexOutOfBoundsException(QString s = "");
    ~IndexOutOfBoundsException() throw() {}
};
class JAVAQTSHARED_EXPORT MissingResourceException : public Exception
{
 public:
    MissingResourceException(QString s = "");
    ~MissingResourceException() throw() {}
};
class JAVAQTSHARED_EXPORT IllegalStateException : public Exception
{
 public:
    IllegalStateException(QString s = "");
    ~IllegalStateException() throw() {}
};
class JAVAQTSHARED_EXPORT ArrayIndexOutOfBoundsException : public Exception
{
 public:
    ArrayIndexOutOfBoundsException(QString s = "");
    ~ArrayIndexOutOfBoundsException() throw() {}
};
class JAVAQTSHARED_EXPORT EmptyStackException : public Exception
{
 public:
    EmptyStackException(QString s = "");
    ~EmptyStackException() throw() {}
};
class JAVAQTSHARED_EXPORT Error : public Exception
{
 public:
    Error(QString s = "");
    ~Error() throw() {}
};
class JAVAQTSHARED_EXPORT CloneNotSupportedException : public Exception
{
 public:
    CloneNotSupportedException(QString s = "");
    ~CloneNotSupportedException() throw() {}
};
class JAVAQTSHARED_EXPORT NegativeArraySizeException : public Exception
{
 public:
    NegativeArraySizeException(QString s = "");
    ~NegativeArraySizeException() throw() {}
};
class JAVAQTSHARED_EXPORT UnsupportedFlavorException : public Exception
{
 public:
    UnsupportedFlavorException(QString s = "");
    ~UnsupportedFlavorException() throw() {}
};
class JAVAQTSHARED_EXPORT MimeTypeParseException : public Exception
{
 public:
    MimeTypeParseException(QString s = "");
    ~MimeTypeParseException() throw() {}
};
class JAVAQTSHARED_EXPORT InvalidDnDOperationException : public Exception
{
public:
   InvalidDnDOperationException(QString s = "");
   ~InvalidDnDOperationException() throw() {}

};
class JAVAQTSHARED_EXPORT HeadlessException : public Exception
{
public:
   HeadlessException(QString s = "");
   ~HeadlessException() throw() {}

};
class JAVAQTSHARED_EXPORT TooManyListenersException : public Exception
{
public:
   TooManyListenersException(QString s = "");
   ~TooManyListenersException() throw() {}

};
class JAVAQTSHARED_EXPORT PrinterException : public Exception
{
public:
   PrinterException(QString s = "");
   ~PrinterException() throw() {}

};
class JAVAQTSHARED_EXPORT AudioException : public Exception
{
public:
   AudioException(QString s = "");
   ~AudioException() throw() {}

};

class JAVAQTSHARED_EXPORT InitializationException : public Exception
{
 //Q_OBJECT
public:
 void raise() const { throw *this; }
 InitializationException *clone() const { return new InitializationException(*this); }

 InitializationException(QString msg, QString localMsg) : Exception(msg, localMsg) {}
 InitializationException(QString msg, QString localMsg, Exception* ex =0) : Exception(msg, localMsg, ex) {}
 InitializationException(Exception* cause) : Exception(cause)
 {
  //super(cause);
  this->localMsg = cause->getLocalizedMessage();
 }

 ~InitializationException() throw() {}
};
class JAVAQTSHARED_EXPORT SAXException : public Exception
{
public:
   SAXException(QString s = "");
   ~SAXException() throw() {}
};
class JAVAQTSHARED_EXPORT UnsatisfiedLinkError : public Exception
{
public:
   UnsatisfiedLinkError(QString s = "");
   ~UnsatisfiedLinkError() throw() {}
};
class JAVAQTSHARED_EXPORT BackingStoreException : public Exception
{
public:
   BackingStoreException(QString s = "");
   ~BackingStoreException() throw() {}
};
class JAVAQTSHARED_EXPORT NoSuchMethodException : public Exception
{
public:
   NoSuchMethodException(QString s = "");
   ~NoSuchMethodException() throw() {}
};
class JAVAQTSHARED_EXPORT InvocationTargetException : public Exception
{
public:
   InvocationTargetException(QString s = "");
   ~InvocationTargetException() throw() {}
};
class JAVAQTSHARED_EXPORT TransformerFactoryConfigurationError : public Exception
{
public:
   TransformerFactoryConfigurationError(QString s = "");
   ~TransformerFactoryConfigurationError() throw() {}
};


#endif // EXCEPTIONS_H
