#ifndef ABSTRACTPROVIDINGPROXYMANAGER_H
#define ABSTRACTPROVIDINGPROXYMANAGER_H
#include "abstractproxymanager.h"
#include "providingmanager.h"

/*abstract*/ class AbstractProvidingProxyManager : public AbstractProxyManager/*<E>*/,  public ProvidingManager/*<E>*/
{
  Q_OBJECT
  Q_INTERFACES( ProvidingManager)
 public:
  AbstractProvidingProxyManager(QObject* parent = nullptr) : AbstractProxyManager(parent) {}
  /*public*/ /*E*/NamedBean* newNamedBean(/*@Nonnull*/ QString systemName, QString userName) /*throws IllegalArgumentException*/;

 private:
  static Logger* log;

 protected:
  /*protected*/ /*E*/NamedBean* provideNamedBean(QString name);
  /*abstract*/virtual /*protected*/ /*E*/NamedBean* makeBean(AbstractManager/*<E>*/* manager,/*@Nonnull*/ QString systemName,
                                                             QString userName) /*throws IllegalArgumentException*/  {return nullptr;}

};
//Q_DECLARE_INTERFACE(AbstractProvidingProxyManager, "AbstractProvidingProxyManager")
#endif // ABSTRACTPROVIDINGPROXYMANAGER_H
