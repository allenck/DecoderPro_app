#include "dccaddressvarhandler.h"
#include "jtextfield.h"
#include "enumvariablevalue.h"
#include <QTimer>

//DccAddressVarHandler::DccAddressVarHandler(QObject *parent) :
//    QObject(parent)
//{
//}
/**
 * Encapulates DCC address handling logic in one place
 *
 *<p>Expects one or more of the variables called:
 *<ul>
 *<li>primaryAddr - Short Address
 *<li>extendAddr - Long Address
 *<li>addMode - Address Format (an Enum variable to select)
 *</ul>
 *and handles the cases where:
 *<ul>
 *<li>All three are present - the normal advanced decoder case
 *<li>Short Address is present and Long Address is not
 *<li>Long Address is present and Short Address is not
 *</ul>
 * At least one of Short Address and Long Address must be present!
 *
 * @author			Bob Jacobsen   Copyright (C) 2013
 * @version			$Revision: 24639 $
 */
// /*public*/ class DccAddressVarHandler {

/*public*/ DccAddressVarHandler::DccAddressVarHandler(VariableValue* primaryAddr, VariableValue* extendAddr, EnumVariableValue* addMode, JTextField* val, QObject *parent) : QObject(parent)
{
 this->primaryAddr = primaryAddr;
 this->extendAddr = extendAddr;
 this->addMode = addMode;
 this->val = val;
 log = new Logger("DccAddressVarHandler");
 QTimer::singleShot(10,this, SLOT(exec()));
}
void DccAddressVarHandler::exec()
{
 // check if only primary, or primary selected
 if (extendAddr == NULL || ( addMode != NULL && addMode->getValueString()!=("1") ) )
 {
  if (primaryAddr!=NULL)
  {
   doPrimary();
  }
 }
 else
 {
  doExtended();
 }
}

/**
 * Handle case of primary address valid
 */
/*protected*/ void DccAddressVarHandler::doPrimary() {}

/**
 * Handle case of extended address valid
 */
/*protected*/ void DccAddressVarHandler::doExtended() {}

