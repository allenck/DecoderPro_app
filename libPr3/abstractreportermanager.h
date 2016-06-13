#ifndef ABSTRACTREPORTERMANAGER_H
#define ABSTRACTREPORTERMANAGER_H
#include "abstractmanager.h"
#include "reporter.h"
#include "exceptions.h"
#include "abstractreporter.h"

class AbstractManager;
class LIBPR3SHARED_EXPORT AbstractReporterManager :  public AbstractManager
{
    Q_OBJECT
public:
    explicit AbstractReporterManager(QObject *parent = 0);
    virtual int getXMLOrder();
    virtual char typeLetter();
    AbstractReporter* provideReporter(QString sName);
    AbstractReporter* getReporter(QString name);
    AbstractReporter* getBySystemName(QString name);
    AbstractReporter* getByUserName(QString key);
    AbstractReporter* getByDisplayName(QString key);
    AbstractReporter* newReporter(QString systemName, QString userName) throw(IllegalArgumentException);
    /**
    * A temporary method that determines if it is possible to add a range
    * of turnouts in numerical order eg 10 to 30
    **/
    bool allowMultipleAdditions(QString systemName);
    QString getNextValidAddress(QString curAddress, QString prefix);

signals:
    void newReporterCreated(AbstractReporterManager*, AbstractReporter*);
    
public slots:
private:
    Logger* log;
protected:
    virtual AbstractReporter* createNewReporter(QString systemName, QString userName) = 0;

};

#endif // ABSTRACTREPORTERMANAGER_H
