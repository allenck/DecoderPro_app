#ifndef FEMALESTRINGEXPRESSIONSOCKET_H
#define FEMALESTRINGEXPRESSIONSOCKET_H
#include "femalesocket.h"
#include "stringexpression.h"
/**
 * A female socket for StringExpression
 */
/*public*/ /*interface*/ FemaleStringExpressionSocket
        : public FemaleSocket, public StringExpression {

};

#endif // FEMALESTRINGEXPRESSIONSOCKET_H
