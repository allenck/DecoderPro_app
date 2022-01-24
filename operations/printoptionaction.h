#ifndef PRINTOPTIONACTION_H
#define PRINTOPTIONACTION_H

#include "abstractaction.h"
#include "printoptionframe.h"
#include <QPointer>

namespace Operations
{
 class PrintOptionFrame;
 class PrintOptionAction : public AbstractAction
 {
  Q_OBJECT
 public:
  PrintOptionAction(QObject* parent);
  /*public*/ PrintOptionAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* e = 0);

 private:
  QPointer<PrintOptionFrame> f;// = null;

 };
}
#endif // PRINTOPTIONACTION_H
