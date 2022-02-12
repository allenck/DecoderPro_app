#ifndef LNTURNOUTMANAGER_H
#define LNTURNOUTMANAGER_H
#include "loconetinterface.h"
#include "abstractturnoutmanager.h"
#include "lntrafficcontroller.h"
//#include "providingmanager.h"
//class AbstractTurnoutManager;
class LIBPR3SHARED_EXPORT LnTurnoutManager : public AbstractTurnoutManager, public LocoNetListener
{
 Q_OBJECT
  Q_INTERFACES(LocoNetListener)
public:
    LnTurnoutManager(LnTrafficController* fastcontroller, LnTrafficController* throttledcontroller, QString prefix, bool mTurnoutNoRetry, QObject* parent = 0);
    /*public*/ LnTurnoutManager(LocoNetSystemConnectionMemo* memo, LocoNetInterface* throttledcontroller, bool mTurnoutNoRetry, QObject *parent = nullptr);
    void dispose() override;
    Turnout* createNewTurnout(QString systemName, QString userName) override;
    /*public*/ static /*final*/ QString BYPASSBUSHBYBITKEY;// = "Bypass Bushby Bit";
    /*public*/ static /*final*/ QString SENDONANDOFFKEY;// = "Send ON/OFF";
    /*public*/ QString getNamedBeanClass()const override {
        return "LnTurnout";
    }
    /*public*/ SystemConnectionMemo* getMemo() override {return AbstractManager::getMemo();}
    /*public*/ QString getDefaultThrownSpeed()const  override {return AbstractTurnoutManager::getDefaultThrownSpeed();}

    QObject* self() override { return (QObject*)this;}
   // /*public*/ QSet<NamedBean*> getNamedBeanSet() override {return AbstractManager::getNamedBeanSet();}
    /*public*/ Turnout* getBySystemName(QString name) override {return (Turnout*)AbstractManager::getBySystemName(name);}
    /*public*/ void addPropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::addPropertyChangeListener(l);}
    /*public*/ void removePropertyChangeListener(PropertyChangeListener* l) override{PropertyChangeSupport::removePropertyChangeListener(l);}
    /*public*/ QString getClosedText() override {return AbstractTurnoutManager::getClosedText();}
    /*public*/ QString getThrownText() override {return AbstractTurnoutManager::getThrownText();}
    /*public*/ QString getDefaultClosedSpeed() const override {return AbstractTurnoutManager::getDefaultClosedSpeed();}

public slots:
    // listen for turnouts, creating them as needed
    void message(LocoNetMessage* l) override;

private:
    LocoNetInterface* fastcontroller;
    LocoNetInterface* throttledcontroller;
    bool mTurnoutNoRetry = false;

    QString prefix;
    int address(int a1, int a2);
    // holds last seen turnout request for possible resend
    LocoNetMessage* lastSWREQ;


 Logger log;
 friend class LnTurnoutManagerTest;
};

#endif // LNTURNOUTMANAGER_H
