#ifndef JSONLAYOUTBLOCKSOCKETSERVICE_H
#define JSONLAYOUTBLOCKSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"
#include "layoutblock.h"

class LayoutBlockListener;
class JsonLayoutBlockHttpService;
class JsonLayoutBlockSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonLayoutBlockSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonLayoutBlockHttpService* service;
 /*private*/ /*final*/ QMap<QString, LayoutBlockListener*>* layoutBlocks;// = new HashMap<>();
 /*private*/ QLocale locale;
 /*private*/ static /*final*/ Logger* log;// = LoggerFactory::getLogger(JsonLayoutBlockServiceFactory.class);
friend class LayoutBlockListener;
};

/*private*/ class LayoutBlockListener : public PropertyChangeListener {
 Q_OBJECT
protected:
 /*protected*/ /*final*/ LayoutBlock* layoutBlock;
private:
 JsonLayoutBlockSocketService* jlbss;
 /*public*/ LayoutBlockListener(LayoutBlock* layoutblock, JsonLayoutBlockSocketService* jlbss);
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);
 friend class JsonLayoutBlockSocketService;
};

#endif // JSONLAYOUTBLOCKSOCKETSERVICE_H
