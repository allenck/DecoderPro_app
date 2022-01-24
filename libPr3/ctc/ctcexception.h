#ifndef CTCEXCEPTION_H
#define CTCEXCEPTION_H
#include "exceptions.h"

class CTCException : public Exception
{
 public:
  /*public*/ CTCException(QString module, QString userIdentifier, QString parameter, QString reason);
  /*public*/ QString getExceptionString();// { return _mModule + ", " + _mUserIdentifier + _mParameter + ", " + _mReason; }
  /*public*/ void logError();// { String exceptionString = getExceptionString(); org.slf4j.LoggerFactory.getLogger(CTCException.class).error(exceptionString); InstanceManager.getDefault(CTCExceptionBuffer.class).logString(CTCExceptionBuffer.ExceptionBufferRecordSeverity.ERROR, exceptionString); }
  /*public*/ void logWarning();// { String exceptionString = getExceptionString(); org.slf4j.LoggerFactory.getLogger(CTCException.class).warn(exceptionString); InstanceManager.getDefault(CTCExceptionBuffer.class).logString(CTCExceptionBuffer.ExceptionBufferRecordSeverity.WARN, exceptionString); }
  static /*public*/ void logError(QString string);// { org.slf4j.LoggerFactory.getLogger(CTCException.class).error(string); InstanceManager.getDefault(CTCExceptionBuffer.class).logString(CTCExceptionBuffer.ExceptionBufferRecordSeverity.ERROR, string); }
  static /*public*/ void logWarning(QString string);// { org.slf4j.LoggerFactory.getLogger(CTCException.class).warn(string); InstanceManager.getDefault(CTCExceptionBuffer.class).logString(CTCExceptionBuffer.ExceptionBufferRecordSeverity.WARN, string); }
  static /*public*/ void logInfo(QString string);// { org.slf4j.LoggerFactory.getLogger(CTCException.class).info(string); InstanceManager.getDefault(CTCExceptionBuffer.class).logString(CTCExceptionBuffer.ExceptionBufferRecordSeverity.INFO, string); }

 private:
  /*private*/ /*final*/ QString _mModule;
  /*private*/ /*final*/ QString _mUserIdentifier;
  /*private*/ /*final*/ QString _mParameter;
  /*private*/ /*final*/ QString _mReason;

};

#endif // CTCEXCEPTION_H
