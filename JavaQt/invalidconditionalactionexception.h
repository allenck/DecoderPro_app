#ifndef INVALIDCONDITIONALACTIONEXCEPTION_H
#define INVALIDCONDITIONALACTIONEXCEPTION_H

#include "jmriexception.h"
#include <QMainWindow>

class InvalidConditionalActionException : public JmriException
{
 public:
  /*public*/ InvalidConditionalActionException(QString s, Throwable* t);
  /*public*/ InvalidConditionalActionException(QString s) ;
  /*public*/ InvalidConditionalActionException(Throwable* t);
  /*public*/ InvalidConditionalActionException();

};

#endif // INVALIDCONDITIONALACTIONEXCEPTION_H
