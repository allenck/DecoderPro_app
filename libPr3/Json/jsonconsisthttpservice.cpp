#include "jsonconsisthttpservice.h"
#include "instancemanager.h"
#include "jsonconsistmanager.h"
#include "jsonutilhttpservice.h"
#include "consistfile.h"
/**
 *
 * @author Randall Wood Copyright (C) 2016
 */
///*public*/ class JsonConsistHttpService extends JsonHttpService {


/*public*/ JsonConsistHttpService::JsonConsistHttpService(ObjectMapper mapper, QObject* parent) : JsonHttpService(mapper, parent) {
    //super(mapper);
//        this->manager = InstanceManager.getOptionalDefault("JsonConsistManager").orElseGet(() -> {
//            return InstanceManager.setDefault(JsonConsistManager.class, new JsonConsistManager());
//        });
    this->manager =  (JsonConsistManager*)InstanceManager::getOptionalDefault("JsonConsistManager");
    if(this->manager == NULL)
    {
     InstanceManager::setDefault("JsonConsistManager", new JsonConsistManager());
    }

}

//@Override
/*public*/ QJsonValue JsonConsistHttpService::doGet(QString /*type*/, QString name, QLocale locale) throw (JsonException) {
    if (!this->manager->isConsistManager()) {
        throw JsonException(503, tr( "ErrorNoConsistManager")); // NOI18N
    }
    return this->getConsist(locale, JsonUtilHttpService::addressForString(name));
}

/**
 * Change the properties and locomotives of a consist->
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
 * @param type   the JSON message type
 * @param locale the locale to throw exceptions in
 * @param name   the consist address, ignored if data contains an
 *               {@value jmri.server.json.JSON#ADDRESS} and
 *               {@value jmri.server.json.JSON#IS_LONG_ADDRESS} nodes
 * @param data   the consist as a JsonObject
 * @return the JSON representation of the Consist
 * @throw jmri.server.json.JsonException if there is no consist manager
 *                                        (code 503), the consist does not
 *                                        exist (code 404), or the consist
 *                                        cannot be saved (code 500).
 */
//@Override
/*public*/ QJsonObject JsonConsistHttpService::doPost(QString /*type*/, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    if (!this->manager->isConsistManager()) {
        throw JsonException(503, tr( "ErrorNoConsistManager")); // NOI18N
    }
    DccLocoAddress* address;
    if (data.value(JSON::ADDRESS).isDouble()) {
        address = new DccLocoAddress(data.value(JSON::ADDRESS).toInt(), data.value(JSON::IS_LONG_ADDRESS).toBool(false));
    } else {
        address = JsonUtilHttpService::addressForString(data.value(JSON::ADDRESS).toString());
    }
    if (!this->manager->getConsistList()->contains(address)) {
        throw JsonException(404, tr( "Unable to access %1 %2.").arg(JSON::CONSIST).arg(name));
    }
    Consist* consist = this->manager->getConsist(address);
    if (data.value(JSON::ID).isString()) {
        consist->setConsistID(data.value(JSON::ID).toString());
    }
    if (data.value(JSON::TYPE).isDouble()) {
        consist->setConsistType(data.value(JSON::TYPE).toInt());
    }
    if (data.value(JSON::ENGINES).isArray()) {
        QList<DccLocoAddress*> engines = QList<DccLocoAddress*>();
        // add every engine
        for (QJsonValue engine : data.value(JSON::ENGINES).toObject()) {
            DccLocoAddress* engineAddress = new DccLocoAddress(engine.toObject().value(JSON::ADDRESS).toInt(), engine.toObject().value(JSON::IS_LONG_ADDRESS).toBool());
            if (!consist->contains(engineAddress)) {
                consist->add(engineAddress, engine.toObject().value(JSON::FORWARD).toBool());
            }
            consist->setPosition(engineAddress, engine.toObject().value(JSON::POSITION).toInt());
            engines.append(engineAddress);
        }
        // remove engines if needed
        QList<DccLocoAddress*> consistEngines =  QList<DccLocoAddress*>(consist->getConsistList());
//        consistEngines.stream().filter((engineAddress) -> (!engines.contains(engineAddress))).forEach((engineAddress) ->
        foreach(DccLocoAddress* engineAddress, consistEngines)
        {
         if(!engines.contains(engineAddress))
            consist->remove(engineAddress);
        }//);
    }
    try {
        (new ConsistFile())->writeFile(this->manager->getConsistList());
    } catch (IOException ex) {
        throw JsonException(500, ex.getLocalizedMessage());
    }
    return this->getConsist(locale, address);
}

//@Override
/*public*/ QJsonObject JsonConsistHttpService::doPut(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    if (!this->manager->isConsistManager()) {
        throw JsonException(503, tr( "ErrorNoConsistManager")); // NOI18N
    }
    DccLocoAddress* address;
    if (data.value(JSON::ADDRESS).isDouble()) {
        address = new DccLocoAddress(data.value(JSON::ADDRESS).toInt(), data.value(JSON::IS_LONG_ADDRESS).toBool(false));
    } else {
        address = JsonUtilHttpService::addressForString(data.value(JSON::ADDRESS).toString());
    }
    this->manager->getConsist(address);
    return this->doPost(type, name, data, locale);
}

//@Override
/*public*/ void JsonConsistHttpService::doDelete(QString /*type*/, QString name, QLocale /*locale*/) throw (JsonException) {
    if (!this->manager->isConsistManager()) {
        throw JsonException(503, tr( "ErrorNoConsistManager")); // NOI18N
    }
    if (!this->manager->getConsistList()->contains(JsonUtilHttpService::addressForString(name))) {
        throw JsonException(404, tr( "Unable to access %1 %2.").arg(JSON::CONSIST).arg(name)); // NOI18N
    }
    this->manager->delConsist(JsonUtilHttpService::addressForString(name));
}

//@Override
/*public*/ QJsonValue JsonConsistHttpService::doGetList(QString type, QLocale locale) throw (JsonException) {
    if (!this->manager->isConsistManager()) {
        throw JsonException(503, tr( "ErrorNoConsistManager")); // NOI18N
    }
    QJsonArray root = QJsonArray();//mapper.createArrayNode();
    for (DccLocoAddress* address : *this->manager->getConsistList()) {
        root.append(getConsist(locale, address));
    }
    return root;
}

/**
 * Get the JSON representation of a consist->
 *
 * The JSON representation is an object with the following data attributes:
 * <ul>
 * <li>address - integer address</li>
 * <li>isLongAddress - boolean true if address is long, false if short</li>
 * <li>type - integer, see {@link jmri.Consist#getConsistType() }</li>
 * <li>id - string with consist Id</li>
 * <li>sizeLimit - the maximum number of locomotives the consist can
 * contain</li>
 * <li>engines - array listing every locomotive in the consist-> Each entry
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
 * @return The JSON representation of the consist->
 * @throw JsonException This exception has code 404 if the consist does not
 *                       exist.
 */
/*public*/ QJsonObject JsonConsistHttpService::getConsist(QLocale locale, DccLocoAddress* address) throw (JsonException) {
    if (this->manager->getConsistList()->contains(address)) {
        QJsonObject root = QJsonObject();//mapper.createObjectNode();
        root.insert(JSON::TYPE, JSON::CONSIST);
        //ObjectNode data = root.putObject(DATA);
        QJsonObject data = QJsonObject();
        Consist* consist = this->manager->getConsist(address);
        data.insert(JSON::ADDRESS, consist->getConsistAddress()->getNumber());
        data.insert(JSON::IS_LONG_ADDRESS, consist->getConsistAddress()->isLongAddress());
        data.insert(JSON::TYPE, consist->getConsistType());
        QJsonArray engines = QJsonArray();//data.putArray(JSON::ENGINES);
        //consist->getConsistList().stream().forEach((locomotive) ->
        foreach(DccLocoAddress* locomotive, consist->getConsistList())
        {
            QJsonObject engine = QJsonObject();//mapper.createObjectNode();
            engine.insert(JSON::ADDRESS, locomotive->getNumber());
            engine.insert(JSON::IS_LONG_ADDRESS, locomotive->isLongAddress());
            engine.insert(JSON::FORWARD, consist->getLocoDirection(locomotive));
            engine.insert(JSON::POSITION, consist->getPosition(locomotive));
            engines.append(engine);
        }//);
        data.insert(JSON::ENGINES, engines);
        data.insert(JSON::ID, consist->getConsistID());
        data.insert(JSON::SIZE_LIMIT, consist->sizeLimit());
        root.insert(JSON::DATA, data);
        return root;
    } else {
        throw JsonException(404, tr( "Unable to access %1 %2.").arg(JSON::CONSIST).arg(address->toString())); // NOI18N
    }
}
