#include "json.h"

/**
 * Constants used in the JMRI JSON protocol.
 * <p>
 * With the exception of the constants F0-F28 (see {@link #F}), all object names
 * used in the JMRI JSON protocol are constants in this class.
 *
 * @author Randall Wood (C) 2013, 2014
 */
//public*/ /*final*/ class JSON {

/**
 * JMRI JSON protocol version.
 * <p>
 * Changes to the major number represent a backwards incompatible change in
 * the protocol, while changes to the minor number represent an addition to
 * the protocol.
 * <p>
 * Protocol version 1.0 was first introduced in JMRI 3.4<br>
 * Protocol version 1.1 was first introduced in JMRI 3.7.1 and finalized in
 * JMRI 3.8<br>
 * Protocol version 2.0 was first introduced in JMRI 3.9.3 and finalized in
 * JMRI 3.10<br>
 * Protocol version 3.0 was first introduced in JMRI 3.11.2.
 * <p>
 * {@value #JSON_PROTOCOL_VERSION}
 */
/*public*/ /*static final*/ QString JSON::JSON_PROTOCOL_VERSION = "3.0"; // NOI18N

/* JSON structure */
/**
 * {@value #TYPE}
 */
/*public*/ /*static final*/ QString JSON::TYPE = "type"; // NOI18N
/**
 * {@value #LIST}
 */
/*public*/ /*static final*/ QString JSON::LIST = "list"; // NOI18N
/**
 * {@value #DATA}
 */
/*public*/ /*static final*/ QString JSON::DATA = "data"; // NOI18N
/**
 * {@value #PING}
 */
/*public*/ /*static final*/ QString JSON::PING = "ping"; // NOI18N
/**
 * {@value #PONG}
 */
/*public*/ /*static final*/ QString JSON::PONG = "pong"; // NOI18N
/**
 * {@value #GOODBYE}
 */
/*public*/ /*static final*/ QString JSON::GOODBYE = "goodbye"; // NOI18N
/**
 * {@value #NAME}
 */
/*public*/ /*static final*/ QString JSON::NAME = "name"; // NOI18N

/* JSON methods */
/**
 * {@value #METHOD}
 */
/*public*/ /*static final*/ QString JSON::METHOD = "method"; // NOI18N
/**
 * {@value #DELETE}
 */
/*public*/ /*static final*/ QString JSON::DELETE = "delete"; // NOI18N
/**
 * {@value #GET}
 */
/*public*/ /*static final*/ QString JSON::GET = "get"; // NOI18N
/**
 * {@value #POST}
 */
/*public*/ /*static final*/ QString JSON::POST = "post"; // NOI18N
/**
 * {@value #PUT}
 */
/*public*/ /*static final*/ QString JSON::PUT = "put"; // NOI18N

/* JSON common tokens */
/**
 * {@value #COMMENT}
 */
/*public*/ /*static final*/ QString JSON::COMMENT = "comment"; // NOI18N
/**
 * {@value #USERNAME}
 */
/*public*/ /*static final*/ QString JSON::USERNAME = "userName"; // NOI18N
/**
 * {@value #STATE}
 */
/*public*/ /*static final*/ QString JSON::STATE = "state"; // NOI18N
/**
 * {@value #VALUE}
 */
/*public*/ /*static final*/ QString JSON::VALUE = "value"; // NOI18N
/**
 * {@value #ID}
 */
/*public*/ /*static final*/ QString JSON::ID = "id"; // NOI18N
/**
 * {@value #STATUS}
 */
/*public*/ /*static final*/ QString JSON::STATUS = "status"; // NOI18N
/**
 * Numeric status value
 *
 * {@value #STATUS_CODE}
 */
/*public*/ /*static final*/ QString JSON::STATUS_CODE = "statusCode"; // NOI18N
/**
  * {@value #PROPERTIES}
  */
 /*public*/ /*static*/ /*final*/ QString JSON::PROPERTIES = "properties"; // NOI18N
/* JSON error */
/**
 * {@value #ERROR}
 */
/*public*/ /*static final*/ QString JSON::ERROR = "error"; // NOI18N
/**
 * {@value #CODE}
 */
/*public*/ /*static final*/ QString JSON::CODE = "code"; // NOI18N
/**
 * {@value #MESSAGE}
 */
/*public*/ /*static final*/ QString JSON::MESSAGE = "message"; // NOI18N

/* JSON hello and metadata */
/**
 * {@value #HELLO}
 */
/*public*/ /*static final*/ QString JSON::HELLO = "hello"; // NOI18N
/**
 * {@value #JMRI}
 */
/*public*/ /*static final*/ QString JSON::JMRI = "JMRI"; // NOI18N
/**
 * {@value #HEARTBEAT}
 */
/*public*/ /*static final*/ QString JSON::HEARTBEAT = "heartbeat"; // NOI18N
/**
 * {@value #RAILROAD}
 */
/*public*/ /*static final*/ QString JSON::RAILROAD = "railroad"; // NOI18N
/**
 * {@value #NODE}
 * <p>
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::NODE = "node"; // NOI18N
/**
 * {@value #ACTIVE_PROFILE}
 * <p>
 * @since 3.0
 */
/*public*/ /*static final*/ QString JSON::ACTIVE_PROFILE = "activeProfile"; // NOI18N
/**
 * {@value #FORMER_NODES}
 * <p>
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::FORMER_NODES = "formerNodes"; // NOI18N
/**
 * {@value #LOCALE}
 * <p>
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::LOCALE = "locale"; // NOI18N

/* JSON list types */
/**
 * {@value #CARS}
 */
/*public*/ /*static final*/ QString JSON::CARS = "cars"; // NOI18N
/**
 * {@value #CONSISTS}
 */
/*public*/ /*static final*/ QString JSON::CONSISTS = "consists"; // NOI18N
/**
 * {@value #ENGINES}
 */
/*public*/ /*static final*/ QString JSON::ENGINES = "engines"; // NOI18N
/**
 * {@value #LIGHTS}
 */
/*public*/ /*static final*/ QString JSON::LIGHTS = "lights"; // NOI18N
/**
 * {@value #LOCATIONS}
 */
/*public*/ /*static final*/ QString JSON::LOCATIONS = "locations"; // NOI18N
/**
 * {@value #MEMORIES}
 */
/*public*/ /*static final*/ QString JSON::MEMORIES = "memories"; // NOI18N
/**
 * {@value #METADATA}
 */
/*public*/ /*static final*/ QString JSON::METADATA = "metadata"; // NOI18N
/**
 * {@value #PANELS}
 */
/*public*/ /*static final*/ QString JSON::PANELS = "panels"; // NOI18N
/**
 * {@value #REPORTERS}
 */
/*public*/ /*static final*/ QString JSON::REPORTERS = "reporters"; // NOI18N
/**
 * {@value #ROSTER}
 */
/*public*/ /*static final*/ QString JSON::ROSTER = "roster"; // NOI18N
/**
 * {@value #ROSTER_GROUP}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::ROSTER_GROUP = "rosterGroup"; // NOI18N
/**
 * {@value #ROSTER_GROUPS}
 */
/*public*/ /*static final*/ QString JSON::ROSTER_GROUPS = "rosterGroups"; // NOI18N
/**
 * {@value #ROUTES}
 */
/*public*/ /*static final*/ QString JSON::ROUTES = "routes"; // NOI18N
/**
 * {@value #SENSORS}
 */
/*public*/ /*static final*/ QString JSON::SENSORS = "sensors"; // NOI18N
/**
 * {@value #SIGNAL_HEADS}
 */
/*public*/ /*static final*/ QString JSON::SIGNAL_HEADS = "signalHeads"; // NOI18N
/**
 * {@value #SIGNAL_MASTS}
 */
/*public*/ /*static final*/ QString JSON::SIGNAL_MASTS = "signalMasts"; // NOI18N
/**
 * {@value #TRAINS}
 */
/*public*/ /*static final*/ QString JSON::TRAINS = "trains"; // NOI18N
/**
 * {@value #TURNOUTS}
 */
/*public*/ /*static final*/ QString JSON::TURNOUTS = "turnouts"; // NOI18N
/**
 * {@value #NETWORK_SERVICES}
 */
/*public*/ /*static final*/ QString JSON::NETWORK_SERVICES = "networkServices"; // NOI18N

/* JSON data types */
/**
 * {@value #CAR}
 */
/*public*/ /*static final*/ QString JSON::CAR = "car"; // NOI18N
/**
 * {@value #CONSIST}
 */
/*public*/ /*static final*/ QString JSON::CONSIST = "consist"; // NOI18N
/**
 * {@value #ENGINE}
 */
/*public*/ /*static final*/ QString JSON::ENGINE = "engine"; // NOI18N
/**
 * {@value #LIGHT}
 */
/*public*/ /*static final*/ QString JSON::LIGHT = "light"; // NOI18N
/**
 * {@value #LOCATION}
 */
/*public*/ /*static final*/ QString JSON::LOCATION = "location"; // NOI18N
/**
 * {@value #LOCATION_ID}
 */
/*public*/ /*static final*/ QString JSON::LOCATION_ID = "locationId"; // NOI18N
/**
 * {@value #MEMORY}
 */
/*public*/ /*static final*/ QString JSON::MEMORY = "memory"; // NOI18N
/**
 * {@value #NETWORK_SERVICE}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::NETWORK_SERVICE = "networkService"; // NOI18N
/**
 * {@value #PANEL}
 */
/*public*/ /*static final*/ QString JSON::PANEL = "panel"; // NOI18N
/**
 * {@value #POWER}
 */
/*public*/ /*static final*/ QString JSON::POWER = "power"; // NOI18N
/**
 * {@value #PROGRAMMER}
 */
/*public*/ /*static final*/ QString JSON::PROGRAMMER = "programmer"; // NOI18N
/**
 * {@value #ROUTE}
 */
/*public*/ /*static final*/ QString JSON::ROUTE = "route"; // NOI18N
/**
 * {@value #SENSOR}
 */
/*public*/ /*static final*/ QString JSON::SENSOR = "sensor"; // NOI18N
/**
 * {@value #SIGNAL_HEAD}
 */
/*public*/ /*static final*/ QString JSON::SIGNAL_HEAD = "signalHead"; // NOI18N
/**
 * {@value #SIGNAL_MAST}
 */
/*public*/ /*static final*/ QString JSON::SIGNAL_MAST = "signalMast"; // NOI18N
/**
 * {@value #REPORTER}
 */
/*public*/ /*static final*/ QString JSON::REPORTER = "reporter"; // NOI18N
/**
 * {@value #ROSTER_ENTRY}
 */
/*public*/ /*static final*/ QString JSON::ROSTER_ENTRY = "rosterEntry"; // NOI18N
/**
 * {@value #THROTTLE}
 */
/*public*/ /*static final*/ QString JSON::THROTTLE = "throttle"; // NOI18N
/**
 * {@value #TIME}
 */
/*public*/ /*static final*/ QString JSON::TIME = "time"; // NOI18N
/**
 * {@value #TRAIN}
 */
/*public*/ /*static final*/ QString JSON::TRAIN = "train"; // NOI18N
/**
 * {@value #TURNOUT}
 */
/*public*/ /*static final*/ QString JSON::TURNOUT = "turnout"; // NOI18N

/* JSON operations tokens */
/**
 * {@value #ICON_NAME}
 */
/*public*/ /*static final*/ QString JSON::ICON_NAME = "iconName"; // NOI18N
/**
 * {@value #LENGTH}
 */
/*public*/ /*static final*/ QString JSON::LENGTH = "length"; // NOI18N
/**
 * {@value #WEIGHT}
 */
/*public*/ /*static final*/ QString JSON::WEIGHT = "weight"; // NOI18N
/**
 * {@value #LEAD_ENGINE}
 */
/*public*/ /*static final*/ QString JSON::LEAD_ENGINE = "leadEngine"; // NOI18N
/**
 * {@value #CABOOSE}
 */
/*public*/ /*static final*/ QString JSON::CABOOSE = "caboose"; // NOI18N
/**
 * {@value #TERMINATE}
 */
/*public*/ /*static final*/ QString JSON::TERMINATE = "terminate"; // NOI18N
/**
 * {@value #TRACK}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::TRACK = "track";
/**
 * {@value #DATE}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::DATE = "date";

/* JSON panel tokens */
/**
 * {@value #CONTROL_PANEL}
 */
/*public*/ /*static final*/ QString JSON::CONTROL_PANEL = "Control Panel"; // NOI18N
/**
 * {@value #LAYOUT_PANEL}
 */
/*public*/ /*static final*/ QString JSON::LAYOUT_PANEL = "Layout"; // NOI18N
/**
 * {@value #PANEL_PANEL}
 */
/*public*/ /*static final*/ QString JSON::PANEL_PANEL = "Panel"; // NOI18N
/**
 * {@value #URL}
 */
/*public*/ /*static final*/ QString JSON::URL = "URL"; // NOI18N
/**
 * {@value #FORMAT}
 */
/*public*/ /*static final*/ QString JSON::FORMAT = "format"; // NOI18N
/**
 * {@value #JSON}
 */
/*public*/ /*static final*/ QString JSON::_JSON = "json"; // NOI18N
/**
 * {@value #XML}
 */
/*public*/ /*static final*/ QString JSON::XML = "xml"; // NOI18N

/* JSON programmer tokens */
/**
 * {@value #MODE}
 */
/*public*/ /*static final*/ QString JSON::MODE = "mode"; // NOI18N
/**
 * {@value #NODE_CV}
 */
/*public*/ /*static final*/ QString JSON::NODE_CV = "CV"; // NOI18N
/**
 * {@value #OP}
 */
/*public*/ /*static final*/ QString JSON::OP = "mode"; // NOI18N
/**
 * {@value #READ}
 */
/*public*/ /*static final*/ QString JSON::READ = "read"; // NOI18N
/**
 * {@value #WRITE}
 */
/*public*/ /*static final*/ QString JSON::WRITE = "write"; // NOI18N

/* JSON reporter tokens */
/**
 * {@value #REPORT}
 */
/*public*/ /*static final*/ QString JSON::REPORT = "report"; // NOI18N
/**
 * {@value #LAST_REPORT}
 */
/*public*/ /*static final*/ QString JSON::LAST_REPORT = "lastReport"; // NOI18N

/* JSON roster and car/engine (operations) tokens */
/**
 * {@value #COLOR}
 */
/*public*/ /*static final*/ QString JSON::COLOR = "color"; // NOI18N
/**
 * {@value #LOAD}
 */
/*public*/ /*static final*/ QString JSON::LOAD = "load"; // NOI18N
/**
 * {@value #MODEL}
 */
/*public*/ /*static final*/ QString JSON::MODEL = "model"; // NOI18N
/**
 * {@value #ROAD}
 */
/*public*/ /*static final*/ QString JSON::ROAD = "road"; // NOI18N
/**
 * {@value #NUMBER}
 */
/*public*/ /*static final*/ QString JSON::NUMBER = "number"; // NOI18N
/**
 * {@value #DESTINATION}
 */
/*public*/ /*static final*/ QString JSON::DESTINATION = "destination"; // NOI18N
/**
 * {@value #DESTINATION_TRACK}
 */
/*public*/ /*static final*/ QString JSON::DESTINATION_TRACK = "dest&track"; // NOI18N
/**
 * {@value #LOCATION_TRACK}
 */
/*public*/ /*static final*/ QString JSON::LOCATION_TRACK = "locationTrack"; // NOI18N
/**
 * {@value #IS_LONG_ADDRESS}
 */
/*public*/ /*static final*/ QString JSON::IS_LONG_ADDRESS = "isLongAddress"; // NOI18N
/**
 * {@value #MFG}
 */
/*public*/ /*static final*/ QString JSON::MFG = "mfg"; // NOI18N
/**
 * {@value #DECODER_MODEL}
 */
/*public*/ /*static final*/ QString JSON::DECODER_MODEL = "decoderModel"; // NOI18N
/**
 * {@value #DECODER_FAMILY}
 */
/*public*/ /*static final*/ QString JSON::DECODER_FAMILY = "decoderFamily"; // NOI18N
/**
 * {@value #MAX_SPD_PCT}
 */
/*public*/ /*static final*/ QString JSON::MAX_SPD_PCT = "maxSpeedPct"; // NOI18N
/**
 * {@value #FUNCTION_KEYS}
 */
/*public*/ /*static final*/ QString JSON::FUNCTION_KEYS = "functionKeys"; // NOI18N
/**
 * {@value #IMAGE}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::IMAGE = "image"; // NOI18N
/**
 * {@value #ICON}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::ICON = "icon"; // NOI18N
/**
 * {@value #SELECTED_ICON}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::SELECTED_ICON = "selectedIcon"; // NOI18N
/**
 * {@value #LABEL}
 */
/*public*/ /*static final*/ QString JSON::LABEL = "label"; // NOI18N
/**
 * {@value #LOCKABLE}
 */
/*public*/ /*static final*/ QString JSON::LOCKABLE = "lockable"; // NOI18N
/**
 * {@value #GROUP}
 */
/*public*/ /*static final*/ QString JSON::GROUP = "group"; // NOI18N
/**
 * {@value #OWNER}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::OWNER = "owner"; // NOI18N
/**
 * {@value #SHUNTING_FUNCTION}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::SHUNTING_FUNCTION = "shuntingFunction"; // NOI18N

/* JSON route (operations) tokens */
/**
 * {@value #DIRECTION}
 */
/*public*/ /*static final*/ QString JSON::DIRECTION = "trainDirection"; // NOI18N
/**
 * {@value #SEQUENCE}
 */
/*public*/ /*static final*/ QString JSON::SEQUENCE = "sequenceId"; // NOI18N
/**
 * {@value #ARRIVAL_TIME}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::ARRIVAL_TIME = "arrivalTime"; // NOI18N
/**
 * {@value #EXPECTED_ARRIVAL}
 */
/*public*/ /*static final*/ QString JSON::EXPECTED_ARRIVAL = "expectedArrivalTime"; // NOI18N
/**
 * {@value #EXPECTED_DEPARTURE}
 */
/*public*/ /*static final*/ QString JSON::EXPECTED_DEPARTURE = "expectedDepartureTime"; // NOI18N
/**
 * {@value #DEPARTURE_TIME}
 */
/*public*/ /*static final*/ QString JSON::DEPARTURE_TIME = "departureTime"; // NOI18N
/**
 * {@value #DEPARTURE_LOCATION}
 */
/*public*/ /*static final*/ QString JSON::DEPARTURE_LOCATION = "trainDepartsName"; // NOI18N
/**
 * {@value #TERMINATES_LOCATION}
 */
/*public*/ /*static final*/ QString JSON::TERMINATES_LOCATION = "trainTerminatesName"; // NOI18N
/**
 * {@value #DESCRIPTION}
 */
/*public*/ /*static final*/ QString JSON::DESCRIPTION = "description"; // NOI18N
/**
 * {@value #ROUTE_ID}
 */
/*public*/ /*static final*/ QString JSON::ROUTE_ID = "routeId"; // NOI18N
/**
 * {@value #HAZARDOUS}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::HAZARDOUS = "hazardous"; // NOI18N
/**
 * {@value #KERNEL}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::KERNEL = "kernel"; // NOI18N
/**
 * {@value #FINAL_DESTINATION}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::FINAL_DESTINATION = "/*final*/Destination"; // NOI18N
/**
 * {@value #REMOVE_COMMENT}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::REMOVE_COMMENT = "removeComment"; // NOI18N
/**
 * {@value #ADD_COMMENT}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::ADD_COMMENT = "addComment"; // NOI18N
/**
 * {@value #IS_LOCAL}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::IS_LOCAL = "isLocal";
/**
 * {@value #ADD_HELPERS}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::ADD_HELPERS = "addHelpers";
/**
 * {@value #CHANGE_CABOOSE}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::CHANGE_CABOOSE = "changeCaboose";
/**
 * {@value #CHANGE_ENGINES}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::CHANGE_ENGINES = "changeEngines";
/**
 * {@value #REMOVE_HELPERS}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::REMOVE_HELPERS = "removeHelpers";
/**
 * {@value #OPTIONS}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::OPTIONS = "options";
/**
 * {@value #ADD}
 *
 * As an attribute of a {@link #ROSTER}, this is an entry that has been
 * added to the roster.
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::ADD = "add";
/**
 * {@value #REMOVE}
 *
 * In operations, this indicates the dropping or setting out of a car or
 * engine.
 *
 * As an attribute of a {@link #ROSTER}, this is an entry that has been
 * removed from the roster.
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::REMOVE = "remove";
/**
 * {@value #ADD_AND_REMOVE}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::ADD_AND_REMOVE = "addAndRemove";
/**
 * {@value #TOTAL}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::TOTAL = "total";
/**
 * {@value #LOADS}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::LOADS = "loads";
/**
 * {@value #EMPTIES}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::EMPTIES = "empties";
/**
 * {@value #RETURN_WHEN_EMPTY}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::RETURN_WHEN_EMPTY = "returnWhenEmpty";
/**
 * {@value #UTILITY}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::UTILITY = "utility";

/* JSON signalling tokens */
/**
 * {@value #APPEARANCE}
 */
/*public*/ /*static final*/ QString JSON::APPEARANCE = "appearance"; // NOI18N
/**
 * {@value #APPEARANCE_NAME}
 */
/*public*/ /*static final*/ QString JSON::APPEARANCE_NAME = "appearanceName"; // NOI18N
/**
 * {@value #ASPECT}
 */
/*public*/ /*static final*/ QString JSON::ASPECT = "aspect"; // NOI18N
/**
 * {@value #ASPECT_DARK}
 */
/*public*/ /*static final*/ QString JSON::ASPECT_DARK = "Dark"; // NOI18N
/**
 * {@value #ASPECT_HELD}
 */
/*public*/ /*static final*/ QString JSON::ASPECT_HELD = "Held"; // NOI18N
/**
 * {@value #ASPECT_UNKNOWN}
 */
/*public*/ /*static final*/ QString JSON::ASPECT_UNKNOWN = "Unknown"; // NOI18N
/**
 * {@value #TOKEN_HELD}
 */
/*public*/ /*static final*/ QString JSON::TOKEN_HELD = "held"; // NOI18N
/**
 * {@value #LIT}
 */
/*public*/ /*static final*/ QString JSON::LIT = "lit"; // NOI18N

/* JSON throttle tokens */
/**
 * {@value #ADDRESS}
 */
/*public*/ /*static final*/ QString JSON::ADDRESS = "address"; // NOI18N
/**
 * {@value #FORWARD}
 */
/*public*/ /*static final*/ QString JSON::FORWARD = "forward"; // NOI18N
/**
 * {@value #RELEASE}
 */
/*public*/ /*static final*/ QString JSON::RELEASE = "release"; // NOI18N
/**
 * {@value #ESTOP}
 */
/*public*/ /*static final*/ QString JSON::ESTOP = "eStop"; // NOI18N
/**
 * {@value #IDLE}
 */
/*public*/ /*static final*/ QString JSON::IDLE = "idle"; // NOI18N
/**
 * {@value #SPEED}
 */
/*public*/ /*static final*/ QString JSON::SPEED = "speed"; // NOI18N
/**
 * {@value #SPEED_STEPS}
 */
/*public*/ /*static final*/ QString JSON::SPEED_STEPS = "speedSteps"; // NOI18N
/**
 * Prefix for the throttle function keys (F0-F28).
 * <p>
 * {@value #F}
 */
/*public*/ /*static final*/ QString JSON::F = "F"; // NOI18N
/**
 * Used by a {@link jmri.jmris.json.JsonThrottle} to notify clients of the
 * number of clients controlling the same throttle.
 * <p>
 * {@value #CLIENTS}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::CLIENTS = "clients"; // NOI18N

/* JSON Sensor and Turnout Tokens */
/**
 * {@value #INVERTED}
 */
/*public*/ /*static final*/ QString JSON::INVERTED = "inverted"; // NOI18N

/* JSON value types */
/**
 * {@value #NULL}
 */
/*public*/ /*static final*/ QString JSON::_NULL = "null"; // NOI18N
/**
 * {@value #INTEGER}
 */
/*public*/ /*static final*/ QString JSON::INTEGER = "int"; // NOI18N

/* JSON network services tokens */
/**
 * {@value #PORT}
 */
/*public*/ /*static final*/ QString JSON::PORT = "port"; // NOI18N

/* JSON consist tokens */
/**
 * {@value #POSITION}
 */
/*public*/ /*static final*/ QString JSON::POSITION = "position"; // NOI18N
/**
 * {@value #SIZE_LIMIT}
 */
/*public*/ /*static final*/ QString JSON::SIZE_LIMIT = "sizeLimit"; // NOI18N

/* Time constants */
/**
 * {@value #RATE}
 */
/*public*/ /*static final*/ QString JSON::RATE = "rate"; // NOI18N

/*
 * JSON State (an unsigned integer)
 */

/* Common state */
///**
// * {@value #UNKNOWN}
// * <p>
// * Note that this value deliberately differs from
// * {@link jmri.NamedBean#UNKNOWN}.
// */
///*public*/ /*static*/ /*final*/ int JSON::UNKNOWN = 0x00;

///* Light and PowerManager state */
///**
// * {@value #ON}
// */
///*public*/ /*static*/ /*final*/ int JSON::ON = 0x02;
///**
// * {@value #OFF}
// */
///*public*/ /*static*/ /*final*/ int JSON::OFF = 0x04;

///* NamedBean state */
///**
// * {@value #INCONSISTENT}
// */
///*public*/ /*static*/ /*final*/ int JSON::INCONSISTENT = 0x08;

/* Route state */
/**
 * {@value #TOGGLE}
 */
/*public*/ /*static*/ /*final*/ int JSON::TOGGLE = 0x08;

/* Sensor state */
/**
 * {@value #ACTIVE}
 */
/*public*/ /*static*/ /*final*/ int JSON::ACTIVE = 0x02;
/**
 * {@value #INACTIVE}
 */
/*public*/ /*static*/ /*final*/ int JSON::INACTIVE = 0x04;

/* SignalHead state */
/**
 * {@value #STATE_DARK}
 */
/*public*/ /*static*/ /*final*/ int JSON::STATE_DARK = 0x00;
/**
 * {@value #RED}
 */
/*public*/ /*static*/ /*final*/ int JSON::RED = 0x01;
/**
 * {@value #FLASHRED}
 */
/*public*/ /*static*/ /*final*/ int JSON::FLASHRED = 0x02;
/**
 * {@value #YELLOW}
 */
/*public*/ /*static*/ /*final*/ int JSON::YELLOW = 0x04;
/**
 * {@value #FLASHYELLOW}
 */
/*public*/ /*static*/ /*final*/ int JSON::FLASHYELLOW = 0x08;
/**
 * {@value #GREEN}
 */
/*public*/ /*static*/ /*final*/ int JSON::GREEN = 0x10;
/**
 * {@value #FLASHGREEN}
 */
/*public*/ /*static*/ /*final*/ int JSON::FLASHGREEN = 0x20;
/**
 * {@value #LUNAR}
 */
/*public*/ /*static*/ /*final*/ int JSON::LUNAR = 0x40;
/**
 * {@value #FLASHLUNAR}
 */
/*public*/ /*static*/ /*final*/ int JSON::FLASHLUNAR = 0x80;
/**
 * {@value #STATE_HELD}
 */
/*public*/ /*static*/ /*final*/ int JSON::STATE_HELD = 0x100;

/* Turnout state */
/**
 * {@value #CLOSED}
 */
/*public*/ /*static*/ /*final*/ int JSON::CLOSED = 0x02;
/**
 * {@value #THROWN}
 */
/*public*/ /*static*/ /*final*/ int JSON::THROWN = 0x04;
/**
 * {@value #UNIT}
 *
 * @since 1.1
 */
/*public*/ /*static final*/ QString JSON::UNIT = "unit"; // NOI18N

/* JMRI JSON Client Autoconfiguration support */
/**
 * {@value #PREFIX}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::PREFIX = "prefix"; // NOI18N
/**
 * {@value #SYSTEM_CONNECTION}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::SYSTEM_CONNECTION = "systemConnection"; // NOI18N
/**
 * {@value #SYSTEM_CONNECTIONS}
 *
 * @since 2.0
 */
/*public*/ /*static final*/ QString JSON::SYSTEM_CONNECTIONS = "systemConnections"; // NOI18N

/* ZeroConf support */
/**
 * {@value #ZEROCONF_SERVICE_TYPE} Not used within the protocol, but used to
 * support discovery of servers supporting the protocol.
 */
/*public*/ /*static final*/ QString JSON::ZEROCONF_SERVICE_TYPE = "_jmri-json._tcp.local."; // NOI18N

/* prevent the constructor from being documented */
/*private*/ JSON::JSON() {
}
