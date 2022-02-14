#ifndef MALEANALOGEXPRESSIONSOCKETFACTORY_H
#define MALEANALOGEXPRESSIONSOCKETFACTORY_H
#include "malesocketfactory.h"

/**
 * Factory class for MaleAnalogExpressionSocket classes.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
/*public*/ /*interface*/class MaleAnalogExpressionSocketFactory : public MaleSocketFactory/*<MaleAnalogExpressionSocket>*/ {
 Q_INTERFACES(MaleSocketFactory)
 public:
};
Q_DECLARE_INTERFACE(MaleAnalogExpressionSocketFactory, "MaleAnalogExpressionSocketFactory")
#endif // MALEANALOGEXPRESSIONSOCKETFACTORY_H
