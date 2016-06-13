#ifndef PRINTMOREOPTIONACTION_H
#define PRINTMOREOPTIONACTION_H
#include "abstractaction.h"

namespace Operations
{
 class PrintMoreOptionFrame;
 class PrintMoreOptionAction : public AbstractAction
 {
  Q_OBJECT
 public:
  PrintMoreOptionAction(QObject* parent);
 /*public*/ PrintMoreOptionAction(QString s,QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
private:
  void common();
  PrintMoreOptionFrame* f;
 };
}
#endif // PRINTMOREOPTIONACTION_H
