#ifndef OPERATIONSCONSIST_H
#define OPERATIONSCONSIST_H
#include "rollingstockgroup.h"
#include "appslib_global.h"


namespace Operations
{
 class Engine;
 class APPSLIBSHARED_EXPORT Consist : public RollingStockGroup
 {
  Q_OBJECT
 public:
  //explicit Consist(QObject *parent = 0);
  /*public*/ Consist(QString name, QObject *parent = 0);
  /*public*/ QList<Engine*> getEngines();
  /*public*/ int getConsistNumber();
  /*public*/ void setConsistNumber(int number) ;
  /*public*/ void dispose();

 signals:

 public slots:
 private:
   Logger * log;
 protected:
  /*protected*/ int _consistNumber;// = 0;

 };
}
#endif // OPERATIONSCONSIST_H
