#ifndef PRINTMOREOPTIONFRAME_H
#define PRINTMOREOPTIONFRAME_H
#include "operationsframe.h"

namespace Operations
{
 class PrintMoreOptionFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  PrintMoreOptionFrame(QWidget* parent = 0);
  /*public*/ void initComponents();
  /*public*/ QString getClassName();

 };
}
#endif // PRINTMOREOPTIONFRAME_H
