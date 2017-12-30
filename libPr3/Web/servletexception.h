#ifndef SERVLETEXCEPTION_H
#define SERVLETEXCEPTION_H
#include "exceptions.h"

class Throwable;
class ServletException : public Exception
{
public:
 ServletException();
 ///*public*/ ServletException(QString message);
 /*public*/ ServletException(QString message = "", Throwable* rootCause = 0);
// /*public*/ ServletException(Throwable rootCause);
 /*public*/ Throwable* getRootCause();

private:
 /*private*/ Throwable* rootCause;

};

#endif // SERVLETEXCEPTION_H
