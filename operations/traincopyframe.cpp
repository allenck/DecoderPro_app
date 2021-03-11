#include "traincopyframe.h"
#include <QMessageBox>
#include "train.h"
#include <QBoxLayout>
#include "gridbaglayout.h"
#include "trainmanager.h"
#include "jtextfield.h"
#include <QPushButton>
#include <QComboBox>
#include "control.h"
#include <QGroupBox>
#include "flowlayout.h"
#include "vptr.h"
#include "traineditframe.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Frame for making a new copy of a train.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2011, 2013
  * @version $Revision: 17977 $
  */
 ///*public*/ class TrainCopyFrame extends OperationsFrame {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 4829987018175695904L;


 /*public*/ TrainCopyFrame::TrainCopyFrame(Train* train, QWidget* parent) : OperationsFrame(parent){
 log = new Logger("TrainCopyFrame");
 trainManager = ((TrainManager*)InstanceManager::getDefault("TrainManager"));

 // labels
 // text field
 trainNameTextField = new JTextField(Control::max_len_string_train_name);

 // major buttons
 copyButton = new QPushButton(tr("Copy"));

 // combo boxes
 trainBox = ((TrainManager*)InstanceManager::getDefault("TrainManager"))->getTrainComboBox();
     // general GUI config

     //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // Set up the panels
     // Layout the panel by rows
     // row 1
     JPanel* pName = new JPanel();
     pName->setLayout(new GridBagLayout());
     pName->setBorder(BorderFactory::createTitledBorder(tr("Name")));
     addItem(pName, trainNameTextField, 0, 0);

     // row 2
     JPanel* pCopy = new JPanel();
     pCopy->setLayout(new GridBagLayout());
     pCopy->setBorder(BorderFactory::createTitledBorder(tr("Select Train to Copy")));
     addItem(pCopy, trainBox, 0, 0);

     trainBox->setCurrentIndex(trainBox->findData(VPtr<Train>::asQVariant(train)));

     // row 4
     QWidget* pButton = new QWidget();
     pButton->setLayout(new FlowLayout);
     pButton->layout()->addWidget(copyButton);

     thisLayout->addWidget(pName);
     thisLayout->addWidget(pCopy);
     thisLayout->addWidget(pButton);

     // add help menu to window
     addHelpMenu("package.jmri.jmrit.operations.Operations_CopyTrain", true); // NOI18N

     adjustSize();
     setMinimumSize(QSize(Control::panelWidth400, Control::panelHeight200));

     setTitle(tr("TitleTrainCopy"));

     // setup buttons
     addButtonAction(copyButton);
 }

 /*public*/ void TrainCopyFrame::buttonActionPerformed(QWidget* ae) {
 QPushButton* source = (QPushButton*)ae;
     if (source == copyButton) {
         log->debug("copy train button activated");
         if (!checkName()) {
             return;
         }

         Train* newTrain = trainManager->getTrainByName(trainNameTextField->text());
         if (newTrain != NULL) {
             reportTrainExists();
             return;
         }
         if (trainBox->currentText() == NULL) {
             reportTrainDoesNotExist();
             return;
         }
         Train* oldTrain = (Train*) VPtr<Train>::asPtr(trainBox->currentData());
         if (oldTrain == NULL) {
             reportTrainDoesNotExist();
             return;
         }

         // now copy
         newTrain = trainManager->copyTrain(oldTrain, trainNameTextField->text());
         new TrainEditFrame(newTrain);
     }
 }

 /*private*/ void TrainCopyFrame::reportTrainExists() {
//     JOptionPane.showMessageDialog(this, tr("TrainNameExists"), MessageFormat.format(Bundle
//             .getMessage("CanNotTrain"), new Object[]{tr("copy")}), JOptionPane.ERROR_MESSAGE);
 QMessageBox::critical(this, tr("Can not %1 train!").arg(tr("copy")), tr("Train with this name already exists"));
}

 /*private*/ void TrainCopyFrame::reportTrainDoesNotExist() {
//     JOptionPane.showMessageDialog(this, tr("SelectTrain"), MessageFormat.format(Bundle
//             .getMessage("CanNotTrain"), new Object[]{tr("copy")}), JOptionPane.ERROR_MESSAGE);
 QMessageBox::critical(this, tr("Can not %1 train!").arg(tr("copy")), tr("Select Train to Copy"));
 }

 /**
  *
  * @return true if name isn't too long
  */
 /*private*/ bool TrainCopyFrame::checkName() {
     if (trainNameTextField->text().trimmed()==("")) {
//         JOptionPane.showMessageDialog(this, tr("EnterTrainName"), MessageFormat.format(Bundle
//                 .getMessage("CanNotTrain"), new Object[]{tr("copy")}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 train!").arg(tr("copy")), tr("Enter New Train Name"));
         return false;
     }
     if (trainNameTextField->text().length() > Control::max_len_string_train_name) {
//         JOptionPane.showMessageDialog(this, MessageFormat.format(tr("TrainNameLess"),
//                 new Object[]{Control.max_len_string_train_name + 1}), MessageFormat.format(Bundle
//                         .getMessage("CanNot"), new Object[]{tr("copy")}), JOptionPane.ERROR_MESSAGE);
      QMessageBox::critical(this, tr("Can not %1 train!").arg(tr("copy")), tr("Train name must be less than %1 characters").arg(Control::max_len_string_train_name + 1));
         return false;
     }
     return true;
 }

 /*public*/ void TrainCopyFrame::dispose() {
     OperationsFrame::dispose();
 }
/*public*/ QString TrainCopyFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.tools.TrainCopyFrame";
}

}
