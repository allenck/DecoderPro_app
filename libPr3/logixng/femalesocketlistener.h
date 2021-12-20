#ifndef FEMALESOCKETLISTENER_H
#define FEMALESOCKETLISTENER_H
#include "femalesocket.h"

/**
 * A listener for when a socket is connected or disconnected.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
/*public*/ /*interface*/class FemaleSocketListener {
 public:
    /**
     * The socket is connected.
     * @param socket the socket
     */
    /*public*/ virtual void connected(FemaleSocket* socket)=0;

    /**
     * The socket is disconnected.
     * @param socket the socket
     */
    /*public*/ virtual void disconnected(FemaleSocket* socket)=0;

    /**
     * The socket name is changed.
     * @param socket the socket
     */
    /*public*/ virtual /*default*/ void socketNameChanged(FemaleSocket* /*socket*/) {
        // Do nothing
    }

};

#endif // FEMALESOCKETLISTENER_H