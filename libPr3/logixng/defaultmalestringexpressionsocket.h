#ifndef DEFAULTMALESTRINGEXPRESSIONSOCKET_H
#define DEFAULTMALESTRINGEXPRESSIONSOCKET_H

#include "abstractmalesocket.h"
#include "malestringexpressionsocket.h"

class DefaultMaleStringExpressionSocket : public AbstractMaleSocket, public MaleStringExpressionSocket
{
  Q_OBJECT
 public:
  DefaultMaleStringExpressionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager, /*@Nonnull*/ StringExpressionBean* stringExpression, QObject* parent = nullptr);
  /*public*/  bool getTriggerOnChange()override;
  /*public*/  void setTriggerOnChange(bool triggerOnChange)override;
  /*public*/  QString evaluate() /*throws JmriException */override;
  /*public*/  int getState()override;
  /*public*/  QString getDisplayName()override;
  /*public*/  void disposeMe()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void setState(int s) /*throws JmriException*/ override;
  /*public*/  QString describeState(int state)override;
  /*public*/  QString getComment()override;
  /*public*/  void setComment(QString comment)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key) override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2) override;
  /*public*/  void setDebugConfig(DebugConfig* config) override;
  /*public*/  DebugConfig* getDebugConfig()override;
  /*public*/  DebugConfig* createDebugConfig()override;
  /*public*/  void setEnabled(bool enable)override;
  /*public*/  void setEnabledFlag(bool enable)override;
  /*public*/  bool isEnabled()override;
  /*public*/  /*static*/ class StringExpressionDebugConfig : public MaleSocket::DebugConfig {
      public:
      // If true, the socket is returning the value of "result" instead of
      // executing the expression.
      /*public*/  bool _forceResult = false;

      // The result if the result is forced.
      /*public*/  QString _result = "";

      //@Override
      /*public*/ DebugConfig* getCopy() {
                StringExpressionDebugConfig* config = new StringExpressionDebugConfig();
                config->_forceResult = _forceResult;
                config->_result = _result;
                return config;
            }
        };
  /*public*/ QString getClassName()override {return "jmri.jmrit.logixng.tools.debugger.DefaultMaleStringExpressionSocket";}
  QObject* self() override {return (QObject*)this;}
  QObject* bself() override {return (QObject*)this;}

 private:
  static Logger* log;
  //    /*private*/ /*final*/ StringExpressionBean ((StringExpressionBean)getObject());
  /*private*/ DebugConfig* _debugConfig = nullptr;
  /*private*/ bool _enabled = true;

};

#endif // DEFAULTMALESTRINGEXPRESSIONSOCKET_H
