#include "trainsscheduleeditframe.h"
#include "control.h"
#include "jtextfield.h"
#include "gridbaglayout.h"
#include <QBoxLayout>
#include "jcombobox.h"
#include "jbutton.h"
#include "trainschedulemanager.h"
#include "logger.h"
#include "vptr.h"
#include "trainschedule.h"
#include "swingpropertychangesupport.h"
#include "propertychangeevent.h"
#include "instancemanager.h"


namespace Operations
{
 /**
  * Used to edit train timetable (Schedule).
  *
  * @author Daniel Boudreau Copyright (C)
  * @version $Revision: 23749 $
  *
  */
 ///*public*/ class TrainsScheduleEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -6005860633909479680L;



 /*public*/ TrainsScheduleEditFrame::TrainsScheduleEditFrame(QWidget* parent)
   : OperationsFrame(parent)
 {
     //super();
  setFrameRef(getClassName());
  log = new Logger("TrainsScheduleEditFrame");
  // text box
  addTextBox = new JTextField(Control::max_len_string_attibute);

  // major buttons
  addButton = new JButton(tr("Add"));
  deleteButton = new JButton(tr("Delete"));
  replaceButton = new JButton(tr("Replace"));

  restoreButton = new JButton(tr("Restore"));

  trainScheduleManager = ((TrainScheduleManager*)InstanceManager::getDefault("Operations::TrainScheduleManager"));     // the following code sets the frame's initial state

  //getContentPane().setLayout(new GridBagLayout());
  QBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  //trainScheduleManager.addPropertyChangeListener(this);
  connect(trainScheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  comboBox = trainScheduleManager->getComboBox();

  // row 1
  addItem(addTextBox, 2, 2);
  addItem(addButton, 3, 2);

  // row 3
  addItem(comboBox, 2, 3);
  addItem(deleteButton, 3, 3);

  // row 4
  addItem(replaceButton, 3, 4);

  // row 5
  addItem(restoreButton, 2, 5);

  addButtonAction(addButton);
  addButtonAction(deleteButton);
  addButtonAction(replaceButton);
  addButtonAction(restoreButton);

  setTitle(tr("MenuItemEditSchedule"));
  initMinimumSize(QSize(Control::panelWidth300, Control::panelHeight200));

 }

 /*public*/ void TrainsScheduleEditFrame::buttonActionPerformed(QWidget* ae) {
 JButton* source = (JButton*)ae;
     if (source == deleteButton && comboBox->currentText() != NULL) {
         trainScheduleManager->deregister((TrainSchedule*) VPtr<TrainSchedule>::asPtr(comboBox->currentData()));
     }
     if (source == restoreButton) {
         trainScheduleManager->createDefaultSchedules();
     }
     // check for valid name
     QString s = addTextBox->text();
     s = s.trimmed();
     if (s==("")) {
         return;	// done
     }
     if (source == addButton) {
         trainScheduleManager->newSchedule(s);
     }
     if (source == replaceButton && comboBox->currentText() != NULL) {
         TrainSchedule* ts = ((TrainSchedule*) VPtr<TrainSchedule>::asPtr(comboBox->currentData()));
         ts->setName(s);
     }
 }

 /*public*/ void TrainsScheduleEditFrame::dispose() {
     //trainScheduleManager.removePropertyChangeListener(this);
 disconnect(trainScheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }

 /*public*/ void TrainsScheduleEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     trainScheduleManager->updateComboBox(comboBox);
 }
/*public*/ QString TrainsScheduleEditFrame::getClassName()
{
 return "jmri.jmrit.operations.trains.schedules.TrainsScheduleEditFrame";
}

}
