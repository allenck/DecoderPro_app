#ifndef RUNTIMEEXCEPTION_H
#define RUNTIMEEXCEPTION_H
#include "exceptions.h"

class RuntimeException : public Exception
{
public:
 RuntimeException();
 /*public*/ RuntimeException(QString message);

};

#endif // RUNTIMEEXCEPTION_H
