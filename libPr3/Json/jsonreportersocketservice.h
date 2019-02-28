#ifndef JSONREPORTERSOCKETSERVICE_H
#define JSONREPORTERSOCKETSERVICE_H
#include "propertychangelistener.h"
#include "jsonsocketservice.h"
#include "reporter.h"

class ReporterListener;
class JsonReporterHttpService;
class JsonReporterSocketService : public JsonSocketService
{
 Q_OBJECT
public:
 JsonReporterSocketService(JsonConnection* connection, QObject* parent = 0);
 /*public*/ void onMessage(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onList(QString type, QJsonObject data, QLocale locale) throw (IOException, JmriException, JsonException);
 /*public*/ void onClose();

private:
 /*private*/ /*final*/ JsonReporterHttpService* service;
 /*private*/ /*final*/ QMap<QString, ReporterListener*>* reporters;// = new HashMap<>();
 /*private*/ QLocale locale;
 friend class ReporterListener;
};
/*private*/ class ReporterListener :public  PropertyChangeListener {
Q_OBJECT
    /*protected*/ /*final*/ Reporter* reporter;
private:
 JsonReporterSocketService* jrss;
    /*public*/ ReporterListener(Reporter* reporter, JsonReporterSocketService* jrss);
public slots:
    //@Override
    /*public*/ void propertyChange(PropertyChangeEvent* e);
 friend class JsonReporterSocketService;
};

#endif // JSONREPORTERSOCKETSERVICE_H
