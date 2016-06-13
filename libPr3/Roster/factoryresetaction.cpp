#include "factoryresetaction.h"
#include "ui_factoryresetaction.h"
#include "resettablemodel.h"
#include "../LayoutEditor/inputdialog.h"


/**
 * Action to create a dialog so that the user can select a factory reset
 * to execute.  The user can cancel this dialog skipping any resets
 *
 * @author    Howard G. Penny    Copyright (C) 2005
 * @version   $Revision: 17977 $
 */
// /*public*/ class FactoryResetAction extends AbstractAction {


/*public*/ FactoryResetAction::FactoryResetAction(QString actionName, ResetTableModel* rpModel, QWidget* parent)
    : QAction(actionName, parent)
{
 //super(actionName);
 rModel = rpModel;
 mParent = parent ;
 log = new Logger("FactoryResetAction");
 connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));
}

/*public*/ void FactoryResetAction::actionPerformed(ActionEvent* e)
{
 log->debug("start to display Factory Reset");
 //Object[] options;
 //options = new String[rModel.getRowCount()];
 QStringList options;
 for (int i=0; i<rModel->rowCount(QModelIndex()); i++)
 {
  options.append(rModel->data(rModel->index(i,0),Qt::DisplayRole).toString());
 }
//    String s = (String)JOptionPane.showInputDialog(
//                        mParent,
//                        "Factory Reset"+(options.length>1?"s":""),
//                        "Caution: Factory Reset",
//                        JOptionPane.WARNING_MESSAGE,
//                        null,
//                        options,
//                        null);
 QComboBox* optionsBox = new QComboBox();
 optionsBox->addItems(options);
 InputDialog* dlg = new InputDialog(tr("Factory Reset")+(options.length()>1?"s":""),optionsBox,tr("Caution: Factory Reset"),mParent);
 if(dlg->exec() == QDialog::Rejected)
  return;
 QString s = dlg->value();\

 //If a string was returned, a reset has been requested.
 if ((s != "") && (s.length() > 0))
 {
  int i = 0;
  while (options.at(i) != (s)) i++;
  rModel->performReset(i);
  return;
 }
}

