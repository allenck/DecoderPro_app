#include "lastresultofdigitalexpression.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "vptr.h"
#include "runtimeexception.h"
#include "conditionalng.h"

/**
 * Returns the last result of a digital expression.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class LastResultOfDigitalExpression extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  LastResultOfDigitalExpression::LastResultOfDigitalExpression(QString sys, QString user,QObject *parent)
 : AbstractDigitalExpression(sys, user,parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    }

    //@Override
    /*public*/  Base* LastResultOfDigitalExpression::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        LastResultOfDigitalExpression* copy = new LastResultOfDigitalExpression(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_digitalExpressionHandle != nullptr) copy->setDigitalExpression(_digitalExpressionHandle);
        return manager->registerExpression(copy);
    }

    /*public*/  void LastResultOfDigitalExpression::setDigitalExpression(/*@Nonnull*/ QString digitalExpressionName) {
        assertListenersAreNotRegistered(log, "setDigitalExpression");
//        DigitalExpressionBean* digitalExpression = (DigitalExpressionBean*)((DefaultDigitalExpressionManager*)
//                InstanceManager::getDefault("DigitalExpressionManager"))
//                        ->getNamedBean(digitalExpressionName)->self();
        DigitalExpressionBean* digitalExpression = nullptr;
        NamedBean* nb = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
          ->getNamedBean(digitalExpressionName);
        if(nb)
          digitalExpression = (DigitalExpressionBean*)nb->self();

        if (digitalExpression != nullptr) {
     //        DigitalExpressionBean* digitalExpression = (DigitalExpressionBean*)
            // We need the male socket, not the expression itself
            if (!(qobject_cast<MaleSocket*>(digitalExpression->self()))) {
                digitalExpression = (DigitalExpressionBean*)digitalExpression->getParent()->bself();
            }
            setDigitalExpression(digitalExpression);
        } else {
            removeDigitalExpression();
            log->error(tr("digitalExpression \"%1\" is not found").arg(digitalExpressionName));
        }
    }

    /*public*/  void LastResultOfDigitalExpression::setDigitalExpression(/*@Nonnull*/ NamedBeanHandle<DigitalExpressionBean*>* handle) {
        assertListenersAreNotRegistered(log, "setDigitalExpression");
        _digitalExpressionHandle = handle;
        ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void LastResultOfDigitalExpression::setDigitalExpression(/*@Nonnull*/ DigitalExpressionBean* digitalExpression) {
        assertListenersAreNotRegistered(log, "setDigitalExpression");
        setDigitalExpression(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(digitalExpression->getDisplayName(), digitalExpression));
    }

    /*public*/  void LastResultOfDigitalExpression::removeDigitalExpression() {
        assertListenersAreNotRegistered(log, "setDigitalExpression");
        if (_digitalExpressionHandle != nullptr) {
            ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _digitalExpressionHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<DigitalExpressionBean*>* LastResultOfDigitalExpression::getDigitalExpression() {
        return _digitalExpressionHandle;
    }

    //@Override
    /*public*/  void LastResultOfDigitalExpression::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<DigitalExpression>::asPtr(evt->getOldValue())) {
                if (VPtr<DigitalExpression>::asPtr(evt->getOldValue())== (getDigitalExpression()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Expression is in use by \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" ==(evt->getPropertyName())) { // No I18N
            if (VPtr<DigitalExpression>::asPtr(evt->getOldValue() )) {
                if (VPtr<DigitalExpression>::asPtr(evt->getOldValue()) == (getDigitalExpression()->getBean())) {
                    removeDigitalExpression();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category LastResultOfDigitalExpression::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool LastResultOfDigitalExpression::evaluate() {
        if (_digitalExpressionHandle != nullptr) {
            MaleSocket* m = (MaleSocket*) _digitalExpressionHandle->getBean()->self();
            while ((m != nullptr) && (! (qobject_cast<MaleDigitalExpressionSocket*>(m->bself())))) {
                m = (MaleSocket*) m->getObject()->bself();
            }
            if (m == nullptr) {
                throw new RuntimeException("The digital expression "
                        + _digitalExpressionHandle->getName()
                        + " is not contained in a DigitalExpressionSocket");
            }
            return ((MaleDigitalExpressionSocket*)m->bself())->getLastResult();
        }
        return false;
    }

    //@Override
    /*public*/  FemaleSocket* LastResultOfDigitalExpression::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int LastResultOfDigitalExpression::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString LastResultOfDigitalExpression::getShortDescription(QLocale locale) {
        return tr(/*locale, */"LastResultOfDigitalExpression");
    }

    //@Override
    /*public*/  QString LastResultOfDigitalExpression::getLongDescription(QLocale locale) {
        QString beanName;
        if (_digitalExpressionHandle != nullptr) {
            beanName = _digitalExpressionHandle->getBean()->getDisplayName();
        } else {
            beanName = tr(/*locale, */ "''");
        }
        return tr(/*locale, */"Last result of digital expression \"%1\"").arg(
                beanName);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LastResultOfDigitalExpression::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LastResultOfDigitalExpression::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_digitalExpressionHandle != nullptr)) {
//            _digitalExpressionHandle->getBean()
//                    ->NamedBean::addPropertyChangeListener(PROPERTY_LAST_RESULT_CHANGED, this);
            ((AbstractNamedBean*)_digitalExpressionHandle->getBean()->self())
                    ->addPropertyChangeListener(PROPERTY_LAST_RESULT_CHANGED, this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LastResultOfDigitalExpression::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _digitalExpressionHandle->getBean()
                    ->NamedBean::removePropertyChangeListener(PROPERTY_LAST_RESULT_CHANGED, this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LastResultOfDigitalExpression::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void LastResultOfDigitalExpression::disposeMe() {
    }

    /*private*/ /*final*/ /*static*/ Logger* LastResultOfDigitalExpression::log = LoggerFactory::getLogger("LastResultOfDigitalExpression");
