#ifndef PRINTMOREOPTIONACTION_H
#define PRINTMOREOPTIONACTION_H
#include "abstractaction.h"
#include "printmoreoptionframe.h"
#include <QPointer>

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
  /*public*/ void actionPerformed(JActionEvent* e = 0);
private:
  void common();
  QPointer<PrintMoreOptionFrame> f;
 };
}
#endif // PRINTMOREOPTIONACTION_H
