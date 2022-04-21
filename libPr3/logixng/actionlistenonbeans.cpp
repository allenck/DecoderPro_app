#include "actionlistenonbeans.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "defaultconditionalng.h"

/**
 * This action listens on some beans and runs the ConditionalNG on property change.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class ActionListenOnBeans extends AbstractDigitalAction
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  ActionListenOnBeans::ActionListenOnBeans(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ActionListenOnBeans");
    }

    //@Override
    /*public*/  Base* ActionListenOnBeans::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionListenOnBeans* copy = new ActionListenOnBeans(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        for (NamedBeanReference* reference : _namedBeanReferences.values()) {
            copy->addReference(reference);
        }
        return manager->registerAction(copy);
    }

    /**
     * Register a bean
     * The bean must be on the form "beantype:name" where beantype is for
     * example turnout, sensor or memory, and name is the name of the bean.
     * The type can be upper case or lower case, it doesn't matter.
     * @param beanAndType the bean and type
     */
    /*public*/  void ActionListenOnBeans::addReference(QString beanAndType) {
        assertListenersAreNotRegistered(log, "addReference");
        QStringList parts = beanAndType.split(":");
        if (parts.length() != 2) {
            throw new IllegalArgumentException(
                    QString("Parameter 'beanAndType' must be on the format type:name")
                    + " where type is turnout, sensor, memory, ...");
        }

        try {
            NamedBeanType::TYPE type = NamedBeanType::valueOf(parts[0]);
            NamedBeanReference* reference = new NamedBeanReference(parts[1], type);
            _namedBeanReferences.insertMulti(reference->_name, reference);
        } catch (IllegalArgumentException* e) {
#if 0
            QString types = Arrays.asList(NamedBeanType.values())
                    .stream()
                    .map(Enum::toString)
                    .collect(Collectors.joining(", "));
            throw new IllegalArgumentException(
                    "Parameter 'beanAndType' has wrong type. Valid types are: " + types);
#else
         throw new IllegalArgumentException(tr("Parameter 'beanAndType' (%1) has wrong type.").arg(beanAndType), e);

#endif
        }
    }

    /*public*/  void ActionListenOnBeans::addReference(NamedBeanReference* reference) {
        assertListenersAreNotRegistered(log, "addReference");
        _namedBeanReferences.insertMulti(reference->_name, reference);
    }

    /*public*/  void ActionListenOnBeans::removeReference(NamedBeanReference* reference) {
        assertListenersAreNotRegistered(log, "removeReference");
        _namedBeanReferences.remove(reference->_name);
    }

    /*public*/  QList<ActionListenOnBeans::NamedBeanReference*> ActionListenOnBeans::getReferences() {
        return _namedBeanReferences.values();
    }

    /*public*/  void ActionListenOnBeans::clearReferences() {
        _namedBeanReferences.clear();
    }

    //@Override
    /*public*/  void ActionListenOnBeans::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
/*
        if ("CanDelete".equals(evt.getPropertyName())) { // No I18N
            if (evt.getOldValue() instanceof Memory) {
                if (evt.getOldValue().equals(getMemory().getBean())) {
                    throw new PropertyVetoException(getDisplayName(), evt);
                }
            }
        } else if ("DoDelete".equals(evt.getPropertyName())) { // No I18N
            if (evt.getOldValue() instanceof Memory) {
                if (evt.getOldValue().equals(getMemory().getBean())) {
                    setMemory((Memory)null);
                }
            }
        }
*/
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ActionListenOnBeans::getCategory() {
        return Category::OTHER;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeans::execute() {
        // Do nothing.
        // The purpose of this action is only to listen on property changes
        // of the registered beans and execute the ConditionalNG when it
        // happens.
    }

    //@Override
    /*public*/  FemaleSocket* ActionListenOnBeans::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionListenOnBeans::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionListenOnBeans::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Listen on beans");
    }

    //@Override
    /*public*/  QString ActionListenOnBeans::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Listen on beans");
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeans::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeans::registerListenersForThisClass() {
        if (_listenersAreRegistered) return;

        for (NamedBeanReference* namedBeanReference : _namedBeanReferences.values()) {
            if (namedBeanReference->_handle != nullptr) {
                if (NamedBeanType::getPropertyName(namedBeanReference->_type) != "" ) {
                    namedBeanReference->_handle->getBean()
                            ->addPropertyChangeListener(NamedBeanType::getPropertyName(namedBeanReference->_type), this);
                } else {
                    namedBeanReference->_handle->getBean()
                            ->addPropertyChangeListener(this);
                }
            }
        }
        _listenersAreRegistered = true;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeans::unregisterListenersForThisClass() {
        if (!_listenersAreRegistered) return;

        for (NamedBeanReference* namedBeanReference : _namedBeanReferences.values()) {
            if (namedBeanReference->_handle != nullptr) {
                namedBeanReference->_handle->getBean()
                        ->removePropertyChangeListener(NamedBeanType::getPropertyName(namedBeanReference->_type), this);
            }
        }
        _listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeans::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeans::disposeMe() {
    }



    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionListenOnBeans::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ActionListenOnBeans: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        for (NamedBeanReference* namedBeanReference : _namedBeanReferences.values()) {
            if (namedBeanReference->_handle != nullptr) {
                if (bean->equals(namedBeanReference->_handle->getBean()->self())) {
                    report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
                }
            }
        }
    }

    /*private*/ /*final*/ /*static*/ /*org.slf4j.*/Logger* ActionListenOnBeans::log = LoggerFactory::getLogger("ActionListenOnBeans");
