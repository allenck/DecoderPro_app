#include "libpr3version.h"
#include "build_number.h"

libPr3Version::libPr3Version(QObject *parent) :
    QObject(parent)
{
}
QString libPr3Version::buildVersion()
{ return QString("1.0.%1 %2 %3:%4:%5").arg(VER_BUILDNR).arg(VER_DATE).arg(VER_HOUR).arg(VER_MINUTE).arg(VER_SECOND);}
