#include "schedulecopyframe.h"
#include "schedulemanager.h"
#include "schedule.h"
#include "jtextfield.h"
#include <qpushbutton.h>
#include <QBoxLayout>
#include <QGroupBox>
#include <gridbaglayout.h>
#include "propertychangeevent.h"
#include "logger.h"
#include <QMessageBox>
#include "control.h"
#include "jcombobox.h"
#include "vptr.h"
#include "propertychangesupport.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Frame for copying a schedule for operations.
  *
  * @author Bob Jacobsen Copyright (C) 2001
  * @author Daniel Boudreau Copyright (C) 2015
  * @version $Revision: 17977 $
  */
 ///*public*/ class ScheduleCopyFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 5798102907541807915L;


 /*public*/ ScheduleCopyFrame::ScheduleCopyFrame(QWidget* parent)
    : OperationsFrame(parent)
 {
  //this(null);
  common(NULL);
 }

 /*public*/ ScheduleCopyFrame::ScheduleCopyFrame(Schedule* schedule, QWidget* parent)
  : OperationsFrame(tr("Copy Schedule"), parent)
 {
  //super(Bundle.getMessage("MenuItemCopySchedule"));
  common(schedule);
 }

 void ScheduleCopyFrame::common(Schedule* schedule)
 {
  log = new Logger("ScheduleCopyFrame");
  scheduleManager = ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"));

  // text field
  scheduleNameTextField = new JTextField(Control::max_len_string_location_name);

  // major buttons
  QPushButton* copyButton = new QPushButton(tr("Copy"));

  // combo boxes
  JComboBox* scheduleBox = scheduleManager->getComboBox();// general GUI config

  //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
  QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());

  // Set up the panels
  // Layout the panel by rows
  // row 1
  JPanel* pName = new JPanel();
  pName->setLayout(new GridBagLayout());
  pName->setBorder(BorderFactory::createTitledBorder(tr("Schedule Name")));
  addItem(pName, scheduleNameTextField, 0, 0);

  // row 2
  JPanel* pCopy = new JPanel();
  pCopy->setLayout(new GridBagLayout());
  //pCopy.setBorder(BorderFactory.createTitledBorder(tr("Select Schedule To Copy")));
  addItem(pCopy, scheduleBox, 0, 0);

  // row 4
  QWidget* pButton = new QWidget();
  pButton->setLayout(new GridBagLayout());
  addItem(pButton, copyButton, 0, 0);

  thisLayout->addWidget (pName);
  thisLayout->addWidget (pCopy);
  thisLayout->addWidget (pButton);

  // get notified if combo box gets modified
  //scheduleManager.addPropertyChangeListener(this);
  connect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  // add help menu to window
  addHelpMenu("package.jmri.jmrit.operations.Operations_Schedules", true); // NOI18N

  // setup buttons
  addButtonAction(copyButton);

  scheduleBox->setCurrentIndex(scheduleBox->findText(schedule->toString()));

  initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight250));
}

/*protected*/ void ScheduleCopyFrame::buttonActionPerformed(QWidget* ae) {
  QPushButton * source = (QPushButton*)ae;
  if (source == copyButton) {
      log->debug("copy Schedule button activated");
      if (!checkName()) {
          return;
      }

      if (scheduleBox->currentText() == NULL) {
//          JOptionPane.showMessageDialog(this, Bundle.getMessage("SelectScheduleToCopy"), MessageFormat.format(Bundle
//                  .getMessage("CanNotSchedule"), new Object[]{Bundle.getMessage("Copy")}), JOptionPane.ERROR_MESSAGE);
       QMessageBox::critical(this, tr("Can not %1 schedule!").arg(tr("Copy")), tr("Select Schedule to Copy"));
          return;
      }

      Schedule* schedule = (Schedule*) VPtr<Schedule>::asPtr(scheduleBox->currentData());
      scheduleManager->copySchedule(schedule, scheduleNameTextField->text());
  }
}

/*protected*/ void ScheduleCopyFrame::updateComboBoxes() {
  log->debug("update Schedule combobox");
  QVariant item = scheduleBox->currentData(); // remember which object was selected
  scheduleManager->updateComboBox(scheduleBox);
  scheduleBox->setCurrentIndex(scheduleBox->findData(item));
}

/**
*
* @return true if name entered and isn't too long
*/
/*protected*/ bool ScheduleCopyFrame::checkName() {
  if (scheduleNameTextField->text().trimmed()==("")) {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("MustEnterName"), MessageFormat.format(Bundle
//              .getMessage("CanNotSchedule"), new Object[]{Bundle.getMessage("Copy")}), JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Can not %1 schedule!").arg(tr("Copy")), tr("Enter a name"));
      return false;
  }
  if (scheduleNameTextField->text().length() > Control::max_len_string_location_name) {
//      JOptionPane.showMessageDialog(this, MessageFormat.format(Bundle.getMessage("ScheduleNameLengthMax"),
//              new Object[]{Integer.toString(Control.max_len_string_location_name + 1)}), MessageFormat.format(Bundle
//                      .getMessage("CanNotSchedule"), new Object[]{Bundle.getMessage("Copy")}), JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Can not %1 schedule!").arg(tr("Copy")), tr("Schedule name must be less than %1 characters").arg(Control::max_len_string_location_name + 1));
      return false;
  }
  Schedule* check = scheduleManager->getScheduleByName(scheduleNameTextField->text());
  if (check != NULL) {
//      JOptionPane.showMessageDialog(this, Bundle.getMessage("ScheduleAlreadyExists"), MessageFormat.format(Bundle
//              .getMessage("CanNotSchedule"), new Object[]{Bundle.getMessage("Copy")}), JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Can not %1 schedule!").arg(tr("Copy")), tr("A schedule with this name already exists"));
      return false;
  }
  return true;
 }

 /*public*/ void ScheduleCopyFrame::dispose() {
     //scheduleManager.removePropertyChangeListener(this);
  connect(scheduleManager->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }

 /*public*/ void ScheduleCopyFrame::propertyChange(PropertyChangeEvent* e) {
     log->debug(tr("PropertyChange (%1) new: (%2)").arg(e->getPropertyName()).arg(e->getNewValue().toString()));
     if (e->getPropertyName()==(ScheduleManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateComboBoxes();
     }
 }
 /*public*/ QString ScheduleCopyFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.schedules.ScheduleCopyFrame";
 }

}
