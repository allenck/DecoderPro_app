#include "loglocalvariables.h"
#include "instancemanager.h"
#include "logixng/conditionalng.h"
#include "logixng/defaultdigitalactionmanager.h"
#include "loggerfactory.h"
#include "symboltable.h"
/**
 * This action prints the local variables to the log.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ class LogLocalVariables extends AbstractDigitalAction {


    /*public*/ LogLocalVariables::LogLocalVariables(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        // super(sys, user);
    setObjectName("LogLocalVariables");
    }

    //@Override
    /*public*/ Base* LogLocalVariables::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        LogLocalVariables* copy = new LogLocalVariables(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        return manager->registerAction(copy);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category LogLocalVariables::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void LogLocalVariables::execute() {
        ConditionalNG* c = getConditionalNG();
        log->warn(tr("LogLocalVariables_Start"));
        for (SymbolTable::Symbol* s : c->getSymbolTable()->getSymbols().values()) {
 // TODO:           log->warn(QString("    ")+tr("Name: %1, value: %2").arg(s->getName(), c->getSymbolTable()->getValue(s->getName())));
        }
        log->warn(tr("Log local variables done"));
    }

    //@Override
    /*public*/ FemaleSocket* LogLocalVariables::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int LogLocalVariables::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString LogLocalVariables::getShortDescription(QLocale locale) {
        return tr(/*locale,*/"LogLocalVariables");
    }

    //@Override
    /*public*/ QString LogLocalVariables::getLongDescription(QLocale locale) {
        return tr(/*locale, */"LogLocalVariables");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void LogLocalVariables::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void LogLocalVariables::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void LogLocalVariables::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void LogLocalVariables::disposeMe() {
    }

    /*private*/ /*final*/ /*static*/ Logger* LogLocalVariables::log = LoggerFactory::getLogger("LogLocalVariables");
