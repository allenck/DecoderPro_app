#ifndef JMRICONFIGUREXMLEXCEPTION_H
#define JMRICONFIGUREXMLEXCEPTION_H

#include "jmriexception.h"

class JmriConfigureXmlException : public JmriException
{
 public:
  /*public*/  JmriConfigureXmlException(QString s, Throwable* t);
  /*public*/  JmriConfigureXmlException(QString s);
  /*public*/  JmriConfigureXmlException(Exception* s);
  /*public*/  JmriConfigureXmlException();

};

#endif // JMRICONFIGUREXMLEXCEPTION_H
