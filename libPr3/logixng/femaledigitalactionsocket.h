#ifndef FEMALEDIGITALACTIONSOCKET_H
#define FEMALEDIGITALACTIONSOCKET_H
#include "femalesocket.h"
#include "digitalaction.h"
/**
 * A female socket for DigitalAction
 */
/*public*/ /*interface*/class FemaleDigitalActionSocket : FemaleSocket, DigitalAction {

  Q_INTERFACES(FemaleSocket DigitalAction)
};
Q_DECLARE_INTERFACE(FemaleDigitalActionSocket, "FemaleDigitalActionSocket")
#endif // FEMALEDIGITALACTIONSOCKET_H
