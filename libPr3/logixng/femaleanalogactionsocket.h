#ifndef FEMALEANALOGACTIONSOCKET_H
#define FEMALEANALOGACTIONSOCKET_H
#include "femalesocket.h"
#include "analogaction.h"
#include "abstractfemalesocket.h"

/**
 * A female socket for AnalogAction
 */
/*public*/ /*interface*/ class FemaleAnalogActionSocket : public FemaleSocket, public AnalogAction {

  Q_INTERFACES(FemaleSocket AnalogAction)

  virtual QObject* self() =0;
};
Q_DECLARE_INTERFACE(FemaleAnalogActionSocket, "FemaleAnalogActionSocket")
#endif // FEMALEANALOGACTIONSOCKET_H
