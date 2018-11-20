#ifndef ABSTRACTSIGNALHEADMANAGER_H
#define ABSTRACTSIGNALHEADMANAGER_H
#include "abstractmanager.h"
#include <QCompleter>
#include "signalheadmanager.h"

class AbstractSignalHead;
class SignalHead;
class LIBPR3SHARED_EXPORT AbstractSignalHeadManager : public SignalHeadManager
{
    Q_OBJECT
public:
    explicit AbstractSignalHeadManager(QObject *parent = 0);
    /*public*/ int getXMLOrder();
    /*public*/ QString getSystemPrefix();
    /*public*/ char typeLetter();
    /*public*/ SignalHead* getSignalHead(QString name);
    /*public*/ SignalHead* getBySystemName(QString name);
    /*public*/ SignalHead* getByUserName(QString key);
    void Register(NamedBean *s);
    QCompleter* getCompleter(QString text, bool bIncludeUserNames = false);

signals:
    void newSignalHeadCreated(AbstractSignalHead*);
    void propertyChange(PropertyChangeEvent *e);
public slots:
friend class PropertyChangeSupport;
friend class VetoablePropertyChangeSupport;
};

#endif // ABSTRACTSIGNALHEADMANAGER_H
