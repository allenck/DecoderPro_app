#ifndef EDITCARTYPEACTION_H
#define EDITCARTYPEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

namespace Operations
{
 class CarAttributeEditFrame;
 class APPSLIBSHARED_EXPORT EditCarTypeAction : public AbstractAction
 {
  Q_OBJECT
 public:
  EditCarTypeAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  CarAttributeEditFrame* f;// = null;

 };
}
#endif // EDITCARTYPEACTION_H
