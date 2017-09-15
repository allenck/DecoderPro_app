#include "lnlightmanager.h"
#include "lnlight.h"

/*public*/ LnLightManager::LnLightManager(LnTrafficController* tc, QString prefix, QObject *parent) : AbstractLightManager(parent)
{
 _trafficController = tc;
 this->prefix = prefix;
}


/**
 *  Returns the system letter for Loconet
 */
/*public*/ QString LnLightManager::getSystemPrefix() { return prefix; }

/**
 * Method to create a new Light based on the system name
 * Returns null if the system name is not in a valid format
 * Assumes calling method has checked that a Light with this
 *    system name does not already exist
 */
/*public*/ Light* LnLightManager::createNewLight(QString systemName, QString userName)
{
 Light* lgt = NULL;
 // check if the output bit is available
 int bitNum = getBitFromSystemName(systemName);
 if (bitNum == 0) return (NULL);
 // Normalize the systemName
 QString sName = getSystemPrefix()+"L"+QString::number(bitNum);   // removes any leading zeros
 // make the new Light object
 lgt = (Light*)new LnLight(sName, userName, _trafficController, this);
 return lgt;
}

/**
 *  Get the bit address from the system name
 */
/*public*/ int LnLightManager::getBitFromSystemName (QString systemName)throw (Exception)
{
 // validate the system Name leader characters
 if ( (!systemName.startsWith(getSystemPrefix())) || (!systemName.startsWith(getSystemPrefix()+"L")) )
 {
  // here if an illegal loconet light system name
  log.error("illegal character in header field of loconet light system name: "+systemName);
  return (0);
 }
 // name must be in the LLnnnnn format
 int num = 0;
// try
// {
 bool bOK;
 num = systemName.mid(getSystemPrefix().length()+1, systemName.length()).toInt(&bOK);
 if(!bOK)
 {
  log.error("illegal character in number field of system name: "+systemName);
  return (0);
 }
 if (num<=0)
 {
  log.error("invalid loconet light system name: "+systemName);
  return (0);
 }
 else if (num>4096)
 {
  log.error("bit number out of range in loconet light system name: "+systemName);
  return (0);
 }
 return (num);
}

/**
 * Public method to validate system name format
 *   returns 'true' if system name has a valid format, else returns 'false'
 */
/*public*/ bool LnLightManager::validSystemNameFormat(QString systemName) {
 return (getBitFromSystemName(systemName)!=0);
}

/**
 * Public method to validate system name for configuration
 *   returns 'true' if system name has a valid meaning in current configuration,
 *      else returns 'false'
 *   for now, this method always returns 'true'; it is needed for the Abstract Light class
 */
/*public*/ bool LnLightManager::validSystemNameConfig(QString /*systemName*/) {
    return (true);
}

/**
 * A method that determines if it is possible to add a range of lights in numerical
 * order eg 11 thru 18, primarily used to show/not show the add range box in the add Light window
 **/
/*public*/ bool LnLightManager::allowMultipleAdditions(QString /*systemName*/) { return true;  }
