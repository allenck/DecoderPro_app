#ifndef JMRISERVICEPROVIDERINTERFACE_H
#define JMRISERVICEPROVIDERINTERFACE_H
#include "bean.h"
/**
 * Implementing or extending interfaces are available as Java Service Provider
 * Interfaces (SPI) within JMRI applications.
 *
 * This interface has no methods or fields and serves only to identify the
 * semantics of being a JMRI-specific SPI.
 *
 * @author Randall Wood (C) 2016
 */
/*public*/ /*interface*/ class JmriServiceProviderInterface : public Bean
{

};
#endif // JMRISERVICEPROVIDERINTERFACE_H
