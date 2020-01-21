#ifndef YARDMASTERBYTRACKFRAME_H
#define YARDMASTERBYTRACKFRAME_H
#include "operationsframe.h"
#include "location.h"
namespace Operations
{
 class YardmasterByTrackFrame : public OperationsFrame
 {
  Q_OBJECT
 public:
  YardmasterByTrackFrame(Location* location, QWidget* parent = nullptr);
  /*public*/ QString getClassName();

 private:
  /*private*/ void initComponents(Location* location);

 };
}
#endif // YARDMASTERBYTRACKFRAME_H
