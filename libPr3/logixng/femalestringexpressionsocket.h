#ifndef FEMALESTRINGEXPRESSIONSOCKET_H
#define FEMALESTRINGEXPRESSIONSOCKET_H
#include "femalesocket.h"
#include "stringexpression.h"

/**
 * A female socket for StringExpression
 */
/*public*/ /*interface*/ class FemaleStringExpressionSocket
        : public FemaleSocket, public StringExpression {
Q_INTERFACES(FemaleSocket StringExpression)
};
Q_DECLARE_INTERFACE(FemaleStringExpressionSocket, "FemaleStringExpressionSocket")
#endif // FEMALESTRINGEXPRESSIONSOCKET_H
