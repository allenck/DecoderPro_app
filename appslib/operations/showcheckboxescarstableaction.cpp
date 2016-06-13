#include "showcheckboxescarstableaction.h"
#include "carstablemodel.h"

//ShowCheckBoxesCarsTableAction::ShowCheckBoxesCarsTableAction()
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
///*public*/ class ShowCheckboxesCarsTableAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = 7015631697067063039L;

 /*public*/ ShowCheckboxesCarsTableAction::ShowCheckboxesCarsTableAction(QString s, QObject* parent)
  : AbstractAction(s, parent)
 {
 //super(s);
 common();
 }

 /*public*/ ShowCheckboxesCarsTableAction::ShowCheckboxesCarsTableAction(CarsTableModel* carsTableModel, QObject* parent)
  : AbstractAction(tr("Show CheckBoxes"), parent)
{
  //this(Bundle.getMessage("TitleShowCheckboxes"));
  common();
 _carsTableModel = carsTableModel;
 }
 void ShowCheckboxesCarsTableAction::common()
 {
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }

 /*public*/ void ShowCheckboxesCarsTableAction::actionPerformed(ActionEvent* e)
 {
  _carsTableModel->toggleSelectVisible();
 }
}
