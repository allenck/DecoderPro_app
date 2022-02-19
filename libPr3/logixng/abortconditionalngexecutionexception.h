#ifndef ABORTCONDITIONALNGEXECUTIONEXCEPTION_H
#define ABORTCONDITIONALNGEXECUTIONEXCEPTION_H
#include "jmriexception.h"

class AbortConditionalNGExecutionException : public JmriException
{
 public:
  AbortConditionalNGExecutionException();
  /*public*/ AbortConditionalNGExecutionException(QString msg);
  /*public*/ AbortConditionalNGExecutionException(Exception *e);
};

#endif // ABORTCONDITIONALNGEXECUTIONEXCEPTION_H
