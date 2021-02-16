#include "jsonutil.h"
#include "loggerfactory.h"
#include "trainmanager.h"
#include "location.h"
#include "locationmanager.h"
#include "json.h"
#include "../operations/route.h"
#include "routelocation.h"
#include "enginemanager.h"
#include "../operations/engine.h"
#include "car.h"
#include "carmanager.h"
#include "track.h"
#include "traincommon.h"

JsonUtil::JsonUtil(ObjectMapper mapper, QObject *parent) : QObject(parent)
{
 this->mapper = mapper;
}
/**
 * A set of static methods for converting certain objects to/from JSON
 * representations.
 *
 * All methods in this class will eventually be deprecated in favor of the
 * implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 *
 * @author Randall Wood
 * @deprecated since 4.5.6
 */
//@Deprecated
///*public*/ class JsonUtil {

/*private*/ /*static*/ /*final*/ Logger* JsonUtil::log = LoggerFactory::getLogger("JsonUtil");

/*static*/ /*public*/ QJsonObject JsonUtil::getCar(QLocale locale, QString id) {
    QJsonObject root = QJsonObject();//mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::CAR);
    root.insert(JSON::DATA, JsonUtil::getCar(Operations::CarManager::instance()->getById(id)));
    return root;
}
#if 0
static /*public*/ JsonNode getCars(Locale locale) {
    ArrayNode root = mapper.createArrayNode();
    for (RollingStock rs : CarManager.instance().getByIdList()) {
        root.add(JsonUtil.getCar(locale, rs->getId()));
    }
    return root;
}

/**
 * Delete the consist at the given address.
 *
 * @param locale  The locale to format exceptions in
 * @param address The address of the consist to delete.
 * @throws JsonException This exception has code 404 if the consist does not
 *                       exist.
 */
static /*public*/ void delConsist(Locale locale, DccLocoAddress address) throws JsonException {
    try {
        if (InstanceManager.getDefault(jmri.ConsistManager.class).getConsistList().contains(address)) {
            InstanceManager.getDefault(jmri.ConsistManager.class).delConsist(address);
        } else {
            throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", CONSIST, address.toString()));
        }
    } catch (NullPointerException ex) {
        throw new JsonException(503, Bundle.getMessage(locale, "ErrorNoConsistManager")); // NOI18N
    }
}

/**
 * Get the JSON representation of a consist.
 *
 * The JSON representation is an object with the following data attributes:
 * <ul>
 * <li>address - integer address</li>
 * <li>isLongAddress - boolean true if address is long, false if short</li>
 * <li>type - integer, see {@link jmri.Consist#getConsistType() }</li>
 * <li>id - string with consist Id</li>
 * <li>sizeLimit - the maximum number of locomotives the consist can
 * contain</li>
 * <li>engines - array listing every locomotive in the consist. Each entry
 * in the array contains the following attributes:
 * <ul>
 * <li>address - integer address</li>
 * <li>isLongAddress - boolean true if address is long, false if short</li>
 * <li>forward - boolean true if the locomotive running is forward in the
 * consists</li>
 * <li>position - integer locomotive's position in the consist</li>
 * </ul>
 * </ul>
 *
 * @param locale  The locale to throw exceptions in.
 * @param address The address of the consist to get.
 * @return The JSON representation of the consist.
 * @throws JsonException This exception has code 404 if the consist does not
 *                       exist.
 */
static /*public*/ JsonNode getConsist(Locale locale, DccLocoAddress address) throws JsonException {
    try {
        if (InstanceManager.getDefault(jmri.ConsistManager.class).getConsistList().contains(address)) {
            ObjectNode root = mapper.createObjectNode();
            root.put(TYPE, CONSIST);
            ObjectNode data = root.putObject(DATA);
            Consist consist = InstanceManager.getDefault(jmri.ConsistManager.class).getConsist(address);
            data.insert(JSON::ADDRESS, consist.getConsistAddress().getNumber());
            data.insert(JSON::IS_LONG_ADDRESS, consist.getConsistAddress().isLongAddress());
            data.insert(JSON::TYPE, consist.getConsistType());
            ArrayNode engines = data.putArray(ENGINES);
            for (DccLocoAddress l : consist.getConsistList()) {
                ObjectNode engine = mapper.createObjectNode();
                engine.put(ADDRESS, l.getNumber());
                engine.put(IS_LONG_ADDRESS, l.isLongAddress());
                engine.put(FORWARD, consist.getLocoDirection(l));
                engine.put(POSITION, consist.getPosition(l));
                engines.add(engine);
            }
            data.insert(JSON::ID, consist.getConsistID());
            data.insert(JSON::SIZE_LIMIT, consist.sizeLimit());
            return root;
        } else {
            throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", CONSIST, address.toString()));
        }
    } catch (NullPointerException ex) {
        throw new JsonException(503, Bundle.getMessage(locale, "ErrorNoConsistManager")); // NOI18N
    }
}

/**
 * Add a consist.
 *
 * Adds a consist, populating it with information from data.
 *
 * @param locale  The locale to throw exceptions in.
 * @param address The address of the new consist.
 * @param data    The JSON representation of the consist. See
 * {@link #getConsist(Locale, jmri.DccLocoAddress) } for the
 *                JSON structure.
 * @throws jmri.server.json.JsonException if no consist manager is available
 */
static /*public*/ void putConsist(Locale locale, DccLocoAddress address, JsonNode data) throws JsonException {
    try {
        if (!InstanceManager.getDefault(jmri.ConsistManager.class).getConsistList().contains(address)) {
            InstanceManager.getDefault(jmri.ConsistManager.class).getConsist(address);
            setConsist(locale, address, data);
        }
    } catch (NullPointerException ex) {
        throw new JsonException(503, Bundle.getMessage(locale, "ErrorNoConsistManager")); // NOI18N
    }
}

/**
 * Get a list of consists.
 *
 * @param locale The locale to throw exceptions in.
 * @return JSON array of consists as in the structure returned by
 * {@link #getConsist(Locale, jmri.DccLocoAddress) }
 * @throws jmri.server.json.JsonException if no ConsistManager is available
 */
static /*public*/ JsonNode getConsists(Locale locale) throws JsonException {
    try {
        ArrayNode root = mapper.createArrayNode();
        for (DccLocoAddress address : InstanceManager.getDefault(jmri.ConsistManager.class).getConsistList()) {
            root.add(getConsist(locale, address));
        }
        return root;
    } catch (NullPointerException ex) {
        throw new JsonException(503, Bundle.getMessage(locale, "ErrorNoConsistManager")); // NOI18N
    }
}

/**
 * Change the properties and locomotives of a consist.
 *
 * This method takes as input the JSON representation of a consist as
 * provided by {@link #getConsist(Locale, jmri.DccLocoAddress) }.
 *
 * If present in the JSON, this method sets the following consist
 * properties:
 * <ul>
 * <li>consistID</li>
 * <li>consistType</li>
 * <li>locomotives (<em>engines</em> in the JSON representation)<br>
 * <strong>NOTE</strong> Since this method adds, repositions, and deletes
 * locomotives, the JSON representation must contain <em>every</em>
 * locomotive that should be in the consist, if it contains the engines
 * node.</li>
 * </ul>
 *
 * @param locale  the locale to throw exceptions in
 * @param address the consist address
 * @param data    the consist as a JsonObject
 * @throws jmri.server.json.JsonException if no ConsistManager is available
 */
static /*public*/ void setConsist(Locale locale, DccLocoAddress address, JsonNode data) throws JsonException {
    try {
        if (InstanceManager.getDefault(jmri.ConsistManager.class).getConsistList().contains(address)) {
            Consist consist = InstanceManager.getDefault(jmri.ConsistManager.class).getConsist(address);
            if (data.path(ID).isTextual()) {
                consist.setConsistID(data.path(ID).asText());
            }
            if (data.path(TYPE).isInt()) {
                consist.setConsistType(data.path(TYPE).asInt());
            }
            if (data.path(ENGINES).isArray()) {
                ArrayList<DccLocoAddress> engines = new ArrayList<>();
                // add every engine in
                for (JsonNode engine : data.path(ENGINES)) {
                    DccLocoAddress engineAddress = new DccLocoAddress(engine.path(ADDRESS).asInt(), engine.path(IS_LONG_ADDRESS).asBoolean());
                    if (!consist.contains(engineAddress)) {
                        consist.add(engineAddress, engine.path(FORWARD).asBoolean());
                    }
                    consist.setPosition(engineAddress, engine.path(POSITION).asInt());
                    engines.add(engineAddress);
                }
                @SuppressWarnings("unchecked")
                ArrayList<DccLocoAddress> consistEngines = (ArrayList<DccLocoAddress>) consist.getConsistList().clone();
                for (DccLocoAddress engineAddress : consistEngines) {
                    if (!engines.contains(engineAddress)) {
                        consist.remove(engineAddress);
                    }
                }
            }
            try {
                (new ConsistFile()).writeFile(InstanceManager.getDefault(jmri.ConsistManager.class).getConsistList());
            } catch (IOException ex) {
                throw new JsonException(500, ex.getLocalizedMessage());
            }
        }
    } catch (NullPointerException ex) {
        throw new JsonException(503, Bundle.getMessage(locale, "ErrorNoConsistManager")); // NOI18N
    }
}
#endif
/**
 *
 * @param locale the client's locale
 * @param id     the engine id
 * @return the engine in JSON
 * @deprecated since 4.5.6
 */
//@Deprecated
/*static*/ /*public*/ QJsonObject JsonUtil::getEngine(QLocale locale, QString id) {
    QJsonObject root = QJsonObject();//mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::ENGINE);
    root.insert(JSON::DATA, JsonUtil::getEngine(Operations::EngineManager::instance()->getById(id)));
    return root;
}
#if 0
/**
 *
 * @param locale the client's locale
 * @return the list of engines
 * @deprecated since 4.5.6
 */
//@Deprecated
static /*public*/ JsonNode getEngines(Locale locale) {
    ArrayNode root = mapper.createArrayNode();
    for (RollingStock rs : EngineManager.instance().getByIdList()) {
        root.add(getEngine(locale, rs->getId()));
    }
    return root;
}

/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ JsonNode getLight(Locale locale, String name) throws JsonException {
    try {
        ObjectNode root = mapper.createObjectNode();
        root.put(TYPE, LIGHT);
        ObjectNode data = root.putObject(DATA);
        Light light = InstanceManager.lightManagerInstance().getLight(name);
        data.insert(JSON::NAME, light.getSystemName());
        data.insert(JSON::USERNAME, light.getUserName());
        data.insert(JSON::COMMENT, light.getComment());
        switch (light.getState()) {
            case Light.OFF:
                data.insert(JSON::STATE, OFF);
                break;
            case Light.ON:
                data.insert(JSON::STATE, ON);
                break;
            default:
                data.insert(JSON::STATE, UNKNOWN);
                break;
        }
        return root;
    } catch (NullPointerException e) {
        log->error("Unable to get light [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", LIGHT, name));
    }
}

/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ JsonNode getLights(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.lightManagerInstance().getSystemNameList()) {
        root.add(getLight(locale, name));
    }
    return root;
}

/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ void putLight(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        InstanceManager.lightManagerInstance().provideLight(name);
    } catch (Exception ex) {
        throw new JsonException(500, Bundle.getMessage(locale, "ErrorCreatingObject", LIGHT, name));
    }
    setLight(locale, name, data);
}

/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ void setLight(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        Light light = InstanceManager.lightManagerInstance().getBySystemName(name);
        if (data.path(USERNAME).isTextual()) {
            light.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(COMMENT).isTextual()) {
            light.setComment(data.path(COMMENT).asText());
        }
        int state = data.path(STATE).asInt(UNKNOWN);
        switch (state) {
            case OFF:
                InstanceManager.lightManagerInstance().getLight(name).setState(Light.OFF);
                break;
            case ON:
                InstanceManager.lightManagerInstance().getLight(name).setState(Light.ON);
                break;
            case UNKNOWN:
                // silently ignore
                break;
            default:
                throw new JsonException(400, Bundle.getMessage(locale, "ErrorUnknownState", LIGHT, state));
        }
    } catch (NullPointerException e) {
        log->error("Unable to get light [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", LIGHT, name));
    }
}
#endif
/**
 *
 * @param locale the client's locale
 * @param id     the location ID
 * @return the JSON representation of a Location
 * @throws JsonException if the location cannot be located by ID
 * @deprecated since 4.5.6
 */
//@Deprecated
/*static*/ /*public*/ QJsonObject JsonUtil::getLocation(QLocale locale, QString id) throw (JsonException) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::LOCATION);
    //ObjectNode data = root.putObject(DATA);
    QJsonObject data = QJsonObject();
    try {
        Operations::Location* location = Operations::LocationManager::instance()->getLocationById(id);
        data.insert(JSON::NAME, location->getName());
        data.insert(JSON::ID, location->getId());
        data.insert(JSON::LENGTH, location->getLength());
        data.insert(JSON::COMMENT, location->getComment());
    } catch (NullPointerException e) {
        log->error(tr("Unable to get location id [%1].").arg(id));
        throw new JsonException(404, tr( "Unable to access %1 %2.").arg(JSON::LOCATION).arg(id));
    }
    root.insert(JSON::DATA, data);
    return root;
}

/**
 *
 * @param locale the client's locale
 * @return a list of Locations
 * @throws JsonException if thrown while creating a location
 * @deprecated since 4.5.6
 */
//@Deprecated
/*static*/ /*public*/ QJsonArray JsonUtil::getLocations(QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray();//mapper.createArrayNode();
    for (Operations::Location* location : Operations::LocationManager::instance()->getLocationsByIdList()) {
        root.append(getLocation(locale, location->getId()));
    }
    return root;
}
#if 0
/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ JsonNode getMemories(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.memoryManagerInstance().getSystemNameList()) {
        root.add(getMemory(locale, name));
    }
    return root;
}

/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ JsonNode getMemory(Locale locale, String name) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, MEMORY);
    ObjectNode data = root.putObject(DATA);
    Memory memory = InstanceManager.memoryManagerInstance().getMemory(name);
    try {
        data.insert(JSON::NAME, memory.getSystemName());
        data.insert(JSON::USERNAME, memory.getUserName());
        data.insert(JSON::COMMENT, memory.getComment());
        if (memory.getValue() == NULL) {
            data.putNull(VALUE);
        } else {
            data.insert(JSON::VALUE, memory.getValue().toString());
        }
    } catch (NullPointerException e) {
        log->error("Unable to get memory [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", MEMORY, name));
    }
    return root;
}

/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ void putMemory(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        InstanceManager.memoryManagerInstance().provideMemory(name);
    } catch (Exception ex) {
        throw new JsonException(500, Bundle.getMessage(locale, "ErrorCreatingObject", MEMORY, name));
    }
    setMemory(locale, name, data);
}

/*
 * deprecated in favor of the implementations of the {@code do*} methods in
 * {@link jmri.server.json.JsonHttpService}.
 * @deprecated since 4.5.1
 */
//@Deprecated
static /*public*/ void setMemory(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        Memory memory = InstanceManager.memoryManagerInstance().getMemory(name);
        if (data.path(USERNAME).isTextual()) {
            memory.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(COMMENT).isTextual()) {
            memory.setComment(data.path(COMMENT).asText());
        }
        if (!data.path(VALUE).isMissingNode()) {
            if (data.path(VALUE).isNull()) {
                memory.setValue(NULL);
            } else {
                memory.setValue(data.path(VALUE).asText());
            }
        }
    } catch (NullPointerException ex) {
        log->error("Unable to get memory [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", MEMORY, name));
    }
}

/**
 *
 * @param locale The client's Locale.
 * @param name   The metadata element to get.
 * @return JSON metadata element.
 * @throws JsonException if name is not a recognized metadata element.
 * @deprecated since 4.5.2
 */
//@Deprecated
static /*public*/ JsonNode getMetadata(Locale locale, String name) throws JsonException {
    String metadata = Metadata.getBySystemName(name);
    ObjectNode root;
    if (metadata != NULL) {
        root = mapper.createObjectNode();
        root.put(TYPE, METADATA);
        ObjectNode data = root.putObject(DATA);
        data.insert(JSON::NAME, name);
        data.insert(JSON::VALUE, Metadata.getBySystemName(name));
    } else {
        log->error("Unable to get metadata [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", METADATA, name));
    }
    return root;
}

/**
 *
 * @param locale The client's Locale.
 * @return Array of JSON metadata elements.
 * @throws JsonException if thrown by
 *                       {@link #getMetadata(java.util.Locale, java.lang.String)}.
 * @deprecated since 4.5.2
 */
//@Deprecated
static /*public*/ JsonNode getMetadata(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    List<String> names = Metadata.getSystemNameList();
    for (String name : names) {
        root.add(getMetadata(locale, name));
    }
    return root;
}

static /*public*/ ObjectNode getPanel(Locale locale, Editor editor, String format) {
    if (editor.getAllowInFrameServlet()) {
        String title = ((JmriJFrame) editor.getTargetPanel().getTopLevelAncestor()).getTitle();
        if (!title.isEmpty() && !Arrays.asList(WebServerPreferences.getDefault().getDisallowedFrames()).contains(title)) {
            String type = PANEL;
            String name = "Panel";
            if (editor instanceof ControlPanelEditor) {
                type = CONTROL_PANEL;
                name = "ControlPanel";
            } else if (editor instanceof LayoutEditor) {
                type = LAYOUT_PANEL;
                name = "Layout";
            }
            ObjectNode root = mapper.createObjectNode();
            root.put(TYPE, PANEL);
            ObjectNode data = root.putObject(DATA);
            data.insert(JSON::NAME, name + "/" + title.replaceAll(" ", "%20").replaceAll("#", "%23")); // NOI18N
            data.insert(JSON::URL, "/panel/" + data.path(NAME).asText() + "?format=" + format); // NOI18N
            data.insert(JSON::USERNAME, title);
            data.insert(JSON::TYPE, type);
            return root;
        }
    }
    return NULL;
}

static /*public*/ JsonNode getPanels(Locale locale, String format) {
    ArrayNode root = mapper.createArrayNode();
    // list loaded Panels (ControlPanelEditor, PanelEditor, LayoutEditor)
    for (Editor editor : Editor.getEditors(ControlPanelEditor.class)) {
        ObjectNode panel = JsonUtil.getPanel(locale, editor, format);
        if (panel != NULL) {
            root.add(panel);
        }
    }
    for (Editor editor : Editor.getEditors(PanelEditor.class)) {
        if (!(LayoutEditor.class.isInstance(editor))) {  //skip LayoutEditor panels, as they will be added later
            ObjectNode panel = JsonUtil.getPanel(locale, editor, format);
            if (panel != NULL) {
                root.add(panel);
            }
        }
    }
    for (Editor editor : Editor.getEditors(LayoutEditor.class)) {
        ObjectNode panel = JsonUtil.getPanel(locale, editor, format);
        if (panel != NULL) {
            root.add(panel);
        }
    }
    return root;
}

//@Deprecated
static /*public*/ JsonNode getPower(Locale locale) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, POWER);
    ObjectNode data = root.putObject(DATA);
    try {
        switch (InstanceManager.getDefault(jmri.PowerManager.class).getPower()) {
            case PowerManager.OFF:
                data.insert(JSON::STATE, OFF);
                break;
            case PowerManager.ON:
                data.insert(JSON::STATE, ON);
                break;
            default:
                data.insert(JSON::STATE, UNKNOWN);
                break;
        }
    } catch (JmriException e) {
        log->error("Unable to get Power state.", e);
        throw new JsonException(500, Bundle.getMessage(locale, "ErrorPower"));
    } catch (NullPointerException e) {
        // No PowerManager is defined; just report it as UNKNOWN
        data.insert(JSON::STATE, UNKNOWN);
    }
    return root;
}

//@Deprecated
static /*public*/ void setPower(Locale locale, JsonNode data) throws JsonException {
    int state = data.path(STATE).asInt(UNKNOWN);
    try {
        switch (state) {
            case OFF:
                InstanceManager.getDefault(jmri.PowerManager.class).setPower(PowerManager.OFF);
                break;
            case ON:
                InstanceManager.getDefault(jmri.PowerManager.class).setPower(PowerManager.ON);
                break;
            case UNKNOWN:
                // quietly ignore
                break;
            default:
                throw new JsonException(400, Bundle.getMessage(locale, "ErrorUnknownState", POWER, state));
        }
    } catch (JmriException ex) {
        throw new JsonException(500, ex);
    }
}

static /*public*/ JsonNode getRailroad(Locale locale) {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, RAILROAD);
    ObjectNode data = root.putObject(DATA);
    data.insert(JSON::NAME, WebServerPreferences.getDefault().getRailRoadName());
    return root;
}

static /*public*/ JsonNode getReporter(Locale locale, String name) {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, REPORTER);
    ObjectNode data = root.putObject(DATA);
    Reporter reporter = InstanceManager.getDefault(jmri.ReporterManager.class).getReporter(name);
    data.insert(JSON::NAME, reporter.getSystemName());
    data.insert(JSON::USERNAME, reporter.getUserName());
    data.insert(JSON::STATE, reporter.getState());
    data.insert(JSON::COMMENT, reporter.getComment());
    data.insert(JSON::REPORT, (reporter.getCurrentReport() != NULL) ? reporter.getCurrentReport().toString() : NULL);
    data.insert(JSON::LAST_REPORT, (reporter.getLastReport() != NULL) ? reporter.getLastReport().toString() : NULL);
    return root;
}

static /*public*/ JsonNode getReporters(Locale locale) {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.getDefault(jmri.ReporterManager.class).getSystemNameList()) {
        root.add(getReporter(locale, name));
    }
    return root;
}

static /*public*/ void putReporter(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        InstanceManager.getDefault(jmri.ReporterManager.class).provideReporter(name);
    } catch (Exception ex) {
        throw new JsonException(500, Bundle.getMessage(locale, "ErrorCreatingObject", REPORTER, name));
    }
    setReporter(locale, name, data);
}

static /*public*/ void setReporter(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        Reporter reporter = InstanceManager.getDefault(jmri.ReporterManager.class).getBySystemName(name);
        if (data.path(USERNAME).isTextual()) {
            reporter.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(COMMENT).isTextual()) {
            reporter.setComment(data.path(COMMENT).asText());
        }
        if (data.path(REPORT).isNull()) {
            InstanceManager.getDefault(jmri.ReporterManager.class).getReporter(name).setReport(NULL);
        } else {
            InstanceManager.getDefault(jmri.ReporterManager.class).getReporter(name).setReport(data.path(REPORT).asText());
        }
    } catch (NullPointerException ex) {
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", REPORTER, name));
    }
}

/**
 * Returns the JSON representation of a roster entry.
 *
 * Note that this returns, for images and icons, a URL relative to the root
 * folder of the JMRI server. It is expected that clients will fill in the
 * server IP address and port as they know it to be.
 *
 * @param locale the client Locale
 * @param id     The id of an entry in the roster.
 * @return a roster entry in JSON notation
 * @deprecated since 4.3.5
 */
//@Deprecated
static /*public*/ JsonNode getRosterEntry(Locale locale, String id) {
    return JsonUtil.getRosterEntry(locale, Roster.getDefault().getEntryForId(id));
}

/**
 * Returns the JSON representation of a roster entry.
 *
 * Note that this returns, for images and icons, a URL relative to the root
 * folder of the JMRI server. It is expected that clients will fill in the
 * server IP address and port as they know it to be.
 *
 * @param locale The client Locale
 * @param re     A RosterEntry that may or may not be in the roster.
 * @return a roster entry in JSON notation
 * @deprecated since 4.3.5
 */
//@Deprecated
static /*public*/ JsonNode getRosterEntry(Locale locale, RosterEntry re) {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, ROSTER_ENTRY);
    ObjectNode entry = root.putObject(DATA);
    entry.put(NAME, re.getId());
    entry.put(ADDRESS, re.getDccAddress());
    entry.put(IS_LONG_ADDRESS, re.isLongAddress());
    entry.put(ROAD, re.getRoadName());
    entry.put(NUMBER, re.getRoadNumber());
    entry.put(MFG, re.getMfg());
    entry.put(DECODER_MODEL, re.getDecoderModel());
    entry.put(DECODER_FAMILY, re.getDecoderFamily());
    entry.put(MODEL, re.getModel());
    entry.put(COMMENT, re.getComment());
    entry.put(MAX_SPD_PCT, Integer.toString(re.getMaxSpeedPCT()));
    entry.put(IMAGE, (re.getImagePath() != NULL) ? "/" + ROSTER + "/" + re.getId() + "/" + IMAGE : (String) NULL);
    entry.put(ICON, (re.getIconPath() != NULL) ? "/" + ROSTER + "/" + re.getId() + "/" + ICON : (String) NULL);
    entry.put(SHUNTING_FUNCTION, re.getShuntingFunction());
    ArrayNode labels = entry.putArray(FUNCTION_KEYS);
    for (int i = 0; i <= re.getMAXFNNUM(); i++) {
        ObjectNode label = mapper.createObjectNode();
        label.put(NAME, F + i);
        label.put(LABEL, re.getFunctionLabel(i));
        label.put(LOCKABLE, re.getFunctionLockable(i));
        label.put(ICON, (re.getFunctionImage(i) != NULL) ? "/" + ROSTER + "/" + re.getId() + "/" + F + i + "/" + ICON : (String) NULL);
        label.put(SELECTED_ICON, (re.getFunctionSelectedImage(i) != NULL) ? "/" + ROSTER + "/" + re.getId() + "/" + F + i + "/" + SELECTED_ICON : (String) NULL);
        labels.add(label);
    }
    ArrayNode rga = entry.putArray(ROSTER_GROUPS);
    for (RosterGroup group : re.getGroups()) {
        rga.add(group.getName());
    }
    return root;
}

/**
 *
 * @param locale The locale of the requesting client
 * @param data   A JsonNode optionally containing a group name in the
 *               "group" node
 * @return the Roster as a Json Array
 * @deprecated since 4.3.5
 */
//@Deprecated
static /*public*/ JsonNode getRoster(Locale locale, JsonNode data) {
    String group = (!data.path(GROUP).isMissingNode()) ? data.path(GROUP).asText() : NULL;
    if (Roster.ALLENTRIES.equals(group)) {
        group = NULL;
    }
    String roadName = (!data.path(ROAD).isMissingNode()) ? data.path(ROAD).asText() : NULL;
    String roadNumber = (!data.path(NUMBER).isMissingNode()) ? data.path(NUMBER).asText() : NULL;
    String dccAddress = (!data.path(ADDRESS).isMissingNode()) ? data.path(ADDRESS).asText() : NULL;
    String mfg = (!data.path(MFG).isMissingNode()) ? data.path(MFG).asText() : NULL;
    String decoderModel = (!data.path(DECODER_MODEL).isMissingNode()) ? data.path(DECODER_MODEL).asText() : NULL;
    String decoderFamily = (!data.path(DECODER_FAMILY).isMissingNode()) ? data.path(DECODER_FAMILY).asText() : NULL;
    String id = (!data.path(NAME).isMissingNode()) ? data.path(NAME).asText() : NULL;
    ArrayNode root = mapper.createArrayNode();
    for (RosterEntry re : Roster.getDefault().getEntriesMatchingCriteria(roadName, roadNumber, dccAddress, mfg, decoderModel, decoderFamily, id, group)) {
        root.add(getRosterEntry(locale, re.getId()));
    }
    return root;
}

/**
 *
 * @param locale The locale of the requesting client
 * @return the list of Roster groups
 * @deprecated since 4.3.5
 */
//@Deprecated
static /*public*/ JsonNode getRosterGroups(Locale locale) {
    ArrayNode root = mapper.createArrayNode();
    root.add(getRosterGroup(locale, Roster.ALLENTRIES));
    for (String name : Roster.getDefault().getRosterGroupList()) {
        root.add(getRosterGroup(locale, name));
    }
    return root;
}

/**
 *
 * @param locale The locale of the requesting client
 * @param name   The name of the group
 * @return A description of the group including its name and size
 * @deprecated since 4.3.5
 */
//@Deprecated
static /*public*/ JsonNode getRosterGroup(Locale locale, String name) {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, ROSTER_GROUP);
    ObjectNode data = root.putObject(DATA);
    data.insert(JSON::NAME, name);
    data.insert(JSON::LENGTH, Roster.getDefault().getEntriesInGroup(name).size());
    return root;
}

//@Deprecated
static /*public*/ JsonNode getRoute(Locale locale, String name) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, ROUTE);
    ObjectNode data = root.putObject(DATA);
    try {
        Route route = InstanceManager.getDefault(jmri.RouteManager.class).getRoute(name);
        SensorManager s = InstanceManager.sensorManagerInstance();
        data.insert(JSON::NAME, route.getSystemName());
        data.insert(JSON::USERNAME, route.getUserName());
        data.insert(JSON::COMMENT, route.getComment());
        Sensor sensor = s.getSensor(route.getTurnoutsAlignedSensor());
        if (sensor != NULL) {
            switch (sensor.getKnownState()) {
                case Sensor.ACTIVE:
                    data.insert(JSON::STATE, ACTIVE);
                    break;
                case Sensor.INACTIVE:
                    data.insert(JSON::STATE, INACTIVE);
                    break;
                case Sensor.INCONSISTENT:
                    data.insert(JSON::STATE, INCONSISTENT);
                    break;
                case Sensor.UNKNOWN:
                default:
                    data.insert(JSON::STATE, UNKNOWN);
                    break;
            }
        } else {
            data.insert(JSON::STATE, UNKNOWN);
        }
    } catch (NullPointerException e) {
        log->error("Unable to get route [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", ROUTE, name));
    }
    return root;
}

//@Deprecated
static /*public*/ JsonNode getRoutes(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.getDefault(jmri.RouteManager.class).getSystemNameList()) {
        root.add(getRoute(locale, name));
    }
    return root;
}

/**
 * Routes can be set by passing a JsonNode with the node <em>state</em>
 * equal to <em>8</em> (the aspect of {@link jmri.Route#TOGGLE}).
 *
 * @param locale The locale to throw exceptions in
 * @param name   The name of the route
 * @param data   A JsonNode containing route attributes to set
 * @throws jmri.server.json.JsonException if the named route does not exist
 *                                        or the state is invalid
 * @see jmri.Route#TOGGLE
 */
//@Deprecated
static /*public*/ void setRoute(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        Route route = InstanceManager.getDefault(jmri.RouteManager.class).getRoute(name);
        if (data.path(USERNAME).isTextual()) {
            route.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(COMMENT).isTextual()) {
            route.setComment(data.path(COMMENT).asText());
        }
        int state = data.path(STATE).asInt(UNKNOWN);
        switch (state) {
            case ACTIVE:
            case TOGGLE:
                route.setRoute();
                break;
            case INACTIVE:
            case UNKNOWN:
                // silently ignore
                break;
            default:
                throw new JsonException(400, Bundle.getMessage(locale, "ErrorUnknownState", ROUTE, state));
        }
    } catch (NullPointerException ex) {
        log->error("Unable to get route [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", ROUTE, name));
    }
}

//@Deprecated
static /*public*/ JsonNode getSensor(Locale locale, String name) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, SENSOR);
    ObjectNode data = root.putObject(DATA);
    try {
        Sensor sensor = InstanceManager.sensorManagerInstance().getSensor(name);
        data.insert(JSON::NAME, name);
        data.insert(JSON::USERNAME, sensor.getUserName());
        data.insert(JSON::COMMENT, sensor.getComment());
        data.insert(JSON::INVERTED, sensor.getInverted());
        switch (sensor.getKnownState()) {
            case Sensor.ACTIVE:
                data.insert(JSON::STATE, ACTIVE);
                break;
            case Sensor.INACTIVE:
                data.insert(JSON::STATE, INACTIVE);
                break;
            case Sensor.INCONSISTENT:
                data.insert(JSON::STATE, INCONSISTENT);
                break;
            case Sensor.UNKNOWN:
            default:
                data.insert(JSON::STATE, UNKNOWN);
                break;
        }
    } catch (NullPointerException e) {
        log->error("Unable to get sensor [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", SENSOR, name));
    }
    return root;
}

//@Deprecated
static /*public*/ JsonNode getSensors(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.sensorManagerInstance().getSystemNameList()) {
        root.add(getSensor(locale, name));
    }
    return root;
}

//@Deprecated
static /*public*/ void putSensor(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        InstanceManager.sensorManagerInstance().provideSensor(name);
    } catch (Exception ex) {
        throw new JsonException(500, Bundle.getMessage(locale, "ErrorCreatingObject", TURNOUT, name));
    }
    setSensor(locale, name, data);
}

//@Deprecated
static /*public*/ void setSensor(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        Sensor sensor = InstanceManager.sensorManagerInstance().getSensor(name);
        if (data.path(USERNAME).isTextual()) {
            sensor.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(INVERTED).isBoolean()) {
            sensor.setInverted(data.path(INVERTED).asBoolean());
        }
        if (data.path(COMMENT).isTextual()) {
            sensor.setComment(data.path(COMMENT).asText());
        }
        int state = data.path(STATE).asInt(UNKNOWN);
        switch (state) {
            case Sensor.ACTIVE:
                sensor.setKnownState(Sensor.ACTIVE);
                break;
            case INACTIVE:
                sensor.setKnownState(Sensor.INACTIVE);
                break;
            case UNKNOWN:
                // silently ignore
                break;
            default:
                throw new JsonException(400, Bundle.getMessage(locale, "ErrorUnknownState", SENSOR, state));
        }
    } catch (NullPointerException e) {
        log->error("Unable to get sensor [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", SENSOR, name));
    } catch (JmriException ex) {
        throw new JsonException(500, ex);
    }
}

static /*public*/ JsonNode getSignalHead(Locale locale, String name) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, SIGNAL_HEAD);
    ObjectNode data = root.putObject(DATA);
    SignalHead signalHead = InstanceManager.getDefault(jmri.SignalHeadManager.class).getSignalHead(name);
    try {
        data.insert(JSON::NAME, name);
        data.insert(JSON::USERNAME, signalHead.getUserName());
        data.insert(JSON::COMMENT, signalHead.getComment());
        data.insert(JSON::LIT, signalHead.getLit());
        data.insert(JSON::APPEARANCE, signalHead.getAppearance());
        data.insert(JSON::TOKEN_HELD, signalHead.getHeld());
        //state is appearance, plus a flag for held status
        if (signalHead.getHeld()) {
            data.insert(JSON::STATE, SignalHead.HELD);
        } else {
            data.insert(JSON::STATE, signalHead.getAppearance());
        }
        data.insert(JSON::APPEARANCE_NAME, signalHead.getAppearanceName());
    } catch (NullPointerException e) {
        log->error("Unable to get signalHead [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", SIGNAL_HEAD, name));
    }
    return root;
}

static /*public*/ JsonNode getSignalHeads(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.getDefault(jmri.SignalHeadManager.class).getSystemNameList()) {
        root.add(getSignalHead(locale, name));
    }
    return root;
}

static /*public*/ void setSignalHead(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        SignalHead signalHead = InstanceManager.getDefault(jmri.SignalHeadManager.class).getSignalHead(name);
        if (data.path(USERNAME).isTextual()) {
            signalHead.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(COMMENT).isTextual()) {
            signalHead.setComment(data.path(COMMENT).asText());
        }
        int state = data.path(STATE).asInt(UNKNOWN);
        boolean isValid = false;
        for (int validState : signalHead.getValidStates()) {
            if (state == validState) {
                isValid = true;
                break;
            }
        }
        if (isValid && state != INCONSISTENT && state != UNKNOWN) {
            // TODO: completely insulate JSON state from SignalHead state
            signalHead.setAppearance(state);
        } else {
            throw new JsonException(400, Bundle.getMessage(locale, "ErrorUnknownState", SIGNAL_HEAD, state));
        }
    } catch (NullPointerException e) {
        log->error("Unable to get signal head [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", SIGNAL_HEAD, name));
    }
}

static /*public*/ JsonNode getSignalMast(Locale locale, String name) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, SIGNAL_MAST);
    ObjectNode data = root.putObject(DATA);
    SignalMast signalMast = InstanceManager.getDefault(jmri.SignalMastManager.class).getSignalMast(name);
    try {
        data.insert(JSON::NAME, name);
        data.insert(JSON::USERNAME, signalMast.getUserName());
        if (signalMast.getComment() != NULL) {
            data.insert(JSON::COMMENT, signalMast.getComment());
        }
        String aspect = signalMast.getAspect();
        if (aspect == NULL) {
            aspect = ASPECT_UNKNOWN; //if NULL, set aspect to "Unknown"
        }
        data.insert(JSON::ASPECT, aspect);
        data.insert(JSON::LIT, signalMast.getLit());
        data.insert(JSON::TOKEN_HELD, signalMast.getHeld());
        //state is appearance, plus flags for held and dark statii
        if ((signalMast.getHeld()) && (signalMast.getAppearanceMap().getSpecificAppearance(jmri.SignalAppearanceMap.HELD) != NULL)) {
            data.insert(JSON::STATE, ASPECT_HELD);
        } else if ((!signalMast.getLit()) && (signalMast.getAppearanceMap().getSpecificAppearance(jmri.SignalAppearanceMap.DARK) != NULL)) {
            data.insert(JSON::STATE, ASPECT_DARK);
        } else {
            data.insert(JSON::STATE, aspect);
        }
    } catch (NullPointerException e) {
        log->error("Unable to get signalMast [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", SIGNAL_MAST, name));
    }
    return root;
}

static /*public*/ JsonNode getSignalMasts(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.getDefault(jmri.SignalMastManager.class).getSystemNameList()) {
        root.add(getSignalMast(locale, name));
    }
    return root;
}

// TODO: test for HELD and DARK aspects
static /*public*/ void setSignalMast(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        SignalMast signalMast = InstanceManager.getDefault(jmri.SignalMastManager.class).getSignalMast(name);
        if (data.path(USERNAME).isTextual()) {
            signalMast.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(COMMENT).isTextual()) {
            signalMast.setComment(data.path(COMMENT).asText());
        }
        String aspect = data.path(ASPECT).asText();
        if (signalMast.getValidAspects().contains(aspect)) {
            signalMast.setAspect(aspect);
        } else {
            throw new JsonException(400, Bundle.getMessage(locale, "ErrorUnknownState", SIGNAL_MAST, aspect));
        }
    } catch (NullPointerException e) {
        log->error("Unable to get signal mast [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", SIGNAL_MAST, name));
    }
}

/**
 *
 * @param locale the client's Locale.
 * @return the JSON networkServices message.
 * @deprecated since 4.5.2; use
 * {@link jmri.server.json.util.JsonUtilHttpService#getSystemConnections(java.util.Locale)}.
 */
//@Deprecated
static /*public*/ JsonNode getSystemConnections(Locale locale) {
    ArrayNode root = mapper.createArrayNode();
    ArrayList<String> prefixes = new ArrayList<String>();
    for (ConnectionConfig config : InstanceManager.getDefault(ConnectionConfigManager.class)) {
        if (!config.getDisabled()) {
            ObjectNode connection = mapper.createObjectNode().put(TYPE, SYSTEM_CONNECTION);
            ObjectNode data = connection.putObject(DATA);
            data.insert(JSON::NAME, config.getConnectionName());
            data.insert(JSON::MFG, config.getManufacturer());
            data.insert(JSON::PREFIX, config.getAdapter().getSystemConnectionMemo().getSystemPrefix());
            prefixes.add(config.getAdapter().getSystemConnectionMemo().getSystemPrefix());
            root.add(connection);
        }
    }
    for (Object instance : InstanceManager.getList(SystemConnectionMemo.class)) {
        SystemConnectionMemo memo = (SystemConnectionMemo) instance;
        if (!memo.getDisabled() && !prefixes.contains(memo.getSystemPrefix())) {
            ObjectNode connection = mapper.createObjectNode().put(TYPE, SYSTEM_CONNECTION);
            ObjectNode data = connection.putObject(DATA);
            data.insert(JSON::NAME, memo.getUserName());
            data.insert(JSON::PREFIX, memo.getSystemPrefix());
            data.putNull(MFG);
            prefixes.add(memo.getSystemPrefix());
            root.add(connection);
        }
    }
    // Following is required because despite there being a SystemConnectionMemo
    // for the default internal connection, it is not used for the default internal
    // connection. This allows a client to map the server's internal objects.
    String prefix = "I";
    if (!prefixes.contains(prefix)) {
        ObjectNode connection = mapper.createObjectNode().put(TYPE, SYSTEM_CONNECTION);
        ObjectNode data = connection.putObject(DATA);
        data.insert(JSON::NAME, ConnectionNameFromSystemName.getConnectionName(prefix));
        data.insert(JSON::PREFIX, prefix);
        data.putNull(MFG);
        root.add(connection);
    }
    return root;
}

//@Deprecated
static /*public*/ JsonNode getTime(Locale locale) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, TIME);
    ObjectNode data = root.putObject(DATA);
    data.insert(JSON::TIME, new ISO8601DateFormat().format(InstanceManager.getDefault(jmri.Timebase.class).getTime()));
    data.insert(JSON::RATE, InstanceManager.getDefault(jmri.Timebase.class).getRate());
    data.insert(JSON::STATE, InstanceManager.getDefault(jmri.Timebase.class).getRun() ? ON : OFF);
    return root;
}

//@Deprecated
static /*public*/ void setTime(Locale locale, JsonNode data) throws JsonException {
    try {
        if (data.path(TIME).isTextual()) {
            InstanceManager.getDefault(jmri.Timebase.class).setTime(new ISO8601DateFormat().parse(data.path(TIME).asText()));
        }
        if (data.path(RATE).isDouble()) {
            InstanceManager.getDefault(jmri.ClockControl.class).setRate(data.path(RATE).asDouble());
        }
        if (data.path(STATE).isInt()) {
            InstanceManager.getDefault(jmri.Timebase.class).setRun(data.path(STATE).asInt() == ON);
        }
    } catch (ParseException ex) {
        log->error("Time \"{}\" not in ISO 8601 date format", data.path(TIME).asText());
        throw new JsonException(400, Bundle.getMessage(locale, "ErrorTimeFormat"));
    }
}
#endif
/*static*/ /*public*/ QJsonObject JsonUtil::getTrain(QLocale locale, QString id) throw (JsonException) {
    QJsonObject root = QJsonObject();;//mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::TRAIN);
    //ObjectNode data = root.putObject(JSON::DATA);
    QJsonObject data = QJsonObject();
    try {
        Operations::Train* train = Operations::TrainManager::instance()->getTrainById(id);
        data.insert(JSON::NAME, train->getName());
        data.insert(JSON::ICON_NAME, train->getIconName());
        data.insert(JSON::ID, train->getId());
        data.insert(JSON::DEPARTURE_TIME, train->getFormatedDepartureTime());
        data.insert(JSON::DESCRIPTION, train->getDescription());
        data.insert(JSON::COMMENT, train->getComment());
        data.insert(JSON::ROUTE, train->getRoute()->getName());
        data.insert(JSON::ROUTE_ID, train->getRoute()->getId());
        data.insert(JSON::LOCATIONS, getRouteLocationsForTrain(locale, train));
        data.insert(JSON::ENGINES, getEnginesForTrain(locale, train));
        data.insert(JSON::CARS, getCarsForTrain(locale, train));
        if (train->getTrainDepartsName() != NULL) {
            data.insert(JSON::DEPARTURE_LOCATION, train->getTrainDepartsName());
        }
        if (train->getTrainTerminatesName() != NULL) {
            data.insert(JSON::TERMINATES_LOCATION, train->getTrainTerminatesName());
        }
        data.insert(JSON::LOCATION, train->getCurrentLocationName());
        if (train->getCurrentLocation() != NULL) {
            data.insert(JSON::LOCATION_ID, train->getCurrentLocation()->getId());
        }
        data.insert(JSON::STATUS, train->getStatus(locale));
        data.insert(JSON::STATUS_CODE, train->getStatusCode());
        data.insert(JSON::LENGTH, train->getTrainLength());
        data.insert(JSON::WEIGHT, train->getTrainWeight());
        if (train->getLeadEngine() != NULL) {
            data.insert(JSON::LEAD_ENGINE, train->getLeadEngine()->toString());
        }
        data.insert(JSON::CABOOSE, train->getCabooseRoadAndNumber());
root.insert(JSON::DATA, data);
    } catch (NullPointerException e) {
        log->error(tr("Unable to get train id [%1].").arg(id));
        throw new JsonException(404, tr( "Unable to access %1 %2.").arg(JSON::TRAIN).arg(id));
    }
    return root;
}

/*static*/ /*public*/ QJsonArray JsonUtil::getTrains(QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray();//mapper.createArrayNode();
    for (Operations::Train* train : Operations::TrainManager::instance()->getTrainsByNameList()) {
        root.append(getTrain(locale, train->getId()));
    }
    return root;
}
#if 0
/**
 * Sets the properties in the data parameter for the train with the given
 * id.
 *
 * Currently only moves the train to the location given with the key
 * {@value jmri.jmris.json.JSON#LOCATION}. If the move cannot be completed,
 * throws error code 428.
 *
 * @param locale The locale to throw exceptions in.
 * @param id     The id of the train->
 * @param data   Train data to change.
 * @throws jmri.server.json.JsonException if the train cannot move to the
 *                                        location in data.
 */
static /*public*/ void setTrain(Locale locale, String id, JsonNode data) throws JsonException {
    Train train = TrainManager.instance().getTrainById(id);
    if (!data.path(LOCATION).isMissingNode()) {
        String location = data.path(LOCATION).asText();
        if (location->equals(NULL)) {
            train->terminate();
        } else if (!train->move(location)) {
            throw new JsonException(428, Bundle.getMessage(locale, "ErrorTrainMovement", id, location));
        }
    }
}

//@Deprecated
static /*public*/ JsonNode getTurnout(Locale locale, String name) throws JsonException {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, TURNOUT);
    ObjectNode data = root.putObject(DATA);
    try {
        Turnout turnout = InstanceManager.turnoutManagerInstance().getTurnout(name);
        data.insert(JSON::NAME, turnout.getSystemName());
        data.insert(JSON::USERNAME, turnout.getUserName());
        data.insert(JSON::COMMENT, turnout.getComment());
        data.insert(JSON::INVERTED, turnout.getInverted());
        switch (turnout.getKnownState()) {
            case Turnout.THROWN:
                data.insert(JSON::STATE, THROWN);
                break;
            case Turnout.CLOSED:
                data.insert(JSON::STATE, CLOSED);
                break;
            case Turnout.INCONSISTENT:
                data.insert(JSON::STATE, INCONSISTENT);
                break;
            case Turnout.UNKNOWN:
            default:
                data.insert(JSON::STATE, UNKNOWN);
                break;
        }
    } catch (NullPointerException e) {
        log->error("Unable to get turnout [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", TURNOUT, name));
    }
    return root;
}

//@Deprecated
static /*public*/ JsonNode getTurnouts(Locale locale) throws JsonException {
    ArrayNode root = mapper.createArrayNode();
    for (String name : InstanceManager.turnoutManagerInstance().getSystemNameList()) {
        root.add(getTurnout(locale, name));
    }
    return root;
}

//@Deprecated
static /*public*/ void putTurnout(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        InstanceManager.turnoutManagerInstance().provideTurnout(name);
    } catch (Exception ex) {
        throw new JsonException(500, Bundle.getMessage(locale, "ErrorCreatingObject", TURNOUT, name));
    }
    setTurnout(locale, name, data);
}

//@Deprecated
static /*public*/ void setTurnout(Locale locale, String name, JsonNode data) throws JsonException {
    try {
        Turnout turnout = InstanceManager.turnoutManagerInstance().getTurnout(name);
        if (data.path(USERNAME).isTextual()) {
            turnout.setUserName(data.path(USERNAME).asText());
        }
        if (data.path(INVERTED).isBoolean()) {
            turnout.setInverted(data.path(INVERTED).asBoolean());
        }
        if (data.path(COMMENT).isTextual()) {
            turnout.setComment(data.path(COMMENT).asText());
        }
        int state = data.path(STATE).asInt(UNKNOWN);
        switch (state) {
            case THROWN:
                turnout.setCommandedState(Turnout.THROWN);
                break;
            case CLOSED:
                turnout.setCommandedState(Turnout.CLOSED);
                break;
            case UNKNOWN:
                // leave state alone in this case
                break;
            default:
                throw new JsonException(400, Bundle.getMessage(locale, "ErrorUnknownState", TURNOUT, state));
        }
    } catch (NullPointerException ex) {
        log->error("Unable to get turnout [{}].", name);
        throw new JsonException(404, Bundle.getMessage(locale, "ErrorObject", TURNOUT, name));
    }
}

/**
 *
 * @param locale the client's Locale.
 * @param type   the requested type.
 * @return JSON error message.
 * @deprecated since 4.5.2; throw a {@link jmri.server.json.JsonException}
 * instead.
 */
//@Deprecated
static /*public*/ JsonNode getUnknown(Locale locale, String type) {
    return handleError(404, Bundle.getMessage(locale, "ErrorUnknownType", type));
}
#endif
/*static*/ /*private*/ QJsonArray JsonUtil::getCarsForTrain(QLocale locale, Operations::Train* train) {
    QJsonArray clan = QJsonArray();//mapper.createArrayNode();
    Operations::CarManager* carManager = Operations::CarManager::instance();
    QList<Operations::Car*>* carList = carManager->getByTrainDestinationList(train);
    foreach (Operations::Car* car, *carList) {
        clan.append(getCar(locale, car->getId()).value(JSON::DATA)); //add each car's data to the carList array
    }
    return clan;  //return array of car data
}

/*static*/ /*private*/ QJsonArray JsonUtil::getEnginesForTrain(QLocale locale, Operations::Train* train) {
    QJsonArray elan = QJsonArray();//mapper.createArrayNode();
    Operations::EngineManager* engineManager = Operations::EngineManager::instance();
    QList<Operations::Engine*>* engineList = engineManager->getByTrainBlockingList(train);
    foreach (Operations::Engine* engine, *engineList) {
        elan.append(getEngine(locale, engine->getId()).value(JSON::DATA)); //add each engine's data to the engineList array
    }
    return elan;  //return array of engine data
}

/*static*/ /*private*/ QJsonArray JsonUtil::getRouteLocationsForTrain(QLocale locale, Operations::Train* train) throw (JsonException) {
    QJsonArray rlan = QJsonArray(); //mapper.createArrayNode();
    QList<Operations::RouteLocation*>* routeList = train->getRoute()->getLocationsBySequenceList();
    foreach (Operations::RouteLocation* route, *routeList) {
        QJsonObject rln = QJsonObject(); //mapper.createObjectNode();
        Operations::RouteLocation* rl = route;
        rln.insert(JSON::ID, rl->getId());
        rln.insert(JSON::NAME, rl->getName());
        rln.insert(JSON::DIRECTION, rl->getTrainDirectionString());
        rln.insert(JSON::COMMENT, rl->getComment());
        rln.insert(JSON::SEQUENCE, rl->getSequenceId());
        rln.insert(JSON::EXPECTED_ARRIVAL, train->getExpectedArrivalTime(rl));
        rln.insert(JSON::EXPECTED_DEPARTURE, train->getExpectedDepartureTime(rl));
        rln.insert(JSON::LOCATION, getLocation(locale, rl->getLocation()->getId()).value(JSON::DATA));
        rlan.append(rln); //add this routeLocation to the routeLocation array
    }
    return rlan;  //return array of routeLocations
}
#if 0
/**
 *
 * @param locale    the client's Locale
 * @param heartbeat seconds before which no communications from client will
 *                  cause connection to be broken
 * @return a JSON hello message
 * @deprecated since 4.5.2; use
 * {@link jmri.server.json.util.JsonUtilHttpService#getHello(java.util.Locale, int)}.
 */
//@Deprecated
static /*public*/ JsonNode getHello(Locale locale, int heartbeat) {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, HELLO);
    ObjectNode data = root.putObject(DATA);
    data.insert(JSON::JMRI, jmri.Version.name());
    data.insert(JSON::JSON, JSON_PROTOCOL_VERSION);
    data.insert(JSON::HEARTBEAT, Math.round(heartbeat * 0.9f));
    data.insert(JSON::RAILROAD, WebServerPreferences.getDefault().getRailRoadName());
    data.insert(JSON::NODE, NodeIdentity.identity());
    data.insert(JSON::ACTIVE_PROFILE, ProfileManager.getDefault().getActiveProfile().getName());
    return root;
}

/**
 *
 * @param locale the client's Locale.
 * @return the JSON networkServices message.
 * @deprecated since 4.5.2; use
 * {@link jmri.server.json.util.JsonUtilHttpService#getNetworkServices(java.util.Locale)}.
 */
//@Deprecated
static /*public*/ JsonNode getNetworkServices(Locale locale) {
    ArrayNode root = mapper.createArrayNode();
    for (ZeroConfService service : ZeroConfService.allServices()) {
        ObjectNode ns = mapper.createObjectNode().put(TYPE, NETWORK_SERVICE);
        ObjectNode data = ns.putObject(DATA);
        data.insert(JSON::NAME, service.name());
        data.insert(JSON::PORT, service.serviceInfo().getPort());
        data.insert(JSON::TYPE, service.type());
        Enumeration<String> pe = service.serviceInfo().getPropertyNames();
        while (pe.hasMoreElements()) {
            String pn = pe.nextElement();
            data.insert(JSON::pn, service.serviceInfo().getPropertyString(pn));
        }
        root.add(ns);
    }
    return root;
}

/**
 *
 * @param locale the client's Locale
 * @return the JSON node message
 * @deprecated since 4.5.2; use
 * {@link jmri.server.json.util.JsonUtilHttpService#getNode(java.util.Locale)}.
 */
//@Deprecated
/*public*/ static JsonNode getNode(Locale locale) {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, NODE);
    ObjectNode data = root.putObject(DATA);
    data.insert(JSON::NODE, NodeIdentity.identity());
    ArrayNode nodes = mapper.createArrayNode();
    for (String node : NodeIdentity.formerIdentities()) {
        nodes.add(node);
    }
    data.insert(JSON::FORMER_NODES, nodes);
    return root;
}

/**
 * JSON errors should be handled by throwing a
 * {@link jmri.server.json.JsonException}.
 *
 * @param code the error value
 * @param message the error message
 * @return a JSON encoded error
 * @deprecated
 */
//@Deprecated
static /*public*/ ObjectNode handleError(int code, String message) {
    ObjectNode root = mapper.createObjectNode();
    root.put(TYPE, ERROR);
    ObjectNode data = root.putObject(DATA);
    data.insert(JSON::CODE, code);
    data.insert(JSON::MESSAGE, message);
    return root;
}

/**
 * Gets the {@link jmri.DccLocoAddress} for a String in the form
 * <code>number(type)</code> or <code>number</code>.
 *
 * Type may be <code>L</code> for long or <code>S</code> for short. If the
 * type is not specified, type is assumed to be short.
 *
 * @param address the address
 * @return The DccLocoAddress for address.
 * @deprecated since 4.5.3; use
 * {@link jmri.server.json.util.JsonUtilHttpService#addressForString(java.lang.String)}
 * instead.
 */
//@Deprecated
static /*public*/ DccLocoAddress addressForString(String address) {
    return JsonUtilHttpService.addressForString(address);
}
#endif
/*static*/ /*public*/ QJsonObject JsonUtil::getCar(Operations::Car* car) {
    QJsonObject node = JsonUtil::getRollingStock(car);
     node.insert(JSON::LOAD, car->getLoadName()); // NOI18N
     node.insert(JSON::HAZARDOUS, car->isHazardous());
     node.insert(JSON::REMOVE_COMMENT, car->getDropComment());
     node.insert(JSON::ADD_COMMENT, car->getPickupComment());
     node.insert(JSON::KERNEL, car->getKernelName());
     node.insert(JSON::UTILITY, car->isUtility());
    if (car->getFinalDestinationTrack() != NULL) {
         node.insert(JSON::FINAL_DESTINATION, JsonUtil::getLocationAndTrack(car->getFinalDestinationTrack(), NULL));
    } else if (car->getFinalDestination() != NULL) {
         node.insert(JSON::FINAL_DESTINATION, JsonUtil::getLocation(car->getFinalDestination(), NULL));
    }
    if (car->getReturnWhenEmptyDestTrack() != NULL) {
         node.insert(JSON::RETURN_WHEN_EMPTY, JsonUtil::getLocationAndTrack(car->getReturnWhenEmptyDestTrack(), NULL));
    } else if (car->getReturnWhenEmptyDestination() != NULL) {
         node.insert(JSON::RETURN_WHEN_EMPTY, JsonUtil::getLocation(car->getReturnWhenEmptyDestination(), NULL));
    }
    return node;
}

/*static*/ /*public*/ QJsonObject JsonUtil::getEngine(Operations::Engine* engine) {
    QJsonObject node = JsonUtil::getRollingStock(engine);
    node.insert(JSON::MODEL, engine->getModel());
    node.insert(JSON::CONSIST, engine->getConsistName());
    return node;
}

/*static*/ /*private*/ QJsonObject JsonUtil::getRollingStock(Operations::RollingStock* rs) {
    QJsonObject node = QJsonObject();//mapper.createObjectNode();
     node.insert(JSON::ID, rs->getId());
     node.insert(JSON::NUMBER, Operations::TrainCommon::splitString(rs->getNumber()));
     node.insert(JSON::ROAD, rs->getRoadName());
    QStringList type = rs->getTypeName().split("-"); // second half of string
    // can be anything
     node.insert(JSON::TYPE, type[0]);
     node.insert(JSON::LENGTH, rs->getLength());
     node.insert(JSON::COLOR, rs->getColor());
     node.insert(JSON::OWNER, rs->getOwner());
     node.insert(JSON::COMMENT, rs->getComment());
    if (rs->getTrack() != NULL) {
         node.insert(JSON::LOCATION, JsonUtil::getLocationAndTrack(rs->getTrack(), rs->getRouteLocation()));
    } else if (rs->getLocation() != NULL) {
         node.insert(JSON::LOCATION, JsonUtil::getLocation(rs->getLocation(), rs->getRouteLocation()));
    }
    if (rs->getDestinationTrack() != NULL) {
         node.insert(JSON::DESTINATION, JsonUtil::getLocationAndTrack(rs->getDestinationTrack(), rs->getRouteDestination()));
    } else if (rs->getDestination() != NULL) {
         node.insert(JSON::DESTINATION, JsonUtil::getLocation(rs->getDestination(), rs->getRouteDestination()));
    }
    return node;
}

/*static*/ /*private*/ QJsonObject JsonUtil::getLocation(Operations::Location* location, Operations::RouteLocation* routeLocation) {
    QJsonObject node = QJsonObject();//mapper.createObjectNode();
     node.insert(JSON::NAME, location->getName());
     node.insert(JSON::ID, location->getId());
    if (routeLocation != NULL) {
         node.insert(JSON::ROUTE, routeLocation->getId());
    }
    return node;
}

/*static*/ /*private*/ QJsonObject JsonUtil::getLocationAndTrack(Operations::Track* track, Operations::RouteLocation* routeLocation) {
    QJsonObject node = JsonUtil::getLocation(track->getLocation(), routeLocation);
     node.insert(JSON::TRACK, JsonUtil::getTrack(track));
    return node;
}

/*static*/ /*private*/ QJsonObject JsonUtil::getTrack(Operations::Track* track) {
    QJsonObject node = QJsonObject();//mapper.createObjectNode();
     node.insert(JSON::NAME, track->getName());
     node.insert(JSON::ID, track->getId());
    return node;
}

//}

