#include "valuequalifier.h"

//ValueQualifier::ValueQualifier(QObject *parent) :
//    AbstractQualifier(parent)
//{
//}
/**
 * Qualify a variable on greater than or equal a number
 *
 * @author			Bob Jacobsen   Copyright (C) 2010
 * @version			$Revision: 18542 $
 *
 */
///*public*/ class ValueQualifier extends ArithmeticQualifier {

/*public*/ ValueQualifier::ValueQualifier(VariableValue* qualifiedVal, VariableValue* watchedVal, int value, QString relation)
   :     ArithmeticQualifier(watchedVal, value, relation)
{
 this->qualifiedVal = qualifiedVal;
 setWatchedAvailable(currentDesiredState());
}

/*public*/ void ValueQualifier::setWatchedAvailable(bool enable)
{
 qualifiedVal->setAvailable(enable);
}

/*protected*/ bool ValueQualifier::currentAvailableState()
{
 return qualifiedVal->getAvailable();
}

