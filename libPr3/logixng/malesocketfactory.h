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
/*public*/ /*interface*/class  MaleSocketFactory/*<T>*/ : public NamedBean {
    Q_INTERFACES(NamedBean)
    /**
     * Encapsulate a male socket into another male socket.
     * @param manager the manager that registers this male socket
     * @param maleSocket the male socket to be encapsulated
     * @return the new male socket that encapsulates the old male socket
     */
    /*public*/ virtual /*T*/NamedBean* encapsulateMaleSocket(BaseManager/*<T>*/* manager, NamedBean* maleSocket)=0;

};

#endif // MALESOCKETFACTORY_H
