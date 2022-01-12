#include "jsonturnouthttpservice.h"
#include "instancemanager.h"
#include "proxyturnoutmanager.h"
#include "json.h"
#include "turnout.h"

/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonTurnoutHttpService extends JsonNamedBeanHttpService {

/*public*/ JsonTurnoutHttpService::JsonTurnoutHttpService(ObjectMapper mapper, QObject* parent) : JsonNamedBeanHttpService(mapper, parent){
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonTurnoutHttpService::doGet(QString type, QString name, QLocale locale) /*throw (JsonException)*/ {
    QJsonObject root = QJsonObject();//mapper.createObjectNode();
    root.insert(JSON::TYPE, JSON::TURNOUT);
    Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(name);
    QJsonObject data = this->getNamedBean(turnout, name, type, locale); // throws JsonException if turnout == null
    if (turnout != NULL) {
        data.insert(JSON::INVERTED, turnout->getInverted());
        switch (turnout->getKnownState()) {
            case Turnout::THROWN:
                data.insert(JSON::STATE, JSON::THROWN);
                break;
            case Turnout::CLOSED:
                data.insert(JSON::STATE, JSON::CLOSED);
                break;
            case Turnout::INCONSISTENT:
                data.insert(JSON::STATE, JSON::INCONSISTENT);
                break;
            case Turnout::UNKNOWN:
            default:
                data.insert(JSON::STATE, JSON::UNKNOWN);
                break;
        }
        root.insert(JSON::DATA, data);

    }
    return root;
}

//@Override
/*public*/ QJsonObject JsonTurnoutHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) /*throw (JsonException)*/ {
    Turnout* turnout = ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->getTurnout(name);
    if (turnout == NULL) {
        throw new  JsonException(404, tr("Unable to access %1 %2.").arg(JSON::TURNOUT).arg(name));
    }
    if (data.value(JSON::USERNAME).isString()) {
        turnout->setUserName(data.value(JSON::USERNAME).toString());
    }
    if (data.value(JSON::INVERTED).isBool()) {
        turnout->setInverted(data.value(JSON::INVERTED).toBool());
    }
    if (data.value(JSON::COMMENT).isString()) {
        turnout->setComment(data.value(JSON::COMMENT).toString());
    }
    int state = data.value(JSON::STATE).toInt(JSON::UNKNOWN);
    switch (state) {
        case Turnout::THROWN:
            turnout->setCommandedState(Turnout::THROWN);
            break;
        case Turnout::CLOSED:
            turnout->setCommandedState(Turnout::CLOSED);
            break;
        case Turnout::UNKNOWN:
            // leave state alone in this case
            break;
        default:
            throw new JsonException(400, tr("Attempting to set object type %1 to unknown state %2.").arg(JSON::TURNOUT).arg(state));
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonValue JsonTurnoutHttpService::doPut(QString type, QString name, QJsonObject data, QLocale locale) /*throw (JsonException)*/ {
    try {
        ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->provideTurnout(name);
    } catch (IllegalArgumentException* ex) {
        throw new  JsonException(500, tr("Unable to access %1 %2.").arg(JSON::TURNOUT).arg(name));
    }
    return this->doPost(type, name, data, locale);
}

//@Override
/*public*/ QJsonValue JsonTurnoutHttpService::doGetList(QString /*type*/, QLocale locale) /*throw (JsonException)*/ {
    //ArrayNode root = this->mapper.createArrayNode();
 QJsonArray root = QJsonArray();
    foreach (QString name, ((ProxyTurnoutManager*)InstanceManager::turnoutManagerInstance())->AbstractProxyManager::getSystemNameList())
    {
        root.append(this->doGet(JSON::TURNOUT, name, locale));
    }
    return QJsonValue(root);

}
