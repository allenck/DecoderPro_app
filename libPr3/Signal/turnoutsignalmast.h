#ifndef TURNOUTSIGNALMAST_H
#define TURNOUTSIGNALMAST_H
#include "abstractsignalmast.h"
#include "namedbeanhandle.h"
#include "instancemanager.h"
#include "abstractturnout.h"
#include <QList>

class Turnout;
class LIBPR3SHARED_EXPORT TurnoutSignalMast : public AbstractSignalMast
{
    Q_OBJECT
public:
    //explicit TurnoutSignalMast(QObject *parent = 0);
    /*public*/ TurnoutSignalMast(QString systemName, QString userName = "", QObject *parent = 0) ;
    void configureFromName(QString systemName) ;
    /*public*/ void setAspect(QString aspect);
    /*public*/ void setLit(bool state);
    /*public*/ QString getTurnoutName(QString appearance);
    /*public*/ int getTurnoutState(QString appearance);
    /*public*/ void setTurnout(QString appearance, QString turn, int state);
    /*public*/ void resetPreviousStates(bool boo);
    /*public*/ bool resetPreviousStates();

    /*static*/ class TurnoutAspect/* implements java.io.Serializable*/
    {
    public:
     NamedBeanHandle<Turnout*>* namedTurnout;
     int state;

     TurnoutAspect(QString turnoutName, int turnoutState)
     {
      state = 0;
      namedTurnout = NULL;
      if(turnoutName!="" )
      {
       Turnout* turn = ((ProxyTurnoutManager*) InstanceManager::turnoutManagerInstance())->getTurnout(turnoutName);
       namedTurnout = ((NamedBeanHandleManager*) InstanceManager::getDefault("NamedBeanHandleManager"))->getNamedBeanHandle(turnoutName, turn);
       state = turnoutState;
      }
     }

     Turnout* getTurnout()
     {
      if(namedTurnout==NULL)
       return NULL;
      return namedTurnout->getBean();
     }

     QString getTurnoutName()
     {
      if(namedTurnout==NULL)
       return "";
      return namedTurnout->getName();
     }

     int getTurnoutState()
     {
      return state;
     }
    };

    /*public*/ QList<NamedBeanHandle<Turnout*>* > getHeadsUsed();
    /*public*/ static int getLastRef();

signals:

public slots:
private:
    static int lastRef;// = 0;
 Logger* log;
 QHash<QString, TurnoutAspect*> turnouts;// =  QHash<QString, TurnoutAspect>();

 bool _resetPreviousStates;// = false;


};

#endif // TURNOUTSIGNALMAST_H
