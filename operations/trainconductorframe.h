#ifndef TRAINCONDUCTORFRAME_H
#define TRAINCONDUCTORFRAME_H

#include "operationsframe.h"

namespace Operations
{
 class Train;
 class TrainConductorFrame : public OperationsFrame
 {
 public:
  TrainConductorFrame(Train* train, QWidget* parent = 0);
  /*public*/ QString getClassName();

 private:
  /*private*/ void initComponents(Train* train);

 };
}
#endif // TRAINCONDUCTORFRAME_H
