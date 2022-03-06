#include "abstractanalogaction.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultanalogactionmanager.h"
#include "runtimeexception.h"

/**
 * The base class for LogixNG AnalogActions
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  abstract class AbstractAnalogAction extends AbstractBase
//        implements AnalogActionBean {



/*public*/  AbstractAnalogAction::AbstractAnalogAction(QString sys, QString user, QObject *parent) :AbstractBase(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
    setObjectName("AbstractAnalogAction");
    // Do this test here to ensure all the tests are using correct system names
    Manager::NameValidity isNameValid = ((DefaultAnalogActionManager*)InstanceManager::getDefault("AnalogActionManager"))->AbstractBaseManager::validSystemNameFormat(mSystemName);
    if (isNameValid != Manager::NameValidity::VALID) {
        throw new IllegalArgumentException("system name is not valid");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Base* AbstractAnalogAction::getParent()const {
    return _parent;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AbstractAnalogAction::setParent(Base* parent) {
    _parent = parent;
}

//@Override
/*public*/  QString AbstractAnalogAction::getBeanType() {
    return tr("AnalogAction");
}

//@Override
/*public*/  void AbstractAnalogAction::setState(int s) /*throws JmriException*/ {
    log->warn("Unexpected call to setState in AbstractAnalogAction.");  // NOI18N
    _state = s;
}

//@Override
/*public*/  int AbstractAnalogAction::getState() {
    log->warn("Unexpected call to getState in AbstractAnalogAction.");  // NOI18N
    return _state;
}

/*public*/  QString AbstractAnalogAction::getNewSocketName() {
    int x = 1;
    while (x < 10000) {     // Protect from infinite loop
        bool validName = true;
        for (int i=0; i < getChildCount(); i++) {
            QString name = "A" + QString::number(x);
            if (name ==(getChild(i)->getName())) {
                validName = false;
                break;
            }
        }
        if (validName) {
            return "A" + QString::number(x);
        }
        x++;
    }
    throw new RuntimeException("Unable to find a new socket name");
}


/*private*/ /*final*/ /*static*/ Logger* AbstractAnalogAction::log = LoggerFactory::getLogger("AbstractAnalogAction");
