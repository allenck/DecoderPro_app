#ifndef MALEANALOGACTIONSOCKETFACTORY_H
#define MALEANALOGACTIONSOCKETFACTORY_H
#include "malesocketfactory.h"
#include "maleanalogactionsocket.h"

/**
 * Factory class for MaleAnalogActionSocket classes.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
/*public*/ /*interface*/class  MaleAnalogActionSocketFactory : MaleSocketFactory<MaleAnalogActionSocket> {
Q_INTERFACES(MaleSocketFactory<MaleAnalogActionSocket>)
};
Q_DECLARE_INTERFACE(MaleAnalogActionSocketFactory, "MaleAnalogActionSocketFactory")
#endif // MALEANALOGACTIONSOCKETFACTORY_H
