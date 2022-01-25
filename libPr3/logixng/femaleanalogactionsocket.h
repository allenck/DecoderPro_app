#ifndef FEMALEANALOGACTIONSOCKET_H
#define FEMALEANALOGACTIONSOCKET_H
#include "femalesocket.h"
#include "analogaction.h"
/**
 * A female socket for AnalogAction
 */
/*public*/ /*interface*/ class FemaleAnalogActionSocket : public FemaleSocket, public AnalogAction {

  Q_INTERFACES(FemaleSocket AnalogAction)
};

#endif // FEMALEANALOGACTIONSOCKET_H
