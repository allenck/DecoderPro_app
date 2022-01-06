#ifndef UNEXPECTEDEXCEPTIONCONTEXT_H
#define UNEXPECTEDEXCEPTIONCONTEXT_H

#include "exceptioncontext.h"

class UnexpectedExceptionContext : public ExceptionContext
{
  Q_OBJECT
 public:
  explicit UnexpectedExceptionContext(Exception* ex, QString operation, QObject* parent);
  /*public*/ QString getTitle();

};

#endif // UNEXPECTEDEXCEPTIONCONTEXT_H
