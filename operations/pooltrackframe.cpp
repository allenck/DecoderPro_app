#include "pooltrackframe.h"
#include "trackeditframe.h"
#include "pool.h"
#include "track.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "jtextfield.h"
#include "jcombobox.h"
#include "logger.h"
#include "control.h"
#include <QScrollArea>
#include <QGroupBox>
#include "location.h"
#include <QMessageBox>
#include "operationsxml.h"
#include "vptr.h"
#include "setup.h"
#include "trackeditframe.h"
#include "gridbaglayout.h"

namespace Operations
{
 /**
  *
  * Things to test with this frame:
  *
  * - Adding a new Pool name to the available pools list
  *
  * - What happens when a NULL track is passed to the frame
  *
  * - Selecting an existing pool and saving it to the track
  *
  * - Selecting a minimum length and saving it to the track
  *
  * - Not sure if we want to test the status display panel, as it doesn't do
  * anything.
  *
  * @author Daniel Boudreau Copyright (C) 2011
  * @author Gregory Madsen Copyright (C) 2012
  *
  *
  */
 //class PoolTrackFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 3751835388981078259L;
 // labels

 /*public*/ PoolTrackFrame::PoolTrackFrame(TrackEditFrame* tef, QWidget* parent) : OperationsFrame(tef){
     //super();
common();
     _tefx = tef;
     _track = _tefx->_track;
 }

 /*public*/ PoolTrackFrame::PoolTrackFrame(Track* track, QWidget* parent) : OperationsFrame(){
     //super();
     common();
     _track = track;
 }

 void PoolTrackFrame::common()
 {
  log = new Logger("PoolTrackFrame");
  name = new QLabel(tr("Name"));
  minimum = new QLabel(tr("Minimum"));
  length = new QLabel(tr("Length"));

  // text field
  trackPoolNameTextField = new JTextField(20);
  trackMinLengthTextField = new JTextField(5);

  // combo box
  comboBoxPools = new JComboBox();

  // major buttons
  addButton = new QPushButton(tr("Add"));
  saveButton = new QPushButton(tr("Save"));

  // pool status
  poolStatus = new QGroupBox();

 }

 //@Override
 /*public*/ void PoolTrackFrame::initComponents()
 {
   if (_track == NULL)
   {
       log->debug("track is NULL, pools can not be created");
       return;
   }
   // the following code sets the frame's initial state
   //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
   //_track.addPropertyChangeListener(this);
connect(_track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));
   //_track.getLocation().addPropertyChangeListener(this);
connect(_track->getLocation()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));

   _pool = _track->getPool();

   if (_pool != NULL) {
       //_pool.addPropertyChangeListener(this);
       connect(_pool->propertyChangeSupport, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));
   }

   // load the panel
   QGroupBox* p1Frame = new QGroupBox;
   p1Frame->setLayout(new QVBoxLayout);
   QWidget* p1 = new QWidget();
   p1->setLayout(new QVBoxLayout); //(p1, BoxLayout.Y_AXIS));
   QScrollArea* p1Pane = new QScrollArea(/*p1*/);
   p1Pane->setWidgetResizable(true);
   p1Frame->layout()->addWidget(p1Pane);
   //p1Pane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
   //p1Pane.setBorder(BorderFactory.createTitledBorder(""));
   p1Frame->setStyleSheet(gbStyleSheet);

   QGroupBox* poolName = new QGroupBox();
   poolName->setLayout(new GridBagLayout());
   //poolName.setBorder(BorderFactory.createTitledBorder(tr("PoolName")));
   poolName->setStyleSheet(gbStyleSheet);
   poolName->setTitle(tr("Pool Name"));
   addItem(poolName, trackPoolNameTextField, 0, 0);
   addItem(poolName, addButton, 1, 0);

   QGroupBox* selectPool = new QGroupBox();
   selectPool->setLayout(new GridBagLayout());
   //selectPool.setBorder(BorderFactory.createTitledBorder(tr("PoolSelect")));
   selectPool->setStyleSheet(gbStyleSheet);
   selectPool->setTitle(tr("Pool Select"));
   addItem(selectPool, comboBoxPools, 0, 0);

   QGroupBox* minLengthTrack = new QGroupBox();
   minLengthTrack->setLayout(new GridBagLayout());
//   minLengthTrack.setBorder(BorderFactory.createTitledBorder(MessageFormat.format(Bundle
//           .getMessage("PoolTrackMinimum"), new Object[]{_track.getName()})));
   minLengthTrack->setStyleSheet(gbStyleSheet);
   minLengthTrack->setTitle(tr("Minimum track length %1").arg(_track->getName()));
   addItem(minLengthTrack, trackMinLengthTextField, 0, 0);

   trackMinLengthTextField->setText(QString::number(_track->getMinimumLength()));

   QGroupBox* savePool = new QGroupBox();
   savePool->setLayout(new GridBagLayout());
   //savePool.setBorder(BorderFactory.createTitledBorder(""));
   savePool->setStyleSheet(gbStyleSheet);
   //savePool->setTitle(tr(""));
   addItem(savePool, saveButton, 0, 0);

   p1->layout()->addWidget(poolName);
   p1->layout()->addWidget(selectPool);
   p1->layout()->addWidget(minLengthTrack);
   p1->layout()->addWidget(savePool);

   QGroupBox* p2Frame = new QGroupBox;
   p2Frame->setLayout(new QVBoxLayout);
   QWidget* p2 = new QWidget();
   p2->setLayout(new QVBoxLayout); //(p2, BoxLayout.Y_AXIS));
   QScrollArea* p2Pane = new QScrollArea(p2);
   p2Pane->setWidgetResizable(true);
   p2Frame->layout()->addWidget(p2Pane);
//   p2Pane.setHorizontalScrollBarPolicy(JScrollPane.HORIZONTAL_SCROLLBAR_NEVER);
//   p2Pane.setBorder(BorderFactory.createTitledBorder(""));
   p2Frame->setStyleSheet(gbStyleSheet);

   // pool status panel
   poolStatus->setLayout(new GridBagLayout());

   p2->layout()->addWidget(poolStatus);

   p1Pane->setWidget(p1);
   thisLayout->addWidget(/*p1Pane*/p1Frame);
   p2Pane->setWidget(p2);
   thisLayout->addWidget(p2Pane);
   setTitle(tr("Pool Track"));

   // load comboBox
   updatePoolsComboBox();
   updatePoolStatus();

   // button action - These use a convention in the OperationsFrame base
   // class that requires the events to be sorted out in
   // buttonActionPerformed.
   addButtonAction(addButton);
   addButtonAction(saveButton);

   setMinimumSize(QSize(Control::panelWidth300, Control::panelHeight250));
   setVisible(true);
 }

 /*private*/ void PoolTrackFrame::updatePoolsComboBox() {
     _track->getLocation()->updatePoolComboBox(comboBoxPools);
     comboBoxPools->setCurrentIndex(comboBoxPools->findData(VPtr<Pool>::asQVariant(_track->getPool())));
 }

 /*private*/ void PoolTrackFrame::updatePoolStatus() {
     // This shows the details of the current member tracks in the Pool.
     //poolStatus.removeAll();
  QLayoutItem* item;
  while ( ( item = poolStatus->layout()->takeAt( 0 ) ) != NULL )
  {
      delete item->widget();
      delete item;
  }

     addItemLeft(poolStatus, name, 0, 0);
     addItem(poolStatus, minimum, 1, 0);
     addItem(poolStatus, length, 2, 0);

     QString poolName = "";
     if (_track->getPool() != NULL) {
         Pool* pool = _track->getPool();
         poolName = pool->getName();
         QList<Track*> tracks = pool->getTracks();
         int totalMinLength = 0;
         int totalLength = 0;
         for (int i = 0; i < tracks.size(); i++) {
             Track* track = tracks.at(i);
             QLabel* name = new QLabel();
             name->setText(track->getName());

             QLabel* minimum = new QLabel();
             minimum->setText(QString::number(track->getMinimumLength()));
             totalMinLength = totalMinLength + track->getMinimumLength();

             QLabel* length = new QLabel();
             length->setText(QString::number(track->getLength()));
             totalLength = totalLength + track->getLength();

             addItemLeft(poolStatus, name, 0, i + 1);
             addItem(poolStatus, minimum, 1, i + 1);
             addItem(poolStatus, length, 2, i + 1);
         }
         // Summary
         QLabel* total = new QLabel(tr("Totals"));
         addItem(poolStatus, total, 0, tracks.size() + 1);
         QLabel* totalMin = new QLabel();
         totalMin->setText(QString::number(totalMinLength));
         addItem(poolStatus, totalMin, 1, tracks.size() + 1);
         QLabel* totalLen = new QLabel();
         totalLen->setText(QString::number(totalLength));
         addItem(poolStatus, totalLen, 2, tracks.size() + 1);
     }
//     poolStatus.setBorder(BorderFactory.createTitledBorder(MessageFormat.format(tr("PoolTracks"),
//             new Object[]{poolName})));
     poolStatus->setStyleSheet(gbStyleSheet);
     poolStatus->setTitle(tr("Tracks in pool %1").arg(poolName));
     poolStatus->update();
     //poolStatus->repaint();
     resize(QSize()); // kill JMRI window size
     adjustSize();
 }

 /*public*/ void PoolTrackFrame::buttonActionPerformed(QWidget* ae) {
  QPushButton* source = (QPushButton*)ae;
     if (source == addButton) {
         Location* location = _track->getLocation();
         location->addPool(trackPoolNameTextField->text());
     }

     if (source == saveButton) {
         bool ok;
             _track->setMinimumLength(trackMinLengthTextField->text().toInt(&ok));
         if(!ok)
         {
//             JOptionPane.showMessageDialog(this, tr("TrackMustBeNumber"), Bundle
//                     .getMessage("ErrorTrackLength"), JOptionPane.ERROR_MESSAGE);
          QMessageBox::critical(this, tr("Track length incorrect!"), tr("Track length must be a number"));
             return;
         }

         if (_pool != NULL) {
             //_pool.removePropertyChangeListener(this);
          disconnect(_pool->propertyChangeSupport, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));
         }
         _pool = (Pool*) VPtr<Pool>::asPtr(comboBoxPools->currentData());
         if (_pool != NULL) {
             //_pool.addPropertyChangeListener(this);
          connect(_pool->propertyChangeSupport, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));
         }
         _track->setPool(_pool);	// this causes a property change to this frame

         // save location file
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
 }

 /*public*/ void PoolTrackFrame::dispose() {
     if (_track != NULL) {
         //_track.removePropertyChangeListener(this);
      disconnect(_track->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));
         //_track.getLocation().removePropertyChangeListener(this);
      disconnect(_track->getLocation()->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));
     }
     if (_pool != NULL) {
         //_pool.removePropertyChangeListener(this);
      disconnect(_pool->propertyChangeSupport, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(pack()));
     }
     OperationsFrame::dispose();
 }

 /*public*/ void PoolTrackFrame::propertyChange(PropertyChangeEvent* e) {
     // This should move to the base class
     // Just call LogEvent(e); instead. It will figure out if logging is
     // enabled, etc.
     if (Control::SHOW_PROPERTY) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e->
                 getNewValue().toString()));
     }
     if (e->getPropertyName()==(Location::POOL_LENGTH_CHANGED_PROPERTY)) {
         updatePoolsComboBox();
     }

     if (e->getPropertyName()==(Pool::LISTCHANGE_CHANGED_PROPERTY)
             || e->getPropertyName()==(Location::LENGTH_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::POOL_CHANGED_PROPERTY)
             || e->getPropertyName()==(Track::MIN_LENGTH_CHANGED_PROPERTY)) {
         updatePoolStatus();
     }
 }
 /*public*/ QString PoolTrackFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.tools.PoolTrackFrame";
 }

}
