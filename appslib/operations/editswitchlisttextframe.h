#ifndef EDITSWITCHLISTTEXTFRAME_H
#define EDITSWITCHLISTTEXTFRAME_H

#include "operationsframe.h"
namespace Operations
{
 class EditSwitchListTextFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  EditSwitchListTextFrame(QWidget* parent = 0);
  /*public*/ void initComponents();

 };
}
#endif // EDITSWITCHLISTTEXTFRAME_H
