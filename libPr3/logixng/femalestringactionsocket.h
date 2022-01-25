#ifndef FEMALESTRINGACTIONSOCKET_H
#define FEMALESTRINGACTIONSOCKET_H
#include "femalesocket.h"
#include "stringaction.h"
/**
 * A female socket for StringAction
 */
/*public*/ /*interface*/ class FemaleStringActionSocket : public FemaleSocket, public StringAction {
Q_INTERFACES(FemaleSocket StringAction)
};
Q_DECLARE_INTERFACE(FemaleStringActionSocket, "FemaleStringActionSocket")
#endif // FEMALESTRINGACTIONSOCKET_H
