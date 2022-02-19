#ifndef DEFAULTMALEANALOGACTIONSOCKET_H
#define DEFAULTMALEANALOGACTIONSOCKET_H

#include "abstractmalesocket.h"
#include "maleanalogactionsocket.h"

class AnalogActionBean;
class DefaultMaleAnalogActionSocket : public AbstractMaleSocket, public MaleAnalogActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleAnalogActionSocket)
 public:
  explicit DefaultMaleAnalogActionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
                                         /*@Nonnull*/ AnalogActionBean* action, QObject *parent = nullptr);
  /*public*/  /*static*/ class AnalogActionDebugConfig : public MaleSocket::DebugConfig {
      public:
      // If true, the socket is not executing the action.
      // It's useful if you want to test the LogixNG without affecting the
      // layout (turnouts, sensors, and so on).
      /*public*/  bool _dontExecute = false;

      //@Override
      /*public*/  DebugConfig* getCopy() {
          AnalogActionDebugConfig* config = new AnalogActionDebugConfig();
          config->_dontExecute = _dontExecute;
          return config;
      }

  };
  /*public*/  void setValue(double value) /*throws JmriException*/override;
  /*public*/  QString getDisplayName()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void setState(int s) /*throws JmriException*/ override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  QString getComment()override;
  /*public*/  void setComment(QString comment)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType() override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/  void setDebugConfig(DebugConfig* config)override;
  /*public*/  DebugConfig* getDebugConfig()override;
  /*public*/  DebugConfig* createDebugConfig()override;
  /*public*/  void setEnabled(bool enable)override;
  /*public*/  void setEnabledFlag(bool enable) override;
  /*public*/  bool isEnabled()override;
  /*public*/  void disposeMe()override;

 private:
  static Logger* log;
  //    /*private*/ /*/*final*/*/ AnalogActionBean ((AnalogActionBean)getObject());
  /*private*/ DebugConfig* _debugConfig = nullptr;
  /*private*/ bool _enabled = true;
  /*private*/ void internalSetValue(double value) /*throws JmriException*/;

};

#endif // DEFAULTMALEANALOGACTIONSOCKET_H
