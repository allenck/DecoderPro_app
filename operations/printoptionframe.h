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
  /*public*/ void initComponents() override;
  /*public*/ QString getClassName() override;

 };
}
#endif // PRINTOPTIONFRAME_H
