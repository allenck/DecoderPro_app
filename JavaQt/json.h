#ifndef JSON_H
#define JSON_H

#include <QString>

class JSON
{
 JSON();

public:
 /*public*/ static /*final*/ QString JSON_PROTOCOL_VERSION;//= "3.0"; // NOI18N

 /* JSON structure */
 /**
  * {@value #TYPE}
  */
 /*public*/ static /*final*/ QString TYPE;//= "type"; // NOI18N
 /**
  * {@value #LIST}
  */
 /*public*/ static /*final*/ QString LIST;//= "list"; // NOI18N
 /**
  * {@value #DATA}
  */
 /*public*/ static /*final*/ QString DATA;//= "data"; // NOI18N
 /**
  * {@value #PING}
  */
 /*public*/ static /*final*/ QString PING;//= "ping"; // NOI18N
 /**
  * {@value #PONG}
  */
 /*public*/ static /*final*/ QString PONG;//= "pong"; // NOI18N
 /**
  * {@value #GOODBYE}
  */
 /*public*/ static /*final*/ QString GOODBYE;//= "goodbye"; // NOI18N
 /**
  * {@value #NAME}
  */
 /*public*/ static /*final*/ QString NAME;//= "name"; // NOI18N

 /* JSON methods */
 /**
  * {@value #METHOD}
  */
 /*public*/ static /*final*/ QString METHOD;//= "method"; // NOI18N
 /**
  * {@value #DELETE}
  */
 /*public*/ static /*final*/ QString DELETE;//= "delete"; // NOI18N
 /**
  * {@value #GET}
  */
 /*public*/ static /*final*/ QString GET;//= "get"; // NOI18N
 /**
  * {@value #POST}
  */
 /*public*/ static /*final*/ QString POST;//= "post"; // NOI18N
 /**
  * {@value #PUT}
  */
 /*public*/ static /*final*/ QString PUT;//= "put"; // NOI18N

 /* JSON common tokens */
 /**
  * {@value #COMMENT}
  */
 /*public*/ static /*final*/ QString COMMENT;//= "comment"; // NOI18N
 /**
  * {@value #USERNAME}
  */
 /*public*/ static /*final*/ QString USERNAME;//= "userName"; // NOI18N
 /**
  * {@value #STATE}
  */
 /*public*/ static /*final*/ QString STATE;//= "state"; // NOI18N
 /**
  * {@value #VALUE}
  */
 /*public*/ static /*final*/ QString VALUE;//= "value"; // NOI18N
 /**
  * {@value #ID}
  */
 /*public*/ static /*final*/ QString ID;//= "id"; // NOI18N
 /**
  * {@value #STATUS}
  */
 /*public*/ static /*final*/ QString STATUS;//= "status"; // NOI18N
 /**
  * Numeric status value
  *
  * {@value #STATUS_CODE}
  */
 /*public*/ static /*final*/ QString STATUS_CODE;//= "statusCode"; // NOI18N
 /**
   * {@value #PROPERTIES}
   */
  /*public*/ static /*final*/ QString PROPERTIES;// = "properties"; // NOI18N

 /* JSON error */
 /**
  * {@value #ERROR}
  */
 /*public*/ static /*final*/ QString ERROR;//= "error"; // NOI18N
 /**
  * {@value #CODE}
  */
 /*public*/ static /*final*/ QString CODE;//= "code"; // NOI18N
 /**
  * {@value #MESSAGE}
  */
 /*public*/ static /*final*/ QString MESSAGE;//= "message"; // NOI18N

 /* JSON hello and metadata */
 /**
  * {@value #HELLO}
  */
 /*public*/ static /*final*/ QString HELLO;//= "hello"; // NOI18N
 /**
  * {@value #JMRI}
  */
 /*public*/ static /*final*/ QString JMRI;//= "JMRI"; // NOI18N
 /**
  * {@value #HEARTBEAT}
  */
 /*public*/ static /*final*/ QString HEARTBEAT;//= "heartbeat"; // NOI18N
 /**
  * {@value #RAILROAD}
  */
 /*public*/ static /*final*/ QString RAILROAD;//= "railroad"; // NOI18N
 /**
  * {@value #NODE}
  * <p>
  * @since 1.1
  */
 /*public*/ static /*final*/ QString NODE;//= "node"; // NOI18N
 /**
  * {@value #ACTIVE_PROFILE}
  * <p>
  * @since 3.0
  */
 /*public*/ static /*final*/ QString ACTIVE_PROFILE;//= "activeProfile"; // NOI18N
 /**
  * {@value #FORMER_NODES}
  * <p>
  * @since 1.1
  */
 /*public*/ static /*final*/ QString FORMER_NODES;//= "formerNodes"; // NOI18N
 /**
  * {@value #LOCALE}
  * <p>
  * @since 1.1
  */
 /*public*/ static /*final*/ QString LOCALE;//= "locale"; // NOI18N

 /* JSON list types */
 /**
  * {@value #CARS}
  */
 /*public*/ static /*final*/ QString CARS;//= "cars"; // NOI18N
 /**
  * {@value #CONSISTS}
  */
 /*public*/ static /*final*/ QString CONSISTS;//= "consists"; // NOI18N
 /**
  * {@value #ENGINES}
  */
 /*public*/ static /*final*/ QString ENGINES;//= "engines"; // NOI18N
 /**
  * {@value #LIGHTS}
  */
 /*public*/ static /*final*/ QString LIGHTS;//= "lights"; // NOI18N
 /**
  * {@value #LOCATIONS}
  */
 /*public*/ static /*final*/ QString LOCATIONS;//= "locations"; // NOI18N
 /**
  * {@value #MEMORIES}
  */
 /*public*/ static /*final*/ QString MEMORIES;//= "memories"; // NOI18N
 /**
  * {@value #METADATA}
  */
 /*public*/ static /*final*/ QString METADATA;//= "metadata"; // NOI18N
 /**
  * {@value #PANELS}
  */
 /*public*/ static /*final*/ QString PANELS;//= "panels"; // NOI18N
 /**
  * {@value #REPORTERS}
  */
 /*public*/ static /*final*/ QString REPORTERS;//= "reporters"; // NOI18N
 /**
  * {@value #ROSTER}
  */
 /*public*/ static /*final*/ QString ROSTER;//= "roster"; // NOI18N
 /**
  * {@value #ROSTER_GROUP}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString ROSTER_GROUP;//= "rosterGroup"; // NOI18N
 /**
  * {@value #ROSTER_GROUPS}
  */
 /*public*/ static /*final*/ QString ROSTER_GROUPS;//= "rosterGroups"; // NOI18N
 /**
  * {@value #ROUTES}
  */
 /*public*/ static /*final*/ QString ROUTES;//= "routes"; // NOI18N
 /**
  * {@value #SENSORS}
  */
 /*public*/ static /*final*/ QString SENSORS;//= "sensors"; // NOI18N
 /**
  * {@value #SIGNAL_HEADS}
  */
 /*public*/ static /*final*/ QString SIGNAL_HEADS;//= "signalHeads"; // NOI18N
 /**
  * {@value #SIGNAL_MASTS}
  */
 /*public*/ static /*final*/ QString SIGNAL_MASTS;//= "signalMasts"; // NOI18N
 /**
  * {@value #TRAINS}
  */
 /*public*/ static /*final*/ QString TRAINS;//= "trains"; // NOI18N
 /**
  * {@value #TURNOUTS}
  */
 /*public*/ static /*final*/ QString TURNOUTS;//= "turnouts"; // NOI18N
 /**
  * {@value #NETWORK_SERVICES}
  */
 /*public*/ static /*final*/ QString NETWORK_SERVICES;//= "networkServices"; // NOI18N

 /* JSON data types */
 /**
  * {@value #CAR}
  */
 /*public*/ static /*final*/ QString CAR;//= "car"; // NOI18N
 /**
  * {@value #CONSIST}
  */
 /*public*/ static /*final*/ QString CONSIST;//= "consist"; // NOI18N
 /**
  * {@value #ENGINE}
  */
 /*public*/ static /*final*/ QString ENGINE;//= "engine"; // NOI18N
 /**
  * {@value #LIGHT}
  */
 /*public*/ static /*final*/ QString LIGHT;//= "light"; // NOI18N
 /**
  * {@value #LOCATION}
  */
 /*public*/ static /*final*/ QString LOCATION;//= "location"; // NOI18N
 /**
  * {@value #LOCATION_ID}
  */
 /*public*/ static /*final*/ QString LOCATION_ID;//= "locationId"; // NOI18N
 /**
  * {@value #MEMORY}
  */
 /*public*/ static /*final*/ QString MEMORY;//= "memory"; // NOI18N
 /**
  * {@value #NETWORK_SERVICE}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString NETWORK_SERVICE;//= "networkService"; // NOI18N
 /**
  * {@value #PANEL}
  */
 /*public*/ static /*final*/ QString PANEL;//= "panel"; // NOI18N
 /**
  * {@value #POWER}
  */
 /*public*/ static /*final*/ QString POWER;//= "power"; // NOI18N
 /**
  * {@value #PROGRAMMER}
  */
 /*public*/ static /*final*/ QString PROGRAMMER;//= "programmer"; // NOI18N
 /**
  * {@value #ROUTE}
  */
 /*public*/ static /*final*/ QString ROUTE;//= "route"; // NOI18N
 /**
  * {@value #SENSOR}
  */
 /*public*/ static /*final*/ QString SENSOR;//= "sensor"; // NOI18N
 /**
  * {@value #SIGNAL_HEAD}
  */
 /*public*/ static /*final*/ QString SIGNAL_HEAD;//= "signalHead"; // NOI18N
 /**
  * {@value #SIGNAL_MAST}
  */
 /*public*/ static /*final*/ QString SIGNAL_MAST;//= "signalMast"; // NOI18N
 /**
  * {@value #REPORTER}
  */
 /*public*/ static /*final*/ QString REPORTER;//= "reporter"; // NOI18N
 /**
  * {@value #ROSTER_ENTRY}
  */
 /*public*/ static /*final*/ QString ROSTER_ENTRY;//= "rosterEntry"; // NOI18N
 /**
  * {@value #THROTTLE}
  */
 /*public*/ static /*final*/ QString THROTTLE;//= "throttle"; // NOI18N
 /**
  * {@value #TIME}
  */
 /*public*/ static /*final*/ QString TIME;//= "time"; // NOI18N
 /**
  * {@value #TRAIN}
  */
 /*public*/ static /*final*/ QString TRAIN;//= "train"; // NOI18N
 /**
  * {@value #TURNOUT}
  */
 /*public*/ static /*final*/ QString TURNOUT;//= "turnout"; // NOI18N

 /* JSON operations tokens */
 /**
  * {@value #ICON_NAME}
  */
 /*public*/ static /*final*/ QString ICON_NAME;//= "iconName"; // NOI18N
 /**
  * {@value #LENGTH}
  */
 /*public*/ static /*final*/ QString LENGTH;//= "length"; // NOI18N
 /**
  * {@value #WEIGHT}
  */
 /*public*/ static /*final*/ QString WEIGHT;//= "weight"; // NOI18N
 /**
  * {@value #LEAD_ENGINE}
  */
 /*public*/ static /*final*/ QString LEAD_ENGINE;//= "leadEngine"; // NOI18N
 /**
  * {@value #CABOOSE}
  */
 /*public*/ static /*final*/ QString CABOOSE;//= "caboose"; // NOI18N
 /**
  * {@value #TERMINATE}
  */
 /*public*/ static /*final*/ QString TERMINATE;//= "terminate"; // NOI18N
 /**
  * {@value #TRACK}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString TRACK;//= "track";
 /**
  * {@value #DATE}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString DATE;//= "date";

 /* JSON panel tokens */
 /**
  * {@value #CONTROL_PANEL}
  */
 /*public*/ static /*final*/ QString CONTROL_PANEL;//= "Control Panel"; // NOI18N
 /**
  * {@value #LAYOUT_PANEL}
  */
 /*public*/ static /*final*/ QString LAYOUT_PANEL;//= "Layout"; // NOI18N
 /**
  * {@value #PANEL_PANEL}
  */
 /*public*/ static /*final*/ QString PANEL_PANEL;//= "Panel"; // NOI18N
 /**
  * {@value #URL}
  */
 /*public*/ static /*final*/ QString URL;//= "URL"; // NOI18N
 /**
  * {@value #FORMAT}
  */
 /*public*/ static /*final*/ QString FORMAT;//= "format"; // NOI18N
 /**
  * {@value #JSON}
  */
 /*public*/ static /*final*/ QString _JSON;//= "json"; // NOI18N
 /**
  * {@value #XML}
  */
 /*public*/ static /*final*/ QString XML;//= "xml"; // NOI18N

 /* JSON programmer tokens */
 /**
  * {@value #MODE}
  */
 /*public*/ static /*final*/ QString MODE;//= "mode"; // NOI18N
 /**
  * {@value #NODE_CV}
  */
 /*public*/ static /*final*/ QString NODE_CV;//= "CV"; // NOI18N
 /**
  * {@value #OP}
  */
 /*public*/ static /*final*/ QString OP;//= "mode"; // NOI18N
 /**
  * {@value #READ}
  */
 /*public*/ static /*final*/ QString READ;//= "read"; // NOI18N
 /**
  * {@value #WRITE}
  */
 /*public*/ static /*final*/ QString WRITE;//= "write"; // NOI18N

 /* JSON reporter tokens */
 /**
  * {@value #REPORT}
  */
 /*public*/ static /*final*/ QString REPORT;//= "report"; // NOI18N
 /**
  * {@value #LAST_REPORT}
  */
 /*public*/ static /*final*/ QString LAST_REPORT;//= "lastReport"; // NOI18N

 /* JSON roster and car/engine (operations) tokens */
 /**
  * {@value #COLOR}
  */
 /*public*/ static /*final*/ QString COLOR;//= "color"; // NOI18N
 /**
  * {@value #LOAD}
  */
 /*public*/ static /*final*/ QString LOAD;//= "load"; // NOI18N
 /**
  * {@value #MODEL}
  */
 /*public*/ static /*final*/ QString MODEL;//= "model"; // NOI18N
 /**
  * {@value #ROAD}
  */
 /*public*/ static /*final*/ QString ROAD;//= "road"; // NOI18N
 /**
  * {@value #NUMBER}
  */
 /*public*/ static /*final*/ QString NUMBER;//= "number"; // NOI18N
 /**
  * {@value #DESTINATION}
  */
 /*public*/ static /*final*/ QString DESTINATION;//= "destination"; // NOI18N
 /**
  * {@value #DESTINATION_TRACK}
  */
 /*public*/ static /*final*/ QString DESTINATION_TRACK;//= "dest&track"; // NOI18N
 /**
  * {@value #LOCATION_TRACK}
  */
 /*public*/ static /*final*/ QString LOCATION_TRACK;//= "locationTrack"; // NOI18N
 /**
  * {@value #IS_LONG_ADDRESS}
  */
 /*public*/ static /*final*/ QString IS_LONG_ADDRESS;//= "isLongAddress"; // NOI18N
 /**
  * {@value #MFG}
  */
 /*public*/ static /*final*/ QString MFG;//= "mfg"; // NOI18N
 /**
  * {@value #DECODER_MODEL}
  */
 /*public*/ static /*final*/ QString DECODER_MODEL;//= "decoderModel"; // NOI18N
 /**
  * {@value #DECODER_FAMILY}
  */
 /*public*/ static /*final*/ QString DECODER_FAMILY;//= "decoderFamily"; // NOI18N
 /**
  * {@value #MAX_SPD_PCT}
  */
 /*public*/ static /*final*/ QString MAX_SPD_PCT;//= "maxSpeedPct"; // NOI18N
 /**
  * {@value #FUNCTION_KEYS}
  */
 /*public*/ static /*final*/ QString FUNCTION_KEYS;//= "functionKeys"; // NOI18N
 /**
  * {@value #IMAGE}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString IMAGE;//= "image"; // NOI18N
 /**
  * {@value #ICON}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString ICON;//= "icon"; // NOI18N
 /**
  * {@value #SELECTED_ICON}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString SELECTED_ICON;//= "selectedIcon"; // NOI18N
 /**
  * {@value #LABEL}
  */
 /*public*/ static /*final*/ QString LABEL;//= "label"; // NOI18N
 /**
  * {@value #LOCKABLE}
  */
 /*public*/ static /*final*/ QString LOCKABLE;//= "lockable"; // NOI18N
 /**
  * {@value #GROUP}
  */
 /*public*/ static /*final*/ QString GROUP;//= "group"; // NOI18N
 /**
  * {@value #OWNER}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString OWNER;//= "owner"; // NOI18N
 /**
  * {@value #SHUNTING_FUNCTION}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString SHUNTING_FUNCTION;//= "shuntingFunction"; // NOI18N

 /* JSON route (operations) tokens */
 /**
  * {@value #DIRECTION}
  */
 /*public*/ static /*final*/ QString DIRECTION;//= "trainDirection"; // NOI18N
 /**
  * {@value #SEQUENCE}
  */
 /*public*/ static /*final*/ QString SEQUENCE;//= "sequenceId"; // NOI18N
 /**
  * {@value #ARRIVAL_TIME}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString ARRIVAL_TIME;//= "arrivalTime"; // NOI18N
 /**
  * {@value #EXPECTED_ARRIVAL}
  */
 /*public*/ static /*final*/ QString EXPECTED_ARRIVAL;//= "expectedArrivalTime"; // NOI18N
 /**
  * {@value #EXPECTED_DEPARTURE}
  */
 /*public*/ static /*final*/ QString EXPECTED_DEPARTURE;//= "expectedDepartureTime"; // NOI18N
 /**
  * {@value #DEPARTURE_TIME}
  */
 /*public*/ static /*final*/ QString DEPARTURE_TIME;//= "departureTime"; // NOI18N
 /**
  * {@value #DEPARTURE_LOCATION}
  */
 /*public*/ static /*final*/ QString DEPARTURE_LOCATION;//= "trainDepartsName"; // NOI18N
 /**
  * {@value #TERMINATES_LOCATION}
  */
 /*public*/ static /*final*/ QString TERMINATES_LOCATION;//= "trainTerminatesName"; // NOI18N
 /**
  * {@value #DESCRIPTION}
  */
 /*public*/ static /*final*/ QString DESCRIPTION;//= "description"; // NOI18N
 /**
  * {@value #ROUTE_ID}
  */
 /*public*/ static /*final*/ QString ROUTE_ID;//= "routeId"; // NOI18N
 /**
  * {@value #HAZARDOUS}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString HAZARDOUS;//= "hazardous"; // NOI18N
 /**
  * {@value #KERNEL}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString KERNEL;//= "kernel"; // NOI18N
 /**
  * {@value #FINAL_DESTINATION}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString FINAL_DESTINATION;//= "/*final*/Destination"; // NOI18N
 /**
  * {@value #REMOVE_COMMENT}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString REMOVE_COMMENT;//= "removeComment"; // NOI18N
 /**
  * {@value #ADD_COMMENT}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString ADD_COMMENT;//= "addComment"; // NOI18N
 /**
  * {@value #IS_LOCAL}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString IS_LOCAL;//= "isLocal";
 /**
  * {@value #ADD_HELPERS}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString ADD_HELPERS;//= "addHelpers";
 /**
  * {@value #CHANGE_CABOOSE}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString CHANGE_CABOOSE;//= "changeCaboose";
 /**
  * {@value #CHANGE_ENGINES}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString CHANGE_ENGINES;//= "changeEngines";
 /**
  * {@value #REMOVE_HELPERS}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString REMOVE_HELPERS;//= "removeHelpers";
 /**
  * {@value #OPTIONS}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString OPTIONS;//= "options";
 /**
  * {@value #ADD}
  *
  * As an attribute of a {@link #ROSTER}, this is an entry that has been
  * added to the roster.
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString ADD;//= "add";
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
 /*public*/ static /*final*/ QString REMOVE;//= "remove";
 /**
  * {@value #ADD_AND_REMOVE}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString ADD_AND_REMOVE;//= "addAndRemove";
 /**
  * {@value #TOTAL}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString TOTAL;//= "total";
 /**
  * {@value #LOADS}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString LOADS;//= "loads";
 /**
  * {@value #EMPTIES}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString EMPTIES;//= "empties";
 /**
  * {@value #RETURN_WHEN_EMPTY}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString RETURN_WHEN_EMPTY;//= "returnWhenEmpty";
 /**
  * {@value #UTILITY}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString UTILITY;//= "utility";

 /* JSON signalling tokens */
 /**
  * {@value #APPEARANCE}
  */
 /*public*/ static /*final*/ QString APPEARANCE;//= "appearance"; // NOI18N
 /**
  * {@value #APPEARANCE_NAME}
  */
 /*public*/ static /*final*/ QString APPEARANCE_NAME;//= "appearanceName"; // NOI18N
 /**
  * {@value #ASPECT}
  */
 /*public*/ static /*final*/ QString ASPECT;//= "aspect"; // NOI18N
 /**
  * {@value #ASPECT_DARK}
  */
 /*public*/ static /*final*/ QString ASPECT_DARK;//= "Dark"; // NOI18N
 /**
  * {@value #ASPECT_HELD}
  */
 /*public*/ static /*final*/ QString ASPECT_HELD;//= "Held"; // NOI18N
 /**
  * {@value #ASPECT_UNKNOWN}
  */
 /*public*/ static /*final*/ QString ASPECT_UNKNOWN;//= "Unknown"; // NOI18N
 /**
  * {@value #TOKEN_HELD}
  */
 /*public*/ static /*final*/ QString TOKEN_HELD;//= "held"; // NOI18N
 /**
  * {@value #LIT}
  */
 /*public*/ static /*final*/ QString LIT;//= "lit"; // NOI18N

 /* JSON throttle tokens */
 /**
  * {@value #ADDRESS}
  */
 /*public*/ static /*final*/ QString ADDRESS;//= "address"; // NOI18N
 /**
  * {@value #FORWARD}
  */
 /*public*/ static /*final*/ QString FORWARD;//= "forward"; // NOI18N
 /**
  * {@value #RELEASE}
  */
 /*public*/ static /*final*/ QString RELEASE;//= "release"; // NOI18N
 /**
  * {@value #ESTOP}
  */
 /*public*/ static /*final*/ QString ESTOP;//= "eStop"; // NOI18N
 /**
  * {@value #IDLE}
  */
 /*public*/ static /*final*/ QString IDLE;//= "idle"; // NOI18N
 /**
  * {@value #SPEED}
  */
 /*public*/ static /*final*/ QString SPEED;//= "speed"; // NOI18N
 /**
  * {@value #SPEED_STEPS}
  */
 /*public*/ static /*final*/ QString SPEED_STEPS;//= "speedSteps"; // NOI18N
 /**
  * Prefix for the throttle function keys (F0-F28).
  * <p>
  * {@value #F}
  */
 /*public*/ static /*final*/ QString F;//= "F"; // NOI18N
 /**
  * Used by a {@link jmri.jmris.json.JsonThrottle} to notify clients of the
  * number of clients controlling the same throttle.
  * <p>
  * {@value #CLIENTS}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString CLIENTS;//= "clients"; // NOI18N

 /* JSON Sensor and Turnout Tokens */
 /**
  * {@value #INVERTED}
  */
 /*public*/ static /*final*/ QString INVERTED;//= "inverted"; // NOI18N

 /* JSON value types */
 /**
  * {@value #NULL}
  */
 /*public*/ static /*final*/ QString _NULL;//= "null"; // NOI18N
 /**
  * {@value #INTEGER}
  */
 /*public*/ static /*final*/ QString INTEGER;//= "int"; // NOI18N

 /* JSON network services tokens */
 /**
  * {@value #PORT}
  */
 /*public*/ static /*final*/ QString PORT;//= "port"; // NOI18N

 /* JSON consist tokens */
 /**
  * {@value #POSITION}
  */
 /*public*/ static /*final*/ QString POSITION;//= "position"; // NOI18N
 /**
  * {@value #SIZE_LIMIT}
  */
 /*public*/ static /*final*/ QString SIZE_LIMIT;//= "sizeLimit"; // NOI18N

 /* Time constants */
 /**
  * {@value #RATE}
  */
 /*public*/ static /*final*/ QString RATE;//= "rate"; // NOI18N

 /*
  * JSON State (an unsigned integer)
  */

 /* Common state */
 /**
  * {@value #UNKNOWN}
  * <p>
  * Note that this value deliberately differs from
  * {@link jmri.NamedBean#UNKNOWN}.
  */
 enum TSTATES
 {
  UNKNOWN = 0x00,

 /* Light and PowerManager state */
 /**
  * {@value #ON}
  */
  ON = 0x02,
 /**
  * {@value #OFF}
  */
  OFF= 0x04,

 /* NamedBean state */
 /**
  * {@value #INCONSISTENT}
  */
  INCONSISTENT= 0x08
};
 /* Route state */
 /**
  * {@value #TOGGLE}
  */
 /*public*/ static /*final*/ int TOGGLE;//= 0x08;

 /* Sensor state */
 /**
  * {@value #ACTIVE}
  */
 /*public*/ static /*final*/ int ACTIVE;//= 0x02;
 /**
  * {@value #INACTIVE}
  */
 /*public*/ static /*final*/ int INACTIVE;//= 0x04;

 /* SignalHead state */
 /**
  * {@value #STATE_DARK}
  */
 /*public*/ static /*final*/ int STATE_DARK;//= 0x00;
 /**
  * {@value #RED}
  */
 /*public*/ static /*final*/ int RED;//= 0x01;
 /**
  * {@value #FLASHRED}
  */
 /*public*/ static /*final*/ int FLASHRED;//= 0x02;
 /**
  * {@value #YELLOW}
  */
 /*public*/ static /*final*/ int YELLOW;//= 0x04;
 /**
  * {@value #FLASHYELLOW}
  */
 /*public*/ static /*final*/ int FLASHYELLOW;//= 0x08;
 /**
  * {@value #GREEN}
  */
 /*public*/ static /*final*/ int GREEN;//= 0x10;
 /**
  * {@value #FLASHGREEN}
  */
 /*public*/ static /*final*/ int FLASHGREEN;//= 0x20;
 /**
  * {@value #LUNAR}
  */
 /*public*/ static /*final*/ int LUNAR;//= 0x40;
 /**
  * {@value #FLASHLUNAR}
  */
 /*public*/ static /*final*/ int FLASHLUNAR;//= 0x80;
 /**
  * {@value #STATE_HELD}
  */
 /*public*/ static /*final*/ int STATE_HELD;//= 0x100;

 /* Turnout state */
 /**
  * {@value #CLOSED}
  */
 /*public*/ static /*final*/ int CLOSED;//= 0x02;
 /**
  * {@value #THROWN}
  */
 /*public*/ static /*final*/ int THROWN;//= 0x04;
 /**
  * {@value #UNIT}
  *
  * @since 1.1
  */
 /*public*/ static /*final*/ QString UNIT;//= "unit"; // NOI18N

 /* JMRI JSON Client Autoconfiguration support */
 /**
  * {@value #PREFIX}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString PREFIX;//= "prefix"; // NOI18N
 /**
  * {@value #SYSTEM_CONNECTION}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString SYSTEM_CONNECTION;//= "systemConnection"; // NOI18N
 /**
  * {@value #SYSTEM_CONNECTIONS}
  *
  * @since 2.0
  */
 /*public*/ static /*final*/ QString SYSTEM_CONNECTIONS;//= "systemConnections"; // NOI18N

 /* ZeroConf support */
 /**
  * {@value #ZEROCONF_SERVICE_TYPE} Not used within the protocol, but used to
  * support discovery of servers supporting the protocol.
  */
 /*public*/ static /*final*/ QString ZEROCONF_SERVICE_TYPE;//= "_jmri-json._tcp.local."; // NOI18N
};

#endif // JSON_H
