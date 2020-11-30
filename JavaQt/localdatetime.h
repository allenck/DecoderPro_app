#ifndef LOCALDATETIME_H
#define LOCALDATETIME_H
#include <QDateTime>

class LocalDateTime : public QDateTime
{
 public:
  LocalDateTime();
  static LocalDateTime now();
};

#endif // LOCALDATETIME_H
