#include "analogexpressionanalogio.h"
#include "analogexpressionmanager.h"
#include "instancemanager.h"
#include "namedbean.h"
#include "vptr.h"
#include "analogio.h"
#include "analogiomanager.h"
#include "loggerfactory.h"
#include "typeconversionutil.h"
#include "conditionalng.h"

/**
 * Reads a AnalogIO.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class AnalogExpressionAnalogIO extends AbstractAnalogExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  AnalogExpressionAnalogIO::AnalogExpressionAnalogIO(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractAnalogExpression(sys, user, parent) {

        //super(sys, user);
    }

    //@Override
    /*public*/  Base* AnalogExpressionAnalogIO::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
        AnalogExpressionManager* manager = (AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        AnalogExpressionAnalogIO* copy = new AnalogExpressionAnalogIO(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_analogIOHandle != nullptr) copy->setAnalogIO(_analogIOHandle);
        return manager->registerExpression(copy)->Base::deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<AnalogIO>::asPtr(evt->getOldValue())) {
                if (VPtr<AnalogIO>::asPtr(evt->getOldValue()) == (getAnalogIO()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("AnalogIO is in use by AnalogIO expression \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" ==(evt->getPropertyName())) { // No I18N
            if (VPtr<AnalogIO>::asPtr(evt->getOldValue())) {
                if (VPtr<AnalogIO>::asPtr(evt->getOldValue()) ==(getAnalogIO()->getBean())) {
                    removeAnalogIO();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category AnalogExpressionAnalogIO::getCategory() {
        return Category::ITEM;
    }

    /*public*/  void AnalogExpressionAnalogIO::setAnalogIO(/*@Nonnull*/ QString analogIOName) {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        AnalogIO* analogIO = (AnalogIO*)((AnalogIOManager*)InstanceManager::getDefault("AnalogIOManager"))->getNamedBean(analogIOName)->self();
        if (analogIO != nullptr) {
            setAnalogIO(analogIO);
        } else {
            removeAnalogIO();
            log->error(tr("analogIO \"%1\" is not found").arg(analogIOName));
        }
    }

    /*public*/  void AnalogExpressionAnalogIO::setAnalogIO(/*@Nonnull*/ NamedBeanHandle<AnalogIO*>* handle) {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        _analogIOHandle = handle;
        ((AnalogIOManager*)InstanceManager::getDefault("AnalogIOManager"))->addVetoableChangeListener(this);
    }

    /*public*/  void AnalogExpressionAnalogIO::setAnalogIO(/*@Nonnull*/ AnalogIO* analogIO) {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        setAnalogIO(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(analogIO->getDisplayName(), analogIO));
    }

    /*public*/  void AnalogExpressionAnalogIO::removeAnalogIO() {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        if (_analogIOHandle != nullptr) {
            ((AnalogIOManager*)InstanceManager::getDefault("AnalogIOManager"))->removeVetoableChangeListener(this);
            _analogIOHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<AnalogIO*>* AnalogExpressionAnalogIO::getAnalogIO() {
        return _analogIOHandle;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  double AnalogExpressionAnalogIO::evaluate() {
        if (_analogIOHandle != nullptr) {
            return TypeConversionUtil::convertToDouble(_analogIOHandle->getBean()->getKnownAnalogValue(), false);
        } else {
            return 0.0;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleSocket* AnalogExpressionAnalogIO::getChild(int index)
            /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int AnalogExpressionAnalogIO::getChildCount() {
        return 0;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AnalogExpressionAnalogIO::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "AnalogIO");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  QString AnalogExpressionAnalogIO::getLongDescription(QLocale locale) {
        if (_analogIOHandle != nullptr) {
            return tr(/*locale, */"Get analog constant %1").arg(_analogIOHandle->getBean()->getDisplayName());
        } else {
            return tr(/*locale,*/ "Get analog constant %1").arg("none");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::registerListenersForThisClass() {
        if ((! _listenersAreRegistered) && (_analogIOHandle != nullptr)) {
            _analogIOHandle->getBean()->addPropertyChangeListener("value", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _analogIOHandle->getBean()->removePropertyChangeListener("value", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::propertyChange(PropertyChangeEvent* evt) {
        if (getTriggerOnChange()) {
            AbstractBase::getConditionalNG()->execute();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::disposeMe() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: AnalogExpressionAnalogIO: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getAnalogIO() != nullptr && bean->equals(getAnalogIO()->getBean()->self())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* AnalogExpressionAnalogIO::log = LoggerFactory::getLogger("AnalogExpressionAnalogIO");
