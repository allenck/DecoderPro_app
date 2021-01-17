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
    /*public*/ int getXMLOrder()const override;
//    /*public*/ QString getSystemPrefix()const override;
    /*public*/ char typeLetter()const override ;
    /*public*/ SignalHead* getSignalHead(QString name) override;
    /*public*/ SignalHead* getBySystemName(QString name) const override;
    /*public*/ SignalHead* getByUserName(QString key) const override;
    void Register(NamedBean *s)const override;
    QCompleter* getCompleter(QString text, bool bIncludeUserNames = false) override;
    /*public*/ QString getBeanTypeHandled(bool plural);
    /*public*/ QString getNamedBeanClass()const override {
        return "SignalHead";
    }

signals:
    void newSignalHeadCreated(AbstractSignalHead*);
    void propertyChange(PropertyChangeEvent *e) override;
public slots:
friend class PropertyChangeSupport;
friend class VetoablePropertyChangeSupport;
};

#endif // ABSTRACTSIGNALHEADMANAGER_H
