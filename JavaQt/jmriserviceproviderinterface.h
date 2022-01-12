#ifndef JMRISERVICEPROVIDERINTERFACE_H
#define JMRISERVICEPROVIDERINTERFACE_H
#include <QtCore>
/**
 * Implementing or extending interfaces are available as Java Service Provider
 * Interfaces (SPI) within JMRI applications.
 *
 * This interface has no methods or fields and serves only to identify the
 * semantics of being a JMRI-specific SPI.
 *
 * @author Randall Wood (C) 2016
 */
/*public*/ /*interface*/ class JmriServiceProviderInterface //: public Bean
{
public:
 //JmriServiceProviderInterface(QObject* parent = 0) : Bean(parent) {}
};
Q_DECLARE_INTERFACE(JmriServiceProviderInterface, "JmriServiceProviderInterface")
#endif // JMRISERVICEPROVIDERINTERFACE_H
