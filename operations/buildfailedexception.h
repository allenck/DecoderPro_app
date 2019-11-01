#ifndef BUILDFAILEDEXCEPTION_H
#define BUILDFAILEDEXCEPTION_H
#include "exceptions.h"

class BuildFailedException : public Exception
{
public:
 BuildFailedException();
 /*public*/ /*final*/ static QString NORMAL;// = "normal"; // NOI18N
 /*public*/ /*final*/ static QString STAGING;// = "staging"; // NOI18N

 /*public*/ BuildFailedException(QString s, QString type) ;
 /*public*/ BuildFailedException(QString s);
 /*public*/ BuildFailedException(Exception ex);
 /*public*/ QString getExceptionType();

  private:
  /*private*/ QString type;// = NORMAL;

};

#endif // BUILDFAILEDEXCEPTION_H
