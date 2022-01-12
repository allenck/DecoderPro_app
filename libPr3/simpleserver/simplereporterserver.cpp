#include "simplereporterserver.h"
#include "loggerfactory.h"
#include "reportable.h"
#include <QTcpSocket>
#include "vptr.h"
#include "reportervariant.h"
/**
 * Simple Server interface between the JMRI reporter manager and a network
 * connection
 *
 * @author Paul Bender Copyright (C) 2011
 * @author Randall Wood Copyright (C) 2013
 */
///*public*/ class SimpleReporterServer extends AbstractReporterServer {


/*public*/ SimpleReporterServer::SimpleReporterServer(QTcpSocket *connection, QObject *parent)
 : AbstractReporterServer(parent)
{
    //super();
    this->connection = connection;
}

///*public*/ SimpleReporterServer(DataInputStream inStream, DataOutputStream outStream) {
//    super();
//    output = outStream;
//}


/*
 * Protocol Specific Abstract Functions
 */
//@Override
/*public*/ void SimpleReporterServer::sendReport(QString reporterName, QVariant r) /*throw (IOException)*/ {
    addReporterToList(reporterName);
    if (r != QVariant()) {
//        if (r instanceof jmri.Reportable )
     QObject* obj = VPtr<QObject>::asPtr(r);
     if(qobject_cast<Reportable*>(obj))
        {
           this->sendMessage("REPORTER " + reporterName + " " + VPtr<Reportable>::asPtr(r)->toReportString() + "\n");
        } else {
           this->sendMessage("REPORTER " + reporterName + " " + r.toString() + "\n");
        }
    } else {
        this->sendMessage("REPORTER " + reporterName + "\n");
    }
}

//@Override
/*public*/ void SimpleReporterServer::sendErrorStatus(QString reporterName) /*throw (IOException)*/ {
    this->sendMessage("REPORTER ERROR\n");
}

//@Override
/*public*/ void SimpleReporterServer::parseStatus(QString statusString) throw (JmriException, IOException) {
    int index, index2;
    index = statusString.indexOf(" ") + 1;
    index2 = statusString.indexOf(" ", index + 1);
    int newlinepos = statusString.indexOf("\n");
    QString reporterName = statusString.mid(index, index2>0?index2:newlinepos).toUpper();
    initReporter(reporterName);
    // the string should be "REPORTER xxxxxx REPORTSTRING\n\r"
    // where xxxxxx is the reporter identifier and REPORTSTRING is
    // the report, which may contain spaces.
    if (index2 > 0 && ( newlinepos - (index2 + 1) > 0)) {
        setReporterReport(reporterName, statusString.mid(index2 + 1,newlinepos));
        // setReporterReport ALSO triggers sending the status report, so
        // no further action is required to echo the status to the client.
    } else {
        // send the current status if the report
        try {
           Reporter* reporter = qobject_cast<ReporterManager*>(InstanceManager::getDefault("ReporterManager"))->provideReporter(reporterName);
           sendReport(reporterName, reporter->getCurrentReport());
        } catch (IllegalArgumentException* ex) {
            log->warn(tr("Failed to provide Reporter \"%1\" in parseStatus").arg(reporterName));
        }
    }
}

/*private*/ void SimpleReporterServer::sendMessage(QString message) /*throw (IOException)*/ {
    if (this->output != nullptr) {
        this->output->writeBytes(message.toLocal8Bit().data(), message.length());
    } else {
        this->connection->write(message.toLocal8Bit());
    }
}

/*private*/ /*final*/ /*static*/ Logger* SimpleReporterServer::log = LoggerFactory::getLogger("SimpleReporterServer");
