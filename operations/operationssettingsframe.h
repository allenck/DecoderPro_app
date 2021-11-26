#ifndef OPERATIONSSETTINGSFRAME_H
#define OPERATIONSSETTINGSFRAME_H
#include "operationsframe.h"

namespace Operations
{

 class OperationsSettingsFrame : public OperationsFrame
 {
   Q_OBJECT
  public:
   OperationsSettingsFrame(QWidget* parent = nullptr);
   /*public*/ void initComponents() override;
   /*public*/ QString getClassName() override {return "jmri.jmrit.operations.setup.OperationsSettingsFrame";}
 };
}
#endif // OPERATIONSSETTINGSFRAME_H
