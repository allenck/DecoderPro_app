#ifndef ABSTRACTDEBUGGERMALESOCKET_H
#define ABSTRACTDEBUGGERMALESOCKET_H

#include "abstractmalesocket.h"
#include "debugger.h"
#include "instancemanager.h"
class AbstractDebuggerMaleSocket : public AbstractMaleSocket
{
  Q_OBJECT
 public:
  explicit AbstractDebuggerMaleSocket(BaseManager/*<? extends MaleSocket>*/* manager, MaleSocket *maleSocket, QObject *parent = nullptr);
  /*public*/ /*abstract*/ virtual QString getBeforeInfo()=0;
  /*public*/ /*abstract*/ virtual QString getAfterInfo()=0;
  /*public*/  void setStepInto(bool value);
  /*public*/  void setBreakpointBefore(bool value);
  /*public*/  bool getBreakpointBefore();
  /*public*/  void setBreakpointAfter(bool value);
  /*public*/  bool getBreakpointAfter();
  /*public*/  /*final*/ void setEnabled(bool enable)override final;
  /*public*/  void setEnabledFlag(bool enable) override;
  /*public*/  /*final*/ bool isEnabled()override final;
  /*public*/  /*final*/ void setDebugConfig(DebugConfig* config) override final;
  /*public*/  /*final*/ DebugConfig* getDebugConfig()override final;
  /*public*/  /*final*/ DebugConfig* createDebugConfig()override final ;
  /*public*/  /*final*/ QString getComment()override final;
  /*public*/  /*final*/ void setComment(QString comment)override final ;
  /*public*/  void setParent(Base* parent)override;

  /*public*/ QString getLongDescription(QLocale locale) override{return AbstractMaleSocket::getLongDescription(locale);}
 private:
  /*private*/ /*final*/ Debugger* _debugger = (Debugger*)InstanceManager::getDefault("Debugger");
//    /*protected*/ final MaleSocket ((MaleSocket)getObject());

  /*private*/ bool _breakpointBefore = false;
  /*private*/ bool _breakpointAfter = false;

  /*private*/ bool _stepInto = true;
  /*private*/ bool _lastDoBreak = true;

 protected:
  /*protected*/ bool isDebuggerActive();
  /*protected*/ void before();
  /*protected*/ void after();
  /*protected*/ /*final*/ void registerListenersForThisClass()override;
  /*protected*/ /*final*/ void unregisterListenersForThisClass()override;
  /*protected*/ /*final*/ void disposeMe()override;

};

#endif // ABSTRACTDEBUGGERMALESOCKET_H
