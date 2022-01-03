#ifndef OPTIONACTION_H
#define OPTIONACTION_H

#include "abstractaction.h"
#include "optionframe.h"
#include <QPointer>

namespace Operations
{
 class OptionFrame;
 class OptionAction : public AbstractAction
 {
 public:
  /*public*/ OptionAction(QObject* parent);
 public slots:
  /*public*/ void actionPerformed(JActionEvent* /*e*/);
 private:
  QPointer<OptionFrame> f;// = null;

 };
}
#endif // OPTIONACTION_H
