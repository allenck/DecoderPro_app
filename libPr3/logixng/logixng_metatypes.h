#ifndef LOGIXNG_METATYPES_H
#define LOGIXNG_METATYPES_H

#include <QObject>

class LogixNG_Metatypes : public QObject
{
  Q_OBJECT
 public:
  explicit LogixNG_Metatypes(QObject *parent = nullptr);
  static bool ng_done;// = false;
 signals:


};

#endif // LOGIXNG_METATYPES_H
