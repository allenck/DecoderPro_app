#include "defaultpowermanager.h"
#include "propertychangelistener.h"
#include "propertychangesupport.h"

//DefaultPowerManager::DefaultPowerManager()
//{

//}
/**
 * Default implementation for controlling layout power
 *
 * @author	Bob Jacobsen Copyright (C) 2001, 2008, 2010
 */
// /*public*/ class DefaultPowerManager implements PowerManager {

/*public*/ DefaultPowerManager::DefaultPowerManager(InternalSystemConnectionMemo *memo) : AbstractPowerManager(memo)
{

}

// to free resources when no longer used
//@Override
/*public*/ void DefaultPowerManager::dispose() //throws JmriException
{
}

