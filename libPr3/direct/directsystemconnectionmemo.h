#ifndef DIRECTSYSTEMCONNECTIONMEMO_H
#define DIRECTSYSTEMCONNECTIONMEMO_H

#include "defaultsystemconnectionmemo.h"

class ComponentFactory;
class TrafficController;
class DefaultThrottleManager;
class DirectSystemConnectionMemo : public DefaultSystemConnectionMemo
{
 public:
  /*public*/ DirectSystemConnectionMemo(QObject * parent = 0);
  /*public*/ DirectSystemConnectionMemo(/*@Nonnull*/ QString prefix, /*@Nonnull*/ QString userName, QObject * parent = 0);


  /**
   * Set the traffic controller instance associated with this connection memo.
   *
   * @param s jmri.jmrix.direct.TrafficController object to use.
   */
  /*public*/ void setTrafficController(TrafficController* s);

  /**
   * Get the traffic controller instance associated with this connection memo.
   * @return traffic controller, provided if null.
   */
  /*public*/ TrafficController* getTrafficController();

  /**
   * Set the traffic controller instance associated with this connection memo.
   *
   * @param s jmri.jmrix.direct.ThrottleManager object to use.
   */
  /*public*/ void setThrottleManager(DefaultThrottleManager *s);

  /**
   * Get the ThrottleManager instance associated with this connection memo.
   * @return throttle manager, provided if null.
   */
  /*public*/ DefaultThrottleManager *getThrottleManager();

//  @Override
//  protected ResourceBundle getActionModelResourceBundle() {
//      return null;
//  }

//  //@Override
//  /*public*/ <B extends NamedBean> Comparator<B> getNamedBeanComparator(Class<B> type) {
//      return new NamedBeanComparator<>();
//  }

  /*public*/ void configureManagers();

 private:
  /*private*/ TrafficController* tc = nullptr;
  ComponentFactory* cf = nullptr;
  static Logger* log;
};

#endif // DIRECTSYSTEMCONNECTIONMEMO_H
