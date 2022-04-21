#ifndef ACTIONCLOCK_H
#define ACTIONCLOCK_H

#include "abstractdigitalaction.h"
#include "threadingutil.h"
#include "calendar.h"
#include "instancemanager.h"
#include "simpletimebase.h"

class ActionClock : public AbstractDigitalAction
{
  Q_OBJECT
 public:
   ActionClock(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  /*enum*/ class ClockState {
    public:
//      SetClock(Bundle.getMessage("ActionClock_SetClock")),
//      StartClock(Bundle.getMessage("ActionClock_StartClock")),
//      StopClock(Bundle.getMessage("ActionClock_StopClock"));
 enum STATE {SetClock, StartClock, StopClock};
//      private final String _text;

//      private ClockState(String text) {
//          this._text = text;
//      }

      //@Override
      /*public*/static  QString toString(STATE s) {
       switch (s) {
       case SetClock:return tr("Set Clock");
        case StartClock: return tr("Start clock");
         case StopClock: return tr("Stop clock");
       default:
        throw new IllegalArgumentException();
      }
    }
    /*public*/static STATE valueOf(QString s)
    {
     if(s == tr("Set Clock")) return SetClock;
     if(s == tr("Start clock")) return StartClock;
     if(s == tr("Stop clock")) return StopClock;
     throw new IllegalArgumentException();
    }
    /*public*/ static QList<STATE> values()
    {
     return QList<STATE>{SetClock, StartClock, StopClock};
    }
  };
   /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames)override;
   /*public*/  void setBeanState(ClockState::STATE state);
   /*public*/  ClockState::STATE getBeanState();
   /*public*/  void setClockTime(int minutes);
   /*public*/  int getClockTime();
   /*public*/  static QString formatTime(int minutes);
   /*public*/  Category* getCategory()override;
   /*public*/  void execute() /*throws JmriException*/override;
   /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
   /*public*/  int getChildCount()override;
   /*public*/  QString getShortDescription(QLocale locale)override;
   /*public*/  QString getLongDescription(QLocale locale)override;
   /*public*/  void setup()override;
   /*public*/  void registerListenersForThisClass()override;
   /*public*/  void unregisterListenersForThisClass()override;
   /*public*/  void disposeMe()override;

   QObject* self() override {return (QObject*)this;}
   QObject* bself() override {return (QObject*)this;}

private:
  /*private*/ ClockState::STATE _clockState = ClockState::SetClock;
  /*private*/ int _clockTime = 0;

};
class ActionClock_run : public ThreadActionWithJmriException
{
  Q_OBJECT
  ActionClock::ClockState::STATE theState;
  int _clockTime;
 public:
  ActionClock_run(int _clockTime, ActionClock::ClockState::STATE theState) {this->_clockTime = _clockTime, this->theState = theState;}
  void run()
  {
  switch(theState) {
      case ActionClock::ClockState::SetClock:
      {
          Calendar* cal = Calendar::getInstance();
          cal->setTime(((SimpleTimebase*)InstanceManager::getDefault("Timebase"))->getTime());
          cal->set(Calendar::HOUR_OF_DAY, _clockTime / 60);
          cal->set(Calendar::MINUTE, _clockTime % 60);
          cal->set(Calendar::SECOND, 0);
          ((SimpleTimebase*)InstanceManager::getDefault("Timebase"))->userSetTime(cal->getTime());
          break;
      }
      case ActionClock::ClockState::StartClock:
          ((SimpleTimebase*)InstanceManager::getDefault("Timebase"))->setRun(true);
          break;
      case ActionClock::ClockState::StopClock:
          ((SimpleTimebase*)InstanceManager::getDefault("Timebase"))->setRun(false);
          break;
      default:
          throw new IllegalArgumentException("Invalid clock state: " + ActionClock::ClockState::toString(theState));
   }
  }

};

#endif // ACTIONCLOCK_H
