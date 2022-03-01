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
  /*public*/ virtual void connected(FemaleSocket* socket) {}

    /**
     * The socket is disconnected.
     * @param socket the socket
     */
  /*public*/ virtual void disconnected(FemaleSocket* socket) {}

    /**
     * The socket name is changed.
     * @param socket the socket
     */
    /*public*/ virtual /*default*/ void socketNameChanged(FemaleSocket* /*socket*/) {
        // Do nothing
    }
  virtual QObject* self() {return (QObject*)nullptr;}
};
Q_DECLARE_INTERFACE(FemaleSocketListener, "FemaleSocketListener")
#endif // FEMALESOCKETLISTENER_H
