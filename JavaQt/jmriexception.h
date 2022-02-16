#ifndef JMRIEXCEPTION_H
#define JMRIEXCEPTION_H
#include "exceptions.h"

class JmriException : public Exception
{
 public:
    /*public*/  JmriException(QString s, Throwable* t);
    /*public*/  JmriException(QString s);
    /*public*/  JmriException(Throwable* t) ;
    /*public*/  JmriException() ;
    /*public*/  JmriException(QString s, QList<QString> errors);
    /*public*/  JmriException(QString s, QList<QString> errors, Throwable* t);
    /*public*/  QList<QString> getErrors();
    /*public*/  QString getMessage()override;
    /*public*/  QString getLocalizedMessage()override;
 private:
  /*private*/ /*final*/ QList<QString> errors;

};

#endif // JMRIEXCEPTION_H
