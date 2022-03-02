#ifndef LOGIXNG_MANAGER_CPP
#define LOGIXNG_MANAGER_CPP
#include "logixng_manager.h"
#include "loggerfactory.h"

/**
 * Test if parameter is a properly formatted system name.
 * <P>
 * This method should only be used by the managers of the LogixNG system.
 *
 * @param subSystemNamePrefix the sub system prefix
 * @param systemName the system name
 * @return enum indicating current validity, which might be just as a prefix
 */
/*public*/ /*static*/ Manager::NameValidity LogixNG_Manager::ng_validSystemNameFormat(QString subSystemNamePrefix, QString systemName) {
 QRegularExpressionMatch* match = new  QRegularExpressionMatch();
 // System names with digits. :AUTO: is generated system names
 if (systemName.contains(QRegularExpression(subSystemNamePrefix+"(:AUTO:)?\\d+"), match) && match->capturedLength()== systemName.length()) {
     return NameValidity::VALID;

 // System names with dollar sign allow any characters in the name
 } else if (systemName.contains(QRegularExpression(subSystemNamePrefix+"\\$.+"))) {
     return NameValidity::VALID;

 // System names with :JMRI: belongs to JMRI itself
 } else if (systemName.contains(QRegularExpression(subSystemNamePrefix+":JMRI:.+"))) {
     return NameValidity::VALID;

 // System names with :JMRI-LIB: belongs to software that uses JMRI as a lib
 } else if (systemName.contains(QRegularExpression(subSystemNamePrefix+":JMRI-LIB:.+"))) {
     return NameValidity::VALID;

 // Other system names are not valid
 } else {
         LoggerFactory::getLogger("LogixNG_Manager")
                 ->warn(QString("system name %1 is invalid for sub system prefix %2").arg(
                         systemName, subSystemNamePrefix));
     return NameValidity::INVALID;
 }
}
#endif // LOGIXNG_MANAGER_CPP
