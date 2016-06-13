#ifndef CARSSETFRAMEACTION_H
#define CARSSETFRAMEACTION_H

#include "abstractaction.h"
class JTable;
namespace Operations
{
 class CarsTableModel;
 class CarsSetFrameAction : public AbstractAction
 {
  Q_OBJECT
 public:
  CarsSetFrameAction(QString s, QObject* parent);
  /*public*/ CarsSetFrameAction(JTable* carsTable, QObject* parent);

 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);

 private:
  CarsTableModel* _carsTableModel;
  JTable* _carsTable;

 };
}
#endif // CARSSETFRAMEACTION_H
