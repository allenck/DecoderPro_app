#ifndef MALESTRINGEXPRESSIONSOCKETFACTORY_H
#define MALESTRINGEXPRESSIONSOCKETFACTORY_H
#include "malesocketfactory.h"

/**
 * Factory class for MaleStringExpressionSocket classes.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
/*public*/ /*interface*/class MaleStringExpressionSocketFactory : MaleSocketFactory/*<MaleStringExpressionSocket>*/ {
 Q_INTERFACES(MaleSocketFactory)
 public:
};
Q_DECLARE_INTERFACE(MaleStringExpressionSocketFactory, "MaleStringExpressionSocketFactory")
#endif // MALESTRINGEXPRESSIONSOCKETFACTORY_H
