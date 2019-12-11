#ifndef DEFAULTSIGNALGROUP_H
#define DEFAULTSIGNALGROUP_H
#include "signalgroup.h"
#include "namedbeanhandle.h"
#include "libPr3_global.h"

class SignalSensor;
class Turnout;
class Sensor;
class SignalHeadItem;
class SignalHead;
class SignalMast;
class LIBPR3SHARED_EXPORT DefaultSignalGroup : public SignalGroup
{
    Q_OBJECT
public:
    //explicit DefaultSignalGroup(QObject *parent = 0);
    /*public*/ DefaultSignalGroup(QString systemName, QString userName = "", QObject* parent = 0);
    /*public*/ void setEnabled(bool boo);
    /*public*/ bool getEnabled();
    /*public*/ void setSignalMast(QString pName);
    /*public*/ void setSignalMast(SignalMast* mMast, QString pName);
    /*public*/ SignalMast* getSignalMast();
    /*public*/ QString getSignalMastName();
    /*public*/ void addSignalMastAspect(QString aspect);
    /*public*/ bool isSignalMastAspectIncluded(QString aspect);
    /*public*/ void deleteSignalMastAspect(QString aspect);
    /*public*/ int getNumSignalMastAspects() ;
    /*public*/ QString getSignalMastAspectByIndex(int x);
    /*public*/ void clearSignalMastAspect();
    /*public*/ void addSignalHead(NamedBeanHandle<SignalHead*>* sh);
    /*public*/ void addSignalHead(QString pName);
    /*public*/ void addSignalHead(SignalHead* mHead);
    /*public*/ void setSignalHeadAlignTurnout(SignalHead* mHead, Turnout* mTurn, int state);
    /*public*/ void setSignalHeadAlignSensor(SignalHead* mHead, Sensor* mSen, int state);
    /*public*/ SignalHead* getSignalHeadItemBeanByIndex(int n);
    /*public*/ int getNumSignalHeadItems();
    /*public*/ int getSignalHeadOffState(SignalHead* bean);
    /*public*/ int getSignalHeadOnState(SignalHead* bean);
    /*public*/ int getSignalHeadOffStateByIndex(int n);
    /*public*/ void deleteSignalHead(SignalHead* pSignal);
    /*public*/ void deleteSignalHead(NamedBeanHandle<SignalHead*>* sh);
    /*public*/ void setSignalHeadOnState(SignalHead* head, int state);
    /*public*/ void setSignalHeadOffState(SignalHead* head, int state);
    /*public*/ bool isSignalIncluded(SignalHead* bean);
    /*public*/ bool isTurnoutIncluded(SignalHead* pSignal, Turnout* pTurnout);
    /*public*/ int getTurnoutState(SignalHead* pSignal, Turnout* pTurnout);
    /*public*/ int getTurnoutStateByIndex(int x, Turnout* pTurnout);
    /*public*/ int getTurnoutStateByIndex(int x, int pTurnout);
    /*public*/ QString getTurnoutNameByIndex(int x, int pTurnout);
    /*public*/ Turnout* getTurnoutByIndex(int x, int pTurnout);
    /*public*/ int getSensorStateByIndex(int x, int pSensor);
    /*public*/ QString getSensorNameByIndex(int x, int pSensor);
    /*public*/ Sensor* getSensorByIndex(int x, int pSensor);
    /*public*/ bool isSensorIncluded(SignalHead* pSignal, Sensor* pSensor);
    /*public*/ int getSensorState(SignalHead* pSignal, Sensor* pSensor);
    /*public*/ bool getSensorTurnoutOper(SignalHead* pSignal);
    /*public*/ bool getSensorTurnoutOperByIndex(int x);
    /*public*/ void setSensorTurnoutOper(SignalHead* pSignal, bool boo);
    /*public*/ void clearSignalTurnout(SignalHead* pSignal);
    /*public*/ void clearSignalSensor(SignalHead* pSignal);
    /*public*/ int getNumSignalHeadSensorsByIndex(int x);
    /*public*/ int getNumSignalHeadTurnoutsByIndex(int x);
    /*public*/ int getSignalHeadOnStateByIndex(int n);
    /*public*/ QString getSignalHeadItemNameByIndex(int n);
    /*public*/ int getState();
    /*public*/ void setState(int state);
    /*public*/ /*synchronized*/ int getNumPropertyChangeListeners();
    /*public*/ /*synchronized*/ QVector<PropertyChangeListener*> getPropertyChangeListeners();
    /*public*/ /*synchronized*/ void addPropertyChangeListener(PropertyChangeListener* l);
    /*public*/ /*synchronized*/ void removePropertyChangeListener(PropertyChangeListener* l);

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
PropertyChangeSupport* pcs;// = new PropertyChangeSupport(this);
/*private*/ SignalHeadItem* getSignalHeadItem(QString name);
/*private*/ SignalHeadItem* getSignalHeadItem(NamedBean* bean);
/*private*/ void resetHeads();
/*private*/ void setHead();
/*private*/ SignalHeadItem* getSignalHeadItemByIndex(int n);

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
