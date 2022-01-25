#ifndef FEMALEANALOGEXPRESSIONSOCKET_H
#define FEMALEANALOGEXPRESSIONSOCKET_H
#include "femalesocket.h"
#include "analogexpression.h"
/**
 * A female socket for AnalogExpression
 */
/*public*/ /*interface*/ class FemaleAnalogExpressionSocket
        : public FemaleSocket, public AnalogExpression {

};

#endif // FEMALEANALOGEXPRESSIONSOCKET_H
