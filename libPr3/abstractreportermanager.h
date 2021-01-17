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
    int getXMLOrder()const override;
    char typeLetter()const override;
    Reporter* provideReporter(QString sName)override;
    Reporter* getReporter(QString name)const override;
    NamedBean *getBySystemName(QString name) const override;
    NamedBean* getByUserName(QString key) const override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    Reporter* getByDisplayName(QString key)const override;
    Reporter* newReporter(QString systemName, QString userName)const throw(IllegalArgumentException)override;
    /**
    * A temporary method that determines if it is possible to add a range
    * of turnouts in numerical order eg 10 to 30
    **/
    bool allowMultipleAdditions(QString systemName)const override;
    QString getNextValidAddress(QString curAddress, QString prefix)const override;

signals:
    void newReporterCreated(AbstractReporterManager*, Reporter*);
    
public slots:
private:
    static Logger* log;
protected:
    virtual Reporter* createNewReporter(QString /*systemName*/, QString /*userName*/)const {return NULL;}
 friend class ProxyReporterManager;
};

#endif // ABSTRACTREPORTERMANAGER_H
