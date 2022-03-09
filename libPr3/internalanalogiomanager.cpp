#include "internalanalogiomanager.h"
#include "internalsystemconnectionmemo.h"

/**
 * Implement a AnalogIOManager for "Internal" (virtual) AnalogIOs.
 *
 * @author Bob Jacobsen      Copyright (C) 2009
 * @author Daniel Bergqvist  Copyright (C) 2020
 */
// /*public*/ class InternalAnalogIOManager extends jmri.managers.AbstractAnalogIOManager {

/*public*/ InternalAnalogIOManager::InternalAnalogIOManager(InternalSystemConnectionMemo* memo, QObject* parent)
 : AbstractAnalogIOManager(memo, parent) {
    //super(memo);
 setObjectName("InternalAnalogIOManager");
}

/**
 * {@inheritDoc}
 */
//@Override
//@Nonnull
/*public*/ SystemConnectionMemo* InternalAnalogIOManager::getMemo() {
    return (InternalSystemConnectionMemo*) memo;
}
