#include "abstractstringaction.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "defaultstringactionmanager.h"
#include "femalesocket.h"

/**
 * The base class for LogixNG AnalogActions
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  abstract class AbstractStringAction extends AbstractBase
//        implements StringActionBean {



/*public*/  AbstractStringAction::AbstractStringAction(QString sys, QString user, QObject* parent)
  : AbstractBase(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException */{
    //super(sys, user);

    // Do this test here to ensure all the tests are using correct system names
    Manager::NameValidity isNameValid = ((DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager"))->validSystemNameFormat(mSystemName);
    if (isNameValid != Manager::NameValidity::VALID) {
        throw new IllegalArgumentException("system name is not valid: " + sys);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Base* AbstractStringAction::getParent() const {
    return _parent;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AbstractStringAction::setParent(Base* parent) {
    _parent = parent;
}

//@Override
/*public*/  QString AbstractStringAction::getBeanType() {
    return tr("StringAction");
}

//@Override
/*public*/  void AbstractStringAction::setState(int s) /*throws JmriException*/ {
    log->warn("Unexpected call to setState in AbstractStringAction.");  // NOI18N
    _state = s;
}

//@Override
/*public*/  int AbstractStringAction::getState() {
    log->warn("Unexpected call to getState in AbstractStringAction.");  // NOI18N
    return _state;
}

/*public*/  QString AbstractStringAction::getNewSocketName() {
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


/*private*/ /*final*/ /*static*/ Logger* AbstractStringAction::log = LoggerFactory::getLogger("AbstractStringAction");

