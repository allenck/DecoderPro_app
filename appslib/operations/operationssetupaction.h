#ifndef OPERATIONSSETUPACTION_H
#define OPERATIONSSETUPACTION_H

#include "abstractaction.h"
#include "operationssetupframe.h"
#include "appslib_global.h"

 //class OperationsSetupFrame;
 class APPSLIBSHARED_EXPORT OperationsSetupAction : public AbstractAction
 {
  Q_OBJECT
 public:
  explicit OperationsSetupAction(QObject *parent = 0);
  /*public*/ OperationsSetupAction(QString s,QObject *parent = 0);

 signals:

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  static Operations::OperationsSetupFrame* f;// = null;
  void common();
 };
#endif // OPERATIONSSETUPACTION_H
