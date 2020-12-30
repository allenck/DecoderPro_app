#ifndef SHOWCHECKBOXESCARSTABLEACTION_H
#define SHOWCHECKBOXESCARSTABLEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

class JActionEvent;
namespace Operations
{
 class CarsTableModel;
 class APPSLIBSHARED_EXPORT ShowCheckboxesCarsTableAction : public AbstractAction
 {
  Q_OBJECT

 public:
  /*public*/ ShowCheckboxesCarsTableAction(CarsTableModel* carsTableModel, QObject* parent);
  /*public*/ ShowCheckboxesCarsTableAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
  private:
  CarsTableModel* _carsTableModel;
  void common();
 };
}
#endif // SHOWCHECKBOXESCARSTABLEACTION_H
