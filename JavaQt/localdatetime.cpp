#include "localdatetime.h"

LocalDateTime::LocalDateTime()
{

}

LocalDateTime* LocalDateTime::now()
{
 LocalDateTime* ldt = new LocalDateTime();
 ldt->msec = QDateTime::currentMSecsSinceEpoch();
}

/*public*/ bool LocalDateTime::isAfter(LocalDateTime* t)
{
 if(t->msec > msec)
  return true;
 return false;
}

/*public*/ LocalDateTime* LocalDateTime::plus(quint64 intvl, LocalDateTime::ChronoUnit)
{
 LocalDateTime* ldt = new LocalDateTime();
 ldt->msec = this->msec + intvl;
 return ldt;
}

/*public*/ QString LocalDateTime::toString()
{
 QDateTime dt = QDateTime::fromMSecsSinceEpoch(msec);
 return dt.toString();
}

/*public*/ quint64 LocalDateTime::until(LocalDateTime* ldt, ChronoUnit)
{
 return ldt->msec;
}
