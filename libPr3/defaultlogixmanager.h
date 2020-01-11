#ifndef DEFAULTLOGIXMANAGER_H
#define DEFAULTLOGIXMANAGER_H
#include "abstractmanager.h"
#include "logixmanager.h"
#include "libPr3_global.h"

class DecimalFormat;
class Logix;
class LIBPR3SHARED_EXPORT DefaultLogixManager : public LogixManager
{
    Q_OBJECT
public:
    explicit DefaultLogixManager(QObject *parent = 0);
    int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter() ;
    /*public*/ Logix* createNewLogix(QString systemName, QString userName);
    /*public*/ Logix* createNewLogix(QString userName);
    /*public*/ void deleteLogix(Logix* x);
    /*public*/ void activateAllLogixs();
    /*public*/ Logix* getLogix(QString name);
    /*public*/ Logix* getBySystemName(QString name);
    /*public*/ NamedBean* getByUserName(QString key);
    /*public*/ void setLoadDisabled(bool s);
    /*public*/ bool getLoadDisabled();
    static DefaultLogixManager* _instance;// = NULL;
    static /*public*/ DefaultLogixManager* instance();

signals:
    //void newLogixCreated(Logix* );
public slots:
private:
    DecimalFormat* paddedNumber;// = new DecimalFormat("0000");

    int lastAutoLogixRef;// = 0;
    bool loadDisabled = false;
    Logger* log;
};

#endif // DEFAULTLOGIXMANAGER_H
