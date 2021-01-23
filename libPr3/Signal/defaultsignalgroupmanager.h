#ifndef DEFAULTSIGNALGROUPMANAGER_H
#define DEFAULTSIGNALGROUPMANAGER_H
#include "signalgroupmanager.h"
#include "libPr3_global.h"

class InternalSystemConnectionMemo;
class LIBPR3SHARED_EXPORT DefaultSignalGroupManager : public SignalGroupManager
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit DefaultSignalGroupManager(QObject* parent = nullptr) : SignalGroupManager(parent) {}
    Q_INVOKABLE explicit DefaultSignalGroupManager(InternalSystemConnectionMemo* memo, QObject *parent = 0);
    ~DefaultSignalGroupManager() {}
    DefaultSignalGroupManager(const DefaultSignalGroupManager& other) : SignalGroupManager(other.memo) {}
    /*public*/ int getXMLOrder() const override;
    /*public*/ QString getSystemPrefix()const override;
    /*public*/ char typeLetter()const override;
    /*public*/ SignalGroup* getSignalGroup(QString name)override;
    /*public*/ SignalGroup* getBySystemName(QString key)const ;
    /*public*/ SignalGroup* getByUserName(QString key)const ;
    QT_DEPRECATED /*public*/ SignalGroup* newSignalGroup(QString userName)override;
    /*public*/ SignalGroup* newSignaGroupWithUserName(/*@Nonnull*/ QString userName);
    /*public*/ SignalGroup* provideSignalGroup(QString systemName, QString userName)override;
    QStringList getListOfNames();
    QT_DEPRECATED static /*public*/ DefaultSignalGroupManager* instance();
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
