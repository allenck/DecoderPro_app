#ifndef OPTIONFRAME_H
#define OPTIONFRAME_H

#include "operationsframe.h"

namespace Operations
{
 class OptionFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  /*public*/ OptionFrame(QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 };
}
#endif // OPTIONFRAME_H
