#include "abstractstringexpression.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "defaultstringexpressionmanager.h"
#include "femalesocket.h"
/**
 *
 */
///*public*/  abstract class AbstractStringExpression extends AbstractBase
//        implements StringExpressionBean {



/*public*/  AbstractStringExpression::AbstractStringExpression(QString sys, QString user, QObject* parent) : AbstractBase(sys, user, parent)/*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
    setObjectName("AbstractStringExpression");

    // Do this test here to ensure all the tests are using correct system names
    Manager::NameValidity isNameValid = ((DefaultStringExpressionManager*)InstanceManager::getDefault("StringExpressionManager"))->validSystemNameFormat(mSystemName);
    if (isNameValid != Manager::NameValidity::VALID) {
        throw new IllegalArgumentException("system name is not valid");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Base* AbstractStringExpression::getParent() const {
    return _parent;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AbstractStringExpression::setParent(Base* parent) {
    _parent = parent;
}

//@Override
/*public*/  QString AbstractStringExpression::getBeanType() {
    return tr("StringExpression");
}

//@Override
/*public*/  void AbstractStringExpression::setState(int s) /*throws JmriException*/ {
    log->warn("Unexpected call to setState in AbstractStringExpression.");  // NOI18N
    _state = s;
}

//@Override
/*public*/  int AbstractStringExpression::getState() {
    log->warn("Unexpected call to getState in AbstractStringExpression.");  // NOI18N
    return _state;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AbstractStringExpression::setTriggerOnChange(bool triggerOnChange) {
    _triggerOnChange = triggerOnChange;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool AbstractStringExpression::getTriggerOnChange() {
    return _triggerOnChange;
}

/*public*/  QString AbstractStringExpression::getNewSocketName() {
    int x = 1;
    while (x < 10000) {     // Protect from infinite loop
        bool validName = true;
        for (int i=0; i < AbstractBase::getChildCount(); i++) {
            QString name = "E" + QString::number(x);
            if (name ==(AbstractBase::getChild(i)->getName())) {
                validName = false;
                break;
            }
        }
        if (validName) {
            return "E" +  QString::number(x);
        }
        x++;
    }
    throw new RuntimeException("Unable to find a new socket name");
}


/*private*/ /*final*/ /*static*/ Logger* AbstractStringExpression::log = LoggerFactory::getLogger("AbstractStringExpression");
