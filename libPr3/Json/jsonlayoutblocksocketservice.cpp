#include "jsonlayoutblocksocketservice.h"
#include "loggerfactory.h"
#include "json.h"
#include "jsonlayoutblockhttpservice.h"
#include "jsonlayoutblock.h"
/**
 *
 * @author mstevetodd Copyright (C) 2016 (copied from JsonMemorySocketService)
 * @author Randall Wood
 */
///*public*/ class JsonLayoutBlockSocketService extends JsonSocketService {

    /*private*/ /*static*/ /*final*/ Logger* JsonLayoutBlockSocketService::log = LoggerFactory::getLogger("JsonLayoutBlockServiceFactory");

/*public*/ JsonLayoutBlockSocketService::JsonLayoutBlockSocketService(JsonConnection* connection, QObject* parent) : JsonSocketService(connection, parent){
    //super(connection);
layoutBlocks = new QMap<QString, LayoutBlockListener*>();
 this->service = new JsonLayoutBlockHttpService(connection->getObjectMapper());
}

//@Override
/*public*/ void JsonLayoutBlockSocketService::onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException)
{
 this->locale = locale;
 QString name = data.value(JSON::NAME).toString();
 if (data.value(JSON::METHOD).toString() == (JSON::PUT)) {
     this->connection->sendMessage(this->service->doPut(type, name, data, locale));
 } else {
     this->connection->sendMessage(this->service->doPost(type, name, data, locale));
 }
 if (!this->layoutBlocks->contains(name)) {
     LayoutBlock* layoutblock = ((LayoutBlockManager*) InstanceManager::getDefault("LayoutBlockManager"))->getLayoutBlock(name);
     LayoutBlockListener* listener = new LayoutBlockListener(layoutblock,this);
     //layoutblock.addPropertyChangeListener(listener);
     connect(layoutblock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
     this->layoutBlocks->insert(name, listener);
 }
}

//@Override
/*public*/ void JsonLayoutBlockSocketService::onList(QString type, QJsonObject /*data*/, QLocale locale) throw (IOException, JmriException, JsonException) {
    this->locale = locale;
    this->connection->sendMessage(this->service->doGetList(type, locale));
}

//@Override
/*public*/ void JsonLayoutBlockSocketService::onClose() {
    //layoutBlocks.values().stream().forEach((layoutblock) ->
 foreach(LayoutBlockListener* listener, layoutBlocks->values())
    {
        //layoutblock.layoutBlock.removePropertyChangeListener(layoutblock);
  disconnect(listener->layoutBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), listener, SLOT(propertyChange(PropertyChangeEvent*)));
    }//);
    layoutBlocks->clear();
}

///*private*/ class LayoutBlockListener implements PropertyChangeListener {

//    protected /*final*/ LayoutBlock layoutBlock;

    /*public*/ LayoutBlockListener::LayoutBlockListener(LayoutBlock* layoutblock, JsonLayoutBlockSocketService* jlbss) {
        this->layoutBlock = layoutblock;
 this->jlbss =jlbss;
    }

    //@Override
    /*public*/ void LayoutBlockListener::propertyChange(PropertyChangeEvent* e)
{
        if (e->getPropertyName()==("redraw"))
        {
            jlbss->log->debug(tr("%1 property '%2' changed from '%3' to '%4'").arg(this->layoutBlock->getUserName()).arg(
                    e->getPropertyName()).arg(e->getOldValue().toString()).arg(e->getNewValue().toString()));
            try {
                try {
                    jlbss->connection->sendMessage(jlbss->service->doGet(JsonLayoutBlock::LAYOUTBLOCK, this->layoutBlock->getSystemName(), jlbss->locale));
                } catch (JsonException ex) {
                    jlbss->connection->sendMessage(ex.getJsonMessage());
                }
            } catch (IOException ex) {
                // if we get an error, de-register
                //layoutBlock.removePropertyChangeListener(this);
             disconnect(layoutBlock->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
                jlbss->layoutBlocks->remove(this->layoutBlock->getSystemName());
            }
        }
    }

