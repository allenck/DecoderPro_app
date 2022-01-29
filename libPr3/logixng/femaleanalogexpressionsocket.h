#ifndef FEMALEANALOGEXPRESSIONSOCKET_H
#define FEMALEANALOGEXPRESSIONSOCKET_H
#include "femalesocket.h"
#include "analogexpression.h"
/**
 * A female socket for AnalogExpression
 */
/*public*/ /*interface*/ class FemaleAnalogExpressionSocket
        : public FemaleSocket, public AnalogExpression {
  Q_INTERFACES(FemaleSocket AnalogExpression)

};
Q_DECLARE_INTERFACE(FemaleAnalogExpressionSocket, "FemaleAnalogExpressionSocket")
#endif // FEMALEANALOGEXPRESSIONSOCKET_H
