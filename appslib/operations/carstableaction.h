#ifndef CARSTABLEACTION_H
#define CARSTABLEACTION_H

#include "abstractaction.h"
#include "appslib_global.h"

namespace Operations
{
 class APPSLIBSHARED_EXPORT CarsTableAction : public AbstractAction
 {
  public:
  /*public*/ CarsTableAction(QString s, QObject* parent);
  /*public*/ CarsTableAction(QObject* parent);


 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
 private:
  void common();
 };
}
#endif // CARSTABLEACTION_H
