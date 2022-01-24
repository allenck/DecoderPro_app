#include "xml.h"

Xml::Xml() {}
/**
 * A convenient place to access operations xml element and attribute names.
 *
 * @author Daniel Boudreau Copyright (C) 2012
 * @version $Revision: 22156 $
 *
 */
///*public*/ class Xml {

// Common to operation xml files
    /*static final*/ QString Xml::ID = "id"; // NOI18N
    /*static final*/ QString Xml::NAME = "name"; // NOI18N
    /*static final*/ QString Xml::CAR_TYPES = "carTypes"; // NOI18N
    /*static*/ /*final*/ QString Xml::DIR = "dir"; // NOI18N
    /*static final*/ QString Xml::COMMENT = "comment"; // NOI18N
    /*static final*/ QString Xml::SCHEDULE = "schedule"; // NOI18N
    /*static final*/ QString Xml::TRACK = "track"; // NOI18N
    /*static final*/ QString Xml::TYPES = "types"; // NOI18N
    /*static final*/ QString Xml::LOCO_TYPE = "locoType"; // NOI18N
    /*static final*/ QString Xml::CAR_TYPE = "carType"; // NOI18N
    /*static final*/ QString Xml::_TRUE = "true"; // NOI18N
    /*static final*/ QString Xml::_FALSE = "false"; // NOI18N
    /*static final*/ QString Xml::LOAD = "load"; // NOI18N
    /*static final*/ QString Xml::DIVISION = "division"; // NOI18N
    /*static final*/ QString Xml::DIVISIONS = "divisions"; // NOI18N

// LocationManager.java
/*static*/ /*final*/ QString Xml::LOCATIONS = "locations"; // NOI18N

// Location.java
    ///*static*/ /*final*/ QString Xml::LOCATION = "location"; // NOI18N
    /*static*/ /*final*/ QString Xml::OPS = "ops"; // NOI18N
    /*static*/ /*final*/ QString Xml::SWITCH_LIST = "switchList"; // NOI18N
    /*static*/ /*final*/ QString Xml::SWITCH_LIST_STATE = "switchListState"; // NOI18N
    /*static*/ /*final*/ QString Xml::PRINTER_NAME = "printerName"; // NOI18N

    /*static*/ /*final*/ QString Xml::EAST_TRAIN_ICON_X = "eastTrainIconX"; // NOI18N
    /*static*/ /*final*/ QString Xml::EAST_TRAIN_ICON_Y = "eastTrainIconY"; // NOI18N
    /*static*/ /*final*/ QString Xml::WEST_TRAIN_ICON_X = "westTrainIconX"; // NOI18N
    /*static*/ /*final*/ QString Xml::WEST_TRAIN_ICON_Y = "westTrainIconY"; // NOI18N
    /*static*/ /*final*/ QString Xml::NORTH_TRAIN_ICON_X = "northTrainIconX"; // NOI18N
    /*static*/ /*final*/ QString Xml::NORTH_TRAIN_ICON_Y = "northTrainIconY"; // NOI18N
    /*static*/ /*final*/ QString Xml::SOUTH_TRAIN_ICON_X = "southTrainIconX"; // NOI18N
    /*static*/ /*final*/ QString Xml::SOUTH_TRAIN_ICON_Y = "southTrainIconY"; // NOI18N
    /*static*/ /*final*/ QString Xml::READER = "idReader"; // NOI18N

    /*static*/ /*final*/ QString Xml::PHYSICAL_LOCATION = "physicalLocation"; // NOI18N
    /*static*/ /*final*/ QString Xml::SWITCH_LIST_COMMENT = "switchListComment"; // NOI18N
    /*static*/ /*final*/ QString Xml::SECONDARY = "secondary"; // NOI18N early version of operations called tracks "secondary"
    /*static*/ /*final*/ QString Xml::YES = "yes"; // NOI18N
    /*static*/ /*final*/ QString Xml::NO = "no"; // NOI18N


    // Control.java
    /*static final*/ QString Xml::CONTROL = "control"; // NOI18N
    /*static final*/ QString Xml::BACKWARD_COMPATIBILITY = "backwardCompatibility"; // NOI18N
    /*static final*/ QString Xml::SAVE_USING_PRE_2013_FORMAT = "saveUsingPre_2013_Format"; // NOI18N
    ///*static final*/ QString Xml::LENGTH = "length"; // NOI18N
    /*static final*/ QString Xml::MAXIMUM_STRING_LENGTHS = "maximumStringLengths"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_ATTRIBUTE = "max_len_string_attibute"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_ROAD_NUMBER = "max_len_string_road_number"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_PRINT_ROAD_NUMBER = "max_len_string_print_road_number"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_LOCATION_NAME = "max_len_string_location_name"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_TRACK_NAME = "max_len_string_track_name"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_TRACK_LENGTH_NAME = "max_len_string_track_length_name"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_LENGTH_NAME = "max_len_string_length_name"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_WEIGHT_NAME = "max_len_string_weight_name"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_BUILT_NAME = "max_len_string_built_name"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_TRAIN_NAME = "max_len_string_train_name"; // NOI18N
    /*static final*/ QString Xml::MAX_LEN_STRING_ROUTE_NAME = "max_len_string_route_name"; // NOI18N
    /*static final*/ QString Xml::REPORTS = "reports"; // NOI18N

    // Setup.java
    /*static final*/ QString Xml::OPERATIONS = "operations"; // NOI18N
    /*static final*/ QString Xml::RAIL_ROAD = "railRoad"; // NOI18N
    /*static final*/ QString Xml::SETTINGS = "settings"; // NOI18N
    /*static final*/ QString Xml::MAIN_MENU = "mainMenu"; // NOI18N
    /*static final*/ QString Xml::CLOSE_ON_SAVE = "closeOnSave"; // NOI18N
    /*static final*/ QString Xml::AUTO_SAVE = "autoSave"; // NOI18N
    /*static final*/ QString Xml::AUTO_BACKUP = "autoBackup"; // NOI18N
    /*static final*/ QString Xml::TRAIN_DIRECTION = "trainDirection"; // NOI18N
    /*static final*/ QString Xml::TRAIN_LENGTH = "trainLength"; // NOI18N
    /*static final*/ QString Xml::MAX_ENGINES = "maxEngines"; // NOI18N
    /*static final*/ QString Xml::HPT = "hpt"; // NOI18N
    /*static final*/ QString Xml::SCALE = "scale"; // NOI18N
    ///*static final*/ QString Xml::CAR_TYPES = "carTypes"; // NOI18N
    /*static final*/ QString Xml::SWITCH_TIME = "switchTime"; // NOI18N
    /*static final*/ QString Xml::TRAVEL_TIME = "travelTime"; // NOI18N
    /*static final*/ QString Xml::SHOW_VALUE = "showValue"; // NOI18N
    /*static final*/ QString Xml::VALUE_LABEL = "valueLabel"; // NOI18N
    /*static final*/ QString Xml::SHOW_RFID = "showRfid"; // NOI18N
    /*static final*/ QString Xml::RFID_LABEL = "rfidLabel"; // NOI18N
    /*static final*/ QString Xml::SETUP = "setup"; // NOI18N

    /*static final*/ QString Xml::ROUTER = "router"; // NOI18N
    /*static final*/ QString Xml::CAR_ROUTING_ENABLED = "carRoutingEnabled"; // NOI18N
    /*static final*/ QString Xml::CAR_ROUTING_VIA_YARDS = "carRoutingViaYards"; // NOI18N
    /*static final*/ QString Xml::CAR_ROUTING_VIA_STAGING = "carRoutingViaStaging"; // NOI18N
    /*static final*/ QString Xml::FORWARD_TO_YARD = "forwardToYard"; // NOI18N
    /*static final*/ QString Xml::ONLY_ACTIVE_TRAINS = "onlyActiveTrains"; // NOI18N
    /*static final*/ QString Xml::CHECK_CAR_DESTINATION = "checkCarDestination"; // NOI18N

    /*static final*/ QString Xml::LOGGER = "logger"; // NOI18N
    /*static final*/ QString Xml::CAR_LOGGER = "carLogger"; // NOI18N
    /*static final*/ QString Xml::ENGINE_LOGGER = "engineLogger"; // NOI18N
    /*static final*/ QString Xml::TRAIN_LOGGER = "trainLogger"; // NOI18N

    /*static final*/ QString Xml::PRINT_LOC_COMMENTS = "printLocComments"; // NOI18N
    /*static final*/ QString Xml::PRINT_ROUTE_COMMENTS = "printRouteComments"; // NOI18N
    /*static final*/ QString Xml::PRINT_LOADS_EMPTIES = "printLoadsEmpties"; // NOI18N
    /*static final*/ QString Xml::PRINT_TIMETABLE = "printTimetable"; // NOI18N
    /*static final*/ QString Xml::USE12HR_FORMAT = "use12hrFormat"; // NOI18N
    /*static final*/ QString Xml::PRINT_VALID = "printValid"; // NOI18N
    /*static final*/ QString Xml::SORT_BY_TRACK = "sortByTrack"; // NOI18N
    /*static final*/ QString Xml::PRINT_HEADERS = "printHeaders"; // NOI18N
    /*static final*/ QString Xml::PRINT_CABOOSE_LOAD = "printCabooseLoad"; // NOI18N
    /*static final*/ QString Xml::PRINT_PASSENGER_LOAD = "printPassengerLoad"; // NOI18N

    /*static final*/ QString Xml::LENGTH_UNIT = "lengthUnit"; // NOI18N
    /*static final*/ QString Xml::YEAR_MODELED = "yearModeled"; // NOI18N

    /*static final*/ QString Xml::PICKUP_ENG_FORMAT = "pickupEngFormat"; // NOI18N
    /*static final*/ QString Xml::DROP_ENG_FORMAT = "dropEngFormat"; // NOI18N
    /*static final*/ QString Xml::PICKUP_CAR_FORMAT = "pickupCarFormat"; // NOI18N
    /*static final*/ QString Xml::DROP_CAR_FORMAT = "dropCarFormat"; // NOI18N
    /*static final*/ QString Xml::LOCAL_FORMAT = "localFormat"; // NOI18N
    /*static final*/ QString Xml::MISSING_CAR_FORMAT = "missingCarFormat"; // NOI18N

    /*static final*/ QString Xml::SWITCH_LIST_PICKUP_CAR_FORMAT = "switchListPickupCarFormat"; // NOI18N
    /*static final*/ QString Xml::SWITCH_LIST_DROP_CAR_FORMAT = "switchListDropCarFormat"; // NOI18N
    /*static final*/ QString Xml::SWITCH_LIST_LOCAL_FORMAT = "switchListLocalFormat"; // NOI18N

    /*static final*/ QString Xml::SAME_AS_MANIFEST = "sameAsManifest"; // NOI18N
    /*static final*/ QString Xml::REAL_TIME = "realTime"; // NOI18N
    /*static final*/ QString Xml::ALL_TRAINS = "allTrains"; // NOI18N
    /*static final*/ QString Xml::PAGE_MODE = "pageMode"; // NOI18N, backwards compatible for versions before 3.11
    /*static final*/ QString Xml::PAGE_FORMAT = "pageFormat"; // NOI18N
    /*static final*/ QString Xml::PAGE_NORMAL = "pageNormal"; // NOI18N
    /*static final*/ QString Xml::PAGE_PER_TRAIN = "pagePerTrain"; // NOI18N
    /*static final*/ QString Xml::PAGE_PER_VISIT = "pagePerVisit"; // NOI18N
    /*static final*/ QString Xml::PRINT_ROUTE_LOCATION = "printRouteLocation"; // NOI18N
    /*static final*/ QString Xml::TRACK_SUMMARY = "trackSummary"; // NOI18N

    /*static final*/ QString Xml::PREFIX = "prefix"; // NOI18N
    /*static final*/ QString Xml::SETTING = "setting"; // NOI18N

    /*static final*/ QString Xml::PANEL = "panel"; // NOI18N
    /*static final*/ QString Xml::TRAIN_ICONXY = "trainIconXY"; // NOI18N
    /*static final*/ QString Xml::TRAIN_ICON_APPEND = "trainIconAppend"; // NOI18N

    /*static final*/ QString Xml::FONT_NAME = "fontName"; // NOI18N
    /*static final*/ QString Xml::FONT_SIZE = "fontSize"; // NOI18N
    /*static final*/ QString Xml::SIZE = "size"; // NOI18N

    /*static final*/ QString Xml::PAGE_ORIENTATION = "pageOrientation"; // NOI18N
    /*static final*/ QString Xml::MANIFEST = "manifest"; // NOI18N
    ///*static final*/ QString Xml::SWITCH_LIST = "switchList"; // NOI18N

    /*static final*/ QString Xml::MANIFEST_COLORS = "manifestColors"; // NOI18N
    /*static final*/ QString Xml::DROP_COLOR = "dropColor"; // NOI18N
    /*static final*/ QString Xml::PICKUP_COLOR = "pickupColor"; // NOI18N
    /*static final*/ QString Xml::LOCAL_COLOR = "localColor"; // NOI18N

    /*static final*/ QString Xml::TAB = "tab"; // NOI18N
    /*static final*/ QString Xml::TAB2_LENGTH = "tab2Length"; // NOI18N
    /*static final*/ QString Xml::TAB3_LENGTH = "tab3Length"; // NOI18N
    /*static final*/ QString Xml::ENABLED = "enabled"; // NOI18N

    /*static final*/ QString Xml::COLUMN_FORMAT = "columnFormat"; // NOI18N
    /*static final*/ QString Xml::TWO_COLUMNS = "twoColumns"; // NOI18N
    /*static final*/ QString Xml::MANIFEST_FORMAT = "manifestFormat";  // NOI18N
    ///*static final*/ QString Xml::VALUE = "value"; // NOI18N
    /*static final*/ QString Xml::STANDARD = "0";	// NOI18N
    /*static final*/ QString Xml::TWO_COLUMN = "1"; // NOI18N
    /*static final*/ QString Xml::TWO_COLUMN_TRACK = "2"; // NOI18N

    /*static final*/ QString Xml::TRUNCATE = "truncate"; // NOI18N
    /*static final*/ QString Xml::USE_DEPARTURE_TIME = "useDepartureTime"; // NOI18N
    /*static final*/ QString Xml::USE_EDITOR = "useEditor"; // NOI18N
    /*static final*/ QString Xml::HAZARDOUS_MSG = "hazardousMsg"; // NOI18N

    /*static final*/ QString Xml::MANIFEST_LOGO = "manifestLogo"; // NOI18N

    /*static final*/ QString Xml::BUILD_OPTIONS = "buildOptions"; // NOI18N
    /*static final*/ QString Xml::AGGRESSIVE = "aggressive"; // NOI18N
    /*static final*/ QString Xml::NUMBER_PASSES = "numberPasses";  // NOI18N

    /*static final*/ QString Xml::ALLOW_LOCAL_INTERCHANGE = "allowLocalInterchange"; // NOI18N
    /*static final*/ QString Xml::ALLOW_LOCAL_SPUR = "allowLocalSiding"; // NOI18N
    /*static final*/ QString Xml::ALLOW_LOCAL_YARD = "allowLocalYard"; // NOI18N

    /*static final*/ QString Xml::STAGING_RESTRICTION_ENABLED = "stagingRestrictionEnabled"; // NOI18N
    /*static final*/ QString Xml::STAGING_TRACK_AVAIL = "stagingTrackAvail"; // NOI18N
    /*static final*/ QString Xml::ALLOW_RETURN_STAGING = "allowReturnStaging"; // NOI18N
    /*static final*/ QString Xml::PROMPT_STAGING_ENABLED = "promptStagingEnabled"; // NOI18N
    /*static final*/ QString Xml::PROMPT_TO_STAGING_ENABLED = "promptToStagingEnabled"; // NOI18N

    /*static final*/ QString Xml::GENERATE_CSV_MANIFEST = "generateCsvManifest"; // NOI18N
    /*static final*/ QString Xml::GENERATE_CSV_SWITCH_LIST = "generateCsvSwitchList"; // NOI18N

    ///*static final*/ QString Xml::BUILD_REPORT = "buildReport"; // NOI18N
    /*static final*/ QString Xml::LEVEL = "level"; // NOI18N
    /*static final*/ QString Xml::INDENT = "indent"; // NOI18N
    /*static final*/ QString Xml::ROUTER_LEVEL = "routerLevel"; // NOI18N
    /*static final*/ QString Xml::ALWAYS_PREVIEW = "alwaysPreview"; // NOI18N

    ///*static final*/ QString Xml::OWNER = "owner"; // NOI18N

    /*static final*/ QString Xml::ICON_COLOR = "iconColor"; // NOI18N
    /*static final*/ QString Xml::NORTH = "north"; // NOI18N
    /*static final*/ QString Xml::SOUTH = "south"; // NOI18N
    /*static final*/ QString Xml::EAST = "east"; // NOI18N
    /*static final*/ QString Xml::WEST = "west"; // NOI18N
    /*static final*/ QString Xml::LOCAL = "local"; // NOI18N
    /*static final*/ QString Xml::TERMINATE = "terminate"; // NOI18N

    /*static final*/ QString Xml::COMMENTS = "comments"; // NOI18N
    /*static final*/ QString Xml::MISPLACED_CARS = "misplacedCars"; // NOI18N

    /*static final*/ QString Xml::VSD = "vsd"; // NOI18N
    /*static final*/ QString Xml::ENABLE_PHYSICAL_LOCATIONS = "enablePhysicalLocations"; // NOI18N

    /*static final*/ QString Xml::CATS = "CATS"; // NOI18N
    /*static final*/ QString Xml::EXACT_LOCATION_NAME = "exactLocationName"; // NOI18N
// train.java
     ///*static final*/ QString Xml::TRAIN = "train"; // NOI18N
     /*static final*/ QString Xml::DESCRIPTION = "description"; // NOI18N
     /*static final*/ QString Xml::DEPART_HOUR = "departHour"; // NOI18N
     /*static final*/ QString Xml::DEPART_MINUTE = "departMinute"; // NOI18N
     /*static final*/ QString Xml::ROUTE = "route"; // NOI18N
     /*static final*/ QString Xml::SKIPS = "skips"; // NOI18N
     ///*static final*/ QString Xml::LOCATION = "location"; // NOI18N
     /*static final*/ QString Xml::ROUTE_ID = "routeId"; // NOI18N old format
     /*static final*/ QString Xml::SKIP = "skip"; // NOI18N
     ///*static final*/ QString Xml::CAR_TYPES = "carTypes"; // NOI18N
     ///*static final*/ QString Xml::TYPES = "types"; // NOI18N
     ///*static final*/ QString Xml::CAR_TYPE = "carType"; // NOI18N
     ///*static final*/ QString Xml::LOCO_TYPE = "locoType"; // NOI18N
     /*static final*/ QString Xml::CAR_ROAD_OPERATION = "carRoadOperation"; // NOI18N	should have been option not operation
     /*static final*/ QString Xml::CAR_ROAD_OPTION = "carRoadOption"; // NOI18N
     /*static final*/ QString Xml::CAR_ROADS = "carRoads"; // NOI18N
     /*static final*/ QString Xml::CAR_ROAD = "carRoad"; // NOI18N
     /*static final*/ QString Xml::CAR_LOAD_OPTION = "carLoadOption"; // NOI18N
     /*static final*/ QString Xml::CAR_LOADS = "carLoads"; // NOI18N
     /*static final*/ QString Xml::CAR_LOAD = "carLoad"; // NOI18N
     /*static final*/ QString Xml::CAR_OWNER_OPTION = "carOwnerOption"; // NOI18N
     /*static final*/ QString Xml::BUILT_START_YEAR = "builtStartYear"; // NOI18N
     /*static final*/ QString Xml::BUILT_END_YEAR = "builtEndYear"; // NOI18N
     /*static final*/ QString Xml::CAR_OWNERS = "carOwners"; // NOI18N
     /*static final*/ QString Xml::CAR_OWNER = "carOwner"; // NOI18N

     /*static final*/ QString Xml::NUMBER_ENGINES = "numberEngines"; // NOI18N
     /*static final*/ QString Xml::LEG2_ENGINES = "leg2Engines"; // NOI18N
     /*static final*/ QString Xml::LEG3_ENGINES = "leg3Engines"; // NOI18N

     /*static final*/ QString Xml::ENGINE_ROAD = "engineRoad"; // NOI18N
     /*static final*/ QString Xml::LEG2_ROAD = "leg2Road"; // NOI18N
     /*static final*/ QString Xml::LEG3_ROAD = "leg3Road"; // NOI18N

     /*static final*/ QString Xml::ENGINE_MODEL = "engineModel"; // NOI18N
     /*static final*/ QString Xml::LEG2_MODEL = "leg2Model"; // NOI18N
     /*static final*/ QString Xml::LEG3_MODEL = "leg3Model"; // NOI18N

     /*static final*/ QString Xml::REQUIRES = "requires"; // NOI18N
     /*static final*/ QString Xml::CABOOSE_ROAD = "cabooseRoad"; // NOI18N
     /*static final*/ QString Xml::LEG2_CABOOSE_ROAD = "leg2CabooseRoad"; // NOI18N
     /*static final*/ QString Xml::LEG3_CABOOSE_ROAD = "leg3CabooseRoad"; // NOI18N

     /*static final*/ QString Xml::LEG2_OPTIONS = "leg2Options"; // NOI18N
     /*static final*/ QString Xml::LEG3_OPTIONS = "leg3Options"; // NOI18N

     /*static final*/ QString Xml::BUILD_NORMAL = "buildNormal"; // NOI18N
     /*static final*/ QString Xml::TO_TERMINAL = "toTerminal"; // NOI18N
     /*static final*/ QString Xml::ALLOW_LOCAL_MOVES = "allowLocalMoves"; // NOI18N
     /*static final*/ QString Xml::ALLOW_THROUGH_CARS = "allowThroughCars"; // NOI18N
     /*static final*/ QString Xml::ALLOW_RETURN = "allowReturn"; // NOI18N
     /*static final*/ QString Xml::SERVICE_ALL = "serviceAll"; // NOI18N
     /*static final*/ QString Xml::BUILD_CONSIST = "buildConsist"; // NOI18N
     /*static final*/ QString Xml::SEND_CUSTOM_STAGING = "sendCustomStaging"; // NOI18N

     ///*static final*/ QString Xml::BUILT = "built"; // NOI18N
     /*static final*/ QString Xml::BUILD = "build"; // NOI18N
     /*static final*/ QString Xml::BUILD_FAILED = "buildFailed"; // NOI18N
     /*static final*/ QString Xml::BUILD_FAILED_MESSAGE = "buildFailedMessage"; // NOI18N
     /*static final*/ QString Xml::PRINTED = "printed"; // NOI18N
     /*static final*/ QString Xml::MODIFIED = "modified"; // NOI18N
     /*static final*/ QString Xml::SWITCH_LIST_STATUS = "switchListStatus"; // NOI18N
     /*static final*/ QString Xml::LEAD_ENGINE = "leadEngine"; // NOI18N
     /*static final*/ QString Xml::STATUS = "status"; // NOI18N
     /*static final*/ QString Xml::STATUS_CODE = "statusCode"; // NOI18N
     /*static final*/ QString Xml::TERMINATION_DATE = "TerminationDate"; // NOI18N
     /*static final*/ QString Xml::REQUESTED_CARS = "RequestedCars"; // NOI18N

     /*static final*/ QString Xml::CURRENT = "current"; // NOI18N
     /*static final*/ QString Xml::LEG2_START = "leg2Start"; // NOI18N
     /*static final*/ QString Xml::LEG3_START = "leg3Start"; // NOI18N
     /*static final*/ QString Xml::LEG2_END = "leg2End"; // NOI18N
     /*static final*/ QString Xml::LEG3_END = "leg3End"; // NOI18N
     /*static final*/ QString Xml::DEPARTURE_TRACK = "departureTrack"; // NOI18N
     /*static final*/ QString Xml::TERMINATION_TRACK = "terminationTrack"; // NOI18N

     /*static final*/ QString Xml::SCRIPTS = "scripts"; // NOI18N
     /*static final*/ QString Xml::AFTER_BUILD = "afterBuild"; // NOI18N
     ///*static final*/ QString Xml::TERMINATE = "terminate"; // NOI18N
     /*static final*/ QString Xml::MOVE = "move"; // NOI18N

     ///*static final*/ QString Xml::RAIL_ROAD = "railRoad"; // NOI18N
     ///*static final*/ QString Xml::MANIFEST_LOGO = "manifestLogo"; // NOI18N
     /*static final*/ QString Xml::SHOW_TIMES = "showTimes"; // NOI18N

// TrainManager.java
    /*static final*/ QString Xml::OPTIONS = "options"; // NOI18N
    /*static final*/ QString Xml::TRAIN_OPTIONS = "trainOptions"; // NOI18N
    /*static final*/ QString Xml::BUILD_MESSAGES = "buildMessages"; // NOI18N
    /*static final*/ QString Xml::BUILD_REPORT = "buildReport"; // NOI18N
    /*static final*/ QString Xml::PRINT_PREVIEW = "printPreview"; // NOI18N
    /*static final*/ QString Xml::OPEN_FILE = "openFile"; // NOI18N
    /*static final*/ QString Xml::TRAIN_ACTION = "trainAction"; // NOI18N

    /*static final*/ QString Xml::COLUMN_WIDTHS = "columnWidths"; // NOI18N TODO This here is for backwards compatibility, remove after next major release

    /*static final*/ QString Xml::TRAIN_SCHEDULE_OPTIONS = "trainScheduleOptions"; // NOI18N
    /*static final*/ QString Xml::ACTIVE_ID = "activeId"; // NOI18N
    /*static final*/ QString Xml::START_UP = "startUp"; // NOI18N
    /*static final*/ QString Xml::SHUT_DOWN = "shutDown"; // NOI18N

    /*static*/ /*final*/ QString Xml::CONDUCTOR_OPTIONS = "conductorOptions"; // NOI18N
    /*static*/ /*final*/ QString Xml::SHOW_HYPHEN_NAME = "showHyphenName"; // NOI18N



    /*static final*/ QString Xml::ROW_COLOR_OPTIONS = "rowColorOptions"; // NOI18N
    /*static final*/ QString Xml::ROW_COLOR_MANUAL = "rowColorManual"; // NOI18N
    /*static final*/ QString Xml::ROW_COLOR_BUILT = "rowColorBuilt"; // NOI18N
    /*static final*/ QString Xml::ROW_COLOR_BUILD_FAILED = "rowColorBuidFailed"; // NOI18N
    /*static final*/ QString Xml::ROW_COLOR_TRAIN_EN_ROUTE = "rowColorTrainEnRoute"; // NOI18N
    /*static final*/ QString Xml::ROW_COLOR_TERMINATED = "rowColorTerminated"; // NOI18N

// TrainManagerXml.java
/*static*/ /*final*/ QString Xml::TRAINS = "trains"; // NOI18N

// ManifestCreator.java
    /*static final*/ QString Xml::MANIFEST_CREATOR = "manifestCreator"; // NOI18N
    /*static final*/ QString Xml::RUN_FILE = "runFile"; // NOI18N
    /*static final*/ QString Xml::DIRECTORY = "directory"; // NOI18N
    /*static final*/ QString Xml::COMMON_FILE = "commonFile"; // NOI18N

// RollingStock.java
   /*static*/ /*final*/ QString Xml::ROAD_NUMBER = "roadNumber"; // NOI18N
   /*static*/ /*final*/ QString Xml::ROAD_NAME = "roadName"; // NOI18N
   /*static*/ /*final*/ QString Xml::COLOR = "color"; // NOI18N
   /*static*/ /*final*/ QString Xml::WEIGHT = "weight"; // NOI18N
   /*static*/ /*final*/ QString Xml::WEIGHT_TONS = "weightTons"; // NOI18N
   /*static*/ /*final*/ QString Xml::BUILT = "built"; // NOI18N
   /*static*/ /*final*/ QString Xml::LOCATION = "location"; // NOI18N
   /*static*/ /*final*/ QString Xml::MOVES = "moves"; // NOI18N
   /*static*/ /*final*/ QString Xml::OWNER = "owner"; // NOI18N
   /*static*/ /*final*/ QString Xml::VALUE = "value"; // NOI18N
   /*static*/ /*final*/ QString Xml::RFID = "rfid"; // NOI18N
   /*static*/ /*final*/ QString Xml::TRAIN = "train"; // NOI18N
   /*static*/ /*final*/ QString Xml::TRAIN_ID = "trainId"; // NOI18N
   /*static*/ /*final*/ QString Xml::OUT_OF_SERVICE = "outOfService"; // NOI18N
   /*static*/ /*final*/ QString Xml::DESTINATION = "destination"; // NOI18N
   /*static*/ /*final*/ QString Xml::DES_TRACK = "desTrack"; // NOI18N
   /*static*/ /*final*/ QString Xml::LOC_UNKNOWN = "locUnknown"; // NOI18N
   /*static*/ /*final*/ QString Xml::DATE = "date"; // NOI18N
   /*static*/ /*final*/ QString Xml::BLOCKING = "blocking"; // NOI18N
   /*static*/ /*final*/ QString Xml::SELECTED = "selected"; // NOI18N
/*static*/ /*final*/ QString Xml::TYPE = "type"; // NOI18N

// Engine.java
   /*static*/ /*final*/ QString Xml::ENGINE = "engine"; // NOI18N
   /*static*/ /*final*/ QString Xml::HP = "hp"; // NOI18N
   /*static*/ /*final*/ QString Xml::B_UNIT = "bUnit"; // NOI18N

   ///*static*/ /*final*/ QString Xml::TYPE = "type"; // NOI18N

   ///*static*/ /*final*/ QString Xml::WEIGHT_TONS = "weightTons"; // NOI18N
   /*static*/ /*final*/ QString Xml::CONSIST = "consist"; // NOI18N
   /*static*/ /*final*/ QString Xml::LEAD_CONSIST = "leadConsist"; // NOI18N
   /*static*/ /*final*/ QString Xml::CONSIST_NUM = "consistNum"; // NOI18N

    // EngineManager.java
   /*static*/ /*final*/ QString Xml::ENGINES_OPTIONS = "enginesOptions"; // NOI18N
   ///*static*/ /*final*/ QString Xml::COLUMN_WIDTHS = "columnWidths"; // NOI18N backwards compatible TODO remove in 2013 after production release
  // /*static*/ /*final*/ QString Xml::OPTIONS = "options"; // NOI18N
   /*static*/ /*final*/ QString Xml::CONSISTS = "consists";  // NOI18N
   /*static*/ /*final*/ QString Xml::NEW_CONSISTS = "newConsists";  // NOI18N

    // EngineManagerXml.java
   /*static*/ /*final*/ QString Xml::ENGINES = "engines";  // NOI18N

    // EngineModels.java
   /*static*/ /*final*/ QString Xml::ENGINE_MODELS = "engineModels";  // NOI18N
   /*static*/ /*final*/ QString Xml::MODELS = "models";  // NOI18N

    // EngineTypes.java
   /*static*/ /*final*/ QString Xml::ENGINE_TYPES = "engineTypes";  // NOI18N
   ///*static*/ /*final*/ QString Xml::TYPES = "types"; // NOI18N

    // EngineLengths.java
   /*static*/ /*final*/ QString Xml::ENGINE_LENGTHS = "engineLengths";  // NOI18N
   /*static*/ /*final*/ QString Xml::LENGTHS = "lengths"; // NOI18N
   ///*static*/ /*final*/ QString Xml::VALUE = "value"; // NOI18N
/*static*/ /*final*/ QString Xml::MODEL = "model";  // NOI18N

/*static*/ /*final*/ QString Xml::LOCATION_ID ="locationId"; // NOI18N
/*static*/ /*final*/ QString Xml::SEC_LOCATION_ID="secLocationId"; // NOI18N
/*static*/ /*final*/ QString Xml::DESTINATION_ID="destinationId"; // NOI18N
/*static*/ /*final*/ QString Xml::SEC_DESTINATION_ID="secDestinationId"; // NOI18N
/*static*/ /*final*/ QString Xml::LAST_LOCATION_ID="lastLocationId"; // NOI18N
/*static*/ /*final*/ QString Xml::ROUTE_LOCATION_ID="routeLocationId"; // NOI18N
/*static*/ /*final*/ QString Xml::ROUTE_DESTINATION_ID="routeDestinationId"; // NOI18N
/*static*/ /*final*/ QString Xml::LAST_ROUTE_ID="lastRouteId"; // NOI18N

// Car.java
    /*static*/ /*final*/ QString Xml::CAR = "car"; // NOI18N
    /*static*/ /*final*/ QString Xml::PASSENGER = "passenger"; // NOI18N
    /*static*/ /*final*/ QString Xml::HAZARDOUS = "hazardous"; // NOI18N
    /*static*/ /*final*/ QString Xml::CABOOSE = "caboose"; // NOI18N
    /*static*/ /*final*/ QString Xml::FRED = "fred"; // NOI18N
    /*static*/ /*final*/ QString Xml::UTILITY = "utility"; // NOI18N
    /*static*/ /*final*/ QString Xml::KERNEL = "kernel"; // NOI18N
    /*static*/ /*final*/ QString Xml::LEAD_KERNEL = "leadKernel"; // NOI18N

   /*static*/ /*final*/ QString Xml::LOAD_FROM_STAGING = "loadFromStaging"; // NOI18N
   /*static*/ /*final*/ QString Xml::WAIT = "wait"; // NOI18N
   /*static*/ /*final*/ QString Xml::PICKUP_SCHEDULE_ID = "pickupId"; // NOI18N
   /*static*/ /*final*/ QString Xml::ORDER = "order"; // NOI18N
   /*static*/ /*final*/ QString Xml::SCHEDULE_ID = "scheduleId"; // NOI18N

// CarManager.java
    ///*static*/ /*final*/ QString Xml::OPTIONS = "options"; // NOI18N
    /*static*/ /*final*/ QString Xml::CARS = "cars"; // NOI18N
    /*static*/ /*final*/ QString Xml::CARS_OPTIONS = "carsOptions"; // NOI18N
    ///*static*/ /*final*/ QString Xml::COLUMN_WIDTHS = "columnWidths"; // NOI18N backwards compatible TODO remove in 2013 after production release
    /*static*/ /*final*/ QString Xml::KERNELS = "kernels"; // NOI18N
    /*static*/ /*final*/ QString Xml::NEW_KERNELS = "newKernels"; // NOI18N

// CarRoads.java
    /*static final*/ QString Xml::ROAD_NAMES = "roadNames"; // NOI18N
    /*static final*/ QString Xml::ROADS = "roads"; // NOI18N
    /*static final*/ QString Xml::ROAD = "road"; // NOI18N
// Track.java
/*static*/ /*final*/ QString Xml::LOC_TYPE ="locType"; // NOI18N
/*static*/ /*final*/ QString Xml::LENGTH = "length"; // NOI18N
///*static*/ /*final*/ QString Xml::MOVES = "moves"; // NOI18N
/*static*/ /*final*/ QString Xml::BLOCKING_ORDER = "blockingOrder"; // NOI18N
///*static*/ /*final*/ QString Xml::CAR_ROAD_OPERATION = "carRoadOperation"; // NOI18N misspelled should have been carRoadOption
///*static*/ /*final*/ QString Xml::CAR_ROAD_OPTION = "carRoadOption"; // NOI18N
///*static*/ /*final*/ QString Xml::CAR_ROADS = "carRoads"; // NOI18N
///*static*/ /*final*/ QString Xml::CAR_ROAD = "carRoad"; // NOI18N
///*static*/ /*final*/ QString Xml::CAR_LOAD_OPTION = "carLoadOption"; // NOI18N
/*static*/ /*final*/ QString Xml::CAR_SHIP_LOAD_OPTION = "carShipLoadOption"; // NOI18N
///*static*/ /*final*/ QString Xml::CAR_LOADS = "carLoads"; // NOI18N
/*static*/ /*final*/ QString Xml::CAR_SHIP_LOADS = "carShipLoads"; // NOI18N
///*static*/ /*final*/ QString Xml::CAR_LOAD = "carLoad"; // NOI18N
/*static*/ /*final*/ QString Xml::DROP_IDS = "dropIds"; // NOI18N
/*static*/ /*final*/ QString Xml::DROP_ID = "dropId"; // NOI18N
/*static*/ /*final*/ QString Xml::DROP_OPTION = "dropOption"; // NOI18N
/*static*/ /*final*/ QString Xml::PICKUP_IDS = "pickupIds"; // NOI18N
/*static*/ /*final*/ QString Xml::PICKUP_ID = "pickupId"; // NOI18N
/*static*/ /*final*/ QString Xml::PICKUP_OPTION = "pickupOption"; // NOI18N
///*static*/ /*final*/ QString Xml::COMMENTS = "comments"; // NOI18N
/*static*/ /*final*/ QString Xml::BOTH = "both"; // NOI18N
/*static*/ /*final*/ QString Xml::PICKUP = "pickup"; // NOI18N
/*static*/ /*final*/ QString Xml::SETOUT = "setout"; // NOI18N
/*static*/ /*final*/ QString Xml::TRACK_DESTINATION_OPTION = "trackDestinationOption"; // NOI18N
/*static*/ /*final*/ QString Xml::DESTINATIONS = "destinations"; // NOI18N
///*static*/ /*final*/ QString Xml::DESTINATION = "destination"; // NOI18N

///*static*/ /*final*/ QString Xml::SCHEDULE_ID = "scheduleId"; // NOI18N
/*static*/ /*final*/ QString Xml::ITEM_ID = "itemId"; // NOI18N
/*static*/ /*final*/ QString Xml::ITEM_COUNT = "itemCount"; // NOI18N
/*static*/ /*final*/ QString Xml::FACTOR = "factor"; // NOI18N
/*static*/ /*final*/ QString Xml::SCHEDULE_MODE = "scheduleMode"; // NOI18N
/*static*/ /*final*/ QString Xml::ALTERNATIVE = "alternative"; // NOI18N
/*static*/ /*final*/ QString Xml::LOAD_OPTIONS = "loadOptions"; // NOI18N
/*static*/ /*final*/ QString Xml::BLOCK_OPTIONS = "blockOptions"; // NOI18N
///*static*/ /*final*/ QString Xml::ORDER = "order"; // NOI18N
/*static*/ /*final*/ QString Xml::POOL = "pool"; // NOI18N
/*static*/ /*final*/ QString Xml::MIN_LENGTH = "minLength"; // NOI18N
/*static*/ /*final*/ QString Xml::IGNORE_USED_PERCENTAGE = "ignoreUsedPercentage"; // NOI18N

// RouteLocation.java
    ///*static*/ /*final*/ QString Xml::LOCATION_ID = "locationId"; // NOI18N
    ///*static*/ /*final*/ QString Xml::TRAIN_DIRECTION = "trainDirection"; // NOI18N
    /*static*/ /*final*/ QString Xml::MAX_TRAIN_LENGTH = "maxTrainLength"; // NOI18N
    /*static*/ /*final*/ QString Xml::GRADE = "grade"; // NOI18N
    /*static*/ /*final*/ QString Xml::MAX_CAR_MOVES = "maxCarMoves"; // NOI18N
    /*static*/ /*final*/ QString Xml::RANDOM_CONTROL = "randomControl"; // NOI18N
    /*static*/ /*final*/ QString Xml::PICKUPS = "pickups"; // NOI18N
    /*static*/ /*final*/ QString Xml::DROPS = "drops"; // NOI18N
    ///*static*/ /*final*/ QString Xml::WAIT = "wait"; // NOI18N
    /*static*/ /*final*/ QString Xml::DEPART_TIME = "departTime"; // NOI18N
    /*static*/ /*final*/ QString Xml::TRAIN_ICON_X = "trainIconX"; // NOI18N
    /*static*/ /*final*/ QString Xml::TRAIN_ICON_Y = "trainIconY"; // NOI18N
    /*static*/ /*final*/ QString Xml::SEQUENCE_ID = "sequenceId"; // NOI18N

/*static*/ /*final*/ QString Xml::NEXT_LOAD = "nextLoad"; // NOI18N
    /*static*/ /*final*/ QString Xml::NEXT_WAIT = "nextWait"; // NOI18N
    /*static*/ /*final*/ QString Xml::NEXT_PICKUP_SCHEDULE_ID = "nextPickupId"; // NOI18N
    /*static*/ /*final*/ QString Xml::NEXT_DEST_ID = "nextDestId"; // NOI18N
    /*static*/ /*final*/ QString Xml::NEXT_DEST_TRACK_ID = "nextDestTrackId"; // NOI18N
    /*static*/ /*final*/ QString Xml::PREVIOUS_NEXT_DEST_ID = "previousNextDestId"; // NOI18N
    /*static*/ /*final*/ QString Xml::PREVIOUS_NEXT_DEST_TRACK_ID = "previousNextDestTrackId"; // NOI18N
    /*static*/ /*final*/ QString Xml::PREVIOUS_SCHEDULE_ID = "previousScheduleId"; // NOI18N
    /*static*/ /*final*/ QString Xml::RWE_DEST_ID = "rweDestId"; // NOI18N
    /*static*/ /*final*/ QString Xml::RWE_DEST_TRACK_ID = "rweDestTrackId"; // NOI18N
    /*static*/ /*final*/ QString Xml::RWE_LOAD = "rweLoad"; // NOI18N

// CarLengths.java
    /*static*/ /*final*/ QString Xml::CAR_LENGTHS = "carLengths";
// CarLoads.java
    /*static*/ /*final*/ QString Xml::LOADS = "loads"; // NOI18N
    /*static*/ /*final*/ QString Xml::NAMES = "names"; // NOI18N old style had a list of names
    /*static*/ /*final*/ QString Xml::DEFAULTS = "defaults"; // NOI18N
    /*static*/ /*final*/ QString Xml::EMPTY = "empty"; // NOI18N
    ///*static*/ /*final*/ QString Xml::CAR_LOAD = "carLoad"; // NOI18N
    /*static*/ /*final*/ QString Xml::PRIORITY = "priority"; // NOI18N
    /*static*/ /*final*/ QString Xml::PICKUP_COMMENT = "pickupComment"; // NOI18N
    /*static*/ /*final*/ QString Xml::DROP_COMMENT = "dropComment"; // NOI18N
    /*static*/ /*final*/ QString Xml::LOAD_TYPE = "loadType"; // NOI18N
    /*static*/ /*final*/ QString Xml::OWNERS = "owners";
// RouteManagerXml.java
    /*static*/ /*final*/ QString Xml::ROUTES = "routes"; // NOI18N

// CarColors.java
    /*static*/ /*final*/ QString Xml::CAR_COLORS = "carColors"; // NOI18N
    /*static*/ /*final*/ QString Xml::COLORS = "colors"; // NOI18N
    ///*static*/ /*final*/ QString Xml::COLOR = "color"; // NOI18N
// TrainManifestHeaderText.jafa
   /*static*/ /*final*/ QString Xml::MANIFEST_HEADER_TEXT_STRINGS = "manifestHeaderTextStrings"; // NOI18N
   ///*static*/ /*final*/ QString Xml::ROAD = "road"; // the supported message format options NOI18N
   /*static*/ /*final*/ QString Xml::NUMBER = "number"; // NOI18N
   /*static*/ /*final*/ QString Xml::ENGINE_NUMBER = "engineNumber"; // NOI18N
   ///*static*/ /*final*/ QString Xml::TYPE = "type"; // NOI18N
   ///*static*/ /*final*/ QString Xml::MODEL = "model"; // NOI18N
   ///*static*/ /*final*/ QString Xml::LENGTH = "length"; // NOI18N
   ///*static*/ /*final*/ QString Xml::LOAD = "load"; // NOI18N
   ///*static*/ /*final*/ QString Xml::COLOR = "color"; // NOI18N
   ///*static*/ /*final*/ QString Xml::TRACK = "track"; // NOI18N
   ///*static*/ /*final*/ QString Xml::DESTINATION = "destination"; // NOI18N
   /*static*/ /*final*/ QString Xml::DEST_TRACK = "dest_Track"; // NOI18N
   /*static*/ /*final*/ QString Xml::FINAL_DEST = "Final_Dest"; // NOI18N
   /*static*/ /*final*/ QString Xml::FINAL_DEST_TRACK = "fd_Track"; // NOI18N
   ///*static*/ /*final*/ QString Xml::LOCATION = "location"; // NOI18N
   ///*static*/ /*final*/ QString Xml::CONSIST = "consist"; // NOI18N
   ///*static*/ /*final*/ QString Xml::KERNEL = "kernel"; // NOI18N
   ///*static*/ /*final*/ QString Xml::OWNER = "owner"; // NOI18N
   /*static*/ /*final*/ QString Xml::RWE = "rwe"; // NOI18N
   ///*static*/ /*final*/ QString Xml::COMMENT = "Comment"; // NOI18N
   ///*static*/ /*final*/ QString Xml::DROP_COMMENT = "setOut_msg"; // NOI18N
   ///*static*/ /*final*/ QString Xml::PICKUP_COMMENT = "pickUp_msg"; // NOI18N
  // /*static*/ /*final*/ QString Xml::HAZARDOUS = "hazardous"; // NOI18N
   /*static*/ /*final*/ QString Xml::TEXT= "text"; // NOI18N
// SccheduleManager.java
/*static*/ /*final*/ QString Xml::SCHEDULES = "schedules"; // NOI18N

// ScheduleItem.java
/*static*/ /*final*/ QString Xml::ITEM = "item"; // NOI18N
/*static*/ /*final*/ QString Xml::RANDOM = "random"; // NOI18N
/*static*/ /*final*/ QString Xml::TRAIN_SCHEDULE_ID = "trainScheduleId"; // NOI18N
/*static*/ /*final*/ QString Xml::PICKUP_TRAIN_SCHEDULE_ID = "pickupTrainScheduleId"; // NOI18N
/*static*/ /*final*/ QString Xml::COUNT = "count"; // NOI18N
/*static*/ /*final*/ QString Xml::SHIP = "ship"; // NOI18N
///*static*/ /*final*/ QString Xml::DESTINATION_ID = "destinationId"; // NOI18N
/*static*/ /*final*/ QString Xml::DEST_TRACK_ID = "destTrackId"; // NOI18N
/*static*/ /*final*/ QString Xml::HITS = "hits"; // NOI18N
// TrainSchedule.java
//static final String SCHEDULE = "schedule"; // NOI18N
/*static*/ /*final*/ QString Xml::TRAIN_IDS = "trainIds"; // NOI18N
/*static*/ /*final*/ QString Xml::ROW_COLOR = "rowColor";  // NOI18N

// TrainManifestText.java
    /*static final*/ QString Xml::MANIFEST_TEXT_STRINGS = "manifestTextStrings"; // NOI18N
    /*static final*/ QString Xml::MANIFEST_FOR_TRAIN = "manifestForTrain"; // NOI18N
    /*static final*/ QString Xml::VALID = "valid"; // NOI18N
    /*static final*/ QString Xml::SCHEDULED_WORK = "scheduledWork"; // NOI18N
    /*static final*/ QString Xml::WORK_DEPARTURE_TIME = "workDepartureTime"; // NOI18N
    /*static final*/ QString Xml::WORK_ARRIVAL_TIME = "workArrivalTime"; // NOI18N
    /*static final*/ QString Xml::NO_SCHEDULED_WORK = "noScheduledWork"; // NOI18N
    /*static final*/ QString Xml::NO_SCHEDULED_WORK_ROUTE_COMMENT = "noScheduledWorkRouteComment"; // NOI18N
    //static final*/ QString Xml::DEPART_TIME = "departTime"; // NOI18N
    /*static final*/ QString Xml::TRAIN_DEPARTS_CARS = "trainDepartsCars"; // NOI18N
    /*static final*/ QString Xml::TRAIN_DEPARTS_LOADS = "trainDepartsLoads"; // NOI18N
    /*static final*/ QString Xml::TRAIN_TERMINATES = "trainTerminates"; // NOI18N
    //static final*/ QString Xml::DESTINATION = "destination"; // NOI18N
    /*static final*/ QString Xml::FROM = "from"; // NOI18N
    /*static final*/ QString Xml::TO = "to"; // NOI18N
    /*static final*/ QString Xml::DEST = "dest"; // NOI18N
    ///*static final*/ QString Xml::FINAL_DEST = "finalDest"; // NOI18N
    /*static final*/ QString Xml::ADD_HELPERS = "addHelpers"; // NOI18N
    /*static final*/ QString Xml::REMOVE_HELPERS = "removeHelpers"; // NOI18N
    /*static final*/ QString Xml::LOCO_CHANGE = "locoChange"; // NOI18N
    /*static final*/ QString Xml::CABOOSE_CHANGE = "cabooseChange"; // NOI18N
    /*static final*/ QString Xml::LOCO_CABOOSE_CHANGE = "locoCabooseChange"; // NOI18N

// TrainSwitchListText.java
/*static final*/ QString Xml::SWITCH_LIST_TEXT_STRINGS = "switchListTextStrings"; // NOI18N
/*static final*/ QString Xml::SWICH_LIST_FOR = "switchListFor"; // NOI18N
/*static final*/ QString Xml::SCHEDULED_WORK_TRAIN = "scheduledWorkTrain"; // NOI18N

/*static final*/ QString Xml::DEPARTS_AT = "departsAt"; // NOI18N
/*static final*/ QString Xml::DEPARTS_EXPECTED_ARRIVAL = "departsExpectedArrival"; // NOI18N
/*static final*/ QString Xml::DEPARTED_EXPECTED = "departedExpected"; // NOI18N

/*static final*/ QString Xml::VISIT_NUMBER = "visitNumber"; // NOI18N
/*static final*/ QString Xml::VISIT_NUMBER_DEPARTED = "visitNumberDeparted"; // NOI18N
/*static final*/ QString Xml::VISIT_NUMBER_TERMINATES = "visitNumberTerminates"; // NOI18N
/*static final*/ QString Xml::VISIT_NUMBER_TERMINATES_DEPARTED = "visitNumberTerminatesDeparted"; // NOI18N
/*static final*/ QString Xml::VISIT_NUMBER_DONE = "visitNumberDone"; // NOI18N

/*static final*/ QString Xml::TRAIN_DIRECTION_CHANGE = "trainDirectionChange"; // NOI18N
/*static final*/ QString Xml::NO_CAR_PICK_UPS = "noCarPickUps"; // NOI18N
/*static final*/ QString Xml::NO_CAR_SET_OUTS = "noCarSetOuts"; // NOI18N
/*static final*/ QString Xml::TRAIN_DONE = "trainDone"; // NOI18N

/*static final*/ QString Xml::SWITCH_LIST_TRACK = "switchListTrack";
/*static final*/ QString Xml::HOLD_CAR = "holdCar";

// SwitchListCreator
/*static*/ /*final*/ QString Xml::SWITCHLIST_CREATOR = "switchlistCreator"; // NOI18N
