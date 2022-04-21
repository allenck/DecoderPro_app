#ifndef DEFAULTSIGNALGROUP_H
#define DEFAULTSIGNALGROUP_H
#include "signalgroup.h"
#include "namedbeanhandle.h"
#include "libPr3_global.h"
#include "propertychangelistener.h"
#include "abstractnamedbean.h"

class SignalSensor;
class Turnout;
class Sensor;
class SignalHeadItem;
class SignalHead;
class SignalMast;
class LIBPR3SHARED_EXPORT DefaultSignalGroup : public SignalGroup, public PropertyChangeListener
{
    Q_OBJECT
    Q_INTERFACES(PropertyChangeListener)
public:
    //explicit DefaultSignalGroup(QObject *parent = 0);
    /*public*/ DefaultSignalGroup(QString systemName, QString userName = "", QObject* parent = 0);
    /*public*/ void setEnabled(bool boo) override;
    /*public*/ bool getEnabled()override;
    /*public*/ void setSignalMast(QString pName)override;
    /*public*/ void setSignalMast(SignalMast* mMast, QString pName)override;
    /*public*/ SignalMast* getSignalMast() override;
    /*public*/ QString getSignalMastName() override;
    /*public*/ void addSignalMastAspect(QString aspect) override;
    /*public*/ bool isSignalMastAspectIncluded(QString aspect) override;
    /*public*/ void deleteSignalMastAspect(QString aspect) override;
    /*public*/ int getNumSignalMastAspects() override;
    /*public*/ QString getSignalMastAspectByIndex(int x) override;
    /*public*/ void clearSignalMastAspect()override;
    /*public*/ void addSignalHead(NamedBeanHandle<SignalHead*>* sh) override;
    /*public*/ void addSignalHead(QString pName);
    /*public*/ void addSignalHead(SignalHead* mHead)override;
    /*public*/ void setHeadAlignTurnout(SignalHead* mHead, Turnout* mTurn, int state)override;
    /*public*/ void setHeadAlignSensor(SignalHead* mHead, Sensor* mSen, int state)override;
    /*public*/ SignalHead* getHeadItemBeanByIndex(int n)override;
    /*public*/ int getNumHeadItems()override;
    /*public*/ int getHeadOffState(SignalHead* bean)override;
    /*public*/ int getHeadOnState(SignalHead* bean)override;
    /*public*/ int getHeadOffStateByIndex(int n)override;
    /*public*/ void deleteSignalHead(SignalHead* pSignal)override;
    /*public*/ void deleteSignalHead(NamedBeanHandle<SignalHead*>* sh)override;
    /*public*/ void setHeadOnState(SignalHead* head, int state)override;
    /*public*/ void setHeadOffState(SignalHead* head, int state)override;
    /*public*/ bool isHeadIncluded(SignalHead* bean)override;
    /*public*/ bool isTurnoutIncluded(SignalHead* pSignal, Turnout* pTurnout)override;
    /*public*/ int getTurnoutState(SignalHead* pSignal, Turnout* pTurnout)override;
    /*public*/ int getTurnoutStateByIndex(int x, Turnout* pTurnout)override;
    /*public*/ int getTurnoutStateByIndex(int x, int pTurnout)override;
    /*public*/ QString getTurnoutNameByIndex(int x, int pTurnout)override;
    /*public*/ Turnout* getTurnoutByIndex(int x, int pTurnout)override;
    /*public*/ int getSensorStateByIndex(int x, int pSensor) override;
    /*public*/ QString getSensorNameByIndex(int x, int pSensor) override;
    /*public*/ Sensor* getSensorByIndex(int x, int pSensor) override;
    /*public*/ bool isSensorIncluded(SignalHead* pSignal, Sensor* pSensor) override;
    /*public*/ int getSensorState(SignalHead* pSignal, Sensor* pSensor) override;
    /*public*/ bool getSensorTurnoutOper(SignalHead* pSignal) override;
    /*public*/ bool getSensorTurnoutOperByIndex(int x) override;
    /*public*/ void setSensorTurnoutOper(SignalHead* pSignal, bool boo) override;
    /*public*/ void clearSignalTurnout(SignalHead* pSignal) override;
    /*public*/ void clearSignalSensor(SignalHead* pSignal) override;
    /*public*/ int getNumHeadSensorsByIndex(int x)override;
    /*public*/ int getNumHeadTurnoutsByIndex(int x)override;
    /*public*/ int getHeadOnStateByIndex(int n)override;
    /*public*/ QString getHeadItemNameByIndex(int n)override;
    /*public*/ int getState()override;
    /*public*/ void setState(int state)override;
    /*public*/ /*synchronized*/ int getNumPropertyChangeListeners()override;
    /*public*/ /*synchronized*/ QVector<PropertyChangeListener*> getPropertyChangeListeners();
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l)override;
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l)override;
    QObject* self() override {return (QObject*)this;}
    QObject* pself() override{return (QObject*)this;}
    /*public*/ QList<NamedBeanUsageReport*>* getUsageReport(NamedBean* bean) override;

signals:

public slots:
    /*public*/ void propertyChange(PropertyChangeEvent* e);
private:
    /*private*/ NamedBeanHandle<SignalMast*>* _signalMast;

    QStringList _signalMastAppearances;// = new ArrayList<String>();
    /*private*/ bool headactive;//=false;

    /*private*/ bool enabled;//=true;
Logger* log;
QList <SignalHeadItem*> _signalHeadItem;// = new QList<SignalHeadItem>();
SwingPropertyChangeSupport* pcs;// = new SwingPropertyChangeSupport(this, nullptr);
/*private*/ SignalHeadItem* getHeadItem(QString name);
/*private*/ SignalHeadItem* getHeadItem(NamedBean* bean);
/*private*/ void resetHeads();
/*private*/ void setHead();
/*private*/ SignalHeadItem* getHeadItemByIndex(int n);

protected:
/*protected*/ void firePropertyChange(QString p, QVariant old, QVariant n);

};

/*private*/ /*static*/ class SignalHeadItem : public QObject //java.io.Serializable
{
 Q_OBJECT
public:

 SignalHeadItem(NamedBeanHandle<SignalHead*>* sh);
 /*public*/ QString getName();
 /*public*/ SignalHead* getSignal();
 /*public*/ void setOnAppearance(int app);
 /*public*/ int getOnAppearance();
 /*public*/ void setOffAppearance(int app);
 /*public*/ int getOffAppearance();
 /*public*/ bool getSensorTurnoutOper();
 /*public*/ void setSensorTurnoutOper(bool boo) ;
 /*public*/ bool checkActive();
 /*private*/ /*static*/ class SignalTurnout /*implements java.io.Serializable*/
 {
  NamedBeanHandle<Turnout*>* _turnout;
  int _state;
  Logger* log;
public:
  SignalTurnout(Turnout* turn, int state);
  QString getName();
  bool setState(int state);
  int getState() ;
  Turnout* getTurnout() ;
 };

 void addTurnout(Turnout* turn, int state);
 Turnout* getTurnout(int x);
 int getTurnoutState(Turnout* turn);
 int getNumTurnouts();
 QString getTurnoutName(int x);
 int getTurnoutState(int x);
 bool isTurnoutIncluded(Turnout* pTurnout);
 void clearSignalTurnouts();
 void clearSignalSensors();
 void addSensor(Sensor* sen, int state);
 int getSensorState(Sensor* sen);
 int getNumSensors();
 QString getSensorName(int x);
 Sensor* getSensor(int x);
 int getSensorState(int x);
 bool isSensorIncluded(Sensor* pSensor);
private:
 /*private*/ NamedBeanHandle<SignalHead*>* namedHead;
 /*private*/ int onAppearance;// = 0x00;
 /*private*/ int offAppearance;// = 0x00;
 //Used to determine if we are using an AND or OR when testing the Sensors and Signals
 /*private*/ bool turnoutSensorOper;// = true;
 QList <SignalTurnout*>* _signalTurnoutList;// = new QList<SignalTurnout*>();
 /*private*/ /*static*/ class SignalSensor
 {
  NamedBeanHandle<Sensor*>* _Sensor;
  int _state;
  Logger* log;
 public:
  SignalSensor(Sensor* sen, int state);
  QString getName();
  bool setState(int state);
  int getState();
  Sensor* getSensor();
 };
 QList <SignalSensor*>* _signalSensorList;// = new QList<SignalSensor*>();
 Logger* log;

};
#endif // DEFAULTSIGNALGROUP_H
