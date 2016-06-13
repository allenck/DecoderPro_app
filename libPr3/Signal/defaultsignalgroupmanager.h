#ifndef DEFAULTSIGNALGROUPMANAGER_H
#define DEFAULTSIGNALGROUPMANAGER_H
#include "signalgroupmanager.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DefaultSignalGroupManager : public SignalGroupManager
{
    Q_OBJECT
public:
    explicit DefaultSignalGroupManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();
    /*public*/ SignalGroup* getSignalGroup(QString name);
    /*public*/ SignalGroup* getBySystemName(QString key);
    /*public*/ SignalGroup* getByUserName(QString key);
    /*public*/ SignalGroup* newSignalGroup(QString sys);
    /*public*/ SignalGroup* provideSignalGroup(QString systemName, QString userName);
    QStringList getListOfNames();
    static DefaultSignalGroupManager* _instance;// = NULL;
    static /*public*/ DefaultSignalGroupManager* instance();
    /*public*/ void deleteSignalGroup(SignalGroup* s);

signals:

public slots:
private:
    Logger* log;
};

#endif // DEFAULTSIGNALGROUPMANAGER_H
