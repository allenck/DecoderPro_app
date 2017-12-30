#include "jsonmemorysocketservice.h"
#include "json.h"
#include "jsonmemoryhttpservice.h"
#include "memorymanager.h"
#include "instancemanager.h"
/**
 *
 * @author Randall Wood
 */
///*public*/ class JsonMemorySocketService extends JsonSocketService {


    /*public*/ JsonMemorySocketService::JsonMemorySocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent){
        //super(connection);
        this->service = new JsonMemoryHttpService(connection->getObjectMapper());
 memories = new QMap<QString, MemoryListener*>();
    }

    //@Override
    /*public*/ void JsonMemorySocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException) {
        this->locale = locale;
        QString name = data.value(JSON::NAME).toString();
        if (data.value(JSON::METHOD).toString()==(JSON::PUT)) {
            this->connection->sendMessage(this->service->doPut(type, name, data, locale));
        } else {
            this->connection->sendMessage(this->service->doPost(type, name, data, locale));
        }
        if (!this->memories->contains(name)) {
            Memory* memory = ((MemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(name);
            if (memory != NULL) {
                MemoryListener* listener = new MemoryListener(memory, this);
                //memory.addPropertyChangeListener(listener);
                connect(memory->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
                this->memories->insert(name, listener);
            }
        }
    }

    //@Override
    /*public*/ void JsonMemorySocketService::onList(QString type, JsonNode /*data*/, QLocale locale) throw (IOException, JmriException, JsonException) {
        this->locale = locale;
        this->connection->sendMessage(this->service->doGetList(type, locale));
    }

    //@Override
    /*public*/ void JsonMemorySocketService::onClose() {
        //memories.values().stream().forEach((memory) ->
 foreach(MemoryListener* memoryListener, memories->values())
        {
            //memory.memory.removePropertyChangeListener(memory);
  disconnect(memoryListener->memory->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), memoryListener , SLOT(propertyChange(PropertyChangeEvent*)));
        }//);
        memories->clear();
    }

//    /*private*/ class MemoryListener implements PropertyChangeListener {


        /*public*/ MemoryListener::MemoryListener(Memory* memory, JsonMemorySocketService* jmss) {
            this->memory = memory;
 this->jmss = jmss;
        }

        //@Override
        /*public*/ void MemoryListener::propertyChange(PropertyChangeEvent* e) {
            // If the Commanded State changes, show transition state as "<inconsistent>"
            if (e->getPropertyName()==("value")) {
                try {
                    try {
                        jmss->connection->sendMessage(jmss->service->doGet(JSON::MEMORY, this->memory->getSystemName(), jmss->locale));
                    } catch (JsonException ex) {
                        jmss->connection->sendMessage(ex.getJsonMessage());
                    }
                } catch (IOException ex) {
                    // if we get an error, de-register
                    //memory.removePropertyChangeListener(this);
              disconnect(memory->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)),this, SLOT(propertyChange(PropertyChangeEvent*)));
                    jmss->memories->remove(this->memory->getSystemName());
                }
            }
        }
//    }
