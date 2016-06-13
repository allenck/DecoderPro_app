#ifndef OPTIONACTION_H
#define OPTIONACTION_H

#include "abstractaction.h"
namespace Operations
{
 class OptionFrame;
 class OptionAction : public AbstractAction
 {
 public:
  /*public*/ OptionAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e);
 private:
  OptionFrame* f;// = null;

 };
}
#endif // OPTIONACTION_H
