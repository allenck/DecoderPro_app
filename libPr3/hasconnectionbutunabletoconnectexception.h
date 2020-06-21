#ifndef HASCONNECTIONBUTUNABLETOCONNECTEXCEPTION_H
#define HASCONNECTIONBUTUNABLETOCONNECTEXCEPTION_H
#include "exceptions.h"

class HasConnectionButUnableToConnectException : public InitializationException
{
// Q_OBJECT
// Q_INTERFACES(InitializationException)
public:
 HasConnectionButUnableToConnectException(QString message, QString localized);
 /*public*/ HasConnectionButUnableToConnectException(QString message, QString localized, Throwable *cause);
 /*public*/ HasConnectionButUnableToConnectException(Throwable* cause);

};

#endif // HASCONNECTIONBUTUNABLETOCONNECTEXCEPTION_H
