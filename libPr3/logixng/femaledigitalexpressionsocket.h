#ifndef FEMALEDIGITALEXPRESSIONSOCKET_H
#define FEMALEDIGITALEXPRESSIONSOCKET_H
#include "femalesocket.h"
#include "digitalexpression.h"
/**
 * A female socket for DigitalExpression
 */
/*public*/ /*interface*/ class FemaleDigitalExpressionSocket : public FemaleSocket, public DigitalExpression {
 Q_INTERFACES(FemaleSocket DigitalExpression)
};
Q_DECLARE_INTERFACE(FemaleDigitalExpressionSocket, "FemaleDigitalExpressionSocket")
#endif // FEMALEDIGITALEXPRESSIONSOCKET_H
