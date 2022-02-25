#ifndef DEFAULTMALEDIGITALBOOLEANACTIONSOCKET_H
#define DEFAULTMALEDIGITALBOOLEANACTIONSOCKET_H

#include "abstractmalesocket.h"
#include "maledigitalbooleanactionsocket.h"

class DefaultMaleDigitalBooleanActionSocket : public AbstractMaleSocket, public MaleDigitalBooleanActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalBooleanActionSocket)
 public:
  DefaultMaleDigitalBooleanActionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager, /*@Nonnull*/ DigitalBooleanActionBean* action, QObject* parent = nullptr);
  /*public*/  /*static*/ class DigitalBooleanActionDebugConfig : public MaleSocket::DebugConfig {
      public:
      // If true, the socket is not executing the action.
      // It's useful if you want to test the LogixNG without affecting the
      // layout (turnouts, sensors, and so on).
      /*public*/  bool _dontExecute = false;

      //@Override
      /*public*/  DebugConfig* getCopy() {
          DigitalBooleanActionDebugConfig* config = new DigitalBooleanActionDebugConfig();
          config->_dontExecute = _dontExecute;
          return config;
      }
  };
  /*public*/  void execute(bool hasChangedToTrue, bool hasChangedToFalse) /*throws JmriException*/override;
  /*public*/  QString getDisplayName()override;
  /*public*/  void disposeMe()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void setState(int s) /*throws JmriException*/override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  QString getComment()override;
  /*public*/  void setComment(QString comment)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key)override;
  /*public*/  QSet<QString> getPropertyKeys() override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/  void setDebugConfig(DebugConfig* config)override;
  /*public*/  DebugConfig* getDebugConfig()override;
  /*public*/  DebugConfig* createDebugConfig()override;
  /*public*/  void setEnabled(bool enable) override;
  /*public*/  void setEnabledFlag(bool enable) override;
  /*public*/  bool isEnabled()override;

  QObject* self() override {return (QObject*)this;}

 private:
  static Logger* log;
  //    /*private*/ /*final*/ DigitalBooleanActionBean ((DigitalBooleanActionBean)getObject());
      /*private*/ DebugConfig* _debugConfig = nullptr;
      /*private*/ bool _enabled = true;

};


#endif // DEFAULTMALEDIGITALBOOLEANACTIONSOCKET_H
