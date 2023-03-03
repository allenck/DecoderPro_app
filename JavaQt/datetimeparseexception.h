#ifndef DATETIMEPARSEEXCEPTION_H
#define DATETIMEPARSEEXCEPTION_H
#include "exceptions.h"

class DateTimeParseException : public Exception
{
public:
    DateTimeParseException(QString msg, QString parseString);
    QString getParsedString();
    DateTimeParseException(const DateTimeParseException&) : Exception() {}

private:
    QString parseString;
};

#endif // DATETIMEPARSEEXCEPTION_H
