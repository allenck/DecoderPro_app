#include "jcomponentqualifier.h"

//JComponentQualifier::JComponentQualifier(QObject *parent) :
//    ArithmeticQualifier(parent)
//{
//}
/**
 * Qualify a JComponent on a numerical test
 * by setting the JComponent's visibility
 *
 * @author			Bob Jacobsen   Copyright (C) 2010, 2014
 * @version			$Revision: 25044 $
 *
 */
///*public*/ class JComponentQualifier extends ArithmeticQualifier {



/*public*/ JComponentQualifier::JComponentQualifier(QWidget* component, VariableValue* watchedVal, int value, QString relation, QObject *parent) : ArithmeticQualifier(watchedVal, value, relation, parent)
{
 //super(watchedVal, value, relation);

 this->component = component;

 setWatchedAvailable(currentDesiredState());
}

/*public*/ void JComponentQualifier::setWatchedAvailable(bool enable) {
    component->setVisible(enable);
}

/*protected*/ bool JComponentQualifier::currentAvailableState() {
    return component->isVisible();
}
