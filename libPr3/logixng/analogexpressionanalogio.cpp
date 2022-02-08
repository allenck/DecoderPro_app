#include "analogexpressionanalogio.h"
#include "analogexpressionmanager.h"
#include "instancemanager.h"
#include "namedbean.h"
#include "vptr.h"
#include "analogio.h"


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
    /*public*/  Base* AnalogExpressionAnalogIO::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
        AnalogExpressionManager* manager = (AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString sysName = systemNames.value(AbstractBase::getSystemName());
        QString userName = userNames.value(AbstractBase::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        AnalogExpressionAnalogIO* copy = new AnalogExpressionAnalogIO(sysName, userName);
        copy->AbstractBase::setComment(AbstractBase::getComment());
        if (_analogIOHandle != nullptr) copy->setAnalogIO(_analogIOHandle);
        return manager->registerExpression(copy)->Base::deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<AnalogIO>::asPtr(evt->getOldValue())) {
                if (VPtr<AnalogIO>::asPtr(evt->getOldValue())->equals(getAnalogIO()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("AnalogIO is in use by AnalogIO expression \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" ==(evt->getPropertyName())) { // No I18N
            if (VPtr<AnalogIO>::asPtr(evt->getOldValue())) {
                if (VPtr<AnalogIO>::asPtr(evt.getOldValue()) ==(getAnalogIO().getBean())) {
                    removeAnalogIO();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* getCategory() {
        return Category::ITEM;
    }

    /*public*/  void setAnalogIO(/*@Nonnull*/ QString analogIOName) {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        AnalogIO analogIO = InstanceManager.getDefault(AnalogIOManager.class).getNamedBean(analogIOName);
        if (analogIO != null) {
            setAnalogIO(analogIO);
        } else {
            removeAnalogIO();
            log.error("analogIO \"{}\" is not found", analogIOName);
        }
    }

    /*public*/  void setAnalogIO(/*@Nonnull*/ NamedBeanHandle<AnalogIO> handle) {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        _analogIOHandle = handle;
        InstanceManager.getDefault(AnalogIOManager.class).addVetoableChangeListener(this);
    }

    /*public*/  void setAnalogIO(/*@Nonnull*/ AnalogIO analogIO) {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        setAnalogIO(InstanceManager.getDefault(NamedBeanHandleManager.class)
                .getNamedBeanHandle(analogIO.getDisplayName(), analogIO));
    }

    /*public*/  void removeAnalogIO() {
        assertListenersAreNotRegistered(log, "setAnalogIO");
        if (_analogIOHandle != null) {
            InstanceManager.getDefault(AnalogIOManager.class).removeVetoableChangeListener(this);
            _analogIOHandle = null;
        }
    }

    /*public*/  NamedBeanHandle<AnalogIO> getAnalogIO() {
        return _analogIOHandle;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  double evaluate() {
        if (_analogIOHandle != null) {
            return jmri.util.TypeConversionUtil.convertToDouble(_analogIOHandle.getBean().getKnownAnalogValue(), false);
        } else {
            return 0.0;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  FemaleSocket getChild(int index)
            throws IllegalArgumentException, UnsupportedOperationException {
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  int getChildCount() {
        return 0;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  String getShortDescription(Locale locale) {
        return Bundle.getMessage(locale, "AnalogExpressionAnalogIO_Short");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  String getLongDescription(Locale locale) {
        if (_analogIOHandle != null) {
            return Bundle.getMessage(locale, "AnalogExpressionAnalogIO_Long", _analogIOHandle.getBean().getDisplayName());
        } else {
            return Bundle.getMessage(locale, "AnalogExpressionAnalogIO_Long", "none");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void registerListenersForThisClass() {
        if ((! _listenersAreRegistered) && (_analogIOHandle != null)) {
            _analogIOHandle.getBean().addPropertyChangeListener("value", this);
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _analogIOHandle.getBean().removePropertyChangeListener("value", this);
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void propertyChange(PropertyChangeEvent evt) {
        if (getTriggerOnChange()) {
            getConditionalNG().execute();
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void disposeMe() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogExpressionAnalogIO::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*> report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: AnalogExpressionAnalogIO: bean = %1, report = %2").arg(cdl.get, report);
        if (getAnalogIO() != null && bean.equals(getAnalogIO().getBean())) {
            report.add(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription()));
        }
    }

    /*private*/ /*final*/ static Logger* AnalogExpressionAnalogIO::log = LoggerFactory::getLogger("AnalogExpressionAnalogIO");
