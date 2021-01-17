#ifndef DEFAULTSIGNALMASTMANAGER_H
#define DEFAULTSIGNALMASTMANAGER_H
#include "signalmastmanager.h"
#include "exceptions.h"
#include "libPr3_global.h"

class SignalMastRepeater;
class SignalMast;
class SignalHeadSignalMast;
class AbstractSignalMast;
class SignalMastRepeater;
class LIBPR3SHARED_EXPORT DefaultSignalMastManager : public SignalMastManager
{
    Q_OBJECT
public:
    explicit DefaultSignalMastManager(QObject *parent = 0);
    ~DefaultSignalMastManager() {}
    DefaultSignalMastManager(const DefaultSignalMastManager&) : SignalMastManager() {}
    /*public*/ int getXMLOrder()const  override;
    /*public*/ QString getSystemPrefix()const override ;
    /*public*/ char typeLetter() const override ;
    /*public*/ SignalMast* getSignalMast(QString name) override ;
    /*public*/ SignalMast* provideSignalMast(QString prefix, // nominally IF$shsm
                                        QString signalSystem,
                                        QString mastName,
                                        QStringList heads)  override;
    /*public*/ SignalMast* provideSignalMast(QString name) override;
    /*public*/ SignalMast* getBySystemName(QString key) const override;
    /*public*/ SignalMast* getByUserName(QString key) const override;
#if 1
    /*public*/ void addRepeater(SignalMastRepeater* rp) throw (JmriException);
    /*public*/ void removeRepeater(SignalMastRepeater* rp);
    /*public*/ QList<SignalMastRepeater*>* getRepeaterList();
    /*public*/ void initialiseRepeaters();
#endif
    /*public*/ SignalMast* provide(QString name) throw (IllegalArgumentException) override;
    /*public*/ QString getNamedBeanClass()const override {
        return "SignalMast";
    }

signals:
    void newSignalMastCreated(AbstractSignalMast*);
    void propertyChange(PropertyChangeEvent *e) override;
public slots:
private:
    QList<SignalMastRepeater*>* repeaterList;// = new QList<SignalMastRepeater*>();
    /*private*/ QString parenQuote(QString in);
    Logger* log;
    friend class PropertyChangeSupport;
};
Q_DECLARE_METATYPE(DefaultSignalMastManager)
#endif // DEFAULTSIGNALMASTMANAGER_H
