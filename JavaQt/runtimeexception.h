#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H
#include "exceptions.h"

class RuntimeException : public Exception
{
public:
 RuntimeException();
 /*public*/ RuntimeException(QString message);
 /*public*/ RuntimeException(QString string, Throwable* thrwbl) ;
 /*public*/ RuntimeException(Throwable* thrwbl) ;
};

#endif // RUNTIMEEXCEPTION_H
