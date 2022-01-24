#ifndef LOCALDATETIME_H
#define LOCALDATETIME_H
#include <QDateTime>
#include <QObject>

class LocalDateTime : public QObject
{
 public:
  enum ChronoUnit
  {
   NONE,
   MILLIS
  };
  LocalDateTime();
  static LocalDateTime* now();
  /*public*/ bool isAfter(LocalDateTime * );
  /*public*/ LocalDateTime* plus(quint64 intvl, ChronoUnit);
  /*public*/ QString toString();
  /*public*/ quint64 until(LocalDateTime*, ChronoUnit);
 private:
  quint64 msec;
};

#endif // LOCALDATETIME_H
