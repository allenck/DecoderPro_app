#include "internalmetermanager.h"
#include "internalsystemconnectionmemo.h"

/**
 * Implement a MeterManager for "Internal" (virtual) Meters.
 *
 * @author Bob Jacobsen      Copyright (C) 2009
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
///*public*/ class InternalMeterManager extends jmri.managers.AbstractMeterManager {

    /*public*/ InternalMeterManager::InternalMeterManager(InternalSystemConnectionMemo* memo, QObject* parent)
        : AbstractMeterManager(memo, parent)
    {
        //super(memo);
    }

    /**
     * {@inheritDoc}
     */
    //@Override
    //@Nonnull
    /*public*/ SystemConnectionMemo *InternalMeterManager::getMemo() const {
        return (SystemConnectionMemo*) memo;
    }
