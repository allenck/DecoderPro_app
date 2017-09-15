#ifndef RFIDREPORTERMANAGER_H
#define RFIDREPORTERMANAGER_H
#include "abstractreportermanager.h"
#include "rfidreporter.h"

class LIBPR3SHARED_EXPORT RfidReporterManager : public AbstractReporterManager
{
    Q_OBJECT
public:
    //explicit RfidReporterManager(QObject *parent = 0);
    /*public*/ RfidReporterManager(QString prefix, QObject *parent = 0);
    /*public*/ QString getSystemPrefix();
    Reporter* createNewReporter(QString systemName, QString userName);

signals:
    
public slots:
private:
    /*private*/ QString prefix;
 Logger* log;
};

#endif // RFIDREPORTERMANAGER_H
