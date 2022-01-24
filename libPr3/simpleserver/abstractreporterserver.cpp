#include "abstractreporterserver.h"
#include "loggerfactory.h"

/**
 * Abstract interface between the a JMRI reporter and a network connection
 *
 * @author Paul Bender Copyright (C) 2010
 * @author Randall Wood Copyright (C) 2013
 */
//abstract /*public*/ class AbstractReporterServer {

/*private*/ /*static*/ /*final*/ Logger* AbstractReporterServer::log = LoggerFactory::getLogger("AbstractReporterServer");

/*public*/ AbstractReporterServer::AbstractReporterServer(QObject* parent) : QObject(parent){
    reporters = QMap<QString, ARSReporterListener*>();
}

/*
 * Protocol Specific Abstract Functions
 */
//abstract /*public*/ void sendReport(String reporter, Object r) throws IOException;

//abstract /*public*/ void sendErrorStatus(String reporter) throws IOException;

//abstract /*public*/ void parseStatus(String statusString) throws JmriException, IOException;

/*synchronized*/ /*protected*/ void AbstractReporterServer::addReporterToList(QString reporterName) {
    if (!reporters.contains(reporterName)) {
        reporters.insert(reporterName, new ARSReporterListener(reporterName, this));
        Reporter* reporter = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->getReporter(reporterName);
        if(reporter!=nullptr) {
           //reporter.addPropertyChangeListener(reporters.get(reporterName));
           connect(reporter->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }
    }
}

/*synchronized*/ /*protected*/ void AbstractReporterServer::removeReporterFromList(QString reporterName) {
    if (reporters.contains(reporterName)) {
        Reporter* reporter = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->getReporter(reporterName);
        if(reporter!=nullptr) {
           //reporter.removePropertyChangeListener(reporters.get(reporterName));
           disconnect(reporter->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }
        reporters.remove(reporterName);
    }
}

/*public*/ Reporter* AbstractReporterServer::initReporter(QString reporterName) throw (IllegalArgumentException) {
    Reporter* reporter = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->provideReporter(reporterName);
    this->addReporterToList(reporterName);
    return reporter;
}

/*
 * Set the report state of a reporter
 *
 * @parm reporterName - the name of a reporter
 * @parm r - the object containing the report (currently a string).
 */
/*public*/ void AbstractReporterServer::setReporterReport(QString reporterName, QVariant r) {
    Reporter* reporter;
    // load address from reporterAddrTextField
    try {
        addReporterToList(reporterName);
        reporter = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->getReporter(reporterName);
        if (reporter == nullptr) {
            log->error(tr("Reporter %1 is not available").arg(reporterName));
        } else {
            log->debug("about to set reporter State");
            reporter->setReport(r);
        }
    } catch (Exception* ex) {
        log->error("set reporter report", ex);
    }
}

/*public*/ void AbstractReporterServer::dispose() {
    //for (Map.Entry<String, ReporterListener> entry: this.reporters.entrySet())
 QMapIterator<QString, ARSReporterListener*> entry(reporters);
 while (entry.hasNext())
    {
  entry.next();
        Reporter* reporter = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->getReporter(entry.key());
        if(reporter!=nullptr) {
           //reporter.removePropertyChangeListener(entry.getValue());
         disconnect(reporter->pcs, SIGNAL(propertyChange(PropertyChangeEvent*)), this, SLOT(propertyChange(PropertyChangeEvent*)));
        }
    }
    this->reporters.clear();
}

