#include "resetcheckboxescarstableaction.h"
#include "carstablemodel.h"

//ResetCheckBoxesCarsTableAction::ResetCheckBoxesCarsTableAction()
//{

//}
namespace Operations
{
/**
 * Swing action to show checkboxes in the cars window.
 *
 * @author Bob Jacobsen Copyright (C) 2001
 * @author Daniel Boudreau Copyright (C) 2014
 * @version $Revision: 22219 $
 */
///*public*/ class RESETCHECKBOXESCARSTABLEACTION_H extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 7015631697067063039L;

 /*public*/ ResetCheckboxesCarsTableAction::ResetCheckboxesCarsTableAction(QString s, QObject* parent)
  : AbstractAction(s, parent)
 {
 //super(s);
 common();
 }

 /*public*/ ResetCheckboxesCarsTableAction::ResetCheckboxesCarsTableAction(CarsTableModel* carsTableModel, QObject* parent)
  : AbstractAction(tr("Reset CheckBoxes"), parent)
{
  //this(Bundle.getMessage("TitleResetCheckboxes"));
  common();
  _carsTableModel = carsTableModel;
 }
 void ResetCheckboxesCarsTableAction::common()
 {
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void ResetCheckboxesCarsTableAction::actionPerformed(ActionEvent* e)
 {
  _carsTableModel->resetCheckboxes();
 }
}
