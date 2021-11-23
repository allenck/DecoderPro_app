#include "spureditframe.h"
#include "track.h"
#include <QGroupBox>
#include "jbutton.h"
#include "jcombobox.h"
#include "control.h"
#include <QLabel>
#include "schedulemanager.h"
#include "schedule.h"
#include "vptr.h"
#include "scheduleeditframe.h"
#include "schedule.h"
#include "gridbaglayout.h"
#include "showtrainsservinglocationaction.h"
#include "showcarsbylocationaction.h"
#include "location.h"
#include <QMenu>
#include "changetracktypeaction.h"
#include "ignoreusedtrackaction.h"
#include "alternatetrackaction.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
/**
 * Frame for user edit of a spur.
 *
 * @author Dan Boudreau Copyright (C) 2008, 2011
 * @version $Revision: 29665 $
 */
///*public*/ class SpurEditFrame extends TrackEditFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = 9021321721517947715L;
 // labels, buttons, etc. for spurs

 /*public*/ SpurEditFrame::SpurEditFrame(QWidget* parent)
     : TrackEditFrame(parent)
 {
  //super();
  log = new Logger("SpurEditFrame");
  textSchedule = new QLabel(tr("Delivery Schedule"));
  textSchError = new QLabel();
  editScheduleButton = new JButton();
  comboBoxSchedules = ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->getComboBox();

  panelSchedule = panelOpt4;
  sef = NULL;

 }

 /*public*/ void SpurEditFrame::initComponents(Location* location, Track* track)
 {
  _type = Track::SPUR;

  // setup the optional panel with schedule stuff
  panelSchedule->setLayout(new GridBagLayout());
  panelSchedule->setBorder(BorderFactory::createTitledBorder(tr("Delivery Schedule")));
//  panelSchedule->setStyleSheet(gbStyleSheet);
//  panelSchedule->setTitle("Delivery Schedule");
  addItem(panelSchedule, comboBoxSchedules, 0, 0);
  addItem(panelSchedule, editScheduleButton, 1, 0);
  addItem(panelSchedule, textSchError, 2, 0);

  TrackEditFrame::initComponents(location, track);
  _toolMenu->addAction(new AlternateTrackAction(this));
  _toolMenu->addAction(new IgnoreUsedTrackAction(this));
  _toolMenu->addAction(new ChangeTrackTypeAction(this));
  _toolMenu->addAction(new ShowTrainsServingLocationAction(tr("Show Trains Serving this Track"), _location, _track,this));
  _toolMenu->addAction(new ShowCarsByLocationAction(false, location->getName(), _trackName,this));

  addHelpMenu("package.jmri.jmrit.operations.Operations_Sidings", true); // NOI18N

  // override text strings for tracks
  panelTrainDir->setBorder(BorderFactory::createTitledBorder(tr("This spur is serviced by trains traveling")));
  panelCheckBoxes->setBorder(BorderFactory::createTitledBorder(tr("Select the rolling stock serviced by this spur")));
  deleteTrackButton->setText(tr("Delete Spur Track"));
  addTrackButton->setText(tr("Add Spur Track"));
  saveTrackButton->setText(tr("Save Spur Track"));

  // setup buttons
  addButtonAction(editScheduleButton);
  addComboBoxAction(comboBoxSchedules);

  // Select the spur's Schedule
  updateScheduleComboBox();

  //((ScheduleManager*)InstanceManager::getDefault("ScheduleManager")).addPropertyChangeListener(this);
  connect(((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

  // finish
  panelOrder->setVisible(false); // Car order out of spurs is not available
  adjustSize();
  setVisible(true);
 }

 /*public*/ void SpurEditFrame::buttonActionPerformed(QWidget* ae)
 {
  JButton* source = (JButton*)ae;
  if (source == editScheduleButton) {

      editAddSchedule();
  }
  TrackEditFrame::buttonActionPerformed(ae);
 }

 /*public*/ void SpurEditFrame::comboBoxActionPerformed(QWidget* ae) {
     updateScheduleButtonText();
 }

 /*private*/ void SpurEditFrame::updateScheduleButtonText() {
     if (comboBoxSchedules->currentText() == "") {
         editScheduleButton->setText(tr("Add"));
     } else {
         editScheduleButton->setText(tr("Edit"));
     }
 }


 /*private*/ void SpurEditFrame::editAddSchedule()
 {
  log->debug("Edit/add schedule");

  if (sef != NULL) {
      sef->dispose();
  }
  Schedule* schedule = (Schedule*) VPtr<Schedule>::asPtr(comboBoxSchedules->currentData());
  sef = new ScheduleEditFrame(schedule, _track);
 }

 /*protected*/ void SpurEditFrame::enableButtons(bool enabled)
 {
  editScheduleButton->setEnabled(enabled);
  comboBoxSchedules->setEnabled(enabled);
  if (!enabled)
  {
   comboBoxSchedules->setCurrentIndex(0);
  }
  TrackEditFrame::enableButtons(enabled);
 }

 /*protected*/ void SpurEditFrame::saveTrack(Track* track)
{
  // save the schedule

  QVariant selected = comboBoxSchedules->currentData();
  if (selected == QVariant()) {
      track->setScheduleId(Track::NONE);
  } else {
      Schedule* sch = (Schedule*) VPtr<Schedule>::asPtr(selected);
      // update only if the schedule has changed
      track->setScheduleId(sch->getId());
  }
  textSchError->setText(track->checkScheduleValid());

  TrackEditFrame::saveTrack(track);
 }

 /*protected*/ void SpurEditFrame::addNewTrack()
 {
  TrackEditFrame::addNewTrack();
  updateScheduleComboBox(); // reset schedule and error text
 }

 /*private*/ void SpurEditFrame::updateScheduleComboBox()
 {
  ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->updateComboBox(comboBoxSchedules);
  if (_track != NULL)
  {
   Schedule* sch = ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->getScheduleById(_track->getScheduleId());
   comboBoxSchedules->setCurrentIndex(comboBoxSchedules->findData(VPtr<Schedule>::asQVariant(sch)));
   textSchError->setText(_track->checkScheduleValid());
   if (sch != NULL)
   {
       //sch.removePropertyChangeListener(this);
    disconnect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
       //sch.addPropertyChangeListener(this);
    connect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
   }
  }
 }

 /*public*/ void SpurEditFrame::dispose()
 {

  //((ScheduleManager*)InstanceManager::getDefault("ScheduleManager")).removePropertyChangeListener(this);
  disconnect(((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  if (_track != NULL)
  {
   Schedule* sch = ((ScheduleManager*)InstanceManager::getDefault("ScheduleManager"))->getScheduleById(_track->getScheduleId());
   if (sch != NULL)
       //sch.removePropertyChangeListener(this);
    disconnect(sch->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
  }
  TrackEditFrame::dispose();
 }

 /*public*/ void SpurEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
      ->getNewValue().toString()));
     }

     if (e->getPropertyName()==(ScheduleManager::LISTLENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::SCHEDULE_ID_CHANGED_PROPERTY)) {
         updateScheduleComboBox();
     }
     if (e->getPropertyName()==(Schedule::LISTCHANGE_CHANGED_PROPERTY)) {
         textSchError->setText(_track->checkScheduleValid());
     }

     TrackEditFrame::propertyChange(e);
 }

 /*public*/ QString SpurEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.SpurEditFrame";
 }

}
