#include "datetimeparseexception.h"

DateTimeParseException::DateTimeParseException(QString s, QString parseString)
{
    this->msg = s;
    this->parseString = parseString;
    name = "DateTimeParseException";
}
QString DateTimeParseException::getParsedString()
{
    return parseString;
}
