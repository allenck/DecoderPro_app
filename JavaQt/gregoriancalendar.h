#ifndef GREGORIANCALENDAR_H
#define GREGORIANCALENDAR_H

#include "calendar.h"

class QTimeZone;
class QLocale;
class GregorianCalendar : public Calendar
{
public:
 /*public*/ GregorianCalendar();
 /*public*/ GregorianCalendar(QTimeZone zone, QLocale aLocale);

};

#endif // GREGORIANCALENDAR_H
