#ifndef OPERATIONSSETUPFRAME_H
#define OPERATIONSSETUPFRAME_H
#include "operationsframe.h"
#include "appslib_global.h"

namespace Operations {
 class APPSLIBSHARED_EXPORT OperationsSetupFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  //explicit OperationsSetupFrame(QWidget *parent = 0);
 /*public*/ OperationsSetupFrame(QWidget *parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 signals:

 public slots:

 };
}
#endif // OPERATIONSSETUPFRAME_H
