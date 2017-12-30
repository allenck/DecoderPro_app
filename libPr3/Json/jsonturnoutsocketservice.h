#ifndef JSONTURNOUTSOCKETSERVICE_H
#define JSONTURNOUTSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"

class Turnout;
class TurnoutListener;
class JsonTurnoutHttpService;
class JsonTurnoutSocketService : public JsonSocketService
{
public:
 /*public*/ JsonTurnoutSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();


private:
 /*private*/ /*final*/ JsonTurnoutHttpService* service;
 /*private*/ /*final*/ QMap<QString, TurnoutListener*>* turnouts;// = new QMap<QString, TurnoutListener*>();
 /*private*/ QLocale locale;
friend class TurnoutListener;
};
/*private*/ class TurnoutListener : public PropertyChangeListener {

    /*protected*/ /*final*/ Turnout* _turnout;
 JsonTurnoutSocketService* jtss;
public:
    /*public*/ TurnoutListener(Turnout* turnout, JsonTurnoutSocketService* jtss);
 inline Turnout* turnout() {return _turnout;}
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
};

#endif // JSONTURNOUTSOCKETSERVICE_H
