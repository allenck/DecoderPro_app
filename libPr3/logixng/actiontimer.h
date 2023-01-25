#ifndef ACTIONTIMER_H
#define ACTIONTIMER_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"
#include "timerunit.h"
#include "femaledigitalactionsocket.h"
#include "protectedtimertask.h"
#include "system.h"
#include "conditionalng.h"

class ProtectedTimerTask;
class ActionEntry;
class FemaleDigitalExpressionSocket;
class ActionTimer : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
  /*private*/ /*static*/ class ActionEntry {
      /*private*/ int _delay;
      /*private*/ QString _socketSystemName;
      /*private*/ /*final*/ FemaleDigitalActionSocket* _socket;

      /*private*/ ActionEntry(int delay, FemaleDigitalActionSocket* socket, QString socketSystemName) {
          _delay = delay;
          _socketSystemName = socketSystemName;
          _socket = socket;
      }

      /*private*/ ActionEntry(FemaleDigitalActionSocket* socket) {
          this->_socket = socket;
      }
      friend class ActionTimer;
  };
 public:
  ActionTimer(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  static /*final*/ int EXPRESSION_START;// = 0;
  /*public*/  static /*final*/ int EXPRESSION_STOP;// = 1;
  /*public*/  static /*final*/ int NUM_STATIC_EXPRESSIONS;// = 2;
  /*public*/  /*static*/ class ActionData {
      /*private*/ int _delay;
      /*private*/ QString _socketName;
      /*private*/ QString _socketSystemName;
      public:
      /*public*/  ActionData(int delay, QString socketName, QString socketSystemName) {
          _delay = delay;
          _socketName = socketName;
          _socketSystemName = socketSystemName;
      }
   friend class ActionTimer;
  };
  /*public*/ ActionTimer(QString sys, QString user,
          QList<QMap<QString, QString>> expressionSystemNames,
          QList<ActionData*> actionDataList, QObject *parent = nullptr)
          /*throws BadUserNameException, BadSystemNameException*/;
  /*public*/  Base* getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/override;
  /*public*/  Category getCategory()override;
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  int getDelay(int actionSocket);
  /*public*/  void setDelay(int actionSocket, int delay);
  /*public*/  bool getStartImmediately();
  /*public*/  void setStartImmediately(bool startImmediately);
  /*public*/  bool getRunContinuously();
  /*public*/  void setRunContinuously(bool runContinuously);
  /*public*/  TimerUnit::VAL getUnit();
  /*public*/  void setUnit(TimerUnit::VAL unit) ;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale)override;;
  /*public*/  FemaleDigitalExpressionSocket* getStartExpressionSocket();
  /*public*/  QString getStartExpressionSocketSystemName();
  /*public*/  void setStartExpressionSocketSystemName(QString systemName) ;
  /*public*/  FemaleDigitalExpressionSocket* getStopExpressionSocket();
  /*public*/  QString getStopExpressionSocketSystemName();
  /*public*/  void setStopExpressionSocketSystemName(QString systemName);
  /*public*/  int getNumActions();
  /*public*/  void setNumActions(int num);
  /*public*/  FemaleDigitalActionSocket* getActionSocket(int socket);
  /*public*/  QString getActionSocketSystemName(int socket);
  /*public*/  void setActionSocketSystemName(int socket, QString systemName);
  /*public*/  void setup()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void disposeMe()override;

 private:
  static Logger* log;
  /*private*/ QString _startExpressionSocketSystemName;
  /*private*/ QString _stopExpressionSocketSystemName;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _startExpressionSocket;
  /*private*/ /*final*/ FemaleDigitalExpressionSocket* _stopExpressionSocket;
  /*private*/ /*final*/ QList<ActionEntry*> _actionEntries = QList<ActionEntry*>();
  /*private*/ ProtectedTimerTask* _timerTask = nullptr;
  /*private*/ int _currentTimer = -1;
  /*private*/ enum TimerState {
      Off,
      RunNow,
      WaitToRun,
      Running,
      Completed,
  };
  /*private*/ TimerState _timerState = TimerState::Off;
  /*private*/ bool _startImmediately = false;
  /*private*/ bool _runContinuously = false;
  /*private*/ TimerUnit::VAL _unit = TimerUnit::MilliSeconds;
  /*private*/ long _currentTimerDelay = 0;
  /*private*/ long _currentTimerStart = 0;
  /*private*/ bool _startIsActive = false;
  /*private*/ void setActionData(QList<ActionData*> actionDataList);
  /*private*/ ProtectedTimerTask* getNewTimerTask() ;
  /*private*/ void scheduleTimer(long delay);
  /*private*/ void schedule();
  /*private*/ bool start() /*throws JmriException*/;
  /*private*/ bool checkStart() /*throws JmriException*/ ;
  /*private*/ bool stop() /*throws JmriException*/;
  QMutex mutex1;
  QMutex mutex2;
  QMutex mutex3;
  QMutex mutex4;
  QMutex mutex5;
  QMutex mutex6;

  friend class ActionTimer_ProtectedTimerTask;
};

class ActionTimer_ProtectedTimerTask : public ProtectedTimerTask
{
  Q_OBJECT
  ActionTimer* actionTimer;
  //@Override

 public:
  ActionTimer_ProtectedTimerTask(ActionTimer* actionTimer) {this->actionTimer = actionTimer;}
  /*public*/  void execute() {
      try {
          long currentTimerTime = System::currentTimeMillis() - actionTimer->_currentTimerStart;
          if (currentTimerTime < actionTimer->_currentTimerDelay) {
              actionTimer->scheduleTimer(actionTimer->_currentTimerDelay - currentTimerTime);
          } else {
              actionTimer->_timerState = ActionTimer::TimerState::Completed;
              actionTimer->getConditionalNG()->execute();
          }
      } catch (Exception* e) {
          actionTimer->log->error("Exception thrown", e);
      }
  }
};

#endif // ACTIONTIMER_H
