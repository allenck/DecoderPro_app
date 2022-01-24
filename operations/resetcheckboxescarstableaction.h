#ifndef RESETCHECKBOXESCARSTABLEACTION_H
#define RESETCHECKBOXESCARSTABLEACTION_H
#include "abstractaction.h"
#include "appslib_global.h"

class JActionEvent;
namespace Operations
{
 class CarsTableModel;
 class APPSLIBSHARED_EXPORT ResetCheckboxesCarsTableAction : public AbstractAction
 {
  Q_OBJECT

 public:
  /*public*/ ResetCheckboxesCarsTableAction(CarsTableModel* carsTableModel, QObject* parent);
  /*public*/ ResetCheckboxesCarsTableAction(QString s, QObject* parent);
 public slots:
  /*public*/ void actionPerformed(ActionEvent* e = 0);
  private:
  CarsTableModel* _carsTableModel;
  void common();
 };
}
#endif // RESETCHECKBOXESCARSTABLEACTION_H
