#ifndef DEFAULTSYSTEMCONNECTIONMEMO_H
#define DEFAULTSYSTEMCONNECTIONMEMO_H
#include "systemconnectionmemo.h"
#include <QMap>
#include "startupactionfactory.h"

class DefaultSystemConnectionMemo : public SystemConnectionMemo
{
  Q_OBJECT
 public:
  DefaultSystemConnectionMemo(QObject *parent = 0);
  /*public*/ void _register();
  /*public*/ QString getSystemPrefix() const;
  /*public*/ /*final*/ bool setSystemPrefix(/*@Nonnull*/ QString systemPrefix);
  /*public*/ QString getUserName();
  /*public*/ /*final*/ bool setUserName(/*@Nonnull*/ QString userName);
  /*public*/ bool provides(/*Class<?>*/QString c);
  /*public*/ /*<T> T*/Manager* get(/*Class<?>*/QString type);
  /*public*/ void dispose();
  /*public*/ bool getDisabled();
  /*public*/ void setDisabled(bool disabled);
//  /*public*/ /*abstract*/virtual <B extends NamedBean> Comparator<B> getNamedBeanComparator(Class<B> type);
  /*public*/ StartupActionFactory* getActionFactory();
  /*public*/ bool isDirty();
  /*public*/ bool isRestartRequired();
  /*public*/ ConsistManager* getConsistManager();
  /*public*/ void setConsistManager(ConsistManager* c);
  /*public*/ /*<T>*/ void store(/*@Nonnull*/ Manager *item, /*@Nonnull Class<T>*/QString type);
  /*public*/ /*<T>*/ void deregister(/*@Nonnull T*/Manager *item, /*@Nonnull Class<T>*/QString type);
  /*public*/ int getDefaultOutputInterval();
  /*public*/ int getOutputInterval();
  /*public*/ void setOutputInterval(int newInterval);

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

};

#endif // DEFAULTSYSTEMCONNECTIONMEMO_H
