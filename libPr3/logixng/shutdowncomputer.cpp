#include "shutdowncomputer.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "logixng/defaultdigitalactionmanager.h"

/**
 * This action sets the state of a turnout.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/ class ShutdownComputer extends AbstractDigitalAction {



    /*public*/ ShutdownComputer::ShutdownComputer(QString sys, QString user, QObject* parent)
    : AbstractDigitalAction(sys,user, parent)
            /*throws BadUserNameException, BadSystemNameException */{
        //super(sys, user);
     setObjectName("ShutdownComputer");
    }

    //@Override
    /*public*/ Base* ShutdownComputer::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ShutdownComputer* copy = new ShutdownComputer(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setOperation(_operation);
        return manager->registerAction(copy);
    }

    /*public*/ void ShutdownComputer::setOperation(Operation::TYPE operation) {
        _operation = operation;
    }

    /*public*/ ShutdownComputer::Operation::TYPE ShutdownComputer::getOperation() {
        return _operation;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ShutdownComputer::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ShutdownComputer::execute() {
#if 0
        ThreadingUtil.runOnGUI(() -> {
            switch (_operation) {
                case ShutdownComputer:
                    InstanceManager.getDefault(ShutDownManager.class).shutdownOS();
                    break;

                case RebootComputer:
                    InstanceManager.getDefault(ShutDownManager.class).restartOS();
                    break;

                case ShutdownJMRI:
                    InstanceManager.getDefault(ShutDownManager.class).shutdown();
                    break;

                case RebootJMRI:
                    InstanceManager.getDefault(ShutDownManager.class).restart();
                    break;

                default:
                    throw new RuntimeException("_operation has invalid value: "+_operation.name());
            }
        });
#endif
        ThreadingUtil* tu = new SD_ThreadingUtil(_operation);
        // If we are here, shutdown has failed
        log->error("Shutdown failed");  // NOI18N
    }

    //@Override
    /*public*/ FemaleSocket* ShutdownComputer::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ShutdownComputer::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ShutdownComputer::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ShutdownComputer");
    }

    //@Override
    /*public*/ QString ShutdownComputer::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Shutdown JMRI/computer: %1").arg(Operation::toString(_operation));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ShutdownComputer::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ShutdownComputer::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ShutdownComputer::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ShutdownComputer::disposeMe() {
    }



//    /*public*/ enum Operation {
//        ShutdownComputer(Bundle.getMessage("ShutdownComputer_ShutdownComputer")),
//        RebootComputer(Bundle.getMessage("ShutdownComputer_RebootComputer")),
//        ShutdownJMRI(Bundle.getMessage("ShutdownComputer_ShutdownJMRI")),
//        RebootJMRI(Bundle.getMessage("ShutdownComputer_RebootJMRI"));

//        /*private*/ final QString _text;

//        /*private*/ Operation(QString text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/ QString toString() {
//            return _text;
//        }

//    }


    /*private*/ /*final*/ /*static*/ Logger* ShutdownComputer::log = LoggerFactory::getLogger("ShutdownComputer");
