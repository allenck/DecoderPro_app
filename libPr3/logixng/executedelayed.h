#ifndef EXECUTEDELAYED_H
#define EXECUTEDELAYED_H

#include "abstractdigitalaction.h"
#include "femalesocketlistener.h"
#include "namedbeanaddressing.h"
#include "defaultfemaledigitalactionsocket.h"
#include "timerunit.h"
#include "conditionalng.h"
#include "protectedtimertask.h"
#include "system.h"
#include "runtimeexception.h"
#include "defaultsymboltable.h"

class IFSFemaleSocketListener;
class InternalFemaleSocket;
class FemaleDigitalActionSocket;
class ProtectedTimerTask;
class ExpressionNode;
class ExecuteDelayed : public AbstractDigitalAction, public FemaleSocketListener
{
  Q_OBJECT
  Q_INTERFACES(FemaleSocketListener)
 public:
  explicit ExecuteDelayed(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/override;
  /*public*/  Category* getCategory()override;
  /*public*/  void execute() /*throws JmriException*/ override;
  /*public*/  void setDelayAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/;
  /*public*/  NamedBeanAddressing::TYPE getDelayAddressing();
  /*public*/  int getDelay();
  /*public*/  void setDelay(int delay);
  /*public*/  void setDelayReference(/*@Nonnull */QString reference);
  /*public*/  QString getDelayReference();
  /*public*/  void setDelayLocalVariable(/*@Nonnull*/ QString localVariable);
  /*public*/  QString getDelayLocalVariable();
  /*public*/  void setDelayFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/;
  /*public*/  QString getDelayFormula();
  /*public*/  TimerUnit::VAL getUnit();
  /*public*/  void setUnit(TimerUnit::VAL unit);
  /*public*/  bool getResetIfAlreadyStarted();
  /*public*/  void setResetIfAlreadyStarted(bool resetIfAlreadyStarted);
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ override;
  /*public*/  int getChildCount() override;
  /*public*/  void connected(FemaleSocket* socket) override;
  /*public*/  void disconnected(FemaleSocket* socket)  override;
  /*public*/  QString getShortDescription(QLocale locale) override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleDigitalActionSocket* getSocket();
  /*public*/  QString getSocketSystemName() ;
  /*public*/  void setSocketSystemName(QString systemName);
  /*public*/  void setup() override;
  /*public*/  void registerListenersForThisClass() override;
  /*public*/  void unregisterListenersForThisClass() override;
  /*public*/  void disposeMe() override;

 private:
  static Logger* log;
  /*private*/ QString _socketSystemName;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _socket;
  /*private*/ ProtectedTimerTask* _timerTask;
  /*private*/ NamedBeanAddressing::TYPE _stateAddressing = NamedBeanAddressing::Direct;
  /*private*/ int _delay;
  /*private*/ QString _stateReference = "";
  /*private*/ QString _stateLocalVariable = "";
  /*private*/ QString _stateFormula = "";
  /*private*/ ExpressionNode* _stateExpressionNode;
  /*private*/ TimerUnit::VAL _unit = TimerUnit::MilliSeconds;
  /*private*/ bool _resetIfAlreadyStarted;
  QMutex mutex1;
  class IFSFemaleSocketListener : public FemaleSocketListener
  {
    //Q_OBJECT
   public:
    IFSFemaleSocketListener() {}
    //@Override
    /*public*/ void connected(FemaleSocket* socket) {
        // Do nothing
    }

    //@Override
    /*public*/ void disconnected(FemaleSocket* socket) {
        // Do nothing
    }
    friend class EDProtectedTimerTask;

  };

  /*private*/ class InternalFemaleSocket : DefaultFemaleDigitalActionSocket {

      /*private*/ ConditionalNG* conditionalNG;
      /*private*/ SymbolTable* newSymbolTable;
      ExecuteDelayed* ed;
      public:
      /*public*/ InternalFemaleSocket(ExecuteDelayed* ed) : DefaultFemaleDigitalActionSocket(nullptr, new IFSFemaleSocketListener(), "A")
      {
//          super(null, new FemaleSocketListener(){
//              @Override
//              public void connected(FemaleSocket socket) {
//                  // Do nothing
//              }

//              @Override
//              public void disconnected(FemaleSocket socket) {
//                  // Do nothing
//              }
//          }
//                , "A");
       this->ed = ed;
      }

      //@Override
      /*public*/ void execute() /*throws JmriException*/ {
          if (ed->_socket != nullptr) {
              SymbolTable* oldSymbolTable = conditionalNG->getSymbolTable();
              conditionalNG->setSymbolTable(newSymbolTable);
              ed->_socket->execute();
              conditionalNG->setSymbolTable(oldSymbolTable);
          }
      }
   friend class EDProtectedTimerTask;
  };
  /*private*/ /*final*/ InternalFemaleSocket* _internalSocket = new InternalFemaleSocket(this);
  /*private*/ ProtectedTimerTask* getNewTimerTask(ConditionalNG* conditionalNG) /*throws JmriException*/;


  // These variables are used internally in this action
  /*private*/ long _timerDelay = 0;   // Timer delay in milliseconds
  /*private*/ long _timerStart = 0;   // Timer start in milliseconds
  /*private*/ void parseDelayFormula() /*throws ParserException*/ ;
  /*private*/ long getNewDelay() /*throws JmriException*/;
  /*private*/ void scheduleTimer(ConditionalNG* conditionalNG, long delay) /*throws JmriException*/;

 protected:
  /*protected*/ /*final*/ QList<VariableData*> _localVariables = QList<VariableData*>();

  friend class EDProtectedTimerTask;
};

class EDProtectedTimerTask : public ProtectedTimerTask
{
  Q_OBJECT
  ExecuteDelayed* ed;
  ConditionalNG* conditionalNG;
  DefaultSymbolTable* newSymbolTable;
 public:
  EDProtectedTimerTask(ConditionalNG* conditionalNG, DefaultSymbolTable* newSymbolTable, ExecuteDelayed* ed) {
   this->conditionalNG = conditionalNG; this->newSymbolTable = newSymbolTable, this->ed = ed;}
  //@Override
  /*public*/  void execute() {
      try {
          /*synchronized(ExecuteDelayed.this) */{
              ed->_timerTask = nullptr;
              long currentTimerTime = System::currentTimeMillis() - ed->_timerStart;
              if (currentTimerTime < ed->_timerDelay) {
                  ed->scheduleTimer(conditionalNG, ed->_timerDelay - currentTimerTime);
              } else {
                  ed->_internalSocket->conditionalNG = conditionalNG;
                  ed->_internalSocket->newSymbolTable = newSymbolTable;
                  conditionalNG->execute(ed->_internalSocket);
              }
          }
      }
      catch (RuntimeException* e) {
          ed->log->error("Exception thrown", e);
      }
      catch ( JmriException* e) {
          ed->log->error("Exception thrown", e);
}
  }
};

#endif // EXECUTEDELAYED_H
