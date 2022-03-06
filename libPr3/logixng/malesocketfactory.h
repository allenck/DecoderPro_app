#ifndef MALESOCKETFACTORY_H
#define MALESOCKETFACTORY_H
#include "namedbean.h"
#include "basemanager.h"

/**
 * Factory class for male sockets. This class is used when a tool wants to add
 * extra male sockets around the male sockets for actions and expressions. An
 * example is the debugger.
 *
 * @author Daniel Bergqvist Copyright 2020
 * @param <T> the type of male socket
 */
//template <class T>
/*public*/ /*interface*/class  MaleSocketFactory {
 public:
    /**
     * Encapsulate a male socket into another male socket.
     * @param manager the manager that registers this male socket
     * @param maleSocket the male socket to be encapsulated
     * @return the new male socket that encapsulates the old male socket
     */
  /*public*/ virtual NamedBean* encapsulateMaleSocket(BaseManager/*<T>*/* manager, NamedBean* maleSocket) {return nullptr;}

  virtual QObject*  self() =0;
};
Q_DECLARE_INTERFACE(MaleSocketFactory, "MaleSocketFactory")
#endif // MALESOCKETFACTORY_H
