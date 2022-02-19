#ifndef ABSTRACTBASEMANAGER_H
#define ABSTRACTBASEMANAGER_H

#include <abstractmanager.h>
#include "malesocketfactory.h"
#include "basemanager.h"

class AbstractBaseManager : public AbstractManager, public virtual BaseManager
{
  Q_OBJECT
  Q_INTERFACES(BaseManager)
 public:
  explicit AbstractBaseManager(QObject *parent = nullptr);
  /*public*/ void fireVetoableChange(QString p, QVariant old) /*throws PropertyVetoException*/;
  /*public*/ /*final*/ void deleteBean(/*@Nonnull*/NamedBean* n, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/final override;
  /*public*/  void deleteBean(/*@Nonnull*/ MaleSocket* socket, /*@Nonnull*/ QString property) /*throws PropertyVetoException*/override;
  /*public*/  void deregister(/*@Nonnull*/ NamedBean* s)override;
  /*public*/  /*final*/ NameValidity validSystemNameFormat(QString systemName)override;
  /*public*/  void Register(/*@Nonnull*/ NamedBean* s)override;
  /*public*/  NamedBean* registerBean(/*@Nonnull*/ NamedBean* s)override;
  /*public*/  void registerMaleSocketFactory(MaleSocketFactory/*<E>*/* factory)override;

  //QObject* self() override {return (QObject*)this;}
 private:

 protected:
  /*protected*/ QList<MaleSocketFactory/*<E>*/*> _maleSocketFactories = QList<MaleSocketFactory/*<E>*/*>();
  /*protected*/ /*abstract*/virtual NamedBean* castBean(MaleSocket* maleSocket)=0;

};

#endif // ABSTRACTBASEMANAGER_H
