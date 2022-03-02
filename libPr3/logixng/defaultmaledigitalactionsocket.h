#ifndef DEFAULTMALEDIGITALACTIONSOCKET_H
#define DEFAULTMALEDIGITALACTIONSOCKET_H

#include "abstractmalesocket.h"
#include "maledigitalactionsocket.h"

class DefaultMaleDigitalActionSocket : public AbstractMaleSocket, public MaleDigitalActionSocket
{
  Q_OBJECT
  Q_INTERFACES(MaleDigitalActionSocket)
 public:
  /*public*/ DefaultMaleDigitalActionSocket(/*@Nonnull*/ BaseManager/*<? extends NamedBean>*/* manager,
                                          /*@Nonnull*/ DigitalActionBean* action, QObject *parent = nullptr);
  ~DefaultMaleDigitalActionSocket() {}
  DefaultMaleDigitalActionSocket(const DefaultMaleDigitalActionSocket& o) : AbstractMaleSocket(nullptr, nullptr, nullptr) {}
  /*public*/  /*static*/ class DigitalActionDebugConfig : public MaleSocket::DebugConfig {
      public:
      // If true, the socket is not executing the action.
      // It's useful if you want to test the LogixNG without affecting the
      // layout (turnouts, sensors, and so on).
      /*public*/  bool _dontExecute = false;

      //@Override
      /*public*/  DebugConfig* getCopy() {
          DigitalActionDebugConfig* config = new DigitalActionDebugConfig();
          config->_dontExecute = _dontExecute;
          return config;
      }
  };
  /*public*/  void execute() /*throws JmriException*/override;
  /*public*/  void disposeMe()override;
  /*public*/  void registerListenersForThisClass()override;
  /*public*/  void unregisterListenersForThisClass()override;
  /*public*/  void setState(int s) /*throws JmriException*/ override;
  /*public*/  int getState() override;
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
  /*public*/ QString getClassName() override {return "jmri.jmrit.logixng.implentation.DefaultMaleDigitalActionSocket";}

  QObject* self() override {return (QObject*)this;}

 private:
  static Logger* log;
  //    /*private*/ /*final*/ DigitalActionBean ((DigitalActionBean)getObject());
      /*private*/ DebugConfig* _debugConfig = nullptr;
      /*private*/ bool _enabled = true;

};
//Q_DECLARE_METATYPE(DefaultMaleDigitalActionSocket)
#endif // DEFAULTMALEDIGITALACTIONSOCKET_H
