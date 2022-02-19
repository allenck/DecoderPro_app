#ifndef DEFAULTMALEANALOGEXPRESSIONSOCKET_H
#define DEFAULTMALEANALOGEXPRESSIONSOCKET_H

#include "abstractmalesocket.h"
#include "maleanalogexpressionsocket.h"
#include "malesocket.h"
#include "debugable.h"

class AnalogExpressionDebugConfig;
class AnalogExpressionBean;
class DefaultMaleAnalogExpressionSocket : public AbstractMaleSocket, public MaleAnalogExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogExpressionSocket)
 public:
  explicit DefaultMaleAnalogExpressionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager, /*@Nonnull*/ AnalogExpressionBean* expression, QObject *parent = nullptr);
  /*public*/  bool getTriggerOnChange()override;
  /*public*/  void setTriggerOnChange(bool triggerOnChange)override;
  /*public*/  double evaluate() /*throws JmriException*/ override;
  /*public*/  int getState()override;
  /*public*/  QString getDisplayName()override;
  /*public*/  void disposeMe()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  QString describeState(int state)override;
  /*public*/  QString getComment()override;
  /*public*/  void setComment(QString comment)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/  void setDebugConfig(DebugConfig* config)override;
  /*public*/  DebugConfig* getDebugConfig()override;
  /*public*/  DebugConfig* createDebugConfig()override;
  /*public*/  void setEnabled(bool enable)override;
  /*public*/  void setEnabledFlag(bool enable)override;
  /*public*/  bool isEnabled()override;

  QObject* self() override {return (QObject*)this;}

 private:
  static Logger* log;
  //    /*private*/ /*final*/ AnalogExpressionBean ((AnalogExpressionBean)getObject());
  /*private*/ DebugConfig* _debugConfig = nullptr;
  /*private*/ bool _enabled = true;
  /*private*/ double internalEvaluate() /*throws JmriException*/;

};

/*public*/  /*static*/ class AnalogExpressionDebugConfig : public MaleSocket::DebugConfig {
    public:
    // If true, the socket is returning the value of "result" instead of
    // executing the expression.
    /*public*/  bool _forceResult = false;

    // The result if the result is forced.
    /*public*/  double _result = 0.0f;

    //@Override
    /*public*/  DebugConfig* getCopy() {
        AnalogExpressionDebugConfig* config = new AnalogExpressionDebugConfig();
        config->_forceResult = _forceResult;
        config->_result = _result;
        return config;
    }

};

#endif // DEFAULTMALEANALOGEXPRESSIONSOCKET_H
