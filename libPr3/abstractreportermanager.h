#ifndef ABSTRACTREPORTERMANAGER_H
#define ABSTRACTREPORTERMANAGER_H
#include "abstractmanager.h"
#include "reporter.h"
#include "exceptions.h"
#include "reportermanager.h"


class LIBPR3SHARED_EXPORT AbstractReporterManager :  public AbstractManager, public ReporterManager
{
    Q_OBJECT
  Q_INTERFACES(ReporterManager)
public:
    explicit AbstractReporterManager(SystemConnectionMemo *memo, QObject *parent = 0);
    int getXMLOrder()const override;
    QChar typeLetter() const override;
    Reporter* provideReporter(QString sName)override;
    Reporter* getReporter(QString name) override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    NamedBean *getBySystemName(QString name)  override;
    NamedBean* getByUserName(QString key)  override;
    Reporter* getByDisplayName(QString key) override;
    Reporter* newReporter(QString systemName, QString userName) /*throw(IllegalArgumentException)*/override;
    /**
    * A temporary method that determines if it is possible to add a range
    * of turnouts in numerical order eg 10 to 30
    **/
    bool allowMultipleAdditions(QString systemName) override;
    QString getNextValidAddress(QString curAddress, QString prefix) override;

signals:
    void newReporterCreated(AbstractReporterManager*, Reporter*);
    
public slots:
private:
    static Logger* log;
protected:
    virtual Reporter* createNewReporter(QString /*systemName*/, QString /*userName*/) {return NULL;}
 friend class ProxyReporterManager;
};

#endif // ABSTRACTREPORTERMANAGER_H
