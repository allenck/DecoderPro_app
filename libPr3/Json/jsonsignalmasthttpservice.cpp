#include "jsonsignalmasthttpservice.h"
#include "signalmast.h"
#include "signalmastmanager.h"
#include "instancemanager.h"
#include "jsonsignalmast.h"
#include "json.h"

/**
 * JSON HTTP service for {@link jmri.SignalMast}s.
 *
 * @author Randall Wood (C) 2016
 */
///*public*/ class JsonSignalMastHttpService extends JsonNamedBeanHttpService {

/*public*/ JsonSignalMastHttpService::JsonSignalMastHttpService(ObjectMapper mapper, QObject* parent) : JsonNamedBeanHttpService(mapper, parent){
    //super(mapper);
}

//@Override
/*public*/ QJsonValue JsonSignalMastHttpService::doGet(QString type, QString name, QLocale locale) throw (JsonException) {
    QJsonObject root = QJsonObject(); //mapper.createObjectNode();
    root.insert(JSON::TYPE, JsonSignalMast::SIGNAL_MAST);
    SignalMast* signalMast =((SignalMastManager*) InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
    QJsonObject data = this->getNamedBean(signalMast, name, type, locale);
    if (signalMast != NULL) {
        QString aspect = signalMast->getAspect();
        if (aspect == NULL) {
            aspect = JSON::ASPECT_UNKNOWN; //if NULL, set aspect to "Unknown"
        }
        data.insert(JSON::ASPECT, aspect);
        data.insert(JSON::LIT, signalMast->getLit());
        data.insert(JSON::TOKEN_HELD, signalMast->getHeld());
        //state is appearance, plus flags for held and dark statii
        if ((signalMast->getHeld()) && (signalMast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::HELD) != NULL)) {
            data.insert(JSON::STATE, JSON::ASPECT_HELD);
        } else if ((!signalMast->getLit()) && (signalMast->getAppearanceMap()->getSpecificAppearance(SignalAppearanceMap::DARK) != NULL)) {
            data.insert(JSON::STATE, JSON::ASPECT_DARK);
        } else {
            data.insert(JSON::STATE, aspect);
        }
        root.insert(JSON::DATA, data);

    }
    return root;
}

//@Override
/*public*/ QJsonObject JsonSignalMastHttpService::doPost(QString type, QString name, QJsonObject data, QLocale locale) throw (JsonException) {
    SignalMast* signalMast = ((SignalMastManager*) InstanceManager::getDefault("SignalMastManager"))->getSignalMast(name);
    this->postNamedBean(signalMast, data, name, type, locale);
    if (signalMast != NULL) {
        if (data.value(JSON::STATE).isString()) {
            QString aspect = data.value(JSON::STATE).toString();
            if (aspect == ("Held")) {
                signalMast->setHeld(true);
            } else if ( signalMast->getValidAspects().contains(aspect)) {
                if ( signalMast->getHeld()) {
                     signalMast->setHeld(false);
                }
                if ( signalMast->getAspect() == NULL ||  signalMast->getAspect() != (aspect)) {
                     signalMast->setAspect(aspect);
                }
            } else {
                throw new JsonException(400, tr(/*locale, */"Attempting to set object type %1 to unknown state %2.").arg(JSON::SIGNAL_MAST).arg(aspect));
            }
        }
    }
    return this->doGet(type, name, locale).toObject();
}

//@Override
/*public*/ QJsonValue JsonSignalMastHttpService::doGetList(QString type, QLocale locale) throw (JsonException) {
    QJsonArray root = QJsonArray(); //this->mapper.createArrayNode();

    for (QString name : ((SignalMastManager*) InstanceManager::getDefault("SignalMastManager"))->getSystemNameList()) {
        root.append(this->doGet(JsonSignalMast::SIGNAL_MAST, name, locale));
    }
    return root;
}
