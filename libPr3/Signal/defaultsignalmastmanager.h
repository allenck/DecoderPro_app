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
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix() ;
    /*public*/ char typeLetter() ;
    /*public*/ SignalMast* getSignalMast(QString name) ;
    /*public*/ SignalMast* provideSignalMast(QString prefix, // nominally IF$shsm
                                        QString signalSystem,
                                        QString mastName,
                                        QStringList heads) ;
    /*public*/ SignalMast* provideSignalMast(QString name);
    /*public*/ SignalMast* getBySystemName(QString key) ;
    /*public*/ SignalMast* getByUserName(QString key);
#if 1
    /*public*/ void addRepeater(SignalMastRepeater* rp) throw (JmriException);
    /*public*/ void removeRepeater(SignalMastRepeater* rp);
    /*public*/ QList<SignalMastRepeater*>* getRepeaterList();
    /*public*/ void initialiseRepeaters();
#endif
    /*public*/ SignalMast* provide(QString name) throw (IllegalArgumentException) override;

signals:
    void newSignalMastCreated(AbstractSignalMast*);
    void propertyChange(PropertyChangeEvent *e);
public slots:
private:
    QList<SignalMastRepeater*>* repeaterList;// = new QList<SignalMastRepeater*>();
    /*private*/ QString parenQuote(QString in);
    Logger* log;
    friend class PropertyChangeSupport;
};
Q_DECLARE_METATYPE(DefaultSignalMastManager)
#endif // DEFAULTSIGNALMASTMANAGER_H
