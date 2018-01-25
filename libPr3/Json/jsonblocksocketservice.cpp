#include "jsonblocksocketservice.h"
#include "jsonblockhttpservice.h"
#include "jsonblock.h"
#include "json.h"
#include "jsonconnection.h"
#include "block.h"
#include "blockmanager.h"
#include "instancemanager.h"

/**
 *
 * @author mstevetodd Copyright (C) 2016 (copied from JsonMemorySocketService)
 * @author Randall Wood
 */
///*public*/ class JsonBlockSocketService extends JsonSocketService {


/*public*/ JsonBlockSocketService::JsonBlockSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent)
{
   //super(connection);
 blocks = new QMap<QString, BlockListener*>();
 this->service = new JsonBlockHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonBlockSocketService::onMessage(QString type, QJsonObject data,  QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    QString name = data.value(JSON::NAME).toString();
    if (data.value(JSON::METHOD).toString() == (JSON::PUT)) {
        this->connection->sendMessage(this->service->doPut(type, name, data, locale));
    } else {
        this->connection->sendMessage(this->service->doPost(type, name, data, locale));
    }
    if (!this->blocks->contains(name)) {
        Block* block = ((BlockManager*)InstanceManager::getDefault("BlockManager"))->getBlock(name);
        if (block != NULL) {
            BlockListener* listener = new BlockListener(block, this);
            //block.addPropertyChangeListener(listener);
            connect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
            this->blocks->insert(name, listener);
        }
    }
}

//@Override
/*public*/ void JsonBlockSocketService::onList(QString type, QJsonObject /*data*/,  QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonBlockSocketService::onClose() {
    //blocks.values().stream().forEach((block) ->
    foreach(BlockListener* listener, blocks->values())
    {
        //block->block.removePropertyChangeListener(block);
     disconnect(listener->block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));

    }//);
    blocks->clear();
}

// /*private*/ class BlockListener implements PropertyChangeListener {

//    protected final Block block;

/*public*/ BlockListener::BlockListener(Block* block, JsonBlockSocketService* jbss) {
    this->block = block;
 this->jbss = jbss;
}

//@Override
/*public*/ void BlockListener::propertyChange(PropertyChangeEvent* e) {
    if (e->getPropertyName()==("value")) {
        try {
            try {
                jbss->connection->sendMessage(jbss->service->doGet(JsonBlock::BLOCK, this->block->getSystemName(), jbss->locale));
            } catch (JsonException ex) {
                jbss->connection->sendMessage(ex.getJsonMessage());
            }
        } catch (IOException ex) {
            // if we get an error, de-register
            //block.removePropertyChangeListener(this);
      disconnect(block->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));

            jbss->blocks->remove(this->block->getSystemName());
        }
    }
}
//}
