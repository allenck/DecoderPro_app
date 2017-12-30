#ifndef JSONMEMORYSOCKETSERVICE_H
#define JSONMEMORYSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "memory.h"
#include "propertychangelistener.h"

class QLocale;
class JsonMemoryHttpService;
class MemoryListener;
class JsonMemorySocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonMemorySocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, JsonNode data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonMemoryHttpService* service;
 /*private*/ /*final*/ QMap<QString, MemoryListener*>* memories;// = new HashMap<>();
 /*private*/ QLocale locale;

protected:
 /*protected*/ /*final*/ Memory* memory;
friend class MemoryListener;
};

/*private*/ class MemoryListener : public PropertyChangeListener {

Q_OBJECT
 JsonMemorySocketService* jmss;
 Memory* memory;
public:
    /*public*/ MemoryListener(Memory* memory, JsonMemorySocketService* jmss);
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) ;
 friend class JsonMemorySocketService;
};

#endif // JSONMEMORYSOCKETSERVICE_H
