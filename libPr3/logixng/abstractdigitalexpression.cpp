#include "abstractdigitalexpression.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "runtimeexception.h"

/**
 *
 */
///*public*/  abstract class AbstractDigitalExpression extends AbstractBase
//        implements DigitalExpressionBean {

/*public*/  AbstractDigitalExpression::AbstractDigitalExpression(QString sys, QString user, QObject* parent) : AbstractBase(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
 setObjectName("AbstractDigitalExpression");

    // Do this test here to ensure all the tests are using correct system names
    Manager::NameValidity isNameValid = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->validSystemNameFormat(mSystemName);
    if (isNameValid != Manager::NameValidity::VALID) {
        throw new IllegalArgumentException("system name is not valid");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void AbstractDigitalExpression::notifyChangedResult(bool oldResult, bool newResult) {
    firePropertyChange(Base::PROPERTY_LAST_RESULT_CHANGED, oldResult, newResult);
}

/** {@inheritDoc} */
//@Override
/*public*/  Base* AbstractDigitalExpression::getParent() const {
    return _parent;
}

/** {@inheritDoc} */
//@Override
/*public*/  void AbstractDigitalExpression::setParent(Base* parent) {
    _parent = parent;
}

/** {@inheritDoc} */
//@Override
/*public*/  QString AbstractDigitalExpression::getBeanType() {
    return tr("Digital expression");
}

/** {@inheritDoc} */
//@Override
/*public*/  void AbstractDigitalExpression::setState(int s) /*throws JmriException*/ {
    log->warn("Unexpected call to setState in AbstractDigitalExpression.");  // NOI18N
    _state = s;
}

/** {@inheritDoc} */
//@Override
/*public*/  int AbstractDigitalExpression::getState() {
    log->warn("Unexpected call to getState in AbstractDigitalExpression.");  // NOI18N
    return _state;
}

/*public*/  QString AbstractDigitalExpression::getNewSocketName() {
    QVector<QString> names = QVector<QString>(getChildCount());
    for (int i=0; i < getChildCount(); i++) {
        names[i] = getChild(i)->getName();
    }
    return getNewSocketName(names);
}

/*public*/  /*static*/ QString AbstractDigitalExpression::getNewSocketName(QVector<QString> names) {
    int x = 1;
    while (x < 10000) {     // Protect from infinite loop
        bool validName = true;
        for (int i=0; i < names.length(); i++) {
            QString name = "E" + QString::number(x);
            if (name == (names[i])) {
                validName = false;
                break;
            }
        }
        if (validName) {
            return "E" + QString::number(x);
        }
        x++;
    }
    throw new RuntimeException("Unable to find a new socket name");
}


/*private*/ /*final*/ /*static*/ Logger* AbstractDigitalExpression::log = LoggerFactory::getLogger("AbstractDigitalExpression");

