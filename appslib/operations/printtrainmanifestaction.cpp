#include "printtrainmanifestaction.h"
#include "traineditframe.h"
#include "train.h"
#include <QMessageBox>

namespace Operations
{
 /**
  * Action to print a train's manifest
  *
  * @author Daniel Boudreau Copyright (C) 2010
  * @version $Revision: 28746 $
  */
 ///*public*/ class PrintTrainManifestAction extends AbstractAction {

 /**
  *
  */
 //private static final long serialVersionUID = -8792964051342675135L;

 /*public*/ PrintTrainManifestAction::PrintTrainManifestAction(QString actionName, bool preview, JFrame* frame)
     : AbstractAction(actionName, frame)
 {
  //super(actionName);
  isPreview = preview;
  this->frame = frame;
  connect(this, SIGNAL(triggered(bool)), this, SLOT(actionPerformed()));
 }


 /*public*/ void PrintTrainManifestAction::actionPerformed(ActionEvent* e) {
     TrainEditFrame* f = (TrainEditFrame*) frame;
     Train* train = f->_train;
     if (train == NULL) {
         return;
     }
     if (!train->isBuilt()) {
         QString printOrPreview = tr("print");
         if (isPreview) {
             printOrPreview = tr("preview");
         }
         QString string = tr("Do you want to %1 the previous manifest for Train (%2)?").arg(
                 printOrPreview).arg(train->getName());
//         int results = JOptionPane.showConfirmDialog(NULL, string, MessageFormat.format(
//                 tr("PrintPreviousManifest"), new Object[]{printOrPreview}),
//                 JOptionPane.YES_NO_OPTION);
         int results = QMessageBox::question(NULL, tr("%1 previous manifest?").arg(printOrPreview), string, QMessageBox::Yes | QMessageBox::No);
         if (results != QMessageBox::Yes) {
             return;
         }
     }
     if (!train->printManifest(isPreview)) {
         QString string = tr("Need to build train (%1) before printing!").arg(
                 train->getName());
//         JOptionPane.showMessageDialog(null, string, MessageFormat.format(
//                 tr("CanNotPrintManifest"), new Object[]{tr("print")}),
//                 JOptionPane.ERROR_MESSAGE);
         QMessageBox::critical(NULL, tr("Can not %1 manifest").arg(tr("print")), string);
         return;
     }
 }
}
