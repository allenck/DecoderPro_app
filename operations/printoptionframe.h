#ifndef PRINTOPTIONFRAME_H
#define PRINTOPTIONFRAME_H

#include "operationsframe.h"

namespace Operations
{
 class PrintOptionFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  PrintOptionFrame(QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 };
}
#endif // PRINTOPTIONFRAME_H
