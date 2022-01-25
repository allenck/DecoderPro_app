#ifndef FEMALEDIGITALBOOLEANACTIONSOCKET_H
#define FEMALEDIGITALBOOLEANACTIONSOCKET_H
#include "femalesocket.h"
#include "digitalbooleanaction.h"
/**
 * A female socket for DigitalBooleanAction
 */
/*public*/ /*interface*/ class FemaleDigitalBooleanActionSocket
        : public FemaleSocket, public DigitalBooleanAction {
 Q_INTERFACES(FemaleSocket DigitalBooleanAction)
};
Q_DECLARE_INTERFACE(FemaleDigitalBooleanActionSocket, "FemaleDigitalBooleanActionSocket")
#endif // FEMALEDIGITALBOOLEANACTIONSOCKET_H
