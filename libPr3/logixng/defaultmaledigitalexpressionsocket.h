#ifndef DEFAULTMALEDIGITALEXPRESSIONSOCKET_H
#define DEFAULTMALEDIGITALEXPRESSIONSOCKET_H

#include "abstractmalesocket.h"
#include "maledigitalexpressionsocket.h"

class DigitalExpressionBean;
class DefaultMaleDigitalExpressionSocket : public AbstractMaleSocket, public MaleDigitalExpressionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalExpressionSocket)
 public:
  explicit DefaultMaleDigitalExpressionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
                                              /*@Nonnull*/ DigitalExpressionBean* expression, QObject *parent = nullptr);
  /*public*/  /*static*/ class DigitalExpressionDebugConfig : public MaleSocket::DebugConfig {
      public:
      // If true, the socket is returning the value of "result" instead of
      // executing the expression.
      /*public*/  bool _forceResult = false;

      // The result if the result is forced.
      /*public*/  bool _result = false;

      //@Override
      /*public*/  DebugConfig* getCopy() {
          DigitalExpressionDebugConfig* config = new DigitalExpressionDebugConfig();
          config->_forceResult = _forceResult;
          config->_result = _result;
          return config;
      }
  };
  /*public*/  void notifyChangedResult(bool oldResult, bool newResult);
  /*public*/  bool evaluate() /*throws JmriException*/override;
  /*public*/  bool getLastResult()override;
  /*public*/  int getState()override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  QString describeState(int state)override;
  /*public*/  void setProperty(QString key, QVariant value) override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType() override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/  void setDebugConfig(DebugConfig* config)override;
  /*public*/  DebugConfig* getDebugConfig()override;
  /*public*/  DebugConfig* createDebugConfig() override;
  /*public*/  void setEnabled(bool enable)override;
  /*public*/  void setEnabledFlag(bool enable)override;
  /*public*/  bool isEnabled()override;
  /*public*/  void disposeMe()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  QString getDisplayName()override;

  QObject* self() override {return (QObject*)this;}

 private:
  static Logger* log;
  /*private*/ bool lastEvaluationResult = false;
  /*private*/ DebugConfig* _debugConfig = nullptr;
  /*private*/ bool _enabled = true;
  /*private*/ void checkChangedLastResult(bool savedLastResult);

};

#endif // DEFAULTMALEDIGITALEXPRESSIONSOCKET_H
