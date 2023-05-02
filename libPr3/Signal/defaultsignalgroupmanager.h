#ifndef DEFAULTSIGNALGROUPMANAGER_H
#define DEFAULTSIGNALGROUPMANAGER_H
#include "signalgroupmanager.h"
#include "libPr3_global.h"

class InternalSystemConnectionMemo;
class LIBPR3SHARED_EXPORT DefaultSignalGroupManager : public AbstractManager, public SignalGroupManager
{
    Q_OBJECT
    Q_INTERFACES(SignalGroupManager)
public:
    Q_INVOKABLE explicit DefaultSignalGroupManager(QObject* parent = nullptr) : AbstractManager(parent) {}
    Q_INVOKABLE explicit DefaultSignalGroupManager(InternalSystemConnectionMemo* memo, QObject *parent = 0);
    ~DefaultSignalGroupManager() {}
    DefaultSignalGroupManager(const DefaultSignalGroupManager& other) : AbstractManager(other.memo) {}
    /*public*/ int getXMLOrder() const override;
    /*public*/ QString getSystemPrefix() const override;
    /*public*/ QChar typeLetter() const override;
    /*public*/ SignalGroup* getSignalGroup(QString name)override;
    /*public*/ SignalGroup* getBySystemName(QString key)const override;
    /*public*/ SignalGroup* getByUserName(QString key)const override;
    QT_DEPRECATED /*public*/ SignalGroup* newSignaGroupWithUserName(QString userName)override;
    /*public*/ SignalGroup* newSignalGroupWithUserName(/*@Nonnull*/ QString userName)override;
    /*public*/ SignalGroup* provideSignalGroup(QString systemName, QString userName)override;
    QStringList getListOfNames();
    QT_DEPRECATED static /*public*/ DefaultSignalGroupManager* instance();
    /*public*/ void deleteSignalGroup(SignalGroup* s)override;
    /*public*/ QString getNamedBeanClass()const override {
        return "SignalGroup";
    }
    DefaultSignalGroupManager* _instance() {return new DefaultSignalGroupManager();}
    /*public*/ virtual QStringList getSystemNameList() override {return AbstractManager::getSystemNameList();}
    /*public*/ virtual void addPropertyChangeListener(/*QNullable*/ PropertyChangeListener* listener) override{return AbstractManager::addPropertyChangeListener(listener);}

    QObject* pself() override{return (QObject*)this;}
    QObject* mself() override{return (QObject*)this;}
    QObject* vself() override{return (QObject*)this;}

signals:

public slots:
private:
    Logger* log;
};
Q_DECLARE_METATYPE(DefaultSignalGroupManager)
#endif // DEFAULTSIGNALGROUPMANAGER_H
