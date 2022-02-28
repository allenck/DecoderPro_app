#include "abstractdigitalbooleanaction.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalbooleanactionmanager.h"
#include "runtimeexception.h"
/**
 * The base class for LogixNG Boolean Actions
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  abstract class AbstractDigitalBooleanAction extends AbstractBase
//        implements DigitalBooleanActionBean {


    /*public*/  AbstractDigitalBooleanAction::AbstractDigitalBooleanAction(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractBase(sys, user, parent){
        //super(sys, user);
        setObjectName("AbstractDigitalBooleanAction");

        // Do this test here to ensure all the tests are using correct system names
        Manager::NameValidity isNameValid = ((DefaultDigitalBooleanActionManager*)InstanceManager::getDefault("DigitalBooleanActionManager"))->validSystemNameFormat(mSystemName);
        if (isNameValid != Manager::NameValidity::VALID) {
            throw new IllegalArgumentException("system name is not valid: "+mSystemName);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Base* AbstractDigitalBooleanAction::getParent() const {
        return _parent;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractDigitalBooleanAction::setParent(Base* parent) {
        _parent = parent;
    }

    /*public*/  QString AbstractDigitalBooleanAction::getNewSocketName() {
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

    //@Override
    /*public*/  QString AbstractDigitalBooleanAction::getBeanType() {
        return tr("DigitalBooleanAction");
    }

    //@Override
    /*public*/  void AbstractDigitalBooleanAction::setState(int s) /*throws JmriException*/ {
        log->warn("Unexpected call to setState in AbstractDigitalBooleanAction.");  // NOI18N
        _state = s;
    }

    //@Override
    /*public*/  int AbstractDigitalBooleanAction::getState() {
        log->warn("Unexpected call to getState in AbstractDigitalBooleanAction.");  // NOI18N
        return _state;
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractDigitalBooleanAction::log = LoggerFactory::getLogger("AbstractDigitalBooleanAction");

