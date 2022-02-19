#ifndef ABSTRACTSIGNALHEADMANAGER_H
#define ABSTRACTSIGNALHEADMANAGER_H
#include "abstractmanager.h"
#include <QCompleter>
#include "signalheadmanager.h"

class InternalSystemConnectionMemo;
class AbstractSignalHead;
class SignalHead;
class LIBPR3SHARED_EXPORT AbstractSignalHeadManager : public AbstractManager, public SignalHeadManager
{
    Q_OBJECT
  Q_INTERFACES(SignalHeadManager)
public:
    explicit AbstractSignalHeadManager(InternalSystemConnectionMemo* memo, QObject *parent = 0);
    /*public*/ int getXMLOrder()const override;
//    /*public*/ QString getSystemPrefix()const override;
    /*public*/ QChar typeLetter() const override ;
    /*public*/ SignalHead* getSignalHead(QString name) override;
    /*public*/ SignalHead* getBySystemName(QString name)
    {
     return (SignalHead*) AbstractManager::getBeanBySystemName(name);
    }
    /*public*/ SignalHead* getByUserName(QString key)
    {
     return (SignalHead*) AbstractManager::getByUserName(key);
    }
//    void Register(NamedBean *s) override;
//    QCompleter* getCompleter(QString text, bool bIncludeUserNames = false) override;
    /*public*/ QString getBeanTypeHandled(bool plural) const override;
    /*public*/ QString getNamedBeanClass()const override {
        return "SignalHead";
    }
  /*public*/ SystemConnectionMemo* getMemo() override;

    QObject* self() override{return (QObject*)this;}
    QObject* vself() override {return (QObject*)this;}

//    /*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}
//    /*public*/ SignalHead* getBySystemName(QString name) override {return (SignalHead*)AbstractManager::getBySystemName(name);}
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::addPropertyChangeListener(l);}
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::removePropertyChangeListener(l);}

signals:
    void newSignalHeadCreated(AbstractSignalHead*);
    void propertyChange(PropertyChangeEvent *e) override;
public slots:

 private:
    /*final*/ void init();

friend class SwingPropertyChangeSupport;
friend class VetoableSwingPropertyChangeSupport;
};

#endif // ABSTRACTSIGNALHEADMANAGER_H
