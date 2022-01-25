#ifndef MALEDIGITALACTIONSOCKETFACTORY_H
#define MALEDIGITALACTIONSOCKETFACTORY_H
#include "malesocketfactory.h"
#include "maledigitalactionsocket.h"

/**
 * Factory class for MaleDigitalActionSocket classes.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
/*public*/ /*interface*/class MaleDigitalActionSocketFactory : public MaleSocketFactory<MaleDigitalActionSocket> {
 Q_INTERFACES(MaleSocketFactory<MaleDigitalActionSocket>)
};
Q_DECLARE_INTERFACE(MaleDigitalActionSocketFactory, "MaleDigitalActionSocketFactory")
#endif // MALEDIGITALACTIONSOCKETFACTORY_H
