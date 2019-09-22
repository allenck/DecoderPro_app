#ifndef ABSTRACTREPORTERMANAGER_H
#define ABSTRACTREPORTERMANAGER_H
#include "abstractmanager.h"
#include "reporter.h"
#include "exceptions.h"
#include "reportermanager.h"


class LIBPR3SHARED_EXPORT AbstractReporterManager :  public ReporterManager
{
    Q_OBJECT
public:
    explicit AbstractReporterManager(SystemConnectionMemo *memo, QObject *parent = 0);
    virtual int getXMLOrder();
    virtual char typeLetter();
    Reporter* provideReporter(QString sName);
    Reporter* getReporter(QString name);
    Reporter* getBySystemName(QString name) const;
    Reporter* getByUserName(QString key);
    Reporter* getByDisplayName(QString key);
    Reporter* newReporter(QString systemName, QString userName) throw(IllegalArgumentException);
    /**
    * A temporary method that determines if it is possible to add a range
    * of turnouts in numerical order eg 10 to 30
    **/
    bool allowMultipleAdditions(QString systemName);
    QString getNextValidAddress(QString curAddress, QString prefix) const;

signals:
    void newReporterCreated(AbstractReporterManager*, Reporter*);
    
public slots:
private:
    Logger* log;
protected:
    virtual Reporter* createNewReporter(QString /*systemName*/, QString /*userName*/) {return NULL;}
 friend class ProxyReporterManager;
};

#endif // ABSTRACTREPORTERMANAGER_H
