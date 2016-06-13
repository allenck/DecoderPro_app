#include "printtrainbuildreportaction.h"
#include "jframe.h"
#include "traineditframe.h"
#include "train.h"
#include <QMessageBox>

namespace Operations
{
 /**
  * Action to print a train's build report
  *
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 ///*/*public*/*/ class PrintTrainBuildReportAction extends AbstractAction {

 /**
  *
  */
// private static final long serialVersionUID = -888513883438800079L;

 /*public*/ PrintTrainBuildReportAction::PrintTrainBuildReportAction(QString actionName, bool preview, JFrame* frame)
    : AbstractAction(actionName, frame)
{
     //super(actionName);
     isPreview = preview;
     this->frame = frame;
     connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintTrainBuildReportAction::actionPerformed(ActionEvent* e) {
     TrainEditFrame* f = (TrainEditFrame*) frame;
     Train* train = f->_train;
     if (train == NULL) {
         return;
     }
     if (!train->isBuilt())
     {
         QString printOrPreview = tr("print");
         if (isPreview) {
             printOrPreview = tr("preview");
         }
         QString string = tr("Do you want to %1} the previous build report for Train (%2)?").arg(
                 printOrPreview).arg(train->getName());
//         int results = JOptionPane.showConfirmDialog(null, string, MessageFormat.format(
//                 tr("PrintPreviousBuildReport"), new Object[]{printOrPreview}),
//                 JOptionPane.YES_NO_OPTION);
         int results = QMessageBox::question(NULL, tr("%1 previous build report?").arg(printOrPreview), string,QMessageBox::Yes | QMessageBox::No);
         if (results != QMessageBox::Yes) {
             return;
         }
     }
     if (!train->printBuildReport(isPreview)) {
         QString string = tr("Need to build train (%1) before printing!").arg(
                 train->getName());
//         JOptionPane.showMessageDialog(null, string, tr("CanNotPrintBuildReport"),
//                 JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(NULL, tr("Can not print build report!"), string);
         return;
     }
 }

}
