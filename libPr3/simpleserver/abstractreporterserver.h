#ifndef ABSTRACTREPORTERSERVER_H
#define ABSTRACTREPORTERSERVER_H

#include <QObject>
#include "propertychangelistener.h"
#include "exceptions.h"
#include "reportermanager.h"
#include "instancemanager.h"

class Reporter;
class ARSReporterListener;
class AbstractReporterServer : public QObject
{
 Q_OBJECT
public:
 explicit AbstractReporterServer(QObject *parent = nullptr);
 /*abstract*/ virtual /*public*/ void sendReport(QString /*reporter*/, QVariant /*r*/) /*throw (IOException)*/ {}
 /*abstract*/ virtual /*public*/ void sendErrorStatus(QString /*reporter*/) /*throw (IOException)*/ {}
 /*abstract*/ virtual /*public*/ void parseStatus(QString /*statusString*/) /*throw (JmriException, IOException)*/{}
 /*public*/ Reporter* initReporter(QString reporterName) throw (IllegalArgumentException);
 /*public*/ void setReporterReport(QString reporterName, QVariant r);
 /*public*/ void dispose();

signals:

public slots:

private:
 /*private*/ /*final*/ QMap<QString, ARSReporterListener*> reporters;
static Logger* log;

protected:
/*synchronized*/ /*protected*/ void addReporterToList(QString reporterName);
/*synchronized*/ /*protected*/ void removeReporterFromList(QString reporterName);

 friend class ARSReporterListener;
};

class ARSReporterListener : public QObject,public PropertyChangeListener {
Q_OBJECT
  Q_INTERFACES(PropertyChangeListener)
 AbstractReporterServer* ars;
public:
    ARSReporterListener(QString reporterName, AbstractReporterServer* ars) {
     this->ars = ars;
        name = reporterName;
        reporter = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->getReporter(reporterName);
    }
    QObject* self() override{return (QObject*)this;}

    // update state as state of reporter changes
    //@Override
public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e)override {
        // If the Commanded State changes, show transition state as "<inconsistent>"
        if (e->getPropertyName() ==("currentReport")) {
            QString now;
            try {
                now = e->getNewValue().toString();
            } catch (NullPointerException* npe) {
                // current report is null, which is expected.
                now = nullptr;
            }
            try {
                ars->sendReport(name, now);
            } catch (IOException* ie) {
                ars->log->debug("Error Sending Status");
                // if we get an error, de-register
                ((NamedBean*)reporter->self())->removePropertyChangeListener(this);
                ars->removeReporterFromList(name);
            }
        }
    }
private:
    QString name = "";
    Reporter* reporter = nullptr;
};
#endif // ABSTRACTREPORTERSERVER_H
