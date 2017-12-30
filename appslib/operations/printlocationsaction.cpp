#include "printlocationsaction.h"
#include "locationmanager.h"
#include "hardcopywriter.h"
#include "jframe.h"
#include "location.h"
#include "track.h"
#include "setup.h"
#include "control.h"
#include <QCheckBox>
#include <QPushButton>
#include "cartypes.h"
#include "enginetypes.h"
#include "carmanager.h"
#include "schedule.h"
#include "schedulemanager.h"
#include "rollingstock.h"
#include "logger.h"
#include "trainmanager.h"
#include "train.h"
#include "routemanager.h"
#include "route.h"
#include <QGroupBox>
#include <gridbaglayout.h>
#include <QBoxLayout>

namespace Operations
{
 /**
  * Action to print a summary of the Location* Roster contents
  * <P>
  * This uses the older style printing, for compatibility with Java 1.1.8 in
  * Macintosh MRJ
  *
  * @author Bob Jacobsen Copyright (C) 2003
  * @author Dennis Miller Copyright (C) 2005
  * @author Daniel Boudreau Copyright (C) 2008, 2011, 2012, 2014
  * @version $Revision: 28797 $
  */
 ///*public*/ class PrintLocationsAction extends AbstractAction {

 /**
  *
  */
 ///*private*/ static final long serialVersionUID = 3978269721157121891L;
 /*static*/ /*final*/ QString PrintLocationsAction::NEW_LINE = "\n"; // NOI18N
 /*static*/ /*final*/ QString PrintLocationsAction::FORM_FEED = "\f"; // NOI18N
 /*static*/ /*final*/ QString PrintLocationsAction::TAB = "\t"; // NOI18N
 /*static*/ /*final*/ int PrintLocationsAction::TAB_LENGTH = 10;
 /*static*/ /*final*/ QString PrintLocationsAction::SPACE = "   ";

 /*static*/ /*final*/ int PrintLocationsAction::MAX_NAME_LENGTH = Control::max_len_string_location_name;


 /*public*/ PrintLocationsAction::PrintLocationsAction(QString actionName, bool isPreview, QObject* parent)
 : AbstractAction(actionName, parent)
 {
     //super(actionName);
  common();
  _isPreview = isPreview;
 }

 /*public*/ PrintLocationsAction::PrintLocationsAction(QString actionName, bool isPreview, Location* location, QObject* parent)
 : AbstractAction(actionName, parent)
 {
  //super(actionName);
  common();
  _isPreview = isPreview;
  _location = location;
 }

 void PrintLocationsAction::common()
 {
  log = new Logger("PrintLocationsAction");
  _printLocations = new QCheckBox(tr("Print Locations"));
  printSchedules = new QCheckBox(tr("Print Schedules"));
  printComments = new QCheckBox(tr("Print Comments"));
  printDetails = new QCheckBox(tr("Print Details"));
  printAnalysis = new QCheckBox(tr("Print Analysis"));

  okayButton = new QPushButton(tr("Ok"));
  charactersPerLine = 70;
  showStaging = false;
  lpof = NULL;
  _location = NULL;

  connect(this, SIGNAL(triggered()), this, SLOT(actionPerformed()));

 }

 /*public*/ void PrintLocationsAction::actionPerformed(ActionEvent* /*e*/) {
     if (lpof == NULL) {
         lpof = new LocationPrintOptionFrame(this);
     } else {
         lpof->setVisible(true);
     }
     lpof->initComponents();
 }


 /*public*/ void PrintLocationsAction::printLocations() {
     // obtain a HardcopyWriter
     QString title = tr("Locations Table");
     if (_location != NULL) {
         title = _location->getName();
     }
     //try {
         writer = new HardcopyWriter(new JFrame(), title, Control::reportFontSize, .5, .5, .5, .5, _isPreview);
//     } catch (HardcopyWriter.PrintCanceledException ex) {
//         log->debug("Print cancelled");
//         return;
//     }

     charactersPerLine = writer->getCharactersPerLine();

     //try {
         // print locations?
         if (_printLocations->isChecked()) {
             printLocationsSelected();
         }
         // print schedules?
         if (printSchedules->isChecked()) {
             printSchedulesSelected();
         }
         if (printComments->isChecked()) {
             printCommentsSelected();
         }
         // print detailed report?
         if (printDetails->isChecked()) {
             printDetailsSelected();
         }
         // print analysis?
         if (printAnalysis->isChecked()) {
             printAnalysisSelected();
         }
         // prevent NPE on close
         if (_printLocations->isChecked() || printSchedules->isChecked() || printComments->isChecked()
                 || printDetails->isChecked() || printAnalysis->isChecked()) // force completion of the printing
         {
             writer->close();
         }
//     } catch (IOException we) {
//         log->error("Error printing PrintLocationAction: " + we);
//     }
 }

 // Loop through the Roster, printing as needed
 /*private*/ void PrintLocationsAction::printLocationsSelected() //throws IOException
 {
     QList<Location*> locations = manager->getLocationsByNameList();
     int totalLength = 0;
     int usedLength = 0;
     int numberRS = 0;
     int numberCars = 0;
     int numberEngines = 0;
     // header
     QString s = tr("Location") + TAB + TAB + TAB + tr("Length") + " "
             + tr("Used") + TAB + tr("RS") + TAB + tr("Cars") + TAB
             + tr("Engines") + TAB + tr("Pickups") + " " + tr("Drop")
             + NEW_LINE;
     writer->write(s);
     foreach (Location* location, locations) {
         if (_location != NULL && location != _location) {
             continue;
         }
         // location name, track length, used, number of RS, scheduled pick ups and drops
         s = padOutString(location->getName(), Control::max_len_string_location_name) + TAB + "  "
                 + QString::number(location->getLength()) + TAB + QString::number(location->getUsedLength()) + TAB
                 + QString::number(location->getNumberRS()) + TAB + QString::number(location->getNumberCars()) + TAB
                 + QString::number(location->getNumberEngines()) + TAB + QString::number(location->getPickupRS())
                 + TAB + QString::number(location->getDropRS()) + NEW_LINE;
         writer->write(s);

         totalLength += location->getLength();
         usedLength += location->getUsedLength();
         numberRS += location->getNumberRS();

         QList<Track*> yards = location->getTrackByNameList(Track::YARD);
         if (yards.size() > 0) {
             // header
             writer->write(SPACE + tr("YardName") + NEW_LINE);
             foreach (Track* yard, yards) {
                 writer->write(getTrackString(yard));
                 numberCars += yard->getNumberCars();
                 numberEngines += yard->getNumberEngines();
             }
         }

         QList<Track*> spurs = location->getTrackByNameList(Track::SPUR);
         if (spurs.size() > 0) {
             // header
             writer->write(SPACE + tr("SpurName") + NEW_LINE);
             foreach (Track* spur, spurs) {
                 writer->write(getTrackString(spur));
                 numberCars += spur->getNumberCars();
                 numberEngines += spur->getNumberEngines();
             }
         }

         QList<Track*> interchanges = location->getTrackByNameList(Track::INTERCHANGE);
         if (interchanges.size() > 0) {
             // header
             writer->write(SPACE + tr("InterchangeName") + NEW_LINE);
             foreach (Track* interchange, interchanges) {
                 writer->write(getTrackString(interchange));
                 numberCars += interchange->getNumberCars();
                 numberEngines += interchange->getNumberEngines();
             }
         }

         QList<Track*> stagingTracks = location->getTrackByNameList(Track::STAGING);
         if (stagingTracks.size() > 0) {
             // header
             writer->write(SPACE + tr("StagingName") + NEW_LINE);
             foreach (Track* staging, stagingTracks) {
                 writer->write(getTrackString(staging));
                 numberCars += staging->getNumberCars();
                 numberEngines += staging->getNumberEngines();
             }
         }
         writer->write(NEW_LINE);
     }

     // summary
     s = tr("Total length %1, total used %2, percentage used %3%").arg(QString::number(totalLength)).arg(
         QString::number(usedLength)).arg(QString::number(usedLength * 100 / totalLength))
             + NEW_LINE;
     writer->write(s);
     s = tr("Total rolling stock %1, number of cars %2, number of locomotives %3").arg(QString::number(numberRS),
         QString::number(numberCars), QString::number(numberEngines))
             + NEW_LINE;
     writer->write(s);
     // are there trains en route, then some cars and engines not counted!
     if (numberRS != numberCars + numberEngines) {
         s = tr("Note: %1 locomotives and/or cars are en route, or don''t have track assignments!").arg(QString::number(numberRS
             - (numberCars + numberEngines)))
                 + NEW_LINE;
         writer->write(s);
     }
     if (printSchedules->isChecked() || printComments->isChecked() || printDetails->isChecked()
             || printAnalysis->isChecked()) {
         writer->write(FORM_FEED);
     }
 }

 /*private*/ void PrintLocationsAction::printSchedulesSelected() //throws IOException
 {
     QList<Location*> locations = manager->getLocationsByNameList();
     QString s = padOutString(tr("Schedules"), MAX_NAME_LENGTH) + " " + tr("Location")
             + " - " + tr("SpurName") + NEW_LINE;
     writer->write(s);
     QList<Schedule*> schedules = ScheduleManager::instance()->getSchedulesByNameList();
     foreach (Schedule* schedule, schedules) {
         foreach (Location* location, locations) {
             if (_location != NULL && location != _location) {
                 continue;
             }
             QList<Track*> spurs = location->getTrackByNameList(Track::SPUR);
             foreach (Track* spur, spurs) {
                 if (spur->getScheduleId()==(schedule->getId())) {
                     // pad out schedule name
                     s = padOutString(schedule->getName(), MAX_NAME_LENGTH) + " " + location->getName() + " - "
                             + spur->getName();
                     QString status = spur->checkScheduleValid();
                     if (status!=(Track::SCHEDULE_OKAY)) {
                         QString buf = QString(s);
                         for (int m = s.length(); m < 63; m++) {
                             buf.append(" ");
                         }
                         s = buf/*.toString()*/;
                         if (s.length() > 63) {
                             s = s.mid(0, 63);
                         }
                         s = s + TAB + status;
                     }
                     s = s + NEW_LINE;
                     writer->write(s);
                     // show the schedule's mode
                     QString mode = tr("Sequential");
                     if (spur->getScheduleMode() == Track::MATCH) {
                         mode = tr("Match");
                     }
                     s = padOutString("", MAX_NAME_LENGTH) + SPACE + tr("ScheduleMode") + ": " + mode
                             + NEW_LINE;
                     writer->write(s);
                     // show alternate track if there's one
                     if (spur->getAlternateTrack() != NULL) {
                         s = padOutString("", MAX_NAME_LENGTH)
                                 + SPACE
                                 + tr("Alternate track: %1").arg(spur
                                     ->getAlternateTrack()->getName()) + NEW_LINE;
                         writer->write(s);
                     }
                     // show custom loads from staging if not 100%
                     if (spur->getReservationFactor() != 100) {
                         s = padOutString("", MAX_NAME_LENGTH)
                                 + SPACE
                                 + tr("Percentage custom loads from staging: %1").arg(spur
                                     ->getReservationFactor()) + NEW_LINE;
                         writer->write(s);
                     }
                 }
             }
         }
     }
     if (printComments->isChecked() || printDetails->isChecked() || printAnalysis->isChecked()) {
         writer->write(FORM_FEED);
     }
 }

 /*private*/ void PrintLocationsAction::printCommentsSelected() //throws IOException
 {
     QString s = tr("PrintComments") + NEW_LINE + NEW_LINE;
     writer->write(s);
     QList<Location*> locations = manager->getLocationsByNameList();
     foreach (Location* location, locations) {
         if (_location != NULL && location != _location) {
             continue;
         }
         s = location->getName() + NEW_LINE;
         writer->write(s);
         s = SPACE + location->getComment() + NEW_LINE;
         writer->write(s);
         foreach (Track* track, location->getTrackByNameList(NULL)) {
             if (track->getComment()!=(Track::NONE) || track->getCommentBoth()!=(Track::NONE) || track->getCommentPickup()!=(Track::NONE)
                     || track->getCommentSetout()!=(Track::NONE)) {
                 s = SPACE + track->getName() + NEW_LINE;
                 writer->write(s);
                 if (track->getComment()!=(Track::NONE)) {
                     s = SPACE + SPACE + track->getComment() + NEW_LINE;
                     writer->write(s);
                 }
                 if (track->getCommentBoth()!=(Track::NONE)) {
                     s = SPACE + SPACE + tr("CommentBoth") + ":" + NEW_LINE;
                     writer->write(s);
                     s = SPACE + SPACE + track->getCommentBoth() + NEW_LINE;
                     writer->write(s);
                 }
                 if (track->getCommentPickup()!=(Track::NONE)) {
                     s = SPACE + SPACE + tr("CommentPickup") + ":" + NEW_LINE;
                     writer->write(s);
                     s = SPACE + SPACE + track->getCommentPickup() + NEW_LINE;
                     writer->write(s);
                 }
                 if (track->getCommentSetout()!=(Track::NONE)) {
                     s = SPACE + SPACE + tr("CommentSetout") + ":" + NEW_LINE;
                     writer->write(s);
                     s = SPACE + SPACE + track->getCommentSetout() + NEW_LINE;
                     writer->write(s);
                 }
             }
         }
     }
     if (printDetails->isChecked() || printAnalysis->isChecked()) {
         writer->write(FORM_FEED);
     }
 }

 /*private*/ void PrintLocationsAction::printDetailsSelected() //throws IOException
 {
     QList<Location*> locations = manager->getLocationsByNameList();
     QString s = tr("DetailedReport") + NEW_LINE;
     writer->write(s);
     foreach (Location* location, locations) {
         if (_location != NULL && location != _location) {
             continue;
         }
         QString name = location->getName();
         // services train direction
         int dir = location->getTrainDirections();
         s = NEW_LINE + name + getDirection(dir);
         writer->write(s);
         // services car and engine types
         s = getLocationTypes(location);
         writer->write(s);

         QList<Track*> yards = location->getTrackByNameList(Track::YARD);
         if (yards.size() > 0) {
             s = SPACE + tr("YardName") + NEW_LINE;
             writer->write(s);
             printTrackInfo(location, yards);
         }

         QList<Track*> spurs = location->getTrackByNameList(Track::SPUR);
         if (spurs.size() > 0) {
             s = SPACE + tr("SpurName") + NEW_LINE;
             writer->write(s);
             printTrackInfo(location, spurs);
         }

         QList<Track*> interchanges = location->getTrackByNameList(Track::INTERCHANGE);
         if (interchanges.size() > 0) {
             s = SPACE + tr("InterchangeName") + NEW_LINE;
             writer->write(s);
             printTrackInfo(location, interchanges);
         }

         QList<Track*> stagings = location->getTrackByNameList(Track::STAGING);
         if (stagings.size() > 0) {
             s = SPACE + tr("StagingName") + NEW_LINE;
             writer->write(s);
             printTrackInfo(location, stagings);
         }
     }
     if (printAnalysis->isChecked()) {
         writer->write(FORM_FEED);
     }
 }


 /*private*/ void PrintLocationsAction::printAnalysisSelected() //throws IOException
 {
     CarManager* carManager = CarManager::instance();
     QList<Location*> locations = manager->getLocationsByNameList();
     QList<RollingStock*>* cars = carManager->getByLocationList();
     QStringList carTypes = CarTypes::instance()->getNames();

     QString s = tr("Track Analysis") + NEW_LINE;
     writer->write(s);

     // print the car type being analyzed
     foreach(QString type, carTypes) {
         // get the total length for a given car type
         int numberOfCars = 0;
         int totalTrackLength = 0;
         foreach (RollingStock* car, *cars) {
             if (car->getTypeName()==(type) && car->getLocation() != NULL) {
                 numberOfCars++;
                 totalTrackLength += car->getTotalLength();
             }
         }
         writer->write(tr("%1 %2 total length %3 %4").arg(numberOfCars).arg(type).arg(
             totalTrackLength).arg(Setup::getLengthUnit().toLower())
                 + NEW_LINE);
         // don't bother reporting when the number of cars for a given type is zero
         if (numberOfCars > 0) {
             // spurs
             writer->write(SPACE
                     + tr("Spur tracks that accept car type %1:").arg(type)
                     + NEW_LINE);
             int trackLength = getTrackLengthAcceptType(locations, type, Track::SPUR);
             if (trackLength > 0) {
                 writer->write(SPACE
                         + tr("Spurs that accept type %1 %2 %3 percentage used %4%").arg(type).arg(
                             trackLength).arg(Setup::getLengthUnit().toLower()).arg(100 * totalTrackLength / trackLength) + NEW_LINE);
             } else {
                 writer->write(SPACE + tr("None") + NEW_LINE);
             }
             // yards
             writer->write(SPACE
                     + tr("Yard tracks that accept car type %1:").arg(type)
                     + NEW_LINE);
             trackLength = getTrackLengthAcceptType(locations, type, Track::YARD);
             if (trackLength > 0) {
                 writer->write(SPACE
                         + tr("Yards that accept type %1 %2 %3 percentage used %4%").arg(type).arg(
                             trackLength).arg(Setup::getLengthUnit().toLower()).arg(100 * totalTrackLength / trackLength) + NEW_LINE);
             } else {
                 writer->write(SPACE + tr("None") + NEW_LINE);
             }
             // interchanges
             writer->write(SPACE
                     + tr("Classification/Interchange tracks that accept car type %1:").arg(type)
                     + NEW_LINE);
             trackLength = getTrackLengthAcceptType(locations, type, Track::INTERCHANGE);
             if (trackLength > 0) {
                 writer->write(SPACE
                         + tr("C/I that accept type %1 %2 %3 percentage used %4%").arg(type,
                             trackLength).arg(Setup::getLengthUnit().toLower()).arg(100 * totalTrackLength / trackLength) + NEW_LINE);
             } else {
                 writer->write(SPACE + tr("None") + NEW_LINE);
             }
             // staging
             if (showStaging) {
                 writer->write(SPACE
                         + tr("Stage tracks that accept car type %1:").arg(type)
                         + NEW_LINE);
                 trackLength = getTrackLengthAcceptType(locations, type, Track::STAGING);
                 if (trackLength > 0) {
                     writer->write(SPACE
                             + tr("Staging that accept type %1 %2 %3 percentage used %4%").arg(type,
                                 trackLength).arg(Setup::getLengthUnit().toLower()).arg(100 * totalTrackLength / trackLength) + NEW_LINE);
                 } else {
                     writer->write(SPACE + tr("None") + NEW_LINE);
                 }
             }
         }
     }
 }

 /*private*/ int PrintLocationsAction::getTrackLengthAcceptType(QList<Location*> locations, QString carType, QString trackType) //throws IOException
 {
     int trackLength = 0;
     foreach (Location* location, locations) {
         if (_location != NULL && location != _location) {
             continue;
         }
         QList<Track*> tracks = location->getTrackByNameList(trackType);
         foreach (Track* track, tracks) {
             if (track->acceptsTypeName(carType)) {
                 trackLength = trackLength + track->getLength();
                 writer->write(SPACE
                         + SPACE
                         + tr("%1, %2 length %3 %4").arg(
                             location->getName()).arg(track->getName()).arg(track->getLength()).arg(Setup::getLengthUnit().toLower()) + NEW_LINE);
             }
         }
     }
     return trackLength;
 }

 /*private*/ QString PrintLocationsAction::getTrackString(Track* track) {
     QString s = TAB + padOutString(track->getName(), Control::max_len_string_track_name) + " "
             + QString::number(track->getLength()) + TAB + QString::number(track->getUsedLength()) + TAB
             + QString::number(track->getNumberRS()) + TAB + QString::number(track->getNumberCars()) + TAB
             + QString::number(track->getNumberEngines()) + TAB + QString::number(track->getPickupRS()) + TAB
             + QString::number(track->getDropRS()) + NEW_LINE;
     return s;
 }

 /*private*/ QString PrintLocationsAction::getDirection(int dir) {
     if ((Setup::getTrainDirection() & dir) == 0) {
         return " " + tr("LocalOnly") + NEW_LINE;
     }
     QString direction = " " + tr("ServicedByTrain") + " ";
     if ((Setup::getTrainDirection() & dir & Location::NORTH) > 0) {
         direction = direction + tr("North") + " ";
     }
     if ((Setup::getTrainDirection() & dir & Location::SOUTH) > 0) {
         direction = direction + tr("South") + " ";
     }
     if ((Setup::getTrainDirection() & dir & Location::EAST) > 0) {
         direction = direction + tr("East") + " ";
     }
     if ((Setup::getTrainDirection() & dir & Location::WEST) > 0) {
         direction = direction + tr("West") + " ";
     }
     direction = direction + NEW_LINE;
     return direction;
 }

 /*private*/ void PrintLocationsAction::printTrackInfo(Location* location, QList<Track*> tracks) {
     foreach (Track* track, tracks) {
         //try {
             QString s = TAB + track->getName() + getDirection(location->getTrainDirections() & track->getTrainDirections());
             writer->write(s);
             writer->write(getTrackTypes(location, track));
             writer->write(getTrackRoads(track));
             writer->write(getTrackLoads(track));
             writer->write(getTrackShipLoads(track));
             writer->write(getCarOrder(track));
             writer->write(getSetOutTrains(track));
             writer->write(getPickUpTrains(track));
             writer->write(getDestinations(track));
             writer->write(getSchedule(track));
//         } catch (IOException we) {
//             log->error("Error printing PrintLocationAction: " + we);
//         }
     }
 }



 /*private*/ QString PrintLocationsAction::getLocationTypes(Location* location) {
     QString buf = QString(TAB + TAB + tr("TypesServiced") + NEW_LINE + TAB + TAB);
     int charCount = 0;
     int typeCount = 0;

     foreach (QString type, CarTypes::instance()->getNames()) {
         if (location->acceptsTypeName(type)) {
             typeCount++;
             charCount += type.length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = type.length() + 2;
             }
             buf.append(type + ", ");
         }
     }

     foreach (QString type, EngineTypes::instance()->getNames()) {
         if (location->acceptsTypeName(type)) {
             typeCount++;
             charCount += type.length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = type.length() + 2;
             }
             buf.append(type + ", ");
         }
     }
     if (buf.length() > 2) {
         //buf = buf.mid(0, buf.length() - 2); // remove trailing separators
      buf = buf.mid(0, buf.length() - 2);
     }		// does this location accept all types?
     if (typeCount == CarTypes::instance()->getNames().length() + EngineTypes::instance()->getNames().length()) {
         buf = QString(TAB + TAB + tr("LocationAcceptsAllTypes"));
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getTrackTypes(Location* location, Track* track) {
     QString buf = QString(TAB + TAB + tr("TypesServicedTrack") + NEW_LINE + TAB + TAB);
     int charCount = 0;
     int typeCount = 0;

     foreach(QString type, CarTypes::instance()->getNames()) {
         if (track->acceptsTypeName(type)) {
             typeCount++;
             charCount += type.length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = type.length() + 2;
             }
             buf.append(type + ", ");
         }
     }

     foreach(QString type, EngineTypes::instance()->getNames()) {
         if (track->acceptsTypeName(type)) {
             typeCount++;
             charCount += type.length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = type.length() + 2;
             }
             buf.append(type + ", ");
         }
     }
     if (buf.length() > 2) {
         //buf = buf.mid(0, buf.length() - 2); // remove trailing separators
      buf = buf.mid(0,buf.length()-2);
     }		// does this track accept all types?
     if (typeCount == CarTypes::instance()->getNames().length() + EngineTypes::instance()->getNames().length()) {
         buf = QString(TAB + TAB + tr("TrackAcceptsAllTypes"));
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getTrackRoads(Track* track) {
     if (track->getRoadOption()==(Track::ALL_ROADS)) {
         return TAB + TAB + tr("AcceptsAllRoads") + NEW_LINE;
     }

     QString op = tr("RoadsServicedTrack");
     if (track->getRoadOption()==(Track::EXCLUDE_ROADS)) {
         op = tr("ExcludeRoadsTrack");
     }

     QString buf = QString(TAB + TAB + op + NEW_LINE + TAB + TAB);
     int charCount = 0;

     foreach (QString road, track->getRoadNames()) {
         charCount += road.length() + 2;
         if (charCount > charactersPerLine - 2*TAB_LENGTH) {
             buf.append(NEW_LINE + TAB + TAB);
             charCount = road.length() + 2;
         }
         buf.append(road + ", ");
     }
     if (buf.length() > 2) {
         buf = buf.mid(0, buf.length() - 2); // remove trailing separators
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getTrackLoads(Track* track) {
     if (track->getLoadOption()==(Track::ALL_LOADS)) {
         return TAB + TAB + tr("Track accepts all loads") + NEW_LINE;
     }

     QString op = tr("LoadsServicedTrack");
     if (track->getLoadOption()==(Track::EXCLUDE_LOADS)) {
         op = tr("Loads NOT serviced by this track:");
     }

     QString buf = QString(TAB + TAB + op + NEW_LINE + TAB + TAB);
     int charCount = 0;

     foreach(QString load, track->getLoadNames()) {
         charCount += load.length() + 2;
         if (charCount > charactersPerLine - 2*TAB_LENGTH) {
             buf.append(NEW_LINE + TAB + TAB);
             charCount = load.length() + 2;
         }
         buf.append(load + ", ");
     }
     if (buf.length() > 2) {
         buf = buf.mid(0, buf.length() - 2); // remove trailing separators
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getTrackShipLoads(Track* track) {
     // only staging has the ship load control
     if (track->getTrackType()!=(Track::STAGING)) {
         return "";
     }
     if (track->getShipLoadOption()==(Track::ALL_LOADS)) {
         return TAB + TAB + tr("ShipsAllLoads") + NEW_LINE;
     }
     QString op = tr("LoadsShippedTrack");
     if (track->getShipLoadOption()==(Track::EXCLUDE_LOADS)) {
         op = tr("ExcludeLoadsShippedTrack");
     }

     QString buf = QString(TAB + TAB + op + NEW_LINE + TAB + TAB);
     int charCount = 0;

     foreach (QString load, track->getShipLoadNames()) {
         charCount += load.length() + 2;
         if (charCount > charactersPerLine - 2*TAB_LENGTH) {
             buf.append(NEW_LINE + TAB + TAB);
             charCount = load.length() + 2;
         }
         buf.append(load + ", ");
     }
     if (buf.length() > 2) {
         buf = buf.mid(0, buf.length() - 2); // remove trailing separators
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getCarOrder(Track* track) {
     // only yards and interchanges have the car order option
     if (track->getTrackType()==(Track::SPUR) || track->getTrackType()==(Track::STAGING)
             || track->getServiceOrder()==(Track::NORMAL)) {
         return "";
     }
     if (track->getServiceOrder()==(Track::FIFO)) {
         return TAB + TAB + tr("TrackPickUpOrderFIFO") + NEW_LINE;
     }
     return TAB + TAB + tr("TrackPickUpOrderLIFO") + NEW_LINE;
 }

 /*private*/ QString PrintLocationsAction::getSetOutTrains(Track* track) {
     if (track->getDropOption()==(Track::ANY)) {
         return TAB + TAB + tr("SetOutAllTrains") + NEW_LINE;
     }
     QString buf;
     int charCount = 0;
     QStringList ids = track->getDropIds();
     if (track->getDropOption()==(Track::TRAINS) || track->getDropOption()==(Track::EXCLUDE_TRAINS)) {
         QString trainType = tr("TrainsSetOutTrack");
         if (track->getDropOption()==(Track::EXCLUDE_TRAINS)) {
             trainType = tr("ExcludeTrainsSetOutTrack");
         }
         buf = QString(TAB + TAB + trainType + NEW_LINE + TAB + TAB);
         foreach (QString id, ids) {
             Train* train = TrainManager::instance()->getTrainById(id);
             if (train == NULL) {
                 log->info("Could not find a train for id: " + id + " track (" + track->getName() + ")");
                 continue;
             }
             charCount += train->getName().length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = train->getName().length() + 2;
             }
             buf.append(train->getName() + ", ");
         }
     } else {
         QString routeType = tr("RoutesSetOutTrack");
         if (track->getDropOption()==(Track::EXCLUDE_ROUTES)) {
             routeType = tr("ExcludeRoutesSetOutTrack");
         }
         buf = QString(TAB + TAB + routeType + NEW_LINE + TAB + TAB);
         foreach(QString id, ids) {
             Route* route = RouteManager::instance()->getRouteById(id);
             if (route == NULL) {
                 log->info("Could not find a route for id: " + id + " location (" + track->getLocation()->getName()
                         + ") track (" + track->getName() + ")"); // NOI18N
                 continue;
             }
             charCount += route->getName().length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = route->getName().length() + 2;
             }
             buf.append(route->getName() + ", ");
         }
     }
     if (buf.length() > 2) {
         buf = buf.mid(0, buf.length() - 2); // remove trailing separators
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getPickUpTrains(Track* track) {
     if (track->getPickupOption()==(Track::ANY)) {
         return TAB + TAB + tr("Any train can pick up cars") + NEW_LINE;
     }
     QString buf;
     int charCount = 0;
     QStringList ids = track->getPickupIds();
     if (track->getPickupOption()==(Track::TRAINS) || track->getPickupOption()==(Track::EXCLUDE_TRAINS)) {
         QString trainType = tr("Trains that can pick up cars from this track:");
         if (track->getPickupOption()==(Track::EXCLUDE_TRAINS)) {
             trainType = tr("Trains that can NOT pick up cars from this track:");
         }
         buf = QString(TAB + TAB + trainType + NEW_LINE + TAB + TAB);
         foreach(QString id, ids) {
             Train* train = TrainManager::instance()->getTrainById(id);
             if (train == NULL) {
                 log->info("Could not find a train for id: " + id + " track (" + track->getName() + ")");
                 continue;
             }
             charCount += train->getName().length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = train->getName().length() + 2;
             }
             buf.append(train->getName() + ", ");
         }
     } else {
         QString routeType = tr("Routes that can pick up cars from this track:");
         if (track->getPickupOption()==(Track::EXCLUDE_ROUTES)) {
             routeType = tr("Routes that can NOT pick up cars from this track:");
         }
         buf = QString(TAB + TAB + routeType + NEW_LINE + TAB + TAB);
         foreach(QString id, ids) {
             Route* route = RouteManager::instance()->getRouteById(id);
             if (route == NULL) {
                 log->info("Could not find a route for id: " + id + " location (" + track->getLocation()->getName()
                         + ") track (" + track->getName() + ")"); // NOI18N
                 continue;
             }
             charCount += route->getName().length() + 2;
             if (charCount > charactersPerLine - 2*TAB_LENGTH) {
                 buf.append(NEW_LINE + TAB + TAB);
                 charCount = route->getName().length() + 2;
             }
             buf.append(route->getName() + ", ");
         }
     }
     if (buf.length() > 2) {
         buf = buf.mid(0, buf.length() - 2); // remove trailing separators
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getDestinations(Track* track) {
     if (track->getDestinationOption()==(Track::ALL_DESTINATIONS)) {
         return "";
     }
     QString op = tr("Accept only") + " " + track->getDestinationListSize() + " "
             + tr("Destinations") + ":";
     if (track->getDestinationOption()==(Track::EXCLUDE_DESTINATIONS)) {
         op = tr("Exclude") + " "
                 + (LocationManager::instance()->getNumberOfLocations() - track->getDestinationListSize()) + " "
                 + tr("Destinations") + ":";
     }
     QString buf = QString(TAB + TAB + op + NEW_LINE + TAB + TAB);
     QStringList destIds = track->getDestinationIds();
     int charCount = 0;
     foreach (QString id, destIds) {
         Location* location = manager->getLocationById(id);
         if (location == NULL) {
             continue;
         }
         charCount += location->getName().length() + 2;
         if (charCount > charactersPerLine - 2*TAB_LENGTH) {
             buf.append(NEW_LINE + TAB + TAB);
             charCount = location->getName().length() + 2;
         }
         buf.append(location->getName() + ", ");
     }
     if (buf.length() > 2) {
         buf = buf.mid(0, buf.length() - 2); // remove trailing separators
     }
     buf.append(NEW_LINE);
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::getSchedule(Track* track) {
     // only spurs have schedules
     if (track->getTrackType()!=(Track::SPUR) || track->getSchedule() == NULL) {
         return "";
     }
     QString buf = QString(TAB
             + TAB
             + tr("Schedule name: %1").arg(track->getScheduleName())
             + NEW_LINE);
     if (track->getAlternateTrack() != NULL) {
         buf.append(TAB
                 + TAB
                 + tr("Alternate track: %1").arg(track
                     ->getAlternateTrack()->getName()) + NEW_LINE);
     }
     if (track->getReservationFactor() != 100) {
         buf.append(TAB
                 + TAB
                 + tr("Percentage custom loads from staging: %1").arg(track
                     ->getReservationFactor()) + NEW_LINE);
     }
     return buf/*.toString()*/;
 }

 /*private*/ QString PrintLocationsAction::padOutString(QString s, int length) {
     QString buf = "";//QString(s);
     for (int n = s.length(); n < length; n++) {
         buf.append(" ");
     }
     return buf/*.toString()*/;
 }


// /*public*/ class LocationPrintOptionFrame extends OperationsFrame {

//     /**
//      *
//      */
//     /*private*/ static /*final*/ long serialVersionUID = -8648671751787189906L;
//     PrintLocationsAction pla;

     /*public*/ LocationPrintOptionFrame::LocationPrintOptionFrame(PrintLocationsAction* pla) {
         //super();
         this->pla = pla;
         // create panel
         QGroupBox* pPanel = new QGroupBox();
         pPanel->setLayout(new GridBagLayout());
         //pPanel.setBorder(BorderFactory.createTitledBorder(tr("PrintOptions")));
         pPanel->setStyleSheet(gbStyleSheet);
         addItemLeft(pPanel, pla->_printLocations, 0, 0);
         addItemLeft(pPanel, pla->printSchedules, 0, 3);
         addItemLeft(pPanel, pla->printComments, 0, 5);
         addItemLeft(pPanel, pla->printDetails, 0, 7);
         addItemLeft(pPanel, pla->printAnalysis, 0, 9);
         // set defaults
         pla->_printLocations->setChecked(true);
         pla->printSchedules->setChecked(true);
         pla->printComments->setChecked(false);
         pla->printDetails->setChecked(false);
         pla->printAnalysis->setChecked(false);

         // add tool tips
         QWidget* pButtons = new QWidget();
         pButtons->setLayout(new GridBagLayout());
         pButtons->layout()->addWidget(pla->okayButton);
         addButtonAction(pla->okayButton);

         //getContentPane().setLayout(new BoxLayout(getContentPane(), BoxLayout.Y_AXIS));
         QVBoxLayout* thisLayout = new QVBoxLayout(getContentPane());
         thisLayout->addWidget(pPanel);
         thisLayout->addWidget(pButtons);
         resize(QSize());
         if (pla->_isPreview) {
             setTitle(tr("Preview"));
         } else {
             setTitle(tr("Print"));
         }
         initMinimumSize(QSize(Control::panelWidth300, Control::panelHeight250));
     }

     /*public*/ void LocationPrintOptionFrame::initComponents() {

     }

     /*public*/ void LocationPrintOptionFrame::buttonActionPerformed(QWidget* /*ae*/) {
         setVisible(false);
         pla->printLocations();
     }
// }:

}
