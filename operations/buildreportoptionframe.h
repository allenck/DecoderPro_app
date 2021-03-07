#ifndef BUILDREPORTOPTIONFRAME_H
#define BUILDREPORTOPTIONFRAME_H

#include "operationsframe.h"
namespace Operations
{
 class BuildReportOptionFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  BuildReportOptionFrame(QWidget* parent = 0);
  /*public*/ void initComponents() override;
  /*public*/ QString getClassName() override;

 };
}
#endif // BUILDREPORTOPTIONFRAME_H
