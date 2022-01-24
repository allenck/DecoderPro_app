#ifndef UNCHECKEDIOEXCEPTION_H
#define UNCHECKEDIOEXCEPTION_H

#include "runtimeexception.h"

class UncheckedIOException : public RuntimeException
{
 public:
  UncheckedIOException();
  UncheckedIOException(QString msg);
  UncheckedIOException(Throwable* e);

};

#endif // UNCHECKEDIOEXCEPTION_H
