#ifndef ABSTRACTPROVIDINGPROXYMANAGER_H
#define ABSTRACTPROVIDINGPROXYMANAGER_H
#include "abstractproxymanager.h"
#include "providingmanager.h"

/*abstract*/ class AbstractProvidingProxyManager : public AbstractProxyManager/*<E>*/,  public ProvidingManager/*<E>*/
{
  Q_INTERFACES(AbstractProxyManager ProvidingManager)
 public:
  /*public*/ /*E*/NamedBean* newNamedBean(/*@Nonnull*/ QString systemName, QString userName) /*throws IllegalArgumentException*/;

 private:
  static Logger* log;

 protected:
  /*protected*/ /*E*/NamedBean* provideNamedBean(QString name);
  /*abstract*/virtual /*protected*/ /*E*/NamedBean* makeBean(Manager/*<E>*/* manager,/*@Nonnull*/ QString systemName,
                                                             QString userName) /*throws IllegalArgumentException*/  =0;

};
Q_DECLARE_INTERFACE(AbstractProvidingProxyManager, "AbstractProvidingProxyManager")
#endif // ABSTRACTPROVIDINGPROXYMANAGER_H
