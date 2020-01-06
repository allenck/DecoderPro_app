#include "restartstartupactionfactory.h"

RestartStartupActionFactory::RestartStartupActionFactory(QObject* parent) : AbstractStartupActionFactory(parent)
{

}
/**
 * Factory to register Restart action as a startup action.
 *
 * @author Randall Wood Copyright (C) 2016
 */
///*public*/ class RestartStartupActionFactory extends AbstractStartupActionFactory {

//@Override
/*public*/ QString RestartStartupActionFactory::getTitle(/*Class<?> */QString clazz, QLocale /*locale*/) throw (IllegalArgumentException) {
    if (clazz != ("RestartAction")) {
        throw IllegalArgumentException();
    }
    return tr(/*locale, */"RestartAction"); // NOI18N
}

//@Override
/*public*/ QStringList RestartStartupActionFactory::getActionClasses() {
    //return new Class[]{RestartAction.class};
 QStringList l = QStringList();
 l << "RestartAction";
}
