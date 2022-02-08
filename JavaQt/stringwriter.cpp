#include "stringwriter.h"

StringWriter::StringWriter() : QByteArray()
{
}

/*public*/ QString StringWriter::toString()
{
 return QString::fromStdString(toStdString());
}
