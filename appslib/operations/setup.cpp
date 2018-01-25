#include "setup.h"
#include "operationssetupxml.h"
#include <QStringList>
#include "control.h"
#include "xml.h"
#include "logger.h"
#include <QComboBox>
#include "appslib_global.h"
#include "autosave.h"
#include "trainmanagerxml.h"
#include "propertychangesupport.h"
#include "abstractoperationsserver.h"
#include <QTextEdit>
namespace Operations
{
 Setup::Setup(QObject *parent) :
   QObject(parent)
 {
  pcs = new PropertyChangeSupport(this);
 }

 /*static*/ Setup* Setup::_instance = NULL;

 /*static*/ Setup* Setup::instance()
 {
  if(_instance == NULL)
  {
   _instance = new Setup();
  }
  return _instance;
 }

 /**
  * Operations settings.
  *
  * @author Daniel Boudreau Copyright (C) 2008, 2010, 2012, 2014
  * @version $Revision: 29666 $
  */
 ///*public*/ class Setup {

 /*public*/  /*static final*/ QString Setup::NONE = "";

 // scale ratios from NMRA
 /*private*/  /*static final*/ int Setup::Setup::Z_RATIO = 220;
 /*private*/  /*static final*/ int Setup::Setup::N_RATIO = 160;
 /*private*/  /*static final*/ int Setup::Setup::TT_RATIO = 120;
 /*private*/  /*static final*/ int Setup::Setup::OO_RATIO = 76; // actual ratio 76.2
 /*private*/  /*static final*/ int Setup::Setup::HO_RATIO = 87;
 /*private*/  /*static final*/ int Setup::Setup::S_RATIO = 64;
 /*private*/  /*static final*/ int Setup::Setup::O_RATIO = 48;
 /*private*/  /*static final*/ int Setup::Setup::G_RATIO = 32; // NMRA #1

 // initial weight in milli ounces from NMRA
 /*private*/  /*static final*/ int Setup::Z_INITIAL_WEIGHT = 364; // not specified by NMRA
 /*private*/  /*static final*/ int Setup::N_INITIAL_WEIGHT = 500;
 /*private*/  /*static final*/ int Setup::TT_INITIAL_WEIGHT = 750;
 /*private*/  /*static final*/ int Setup::HOn3_INITIAL_WEIGHT = 750;
 /*private*/  /*static final*/ int Setup::OO_INITIAL_WEIGHT = 750; // not specified by NMRA
 /*private*/  /*static final*/ int Setup::HO_INITIAL_WEIGHT = 1000;
 /*private*/  /*static final*/ int Setup::Sn3_INITIAL_WEIGHT = 1000;
 /*private*/  /*static final*/ int Setup::S_INITIAL_WEIGHT = 2000;
 /*private*/  /*static final*/ int Setup::On3_INITIAL_WEIGHT = 1500;
 /*private*/  /*static final*/ int Setup::O_INITIAL_WEIGHT = 5000;
 /*private*/  /*static final*/ int Setup::G_INITIAL_WEIGHT = 10000; // not specified by NMRA

 // additional weight in milli ounces from NMRA
 /*private*/  /*static final*/ int Setup::Z_ADD_WEIGHT = 100; // not specified by NMRA
 /*private*/  /*static final*/ int Setup::N_ADD_WEIGHT = 150;
 /*private*/  /*static final*/ int Setup::TT_ADD_WEIGHT = 375;
 /*private*/  /*static final*/ int Setup::HOn3_ADD_WEIGHT = 375;
 /*private*/  /*static final*/ int Setup::OO_ADD_WEIGHT = 500; // not specified by NMRA
 /*private*/  /*static final*/ int Setup::HO_ADD_WEIGHT = 500;
 /*private*/  /*static final*/ int Setup::Sn3_ADD_WEIGHT = 500;
 /*private*/  /*static final*/ int Setup::S_ADD_WEIGHT = 500;
 /*private*/  /*static final*/ int Setup::On3_ADD_WEIGHT = 750;
 /*private*/  /*static final*/ int Setup::O_ADD_WEIGHT = 1000;
 /*private*/  /*static final*/ int Setup::G_ADD_WEIGHT = 2000; // not specified by NMRA

 // actual weight to tons conversion ratios (based on 40' boxcar at ~80 tons)
 /*private*/  /*static final*/ int Setup::Z_RATIO_TONS = 130;
 /*private*/  /*static final*/ int Setup::N_RATIO_TONS = 80;
 /*private*/  /*static final*/ int Setup::TT_RATIO_TONS = 36;
 /*private*/  /*static final*/ int Setup::HOn3_RATIO_TONS = 20;
 /*private*/  /*static final*/ int Setup::OO_RATIO_TONS = 20;
 /*private*/  /*static final*/ int Setup::HO_RATIO_TONS = 20; // 20 tons per ounce
 /*private*/  /*static final*/ int Setup::Sn3_RATIO_TONS = 16;
 /*private*/  /*static final*/ int Setup::S_RATIO_TONS = 14;
 /*private*/  /*static final*/ int Setup::On3_RATIO_TONS = 8;
 /*private*/  /*static final*/ int Setup::O_RATIO_TONS = 5;
 /*private*/  /*static final*/ int Setup::G_RATIO_TONS = 2;

 ///*public*/  /*static final*/ int Setup::Z_SCALE = 1;
 ///*public*/  /*static final*/ int Setup::N_SCALE = 2;
 ///*public*/  /*static final*/ int Setup::TT_SCALE = 3;
 ///*public*/  /*static final*/ int Setup::HOn3_SCALE = 4;
 ///*public*/  /*static final*/ int Setup::OO_SCALE = 5;
 ///*public*/  /*static final*/ int Setup::HO_SCALE = 6;
 ///*public*/  /*static final*/ int Setup::Sn3_SCALE = 7;
 ///*public*/  /*static final*/ int Setup::S_SCALE = 8;
 ///*public*/  /*static final*/ int Setup::On3_SCALE = 9;
 ///*public*/  /*static final*/ int Setup::O_SCALE = 10;
 ///*public*/  /*static final*/ int Setup::G_SCALE = 11; // NMRA #1

 ///*public*/  /*static final*/ int Setup::EAST = 1; // train direction serviced by this location
 ///*public*/  /*static final*/ int Setup::WEST = 2;
 ///*public*/  /*static final*/ int Setup::NORTH = 4;
 ///*public*/  /*static final*/ int Setup::SOUTH = 8;

 /*public*/  /*static final*/ QString Setup::EAST_DIR = tr("East");
 /*public*/  /*static final*/ QString Setup::WEST_DIR = tr("West");
 /*public*/  /*static final*/ QString Setup::NORTH_DIR = tr("North");
 /*public*/  /*static final*/ QString Setup::SOUTH_DIR = tr("South");

 /*public*/  /*static final*/ QString Setup::DESCRIPTIVE = tr("Descriptive"); // Car types
 /*public*/  /*static final*/ QString Setup::AAR = tr("ArrCodes"); // Car types

 /*public*/  /*static final*/ QString Setup::MONOSPACED = tr("Monospace"); // default printer font

 /*public*/  /*static final*/ QString Setup::STANDARD_FORMAT = tr("StandardFormat");
 /*public*/  /*static final*/ QString Setup::TWO_COLUMN_FORMAT = tr("TwoColumnFormat");
 /*public*/  /*static final*/ QString Setup::TWO_COLUMN_TRACK_FORMAT = tr("TwoColumnTrackFormat");

 /*public*/  /*static final*/ QString Setup::PORTRAIT = tr("Portrait");
 /*public*/  /*static final*/ QString Setup::LANDSCAPE = tr("Landscape");
 /*public*/  /*static final*/ QString Setup::HALFPAGE = tr("HalfPage");
 /*public*/  /*static final*/ QString Setup::HANDHELD = tr("HandHeld");

 /*public*/  /*static final*/ QString Setup::PAGE_NORMAL = tr("PageNormal");
 /*public*/  /*static final*/ QString Setup::PAGE_PER_TRAIN = tr("PagePerTrain");
 /*public*/  /*static final*/ QString Setup::PAGE_PER_VISIT = tr("PagePerVisit");

 /*public*/  /*static final*/ QString Setup::LENGTHABV = tr("'");

 /*public*/  /*static final*/ QString Setup::BUILD_REPORT_MINIMAL = "1";
 /*public*/  /*static final*/ QString Setup::BUILD_REPORT_NORMAL = "3";
 /*public*/  /*static final*/ QString Setup::BUILD_REPORT_DETAILED = "5";
 /*public*/  /*static final*/ QString Setup::BUILD_REPORT_VERY_DETAILED = "7";

 /*public*/  /*static final*/ QString Setup::ROAD = tr("Road"); // the supported message format options
 /*public*/  /*static final*/ QString Setup::NUMBER = tr("Number");
 /*public*/  /*static final*/ QString Setup::TYPE = tr("Type");
 /*public*/  /*static final*/ QString Setup::MODEL = tr("Model");
 /*public*/  /*static final*/ QString Setup::LENGTH = tr("Length");
 /*public*/  /*static final*/ QString Setup::LOAD = tr("Load");
 /*public*/  /*static final*/ QString Setup::COLOR = tr("Color");
 /*public*/  /*static final*/ QString Setup::TRACK = tr("Track");
 /*public*/  /*static final*/ QString Setup::DESTINATION = tr("Destination");
 /*public*/  /*static final*/ QString Setup::DEST_TRACK = tr("Dest&Track");
 /*public*/  /*static final*/ QString Setup::FINAL_DEST = tr("Final_Dest");
 /*public*/  /*static final*/ QString Setup::FINAL_DEST_TRACK = tr("FD&Track");
 /*public*/  /*static final*/ QString Setup::LOCATION = tr("Location");
 /*public*/  /*static final*/ QString Setup::CONSIST = tr("Consist");
 /*public*/  /*static final*/ QString Setup::KERNEL = tr("Kernel");
 /*public*/  /*static final*/ QString Setup::KERNEL_SIZE = tr("Kernel_Size");
 /*public*/  /*static final*/ QString Setup::OWNER = tr("Owner");
 /*public*/  /*static final*/ QString Setup::RWE = tr("RWE");
 /*public*/  /*static final*/ QString Setup::COMMENT = tr("Comment");
 /*public*/  /*static final*/ QString Setup::DROP_COMMENT = tr("SetOut_Msg");
 /*public*/  /*static final*/ QString Setup::PICKUP_COMMENT = tr("PickUp_Msg");
 /*public*/  /*static final*/ QString Setup::HAZARDOUS = tr("Hazardous");
 /*public*/  /*static final*/ QString Setup::BLANK = " "; // blank has be a character or a space
 /*public*/  /*static final*/ QString Setup::TAB = tr("Tab"); // used to tab out in tabular mode
 /*public*/  /*static final*/ QString Setup::TAB2 = tr("Tab2");
 /*public*/  /*static final*/ QString Setup::TAB3 = tr("Tab3");
 /*public*/  /*static final*/ QString Setup::BOX = " [ ] "; // NOI18N

 // these are for the utility printing when using tabs
 /*public*/  /*static final*/ QString Setup::NO_ROAD = "NO_ROAD"; // NOI18N
 /*public*/  /*static final*/ QString Setup::NO_NUMBER = "NO_NUMBER"; // NOI18N
 /*public*/  /*static final*/ QString Setup::NO_COLOR = "NO_COLOR"; // NOI18N

 // truncated manifests
 /*public*/  /*static final*/ QString Setup::NO_DESTINATION = "NO_DESTINATION"; // NOI18N
 /*public*/  /*static final*/ QString Setup::NO_DEST_TRACK = "NO_DEST_TRACK"; // NOI18N
 /*public*/  /*static final*/ QString Setup::NO_LOCATION = "NO_LOCATION"; // NOI18N
 /*public*/  /*static final*/ QString Setup::NO_TRACK = "NO_TRACK"; // NOI18N

 // the supported colors for printed text
 /*public*/  /*static final*/ QString Setup::BLACK = tr("Black");
 /*public*/  /*static final*/ QString Setup::RED = tr("Red");
 /*public*/  /*static final*/ QString Setup::ORANGE = tr("Orange");
 /*public*/  /*static final*/ QString Setup::YELLOW = tr("Yellow");
 /*public*/  /*static final*/ QString Setup::GREEN = tr("Green");
 /*public*/  /*static final*/ QString Setup::BLUE = tr("Blue");
 /*public*/  /*static final*/ QString Setup::GRAY = tr("Gray");
 /*public*/  /*static final*/ QString Setup::PINK = tr("Pink");
 /*public*/  /*static final*/ QString Setup::CYAN = tr("Cyan");
 /*public*/  /*static final*/ QString Setup::MAGENTA = tr("Magenta");

 // Unit of Length
 /*public*/  /*static final*/ QString Setup::FEET = tr("Feet");
 /*public*/  /*static final*/ QString Setup::METER = tr("Meter");

 /*private*/  /*static final*/ QStringList Setup::carAttributes = QStringList()
   << Setup::ROAD << Setup::NUMBER << Setup::TYPE << Setup::LENGTH
   << Setup::LOAD << Setup::HAZARDOUS << Setup::COLOR << Setup::KERNEL
   << Setup::KERNEL_SIZE << Setup::OWNER << Setup::TRACK << Setup::LOCATION
   << Setup::DESTINATION << Setup::DEST_TRACK << Setup::FINAL_DEST
   << Setup::FINAL_DEST_TRACK << Setup:: COMMENT << Setup:: DROP_COMMENT
   << Setup::PICKUP_COMMENT << Setup:: RWE;

 /*private*/  /*static final*/ QStringList Setup::engineAttributes =  QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: MODEL
   << Setup:: LENGTH << Setup:: CONSIST << Setup:: OWNER << Setup:: TRACK
   << Setup::LOCATION << Setup:: DESTINATION << Setup:: COMMENT;

 /*private*//*static*/int Setup::scale = Setup::HO_SCALE; // Default scale
 /*private*//*static*/int Setup::ratio = Setup::HO_RATIO;
 /*private*//*static*/int Setup::ratioTons = Setup::HO_RATIO_TONS;
 /*private*//*static*/int Setup::initWeight = Setup::HO_INITIAL_WEIGHT;
 /*private*//*static*/int Setup::addWeight = Setup::HO_ADD_WEIGHT;
 /*private*//*static*/QString Setup::railroadName = Setup::NONE;
 /*private*//*static*/int Setup::traindir = Setup::EAST + Setup::WEST + Setup::NORTH + Setup::SOUTH;
 /*private*//*static*/int Setup::maxTrainLength = 1000; // maximum train length
 /*private*//*static*/int Setup::maxEngineSize = 6; // maximum number of engines that can be assigned to a train
 /*private*//*static*/int Setup::horsePowerPerTon = 1; // Horsepower per ton
 /*private*//*static*/int Setup::carMoves = 5; // default number of moves when creating a route
 /*private*//*static*/QString Setup::carTypes = Setup::DESCRIPTIVE;
 /*private*//*static*/QString Setup::ownerName = Setup::NONE;
 /*private*//*static*/QString Setup::fontName = Setup::MONOSPACED;
 /*private*//*static*/int Setup::manifestFontSize = 10;
 /*private*//*static*/int Setup::buildReportFontSize = 10;
 /*private*//*static*/QString Setup::manifestOrientation = Setup::PORTRAIT;
 /*private*//*static*/QString Setup::switchListOrientation = Setup::PORTRAIT;
 /*private*//*static*/QString Setup::pickupColor = Setup::BLACK;
 /*private*//*static*/QString Setup::dropColor = Setup::BLACK;
 /*private*//*static*/QString Setup::localColor = Setup::BLACK;
 /*private*//*static*/QStringList Setup::pickupEngineMessageFormat = QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: BLANK << Setup:: MODEL
   << Setup:: BLANK << Setup:: BLANK << Setup:: LOCATION << Setup:: COMMENT;
 /*private*//*static*/QStringList Setup::dropEngineMessageFormat = QStringList() << Setup::ROAD << Setup:: NUMBER << Setup:: BLANK << Setup:: MODEL << Setup:: BLANK << Setup:: BLANK << Setup:: DESTINATION << Setup:: COMMENT;
 /*private*//*static*/QStringList Setup::pickupManifestMessageFormat = QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: LENGTH
   << Setup::COLOR << Setup:: LOAD << Setup:: HAZARDOUS << Setup:: LOCATION
   << Setup::COMMENT << Setup:: PICKUP_COMMENT;
 /*private*//*static*/QStringList Setup::dropManifestMessageFormat = QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: LENGTH
   << Setup:: COLOR << Setup:: LOAD << Setup:: HAZARDOUS << Setup:: DESTINATION
   << Setup::COMMENT << Setup:: DROP_COMMENT;
 /*private*//*static*/QStringList Setup::localManifestMessageFormat = QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: LENGTH
   << Setup:: COLOR << Setup:: LOAD << Setup:: HAZARDOUS << Setup:: LOCATION << Setup:: DESTINATION << Setup:: COMMENT;
 /*private*//*static*/QStringList Setup::pickupSwitchListMessageFormat = QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: LENGTH
   << Setup:: COLOR << Setup:: LOAD << Setup:: HAZARDOUS << Setup::LOCATION
   << Setup:: COMMENT << Setup:: PICKUP_COMMENT;
 /*private*//*static*/QStringList Setup::dropSwitchListMessageFormat = QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: LENGTH
   << Setup:: COLOR << Setup:: LOAD << Setup:: HAZARDOUS << Setup::DESTINATION
   << Setup:: COMMENT << Setup:: DROP_COMMENT;
 /*private*//*static*/QStringList Setup::localSwitchListMessageFormat = QStringList()
   << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: LENGTH
   << Setup:: COLOR << Setup:: LOAD << Setup:: HAZARDOUS << Setup::LOCATION << Setup:: DESTINATION << Setup:: COMMENT;
 /*private*//*static*/QStringList Setup::missingCarMessageFormat = QStringList() << Setup::ROAD << Setup:: NUMBER << Setup:: TYPE << Setup:: LENGTH << Setup:: COLOR << Setup:: COMMENT;
 /*private*//*static*/QString Setup::pickupEnginePrefix = Setup::BOX + tr("Pick up");
 /*private*//*static*/QString Setup::dropEnginePrefix = Setup::BOX + tr("Set out");
 /*private*//*static*/QString Setup::pickupCarPrefix = Setup::BOX + tr("Pick up");
 /*private*//*static*/QString Setup::dropCarPrefix = Setup::BOX + tr("Set out");
 /*private*//*static*/QString Setup::localPrefix = Setup::BOX + tr("Move");
 /*private*//*static*/QString Setup::switchListPickupCarPrefix = Setup::BOX + tr("Pick up");
 /*private*//*static*/QString Setup::switchListDropCarPrefix = Setup::BOX + tr("Set out");
 /*private*//*static*/QString Setup::switchListLocalPrefix = Setup::BOX + tr("Move");
 /*private*//*static*/QString Setup::miaComment = tr("The following cars are currently misplaced, please contact the dispatcher if found");
 /*private*//*static*/QString Setup::hazardousMsg = "(" + tr("Hazardous") + ")";
 /*private*//*static*/QString Setup::logoURL = Setup::NONE;
 /*private*//*static*/QString Setup::panelName = "Panel"; // NOI18N
 /*private*//*static*/QString Setup::buildReportLevel = Setup::BUILD_REPORT_VERY_DETAILED;
 /*private*//*static*/QString Setup::routerBuildReportLevel = Setup::BUILD_REPORT_NORMAL;
 /*private*//*static*/int Setup::carSwitchTime = 3; // how long it takes to move a car in minutes
 /*private*//*static*/int Setup::travelTime = 4; // how long it takes a train to move from one location to another in minutes
 /*private*//*static*/QString Setup::yearModeled = Setup::NONE; // year being modeled
 /*private*//*static*/QString Setup::lengthUnit = Setup::FEET;
 /*private*//*static*/QString Setup::iconNorthColor = Setup::NONE;
 /*private*//*static*/QString Setup::iconSouthColor = Setup::NONE;
 /*private*//*static*/QString Setup::iconEastColor = Setup::NONE;
 /*private*//*static*/QString Setup::iconWestColor = Setup::NONE;
 /*private*//*static*/QString Setup::iconLocalColor = Setup::NONE;
 /*private*//*static*/QString Setup::iconTerminateColor = Setup::NONE;

 /*private*//*static*/bool Setup::tab = false; // when true, tab out manifest and switch lists
 /*private*//*static*/int Setup::tab1CharLength = Operations::Control::max_len_string_attibute;
 /*private*//*static*/int Setup::tab2CharLength = 6; // arbitrary lengths
 /*private*//*static*/int Setup::tab3CharLength = 8;

 /*private*//*static*/QString Setup::manifestFormat = Setup::STANDARD_FORMAT;
 /*private*//*static*/bool Setup::manifestEditorEnabled = false; // when true use text editor to view build report
 /*private*//*static*/bool Setup::switchListSameManifest = true; // when true switch list format is the same as the manifest
 /*private*//*static*/bool Setup::manifestTruncated = false; // when true, manifest is truncated if switch list is available
 /*private*//*static*/bool Setup::manifestDepartureTime = false; // when true, manifest shows train's departure time
 /*private*//*static*/bool Setup::switchListRouteComment = true; // when true, switch list have route location comments
 /*private*//*static*/bool Setup::trackSummary = true; // when true, print Setup::switch list track summary

 /*private*//*static*/bool Setup::switchListRealTime = true; // when true switch list only show work for built trains
 /*private*//*static*/bool Setup::switchListAllTrains = true; // when true show all trains that visit the location
 /*private*//*static*/QString Setup::switchListPageFormat = Setup::PAGE_NORMAL; // how switch lists pages are printed

 /*private*//*static*/bool Setup::buildReportEditorEnabled = false; // when true use text editor to view build report
 /*private*//*static*/bool Setup::buildReportIndentEnabled = true; // when true use text editor to view build report
 /*private*//*static*/bool Setup::buildReportAlwaysPreviewEnabled = false; // when true use text editor to view build report

 /*private*//*static*/bool Setup::enableTrainIconXY = true;
 /*private*//*static*/bool Setup::appendTrainIcon = false; // when true, append engine number to train name
 /*private*//*static*/QString Setup::setupComment = Setup::NONE;

 /*private*/ /*static*/ bool Setup::mainMenuEnabled = false; // when true add operations menu to main menu bar
 #if 1
 /*private*//*static*/bool Setup::closeWindowOnSave = false; // when true, close window when save button is activated
 /*private*//*static*/bool Setup::autoSave = true; // when true, automatically save files if modified
 /*private*//*static*/bool Setup::autoBackup = true; // when true, automatically backup files
 /*private*//*static*/bool Setup::enableValue = false; // when true show value fields for rolling stock
 /*private*//*static*/QString Setup::labelValue = tr("Value");
 /*private*//*static*/bool Setup::enableRfid = false; // when true show RFID fields for rolling stock
 /*private*//*static*/QString Setup::labelRfid = tr("RFID");

 /*private*//*static*/bool Setup::carRoutingEnabled = true; // when true enable car routing
 /*private*//*static*/bool Setup::carRoutingYards = true; // when true enable car routing via yard tracks
 /*private*//*static*/bool Setup::carRoutingStaging = false; // when true staging tracks can be used for car routing
 /*private*//*static*/bool Setup::forwardToYardEnabled = true; // when true forward car to yard if track is full
 /*private*//*static*/bool Setup::onlyActiveTrains = false; // when true only active trains are used for routing
 /*private*//*static*/bool Setup::checkCarDestination = false; // when true check car's track for valid destination

 /*private*//*static*/bool Setup::carLogger = false; // when true car logger is enabled
 /*private*//*static*/bool Setup::engineLogger = false; // when true engine logger is enabled
 /*private*//*static*/bool Setup::trainLogger = false; // when true train logger is enabled

 /*private*//*static*/bool Setup::aggressiveBuild = false; // when true subtract car length from track reserve length
 /*private*//*static*/int Setup::numberPasses = 2; // the number of passes in train builder
 /*private*//*static*/bool Setup::allowLocalInterchangeMoves = false; // when true local C/I to C/I moves are allowed
 /*private*//*static*/bool Setup::allowLocalYardMoves = false; // when true local yard to yard moves are allowed
 /*private*//*static*/bool Setup::allowLocalSpurMoves = false; // when true local spur to spur moves are allowed

 /*private*//*static*/bool Setup::trainIntoStagingCheck = true; // staging track must accept train's rolling stock types and roads
 /*private*//*static*/bool Setup::trackImmediatelyAvail = false; // when true staging track is available for other trains
 /*private*//*static*/bool Setup::allowCarsReturnStaging = false; // allow cars on a turn to return to staging if necessary (prevent build failure)
 /*private*//*static*/bool Setup::promptFromStaging = false; // prompt user to specify which departure staging track to use
 /*private*//*static*/bool Setup::promptToStaging = false; // prompt user to specify which arrival staging track to use

 /*private*//*static*/bool Setup::generateCsvManifest = false; // when true generate csv manifest
 /*private*//*static*/bool Setup::generateCsvSwitchList = false; // when true generate csv switch list
 /*private*//*static*/bool Setup::enableVsdPhysicalLocations = false;

 /*private*//*static*/bool Setup::printLocationComments = false; // when true print Setup::location comments on the manifest
 /*private*//*static*/bool Setup::printRouteComments = false; // when true print Setup::route comments on the manifest
 /*private*//*static*/bool Setup::printLoadsAndEmpties = false; // when true print Setup::Loads and Empties on the manifest
 /*private*//*static*/bool Setup::printTimetableName = false; // when true print Setup::timetable name on manifests and switch lists
 /*private*//*static*/bool Setup::use12hrFormat = false; // when true use 12hr rather than 24hr format
 /*private*//*static*/bool Setup::printValid = true; // when true print Setup::out the valid time and date
 /*private*//*static*/bool Setup::sortByTrack = false; // when true manifest work is sorted by track names
 /*private*//*static*/bool Setup::printHeaders = false; // when true add headers to manifest and switch lists

 /*private*//*static*/bool Setup::printCabooseLoad = false; // when true print Setup::caboose load
 /*private*//*static*/bool Setup::printPassengerLoad = false; // when true print Setup::passenger car load

 // property changes
 /*public*/  /*static final*/ QString Setup::SWITCH_LIST_CSV_PROPERTY_CHANGE = "setupSwitchListCSVChange"; //  NOI18N
 /*public*/  /*static final*/ QString Setup::MANIFEST_CSV_PROPERTY_CHANGE = "setupManifestCSVChange"; //  NOI18N
 /*public*/  /*static final*/ QString Setup::REAL_TIME_PROPERTY_CHANGE = "setupSwitchListRealTime"; //  NOI18N
 #endif
 /*public*//*static*/bool Setup::isMainMenuEnabled()
 {
  Operations::OperationsSetupXml::instance(); // load file
  return mainMenuEnabled;
 }

 /*public*//*static*/void Setup::setMainMenuEnabled(bool enabled)
 {
  mainMenuEnabled = enabled;
 }

 /*public*//*static*/bool Setup::isCloseWindowOnSaveEnabled() {
     return closeWindowOnSave;
 }

 /*public*//*static*/void Setup::setCloseWindowOnSaveEnabled(bool enabled) {
     closeWindowOnSave = enabled;
 }

 /*public*//*static*/bool Setup::isAutoSaveEnabled() {
     return autoSave;
 }

 /*public*//*static*/void Setup::setAutoSaveEnabled(bool enabled) {
     bool old = autoSave;
     autoSave = enabled;
     if (!old && enabled)
     {
      new AutoSave();
     }
 }

 /*public*//*static*/bool Setup::isAutoBackupEnabled() {
     return autoBackup;
 }

 /*public*//*static*/void Setup::setAutoBackupEnabled(bool enabled) {
     // Do an autoBackup only if we are changing the setting from false to
     // true.
     if (enabled && !autoBackup) {
         try {
 // TODO:            new AutoBackup().autoBackup();
         } catch (IOException ex) {
 // TODO            log->debug("Autobackup after setting AutoBackup flag true", ex);
         }
     }

     autoBackup = enabled;
 }
 #if 1
 /*public*//*static*/bool Setup::isValueEnabled() {
     return enableValue;
 }

 /*public*//*static*/void Setup::setValueEnabled(bool enabled) {
     enableValue = enabled;
 }

 /*public*//*static*/QString Setup::getValueLabel() {
     return labelValue;
 }

 /*public*//*static*/void Setup::setValueLabel(QString label) {
     labelValue = label;
 }

 /*public*//*static*/bool Setup::isRfidEnabled() {
     return enableRfid;
 }

 /*public*//*static*/void Setup::setRfidEnabled(bool enabled) {
     enableRfid = enabled;
 }

 /*public*//*static*/QString Setup::getRfidLabel() {
     return labelRfid;
 }

 /*public*//*static*/void Setup::setRfidLabel(QString label) {
     labelRfid = label;
 }

 /*public*//*static*/bool Setup::isCarRoutingEnabled() {
     return carRoutingEnabled;
 }

 /*public*//*static*/void Setup::setCarRoutingEnabled(bool enabled) {
     carRoutingEnabled = enabled;
 }

 /*public*//*static*/bool Setup::isCarRoutingViaYardsEnabled() {
     return carRoutingYards;
 }

 /*public*//*static*/void Setup::setCarRoutingViaYardsEnabled(bool enabled) {
     carRoutingYards = enabled;
 }

 /*public*//*static*/bool Setup::isCarRoutingViaStagingEnabled() {
     return carRoutingStaging;
 }

 /*public*//*static*/void Setup::setCarRoutingViaStagingEnabled(bool enabled) {
     carRoutingStaging = enabled;
 }

 /*public*//*static*/bool Setup::isForwardToYardEnabled() {
     return forwardToYardEnabled;
 }

 /*public*//*static*/void Setup::setForwardToYardEnabled(bool enabled) {
     forwardToYardEnabled = enabled;
 }

 /*public*//*static*/bool Setup::isOnlyActiveTrainsEnabled() {
     return onlyActiveTrains;
 }

 /*public*//*static*/void Setup::setOnlyActiveTrainsEnabled(bool enabled) {
     onlyActiveTrains = enabled;
 }

 /*public*//*static*/bool Setup::isCheckCarDestinationEnabled() {
     return checkCarDestination;
 }

 /*public*//*static*/void Setup::setCheckCarDestinationEnabled(bool enabled) {
     checkCarDestination = enabled;
 }

 /*public*//*static*/bool Setup::isBuildAggressive() {
     return aggressiveBuild;
 }

 /*public*//*static*/void Setup::setBuildAggressive(bool enabled) {
     aggressiveBuild = enabled;
 }

 /*public*//*static*/int Setup::getNumberPasses() {
     return numberPasses;
 }

 /*public*//*static*/void Setup::setNumberPasses(int number) {
     numberPasses = number;
 }

 /*public*//*static*/bool Setup::isLocalInterchangeMovesEnabled() {
     return allowLocalInterchangeMoves;
 }

 /*public*//*static*/void Setup::setLocalInterchangeMovesEnabled(bool enabled) {
     allowLocalInterchangeMoves = enabled;
 }

 /*public*//*static*/bool Setup::isLocalYardMovesEnabled() {
     return allowLocalYardMoves;
 }

 /*public*//*static*/void Setup::setLocalYardMovesEnabled(bool enabled) {
     allowLocalYardMoves = enabled;
 }

 /*public*//*static*/bool Setup::isLocalSpurMovesEnabled() {
     return allowLocalSpurMoves;
 }

 /*public*//*static*/void Setup::setLocalSpurMovesEnabled(bool enabled) {
     allowLocalSpurMoves = enabled;
 }

 /*public*//*static*/bool Setup::isTrainIntoStagingCheckEnabled() {
     return trainIntoStagingCheck;
 }

 /*public*//*static*/void Setup::setTrainIntoStagingCheckEnabled(bool enabled) {
     trainIntoStagingCheck = enabled;
 }

 /*public*//*static*/bool Setup::isStagingTrackImmediatelyAvail() {
     return trackImmediatelyAvail;
 }

 /*public*//*static*/void Setup::setStagingTrackImmediatelyAvail(bool enabled) {
     trackImmediatelyAvail = enabled;
 }

 /*public*//*static*/bool Setup::isAllowReturnToStagingEnabled() {
     return allowCarsReturnStaging;
 }

 /*public*//*static*/void Setup::setAllowReturnToStagingEnabled(bool enabled) {
     allowCarsReturnStaging = enabled;
 }

 /*public*//*static*/bool Setup::isPromptFromStagingEnabled() {
     return promptFromStaging;
 }

 /*public*//*static*/void Setup::setPromptFromStagingEnabled(bool enabled) {
     promptFromStaging = enabled;
 }

 /*public*//*static*/bool Setup::isPromptToStagingEnabled() {
     return promptToStaging;
 }

 /*public*//*static*/void Setup::setPromptToStagingEnabled(bool enabled) {
     promptToStaging = enabled;
 }

 /*public*//*static*/bool Setup::isGenerateCsvManifestEnabled() {
     return generateCsvManifest;
 }

 /*public*//*static*/void Setup::setGenerateCsvManifestEnabled(bool enabled) {
     bool old = generateCsvManifest;
     generateCsvManifest = enabled;
     if (enabled && !old) {
     TrainManagerXml::instance()->createDefaultCsvManifestDirectory();
     }
     setDirtyAndFirePropertyChange(MANIFEST_CSV_PROPERTY_CHANGE, old, enabled);
 }

 /*public*//*static*/bool Setup::isGenerateCsvSwitchListEnabled() {
     return generateCsvSwitchList;
 }

 /*public*//*static*/void Setup::setGenerateCsvSwitchListEnabled(bool enabled) {
     bool old = generateCsvSwitchList;
     generateCsvSwitchList = enabled;
     if (enabled && !old) {
      TrainManagerXml::instance()->createDefaultCsvSwitchListDirectory();
     }
     setDirtyAndFirePropertyChange(SWITCH_LIST_CSV_PROPERTY_CHANGE, old, enabled);
 }

 /*public*//*static*/bool Setup::isVsdPhysicalLocationEnabled() {
     return enableVsdPhysicalLocations;
 }

 /*public*//*static*/void Setup::setVsdPhysicalLocationEnabled(bool enabled) {
     enableVsdPhysicalLocations = enabled;
 }
 #endif
 /*public*//*static*/QString Setup::getRailroadName()
 {
  if (railroadName == NULL)
  {
   //return //WebServerManager.getWebServerPreferences().getRailRoadName();
  }
  return railroadName;
 }

 /*public*//*static*/void Setup::setRailroadName(QString name) {
     QString old = railroadName;
     railroadName = name;
     setDirtyAndFirePropertyChange("Railroad Name Change", old, name); // NOI18N
 }

 /*public*//*static*/QString Setup::getHazardousMsg() {
     return hazardousMsg;
 }

 /*public*//*static*/void Setup::setHazardousMsg(QString message) {
     hazardousMsg = message;
 }

 /*public*//*static*/QString Setup::getMiaComment() {
     return miaComment;
 }

 /*public*//*static*/void Setup::setMiaComment(QString comment) {
     miaComment = comment;
 }

 /*public*//*static*/void Setup::setTrainDirection(int direction) {
     traindir = direction;
 }

 /*public*//*static*/int Setup::getTrainDirection() {
     return traindir;
 }

 /*public*//*static*/void Setup::setMaxTrainLength(int length) {
     maxTrainLength = length;
 }

 /*public*//*static*/int Setup::getMaxTrainLength() {
     return maxTrainLength;
 }

 /*public*//*static*/void Setup::setMaxNumberEngines(int value) {
     maxEngineSize = value;
 }

 /*public*//*static*/int Setup::getMaxNumberEngines() {
     return maxEngineSize;
 }

 /*public*//*static*/void Setup::setHorsePowerPerTon(int value) {
     horsePowerPerTon = value;
 }

 /*public*//*static*/int Setup::getHorsePowerPerTon() {
     return horsePowerPerTon;
 }

 /*public*//*static*/void Setup::setCarMoves(int moves) {
     carMoves = moves;
 }

 /*public*//*static*/int Setup::getCarMoves() {
     return carMoves;
 }

 /*public*//*static*/QString Setup::getPanelName() {
     return panelName;
 }

 /*public*//*static*/void Setup::setPanelName(QString name) {
     panelName = name;
 }

 /*public*//*static*/QString Setup::getLengthUnit() {
     //return lengthUnit;
  return tr("feet");
 }

 /*public*//*static*/void Setup::setLengthUnit(QString unit) {
     lengthUnit = unit;
 }

 /*public*//*static*/QString Setup::Setup::getYearModeled() {
     return yearModeled;
 }

 /*public*//*static*/void Setup::setYearModeled(QString year) {
     yearModeled = year;
 }

 /*public*//*static*/QString Setup::getCarTypes() {
     return carTypes;
 }

 /*public*//*static*/void Setup::setCarTypes(QString types) {
     carTypes = types;
 }

 /*public*//*static*/void Setup::setTrainIconCordEnabled(bool enable) {
     enableTrainIconXY = enable;
 }

 /*public*//*static*/bool Setup::isTrainIconCordEnabled() {
     return enableTrainIconXY;
 }

 /*public*//*static*/void Setup::setTrainIconAppendEnabled(bool enable) {
     appendTrainIcon = enable;
 }

 /*public*//*static*/bool Setup::isTrainIconAppendEnabled() {
     return appendTrainIcon;
 }

 /*public*//*static*/void Setup::setComment(QString comment) {
     setupComment = comment;
 }

 /*public*//*static*/QString Setup::getComment(bool asText)
 {
  if(asText)
  {
   QTextEdit te(setupComment);
   return te.toPlainText();
  }
  return setupComment;
 }

 /*public*//*static*/void Setup::setBuildReportLevel(QString level) {
     buildReportLevel = level;
 }

 /*public*//*static*/QString Setup::getBuildReportLevel() {
     return buildReportLevel;
 }

 /*public*//*static*/void Setup::setRouterBuildReportLevel(QString level) {
     routerBuildReportLevel = level;
 }

 /*public*//*static*/QString Setup::getRouterBuildReportLevel() {
     return routerBuildReportLevel;
 }

 /*public*//*static*/void Setup::setManifestEditorEnabled(bool enable) {
     manifestEditorEnabled = enable;
 }

 /*public*//*static*/bool Setup::isManifestEditorEnabled() {
     return manifestEditorEnabled;
 }

 /*public*//*static*/void Setup::setBuildReportEditorEnabled(bool enable) {
     buildReportEditorEnabled = enable;
 }

 /*public*//*static*/bool Setup::isBuildReportEditorEnabled() {
     return buildReportEditorEnabled;
 }

 /*public*//*static*/void Setup::setBuildReportIndentEnabled(bool enable) {
     buildReportIndentEnabled = enable;
 }

 /*public*//*static*/bool Setup::isBuildReportIndentEnabled() {
     return buildReportIndentEnabled;
 }

 /*public*//*static*/void Setup::setBuildReportAlwaysPreviewEnabled(bool enable) {
     buildReportAlwaysPreviewEnabled = enable;
 }

 /*public*//*static*/bool Setup::isBuildReportAlwaysPreviewEnabled() {
     return buildReportAlwaysPreviewEnabled;
 }

 /*public*//*static*/void Setup::setSwitchListFormatSameAsManifest(bool b) {
     switchListSameManifest = b;
 }

 /*public*//*static*/bool Setup::isSwitchListFormatSameAsManifest() {
     return switchListSameManifest;
 }

 /*public*//*static*/void Setup::setTrackSummaryEnabled(bool b) {
     trackSummary = b;
 }

 /*public*//*static*/bool Setup::isTrackSummaryEnabled() {
     return trackSummary;
 }

 /*public*//*static*/void Setup::setSwitchListRouteLocationCommentEnabled(bool b) {
     switchListRouteComment = b;
 }

 /*public*//*static*/bool Setup::isSwitchListRouteLocationCommentEnabled() {
     return switchListRouteComment;
 }

 /*public*//*static*/void Setup::setSwitchListRealTime(bool b) {
     bool old = switchListRealTime;
     switchListRealTime = b;
     setDirtyAndFirePropertyChange(REAL_TIME_PROPERTY_CHANGE, old, b);
 }

 /*public*//*static*/bool Setup::isSwitchListRealTime() {
     return switchListRealTime;
 }

 /*public*//*static*/void Setup::setSwitchListAllTrainsEnabled(bool b) {
     bool old = switchListAllTrains;
     switchListAllTrains = b;
     setDirtyAndFirePropertyChange("Switch List All Trains", old, b); // NOI18N
 }

 /*public*//*static*/bool Setup::isSwitchListAllTrainsEnabled() {
     return switchListAllTrains;
 }

 /*public*//*static*/void Setup::setSwitchListPageFormat(QString format) {
     switchListPageFormat = format;
 }

 /*public*//*static*/QString Setup::getSwitchListPageFormat() {
     return switchListPageFormat;
 }

 /*public*//*static*/void Setup::setTruncateManifestEnabled(bool b) {
     manifestTruncated = b;
 }

 /*public*//*static*/bool Setup::isTruncateManifestEnabled() {
     return manifestTruncated;
 }

 /*public*//*static*/void Setup::setUseDepartureTimeEnabled(bool b) {
     manifestDepartureTime = b;
 }

 /*public*//*static*/bool Setup::isUseDepartureTimeEnabled() {
     return manifestDepartureTime;
 }

 /*public*//*static*/void Setup::setPrintLocationCommentsEnabled(bool enable) {
     printLocationComments = enable;
 }

 /*public*//*static*/bool Setup::isPrintLocationCommentsEnabled() {
     return printLocationComments;
 }

 /*public*//*static*/void Setup::setPrintRouteCommentsEnabled(bool enable) {
     printRouteComments = enable;
 }

 /*public*//*static*/bool Setup::isPrintRouteCommentsEnabled() {
     return printRouteComments;
 }

 /*public*//*static*/void Setup::setPrintLoadsAndEmptiesEnabled(bool enable) {
     printLoadsAndEmpties = enable;
 }

 /*public*//*static*/bool Setup::isPrintLoadsAndEmptiesEnabled() {
     return printLoadsAndEmpties;
 }

 /*public*//*static*/void Setup::setPrintTimetableNameEnabled(bool enable) {
     printTimetableName = enable;
 }

 /*public*//*static*/bool Setup::isPrintTimetableNameEnabled() {
     return printTimetableName;
 }

 /*public*//*static*/void Setup::set12hrFormatEnabled(bool enable) {
     use12hrFormat = enable;
 }

 /*public*//*static*/bool Setup::is12hrFormatEnabled() {
     return use12hrFormat;
 }

 /*public*//*static*/void Setup::setPrintValidEnabled(bool enable) {
     printValid = enable;
 }

 /*public*//*static*/bool Setup::isPrintValidEnabled() {
     return printValid;
 }

 /*public*//*static*/void Setup::setSortByTrackEnabled(bool enable) {
     sortByTrack = enable;
 }

 /*public*//*static*/bool Setup::isSortByTrackEnabled() {
     return sortByTrack;
 }

 /*public*//*static*/void Setup::setPrintHeadersEnabled(bool enable) {
     printHeaders = enable;
 }

 /*public*//*static*/bool Setup::isPrintHeadersEnabled() {
     return printHeaders;
 }

 /*public*//*static*/void Setup::setPrintCabooseLoadEnabled(bool enable) {
     printCabooseLoad = enable;
 }

 /*public*//*static*/bool Setup::isPrintCabooseLoadEnabled() {
     return printCabooseLoad;
 }

 /*public*//*static*/void Setup::setPrintPassengerLoadEnabled(bool enable) {
     printPassengerLoad = enable;
 }

 /*public*//*static*/bool Setup::isPrintPassengerLoadEnabled() {
     return printPassengerLoad;
 }

 /*public*//*static*/void Setup::setSwitchTime(int minutes) {
     carSwitchTime = minutes;
 }

 /*public*//*static*/int Setup::getSwitchTime() {
     return carSwitchTime;
 }

 /*public*//*static*/void Setup::setTravelTime(int minutes) {
     travelTime = minutes;
 }

 /*public*//*static*/int Setup::getTravelTime() {
     return travelTime;
 }

 /*public*//*static*/void Setup::setTrainIconColorNorth(QString color) {
     iconNorthColor = color;
 }

 /*public*//*static*/QString Setup::getTrainIconColorNorth() {
     return iconNorthColor;
 }

 /*public*//*static*/void Setup::setTrainIconColorSouth(QString color) {
     iconSouthColor = color;
 }

 /*public*//*static*/QString Setup::getTrainIconColorSouth() {
     return iconSouthColor;
 }

 /*public*//*static*/void Setup::setTrainIconColorEast(QString color) {
     iconEastColor = color;
 }

 /*public*//*static*/QString Setup::getTrainIconColorEast() {
     return iconEastColor;
 }

 /*public*//*static*/void Setup::setTrainIconColorWest(QString color) {
     iconWestColor = color;
 }

 /*public*//*static*/QString Setup::getTrainIconColorWest() {
     return iconWestColor;
 }

 /*public*//*static*/void Setup::setTrainIconColorLocal(QString color) {
     iconLocalColor = color;
 }

 /*public*//*static*/QString Setup::getTrainIconColorLocal() {
     return iconLocalColor;
 }

 /*public*//*static*/void Setup::setTrainIconColorTerminate(QString color) {
     iconTerminateColor = color;
 }

 /*public*//*static*/QString Setup::getTrainIconColorTerminate() {
     return iconTerminateColor;
 }

 /*public*//*static*/QString Setup::getFontName() {
     return fontName;
 }

 /*public*//*static*/void Setup::setFontName(QString name) {
     fontName = name;
 }

 /*public*//*static*/int Setup::getManifestFontSize() {
     return manifestFontSize;
 }

 /*public*//*static*/void Setup::setManifestFontSize(int size) {
     manifestFontSize = size;
 }

 /*public*//*static*/int Setup::getBuildReportFontSize() {
     return buildReportFontSize;
 }

 /*public*//*static*/void Setup::setBuildReportFontSize(int size) {
     buildReportFontSize = size;
 }

 /*public*//*static*/QString Setup::getManifestOrientation() {
     return manifestOrientation;
 }

 /*public*//*static*/void Setup::setManifestOrientation(QString orientation) {
     manifestOrientation = orientation;
 }

 /*public*//*static*/QString Setup::getSwitchListOrientation() {
     if (isSwitchListFormatSameAsManifest()) {
         return manifestOrientation;
     } else {
         return switchListOrientation;
     }
 }

 /*public*//*static*/void Setup::setSwitchListOrientation(QString orientation) {
     switchListOrientation = orientation;
 }

 /*public*//*static*/bool Setup::isTabEnabled() {
     return tab;
 }

 /*public*//*static*/void Setup::setTabEnabled(bool enable) {
     tab = enable;
 }

 /*public*//*static*/int Setup::getTab1Length() {
     return tab1CharLength;
 }

 /*public*//*static*/void Setup::setTab1length(int length) {
     tab1CharLength = length;
 }

 /*public*//*static*/int Setup::getTab2Length() {
     return tab2CharLength;
 }

 /*public*//*static*/void Setup::setTab2length(int length) {
     tab2CharLength = length;
 }

 /*public*//*static*/int Setup::getTab3Length() {
     return tab3CharLength;
 }

 /*public*//*static*/void Setup::setTab3length(int length) {
     tab3CharLength = length;
 }

 /*public*//*static*/QString Setup::getManifestFormat() {
     return manifestFormat;
 }

 /*public*//*static*/void Setup::setManifestFormat(QString format) {
     manifestFormat = format;
 }

 /*public*//*static*/bool Setup::isCarLoggerEnabled() {
     return carLogger;
 }

 /*public*//*static*/void Setup::setCarLoggerEnabled(bool enable) {
     carLogger = enable;
 // TOD)::    RollingStockLogger.instance().enableCarLogging(enable);
 }

 /*public*//*static*/bool Setup::isEngineLoggerEnabled() {
     return engineLogger;
 }

 /*public*//*static*/void Setup::setEngineLoggerEnabled(bool enable) {
     engineLogger = enable;
 // TODO:    RollingStockLogger.instance().enableEngineLogging(enable);
 }

 /*public*//*static*/bool Setup::isTrainLoggerEnabled() {
     return trainLogger;
 }

 /*public*//*static*/void Setup::setTrainLoggerEnabled(bool enable) {
     trainLogger = enable;
 // TODO:    TrainLogger.instance().enableTrainLogging(enable);
 }

 /*public*//*static*/QString Setup::getPickupEnginePrefix() {
     return pickupEnginePrefix;
 }

 /*public*//*static*/void Setup::setPickupEnginePrefix(QString prefix) {
     pickupEnginePrefix = prefix;
 }

 /*public*//*static*/QString Setup::getDropEnginePrefix() {
     return dropEnginePrefix;
 }

 /*public*//*static*/void Setup::setDropEnginePrefix(QString prefix) {
     dropEnginePrefix = prefix;
 }

 /*public*//*static*/QString Setup::getPickupCarPrefix() {
     return pickupCarPrefix;
 }

 /*public*//*static*/void Setup::setPickupCarPrefix(QString prefix) {
     pickupCarPrefix = prefix;
 }

 /*public*//*static*/QString Setup::getDropCarPrefix() {
     return dropCarPrefix;
 }

 /*public*//*static*/void Setup::setDropCarPrefix(QString prefix) {
     dropCarPrefix = prefix;
 }

 /*public*//*static*/QString Setup::getLocalPrefix() {
     return localPrefix;
 }

 /*public*//*static*/void Setup::setLocalPrefix(QString prefix) {
     localPrefix = prefix;
 }

 /*public*//*static*/int Setup::getManifestPrefixLength() {
     int maxLength = getPickupEnginePrefix().length();
     if (getDropEnginePrefix().length() > maxLength) {
         maxLength = getDropEnginePrefix().length();
     }
     if (getPickupCarPrefix().length() > maxLength) {
         maxLength = getPickupCarPrefix().length();
     }
     if (getDropCarPrefix().length() > maxLength) {
         maxLength = getDropCarPrefix().length();
     }
     if (getLocalPrefix().length() > maxLength) {
         maxLength = getLocalPrefix().length();
     }
     return maxLength;
 }

 /*public*//*static*/QString Setup::getSwitchListPickupCarPrefix() {
     if (isSwitchListFormatSameAsManifest()) {
         return pickupCarPrefix;
     } else {
         return switchListPickupCarPrefix;
     }
 }

 /*public*//*static*/void Setup::setSwitchListPickupCarPrefix(QString prefix) {
     switchListPickupCarPrefix = prefix;
 }

 /*public*//*static*/QString Setup::getSwitchListDropCarPrefix() {
     if (isSwitchListFormatSameAsManifest()) {
         return dropCarPrefix;
     } else {
         return switchListDropCarPrefix;
     }
 }

 /*public*//*static*/void Setup::setSwitchListDropCarPrefix(QString prefix) {
     switchListDropCarPrefix = prefix;
 }

 /*public*//*static*/QString Setup::getSwitchListLocalPrefix() {
     if (isSwitchListFormatSameAsManifest()) {
         return localPrefix;
     } else {
         return switchListLocalPrefix;
     }
 }

 /*public*//*static*/void Setup::setSwitchListLocalPrefix(QString prefix) {
     switchListLocalPrefix = prefix;
 }

 /*public*//*static*/int Setup::getSwitchListPrefixLength() {
     int maxLength = getPickupEnginePrefix().length();
     if (getDropEnginePrefix().length() > maxLength) {
         maxLength = getDropEnginePrefix().length();
     }
     if (getSwitchListPickupCarPrefix().length() > maxLength) {
         maxLength = getSwitchListPickupCarPrefix().length();
     }
     if (getSwitchListDropCarPrefix().length() > maxLength) {
         maxLength = getSwitchListDropCarPrefix().length();
     }
     if (getSwitchListLocalPrefix().length() > maxLength) {
         maxLength = getSwitchListLocalPrefix().length();
     }
     return maxLength;
 }

 /*public*//*static*/QStringList Setup::getEngineAttributes() {
     //return engineAttributes.clone();
  return QStringList(engineAttributes);
 }

 /*public*//*static*/QStringList Setup::getPickupEngineMessageFormat() {
     //return pickupEngineMessageFormat.clone();
  return QStringList(pickupEngineMessageFormat);
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setPickupEngineMessageFormat(QStringList format) {
  pickupEngineMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getDropEngineMessageFormat() {
     //return dropEngineMessageFormat.clone();
  return QStringList(dropEngineMessageFormat);
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setDropEngineMessageFormat(QStringList format) {
     dropEngineMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getCarAttributes() {
     //return carAttributes.clone();
  return QStringList(carAttributes);
 }

 /*public*//*static*/QStringList Setup::getPickupManifestMessageFormat() {
     //return pickupManifestMessageFormat.clone();
  return QStringList(pickupManifestMessageFormat);
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setPickupManifestMessageFormat(QStringList format) {
     pickupManifestMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getDropManifestMessageFormat() {
     //return dropManifestMessageFormat.clone();
  return QStringList(dropManifestMessageFormat);
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setDropManifestMessageFormat(QStringList format) {
     dropManifestMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getLocalManifestMessageFormat() {
     //return localManifestMessageFormat.clone();
  return QStringList(localManifestMessageFormat);
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setLocalManifestMessageFormat(QStringList format) {
     localManifestMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getMissingCarMessageFormat() {
     //return missingCarMessageFormat.clone();
  return QStringList(missingCarMessageFormat);

 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setMissingCarMessageFormat(QStringList format) {
     missingCarMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getPickupSwitchListMessageFormat()
 {
  if (isSwitchListFormatSameAsManifest())
  {
      //return pickupManifestMessageFormat.clone();
   return QStringList(pickupManifestMessageFormat);
  }
  else
  {
      //return pickupSwitchListMessageFormat.clone();
   return QStringList(pickupSwitchListMessageFormat);
  }
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setPickupSwitchListMessageFormat(QStringList format) {
     pickupSwitchListMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getDropSwitchListMessageFormat() {
     if (isSwitchListFormatSameAsManifest()) {
         //return dropManifestMessageFormat.clone();
      return QStringList(dropManifestMessageFormat);
     } else {
         //return dropSwitchListMessageFormat.clone();
      return QStringList(dropSwitchListMessageFormat);
     }
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setDropSwitchListMessageFormat(QStringList format) {
     dropSwitchListMessageFormat = format;
 }

 /*public*//*static*/QStringList Setup::getLocalSwitchListMessageFormat() {
     if (isSwitchListFormatSameAsManifest()) {
         //return localManifestMessageFormat.clone();
      return QStringList(localManifestMessageFormat);
     } else {
         //return localSwitchListMessageFormat.clone();
         return QStringList(localManifestMessageFormat);
     }
 }

 //@edu.umd.cs.findbugs.annotations.SuppressFBWarnings("EI_EXPOSE_STATIC_REP2")
 /*public*//*static*/void Setup::setLocalSwitchListMessageFormat(QStringList format) {
     localSwitchListMessageFormat = format;
 }

 /**
  * Gets the manifest format for utility cars. The car's road, number, and
  * color are not printed.
  *
  * @return Utility car format
  */
 /*public*//*static*/QStringList Setup::getPickupUtilityManifestMessageFormat() {
     return createUitlityCarMessageFormat(getPickupManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getDropUtilityManifestMessageFormat() {
     return createUitlityCarMessageFormat(getDropManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getLocalUtilityManifestMessageFormat() {
     return createUitlityCarMessageFormat(getLocalManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getPickupUtilitySwitchListMessageFormat() {
     return createUitlityCarMessageFormat(getPickupSwitchListMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getDropUtilitySwitchListMessageFormat() {
     return createUitlityCarMessageFormat(getDropSwitchListMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getLocalUtilitySwitchListMessageFormat() {
     return createUitlityCarMessageFormat(getLocalSwitchListMessageFormat());
 }

 /*private*//*static*/QStringList Setup::createUitlityCarMessageFormat(QStringList format) {
     // remove car's road, number, color
  for (int i = 0; i < format.length(); i++) {
         if (format[i]==(ROAD)) {
             format[i] = NO_ROAD;
         } else if (format[i]==(NUMBER)) {
             format[i] = NO_NUMBER;
         } else if (format[i]==(COLOR)) {
             format[i] = NO_COLOR;
         }
     }
     return format;
 }

 /*public*//*static*/QStringList Setup::getPickupTruncatedManifestMessageFormat() {
     return createTruncatedManifestMessageFormat(getPickupManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getDropTruncatedManifestMessageFormat() {
     return createTruncatedManifestMessageFormat(getDropManifestMessageFormat());
 }

 /*private*//*static*/QStringList Setup::createTruncatedManifestMessageFormat(QStringList format) {
     // remove car's destination and location
  for (int i = 0; i < format.length(); i++)
  {
         if (format[i]==(DESTINATION)) {
             format[i] = NO_DESTINATION;
         } else if (format[i]==(DEST_TRACK)) {
             format[i] = NO_DEST_TRACK;
         } else if (format[i]==(LOCATION)) {
             format[i] = NO_LOCATION;
         } else if (format[i]==(TRACK)) {
             format[i] = NO_TRACK;
         }
     }
     return format;
 }

 /*public*//*static*/QStringList Setup::getPickupTwoColumnByTrackManifestMessageFormat() {
     return createTwoColumnByTrackPickupMessageFormat(getPickupManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getPickupTwoColumnByTrackSwitchListMessageFormat() {
     return createTwoColumnByTrackPickupMessageFormat(getPickupSwitchListMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getPickupTwoColumnByTrackUtilityManifestMessageFormat() {
     return createTwoColumnByTrackPickupMessageFormat(getPickupUtilityManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getPickupTwoColumnByTrackUtilitySwitchListMessageFormat() {
     return createTwoColumnByTrackPickupMessageFormat(getPickupUtilitySwitchListMessageFormat());
 }

 /*private*//*static*/QStringList Setup::createTwoColumnByTrackPickupMessageFormat(QStringList format) {
  for (int i = 0; i < format.length(); i++) {
         if (format[i]==(LOCATION)) {
             format[i] = BLANK;
         } else if (format[i]==(TRACK)) {
             format[i] = BLANK;
         }
     }
     return format;
 }

 /*public*//*static*/QStringList Setup::getDropTwoColumnByTrackManifestMessageFormat() {
     return createTwoColumnByTrackDropMessageFormat(getDropManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getDropTwoColumnByTrackSwitchListMessageFormat() {
     return createTwoColumnByTrackDropMessageFormat(getDropSwitchListMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getDropTwoColumnByTrackUtilityManifestMessageFormat() {
     return createTwoColumnByTrackDropMessageFormat(getDropUtilityManifestMessageFormat());
 }

 /*public*//*static*/QStringList Setup::getDropTwoColumnByTrackUtilitySwitchListMessageFormat() {
     return createTwoColumnByTrackDropMessageFormat(getDropUtilitySwitchListMessageFormat());
 }

 /*private*//*static*/QStringList Setup::createTwoColumnByTrackDropMessageFormat(QStringList format) {
  for (int i = 0; i < format.length(); i++) {
         if (format[i]==(DESTINATION)) {
             format[i] = BLANK;
         } else if (format[i]==(TRACK)) {
             format[i] = BLANK;
         }
     }
     return format;
 }

 /*public*//*static*/QString Setup::getDropTextColor() {
     return dropColor;
 }

 /*public*//*static*/void Setup::setDropTextColor(QString color) {
     dropColor = color;
 }

 /*public*//*static*/QString Setup::getPickupTextColor() {
     return pickupColor;
 }

 /*public*//*static*/void Setup::setPickupTextColor(QString color) {
     pickupColor = color;
 }

 /*public*//*static*/QString Setup::getLocalTextColor() {
     return localColor;
 }

 /*public*//*static*/void Setup::setLocalTextColor(QString color) {
     localColor = color;
 }

 /*public*//*static*/QColor Setup::getPickupColor() {
     return getColor(pickupColor);
 }

 /*public*//*static*/QColor Setup::getDropColor() {
     return getColor(dropColor);
 }

 /*public*//*static*/QColor Setup::getLocalColor() {
     return getColor(localColor);
 }

 /*public*//*static*/QColor Setup::getColor(QString colorName) {
     if (colorName==(BLACK)) {
      return Qt::black;
     }
     if (colorName==(BLUE)) {
      return  Qt::blue;
     }
     if (colorName==(GREEN)) {
      return  Qt::green;
     }
     if (colorName==(RED)) {
      return  Qt::red;
     }
     if (colorName==(ORANGE)) {
      return  QColor(255,165,0);
     }
     if (colorName==(GRAY)) {
      return  Qt::gray;
     }
     if (colorName==(YELLOW)) {
      return  Qt::yellow;
     }
     if (colorName==(PINK)) {
      return  QColor(255,192,203);
     }
     if (colorName==(CYAN)) {
      return  Qt::cyan;
     }
     if (colorName==(MAGENTA)) {
      return  Qt::magenta;
     }
     return QColor(); // default
 }

 /*public*//*static*/QString Setup::getManifestLogoURL() {
     return logoURL;
 }

 /*public*//*static*/void Setup::setManifestLogoURL(QString pathName) {
     logoURL = pathName;
 }

 /*public*//*static*/QString Setup::getOwnerName() {
     return ownerName;
 }

 /*public*//*static*/void Setup::setOwnerName(QString name) {
     ownerName = name;
 }

 /*public*//*static*/int Setup::getScaleRatio() {
     if (scale == 0) {
         Logger::error("Scale not set");
     }
     return ratio;
 }

 /*public*//*static*/int Setup::getScaleTonRatio() {
     if (scale == 0) {
         Logger::error("Scale not set");
     }
     return ratioTons;
 }

 /*public*//*static*/int Setup::getInitalWeight() {
     if (scale == 0) {
         Logger::error("Scale not set");
     }
     return initWeight;
 }

 /*public*//*static*/int Setup::getAddWeight() {
     if (scale == 0) {
         Logger::error("Scale not set");
     }
     return addWeight;
 }

 /*public*//*static*/int Setup::getScale() {
     return scale;
 }

 /*public*//*static*/void Setup::setScale(int s) {
     scale = s;
     switch (scale) {
         case Z_SCALE:
             ratio = Z_RATIO;
             initWeight = Z_INITIAL_WEIGHT;
             addWeight = Z_ADD_WEIGHT;
             ratioTons = Z_RATIO_TONS;
             break;
         case N_SCALE:
             ratio = N_RATIO;
             initWeight = N_INITIAL_WEIGHT;
             addWeight = N_ADD_WEIGHT;
             ratioTons = N_RATIO_TONS;
             break;
         case TT_SCALE:
             ratio = TT_RATIO;
             initWeight = TT_INITIAL_WEIGHT;
             addWeight = TT_ADD_WEIGHT;
             ratioTons = TT_RATIO_TONS;
             break;
         case HOn3_SCALE:
             ratio = HO_RATIO;
             initWeight = HOn3_INITIAL_WEIGHT;
             addWeight = HOn3_ADD_WEIGHT;
             ratioTons = HOn3_RATIO_TONS;
             break;
         case OO_SCALE:
             ratio = OO_RATIO;
             initWeight = OO_INITIAL_WEIGHT;
             addWeight = OO_ADD_WEIGHT;
             ratioTons = OO_RATIO_TONS;
             break;
         case HO_SCALE:
             ratio = HO_RATIO;
             initWeight = HO_INITIAL_WEIGHT;
             addWeight = HO_ADD_WEIGHT;
             ratioTons = HO_RATIO_TONS;
             break;
         case Sn3_SCALE:
             ratio = S_RATIO;
             initWeight = Sn3_INITIAL_WEIGHT;
             addWeight = Sn3_ADD_WEIGHT;
             ratioTons = Sn3_RATIO_TONS;
             break;
         case S_SCALE:
             ratio = S_RATIO;
             initWeight = S_INITIAL_WEIGHT;
             addWeight = S_ADD_WEIGHT;
             ratioTons = S_RATIO_TONS;
             break;
         case On3_SCALE:
             ratio = O_RATIO;
             initWeight = On3_INITIAL_WEIGHT;
             addWeight = On3_ADD_WEIGHT;
             ratioTons = On3_RATIO_TONS;
             break;
         case O_SCALE:
             ratio = O_RATIO;
             initWeight = O_INITIAL_WEIGHT;
             addWeight = O_ADD_WEIGHT;
             ratioTons = O_RATIO_TONS;
             break;
         case G_SCALE:
             ratio = G_RATIO;
             initWeight = G_INITIAL_WEIGHT;
             addWeight = G_ADD_WEIGHT;
             ratioTons = G_RATIO_TONS;
             break;
         default:
             Logger::error("Unknown scale");
     }
 }

 /*public*//*static*/QComboBox* Setup::getManifestFormatComboBox() {
     QComboBox* box = new QComboBox();
     box->addItem(STANDARD_FORMAT);
     box->addItem(TWO_COLUMN_FORMAT);
     box->addItem(TWO_COLUMN_TRACK_FORMAT);
     return box;
 }

 /*public*//*static*/QComboBox* Setup::getOrientationComboBox() {
     QComboBox* box = new QComboBox();
     box->addItem(PORTRAIT);
     box->addItem(LANDSCAPE);
     box->addItem(HALFPAGE);
     box->addItem(HANDHELD);
     return box;
 }

 /*public*//*static*/QComboBox* Setup::getSwitchListPageFormatComboBox() {
     QComboBox* box = new QComboBox();
     box->addItem(PAGE_NORMAL);
     box->addItem(PAGE_PER_TRAIN);
     box->addItem(PAGE_PER_VISIT);
     return box;
 }

 /**
  *
  * @return the available text colors used for printing
  */
 /*public*//*static*/QComboBox* Setup::getPrintColorComboBox() {
     QComboBox* box = new QComboBox();
     box->addItem(BLACK);
     box->addItem(RED);
     box->addItem(ORANGE);
     box->addItem(YELLOW);
     box->addItem(GREEN);
     box->addItem(BLUE);
     box->addItem(GRAY);
     return box;
 }

 /*public*//*static*/QComboBox* Setup::getEngineMessageComboBox() {
     QComboBox* box = new QComboBox();
     box->addItem(BLANK);
     foreach (QString attribute, getEngineAttributes()) {
         box->addItem(attribute);
     }
     if (isTabEnabled()) {
         box->addItem(TAB);
         box->addItem(TAB2);
         box->addItem(TAB3);
     }
     return box;
 }

 /*public*//*static*/QComboBox* Setup::getCarMessageComboBox() {
     QComboBox* box = new QComboBox();
     box->addItem(BLANK);
     foreach (QString attribute , getCarAttributes()) {
         box->addItem(attribute);
     }
     if (isTabEnabled()) {
         box->addItem(TAB);
         box->addItem(TAB2);
         box->addItem(TAB3);
     }
     return box;
 }

 /**
  *
  * @return JComboBox loaded with the strings (North, South, East, West)
  *         showing the available train directions for this railroad
  */
 /*public*//*static*/QComboBox* Setup::getTrainDirectionComboBox() {
     QComboBox* box = new QComboBox();
     foreach (QString direction, getTrainDirectionList())
         box->addItem(direction);
     return box;
 }

 /**
  * Get train directions QString Setup::format
  *
  * @return List of valid train directions
  */
 /*public*//*static*/QVector<QString> Setup::getTrainDirectionList() {
     QVector<QString> directions =  QVector<QString>();
     if ((traindir & EAST) > 0) {
         directions.append(EAST_DIR);
     }
     if ((traindir & WEST) > 0) {
         directions.append(WEST_DIR);
     }
     if ((traindir & NORTH) > 0) {
         directions.append(NORTH_DIR);
     }
     if ((traindir & SOUTH) > 0) {
         directions.append(SOUTH_DIR);
     }
     return directions;
 }

 /**
  * Converts binary direction to QString Setup::direction
  *
  * @param direction EAST, WEST, NORTH, SOUTH
  * @return QString Setup::representation of a direction
  */
 /*public*//*static*/QString Setup::getDirectionString(int direction) {
     switch (direction) {
         case EAST:
             return EAST_DIR;
         case WEST:
             return WEST_DIR;
         case NORTH:
             return NORTH_DIR;
         case SOUTH:
             return SOUTH_DIR;
         default:
             return "unknown"; // NOI18N
     }
 }

 /**
  * Converts binary direction to a set of QString Setup::directions
  *
  * @param directions EAST, WEST, NORTH, SOUTH
  * @return QStringList representation of a set of directions
  */
 /*public*//*static*/QStringList Setup::getDirectionStrings(int directions) {
  QVector<QString> dir = QVector<QString>(4);
     int i = 0;
     if ((directions & EAST) > 0) {
         dir.replace(i++, EAST_DIR);
     }
     if ((directions & WEST) > 0) {
         dir.replace(i++, WEST_DIR);
     }
     if ((directions & NORTH) > 0) {
         dir.replace(i++, NORTH_DIR);
     }
     if ((directions & SOUTH) > 0) {
         dir.replace(i++, SOUTH_DIR);
     }
     return dir.toList();
 }

 /**
  * Converts QString Setup::direction to binary direction
  *
  * @param direction EAST_DIR WEST_DIR NORTH_DIR SOUTH_DIR
  * @return integer representation of a direction
  */
 /*public*//*static*/int Setup::getDirectionInt(QString direction) {
     if (direction==(EAST_DIR)) {
         return EAST;
     } else if (direction==(WEST_DIR)) {
         return WEST;
     } else if (direction==(NORTH_DIR)) {
         return NORTH;
     } else if (direction==(SOUTH_DIR)) {
         return SOUTH;
     } else {
         return 0; // return unknown
     }
 }

 // must synchronize changes with operation-config.dtd
 /*public*//*static*/QDomElement Setup::store()
 {
     QDomElement values;
     //QDomDocument doc;

     QDomElement e = doc.createElement(Xml::OPERATIONS);
     e.appendChild(values = doc.createElement(Xml::RAIL_ROAD));
     values.setAttribute(Xml::NAME, getRailroadName());

     e.appendChild(values = doc.createElement(Xml::SETUP));
     values.setAttribute(Xml::COMMENT, getComment());

     e.appendChild(values = doc.createElement(Xml::SETTINGS));
     values.setAttribute(Xml::MAIN_MENU, isMainMenuEnabled() ? Xml::_TRUE : Xml::_FALSE);

     values.setAttribute(Xml::CLOSE_ON_SAVE, isCloseWindowOnSaveEnabled() ? Xml::_TRUE : Xml::_FALSE);

     values.setAttribute(Xml::AUTO_SAVE, isAutoSaveEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::AUTO_BACKUP, isAutoBackupEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::TRAIN_DIRECTION,  QString::number(getTrainDirection()));
     values.setAttribute(Xml::TRAIN_LENGTH,  QString::number(getMaxTrainLength()));
     values.setAttribute(Xml::MAX_ENGINES,  QString::number(getMaxNumberEngines()));
     values.setAttribute(Xml::HPT,  QString::number(getHorsePowerPerTon()));
     values.setAttribute(Xml::SCALE,  QString::number(getScale()));
     values.setAttribute(Xml::CAR_TYPES, getCarTypes());
     values.setAttribute(Xml::SWITCH_TIME,  QString::number(getSwitchTime()));
     values.setAttribute(Xml::TRAVEL_TIME,  QString::number(getTravelTime()));
     values.setAttribute(Xml::SHOW_VALUE, isValueEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::VALUE_LABEL, getValueLabel());
     values.setAttribute(Xml::SHOW_RFID, isRfidEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::RFID_LABEL, getRfidLabel());
     values.setAttribute(Xml::LENGTH_UNIT, getLengthUnit());
     values.setAttribute(Xml::YEAR_MODELED, getYearModeled());
     // next 7 manifest attributes for backward compatibility TODO remove in future release 2014
 //        values.setAttribute(Xml::PRINT_LOC_COMMENTS, isPrintLocationCommentsEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::PRINT_ROUTE_COMMENTS, isPrintRouteCommentsEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::PRINT_LOADS_EMPTIES, isPrintLoadsAndEmptiesEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::PRINT_TIMETABLE, isPrintTimetableNameEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::USE12HR_FORMAT, is12hrFormatEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::PRINT_VALID, isPrintValidEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::SORT_BY_TRACK, isSortByTrackEnabled() ? Xml::_TRUE : Xml::_FALSE);
     // This one was left out, wait until 2016
     values.setAttribute(Xml::PRINT_HEADERS, isPrintHeadersEnabled() ? Xml::_TRUE : Xml::_FALSE);
     // next three logger attributes for backward compatibility TODO remove in future release 2014
 //        values.setAttribute(Xml::CAR_LOGGER, isCarLoggerEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::ENGINE_LOGGER, isEngineLoggerEnabled() ? Xml::_TRUE : Xml::_FALSE);
 //        values.setAttribute(Xml::TRAIN_LOGGER, isTrainLoggerEnabled() ? Xml::_TRUE : Xml::_FALSE);

     e.appendChild(values = doc.createElement(Xml::PICKUP_ENG_FORMAT));
     storeXmlMessageFormat(values, getPickupEnginePrefix(), getPickupEngineMessageFormat());

     e.appendChild(values = doc.createElement(Xml::DROP_ENG_FORMAT));
     storeXmlMessageFormat(values, getDropEnginePrefix(), getDropEngineMessageFormat());

     e.appendChild(values = doc.createElement(Xml::PICKUP_CAR_FORMAT));
     storeXmlMessageFormat(values, getPickupCarPrefix(), getPickupManifestMessageFormat());

     e.appendChild(values = doc.createElement(Xml::DROP_CAR_FORMAT));
     storeXmlMessageFormat(values, getDropCarPrefix(), getDropManifestMessageFormat());

     e.appendChild(values = doc.createElement(Xml::LOCAL_FORMAT));
     storeXmlMessageFormat(values, getLocalPrefix(), getLocalManifestMessageFormat());

     e.appendChild(values = doc.createElement(Xml::MISSING_CAR_FORMAT));
     storeXmlMessageFormat(values, NONE, getMissingCarMessageFormat());

     e.appendChild(values = doc.createElement(Xml::SWITCH_LIST));
     values.setAttribute(Xml::SAME_AS_MANIFEST, isSwitchListFormatSameAsManifest() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::REAL_TIME, isSwitchListRealTime() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::ALL_TRAINS, isSwitchListAllTrainsEnabled() ? Xml::_TRUE : Xml::_FALSE);

     // save switch list format
     QString format = Xml::PAGE_NORMAL;
     if (getSwitchListPageFormat()==(PAGE_PER_TRAIN)) {
         format = Xml::PAGE_PER_TRAIN;
         values.setAttribute(Xml::PAGE_MODE, Xml::_TRUE); // backwards compatible for versions before 3.11
     } else if (getSwitchListPageFormat()==(PAGE_PER_VISIT)) {
         format = Xml::PAGE_PER_VISIT;
     }
     values.setAttribute(Xml::PAGE_FORMAT, format);

     values.setAttribute(Xml::PRINT_ROUTE_LOCATION, isSwitchListRouteLocationCommentEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::TRACK_SUMMARY, isTrackSummaryEnabled() ? Xml::_TRUE : Xml::_FALSE);

     e.appendChild(values = doc.createElement(Xml::SWITCH_LIST_PICKUP_CAR_FORMAT));
     storeXmlMessageFormat(values, getSwitchListPickupCarPrefix(), getPickupSwitchListMessageFormat());

     e.appendChild(values = doc.createElement(Xml::SWITCH_LIST_DROP_CAR_FORMAT));
     storeXmlMessageFormat(values, getSwitchListDropCarPrefix(), getDropSwitchListMessageFormat());

     e.appendChild(values = doc.createElement(Xml::SWITCH_LIST_LOCAL_FORMAT));
     storeXmlMessageFormat(values, getSwitchListLocalPrefix(), getLocalSwitchListMessageFormat());

     e.appendChild(values = doc.createElement(Xml::PANEL));
     values.setAttribute(Xml::NAME, getPanelName());
     values.setAttribute(Xml::TRAIN_ICONXY, isTrainIconCordEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::TRAIN_ICON_APPEND, isTrainIconAppendEnabled() ? Xml::_TRUE : Xml::_FALSE);

     e.appendChild(values = doc.createElement(Xml::FONT_NAME));
     values.setAttribute(Xml::NAME, getFontName());

     e.appendChild(values = doc.createElement(Xml::FONT_SIZE));
     values.setAttribute(Xml::SIZE,  QString::number(getManifestFontSize()));

     e.appendChild(values = doc.createElement(Xml::PAGE_ORIENTATION));
     values.setAttribute(Xml::MANIFEST, getManifestOrientation());
     values.setAttribute(Xml::SWITCH_LIST, getSwitchListOrientation());

     e.appendChild(values = doc.createElement(Xml::MANIFEST_COLORS));
     values.setAttribute(Xml::DROP_COLOR, getDropTextColor());
     values.setAttribute(Xml::PICKUP_COLOR, getPickupTextColor());
     values.setAttribute(Xml::LOCAL_COLOR, getLocalTextColor());

     e.appendChild(values = doc.createElement(Xml::TAB));
     values.setAttribute(Xml::ENABLED, isTabEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::LENGTH,  QString::number(getTab1Length()));
     values.setAttribute(Xml::TAB2_LENGTH,  QString::number(getTab2Length()));
     values.setAttribute(Xml::TAB3_LENGTH,  QString::number(getTab3Length()));

     e.appendChild(values = doc.createElement(Xml::MANIFEST));
     values.setAttribute(Xml::PRINT_LOC_COMMENTS, isPrintLocationCommentsEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PRINT_ROUTE_COMMENTS, isPrintRouteCommentsEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PRINT_LOADS_EMPTIES, isPrintLoadsAndEmptiesEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PRINT_TIMETABLE, isPrintTimetableNameEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::USE12HR_FORMAT, is12hrFormatEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PRINT_VALID, isPrintValidEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::SORT_BY_TRACK, isSortByTrackEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PRINT_HEADERS, isPrintHeadersEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::TRUNCATE, isTruncateManifestEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::USE_DEPARTURE_TIME, isUseDepartureTimeEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::USE_EDITOR, isManifestEditorEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PRINT_CABOOSE_LOAD, isPrintCabooseLoadEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PRINT_PASSENGER_LOAD, isPrintPassengerLoadEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::HAZARDOUS_MSG, getHazardousMsg());

     // backward compatible, remove in 2015
 //        e.appendChild(values = doc.createElement(Xml::COLUMN_FORMAT));
 //        values.setAttribute(Xml::TWO_COLUMNS, getManifestFormat() == TWO_COLUMN_FORMAT ? Xml::_TRUE : Xml::_FALSE);
     // new format June 2014
     e.appendChild(values = doc.createElement(Xml::MANIFEST_FORMAT));

     // save manifest format
     QString value = Xml::STANDARD;
     if (getManifestFormat()==(TWO_COLUMN_FORMAT)) {
         value = Xml::TWO_COLUMN;
     } else if (getManifestFormat()==(TWO_COLUMN_TRACK_FORMAT)) {
         value = Xml::TWO_COLUMN_TRACK;
     }
     values.setAttribute(Xml::VALUE, value);

     if (getManifestLogoURL()!=(NONE)) {
         values = doc.createElement(Xml::MANIFEST_LOGO);
         values.setAttribute(Xml::NAME, getManifestLogoURL());
         e.appendChild(values);
     }

     e.appendChild(values = doc.createElement(Xml::BUILD_OPTIONS));
     values.setAttribute(Xml::AGGRESSIVE, isBuildAggressive() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::NUMBER_PASSES,  QString::number(getNumberPasses()));

     values.setAttribute(Xml::ALLOW_LOCAL_INTERCHANGE, isLocalInterchangeMovesEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::ALLOW_LOCAL_SPUR, isLocalSpurMovesEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::ALLOW_LOCAL_YARD, isLocalYardMovesEnabled() ? Xml::_TRUE : Xml::_FALSE);

     values.setAttribute(Xml::STAGING_RESTRICTION_ENABLED, isTrainIntoStagingCheckEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::STAGING_TRACK_AVAIL, isStagingTrackImmediatelyAvail() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::ALLOW_RETURN_STAGING, isAllowReturnToStagingEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PROMPT_STAGING_ENABLED, isPromptFromStagingEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::PROMPT_TO_STAGING_ENABLED, isPromptToStagingEnabled() ? Xml::_TRUE : Xml::_FALSE);

     values.setAttribute(Xml::GENERATE_CSV_MANIFEST, isGenerateCsvManifestEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::GENERATE_CSV_SWITCH_LIST, isGenerateCsvSwitchListEnabled() ? Xml::_TRUE : Xml::_FALSE);

     e.appendChild(values = doc.createElement(Xml::BUILD_REPORT));
     values.setAttribute(Xml::LEVEL, getBuildReportLevel());
     values.setAttribute(Xml::ROUTER_LEVEL, getRouterBuildReportLevel());
     values.setAttribute(Xml::USE_EDITOR, isBuildReportEditorEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::INDENT, isBuildReportIndentEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::ALWAYS_PREVIEW, isBuildReportAlwaysPreviewEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::FONT_SIZE,  QString::number(getBuildReportFontSize()));

     // new format for router options
     e.appendChild(values = doc.createElement(Xml::ROUTER));
     values.setAttribute(Xml::CAR_ROUTING_ENABLED, isCarRoutingEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::CAR_ROUTING_VIA_YARDS, isCarRoutingViaYardsEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::CAR_ROUTING_VIA_STAGING, isCarRoutingViaStagingEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::FORWARD_TO_YARD, isForwardToYardEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::ONLY_ACTIVE_TRAINS, isOnlyActiveTrainsEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::CHECK_CAR_DESTINATION, isCheckCarDestinationEnabled() ? Xml::_TRUE : Xml::_FALSE);

     // new format for logger options
     e.appendChild(values = doc.createElement(Xml::LOGGER));
     values.setAttribute(Xml::CAR_LOGGER, isCarLoggerEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::ENGINE_LOGGER, isEngineLoggerEnabled() ? Xml::_TRUE : Xml::_FALSE);
     values.setAttribute(Xml::TRAIN_LOGGER, isTrainLoggerEnabled() ? Xml::_TRUE : Xml::_FALSE);

     e.appendChild(values = doc.createElement(Xml::OWNER));
     values.setAttribute(Xml::NAME, getOwnerName());

     e.appendChild(values = doc.createElement(Xml::ICON_COLOR));
     values.setAttribute(Xml::NORTH, getTrainIconColorNorth());
     values.setAttribute(Xml::SOUTH, getTrainIconColorSouth());
     values.setAttribute(Xml::EAST, getTrainIconColorEast());
     values.setAttribute(Xml::WEST, getTrainIconColorWest());
     values.setAttribute(Xml::LOCAL, getTrainIconColorLocal());
     values.setAttribute(Xml::TERMINATE, getTrainIconColorTerminate());

     e.appendChild(values = doc.createElement(Xml::COMMENTS));
     values.setAttribute(Xml::MISPLACED_CARS, getMiaComment());

     if (isVsdPhysicalLocationEnabled()) {
         e.appendChild(values = doc.createElement(Xml::VSD));
         values.setAttribute(Xml::ENABLE_PHYSICAL_LOCATIONS, isVsdPhysicalLocationEnabled() ? Xml::_TRUE : Xml::_FALSE);
     }

     // Save CATS setting
     e.appendChild(values = doc.createElement(Xml::CATS));
     values.setAttribute(Xml::EXACT_LOCATION_NAME, AbstractOperationsServer::isExactLoationNameEnabled() ? Xml::_TRUE
             : Xml::_FALSE);

     return e;
 }

 /*private*//*static*/void Setup::storeXmlMessageFormat(QDomElement values, QString prefix, QStringList messageFormat)
 {
   values.setAttribute(Xml::PREFIX, prefix);
   QString buf;// = new StringBuffer();
   stringToKeyConversion(messageFormat);
   foreach (QString attribute, messageFormat) {
       buf.append(attribute + ",");
   }
   values.setAttribute(Xml::SETTING, buf/*.toString()*/);
 }

 /*public*//*static*/void Setup::load(QDomElement e)
 {
  Logger* log = new Logger("Setup");
  QString tn = e.tagName();
  if (e.firstChildElement(Xml::OPERATIONS).isNull())
  {
   log->debug("operation setup values missing");
   return;
  }
  QDomElement operations = e.firstChildElement(Xml::OPERATIONS);
  QString a;

  if ((operations.firstChildElement(Xml::RAIL_ROAD) != QDomElement())
         && (a = operations.firstChildElement(Xml::RAIL_ROAD).attribute(Xml::NAME)) != "") {
         QString name = a;
         if (log->isDebugEnabled()) {
             log->debug(tr("railroadName: %1").arg(name));
         }
         railroadName = name; // don't set the dirty bit
     }

     if ((operations.firstChildElement(Xml::SETUP) != QDomElement())
         && (a = operations.firstChildElement(Xml::SETUP).attribute(Xml::COMMENT)) != "") {
         QString comment = a;
         if (log->isDebugEnabled()) {
             log->debug(tr("setup comment: %1").arg(comment));
         }
         setupComment = comment;
     }

     if (operations.firstChildElement(Xml::SETTINGS) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::MAIN_MENU)) != NULL) {
             QString enabled = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("mainMenu: %1").arg(enabled));
             }
             setMainMenuEnabled(enabled==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::CLOSE_ON_SAVE)) != NULL) {
             QString enabled = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("closeOnSave: %1").arg(enabled));
             }
             setCloseWindowOnSaveEnabled(enabled==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::TRAIN_DIRECTION)) != NULL) {
             QString dir = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("direction: %1").arg(dir));
             }
             bool ok;
                 setTrainDirection(dir.toInt(&ok));
                 if(!ok) {
                 Logger::error(tr("Train direction (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::TRAIN_LENGTH)) != NULL) {
             QString length = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("Max train length: %1").arg(length));
             }
             bool ok;
                 setMaxTrainLength(length.toInt(&ok));
                 if(!ok) {
                 Logger::error(tr("Train maximum length (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::MAX_ENGINES)) != NULL) {
             QString size = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("Max number of engines: %1").arg(size));
             }
             //try {
             bool ok;
              setMaxNumberEngines(size.toInt(&ok));
             if(!ok) {
                 Logger::error(tr("Maximum number of engines (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::HPT)) != NULL) {
             QString value = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("HPT: %1").arg(value));
             }
             //try {
             bool ok;
                 setHorsePowerPerTon(value.toInt(&ok));
             if(!ok) {
                 Logger::error(tr("Train HPT (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::SCALE)) != NULL) {
             QString scale = a;
             if (log->isDebugEnabled()) {
                 log->debug("scale: " + scale);
             }
             //try {
             bool ok;
              setScale(scale.toInt(&ok));
             if(!ok) {
                 Logger::error(tr("Scale (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::CAR_TYPES)) != NULL) {
             QString types = a;
             if (log->isDebugEnabled()) {
                 log->debug("CarTypes: " + types);
             }
             setCarTypes(types);
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::SWITCH_TIME)) != NULL) {
             QString minutes = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("switchTime: %1").arg(minutes));
             }
             bool ok;
                 setSwitchTime(minutes.toInt(&ok));
                 if(!ok) {
                 Logger::error(tr("Switch time (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::TRAVEL_TIME)) != NULL) {
             QString minutes = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("travelTime: %1").arg(minutes));
             }
             bool ok;
             setTravelTime(minutes.toInt(&ok));
             if(!ok){
                 Logger::error(tr("Travel time (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::SHOW_VALUE)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("showValue: %1").arg(enable));
             }
             setValueEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::VALUE_LABEL)) != NULL) {
             QString label = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("valueLabel: %1").arg(label));
             }
             setValueLabel(label);
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::SHOW_RFID)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("showRfid: %1").arg(enable));
             }
             setRfidEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::RFID_LABEL)) != NULL) {
             QString label = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("rfidLabel: %1").arg(label));
             }
             setRfidLabel(label);
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::LENGTH_UNIT)) != NULL) {
             QString unit = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("lengthUnit: %1").arg(unit));
             }
             setLengthUnit(unit);
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::YEAR_MODELED)) != NULL) {
             QString year = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("yearModeled: %1").arg(year));
             }
             setYearModeled(year);
         }
         // next seven attributes are for backward compatibility
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::PRINT_LOC_COMMENTS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("printLocComments: %1").arg(enable));
             }
             setPrintLocationCommentsEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::PRINT_ROUTE_COMMENTS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("printRouteComments: %1").arg(enable));
             }
             setPrintRouteCommentsEnabled(enable==(Xml::_TRUE));
         }

         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::PRINT_LOADS_EMPTIES)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("printLoadsEmpties: %1").arg(enable));
             }
             setPrintLoadsAndEmptiesEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::PRINT_TIMETABLE)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("printTimetable: %1").arg(enable));
             }
             setPrintTimetableNameEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::USE12HR_FORMAT)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("use12hrFormat: %1").arg(enable));
             }
             set12hrFormatEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::PRINT_VALID)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("printValid: %1").arg(enable));
             }
             setPrintValidEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::SORT_BY_TRACK)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("sortByTrack: %1").arg(enable));
             }
             setSortByTrackEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::PRINT_HEADERS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("printHeaders: %1").arg(enable));
             }
             setPrintHeadersEnabled(enable==(Xml::_TRUE));
         }
     }
 #if 1
     if (operations.firstChildElement(Xml::PICKUP_ENG_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::PICKUP_ENG_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setPickupEnginePrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::PICKUP_ENG_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("pickupEngFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             keyToStringConversion(keys);
             setPickupEngineMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::DROP_ENG_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::DROP_ENG_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setDropEnginePrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::DROP_ENG_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("dropEngFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             keyToStringConversion(keys);
             setDropEngineMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::PICKUP_CAR_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::PICKUP_CAR_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setPickupCarPrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::PICKUP_CAR_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("pickupCarFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             replaceOldFormat(keys);
             keyToStringConversion(keys);
             setPickupManifestMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::DROP_CAR_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::DROP_CAR_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setDropCarPrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::DROP_CAR_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("dropCarFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             replaceOldFormat(keys);
             keyToStringConversion(keys);
             setDropManifestMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::LOCAL_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::LOCAL_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setLocalPrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::LOCAL_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("localFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             replaceOldFormat(keys);
             keyToStringConversion(keys);
             setLocalManifestMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::MISSING_CAR_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::MISSING_CAR_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("missingCarFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             keyToStringConversion(keys);
             setMissingCarMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::SWITCH_LIST) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST).attribute(Xml::SAME_AS_MANIFEST)) != NULL) {
             QString b = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("sameAsManifest: %1").arg(b));
             }
             setSwitchListFormatSameAsManifest(b==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST).attribute(Xml::REAL_TIME)) != NULL) {
             QString b = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("realTime: %1").arg(b));
             }
             switchListRealTime = b==(Xml::_TRUE);
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST).attribute(Xml::ALL_TRAINS)) != NULL) {
             QString b = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("allTrains: %1").arg(b));
             }
             switchListAllTrains = b==(Xml::_TRUE);
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST).attribute(Xml::PAGE_FORMAT)) != NULL) {
             //switch (a) {
                 //case Xml::PAGE_NORMAL:
          if(a ==Xml::PAGE_NORMAL )
                     switchListPageFormat = PAGE_NORMAL;
//                     break;
//                 case Xml::PAGE_PER_TRAIN:
          else if(a == Xml::PAGE_PER_TRAIN)
                     switchListPageFormat = PAGE_PER_TRAIN;
//                     break;
//                 case Xml::PAGE_PER_VISIT:
          else if(a == Xml::PAGE_PER_VISIT)
                     switchListPageFormat = PAGE_PER_VISIT;
//                     break;
//                 default:
          else
                     Logger::error(tr("Unknown switch list page format %1").arg(a));
//             }
         } // old way to save switch list page format pre 3.11
         else if ((a = operations.firstChildElement(Xml::SWITCH_LIST).attribute(Xml::PAGE_MODE)) != NULL) {
             QString b = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("old style pageMode: %1").arg(b));
             }
             if (b==(Xml::_TRUE)) {
                 switchListPageFormat = PAGE_PER_TRAIN;
             }
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST).attribute(Xml::PRINT_ROUTE_LOCATION)) != NULL) {
             QString b = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("print Setup::route location comment: %1").arg(b));
             }
             setSwitchListRouteLocationCommentEnabled(b==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST).attribute(Xml::TRACK_SUMMARY)) != NULL) {
             QString b = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("track summary: %1").arg(b));
             }
             setTrackSummaryEnabled(b==(Xml::_TRUE));
         }
     }
     if (operations.firstChildElement(Xml::SWITCH_LIST_PICKUP_CAR_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST_PICKUP_CAR_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setSwitchListPickupCarPrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST_PICKUP_CAR_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug("switchListpickupCarFormat: " + setting);
             }
             QStringList keys = setting.split(",");
             replaceOldFormat(keys);
             keyToStringConversion(keys);
             setPickupSwitchListMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::SWITCH_LIST_DROP_CAR_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST_DROP_CAR_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setSwitchListDropCarPrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST_DROP_CAR_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("switchListDropCarFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             replaceOldFormat(keys);
             keyToStringConversion(keys);
             setDropSwitchListMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::SWITCH_LIST_LOCAL_FORMAT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST_LOCAL_FORMAT).attribute(Xml::PREFIX)) != NULL) {
             setSwitchListLocalPrefix(a);
         }
         if ((a = operations.firstChildElement(Xml::SWITCH_LIST_LOCAL_FORMAT).attribute(Xml::SETTING)) != NULL) {
             QString setting = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("switchListLocalFormat: %1").arg(setting));
             }
             QStringList keys = setting.split(",");
             replaceOldFormat(keys);
             keyToStringConversion(keys);
             setLocalSwitchListMessageFormat(keys);
         }
     }
     if (operations.firstChildElement(Xml::PANEL) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::PANEL).attribute(Xml::NAME)) != NULL) {
             QString panel = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("panel: %1").arg(panel));
             }
             setPanelName(panel);
         }
         if ((a = operations.firstChildElement(Xml::PANEL).attribute(Xml::TRAIN_ICONXY)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("TrainIconXY: " + enable);
             }
             setTrainIconCordEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::PANEL).attribute(Xml::TRAIN_ICON_APPEND)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("TrainIconAppend: " + enable);
             }
             setTrainIconAppendEnabled(enable==(Xml::_TRUE));
         }
     }
     if ((operations.firstChildElement(Xml::FONT_NAME) != QDomElement())
             && (a = operations.firstChildElement(Xml::FONT_NAME).attribute(Xml::NAME)) != NULL) {
         QString font = a;
         if (log->isDebugEnabled()) {
             log->debug("fontName: " + font);
         }
         setFontName(font);
     }
     if ((operations.firstChildElement(Xml::FONT_SIZE) != QDomElement())
             && (a = operations.firstChildElement(Xml::FONT_SIZE).attribute(Xml::SIZE)) != NULL) {
         QString size = a;
         if (log->isDebugEnabled()) {
             log->debug("fontsize: " + size);
         }
         bool ok;
             setManifestFontSize(size.toInt(&ok));
         if(!ok) {
             Logger::error(tr("Manifest font size (%1) isn't a valid number").arg(a));
         }
     }
     if ((operations.firstChildElement(Xml::PAGE_ORIENTATION) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::PAGE_ORIENTATION).attribute(Xml::MANIFEST)) != NULL) {
             QString orientation = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifestOrientation: " + orientation);
             }
             setManifestOrientation(orientation);
         }
         if ((a = operations.firstChildElement(Xml::PAGE_ORIENTATION).attribute(Xml::SWITCH_LIST)) != NULL) {
             QString orientation = a;
             if (log->isDebugEnabled()) {
                 log->debug("switchListOrientation: " + orientation);
             }
             setSwitchListOrientation(orientation);
         }
     }
     if ((operations.firstChildElement(Xml::MANIFEST_COLORS) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::MANIFEST_COLORS).attribute(Xml::DROP_COLOR)) != NULL) {
             QString dropColor = a;
             if (log->isDebugEnabled()) {
                 log->debug("dropColor: " + dropColor);
             }
             setDropTextColor(dropColor);
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST_COLORS).attribute(Xml::PICKUP_COLOR)) != NULL) {
             QString pickupColor = a;
             if (log->isDebugEnabled()) {
                 log->debug("pickupColor: " + pickupColor);
             }
             setPickupTextColor(pickupColor);
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST_COLORS).attribute(Xml::LOCAL_COLOR)) != NULL) {
             QString localColor = a;
             if (log->isDebugEnabled()) {
                 log->debug("localColor: " + localColor);
             }
             setLocalTextColor(localColor);
         }
     }
     if ((operations.firstChildElement(Xml::TAB) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::TAB).attribute(Xml::ENABLED)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("tab: " + enable);
             }
             setTabEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::TAB).attribute(Xml::LENGTH)) != NULL) {
             QString length = a;
             if (log->isDebugEnabled()) {
                 log->debug("tab 1 length: " + length);
             }
             bool ok;
                 setTab1length(length.toInt(&ok));
             if(!ok) {
                 Logger::error(tr("Tab 1 length (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::TAB).attribute(Xml::TAB2_LENGTH)) != NULL) {
             QString length = a;
             if (log->isDebugEnabled()) {
                 log->debug("tab 2 length: " + length);
             }
             bool ok;
                 setTab2length(length.toInt(&ok));
             if(!ok) {
                 Logger::error(tr("Tab 2 length (%1) isn't a valid number").arg(a));
             }
         }
         if ((a = operations.firstChildElement(Xml::TAB).attribute(Xml::TAB3_LENGTH)) != NULL) {
             QString length = a;
             if (log->isDebugEnabled()) {
                 log->debug("tab 3 length: " + length);
             }
             bool ok;
                 setTab3length(length.toInt(&ok));
             if(!ok) {
                 Logger::error(tr("Tab 3 length (%1) isn't a valid number").arg(a));
             }
         }
     }
     if ((operations.firstChildElement(Xml::MANIFEST) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_LOC_COMMENTS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest printLocComments: " + enable);
             }
             setPrintLocationCommentsEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_ROUTE_COMMENTS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest printRouteComments: " + enable);
             }
             setPrintRouteCommentsEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_LOADS_EMPTIES)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest printLoadsEmpties: " + enable);
             }
             setPrintLoadsAndEmptiesEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_TIMETABLE)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest printTimetable: " + enable);
             }
             setPrintTimetableNameEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::USE12HR_FORMAT)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest use12hrFormat: " + enable);
             }
             set12hrFormatEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_VALID)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest printValid: " + enable);
             }
             setPrintValidEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::SORT_BY_TRACK)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest sortByTrack: " + enable);
             }
             setSortByTrackEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_HEADERS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest print Setup::headers: " + enable);
             }
             setPrintHeadersEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::TRUNCATE)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest truncate: " + enable);
             }
             setTruncateManifestEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::USE_DEPARTURE_TIME)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest use departure time: " + enable);
             }
             setUseDepartureTimeEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::USE_EDITOR)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest useEditor: " + enable);
             }
             setManifestEditorEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_CABOOSE_LOAD)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest print Setup::caboose load: " + enable);
             }
             setPrintCabooseLoadEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::PRINT_PASSENGER_LOAD)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest print Setup::passenger load: " + enable);
             }
             setPrintPassengerLoadEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::MANIFEST).attribute(Xml::HAZARDOUS_MSG)) != NULL) {
             QString message = a;
             if (log->isDebugEnabled()) {
                 log->debug("manifest hazardousMsg: " + message);
             }
             setHazardousMsg(message);
         }
     }
     if ((operations.firstChildElement(Xml::MANIFEST_FORMAT) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::MANIFEST_FORMAT).attribute(Xml::VALUE)) != NULL) {
//             switch (a) {
//                 case Xml::STANDARD:
          if(a == Xml::STANDARD)
                     manifestFormat = STANDARD_FORMAT;
//                     break;
//                 case Xml::TWO_COLUMN:
          else if(a == Xml::TWO_COLUMN)
                     manifestFormat = TWO_COLUMN_FORMAT;
//                     break;
//                 case Xml::TWO_COLUMN_TRACK:
          else if(a==Xml::TWO_COLUMN_TRACK)
                     manifestFormat = TWO_COLUMN_TRACK_FORMAT;
//                     break;
//                 default:
          else
                     log->debug("Unknown manifest format");
//             }
         }
     } else if ((operations.firstChildElement(Xml::COLUMN_FORMAT) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::COLUMN_FORMAT).attribute(Xml::TWO_COLUMNS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("two columns: " + enable);
             }
             if (enable==(Xml::_TRUE)) {
                 setManifestFormat(TWO_COLUMN_FORMAT);
             }
         }
     }
     // get manifest logo
     if ((operations.firstChildElement(Xml::MANIFEST_LOGO) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::MANIFEST_LOGO).attribute(Xml::NAME)) != NULL) {
             setManifestLogoURL(a);
         }
     }
     if ((operations.firstChildElement(Xml::BUILD_OPTIONS) != QDomElement())) {
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::AGGRESSIVE)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("aggressive: " + enable);
             }
             setBuildAggressive(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::NUMBER_PASSES)) != NULL) {
             QString number = a;
             if (log->isDebugEnabled()) {
                 log->debug(tr("number of passes: %1").arg(number));
             }
             bool ok;
                 setNumberPasses(number.toInt(&ok));
             if(!ok) {
                 log->debug("Number of passes isn't a number");
             }
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::ALLOW_LOCAL_INTERCHANGE)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("noLocalInterchange: " + enable);
             }
             setLocalInterchangeMovesEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::ALLOW_LOCAL_SPUR)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("noLocalSpur: " + enable);
             }
             setLocalSpurMovesEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::ALLOW_LOCAL_YARD)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("noLocalYard: " + enable);
             }
             setLocalYardMovesEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::STAGING_RESTRICTION_ENABLED)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("stagingRestrictionEnabled: " + enable);
             }
             setTrainIntoStagingCheckEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::STAGING_TRACK_AVAIL)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("stagingTrackAvail: " + enable);
             }
             setStagingTrackImmediatelyAvail(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::ALLOW_RETURN_STAGING)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("allowReturnStaging: " + enable);
             }
             setAllowReturnToStagingEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::PROMPT_STAGING_ENABLED)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("promptStagingEnabled: " + enable);
             }
             setPromptFromStagingEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::PROMPT_TO_STAGING_ENABLED)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("promptToStagingEnabled: " + enable);
             }
             setPromptToStagingEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::GENERATE_CSV_MANIFEST)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("generateCvsManifest: " + enable);
             }
             generateCsvManifest = enable==(Xml::_TRUE);
         }
         if ((a = operations.firstChildElement(Xml::BUILD_OPTIONS).attribute(Xml::GENERATE_CSV_SWITCH_LIST)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("generateCvsSwitchList: " + enable);
             }
             generateCsvSwitchList = enable==(Xml::_TRUE);
         }
     }
     if (operations.firstChildElement(Xml::BUILD_REPORT) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::BUILD_REPORT).attribute(Xml::LEVEL)) != NULL) {
             QString level = a;
             if (log->isDebugEnabled()) {
                 log->debug("buildReportLevel: " + level);
             }
             setBuildReportLevel(level);
         }
         if ((a = operations.firstChildElement(Xml::BUILD_REPORT).attribute(Xml::ROUTER_LEVEL)) != NULL) {
             QString level = a;
             if (log->isDebugEnabled()) {
                 log->debug("routerBuildReportLevel: " + level);
             }
             setRouterBuildReportLevel(level);
         }
         if ((a = operations.firstChildElement(Xml::BUILD_REPORT).attribute(Xml::USE_EDITOR)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("build report useEditor: " + enable);
             }
             setBuildReportEditorEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_REPORT).attribute(Xml::INDENT)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("build report indent: " + enable);
             }
             setBuildReportIndentEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::BUILD_REPORT).attribute(Xml::FONT_SIZE)) != NULL) {
             QString size = a;
             if (log->isDebugEnabled()) {
                 log->debug("build font size: " + size);
             }
             bool ok;
                 setBuildReportFontSize(size.toInt(&ok));
             if(!ok) {
                 Logger::error("Build report font size ({}) isn't a valid number", a);
             }
         }
         if ((a = operations.firstChildElement(Xml::BUILD_REPORT).attribute(Xml::ALWAYS_PREVIEW)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("build report always preview: " + enable);
             }
             setBuildReportAlwaysPreviewEnabled(enable==(Xml::_TRUE));
         }
     }

     if (operations.firstChildElement(Xml::ROUTER) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::ROUTER).attribute(Xml::CAR_ROUTING_ENABLED)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carRoutingEnabled: " + enable);
             }
             setCarRoutingEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::ROUTER).attribute(Xml::CAR_ROUTING_VIA_YARDS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carRoutingViaYards: " + enable);
             }
             setCarRoutingViaYardsEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::ROUTER).attribute(Xml::CAR_ROUTING_VIA_STAGING)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carRoutingViaStaging: " + enable);
             }
             setCarRoutingViaStagingEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::ROUTER).attribute(Xml::FORWARD_TO_YARD)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("forwardToYard: " + enable);
             }
             setForwardToYardEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::ROUTER).attribute(Xml::ONLY_ACTIVE_TRAINS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("onlyActiveTrains: " + enable);
             }
             setOnlyActiveTrainsEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::ROUTER).attribute(Xml::CHECK_CAR_DESTINATION)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("checkCarDestination: " + enable);
             }
             setCheckCarDestinationEnabled(enable==(Xml::_TRUE));
         }
     } else if (operations.firstChildElement(Xml::SETTINGS) != QDomElement()) {
         // the next four items are for backwards compatibility
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::CAR_ROUTING_ENABLED)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carRoutingEnabled: " + enable);
             }
             setCarRoutingEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::CAR_ROUTING_VIA_YARDS)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carRoutingViaYards: " + enable);
             }
             setCarRoutingViaYardsEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::CAR_ROUTING_VIA_STAGING)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carRoutingViaStaging: " + enable);
             }
             setCarRoutingViaStagingEnabled(enable==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::FORWARD_TO_YARD)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("forwardToYard: " + enable);
             }
             setForwardToYardEnabled(enable==(Xml::_TRUE));
         }
     }
 #endif
     if ((operations.firstChildElement(Xml::OWNER) != QDomElement())
         && (a = operations.firstChildElement(Xml::OWNER).attribute(Xml::NAME)) != "") {
         QString owner = a;
         if (log->isDebugEnabled()) {
             log->debug("owner: " + owner);
         }
         setOwnerName(owner);
     }
     if (operations.firstChildElement(Xml::ICON_COLOR) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::ICON_COLOR).attribute(Xml::NORTH)) != NULL) {
             QString color = a;
             if (log->isDebugEnabled()) {
                 log->debug("north color: " + color);
             }
             setTrainIconColorNorth(color);
         }
         if ((a = operations.firstChildElement(Xml::ICON_COLOR).attribute(Xml::SOUTH)) != NULL) {
             QString color = a;
             if (log->isDebugEnabled()) {
                 log->debug("south color: " + color);
             }
             setTrainIconColorSouth(color);
         }
         if ((a = operations.firstChildElement(Xml::ICON_COLOR).attribute(Xml::EAST)) != NULL) {
             QString color = a;
             if (log->isDebugEnabled()) {
                 log->debug("east color: " + color);
             }
             setTrainIconColorEast(color);
         }
         if ((a = operations.firstChildElement(Xml::ICON_COLOR).attribute(Xml::WEST)) != NULL) {
             QString color = a;
             if (log->isDebugEnabled()) {
                 log->debug("west color: " + color);
             }
             setTrainIconColorWest(color);
         }
         if ((a = operations.firstChildElement(Xml::ICON_COLOR).attribute(Xml::LOCAL)) != NULL) {
             QString color = a;
             if (log->isDebugEnabled()) {
                 log->debug("local color: " + color);
             }
             setTrainIconColorLocal(color);
         }
         if ((a = operations.firstChildElement(Xml::ICON_COLOR).attribute(Xml::TERMINATE)) != NULL) {
             QString color = a;
             if (log->isDebugEnabled()) {
                 log->debug("terminate color: " + color);
             }
             setTrainIconColorTerminate(color);
         }
     }
     if (operations.firstChildElement(Xml::COMMENTS) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::COMMENTS).attribute(Xml::MISPLACED_CARS)) != NULL) {
             QString comment = a;
             if (log->isDebugEnabled()) {
                 log->debug("Misplaced comment: " + comment);
             }
             setMiaComment(comment);
         }
     }

     if (operations.firstChildElement(Xml::VSD) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::VSD).attribute(Xml::ENABLE_PHYSICAL_LOCATIONS)) != NULL) {
             QString enable = a;
             setVsdPhysicalLocationEnabled(enable==(Xml::_TRUE));
         }
     }

     if (operations.firstChildElement(Xml::CATS) != QDomElement())
     {
         if ((a = operations.firstChildElement(Xml::CATS).attribute(Xml::EXACT_LOCATION_NAME)) != NULL)
         {
             QString enable = a;
             AbstractOperationsServer::setExactLocationName(enable==(Xml::_TRUE));
         }
     }

     if (operations.firstChildElement(Xml::SETTINGS) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::AUTO_SAVE)) != NULL) {
             QString enabled = a;
             if (log->isDebugEnabled()) {
                 log->debug("autoSave: " + enabled);
             }
             setAutoSaveEnabled(enabled==(Xml::_TRUE));
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::AUTO_BACKUP)) != NULL) {
             QString enabled = a;
             if (log->isDebugEnabled()) {
                 log->debug("autoBackup: " + enabled);
             }
             setAutoBackupEnabled(enabled==(Xml::_TRUE));
         }
     }

     if (operations.firstChildElement(Xml::LOGGER) != QDomElement()) {
         if ((a = operations.firstChildElement(Xml::LOGGER).attribute(Xml::CAR_LOGGER)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carLogger: " + enable);
             }
             carLogger = enable==(Xml::_TRUE);
         }
         if ((a = operations.firstChildElement(Xml::LOGGER).attribute(Xml::ENGINE_LOGGER)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("engineLogger: " + enable);
             }
             engineLogger = enable==(Xml::_TRUE);
         }
         if ((a = operations.firstChildElement(Xml::LOGGER).attribute(Xml::TRAIN_LOGGER)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("trainLogger: " + enable);
             }
             trainLogger = enable==(Xml::_TRUE);
         }
     } else if (operations.firstChildElement(Xml::SETTINGS) != QDomElement()) {
         // for backward compatibility
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::CAR_LOGGER)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("carLogger: " + enable);
             }
             carLogger = enable==(Xml::_TRUE);
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::ENGINE_LOGGER)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("engineLogger: " + enable);
             }
             engineLogger = enable==(Xml::_TRUE);
         }
         if ((a = operations.firstChildElement(Xml::SETTINGS).attribute(Xml::TRAIN_LOGGER)) != NULL) {
             QString enable = a;
             if (log->isDebugEnabled()) {
                 log->debug("trainLogger: " + enable);
             }
             trainLogger = enable==(Xml::_TRUE);
         }
     }

 }

 // replace old pickup and drop message keys
 // Change happened from 2.11.3 to 2.11.4
 // 4/16/2014
 // replace three keys that have spaces in the text
 /*private*//*static*/void Setup::replaceOldFormat(QStringList format) {
  for (int i = 0; i < format.length(); i++) {
         if (format[i]==("Pickup Msg")) // NOI18N
         {
             format[i] = PICKUP_COMMENT;
         } else if (format[i]==("Drop Msg")) // NOI18N
         {
             format[i] = DROP_COMMENT;
         }
         // three keys with spaces that need conversion
         if (format[i]==("PickUp Msg")) // NOI18N
         {
             format[i] = "PickUp_Msg"; // NOI18N
         } else if (format[i]==("SetOut Msg")) // NOI18N
         {
             format[i] = "SetOut_Msg"; // NOI18N
         } else if (format[i]==("Final Dest")) // NOI18N
         {
             format[i] = "Final_Dest"; // NOI18N
         }
     }
 }
 #if 1
 /**
  * Converts the xml key to the proper locale text
  *
  * @param keys
  */
 /*private*//*static*/void Setup::keyToStringConversion(QStringList keys) {
     for (int i = 0; i < keys.length(); i++) {
         if (keys[i]==(BLANK)) {
             continue;
         }
         // TODO:
//         try {
//             keys[i] = tr(keys[i]);
//         } catch (Exception e) {
//             log->debug("Key {}: ({}) not found", i, keys[i]);
//         }

     }
 }

 /*private*/  /*static final*/ QStringList attributtes = QStringList() << "Road" << "Number" << "Type" << "Model" << "Length" << "Load" << "Color" <<
         "Track" << "Destination" << "Dest&Track" << "Final_Dest" << "FD&Track" << "Location" << "Consist" << "Kernel" << "Kernel_Size" << "Owner" <<
         "RWE" << "Comment" << "SetOut_Msg" << "PickUp_Msg" << "Hazardous" << "Tab";
// /*private*/  /*static final*/ QStringList trAttr = QStringList() << tr("Road ") << tr("Number ") << tr("Type ") << tr("Model ") << tr("Length ") << tr("Load ") << tr("Color") <<
//         tr("Track ") << tr("Destination ") << tr("Dest&Track ") << tr("Final_Dest ") << tr("FD&Track ") << tr("Location ") << tr("Consist ") << tr("Kernel ") << tr("Kernel_Size ") << tr("Owner") <<
//         tr("RWE ") << tr("Comment ") << tr("SetOut_Msg ") << tr("PickUp_Msg ") << tr("Hazardous ") << tr("Tab");

 #endif
 /**
  * Converts the strings into English tags for xml storage
  *
  * @param strings
  */
 /*private*//*static*/void Setup::stringToKeyConversion(QStringList strings)
 {
 #if 0
     Locale locale = Locale.ROOT;
     for (int Setup::i = 0; i < strings.length; i++) {
         QString Setup::old = strings[i];
         if (old==(BLANK)) {
             continue;
         }
         for (QString Setup::attribute : attributtes) {
             if (strings[i]==(tr(attribute))) {
                 strings[i] = tr(locale, attribute);
                 break;
             }
         }
         // log->debug("Converted {} to %1").arg(old, strings[i]);
     }
 #endif
 }
 ///*static*/ PropertyChangeSupport* Setup::pcs = new PropertyChangeSupport("Setup");

 #if 0

 /*public*//*static*/synchronized void addPropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.addPropertyChangeListener(l);
 }

 /*public*//*static*/synchronized void removePropertyChangeListener(java.beans.PropertyChangeListener l) {
     pcs.removePropertyChangeListener(l);
 }
 #endif
 /*protected*//*static*/void Setup::setDirtyAndFirePropertyChange(QString p, QVariant old, QVariant n) {
     Operations::OperationsSetupXml::instance()->setDirty(true);
 //    pcs.firePropertyChange(p, old, n);
 }

 QDomDocument Setup::doc= QDomDocument();
 /*public*/ void Setup::setDoc(QDomDocument doc)
 {
  Setup::doc = doc;
 }
}
