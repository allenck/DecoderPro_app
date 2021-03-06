#include "scheduleeditframe.h"
#include "jtextfield.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QRadioButton>
#include <QGroupBox>
#include <QCheckBox>
#include "jcombobox.h"
#include "track.h"
#include "location.h"
#include "control.h"
#include "setup.h"
#include "schedulemanager.h"
#include "locationmanagerxml.h"
#include <QScrollArea>
#include "scheduletablemodel.h"
#include "jtable.h"
#include "cartypes.h"
#include <QScrollBar>
#include "gridbaglayout.h"
#include <QButtonGroup>
#include <QMenu>
#include <QMenuBar>
#include "logger.h"
#include "schedulesbyloadaction.h"
#include "scheduleresethitsaction.h"
#include <QMessageBox>
#include "locationmanager.h"
#include "schedulecopyaction.h"
#include "scheduleoptionsaction.h"
#include "instancemanager.h"

namespace Operations
{
/**
 * Frame for user edit of a schedule
 *
 * @author Dan Boudreau Copyright (C) 2008, 2011
 * @version $Revision: 29644 $
 */
///*public*/ class ScheduleEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -4077459319293039003L;

 /*public*/ /*static*/ /*final*/ int ScheduleEditFrame::MAX_NAME_LENGTH = Control::max_len_string_location_name;
 /*public*/ /*static*/ /*final*/ QString ScheduleEditFrame::NAME = tr("Name");
 /*public*/ /*static*/ /*final*/ QString ScheduleEditFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ ScheduleEditFrame::ScheduleEditFrame(Schedule* schedule, Track* track, QWidget* parent)
     : OperationsFrame(parent)
 {
    // super();
     scheduleModel = new ScheduleTableModel();
     scheduleTable = new JTable(scheduleModel);
     scheduleTable->setObjectName("ScheduleTable");
     //JScrollPane schedulePane;

     manager = NULL;
     managerXml = NULL;

     _schedule = NULL ;
     _scheduleItem = NULL ;
     _location = NULL ;
     _track = NULL ;

     // labels
     // major buttons
     addTypeButton = new QPushButton(tr("AddType"));
     saveScheduleButton = new QPushButton(tr("Save Schedule"));
     deleteScheduleButton = new QPushButton(tr("Delete Schedule"));
     addScheduleButton = new QPushButton(tr("Add Schedule"));

     // check boxes
     QCheckBox* checkBox = NULL;

     // radio buttons
     addLocAtTop = new QRadioButton(tr("Top"));
     addLocAtBottom = new QRadioButton(tr("Bottom"));
     sequentialRadioButton = new QRadioButton(tr("Sequential"));
     matchRadioButton = new QRadioButton(tr("Match"));

     // text field
     scheduleNameTextField = new JTextField(20);
     commentTextField = new JTextField(35);

     // combo boxes
     typeBox = new JComboBox();

     _schedule = schedule;
     _location = track->getLocation();
     _track = track;

     // load managers
     manager = ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"));
     managerXml = ((LocationManagerXml*)InstanceManager::getDefault("LocationManagerXml"));

     // Set up the jtable in a Scroll Pane..
//     schedulePane = new JScrollPane(scheduleTable);
//     schedulePane->setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);

     scheduleModel->initTable(this, scheduleTable, schedule, _location, _track);
     if (_schedule != NULL )
     {
      scheduleNameTextField->setText(_schedule->getName());
      commentTextField->setText(_schedule->getComment());
      setTitle(tr("Edit Schedule for Spur %1").arg(_track->getName()));
      enableButtons(true);
     }
     else
     {
      tr("Add Schedule for Spur %1").arg(_track->getName());
      enableButtons(false);
     }

     //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // Layout the panel by rows
     QWidget* p1 = new QWidget();
     p1->setLayout(new QHBoxLayout); //(p1, BoxLayout.X_AXIS));

     QScrollArea* p1Pane = new QScrollArea(/*p1*/);
     //p1Pane->setVerticalScrollBarPolicy(JScrollPane.VERTICAL_SCROLLBAR_NEVER);
     p1Pane->verticalScrollBar()->setEnabled(false);
     p1Pane->setWidgetResizable(true);
     p1Pane->setMinimumSize(QSize(300,3 * scheduleNameTextField->sizeHint().height()));
     p1Pane->setMaximumSize(QSize(2000, 200));

     // row 1a name
     QGroupBox* pName = new QGroupBox();
     pName->setLayout(new GridBagLayout());
     pName->setStyleSheet(gbStyleSheet);
     pName->setTitle(tr("Name"));
     //pName->setBorder(BorderFactory.createTitledBorder(tr("Name")));
     addItem(pName, scheduleNameTextField, 0, 0);

     // row 1b comment
     QGroupBox* pC = new QGroupBox();
     pC->setLayout(new GridBagLayout());
     //pC->setBorder(BorderFactory.createTitledBorder(tr("Comment")));
     pC->setStyleSheet(gbStyleSheet);
     pC->setTitle(tr("Comment"));
     addItem(pC, commentTextField, 0, 0);

     // row 1c mode
     QGroupBox* pMode = new QGroupBox();
     pMode->setLayout(new GridBagLayout());
     //pMode->setBorder(BorderFactory.createTitledBorder(tr("ScheduleMode")));
     pMode->setStyleSheet(gbStyleSheet);
     pMode->setTitle(tr("Schedule Mode"));
     addItem(pMode, sequentialRadioButton, 0, 0);
     addItem(pMode, matchRadioButton, 1, 0);

     sequentialRadioButton->setToolTip(tr("When selected, schedule items are serviced sequentially"));
     matchRadioButton->setToolTip(tr("When selected, check all schedule items for a match"));
     QButtonGroup* modeGroup = new QButtonGroup();
     modeGroup->addButton(sequentialRadioButton);
     modeGroup->addButton(matchRadioButton);

     sequentialRadioButton->setChecked(_track->getScheduleMode() == Track::SEQUENTIAL);
     matchRadioButton->setChecked(_track->getScheduleMode() == Track::MATCH);
     scheduleModel->setMatchMode(_track->getScheduleMode() == Track::MATCH);

     p1->layout()->addWidget(pName);
     p1->layout()->addWidget(pC);
     p1->layout()->addWidget(pMode);
     p1Pane->setWidget(p1);

     // row 2
     QGroupBox* p3 = new QGroupBox();
     p3->setLayout(new GridBagLayout());
     //p3->setBorder(BorderFactory.createTitledBorder(tr("AddItem")));
     p3->setStyleSheet(gbStyleSheet);
     p3->setTitle(tr("Add New Delivery"));
     addItem(p3, typeBox, 0, 1);
     addItem(p3, addTypeButton, 1, 1);
     addItem(p3, addLocAtTop, 2, 1);
     addItem(p3, addLocAtBottom, 3, 1);
     QButtonGroup* group = new QButtonGroup();
     group->addButton(addLocAtTop);
     group->addButton(addLocAtBottom);
     addLocAtBottom->setChecked(true);

     p3->setMaximumSize(QSize(2000, 200));

     // row 11 buttons
     QGroupBox* pB = new QGroupBox();
     pB->setLayout(new GridBagLayout());
     //pB->setBorder(BorderFactory.createTitledBorder(""));
     pB->setStyleSheet(gbStyleSheet);
     pName->setTitle(tr("Name"));
     pB->setMaximumSize(QSize(2000, 200));

     // row 13
     addItem(pB, deleteScheduleButton, 0, 0);
     addItem(pB, addScheduleButton, 1, 0);
     addItem(pB, saveScheduleButton, 3, 0);

     thisLayout->addWidget(p1Pane);
     thisLayout->addWidget(/*schedulePane*/scheduleTable);
     thisLayout->addWidget(p3);
     thisLayout->addWidget(pB);

     // setup buttons
     addButtonAction(addTypeButton);
     addButtonAction(deleteScheduleButton);
     addButtonAction(addScheduleButton);
     addButtonAction(saveScheduleButton);

     // setup radio buttons
     addRadioButtonAction(sequentialRadioButton);
     addRadioButtonAction(matchRadioButton);

     // setup combobox
     loadTypeComboBox();

     // build menu
     QMenuBar* menuBar = new QMenuBar();
     QMenu* toolMenu = new QMenu("Tools");
     menuBar->addMenu(toolMenu);
     toolMenu->addAction(new ScheduleCopyAction(schedule,this));
     toolMenu->addAction(new ScheduleOptionsAction(this));
     toolMenu->addAction(new ScheduleResetHitsAction(schedule, this));
     toolMenu->addAction(new SchedulesByLoadAction(tr("Show Schedules by Car Type and Load"),this));
     setMenuBar(menuBar);
     addHelpMenu("package.jmri.jmrit.operations.Operations_Schedules", true); // NOI18N

     // get notified if car types or roads are changed
     //CarTypes::instance().addPropertyChangeListener(this);
     connect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //_location.addPropertyChangeListener(this);
     connect(_location, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
    // _track.addPropertyChangeListener(this);
     connect(_track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     // set frame size and schedule for display
     initMinimumSize(QSize(Control::panelWidth700, Control::panelHeight400));
 }

 // Save, Delete, Add
 /*public*/ void ScheduleEditFrame::buttonActionPerformed(QWidget* ae)
 {
  QPushButton* source = (QPushButton*)ae;
  if (source == addTypeButton) {
      addNewScheduleItem();
  }
  if (source == saveScheduleButton) {
      log->debug("schedule save button activated");
      Schedule* schedule = manager->getScheduleByName(scheduleNameTextField->text());
      if (_schedule == NULL  && schedule == NULL ) {
          saveNewSchedule();
      } else {
          if (schedule != NULL  && schedule != _schedule) {
              reportScheduleExists(tr("save"));
              return;
          }
          saveSchedule();
      }
      if (Setup::isCloseWindowOnSaveEnabled()) {
          dispose();
      }
  }
  if (source == deleteScheduleButton)
  {
   log->debug("schedule delete button activated");
//      if (JOptionPane.showConfirmDialog(this, MessageFormat.format(
//              tr("DoYouWantToDeleteSchedule"),
//              new Object[]{scheduleNameTextField.getText()}), Bundle
//              .getMessage("?"), JOptionPane.YES_NO_OPTION) != JOptionPane.YES_OPTION) {
   if(   QMessageBox::question(this, tr("Delete Schedule"), tr("Do you want to delete schedule %1?").arg(scheduleNameTextField->text()), QMessageBox::Yes | QMessageBox::No) != QMessageBox::Yes)
   {
    return;
   }
   Schedule* schedule = manager->getScheduleByName(scheduleNameTextField->text());
   if (schedule == NULL ) {
       return;
   }

   if (_track != NULL ) {
       _track->setScheduleId(Track::NONE);
   }

   manager->deregister(schedule);
   _schedule = NULL ;

   enableButtons(false);
   // save schedule file
   OperationsXml::save();
  }
  if (source == addScheduleButton)
  {
   Schedule* schedule = manager->getScheduleByName(scheduleNameTextField->text());
   if (schedule != NULL ) {
       reportScheduleExists(tr("add"));
       return;
   }
   saveNewSchedule();
  }
 }

 /*public*/ void ScheduleEditFrame::radioButtonActionPerformed(QWidget* ae) {
     log->debug("Radio button action");
     QRadioButton* source = (QRadioButton*)ae;
     scheduleModel->setMatchMode(source == matchRadioButton);
 }

 /*private*/ void ScheduleEditFrame::addNewScheduleItem()
 {
  if (typeBox->currentText() == NULL ) {
      return;
  }
  // add item to this schedule
  if (addLocAtTop->isChecked()) {
      _schedule->addItem( typeBox->currentText(), 0);
  } else {
      _schedule->addItem( typeBox->currentText());
  }
  if (_track->getScheduleMode() == Track::MATCH
          && typeBox->currentIndex() < typeBox->count() - 1) {
      typeBox->setCurrentIndex(typeBox->currentIndex() + 1);
  }
 }

 /*private*/ void ScheduleEditFrame::saveNewSchedule() {
     if (!checkName(tr("add"))) {
         return;
     }
     Schedule* schedule = manager->newSchedule(scheduleNameTextField->text());
     scheduleModel->initTable(this, scheduleTable, schedule, _location, _track);
     _schedule = schedule;
     // enable checkboxes
     enableButtons(true);
     saveSchedule();
 }

 /*private*/ void ScheduleEditFrame::saveSchedule() {
     if (!checkName(tr("save"))) {
         return;
     }
     _schedule->setName(scheduleNameTextField->text());
     _schedule->setComment(commentTextField->text());

//     if (scheduleTable.isEditing()) {
//         log->debug("schedule table edit true");
//         scheduleTable.getCellEditor().stopCellEditing();
//         scheduleTable.clearSelection();
//     }
     if (_track != NULL ) {
         if (_track->getScheduleId()!=(_schedule->getId())) {
             ((LocationManager*)InstanceManager::getDefault("LocationManager"))->resetMoves();
         }
         _track->setScheduleId(_schedule->getId());
         if (sequentialRadioButton->isChecked()) {
             _track->setScheduleMode(Track::SEQUENTIAL);
         } else {
             _track->setScheduleMode(Track::MATCH);
         }
     }

     saveTableDetails(scheduleTable);
     // save schedule file
     OperationsXml::save();
 }

 /*private*/ void ScheduleEditFrame::loadTypeComboBox()
{
  typeBox->clear();
  foreach (QString typeName, ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getNames())
  {
   if (_track->acceptsTypeName(typeName))
   {
    typeBox->addItem(typeName);
   }
  }
 }

 /**
  *
  * @return true if name is less than 26 characters
  */
 /*private*/ bool ScheduleEditFrame::checkName(QString s)
 {
  if (scheduleNameTextField->text().trimmed()==("")) {
      return false;
  }
  if (scheduleNameTextField->text().length() > MAX_NAME_LENGTH)
  {
   log->error("Schedule name must be less than 26 characters");
//   JOptionPane.showMessageDialog(this, MessageFormat.format(
//           tr("ScheduleNameLengthMax"),
//           new Object[]{Integer.toString(MAX_NAME_LENGTH + 1)}), MessageFormat.format(
//                   tr("CanNotSchedule"), new Object[]{s}),
//           JOptionPane.ERROR_MESSAGE);
   QMessageBox::critical(this, tr("Can not %1 schedule!").arg(s), tr("Schedule name must be less than {0} characters").arg(MAX_NAME_LENGTH + 1));
   return false;
  }
  return true;
 }

 /*private*/ void ScheduleEditFrame::reportScheduleExists(QString s)
 {
  log->info("Can not " + s + ", schedule already exists");
//     JOptionPane.showMessageDialog(this, tr("ReportExists"),
//             MessageFormat.format(tr("CanNotSchedule"), new Object[]{s}),
//             JOptionPane.ERROR_MESSAGE);
  QMessageBox::critical(this, tr("Can not %1 schedule!").arg(s), tr("A schedule with this name already exists"));
 }

 /*private*/ void ScheduleEditFrame::enableButtons(bool enabled) {
     typeBox->setEnabled(enabled);
     addTypeButton->setEnabled(enabled);
     addLocAtTop->setEnabled(enabled);
     addLocAtBottom->setEnabled(enabled);
     saveScheduleButton->setEnabled(enabled);
     deleteScheduleButton->setEnabled(enabled);
     scheduleTable->setEnabled(enabled);
     // the inverse!
     addScheduleButton->setEnabled(!enabled);
 }

 /*public*/ void ScheduleEditFrame::dispose() {
     //CarTypes::instance().removePropertyChangeListener(this);
     disconnect(((CarTypes*)InstanceManager::getDefault("CarTypes")), SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     //_location.removePropertyChangeListener(this);
     disconnect(_location, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     //_track.removePropertyChangeListener(this);
     disconnect(_track, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     scheduleModel->dispose();
     OperationsFrame::dispose();
 }

 /*public*/ void ScheduleEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
      log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
              ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(CarTypes::CARTYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::TYPES_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::TYPES_CHANGED_PROPERTY)) {
         loadTypeComboBox();
     }
 }
/*public*/ QString ScheduleEditFrame::getClassName()
{
 return "jmri.jmrit.operations.locations.schedules.ScheduleEditFrame";
}

}
