#include "jsonconsistsocketservice.h"
#include "jsonconsisthttpservice.h"
#include "loggerfactory.h"
#include "consistfile.h"
/**
 *
 * @author Randall Wood Copyright (C) 2016
 */
///*public*/ class JsonConsistSocketService extends JsonSocketService {

/*private*/ /*final*/ /*static*/ Logger* JsonConsistSocketService::log = LoggerFactory::getLogger("JsonConsistSocketService");

/*public*/ JsonConsistSocketService::JsonConsistSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent)
{
    //super(connection);
 consists =  QSet<DccLocoAddress*>();
 consistListener =  new JsonConsistListener(this);
 consistListListener =  new JsonConsistListListener(this);

 this->service = new JsonConsistHttpService(connection->getObjectMapper());
 if(this->service->manager != NULL)
  this->service->manager->addConsistListListener(this->consistListListener);
}

//@Override
/*public*/ void JsonConsistSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    if (JSON::CONSISTS == (type)) {
        this->connection->sendMessage(this->service->doGetList(type, locale));
    } else {
        DccLocoAddress* address = new DccLocoAddress(data.value(JSON::ADDRESS).toInt(), data.value(JSON::IS_LONG_ADDRESS).toBool());
        QString name = address->getNumber() + (address->isLongAddress() ? "L" : "");
        if (data.value(JSON::METHOD).toString() == ( JSON::PUT)) {
            this->connection->sendMessage(this->service->doPut(type, name, data, locale));
        } else {
            this->connection->sendMessage(this->service->doPost(type, name, data, locale));
        }
        if (!this->consists.contains(address)) {
            this->service->manager->getConsist(address)->addConsistListener(this->consistListener);
            this->consists.insert(address);
        }
    }
}

//@Override
/*public*/ void JsonConsistSocketService::onList(QString type, QJsonObject data, QLocale /*locale*/) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonConsistSocketService::onClose() {
//    this->consists.stream().forEach((address) -> {
//        this->service->manager.getConsist(address).removeConsistListener(this->consistListener);
//    });
 foreach(DccLocoAddress* address, this->consists)
 {
    this->consists.clear();
    this->service->manager->removeConsistListListener(this->consistListListener);
 }
}

///*private*/ class JsonConsistListener implements ConsistListener {
JsonConsistListener::JsonConsistListener(JsonConsistSocketService* jcss) {this->jcss = jcss;}

    //@Override
    /*public*/ void JsonConsistListener::consistReply(DccLocoAddress* locoaddress, int status) {
        try {
            try {
                jcss->connection->sendMessage(jcss->service->getConsist(jcss->locale, locoaddress));
            } catch (JsonException ex) {
                jcss->connection->sendMessage(ex.getJsonMessage());
            }
        } catch (IOException* ex) {
            // this IO execption caused by broken comms with client
            jcss->service->manager->getConsist(locoaddress)->removeConsistListener(this);
            jcss->consists.remove(locoaddress);
        }
        try {
            (new ConsistFile())->writeFile(jcss->service->manager->getConsistList()->toList());
        } catch (IOException* ex) {
            // this IO execption caused by unable to write file
            jcss->log->error(tr("Unable to write consist file \"%1\": %2").arg( ConsistFile::defaultConsistFilename()).arg(ex->getMessage()));
        }
    }
//}

///*private*/ class JsonConsistListListener implements ConsistListListener {

JsonConsistListListener::JsonConsistListListener(JsonConsistSocketService* jcss) { this->jcss = jcss;}
    //@Override
    /*public*/ void JsonConsistListListener::notifyConsistListChanged() {
        try {
            try {
                jcss->connection->sendMessage(jcss->service->doGetList(JSON::CONSISTS, jcss->locale));
            } catch (JsonException ex) {
                jcss->connection->sendMessage(ex.getJsonMessage());
            }
        } catch (IOException* ex) {
            // this IO execption caused by broken comms with client
            jcss->service->manager->removeConsistListListener(this);
        }
        try {
            (new ConsistFile())->writeFile(jcss->service->manager->getConsistList()->toList());
        } catch (IOException* ex) {
            // this IO execption caused by unable to write file
            jcss->log->error(tr("Unable to write consist file \"%1\": %2").arg( ConsistFile::defaultConsistFilename()).arg(ex->getMessage()));
        }
    }
//}
