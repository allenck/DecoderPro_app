#ifndef JSONLIGHTSOCKETSERVICE_H
#define JSONLIGHTSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"

class Light;
class LightListener;
class JsonLightHttpService;
class JsonLightSocketService : public JsonSocketService
{
public:
 JsonLightSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) /*throw (IOException, JmriException, JsonException)*/;
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) /*throw (IOException, JmriException, JsonException)*/;
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonLightHttpService* service;
 /*private*/ /*final*/ QMap<QString, LightListener*>* lights;// = new HashMap<>();
 /*private*/ QLocale locale;
friend class LightListener;
};

/*private*/ class LightListener : public QObject,public PropertyChangeListener {
private:
 JsonLightSocketService* jlss;
Q_OBJECT
 Q_INTERFACES(PropertyChangeListener)
protected:
    /*protected*/ /*final*/ Light* light;
public:
 LightListener();
    /*public*/ LightListener(Light* light, JsonLightSocketService* jlss);
 QObject* self() override{return (QObject*)this;}
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e) override;
 friend class JsonLightSocketService;
};

#endif // JSONLIGHTSOCKETSERVICE_H
