#ifndef METATYPES_H
#define METATYPES_H

#include <QObject>
namespace Operations {


 class Metatypes : public QObject
 {
   Q_OBJECT
  public:
   explicit Metatypes(QObject *parent = nullptr);
   static bool done;
  signals:

 };
}
#endif // METATYPES_H
