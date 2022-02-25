#ifndef DEFAULTMALESTRINGACTIONSOCKET_H
#define DEFAULTMALESTRINGACTIONSOCKET_H

#include "abstractmalesocket.h"
#include "malestringactionsocket.h"

class StringActionBean;
class DefaultMaleStringActionSocket : public AbstractMaleSocket, public MaleStringActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleStringActionSocket)
 public:
  explicit DefaultMaleStringActionSocket(BaseManager/*<? extends NamedBean>*/* manager, /*@Nonnull*/ StringActionBean* stringAction, QObject *parent = nullptr);
  /*public*/  /*static*/ class StringActionDebugConfig : public MaleSocket::DebugConfig {
 public:
      // If true, the socket is not executing the action.
      // It's useful if you want to test the LogixNG without affecting the
      // layout (turnouts, sensors, and so on).
      /*public*/  bool _dontExecute = false;

      //@Override
      /*public*/  DebugConfig* getCopy() {
          StringActionDebugConfig* config = new StringActionDebugConfig();
          config->_dontExecute = _dontExecute;
          return config;
      }
  };
  /*public*/  void setValue(QString value) /*throws JmriException*/override;
  /*public*/  QString getDisplayName() override;
  /*public*/  void disposeMe()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void setState(int s) /*throws JmriException*/ override;
  /*public*/  int getState()override;
  /*public*/  QString describeState(int state)override;
  /*public*/  QString getComment()override;
  /*public*/  void setComment(QString comment)override;
  /*public*/  void setProperty(QString key, QVariant value)override;
  /*public*/  QVariant getProperty(QString key)override;
  /*public*/  void removeProperty(QString key) override;
  /*public*/  QSet<QString> getPropertyKeys()override;
  /*public*/  QString getBeanType()override;
  /*public*/  int compareSystemNameSuffix(QString suffix1, QString suffix2, NamedBean* n2)override;
  /*public*/  void setDebugConfig(DebugConfig* config)override;
  /*public*/  DebugConfig *getDebugConfig()override;
  /*public*/  DebugConfig* createDebugConfig()override;
  /*public*/  void setEnabled(bool enable)override;
  /*public*/  void setEnabledFlag(bool enable)override;
  /*public*/  bool isEnabled()override;

  QObject* self() override {return (QObject*)this;}

 private:
  /*private*/ DebugConfig* _debugConfig = nullptr;
  /*private*/ bool _enabled = true;
  static Logger* log;
};

#endif // DEFAULTMALESTRINGACTIONSOCKET_H
