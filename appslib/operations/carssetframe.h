#ifndef CARSSETFRAME_H
#define CARSSETFRAME_H

#include "carsetframe.h"

class QSortFilterProxyModel;
namespace Operations
{
 class CarsTableModel;
 class CarsSetFrame : public CarSetFrame
 {
  Q_OBJECT
 public:
  CarsSetFrame(QWidget* parent = 0);
  /*public*/ void initComponents(JTable* carsTable);

 public slots:
  /*public*/ void buttonActionPerformed(QWidget* ae);

 private:
  bool toggle;// = true;
  CarsTableModel* _carsTableModel;
  JTable* _carsTable;
  QSortFilterProxyModel* _sorter;
  // Ignore checkbox states
  /*private*/ static bool ignoreStatusCheckBoxSelected;//= false;
  /*private*/ static bool ignoreLocationCheckBoxSelected;//= false;
  /*private*/ static bool ignoreRWECheckBoxSelected;//= false;
  /*private*/ static bool ignoreLoadCheckBoxSelected;//= false;
  /*private*/ static bool ignoreKernelCheckBoxSelected;//= false;
  /*private*/ static bool ignoreDestinationCheckBoxSelected;//= false;
  /*private*/ static bool ignoreFinalDestinationCheckBoxSelected;//= false;
  /*private*/ static bool ignoreTrainCheckBoxSelected;//= false;
  Logger* log;
 protected:
  /*protected*/ void ignoreAll(bool b);
  /*protected*/ bool save();

 };
}
#endif // CARSSETFRAME_H
