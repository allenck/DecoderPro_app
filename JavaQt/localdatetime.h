#ifndef LOCALDATETIME_H
#define LOCALDATETIME_H
#include <QDateTime>

class LocalDateTime : public QDateTime
{
 public:
  LocalDateTime();
  static LocalDateTime now();
  /*public*/ bool isAfter(LocalDateTime );
};

#endif // LOCALDATETIME_H
