#ifndef ABORTCONDITIONALNGEXECUTIONEXCEPTION_H
#define ABORTCONDITIONALNGEXECUTIONEXCEPTION_H
#include "exceptions.h"

class AbortConditionalNGExecutionException : public JmriException
{
 public:
  AbortConditionalNGExecutionException();
  /*public*/ AbortConditionalNGExecutionException(QString msg);
  /*public*/ AbortConditionalNGExecutionException(Exception e);
};

#endif // ABORTCONDITIONALNGEXECUTIONEXCEPTION_H
