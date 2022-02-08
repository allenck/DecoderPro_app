#ifndef FEMALEANALOGACTIONSOCKET_H
#define FEMALEANALOGACTIONSOCKET_H
#include "femalesocket.h"
#include "analogaction.h"
#include "abstractfemalesocket.h"

/**
 * A female socket for AnalogAction
 */
/*public*/ /*interface*/ class FemaleAnalogActionSocket : public AbstractFemaleSocket, public AnalogAction {

  Q_INTERFACES(AbstractFemaleSocket AnalogAction)

  virtual QObject* self() =0;
};

#endif // FEMALEANALOGACTIONSOCKET_H
