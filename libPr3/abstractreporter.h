#ifndef ABSTRACTREPORTER_H
#define ABSTRACTREPORTER_H
#include "reporter.h"
#include "libPr3_global.h"
#include "qvariant.h"
#include "vptr.h"
#include "rfid/transpondingtag.h"
#include "rfid/reportervariant.h"

class LIBPR3SHARED_EXPORT AbstractReporter : public Reporter
{
 Q_OBJECT
public:
    explicit AbstractReporter(QObject *parent = 0);
    AbstractReporter(QString systemName, QObject *parent = 0);
    AbstractReporter(QString systemName, QString userName, QObject *parent = 0);
    /*public*/ QString getBeanType();
    ReporterVariant getCurrentReport();
    ReporterVariant getLastReport();
    /**
     * Provide a general method for updating the report.
     */
    void setReport(QVariant r);
    /*public*/ int getState() { return state; }
    /*public*/ void setState(int s) { state = s; }

signals:
    void propertyChange(AbstractReporter*, QString pName, QVariant o, QVariant n);

public slots:
 private:
    // internal data members
    QVariant _lastReport;
    QVariant _currentReport;
    int state;// = 0;
};

#endif // ABSTRACTREPORTER_H
