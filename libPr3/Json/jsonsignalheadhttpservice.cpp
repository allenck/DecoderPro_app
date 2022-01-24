#include "jsonsignalheadhttpservice.h"
#include "signalhead.h"
#include "signalheadmanager.h"
#include "instancemanager.h"
#include "jsonsignalhead.h"
#include "json.h"

/**
 * JSON HTTP service for {@link jmri.SignalHead}s.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonSignalHeadHttpService extends JsonNamedBeanHttpService {

/*public*/ JsonSignalHeadHttpService::JsonSignalHeadHttpService(ObjectMapper mapper, QObject* parent) : JsonNamedBeanHttpService(mapper, parent) {
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonSignalHeadHttpService::doGet(QString type, QString name, QLocale locale) /*throw (JsonException)*/ {
    QJsonObject root = QJsonObject(); //mapper.createQJsonObject();
    root.insert(JSON::TYPE, JsonSignalHead::SIGNAL_HEAD);
    SignalHead* signalHead = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
    QJsonObject data = this->getNamedBean(signalHead, name, type, locale);
    if (signalHead != NULL) {
        data.insert(JSON::LIT, signalHead->getLit());
        data.insert(JSON::APPEARANCE, signalHead->getAppearance());
        data.insert(JSON::TOKEN_HELD, signalHead->getHeld());
        //state is appearance, plus a flag for held status
        if (signalHead->getHeld()) {
            data.insert(JSON::STATE, SignalHead::HELD);
        } else {
            data.insert(JSON::STATE, signalHead->getAppearance());
        }
        data.insert(JSON::APPEARANCE_NAME, signalHead->getAppearanceName());
    }
    root.insert(JSON::DATA, data);

    return root;
}

//@Override
/*public*/ QJsonObject JsonSignalHeadHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) /*throw (JsonException)*/ {
    SignalHead* signalHead = ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSignalHead(name);
    this->postNamedBean(signalHead, data, name, type, locale);
    if (signalHead != NULL) {
        if (data.value(JSON::STATE).isDouble()) {
            int state = data.value(JSON::STATE).toDouble();
            if (state == SignalHead::HELD) {
                signalHead->setHeld(true);
            } else {
                bool isValid = false;
                for (int validState : signalHead->getValidStates()) {
                    if (state == validState) {
                        isValid = true;
                        // TODO: completely insulate JSON state from SignalHead state
                        if (signalHead->getHeld()) signalHead->setHeld(false);
                        signalHead->setAppearance(state);
                        break;
                    }
                }
                if (!isValid) {
                    throw new JsonException(400, tr(/*locale, */"Attempting to set object type %1 to unknown state %2.").arg(JsonSignalHead::SIGNAL_HEAD).arg(state));
                }
            }
        }
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonValue JsonSignalHeadHttpService::doGetList(QString type, QLocale locale) /*throw (JsonException)*/ {
    QJsonArray root = QJsonArray(); //this->mapper.createArrayNode();
    foreach (QString name, ((SignalHeadManager*)InstanceManager::getDefault("SignalHeadManager"))->getSystemNameList()) {
        root.append(this->doGet(JsonSignalHead::SIGNAL_HEAD, name, locale));
    }
    return root;
}
