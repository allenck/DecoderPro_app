#include "trackdestinationeditframe.h"
#include "locationmanager.h"
#include <QVBoxLayout>
#include "jbutton.h"
#include "track.h"
#include "gridbaglayout.h"
#include <QScrollArea>
#include <QRadioButton>
#include <QButtonGroup>
#include <QLabel>
#include <QScrollArea>
#include "logger.h"
#include "track.h"
#include "location.h"
#include "flowlayout.h"
#include "control.h"
#include "operationsxml.h"
#include "setup.h"
#include <QCheckBox>
#include "cartypes.h"
#include <QMessageBox>
#include "carloads.h"
#include "rollingstock.h"
#include "carroads.h"
#include "car.h"
#include "carmanager.h"
#include "router.h"
#include "instancemanager.h"
#include "borderfactory.h"

namespace Operations
{
 /**
  * Frame for user edit of track roads
  *
  * @author Dan Boudreau Copyright (C) 2013
  * @version $Revision: 22371 $
  */
 ///*public*/ class TrackDestinationEditFrame extends OperationsFrame implements java.beans.PropertyChangeListener {

 /**
  *
  */
 //private static final long serialVersionUID = -962898724870308907L;



 /*public*/ /*static*/ /*final*/ QString TrackDestinationEditFrame::DISPOSE = "dispose"; // NOI18N

 /*public*/ TrackDestinationEditFrame::TrackDestinationEditFrame(QWidget* parent)
   : OperationsFrame(tr("Edit Track Destinations"),parent)
 {
     //super(tr("TitleEditTrackDestinations"));
 log = new Logger("TrackDestinationEditFrame");
      _track = NULL;

      locationManager = ((LocationManager*)InstanceManager::getDefault("Operations::LocationManager"));

     // panels
     pControls = new JPanel();
     panelDestinations = new JPanel();
     paneDestinations = new QScrollArea(/*panelDestinations*/);

     // major buttons
     saveTrackButton = new JButton(tr("SaveTrack"));
     checkDestinationsButton = new JButton(tr("CheckDestinations"));

     // radio buttons
     destinationsAll = new QRadioButton(tr("AcceptAll"));
     destinationsInclude = new QRadioButton(tr("AcceptOnly"));
     destinationsExclude = new QRadioButton(tr("Exclude"));

     // labels
     trackName = new QLabel(); }

 /*public*/ void TrackDestinationEditFrame::initComponents(Track* track) {
     _track = track;

     // property changes
     // the following code sets the frame's initial state
     //getContentPane()->setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
     QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
     // Set up the panels
     // Layout the panel by rows
     // row 1
     JPanel* p1 = new JPanel();
     p1->setLayout(new QHBoxLayout);//(p1, BoxLayout.X_AXIS));
     p1->setMaximumSize(QSize(2000, 250));

     // row 1a
     JPanel* pTrackName = new JPanel();
     pTrackName->setLayout(new GridBagLayout());
     pTrackName->setBorder(BorderFactory::createTitledBorder(tr("Track")));
     addItem(pTrackName, trackName, 0, 0);

     // row 1b
     JPanel* pLocationName = new JPanel();
     pLocationName->setLayout(new GridBagLayout());
     pLocationName->setBorder(BorderFactory::createTitledBorder(tr("Location")));
     addItem(pLocationName, new QLabel(_track->getLocation()->getName()), 0, 0);

     p1->layout()->addWidget(pTrackName);
     p1->layout()->addWidget(pLocationName);

     // row 3
     JPanel* p3Frame = new JPanel;
     QWidget* p3 = new QWidget();
     p3->setLayout(new QVBoxLayout);//(p3, BoxLayout.Y_AXIS));
     QScrollArea* pane3 = new QScrollArea(/*p3*/);
     p3Frame->setBorder(BorderFactory::createTitledBorder(tr("Destination Track")));
     pane3->setMaximumSize(QSize(2000, 400));

     QWidget* pRadioButtons = new QWidget();
     pRadioButtons->setLayout(new FlowLayout());

     pRadioButtons->layout()->addWidget(destinationsAll);
     pRadioButtons->layout()->addWidget(destinationsInclude);
     pRadioButtons->layout()->addWidget(destinationsExclude);

     p3->layout()->addWidget(pRadioButtons);

     // row 4
     JPanel* panelDestinationsFrame = new JPanel;
     panelDestinationsFrame->setLayout(new QVBoxLayout);
     panelDestinationsFrame->layout()->addWidget(paneDestinations);
     paneDestinations->setWidgetResizable(true);
     panelDestinations->setLayout(new GridBagLayout());
     panelDestinationsFrame->setBorder(BorderFactory::createTitledBorder(tr("Destinations")));

     QButtonGroup* bGroup = new QButtonGroup();
     bGroup->addButton(destinationsAll);
     bGroup->addButton(destinationsInclude);
     bGroup->addButton(destinationsExclude);

     // row 12
     JPanel* panelButtons = new JPanel();
     panelButtons->setLayout(new GridBagLayout());
     panelButtons->setBorder(BorderFactory::createTitledBorder(""));
     //panelButtons->setTitle(tr(""));
     panelButtons->setMaximumSize(QSize(2000, 200));

     // row 13
     addItem(panelButtons, checkDestinationsButton, 0, 0);
     addItem(panelButtons, saveTrackButton, 1, 0);

     thisLayout->addWidget(p1);
     pane3->setWidget(p3);
     thisLayout->addWidget(/*pane3*/p3Frame);
     paneDestinations->setWidget(panelDestinations);
     thisLayout->addWidget(/*paneDestinations*/panelDestinationsFrame);
     thisLayout->addWidget(panelButtons);

     // setup buttons
     addButtonAction(checkDestinationsButton);
     addButtonAction(saveTrackButton);

     addRadioButtonAction(destinationsAll);
     addRadioButtonAction(destinationsInclude);
     addRadioButtonAction(destinationsExclude);

     // load fields and enable buttons
     if (_track != NULL) {
      _track->SwingPropertyChangeSupport::addPropertyChangeListener(this);
         trackName->setText(_track->getName());
         enableButtons(true);
     } else {
         enableButtons(false);
     }

     updateDestinations();

     //locationManager->SwingPropertyChangeSupport::addPropertyChangeListener(this);
     connect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

     // build menu
     // JMenuBar menuBar = new JMenuBar();
     // _toolMenu = new JMenu(tr("Tools"));
     // menuBar.add(_toolMenu);
     // setJMenuBar(menuBar);
     initMinimumSize(QSize(Control::panelWidth400, Control::panelHeight500));
 }

 // Save, Delete, Add
 /*public*/ void TrackDestinationEditFrame::buttonActionPerformed(QWidget* ae) {
     if (_track == NULL) {
         return;
     }
     JButton* source = (JButton*)ae;
     if (source == saveTrackButton) {
         log->debug("track save button activated");
         OperationsXml::save();
         if (Setup::isCloseWindowOnSaveEnabled()) {
             dispose();
         }
     }
     if (source == checkDestinationsButton) {
         checkDestinationsButton->setEnabled(false); // testing can take awhile, so disable
         checkDestinationsValid();
     }
 }

 /*protected*/ void TrackDestinationEditFrame::enableButtons(bool enabled) {
     saveTrackButton->setEnabled(enabled);
     checkDestinationsButton->setEnabled(enabled);
     destinationsAll->setEnabled(enabled);
     destinationsInclude->setEnabled(enabled);
     destinationsExclude->setEnabled(enabled);
 }

 /*public*/ void TrackDestinationEditFrame::radioButtonActionPerformed(QWidget* ae) {
 QRadioButton* source = (QRadioButton*)ae;
     log->debug("radio button activated");
     if (source == destinationsAll) {
         _track->setDestinationOption(Track::ALL_DESTINATIONS);
     }
     if (source == destinationsInclude) {
         _track->setDestinationOption(Track::INCLUDE_DESTINATIONS);
     }
     if (source == destinationsExclude) {
         _track->setDestinationOption(Track::EXCLUDE_DESTINATIONS);
     }
     updateDestinations();
 }

 /*private*/ void TrackDestinationEditFrame::updateDestinations() {
     log->debug("Update destinations");
     //panelDestinations.removeAll();
     QLayoutItem* item;
     while ( ( item = panelDestinations->layout()->takeAt( 0 ) ) != NULL )
     {
         delete item->widget();
         delete item;
     }
     if (_track != NULL) {
         destinationsAll->setChecked(_track->getDestinationOption()==(Track::ALL_DESTINATIONS));
         destinationsInclude->setChecked(_track->getDestinationOption()==(Track::INCLUDE_DESTINATIONS));
         destinationsExclude->setChecked(_track->getDestinationOption()==(Track::EXCLUDE_DESTINATIONS));
     }
     QList<Location*> locations = locationManager->getLocationsByNameList();
     for (int i = 0; i < locations.size(); i++) {
         Location* loc = locations.at(i);
         QCheckBox* cb = new QCheckBox(loc->getName());
         addItemLeft(panelDestinations, cb, 0, i);
         cb->setEnabled(!destinationsAll->isChecked());
         addCheckBoxAction(cb);
         if (destinationsAll->isChecked()) {
             cb->setChecked(true);
         } else if (_track != NULL && _track->acceptsDestination(loc)
                 ^ _track->getDestinationOption()==(Track::EXCLUDE_DESTINATIONS)) {
             cb->setChecked(true);
         }
     }
     panelDestinations->update();
 }

 /*public*/ void TrackDestinationEditFrame::checkBoxActionPerformed(QWidget* ae) {
     QCheckBox* b = (QCheckBox*) ae;
     log->debug(tr("checkbox change %1").arg(b->text()));
     if (_track == NULL) {
         return;
     }
     Location* loc = locationManager->getLocationByName(b->text());
     if (loc != NULL) {
         if (b->isChecked() ^ _track->getDestinationOption()==(Track::EXCLUDE_DESTINATIONS)) {
             _track->addDestination(loc);
         } else {
             _track->deleteDestination(loc);
         }
     }
 }

 //    JmriJFrame statusFrame;
 //    JLabel text;

 /*private*/ void TrackDestinationEditFrame::checkDestinationsValid() {
     // create a status frame
     //      statusFrame = new JmriJFrame(tr("TitleEditTrackDestinations"));
     //      JPanel ps = new JPanel();
     //      ps->setLayout(new BoxLayout(ps, BoxLayout.Y_AXIS));
     //      text = new JLabel("Start with this");
     //      ps.add(text);
     //
     //      statusFrame.thisLayout->addWidget(ps);
     //      statusFrame.pack();
     //      statusFrame->setSize(Control::panelWidth700, 100);
     //      statusFrame->setVisible(true);

//     SwingUtilities.invokeLater(new Runnable() {
//         /*public*/ void run() {
//             if (checkLocationsLoop())
//                 JOptionPane.showMessageDialog(NULL, tr("OkayMessage"));
//             checkDestinationsButton->setEnabled(true);
//             //                statusFrame.dispose();
//         }
//     });
  CheckLocations* checkLocations = new CheckLocations(this);
  QThread* thread = new QThread;
  checkLocations->moveToThread(thread);
  connect(thread, SIGNAL(started()), checkLocations, SLOT(process()));
  connect(checkLocations, SIGNAL(finished()), thread, SLOT(quit()));
  connect(checkLocations, SIGNAL(finished()), thread, SLOT(deleteLater()));
  connect(checkLocations, SIGNAL(msg(QString)), this, SLOT(on_msg(QString)));
  thread->start();
 }

 CheckLocations::CheckLocations(TrackDestinationEditFrame* frame)
 {
  this->frame = frame;
 }

 void CheckLocations::process()
 {
  if(frame->checkLocationsLoop())
  {
   emit msg(tr("No problems found with destinations"));
  }
  frame->checkDestinationsButton->setEnabled(true);
  emit finished();
 }

 void TrackDestinationEditFrame::on_msg(QString msg)
 {
  QMessageBox::information(this, tr("Information"), msg);
 }

 /*private*/ bool TrackDestinationEditFrame::checkLocationsLoop() {
     bool noIssues = true;
     foreach (Location* destination, locationManager->getLocationsByNameList()) {
         if (_track->acceptsDestination(destination)) {
             log->debug(tr("Track (%1) accepts destination (%2)").arg(_track->getName()).arg(destination->getName()));
             //                text->setText("Destination : " + destination.getName());
             //                statusFrame.revalidate();
             //                statusFrame.repaint();
             if (_track->getLocation() == destination) {
                 continue;
             }
             // now check to see if the track's rolling stock is accepted by the destination
             checkTypes: foreach (QString type, ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getNames()) {
                 if (!_track->acceptsTypeName(type)) {
                     continue;
                 }
                 if (!destination->acceptsTypeName(type)) {
                     noIssues = false;
//                     int response = JOptionPane.showConfirmDialog(this,
//                             tr("WarningDestinationCarType"), new Object[]{
//                                     destination.getName(), type}), tr("WarningCarMayNotMove"),
//                             JOptionPane.OK_CANCEL_OPTION);
                     int response = QMessageBox::question(this, tr("Car may not reach destination!"), tr("Warning destination (%1) does not service car type (%2)").arg(destination->getName()).arg(type), QMessageBox::Ok | QMessageBox::Cancel);
                     if (response == QMessageBox::Ok)
                         continue;
                     return false; // done
                 }
                 // now determine if there's a track willing to service car type
                 foreach (Track* track, destination->getTrackList()) {
                     if (track->acceptsTypeName(type)) {
                         //continue checkTypes; // yes there's a track
                     }
                 }
                 noIssues = false;
//                 int response = JOptionPane.showConfirmDialog(this, MessageFormat
//                         .format(tr("WarningDestinationTrackCarType"), new Object[]{
//                                 destination.getName(), type}), tr("WarningCarMayNotMove"),
//                         JOptionPane.OK_CANCEL_OPTION);
                 int response = QMessageBox::question(this, tr("Car may not reach destination!"), tr("Warning! Couldn''t find a track at (%1) that can service car type (%2)").arg(destination->getName()).arg(type), QMessageBox::Ok | QMessageBox::Cancel);
                 if (response == QMessageBox::Ok)
                     continue;
                 return false; // done
             }
             // now check road names
             checkRoads: foreach (QString road, ((CarRoads*)InstanceManager::getDefault("Operations::CarRoads"))->getNames())
             {
              if (!_track->acceptsRoadName(road))
              {
                  continue;
              }
              // now determine if there's a track willing to service this road
              bool _continue = true;
              foreach (Track* track, destination->getTrackList())
              {
               if (track->acceptsRoadName(road))
               {
                   //continue checkRoads; // yes there's a track
                _continue = false;
                break;
               }
              }
              if(_continue)
               continue;
              noIssues = false;
//              int response = JOptionPane.showConfirmDialog(this, MessageFormat
//                      .format(tr("WarningDestinationTrackCarRoad"), new Object[]{
//                              destination.getName(), road}), tr("WarningCarMayNotMove"),
//                      JOptionPane.OK_CANCEL_OPTION);
              int response = QMessageBox::question(this, tr("Car may not reach destination!").arg(destination->getName()).arg(road), tr("Warning! Couldn''t find a track at (%1) that can service car road (%2)"), QMessageBox::Ok | QMessageBox::Cancel);
              if (response == QMessageBox::Ok)
                  continue;
              return false; // done
             }
             // now check load names
             foreach (QString type, ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getNames()) {
                 if (!_track->acceptsTypeName(type)) {
                     continue;
                 }
                 QList<QString> loads = ((CarLoads*)InstanceManager::getDefault("Operations::CarLoads"))->getNames(type);
                 checkLoads: foreach (QString load, loads) {
                     if (!_track->acceptsLoadName(load)) {
                         continue;
                     }
                     // now determine if there's a track willing to service this load
                     bool _continue = true;
                     foreach (Track* track, destination->getTrackList())
                     {
                         if (track->acceptsLoadName(load)) {
                             //continue checkLoads;
                          _continue = false;
                          break;
                         }

                     }
                     if(_continue)
                      continue;
//                     noIssues = false;
//                     int response = JOptionPane.showConfirmDialog(this, MessageFormat.format(Bundle
//                             .getMessage("WarningDestinationTrackCarLoad"), new Object[]{destination.getName(),
//                             type, load}), tr("WarningCarMayNotMove"), JOptionPane.OK_CANCEL_OPTION);
                     int response = QMessageBox::question(this, tr("Car may not reach destination!"), tr("Warning! Couldn't find a track at (%1) that can service car type (%2) and load (%3)").arg(destination->getName()).arg(type).arg(load),QMessageBox::Ok| QMessageBox::Cancel);
                     if (response == QMessageBox::Ok)
                         continue;
                     return false; // done
                 }
                 // now check car type and load combinations
                 checkLoads1: foreach (QString load, loads) {
                     if (!_track->acceptsLoad(load, type)) {
                         continue;
                     }
                     // now determine if there's a track willing to service this load
                     bool __continue = true;
                     foreach (Track* track, destination->getTrackList()) {
                         if (track->acceptsLoad(load, type)) {
                             //continue checkLoads;
                          __continue = false;
                          break;
                         }
                     }
                     if(__continue)
                      continue;
                     noIssues = false;
//                     int response = JOptionPane.showConfirmDialog(this, MessageFormat.format(Bundle
//                             .getMessage("WarningDestinationTrackCarLoad"), new Object[]{destination.getName(),
//                             type, load}), tr("WarningCarMayNotMove"), JOptionPane.OK_CANCEL_OPTION);
                     int response = QMessageBox::question(this, tr("Car may not reach destination!"), tr("Warning! Couldn't find a track at (%1) that can service car type (%2) and load (%3)").arg(destination->getName()).arg(type).arg(load),QMessageBox::Ok| QMessageBox::Cancel);
                     if (response == QMessageBox::Ok)
                         continue;
                     return false; // done
                 }
             }
             // now determine if there's a train or trains that can move a car from this track to the destinations
             // need to check all car types, loads, and roads that this track services
             Car* car = new Car();
             car->setLength(QString::number(-RollingStock::COUPLER)); // set car length to net out to zero
             foreach (QString type, ((CarTypes*)InstanceManager::getDefault("CarTypes"))->getNames()) {
                 if (!_track->acceptsTypeName(type)) {
                     continue;
                 }
                 QStringList loads = ((CarLoads*)InstanceManager::getDefault("Operations::CarLoads"))->getNames(type);
                 foreach (QString load, loads) {
                     if (!_track->acceptsLoad(load, type)) {
                         continue;
                     }
                     foreach (QString road, ((CarRoads*)InstanceManager::getDefault("Operations::CarRoads"))->getNames()) {
                         if (!_track->acceptsRoadName(road)) {
                             continue;
                         }
                         // is there a car with this road?
                         bool foundCar = false;
                         foreach (RollingStock* rs, *((CarManager*)InstanceManager::getDefault("Operations::CarManager"))->getList()) {
                             if (rs->getTypeName()==(type) && rs->getRoadName()==(road)) {
                                 foundCar = true;
                                 break;
                             }
                         }
                         if (!foundCar) {
                             continue; // no car with this road name
                         }

                         car->setTypeName(type);
                         car->setRoadName(road);
                         car->setLoadName(load);
                         car->setTrack(_track);
                         car->setFinalDestination(destination);

                         // does the destination accept this car?
                         // this checks tracks that have schedules
                         QString testDest = "";
                         foreach (Track* track, destination->getTrackList()) {
                             if (track->getScheduleMode() == Track::SEQUENTIAL) {
                                 // must test in match mode
                                 track->setScheduleMode(Track::MATCH);
                                 QString itemId = track->getScheduleItemId();
                                 testDest = car->testDestination(destination, track);
                                 track->setScheduleMode(Track::SEQUENTIAL);
                                 track->setScheduleItemId(itemId);
                             } else {
                                 testDest = car->testDestination(destination, track);
                             }
                             if (testDest==(Track::OKAY)) {
                                 break; // done
                             }
                         }

                         if (testDest!=(Track::OKAY)) {
                             noIssues = false;
//                             int response = JOptionPane.showConfirmDialog(this, MessageFormat.format(Bundle
//                                     .getMessage("WarningNoTrack"), new Object[]{destination.getName(), type, road, load,
//                                     destination.getName()}), tr("WarningCarMayNotMove"),
//                                     JOptionPane.OK_CANCEL_OPTION);
                             int response = QMessageBox::question(this, tr("Car may not reach destination!"), tr("Warning! Location (%1) doesn't have a track that can service car type (%2) road (%3), load (%4)").arg(destination->getName()).arg(type).arg(road).arg(load),QMessageBox::Ok| QMessageBox::Cancel);

                             if (response == QMessageBox::Yes)
                                 continue;
                             return false; // done
                         }

                         log->debug(tr("Find train for car type (%1), road (%2), load (%3)").arg(type).arg(road).arg(load));

                         bool results = Router::instance()->setDestination(car, NULL, NULL);
                         car->setDestination(NULL, NULL); // clear destination if set by router
                         if (!results) {
                             noIssues = false;
//                             int response = JOptionPane.showConfirmDialog(this, MessageFormat.format(Bundle
//                                     .getMessage("WarningNoTrain"), new Object[]{type, road, load,
//                                     destination.getName()}), tr("WarningCarMayNotMove"),
//                                     JOptionPane.OK_CANCEL_OPTION);
                             int response = QMessageBox::question(this, tr("Car may not reach destination!"), tr("Warning! Couldn''t find train(s) able to service car type (%1) road (%2), load (%3) to (%4)").arg(type).arg(road).arg(load).arg(destination->getName()),QMessageBox::Ok| QMessageBox::Cancel);
                             if (response == QMessageBox::Ok)
                                 continue;
                             return false; // done
                         }
                         // TODO need to check owners and car built dates
                     }
                 }
             }
         }
     }
     return noIssues;
 }

 /*public*/ void TrackDestinationEditFrame::dispose() {
     if (_track != NULL) {
      _track->removePropertyChangeListener(this);
     }
     //locationManager.removePropertyChangeListener(this);
     disconnect(locationManager, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
     OperationsFrame::dispose();
 }

 /*public*/ void TrackDestinationEditFrame::propertyChange(PropertyChangeEvent* e) {
     if (Control::SHOW_PROPERTY) {
         log->debug(tr("Property change: (%1) old: (%2) new: (%3)").arg(e->getPropertyName()).arg(e->getOldValue().toString()).arg(e
                 ->getNewValue().toString()));
     }
     if (e->getPropertyName()==(LocationManager::LISTLENGTH_CHANGED_PROPERTY)) {
         updateDestinations();
     }
 }
 /*public*/ QString TrackDestinationEditFrame::getClassName()
 {
  return "jmri.jmrit.operations.locations.tools.TrackDestinationEditFrame";
 }

}
