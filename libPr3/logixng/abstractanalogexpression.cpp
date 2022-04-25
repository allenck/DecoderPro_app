#include "abstractanalogexpression.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "analogexpressionmanager.h"
#include "runtimeexception.h"
#include "defaultanalogexpressionmanager.h"

/**
 *
 */
///*public*/  abstract class AbstractAnalogExpression extends AbstractBase
//        implements AnalogExpressionBean {



    /*public*/  AbstractAnalogExpression::AbstractAnalogExpression(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractBase(sys, user, parent) {
        //super(sys, user);

        // Do this test here to ensure all the tests are using correct system names
        Manager::NameValidity isNameValid = ((DefaultAnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager"))->validSystemNameFormat(mSystemName);
        if (isNameValid != Manager::NameValidity::VALID) {
            throw new IllegalArgumentException("system name is not valid");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Base* AbstractAnalogExpression::getParent() const {
        return _parent;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractAnalogExpression::setParent(Base* parent) {
        _parent = parent;
    }

    //@Override
    /*public*/  QString AbstractAnalogExpression:: getBeanType() {
        return tr("AnalogExpression");
    }

    //@Override
    /*public*/  void AbstractAnalogExpression::setState(int s) /*throws JmriException*/ {
        log->warn("Unexpected call to setState in AbstractAnalogExpression.");  // NOI18N
        _state = s;
    }

    //@Override
    /*public*/  int AbstractAnalogExpression::getState() {
        log->warn("Unexpected call to getState in AbstractAnalogExpression.");  // NOI18N
        return _state;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractAnalogExpression::setTriggerOnChange(bool triggerOnChange) {
        _triggerOnChange = triggerOnChange;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool AbstractAnalogExpression::getTriggerOnChange() {
        return _triggerOnChange;
    }

    /*public*/  QString AbstractAnalogExpression::getNewSocketName() {
        int x = 1;
        while (x < 10000) {     // Protect from infinite loop
            bool validName = true;
            for (int i=0; i < AbstractBase::getChildCount(); i++) {
                QString name = "E" + QString::number(x);
                if (name == (AbstractBase::getChild(i)->getName())) {
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


    /*private*/ /*final*/ /*static*/ /*org.slf4j.*/Logger* AbstractAnalogExpression::log = LoggerFactory::getLogger("AbstractAnalogExpression");
