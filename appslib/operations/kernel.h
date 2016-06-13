#ifndef KERNEL_H
#define KERNEL_H
#include "rollingstockgroup.h"
#include "appslib_global.h"

namespace Operations
{
 class Car;
 class APPSLIBSHARED_EXPORT Kernel : public RollingStockGroup
 {
  Q_OBJECT
 public:
  //explicit Kernel(QObject *parent = 0);
  /*public*/ Kernel(QString name,QObject *parent = 0);
  /*public*/ QList<Car*> getCars() ;
  /*public*/ void dispose();

 signals:

 public slots:

 private:
  Logger* log;
 };
}
#endif // KERNEL_H
