#ifndef XML_H
#define XML_H
#include <QString>
#include "appslib_global.h"
class APPSLIBSHARED_EXPORT Xml
{
 public:
  Xml();
  // Common to operation xml files
     static /*final*/ QString ID;// "id"; // NOI18N
     static /*final*/ QString NAME;// "name"; // NOI18N
     static /*final*/ QString CAR_TYPES;//; //="carTypes"; // NOI18N
     static /*final*/ QString DIR;//; //="dir"; // NOI18N
     static /*final*/ QString COMMENT;// "comment"; // NOI18N
     static /*final*/ QString SCHEDULE;//; //="schedule"; // NOI18N
     static /*final*/ QString TRACK;//; //="track"; // NOI18N
     static /*final*/ QString TYPES;//; //="types"; // NOI18N
     static /*final*/ QString LOCO_TYPE;//; //="locoType"; // NOI18N
     static /*final*/ QString CAR_TYPE;//; //="carType"; // NOI18N
     static /*final*/ QString _TRUE;// "true"; // NOI18N
     static /*final*/ QString _FALSE;// "false"; // NOI18N
     static /*final*/ QString LOAD;// = "load"; // NOI18N

     // LocationManager.java
     static /*final*/ QString LOCATIONS;//; //="locations"; // NOI18N

     // Location.java
         //static /*final*/ QString LOCATION; //="location"; // NOI18N
         static /*final*/ QString OPS; //="ops"; // NOI18N
         static /*final*/ QString SWITCH_LIST; //="switchList"; // NOI18N
         static /*final*/ QString SWITCH_LIST_STATE; //="switchListState"; // NOI18N
         static /*final*/ QString PRINTER_NAME; //="printerName"; // NOI18N

         static /*final*/ QString EAST_TRAIN_ICON_X; //="eastTrainIconX"; // NOI18N
         static /*final*/ QString EAST_TRAIN_ICON_Y; //="eastTrainIconY"; // NOI18N
         static /*final*/ QString WEST_TRAIN_ICON_X; //="westTrainIconX"; // NOI18N
         static /*final*/ QString WEST_TRAIN_ICON_Y; //="westTrainIconY"; // NOI18N
         static /*final*/ QString NORTH_TRAIN_ICON_X; //="northTrainIconX"; // NOI18N
         static /*final*/ QString NORTH_TRAIN_ICON_Y; //="northTrainIconY"; // NOI18N
         static /*final*/ QString SOUTH_TRAIN_ICON_X; //="southTrainIconX"; // NOI18N
         static /*final*/ QString SOUTH_TRAIN_ICON_Y; //="southTrainIconY"; // NOI18N
         static /*final*/ QString READER; //="idReader"; // NOI18N

         static /*final*/ QString PHYSICAL_LOCATION; //="physicalLocation"; // NOI18N
         static /*final*/ QString SWITCH_LIST_COMMENT; //="switchListComment"; // NOI18N
         static /*final*/ QString SECONDARY; //="secondary"; // NOI18N early version of operations called tracks "secondary"

         static /*final*/ QString YES;// "yes"; // NOI18N
     static /*final*/ QString NO;// "no"; // NOI18N



     // Control.java
     static /*final*/ QString CONTROL;// "control"; // NOI18N
     static /*final*/ QString BACKWARD_COMPATIBILITY;// "backwardCompatibility"; // NOI18N
     static /*final*/ QString SAVE_USING_PRE_2013_FORMAT;// "saveUsingPre_2013_Format"; // NOI18N
     //static /*final*/ QString LENGTH;// "length"; // NOI18N
     static /*final*/ QString MAXIMUM_STRING_LENGTHS;// "maximumStringLengths"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_ATTRIBUTE;// "max_len_string_attibute"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_ROAD_NUMBER;// "max_len_string_road_number"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_PRINT_ROAD_NUMBER;// "max_len_string_print_road_number"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_LOCATION_NAME;// "max_len_string_location_name"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_TRACK_NAME;// "max_len_string_track_name"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_TRACK_LENGTH_NAME;// "max_len_string_track_length_name"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_LENGTH_NAME;// "max_len_string_length_name"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_WEIGHT_NAME;// "max_len_string_weight_name"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_BUILT_NAME;// "max_len_string_built_name"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_TRAIN_NAME;// "max_len_string_train_name"; // NOI18N
     static /*final*/ QString MAX_LEN_STRING_ROUTE_NAME;// "max_len_string_route_name"; // NOI18N
     static /*final*/ QString REPORTS;// "reports"; // NOI18N

     // Setup.java
     static /*final*/ QString OPERATIONS;// "operations"; // NOI18N
     static /*final*/ QString RAIL_ROAD;// "railRoad"; // NOI18N
     static /*final*/ QString SETTINGS;// "settings"; // NOI18N
     static /*final*/ QString MAIN_MENU;// "mainMenu"; // NOI18N
     static /*final*/ QString CLOSE_ON_SAVE;// "closeOnSave"; // NOI18N
     static /*final*/ QString AUTO_SAVE;// "autoSave"; // NOI18N
     static /*final*/ QString AUTO_BACKUP;// "autoBackup"; // NOI18N
     static /*final*/ QString TRAIN_DIRECTION;// "trainDirection"; // NOI18N
     static /*final*/ QString TRAIN_LENGTH;// "trainLength"; // NOI18N
     static /*final*/ QString MAX_ENGINES;// "maxEngines"; // NOI18N
     static /*final*/ QString HPT;// "hpt"; // NOI18N
     static /*final*/ QString SCALE;// "scale"; // NOI18N
     //static /*final*/ QString CAR_TYPES;// "carTypes"; // NOI18N
     static /*final*/ QString SWITCH_TIME;// "switchTime"; // NOI18N
     static /*final*/ QString TRAVEL_TIME;// "travelTime"; // NOI18N
     static /*final*/ QString SHOW_VALUE;// "showValue"; // NOI18N
     static /*final*/ QString VALUE_LABEL;// "valueLabel"; // NOI18N
     static /*final*/ QString SHOW_RFID;// "showRfid"; // NOI18N
     static /*final*/ QString RFID_LABEL;// "rfidLabel"; // NOI18N
     static /*final*/ QString SETUP;// "setup"; // NOI18N

     static /*final*/ QString ROUTER;// "router"; // NOI18N
     static /*final*/ QString CAR_ROUTING_ENABLED;// "carRoutingEnabled"; // NOI18N
     static /*final*/ QString CAR_ROUTING_VIA_YARDS;// "carRoutingViaYards"; // NOI18N
     static /*final*/ QString CAR_ROUTING_VIA_STAGING;// "carRoutingViaStaging"; // NOI18N
     static /*final*/ QString FORWARD_TO_YARD;// "forwardToYard"; // NOI18N
     static /*final*/ QString ONLY_ACTIVE_TRAINS;// "onlyActiveTrains"; // NOI18N
     static /*final*/ QString CHECK_CAR_DESTINATION;// "checkCarDestination"; // NOI18N

     static /*final*/ QString LOGGER;// "logger"; // NOI18N
     static /*final*/ QString CAR_LOGGER;// "carLogger"; // NOI18N
     static /*final*/ QString ENGINE_LOGGER;// "engineLogger"; // NOI18N
     static /*final*/ QString TRAIN_LOGGER;// "trainLogger"; // NOI18N

     static /*final*/ QString PRINT_LOC_COMMENTS;// "printLocComments"; // NOI18N
     static /*final*/ QString PRINT_ROUTE_COMMENTS;// "printRouteComments"; // NOI18N
     static /*final*/ QString PRINT_LOADS_EMPTIES;// "printLoadsEmpties"; // NOI18N
     static /*final*/ QString PRINT_TIMETABLE;// "printTimetable"; // NOI18N
     static /*final*/ QString USE12HR_FORMAT;// "use12hrFormat"; // NOI18N
     static /*final*/ QString PRINT_VALID;// "printValid"; // NOI18N
     static /*final*/ QString SORT_BY_TRACK;// "sortByTrack"; // NOI18N
     static /*final*/ QString PRINT_HEADERS;// "printHeaders"; // NOI18N
     static /*final*/ QString PRINT_CABOOSE_LOAD;// "printCabooseLoad"; // NOI18N
     static /*final*/ QString PRINT_PASSENGER_LOAD;// "printPassengerLoad"; // NOI18N

     static /*final*/ QString LENGTH_UNIT;// "lengthUnit"; // NOI18N
     static /*final*/ QString YEAR_MODELED;// "yearModeled"; // NOI18N

     static /*final*/ QString PICKUP_ENG_FORMAT;// "pickupEngFormat"; // NOI18N
     static /*final*/ QString DROP_ENG_FORMAT;// "dropEngFormat"; // NOI18N
     static /*final*/ QString PICKUP_CAR_FORMAT;// "pickupCarFormat"; // NOI18N
     static /*final*/ QString DROP_CAR_FORMAT;// "dropCarFormat"; // NOI18N
     static /*final*/ QString LOCAL_FORMAT;// "localFormat"; // NOI18N
     static /*final*/ QString MISSING_CAR_FORMAT;// "missingCarFormat"; // NOI18N

     static /*final*/ QString SWITCH_LIST_PICKUP_CAR_FORMAT;// "switchListPickupCarFormat"; // NOI18N
     static /*final*/ QString SWITCH_LIST_DROP_CAR_FORMAT;// "switchListDropCarFormat"; // NOI18N
     static /*final*/ QString SWITCH_LIST_LOCAL_FORMAT;// "switchListLocalFormat"; // NOI18N

     static /*final*/ QString SAME_AS_MANIFEST;// "sameAsManifest"; // NOI18N
     static /*final*/ QString REAL_TIME;// "realTime"; // NOI18N
     static /*final*/ QString ALL_TRAINS;// "allTrains"; // NOI18N
     static /*final*/ QString PAGE_MODE;// "pageMode"; // NOI18N, backwards compatible for versions before 3.11
     static /*final*/ QString PAGE_FORMAT;// "pageFormat"; // NOI18N
     static /*final*/ QString PAGE_NORMAL;// "pageNormal"; // NOI18N
     static /*final*/ QString PAGE_PER_TRAIN;// "pagePerTrain"; // NOI18N
     static /*final*/ QString PAGE_PER_VISIT;// "pagePerVisit"; // NOI18N
     static /*final*/ QString PRINT_ROUTE_LOCATION;// "printRouteLocation"; // NOI18N
     static /*final*/ QString TRACK_SUMMARY;// "trackSummary"; // NOI18N

     static /*final*/ QString PREFIX;// "prefix"; // NOI18N
     static /*final*/ QString SETTING;// "setting"; // NOI18N

     static /*final*/ QString PANEL;// "panel"; // NOI18N
     static /*final*/ QString TRAIN_ICONXY;// "trainIconXY"; // NOI18N
     static /*final*/ QString TRAIN_ICON_APPEND;// "trainIconAppend"; // NOI18N

     static /*final*/ QString FONT_NAME;// "fontName"; // NOI18N
     static /*final*/ QString FONT_SIZE;// "fontSize"; // NOI18N
     static /*final*/ QString SIZE;// "size"; // NOI18N

     static /*final*/ QString PAGE_ORIENTATION;// "pageOrientation"; // NOI18N
     static /*final*/ QString MANIFEST;// "manifest"; // NOI18N
     //static /*final*/ QString SWITCH_LIST;// "switchList"; // NOI18N

     static /*final*/ QString MANIFEST_COLORS;// "manifestColors"; // NOI18N
     static /*final*/ QString DROP_COLOR;// "dropColor"; // NOI18N
     static /*final*/ QString PICKUP_COLOR;// "pickupColor"; // NOI18N
     static /*final*/ QString LOCAL_COLOR;// "localColor"; // NOI18N

     static /*final*/ QString TAB;// "tab"; // NOI18N
     static /*final*/ QString TAB2_LENGTH;// "tab2Length"; // NOI18N
     static /*final*/ QString TAB3_LENGTH;// "tab3Length"; // NOI18N
     static /*final*/ QString ENABLED;// "enabled"; // NOI18N

     static /*final*/ QString COLUMN_FORMAT;// "columnFormat"; // NOI18N
     static /*final*/ QString TWO_COLUMNS;// "twoColumns"; // NOI18N
     static /*final*/ QString MANIFEST_FORMAT;// "manifestFormat";  // NOI18N
     //static /*final*/ QString VALUE;// "value"; // NOI18N
     static /*final*/ QString STANDARD;// "0";	// NOI18N
     static /*final*/ QString TWO_COLUMN;// "1"; // NOI18N
     static /*final*/ QString TWO_COLUMN_TRACK;// "2"; // NOI18N

     static /*final*/ QString TRUNCATE;// "truncate"; // NOI18N
     static /*final*/ QString USE_DEPARTURE_TIME;// "useDepartureTime"; // NOI18N
     static /*final*/ QString USE_EDITOR;// "useEditor"; // NOI18N
     static /*final*/ QString HAZARDOUS_MSG;// "hazardousMsg"; // NOI18N

     static /*final*/ QString MANIFEST_LOGO;// "manifestLogo"; // NOI18N

     static /*final*/ QString BUILD_OPTIONS;// "buildOptions"; // NOI18N
     static /*final*/ QString AGGRESSIVE;// "aggressive"; // NOI18N
     static /*final*/ QString NUMBER_PASSES;// "numberPasses";  // NOI18N

     static /*final*/ QString ALLOW_LOCAL_INTERCHANGE;// "allowLocalInterchange"; // NOI18N
     static /*final*/ QString ALLOW_LOCAL_SPUR;// "allowLocalSiding"; // NOI18N
     static /*final*/ QString ALLOW_LOCAL_YARD;// "allowLocalYard"; // NOI18N

     static /*final*/ QString STAGING_RESTRICTION_ENABLED;// "stagingRestrictionEnabled"; // NOI18N
     static /*final*/ QString STAGING_TRACK_AVAIL;// "stagingTrackAvail"; // NOI18N
     static /*final*/ QString ALLOW_RETURN_STAGING;// "allowReturnStaging"; // NOI18N
     static /*final*/ QString PROMPT_STAGING_ENABLED;// "promptStagingEnabled"; // NOI18N
     static /*final*/ QString PROMPT_TO_STAGING_ENABLED;// "promptToStagingEnabled"; // NOI18N

     static /*final*/ QString GENERATE_CSV_MANIFEST;// "generateCsvManifest"; // NOI18N
     static /*final*/ QString GENERATE_CSV_SWITCH_LIST;// "generateCsvSwitchList"; // NOI18N

     //static /*final*/ QString BUILD_REPORT;// "buildReport"; // NOI18N
     static /*final*/ QString LEVEL;// "level"; // NOI18N
     static /*final*/ QString INDENT;// "indent"; // NOI18N
     static /*final*/ QString ROUTER_LEVEL;// "routerLevel"; // NOI18N
     static /*final*/ QString ALWAYS_PREVIEW;// "alwaysPreview"; // NOI18N

     //static /*final*/ QString OWNER;// "owner"; // NOI18N

     static /*final*/ QString ICON_COLOR;// "iconColor"; // NOI18N
     static /*final*/ QString NORTH;// "north"; // NOI18N
     static /*final*/ QString SOUTH;// "south"; // NOI18N
     static /*final*/ QString EAST;// "east"; // NOI18N
     static /*final*/ QString WEST;// "west"; // NOI18N
     static /*final*/ QString LOCAL;// "local"; // NOI18N
     static /*final*/ QString TERMINATE;// "terminate"; // NOI18N

     static /*final*/ QString COMMENTS;// "comments"; // NOI18N
     static /*final*/ QString MISPLACED_CARS;// "misplacedCars"; // NOI18N

     static /*final*/ QString VSD;// "vsd"; // NOI18N
     static /*final*/ QString ENABLE_PHYSICAL_LOCATIONS;// "enablePhysicalLocations"; // NOI18N

     static /*final*/ QString CATS;// "CATS"; // NOI18N
     static /*final*/ QString EXACT_LOCATION_NAME;// "exactLocationName"; // NOI18N
     // train.java
         //static /*final*/QString TRAIN; //="train"; // NOI18N
         static /*final*/QString DESCRIPTION; //="description"; // NOI18N
         static /*final*/QString DEPART_HOUR; //="departHour"; // NOI18N
         static /*final*/QString DEPART_MINUTE; //="departMinute"; // NOI18N
         static /*final*/QString ROUTE; //="route"; // NOI18N
         static /*final*/QString SKIPS; //="skips"; // NOI18N
         //static /*final*/QString LOCATION; //="location"; // NOI18N
         static /*final*/QString ROUTE_ID; //="routeId"; // NOI18N old format
         static /*final*/QString SKIP; //="skip"; // NOI18N
         //static /*final*/QString CAR_TYPES; //="carTypes"; // NOI18N
         //static /*final*/QString TYPES; //="types"; // NOI18N
         //static /*final*/QString CAR_TYPE; //="carType"; // NOI18N
         //static /*final*/QString LOCO_TYPE; //="locoType"; // NOI18N
         static /*final*/QString CAR_ROAD_OPERATION; //="carRoadOperation"; // NOI18N	should have been option not operation
         static /*final*/QString CAR_ROAD_OPTION; //="carRoadOption"; // NOI18N
         static /*final*/QString CAR_ROADS; //="carRoads"; // NOI18N
         static /*final*/QString CAR_ROAD; //="carRoad"; // NOI18N
         static /*final*/QString CAR_LOAD_OPTION; //="carLoadOption"; // NOI18N
         static /*final*/QString CAR_LOADS; //="carLoads"; // NOI18N
         static /*final*/QString CAR_LOAD; //="carLoad"; // NOI18N
         static /*final*/QString CAR_OWNER_OPTION; //="carOwnerOption"; // NOI18N
         static /*final*/QString BUILT_START_YEAR; //="builtStartYear"; // NOI18N
         static /*final*/QString BUILT_END_YEAR; //="builtEndYear"; // NOI18N
         static /*final*/QString CAR_OWNERS; //="carOwners"; // NOI18N
         static /*final*/QString CAR_OWNER; //="carOwner"; // NOI18N

         static /*final*/QString NUMBER_ENGINES; //="numberEngines"; // NOI18N
         static /*final*/QString LEG2_ENGINES; //="leg2Engines"; // NOI18N
         static /*final*/QString LEG3_ENGINES; //="leg3Engines"; // NOI18N

         static /*final*/QString ENGINE_ROAD; //="engineRoad"; // NOI18N
         static /*final*/QString LEG2_ROAD; //="leg2Road"; // NOI18N
         static /*final*/QString LEG3_ROAD; //="leg3Road"; // NOI18N

         static /*final*/QString ENGINE_MODEL; //="engineModel"; // NOI18N
         static /*final*/QString LEG2_MODEL; //="leg2Model"; // NOI18N
         static /*final*/QString LEG3_MODEL; //="leg3Model"; // NOI18N

         static /*final*/QString REQUIRES; //="requires"; // NOI18N
         static /*final*/ QString CABOOSE_ROAD; //="cabooseRoad"; // NOI18N
         static /*final*/ QString LEG2_CABOOSE_ROAD; //="leg2CabooseRoad"; // NOI18N
         static /*final*/ QString LEG3_CABOOSE_ROAD; //="leg3CabooseRoad"; // NOI18N

         static /*final*/ QString LEG2_OPTIONS; //="leg2Options"; // NOI18N
         static /*final*/ QString LEG3_OPTIONS; //="leg3Options"; // NOI18N

         static /*final*/ QString BUILD_NORMAL; //="buildNormal"; // NOI18N
         static /*final*/ QString TO_TERMINAL; //="toTerminal"; // NOI18N
         static /*final*/ QString ALLOW_LOCAL_MOVES; //="allowLocalMoves"; // NOI18N
         static /*final*/ QString ALLOW_THROUGH_CARS; //="allowThroughCars"; // NOI18N
         static /*final*/ QString ALLOW_RETURN; //="allowReturn"; // NOI18N
         static /*final*/ QString SERVICE_ALL; //="serviceAll"; // NOI18N
         static /*final*/ QString BUILD_CONSIST; //="buildConsist"; // NOI18N
         static /*final*/ QString SEND_CUSTOM_STAGING; //="sendCustomStaging"; // NOI18N

         //static /*final*/ QString BUILT; //="built"; // NOI18N
         static /*final*/ QString BUILD; //="build"; // NOI18N
         static /*final*/ QString BUILD_FAILED; //="buildFailed"; // NOI18N
         static /*final*/ QString BUILD_FAILED_MESSAGE; //="buildFailedMessage"; // NOI18N
         static /*final*/ QString PRINTED; //="printed"; // NOI18N
         static /*final*/ QString MODIFIED; //="modified"; // NOI18N
         static /*final*/ QString SWITCH_LIST_STATUS; //="switchListStatus"; // NOI18N
         static /*final*/ QString LEAD_ENGINE; //="leadEngine"; // NOI18N
         static /*final*/ QString STATUS; //="status"; // NOI18N
         static /*final*/ QString STATUS_CODE; //="statusCode"; // NOI18N
         static /*final*/ QString TERMINATION_DATE; //="TerminationDate"; // NOI18N
         static /*final*/ QString REQUESTED_CARS; //="RequestedCars"; // NOI18N

         static /*final*/ QString CURRENT; //="current"; // NOI18N
         static /*final*/ QString LEG2_START; //="leg2Start"; // NOI18N
         static /*final*/ QString LEG3_START; //="leg3Start"; // NOI18N
         static /*final*/ QString LEG2_END; //="leg2End"; // NOI18N
         static /*final*/ QString LEG3_END; //="leg3End"; // NOI18N
         static /*final*/ QString DEPARTURE_TRACK; //="departureTrack"; // NOI18N
         static /*final*/ QString TERMINATION_TRACK; //="terminationTrack"; // NOI18N

         static /*final*/ QString SCRIPTS; //="scripts"; // NOI18N
         static /*final*/ QString AFTER_BUILD; //="afterBuild"; // NOI18N
         //static /*final*/ QString TERMINATE; //="terminate"; // NOI18N
         static /*final*/ QString MOVE; //="move"; // NOI18N

         //static /*final*/ QString RAIL_ROAD; //="railRoad"; // NOI18N
         //static /*final*/ QString MANIFEST_LOGO; //="manifestLogo"; // NOI18N
         static /*final*/ QString SHOW_TIMES; //="showTimes"; // NOI18N

         // TrainManager.java
             static /*final*/ QString OPTIONS;//; //="options"; // NOI18N
             static /*final*/ QString TRAIN_OPTIONS;//; //="trainOptions"; // NOI18N
             static /*final*/ QString BUILD_MESSAGES;//; //="buildMessages"; // NOI18N
             static /*final*/ QString BUILD_REPORT;//; //="buildReport"; // NOI18N
             static /*final*/ QString PRINT_PREVIEW;//; //="printPreview"; // NOI18N
             static /*final*/ QString OPEN_FILE;//; //="openFile"; // NOI18N
             static /*final*/ QString TRAIN_ACTION;//; //="trainAction"; // NOI18N

             static /*final*/ QString COLUMN_WIDTHS; //; //="columnWidths"; // NOI18N TODO This here is for backwards compatibility, remove after next major release

                 static /*final*/ QString TRAIN_SCHEDULE_OPTIONS; //="trainScheduleOptions"; // NOI18N
                 static /*final*/ QString ACTIVE_ID; //="activeId"; // NOI18N
                 static /*final*/ QString START_UP; //="startUp"; // NOI18N
                 static /*final*/ QString SHUT_DOWN; //="shutDown"; // NOI18N

                 static /*final*/ QString ROW_COLOR_OPTIONS; //="rowColorOptions"; // NOI18N
                 static /*final*/ QString ROW_COLOR_MANUAL; //="rowColorManual"; // NOI18N
                 static /*final*/ QString ROW_COLOR_BUILT; //="rowColorBuilt"; // NOI18N
                 static /*final*/ QString ROW_COLOR_BUILD_FAILED; //="rowColorBuidFailed"; // NOI18N
                 static /*final*/ QString ROW_COLOR_TRAIN_EN_ROUTE; //="rowColorTrainEnRoute"; // NOI18N
                 static /*final*/ QString ROW_COLOR_TERMINATED; //="rowColorTerminated"; // NOI18N

                 // TrainManagerXml.java
                 static /*final*/ QString TRAINS;//; //="trains"; // NOI18N

                 // ManifestCreator.java
                     static /*final*/ QString MANIFEST_CREATOR;//; //="manifestCreator"; // NOI18N
                     static /*final*/ QString RUN_FILE;//; //="runFile"; // NOI18N
                     static /*final*/ QString DIRECTORY;//; //="directory"; // NOI18N
                     static /*final*/ QString COMMON_FILE;//; //="commonFile"; // NOI18N

  // RollingStock.java
      static /*final*/ QString ROAD_NUMBER; //="roadNumber"; // NOI18N
      static /*final*/ QString ROAD_NAME; //="roadName"; // NOI18N
      static /*final*/ QString COLOR; //="color"; // NOI18N
      static /*final*/ QString WEIGHT; //="weight"; // NOI18N
      static /*final*/ QString WEIGHT_TONS; //="weightTons"; // NOI18N
      static /*final*/ QString BUILT; //="built"; // NOI18N
      static /*final*/ QString LOCATION; //="location"; // NOI18N
      static /*final*/ QString MOVES; //="moves"; // NOI18N
      static /*final*/ QString OWNER; //="owner"; // NOI18N
      static /*final*/ QString VALUE; //="value"; // NOI18N
      static /*final*/ QString RFID; //="rfid"; // NOI18N
      static /*final*/ QString TRAIN; //="train"; // NOI18N
      static /*final*/ QString TRAIN_ID; //="trainId"; // NOI18N
      static /*final*/ QString OUT_OF_SERVICE; //="outOfService"; // NOI18N
      static /*final*/ QString DESTINATION; //="destination"; // NOI18N
      static /*final*/ QString DES_TRACK; //="desTrack"; // NOI18N
      static /*final*/ QString LOC_UNKNOWN; //="locUnknown"; // NOI18N
      static /*final*/ QString DATE; //="date"; // NOI18N
      static /*final*/ QString BLOCKING; //="blocking"; // NOI18N
      static /*final*/ QString SELECTED; //="selected"; // NOI18N

                         static /*final*/ QString LOCATION_ID; //="locationId"; // NOI18N
                         static /*final*/ QString SEC_LOCATION_ID; //="secLocationId"; // NOI18N
                         static /*final*/ QString DESTINATION_ID; //="destinationId"; // NOI18N
                         static /*final*/ QString SEC_DESTINATION_ID; //="secDestinationId"; // NOI18N
                         static /*final*/ QString LAST_LOCATION_ID; //="lastLocationId"; // NOI18N
                         static /*final*/ QString ROUTE_LOCATION_ID; //="routeLocationId"; // NOI18N
                         static /*final*/ QString ROUTE_DESTINATION_ID; //="routeDestinationId"; // NOI18N
                         static /*final*/ QString LAST_ROUTE_ID; //="lastRouteId"; // NOI18N

                         // Car.java
                         static /*final*/ QString PASSENGER; //="passenger"; // NOI18N
                         static /*final*/ QString TYPE;// = "type"; // NOI18N
                         // Engine.java
                             static /*final*/ QString ENGINE; //="engine"; // NOI18N
                             static /*final*/ QString HP; //="hp"; // NOI18N
                             static /*final*/ QString B_UNIT;// = "bUnit"; // NOI18N

                             //static /*final*/ QString TYPE; //="type"; // NOI18N

                             //static /*final*/ QString WEIGHT_TONS; //="weightTons"; // NOI18N
                             static /*final*/ QString CONSIST; //="consist"; // NOI18N
                             static /*final*/ QString LEAD_CONSIST; //="leadConsist"; // NOI18N
                             static /*final*/ QString CONSIST_NUM; //="consistNum"; // NOI18N

                             // EngineManager.java
                             static /*final*/ QString ENGINES_OPTIONS; //="enginesOptions"; // NOI18N
                             //static /*final*/ QString COLUMN_WIDTHS; //="columnWidths"; // NOI18N backwards compatible TODO remove in 2013 after production release
                             //static /*final*/ QString OPTIONS; //="options"; // NOI18N
                             static /*final*/ QString CONSISTS; //="consists";  // NOI18N
                             static /*final*/ QString NEW_CONSISTS; //="newConsists";  // NOI18N

                             // EngineManagerXml.java
                             static /*final*/ QString ENGINES; //="engines";  // NOI18N

                             // EngineModels.java
                             static /*final*/ QString ENGINE_MODELS; //="engineModels";  // NOI18N
                             static /*final*/ QString MODELS; //="models";  // NOI18N

                             // EngineTypes.java
                             static /*final*/ QString ENGINE_TYPES; //="engineTypes";  // NOI18N
                             //static /*final*/ QString TYPES; //="types"; // NOI18N

                             // EngineLengths.java
                             static /*final*/ QString ENGINE_LENGTHS; //="engineLengths";  // NOI18N
                             static /*final*/ QString LENGTHS; //="lengths"; // NOI18N
                             //static /*final*/ QString VALUE; //="value"; // NOI18N
                             static /*final*/ QString MODEL; //="model";  // NOI18N
 // Car.java
     static /*final*/ QString CAR; //="car"; // NOI18N
     //static /*final*/ QString PASSENGER; //="passenger"; // NOI18N
     static /*final*/ QString HAZARDOUS; //="hazardous"; // NOI18N
     static /*final*/ QString CABOOSE; //="caboose"; // NOI18N
     static /*final*/ QString FRED; //="fred"; // NOI18N
     static /*final*/ QString UTILITY; //="utility"; // NOI18N
     static /*final*/ QString KERNEL; //="kernel"; // NOI18N
     static /*final*/ QString LEAD_KERNEL; //="leadKernel"; // NOI18N

     static /*final*/ QString LOAD_FROM_STAGING;// = "loadFromStaging"; // NOI18N
     static /*final*/ QString WAIT;// = "wait"; // NOI18N
     static /*final*/ QString PICKUP_SCHEDULE_ID;// = "pickupId"; // NOI18N
     static /*final*/ QString ORDER;// = "order"; // NOI18N
     static /*final*/ QString SCHEDULE_ID;// = "scheduleId"; // NOI18N
     static /*final*/ QString NEXT_LOAD;//= "nextLoad"; // NOI18N
         static /*final*/ QString NEXT_WAIT;//= "nextWait"; // NOI18N
         static /*final*/ QString NEXT_PICKUP_SCHEDULE_ID;//= "nextPickupId"; // NOI18N
         static /*final*/ QString NEXT_DEST_ID;//= "nextDestId"; // NOI18N
         static /*final*/ QString NEXT_DEST_TRACK_ID;//= "nextDestTrackId"; // NOI18N
         static /*final*/ QString PREVIOUS_NEXT_DEST_ID;//= "previousNextDestId"; // NOI18N
         static /*final*/ QString PREVIOUS_NEXT_DEST_TRACK_ID;//= "previousNextDestTrackId"; // NOI18N
         static /*final*/ QString PREVIOUS_SCHEDULE_ID;//= "previousScheduleId"; // NOI18N
         static /*final*/ QString RWE_DEST_ID;//= "rweDestId"; // NOI18N
         static /*final*/ QString RWE_DEST_TRACK_ID;//= "rweDestTrackId"; // NOI18N
         static /*final*/ QString RWE_LOAD;//= "rweLoad"; // NOI18N

     // CarManager.java
     //static /*final*/ QString OPTIONS; //="options"; // NOI18N
     static /*final*/ QString CARS; //="cars"; // NOI18N
     static /*final*/ QString CARS_OPTIONS; //="carsOptions"; // NOI18N
     //static /*final*/ QString COLUMN_WIDTHS; //="columnWidths"; // NOI18N backwards compatible TODO remove in 2013 after production release
     static /*final*/ QString KERNELS; //="kernels"; // NOI18N
     static /*final*/ QString NEW_KERNELS; //="newKernels"; // NOI18N

     // CarRoads.java
     static /*final*/ QString ROAD_NAMES;// = "roadNames"; // NOI18N
     static /*final*/ QString ROADS;// = "roads"; // NOI18N
     static /*final*/ QString ROAD;//= "road"; // NOI18N

     // Track.java
     static /*final*/ QString LOC_TYPE; //="locType"; // NOI18N
     static /*final*/ QString LENGTH; //="length"; // NOI18N
     //static /*final*/ QString MOVES; //="moves"; // NOI18N
     static /*final*/ QString BLOCKING_ORDER; //="blockingOrder"; // NOI18N
     //static /*final*/ QString CAR_ROAD_OPERATION; //="carRoadOperation"; // NOI18N misspelled should have been carRoadOption
     //static /*final*/ QString CAR_ROAD_OPTION; //="carRoadOption"; // NOI18N
     //static /*final*/ QString CAR_ROADS; //="carRoads"; // NOI18N
     //static /*final*/ QString CAR_ROAD; //="carRoad"; // NOI18N
    // static /*final*/ QString CAR_LOAD_OPTION; //="carLoadOption"; // NOI18N
     static /*final*/ QString CAR_SHIP_LOAD_OPTION; //="carShipLoadOption"; // NOI18N
     //static /*final*/ QString CAR_LOADS; //="carLoads"; // NOI18N
     static /*final*/ QString CAR_SHIP_LOADS; //="carShipLoads"; // NOI18N
     //static /*final*/ QString CAR_LOAD; //="carLoad"; // NOI18N
     static /*final*/ QString DROP_IDS; //="dropIds"; // NOI18N
     static /*final*/ QString DROP_ID; //="dropId"; // NOI18N
     static /*final*/ QString DROP_OPTION; //="dropOption"; // NOI18N
     static /*final*/ QString PICKUP_IDS; //="pickupIds"; // NOI18N
     static /*final*/ QString PICKUP_ID; //="pickupId"; // NOI18N
     static /*final*/ QString PICKUP_OPTION; //="pickupOption"; // NOI18N
     //static /*final*/ QString COMMENTS; //="comments"; // NOI18N
     static /*final*/ QString BOTH; //="both"; // NOI18N
     static /*final*/ QString PICKUP; //="pickup"; // NOI18N
     static /*final*/ QString SETOUT; //="setout"; // NOI18N
     static /*final*/ QString TRACK_DESTINATION_OPTION; //="trackDestinationOption"; // NOI18N
     static /*final*/ QString DESTINATIONS; //="destinations"; // NOI18N
     //static /*final*/ QString DESTINATION; //="destination"; // NOI18N

     //static /*final*/ QString SCHEDULE_ID; //="scheduleId"; // NOI18N
     static /*final*/ QString ITEM_ID; //="itemId"; // NOI18N
     static /*final*/ QString ITEM_COUNT; //="itemCount"; // NOI18N
     static /*final*/ QString FACTOR; //="factor"; // NOI18N
     static /*final*/ QString SCHEDULE_MODE; //="scheduleMode"; // NOI18N
     static /*final*/ QString ALTERNATIVE; //="alternative"; // NOI18N
     static /*final*/ QString LOAD_OPTIONS; //="loadOptions"; // NOI18N
     static /*final*/ QString BLOCK_OPTIONS; //="blockOptions"; // NOI18N
     //static /*final*/ QString ORDER; //="order"; // NOI18N
     static /*final*/ QString POOL; //="pool"; // NOI18N
     static /*final*/ QString MIN_LENGTH; //="minLength"; // NOI18N
     static /*final*/ QString IGNORE_USED_PERCENTAGE; //="ignoreUsedPercentage"; // NOI18N

     // RouteLocation.java
         //static /*final*/ QString LOCATION_ID; //="locationId"; // NOI18N
         //static /*final*/ QString TRAIN_DIRECTION; //="trainDirection"; // NOI18N
         static /*final*/ QString MAX_TRAIN_LENGTH; //="maxTrainLength"; // NOI18N
         static /*final*/ QString GRADE; //="grade"; // NOI18N
         static /*final*/ QString MAX_CAR_MOVES; //="maxCarMoves"; // NOI18N
         static /*final*/ QString RANDOM_CONTROL; //="randomControl"; // NOI18N
         static /*final*/ QString PICKUPS; //="pickups"; // NOI18N
         static /*final*/ QString DROPS; //="drops"; // NOI18N
         //static /*final*/ QString WAIT; //="wait"; // NOI18N
         static /*final*/ QString DEPART_TIME; //="departTime"; // NOI18N
         static /*final*/ QString TRAIN_ICON_X; //="trainIconX"; // NOI18N
         static /*final*/ QString TRAIN_ICON_Y; //="trainIconY"; // NOI18N
         static /*final*/ QString SEQUENCE_ID; //="sequenceId"; // NOI18N

         // CarLengths.java
         static /*final*/ QString CAR_LENGTHS;// = "carLengths";

     // CarLoads.java
         static /*final*/ QString LOADS;// = "loads"; // NOI18N
         static /*final*/ QString NAMES;// = "names"; // NOI18N old style had a list of names
         static /*final*/ QString DEFAULTS;// = "defaults"; // NOI18N
         static /*final*/ QString EMPTY;// = "empty"; // NOI18N
         //static /*final*/ QString CAR_LOAD;// = "carLoad"; // NOI18N
         static /*final*/ QString PRIORITY;// = "priority"; // NOI18N
         static /*final*/ QString PICKUP_COMMENT;// = "pickupComment"; // NOI18N
         static /*final*/ QString DROP_COMMENT;// = "dropComment"; // NOI18N
         static /*final*/ QString LOAD_TYPE;// = "loadType"; // NOI18N
         static /*final*/ QString OWNERS;

         // RouteManagerXml.java
             static /*final*/ QString ROUTES;// = "routes"; // NOI18N
         // CarColors.java
             static /*final*/ QString CAR_COLORS ;//= "carColors"; // NOI18N
             static /*final*/ QString COLORS;// = "colors"; // NOI18N
             //static /*final*/ QString COLOR;// = "color"; // NOI18N
       // TrainManifestHeaderText.jafa
          static /*final*/ QString MANIFEST_HEADER_TEXT_STRINGS;//= "manifestHeaderTextStrings"; // NOI18N
          //static /*final*/ QString ROAD;//= "road"; // the supported message format options NOI18N
          static /*final*/ QString NUMBER;//= "number"; // NOI18N
          static /*final*/ QString ENGINE_NUMBER;//= "engineNumber"; // NOI18N
          //static /*final*/ QString TYPE;//= "type"; // NOI18N
         // static /*final*/ QString MODEL;//= "model"; // NOI18N
          //static /*final*/ QString LENGTH;//= "length"; // NOI18N
          //static /*final*/ QString LOAD;//= "load"; // NOI18N
          //static /*final*/ QString COLOR;//= "color"; // NOI18N
          //static /*final*/ QString TRACK;//= "track"; // NOI18N
          //static /*final*/ QString DESTINATION;//= "destination"; // NOI18N
          static /*final*/ QString DEST_TRACK;//= "dest_Track"; // NOI18N
          static /*final*/ QString FINAL_DEST;//= "Final_Dest"; // NOI18N
          static /*final*/ QString FINAL_DEST_TRACK;//= "fd_Track"; // NOI18N
          //static /*final*/ QString LOCATION;//= "location"; // NOI18N
          //static /*final*/ QString CONSIST;//= "consist"; // NOI18N
          //static /*final*/ QString KERNEL;//= "kernel"; // NOI18N
          //static /*final*/ QString OWNER;//= "owner"; // NOI18N
          static /*final*/ QString RWE;//= "rwe"; // NOI18N
          //static /*final*/ QString COMMENT;//= "Comment"; // NOI18N
          //static /*final*/ QString DROP_COMMENT;//= "setOut_msg"; // NOI18N
          //static /*final*/ QString PICKUP_COMMENT;//= "pickUp_msg"; // NOI18N
          //static /*final*/ QString HAZARDOUS;//= "hazardous"; // NOI18N
          static /*final*/ QString TEXT;//= "text"; // NOI18N
// SccheduleManager.java
static /*final*/ QString SCHEDULES;// = "schedules"; // NOI18N

// ScheduleItem.java
static /*final*/ QString ITEM;// = "item"; // NOI18N
          static /*final*/ QString RANDOM;//= "random"; // NOI18N
          static /*final*/ QString TRAIN_SCHEDULE_ID;//= "trainScheduleId"; // NOI18N
          static /*final*/ QString PICKUP_TRAIN_SCHEDULE_ID;//= "pickupTrainScheduleId"; // NOI18N
          static /*final*/ QString COUNT;//= "count"; // NOI18N
          static /*final*/ QString SHIP;//= "ship"; // NOI18N
         // static /*final*/ QString DESTINATION_ID;//= "destinationId"; // NOI18N
          static /*final*/ QString DEST_TRACK_ID;//= "destTrackId"; // NOI18N
          static /*final*/ QString HITS;//= "hits"; // NOI18N
          // TrainSchedule.java
          //static /*final*/ QString SCHEDULE = "schedule"; // NOI18N
          static /*final*/ QString TRAIN_IDS;// = "trainIds"; // NOI18N
static /*final*/ QString ROW_COLOR;// = "rowColor";  // NOI18N};

// TrainManifestText.java
    static /*final*/ QString MANIFEST_TEXT_STRINGS;//= "manifestTextStrings"; // NOI18N
    static /*final*/ QString MANIFEST_FOR_TRAIN;//= "manifestForTrain"; // NOI18N
    static /*final*/ QString VALID;//= "valid"; // NOI18N
    static /*final*/ QString SCHEDULED_WORK;//= "scheduledWork"; // NOI18N
    static /*final*/ QString WORK_DEPARTURE_TIME;//= "workDepartureTime"; // NOI18N
    static /*final*/ QString WORK_ARRIVAL_TIME;//= "workArrivalTime"; // NOI18N
    static /*final*/ QString NO_SCHEDULED_WORK;//= "noScheduledWork"; // NOI18N
    static /*final*/ QString NO_SCHEDULED_WORK_ROUTE_COMMENT;//= "noScheduledWorkRouteComment"; // NOI18N
    //static /*final*/ QString DEPART_TIME;//= "departTime"; // NOI18N
    static /*final*/ QString TRAIN_DEPARTS_CARS;//= "trainDepartsCars"; // NOI18N
    static /*final*/ QString TRAIN_DEPARTS_LOADS;//= "trainDepartsLoads"; // NOI18N
    static /*final*/ QString TRAIN_TERMINATES;//= "trainTerminates"; // NOI18N
    //static /*final*/ QString DESTINATION;//= "destination"; // NOI18N
    static /*final*/ QString FROM;//= "from"; // NOI18N
    static /*final*/ QString TO;//= "to"; // NOI18N
    static /*final*/ QString DEST;//= "dest"; // NOI18N
    //static /*final*/ QString FINAL_DEST;//= "finalDest"; // NOI18N
    static /*final*/ QString ADD_HELPERS;//= "addHelpers"; // NOI18N
    static /*final*/ QString REMOVE_HELPERS;//= "removeHelpers"; // NOI18N
    static /*final*/ QString LOCO_CHANGE;//= "locoChange"; // NOI18N
    static /*final*/ QString CABOOSE_CHANGE;//= "cabooseChange"; // NOI18N
    static /*final*/ QString LOCO_CABOOSE_CHANGE;//= "locoCabooseChange"; // NOI18N

    // TrainSwitchListText.java
    static /*final*/ QString SWITCH_LIST_TEXT_STRINGS;// = "switchListTextStrings"; // NOI18N
    static /*final*/ QString SWICH_LIST_FOR;// = "switchListFor"; // NOI18N
    static /*final*/ QString SCHEDULED_WORK_TRAIN;// = "scheduledWorkTrain"; // NOI18N

    static /*final*/ QString DEPARTS_AT;// = "departsAt"; // NOI18N
    static /*final*/ QString DEPARTS_EXPECTED_ARRIVAL;// = "departsExpectedArrival"; // NOI18N
    static /*final*/ QString DEPARTED_EXPECTED;// = "departedExpected"; // NOI18N

    static /*final*/ QString VISIT_NUMBER;// = "visitNumber"; // NOI18N
    static /*final*/ QString VISIT_NUMBER_DEPARTED;// = "visitNumberDeparted"; // NOI18N
    static /*final*/ QString VISIT_NUMBER_TERMINATES;// = "visitNumberTerminates"; // NOI18N
    static /*final*/ QString VISIT_NUMBER_TERMINATES_DEPARTED;// = "visitNumberTerminatesDeparted"; // NOI18N
    static /*final*/ QString VISIT_NUMBER_DONE;// = "visitNumberDone"; // NOI18N

    static /*final*/ QString TRAIN_DIRECTION_CHANGE;// = "trainDirectionChange"; // NOI18N
    static /*final*/ QString NO_CAR_PICK_UPS;// = "noCarPickUps"; // NOI18N
    static /*final*/ QString NO_CAR_SET_OUTS;// = "noCarSetOuts"; // NOI18N
    static /*final*/ QString TRAIN_DONE;// = "trainDone"; // NOI18N

    static /*final*/ QString SWITCH_LIST_TRACK;// = "switchListTrack";
    static /*final*/ QString HOLD_CAR;// = "holdCar";
};
#endif // XML_H
