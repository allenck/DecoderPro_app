#ifndef JSONOPERATIONSSOCKETSERVICE_H
#define JSONOPERATIONSSOCKETSERVICE_H
#include "jsonsocketservice.h"
#include "propertychangelistener.h"
#include "train.h"

class JsonOperationsHttpService;
class TrainListener;
class JsonOperationsSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 /*public*/ JsonOperationsSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();


private:
 /*private*/ QLocale locale;
 /*private*/ /*final*/ JsonOperationsHttpService* service;
 /*private*/ /*final*/ QMap<QString, TrainListener*> trains;// = new HashMap<>();
friend class TrainListener;
};
/*private*/ class TrainListener : public PropertyChangeListener {

 Q_OBJECT
 JsonOperationsSocketService* joss;
public :
public slots:
 /*public*/ void propertyChange(PropertyChangeEvent* e);

protected:
    /*protected*/ /*final*/ Operations::Train* train;
    /*protected*/ TrainListener(QString id, JsonOperationsSocketService* joss) ;
 friend class JsonOperationsSocketService;
};

#endif // JSONOPERATIONSSOCKETSERVICE_H
