#ifndef DEFAULTCONDITIONALNG_H
#define DEFAULTCONDITIONALNG_H

#include "abstractbase.h"
#include "femalesocketlistener.h"
#include "conditionalng.h"
#include "executelock.h"
#include "defaultstack.h"
#include "threadingutil.h"

class ExecuteTask;
class DefaultConditionalNG : public AbstractBase, public  ConditionalNG, public FemaleSocketListener
{
 Q_OBJECT
  Q_INTERFACES(ConditionalNG FemaleSocketListener)
 public:
  explicit DefaultConditionalNG(QString sys, QString user, QObject *parent = nullptr);
  /*public*/  DefaultConditionalNG(QString sys, QString user, int threadID, QObject *parent=nullptr);
  /*public*/  LogixNG_Thread* getCurrentThread()override;
  /*public*/  int getStartupThreadId()override;
  /*public*/  void setStartupThreadId(int threadId)override;
  /*public*/  Base* getParent() const override;
  /*public*/  void setParent(Base* parent)override;
  /*public*/  FemaleDigitalActionSocket* getFemaleSocket() override;
  /*public*/  void setRunDelayed(bool value)override;
  /*public*/  bool getRunDelayed()override;
  /*public*/ void execute()override;
  /*public*/  void execute(bool allowRunDelayed)override;
  /*public*/  void execute(FemaleDigitalActionSocket* socket)override;
  /*public*/  Stack* getStack() override;
  /*public*/  SymbolTable* getSymbolTable()override;
  /*public*/  void setSymbolTable(SymbolTable* symbolTable)override;
  /*public*/  QString getBeanType() override;
  /*public*/  void setState(int s) /*throws JmriException */override;
  /*public*/  int getState()override;
  /*public*/  void connected(FemaleSocket* socket)override;
  /*public*/  void disconnected(FemaleSocket* socket)override;
  /*public*/  QString getShortDescription(QLocale locale)override;
  /*public*/  QString getLongDescription(QLocale locale)override;
  /*public*/  FemaleSocket* getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/override;
  /*public*/  int getChildCount()override;
  /*public*/  Category* getCategory()override;
  /*public*/  void setSocketSystemName(QString systemName);
  /*public*/  QString getSocketSystemName();
  /*final*/ /*public*/  void setup()override;
  /*final*/ /*public*/  void disposeMe()override;
  /*public*/  void setEnabled(bool enable)override;
  /*public*/  bool isEnabled()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  Base* getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames)override;

  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ /*final*/ LogixNG_Thread* _thread;
  /*private*/ int _startupThreadId;
  /*private*/ Base* _parent = nullptr;
  /*private*/ QString _socketSystemName = nullptr;
  /*private*/ /*final*/ FemaleDigitalActionSocket* _femaleSocket;
  /*private*/ bool _enabled = true;
  /*private*/ /*final*/ ExecuteLock* _executeLock = new ExecuteLock();
  /*private*/ bool _runDelayed = true;
  /*private*/ /*final*/ Stack* _stack = new DefaultStack();
  /*private*/ SymbolTable* _symbolTable;
  void common(QString sys, QString user, int threadID);
  /*private*/ void runOnLogixNG_Thread(
          /*@Nonnull*/ ThreadAction* ta,
          bool allowRunDelayed);
  /*private*/ static void internalExecute(ConditionalNG* conditionalNG, FemaleDigitalActionSocket* femaleSocket);

  friend class ExecuteTask;
  friend class DCThreadAction;
};
/*private*/ /*static*/ class ExecuteTask : public ThreadAction {
Q_OBJECT
    /*private*/ /*final*/ ConditionalNG* _conditionalNG;
    /*private*/ /*final*/ ExecuteLock* _executeLock;
    /*private*/ /*final*/ FemaleDigitalActionSocket* _localFemaleSocket;
    DefaultConditionalNG* dcng;
 public:
    /*public*/  ExecuteTask(ConditionalNG* conditionalNG, ExecuteLock* executeLock, FemaleDigitalActionSocket* femaleSocket, DefaultConditionalNG* dcng) {
        _conditionalNG = conditionalNG;
        _executeLock = executeLock;
        _localFemaleSocket = femaleSocket;
        this->dcng = dcng;
    }

    //@Override
    /*public*/  void run() {
        while (_executeLock->loop()) {
            dcng->internalExecute(_conditionalNG, _localFemaleSocket);
        }
    }
    friend class DefaultConditionalNG;
};
class DCThreadAction : public ThreadAction
{
  Q_OBJECT
 public:
  DefaultConditionalNG* dcng;
  FemaleDigitalActionSocket* socket;
  DCThreadAction (FemaleDigitalActionSocket* socket,  DefaultConditionalNG* dcng) {this->socket = socket; this->dcng = dcng;}
  void run() {
   dcng->internalExecute(dcng, socket);
  }

};

#endif // DEFAULTCONDITIONALNG_H
