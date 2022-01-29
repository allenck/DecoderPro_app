#include "abstractdigitalaction.h"
#include "digitalactionmanager.h"
#include "loggerfactory.h"
#include "runtimeexception.h"
#include "instancemanager.h"
#include "manager.h"
/**
 * The base class for LogixNG Actions
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  abstract class AbstractDigitalAction extends AbstractBase
//        implements DigitalActionBean {

    /*public*/  AbstractDigitalAction::AbstractDigitalAction(QString sys, QString user, QObject* parent) : AbstractBase(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);

        // Do this test here to ensure all the tests are using correct system names
        Manager::NameValidity isNameValid = ((DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))->validSystemNameFormat(mSystemName);
        if (isNameValid != Manager::NameValidity::VALID) {
            throw new IllegalArgumentException("system name is not valid: "+mSystemName);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Base* AbstractDigitalAction::getParent() const{
        return _parent;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AbstractDigitalAction::setParent(Base* parent) {
        _parent = parent;
    }

    /*public*/  QString AbstractDigitalAction::getNewSocketName() {
        QVector<QString> names = QVector<QString>(Base::getChildCount());
        for (int i=0; i < Base::getChildCount(); i++) {
            names[i] = Base::getChild(i)->getName();
        }
        return getNewSocketName(names);
    }

    /*public*/  /*static*/ QString AbstractDigitalAction::getNewSocketName(QVector<QString> names) {
        int x = 1;
        while (x < 10000) {     // Protect from infinite loop
            bool validName = true;
            for (int i=0; i < names.length(); i++) {
                QString name = "A" + QString::number(x);
                if (name == (names[i])) {
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
    /*public*/  QString AbstractDigitalAction::getBeanType() {
        return tr("DigitalAction");
    }

    //@Override
    /*public*/  void AbstractDigitalAction::setState(int s) /*throws JmriException*/ {
        log->warn("Unexpected call to setState in AbstractDigitalAction.");  // NOI18N
        _state = s;
    }

    //@Override
    /*public*/  int AbstractDigitalAction::getState() {
        log->warn("Unexpected call to getState in AbstractDigitalAction.");  // NOI18N
        return _state;
    }


    /*private*/ /*final*/ /*static*/ Logger* AbstractDigitalAction::log = LoggerFactory::getLogger("AbstractDigitalAction");

