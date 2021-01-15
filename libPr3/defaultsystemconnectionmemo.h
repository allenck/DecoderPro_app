#ifndef DEFAULTSYSTEMCONNECTIONMEMO_H
#define DEFAULTSYSTEMCONNECTIONMEMO_H
#include "systemconnectionmemo.h"
#include <QMap>
#include "startupactionfactory.h"


class DefaultSystemConnectionMemo : /*public Bean,*/ public SystemConnectionMemo
{
  Q_OBJECT
  //Q_INTERFACES(SystemConnectionMemo)
 public:
  DefaultSystemConnectionMemo(QObject* parent = nullptr) {}
  /*public*/ void _register() override;
  /*public*/ QString getSystemPrefix() const override;
  /*public*/ /*final*/ bool setSystemPrefix(/*@Nonnull*/ QString systemPrefix) override;
  /*public*/ QString getUserName() const override;
  /*public*/ /*final*/ bool setUserName(/*@Nonnull*/ QString userName) override;
  /*public*/ bool provides(/*Class<?>*/QString c) override;
  /*public*/ /*<T> T*/Manager* get(/*Class<?>*/QString type) override;
  /*public*/ void dispose() override;
  /*public*/ bool getDisabled() override;
  /*public*/ void setDisabled(bool disabled) override;
//  /*public*/ /*abstract*/virtual <B extends NamedBean> Comparator<B> getNamedBeanComparator(Class<B> type);
  /*public*/ StartupActionFactory* getActionFactory();
  /*public*/ bool isDirty() override;
  /*public*/ bool isRestartRequired() override;
  /*public*/ ConsistManager* getConsistManager();
  /*public*/ void setConsistManager(ConsistManager* c);
  /*public*/ /*<T>*/ void store(/*@Nonnull*/ Manager *item, /*@Nonnull Class<T>*/QString type);
  /*public*/ /*<T>*/ void deregister(/*@Nonnull T*/Manager *item, /*@Nonnull Class<T>*/QString type);
  /*public*/ int getDefaultOutputInterval() override;
  /*public*/ int getOutputInterval() override;
  /*public*/ void setOutputInterval(int newInterval) override;
  //QObject* self() {return (QObject*)this;}
 private:
  /*private*/ bool disabled = false;
  /*private*/ bool disabledAsLoaded = false; // Boolean can be true, false, or null
  /*private*/ QString prefix;
  /*private*/ QString prefixAsLoaded;
  /*private*/ QString userName;
  /*private*/ QString userNameAsLoaded;
  static Logger* log;
  /*private*/ /*<T> */void removeRegisteredObject(/*Class<T>*/QString c);
  /*private*/ ConsistManager* generateDefaultConsistManagerForConnection();
  /**
   * Duration in milliseconds of interval between separate Turnout commands on the same connection.
   * <p>
   * Change from e.g. connection config dialog and scripts using {@link #setOutputInterval(int)}
   */
  /*private*/ int _interval = getDefaultOutputInterval();
  /*private*/ /*<T>*/ void disposeIfPossible(/*Class<T>*/QString c, Manager* object);

 protected:
  /*protected*/ DefaultSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString userName, QObject *parent = 0);
  /*protected*/ QMap</*Class<?>*/QString,Manager*> classObjectMap;
  /*protected*/ /*abstract*/virtual ResourceBundle* getActionModelResourceBundle() {return nullptr;}
  QT_DEPRECATED /*protected*/ /*final*/ void addToActionList();
  QT_DEPRECATED /*protected*/ /*final*/ void removeFromActionList();

  friend class InternalSystemConnectionMemo;
  friend class JMRIClientSystemConnectionMemo;
  friend class AbstractPortControllerScaffold;
};

#endif // DEFAULTSYSTEMCONNECTIONMEMO_H
