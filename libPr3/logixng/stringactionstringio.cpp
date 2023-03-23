#include "stringactionstringio.h"
#include "abstractstringiomanager.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "logixng/defaultstringactionmanager.h"
#include "logixng/stringio.h"
#include "vptr.h"

/**
 * Sets a StringIO.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/ class StringActionStringIO extends AbstractStringAction
//        implements VetoableChangeListener {


    /*public*/ StringActionStringIO::StringActionStringIO(QString sys, QString user, QObject* parent)
    : AbstractStringAction(sys, user, parent){
        //super(sys, user);
     setObjectName("StringActionStringIO");
    }

    //@Override
    /*public*/ Base* StringActionStringIO::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) {
        StringActionManager* manager = (DefaultStringActionManager*)InstanceManager::getDefault("StringActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        StringActionStringIO* copy = new StringActionStringIO(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_stringIOHandle != nullptr) copy->setStringIO(_stringIOHandle);
        return manager->registerAction(copy);
    }

    /*public*/ void StringActionStringIO::setStringIO(/*@Nonnull*/ QString stringIOName) {
        assertListenersAreNotRegistered(log, "setStringIO");
        StringIO* stringIO = (StringIO*)((AbstractStringIOManager*)InstanceManager::getDefault("StringIOManager"))->getNamedBean(stringIOName)->self();
        if (stringIO != nullptr) {
            setStringIO(stringIO);
        } else {
            removeStringIO();
            log->error(tr("stringIO \"%1\" is not found").arg(stringIOName));
        }
    }

    /*public*/ void StringActionStringIO::StringActionStringIO::setStringIO(/*@Nonnull*/ NamedBeanHandle<StringIO*>* handle) {
        assertListenersAreNotRegistered(log, "setStringIO");
        _stringIOHandle = handle;
        ((AbstractStringIOManager*)InstanceManager::getDefault("StringIOManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void StringActionStringIO::setStringIO(/*@Nonnull*/ StringIO* stringIO) {
        assertListenersAreNotRegistered(log, "setStringIO");
        setStringIO(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                    ->getNamedBeanHandle(stringIO->getDisplayName(), stringIO));
    }

    /*public*/ void StringActionStringIO::removeStringIO() {
        assertListenersAreNotRegistered(log, "setStringIO");
        if (_stringIOHandle != nullptr) {
            ((AbstractStringIOManager*)InstanceManager::getDefault("StringIOManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _stringIOHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<StringIO*>* StringActionStringIO::getStringIO() {
        return _stringIOHandle;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void StringActionStringIO::setValue(QString value) /*throws JmriException*/ {
        if (_stringIOHandle != nullptr) {
            _stringIOHandle->getBean()->setCommandedStringValue(value);
        }
    }

    //@Override
    /*public*/ void StringActionStringIO::vetoableChange(PropertyChangeEvent* evt) /*throws PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<StringIO>::asPtr(evt->getOldValue())) {
                if (VPtr<StringIO>::asPtr(evt->getOldValue())->equals(getStringIO()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("StringIO is in use by StringIO action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<StringIO>::asPtr(evt->getOldValue() )) {
                if (VPtr<StringIO>::asPtr(evt->getOldValue())->equals(getStringIO()->getBean())) {
                    removeStringIO();
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ FemaleSocket* StringActionStringIO::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ int StringActionStringIO::getChildCount() {
        return 0;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category StringActionStringIO::getCategory() {
        return Category::ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString StringActionStringIO::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "StringActionStringIO_Short");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ QString StringActionStringIO::getLongDescription(QLocale locale) {
        if (_stringIOHandle != nullptr) {
            return tr(/*locale,*/ "").arg(_stringIOHandle->getBean()->getDisplayName());
        } else {
            return tr(/*locale,*/ "Set stringIO %1").arg("none");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void StringActionStringIO::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void StringActionStringIO::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void StringActionStringIO::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void StringActionStringIO::disposeMe() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void StringActionStringIO::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: StringActionStringIO: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
    if (getStringIO() != nullptr && bean->equals(getStringIO()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* StringActionStringIO::log = LoggerFactory::getLogger("StringActionStringIO");
