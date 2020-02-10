#include "hasconnectionbutunabletoconnectexception.h"

/**
 * An exception thrown then there is a configured connection, but JMRI is
 * unable to open that connection. For example, a LocoNet connection with a
 * LocoBufferUSB is configured but the LocoBufferUSB is not connected.
 */
//public class HasConnectionButUnableToConnectException extends InitializationException {

    /*public*/HasConnectionButUnableToConnectException:: HasConnectionButUnableToConnectException(QString message, QString localized)
      : InitializationException(message, localized, nullptr)
    {
      // super(message, localized)
    }

    /*public*/ HasConnectionButUnableToConnectException::HasConnectionButUnableToConnectException(QString message, QString localized, Throwable* cause)
      : InitializationException(message, localized, (Exception*)cause)
    {
        //super(message, localized, cause);
    }

    /*public*/ HasConnectionButUnableToConnectException::HasConnectionButUnableToConnectException(Throwable* cause)
      : InitializationException((Exception*)cause)
    {
        //super(cause);
    }
