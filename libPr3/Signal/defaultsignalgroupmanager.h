#ifndef DEFAULTSIGNALGROUPMANAGER_H
#define DEFAULTSIGNALGROUPMANAGER_H
#include "signalgroupmanager.h"
#include "libPr3_global.h"

class LIBPR3SHARED_EXPORT DefaultSignalGroupManager : public SignalGroupManager
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultSignalGroupManager(QObject *parent = 0);
    ~DefaultSignalGroupManager() {}
    DefaultSignalGroupManager(const DefaultSignalGroupManager&) : SignalGroupManager() {}
    /*public*/ int getXMLOrder() const override;
    /*public*/ QString getSystemPrefix()const override;
    /*public*/ char typeLetter()const override;
    /*public*/ SignalGroup* getSignalGroup(QString name)override;
    /*public*/ SignalGroup* getBySystemName(QString key)const ;
    /*public*/ SignalGroup* getByUserName(QString key)const ;
    /*public*/ SignalGroup* newSignalGroup(QString sys)override;
    /*public*/ SignalGroup* provideSignalGroup(QString systemName, QString userName)override;
    QStringList getListOfNames();
    static DefaultSignalGroupManager* _instance;// = NULL;
    static /*public*/ DefaultSignalGroupManager* instance();
    /*public*/ void deleteSignalGroup(SignalGroup* s)override;
    /*public*/ QString getNamedBeanClass()const override {
        return "SignalGroup";
    }

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(DefaultSignalGroupManager)
#endif // DEFAULTSIGNALGROUPMANAGER_H
