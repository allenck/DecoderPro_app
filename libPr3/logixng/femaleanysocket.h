#ifndef FEMALEANYSOCKET_H
#define FEMALEANYSOCKET_H
#include <QtCore>
#include "femalesocket.h"
/**
 * A female socket that can hold any male socket
 *
 * @author Daniel Bergqvist (C) 2020
 */
/*public*/ /*interface*/class FemaleAnySocket : public FemaleSocket {
    Q_INTERFACES(FemaleSocket)
};
Q_DECLARE_INTERFACE(FemaleAnySocket, "FemaleAnySocket")
#endif // FEMALEANYSOCKET_H
