#include "expressionmemory.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "abstractbase.h"
#include "defaultmemorymanager.h"
#include "vptr.h"
#include "typeconversionutil.h"
#include "conditionalng.h"

/**
 * Evaluates the state of a Memory.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ExpressionMemory extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


/*public*/  ExpressionMemory::ExpressionMemory(QString sys, QString user, QObject *parent)
: AbstractDigitalExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
 setObjectName("ExpressionMemory");
}

//@Override
/*public*/  Base* ExpressionMemory::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    ExpressionMemory* copy = new ExpressionMemory(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
    copy->setMemoryOperation(_memoryOperation);
    copy->setCompareTo(_compareTo);
    copy->setCaseInsensitive(_caseInsensitive);
    copy->setConstantValue(_constantValue);
    if (_otherMemoryHandle != nullptr) copy->setOtherMemory(_otherMemoryHandle);
    copy->setListenToOtherMemory(_listenToOtherMemory);
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*public*/  void ExpressionMemory::setMemory(/*@Nonnull*/ QString memoryName) {
    assertListenersAreNotRegistered(log, "setMemory");
    Memory* memory = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName)->self();
    if (memory != nullptr) {
        setMemory(memory);
    } else {
        removeMemory();
        log->warn(tr("memory \"%1\" is not found").arg(memoryName));
    }
}

/*public*/  void ExpressionMemory::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
    assertListenersAreNotRegistered(log, "setMemory");
    _memoryHandle = handle;
    InstanceManager::memoryManagerInstance()->addVetoableChangeListener(this);
    addRemoveVetoListener();
}

/*public*/  void ExpressionMemory::setMemory(/*@Nonnull*/ Memory* memory) {
    assertListenersAreNotRegistered(log, "setMemory");
    setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(memory->getDisplayName(), memory));
}

/*public*/  void ExpressionMemory::removeMemory() {
    assertListenersAreNotRegistered(log, "removeMemory");
    if (_memoryHandle != nullptr) {
        _memoryHandle = nullptr;
        addRemoveVetoListener();
    }
}

/*public*/  NamedBeanHandle<Memory*>* ExpressionMemory::getMemory() {
    return _memoryHandle;
}

/*public*/  void ExpressionMemory::setOtherMemory(/*@Nonnull*/ QString memoryName) {
    assertListenersAreNotRegistered(log, "setOtherMemory");
    MemoryManager* memoryManager = (DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager");
    Memory* memory = memoryManager->getMemory(memoryName);
    if (memory != nullptr) {
        setOtherMemory(memory);
    } else {
        removeOtherMemory();
        log->warn(tr("memory \"%1\" is not found").arg(memoryName));
    }
}

/*public*/  void ExpressionMemory::setOtherMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
    assertListenersAreNotRegistered(log, "setOtherMemory");
    _otherMemoryHandle = handle;
    addRemoveVetoListener();
}

/*public*/  void ExpressionMemory::setOtherMemory(/*@Nonnull*/ Memory* memory) {
    assertListenersAreNotRegistered(log, "setOtherMemory");
    setOtherMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(memory->getDisplayName(), memory));
}

/*public*/  void ExpressionMemory::removeOtherMemory() {
    assertListenersAreNotRegistered(log, "removeOtherMemory");
    if (_otherMemoryHandle != nullptr) {
        _otherMemoryHandle = nullptr;
        addRemoveVetoListener();
    }
}

/*public*/  NamedBeanHandle<Memory*>* ExpressionMemory::getOtherMemory() {
    return _otherMemoryHandle;
}

/*public*/  void ExpressionMemory::setLocalVariable(/*@Nonnull*/ QString localVariable) {
    assertListenersAreNotRegistered(log, "setOtherLocalVariable");
    _localVariable = localVariable;
}

/*public*/  QString ExpressionMemory::getLocalVariable() {
    return _localVariable;
}

/*public*/  void ExpressionMemory::setConstantValue(QString constantValue) {
    _constantValue = constantValue;
}

/*public*/  QString ExpressionMemory::getConstantValue() {
    return _constantValue;
}

/*public*/  void ExpressionMemory::setRegEx(QString regEx) {
    _regEx = regEx;
}

/*public*/  QString ExpressionMemory::getRegEx() {
    return _regEx;
}

/*public*/  void ExpressionMemory::setListenToOtherMemory(bool listenToOtherMemory) {
    this->_listenToOtherMemory = listenToOtherMemory;
}

/*public*/  bool ExpressionMemory::getListenToOtherMemory() {
    return _listenToOtherMemory;
}

/*public*/  void ExpressionMemory::setMemoryOperation(MemoryOperation::TYPE memoryOperation) {
    _memoryOperation = memoryOperation;
}

/*public*/  ExpressionMemory::MemoryOperation::TYPE ExpressionMemory::getMemoryOperation() {
    return _memoryOperation;
}

/*public*/  void ExpressionMemory::setCompareTo(CompareTo::TYPE compareTo) {
    _compareTo = compareTo;
}

/*public*/  ExpressionMemory::CompareTo::TYPE ExpressionMemory::getCompareTo() {
    return _compareTo;
}

/*public*/  void ExpressionMemory::setCaseInsensitive(bool caseInsensitive) {
    _caseInsensitive = caseInsensitive;
}

/*public*/  bool ExpressionMemory::getCaseInsensitive() {
    return _caseInsensitive;
}

/*private*/ void ExpressionMemory::addRemoveVetoListener() {
    if ((_memoryHandle != nullptr) || (_otherMemoryHandle != nullptr)) {
        ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    } else {
        ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
    }
}

//@Override
/*public*/  void ExpressionMemory::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Memory>::asPtr(evt->getOldValue()) ) {
            bool doVeto = false;
            if ((_memoryHandle != nullptr) && VPtr<Memory>::asPtr(evt->getOldValue())->equals(_memoryHandle->getBean())) doVeto = true;
            if ((_otherMemoryHandle != nullptr) && VPtr<Memory>::asPtr(evt->getOldValue())->equals(_otherMemoryHandle->getBean())) doVeto = true;
            if (doVeto) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Memory is in use by Memory expression \"%1\"").arg(AbstractNamedBean::getDisplayName()), e); // NOI18N
            }
        }
    } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Memory>::asPtr(evt->getOldValue())) {
            if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(_memoryHandle->getBean())) {
                removeMemory();
            }
            if ((_otherMemoryHandle != nullptr) && VPtr<Memory>::asPtr(evt->getOldValue())->equals(_otherMemoryHandle->getBean())) {
                removeOtherMemory();
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* ExpressionMemory::getCategory() {
    return Category::ITEM;
}

/*private*/ QString ExpressionMemory::getString(QVariant o) {
    if (o != QVariant()) {
        return o.toString();
    }
    return "";
}

/**
 * Compare two values using the comparator set using the comparison
 * instructions in {@link #_memoryOperation}.
 *
 * <strong>Note:</strong> {@link #_memoryOperation} must be one of
 * {@link #ExpressionMemory.MemoryOperation.LESS_THAN},
 * {@link #ExpressionMemory.MemoryOperation.LESS_THAN_OR_EQUAL},
 * {@link #ExpressionMemory.MemoryOperation.EQUAL},
 * {@link #ExpressionMemory.MemoryOperation.GREATER_THAN_OR_EQUAL},
 * or {@link #ExpressionMemory.MemoryOperation.GREATER_THAN}.
 *
 * @param value1          left side of the comparison
 * @param value2          right side of the comparison
 * @param caseInsensitive true if comparison should be case insensitive;
 *                        false otherwise
 * @return true if values compare per _memoryOperation; false otherwise
 */
/*private*/ bool ExpressionMemory::compare(QString value1, QString value2, bool caseInsensitive) {
    if (value1 == "") {
        return value2 == "";
    } else {
        if (value2 == "null") {
            return false;
        }
        value1 = value1.trimmed();
        value2 = value2.trimmed();
    }
    bool ok;
    try {
        int n1 = value1.toInt(&ok); if(!ok) throw new NumberFormatException();
;        try {
            int n2 = value2.toInt(&ok); if(!ok) throw new NumberFormatException();
            log->debug(tr("Compare numbers: n1= %1 to n2= %2").arg(n1, n2));
            switch (_memoryOperation) // both are numbers
            {
                case MemoryOperation::LessThan:
                    return (n1 < n2);
                case MemoryOperation::LessThanOrEqual:
                    return (n1 <= n2);
                case MemoryOperation::Equal:
                    return (n1 == n2);
                case MemoryOperation::NotEqual:
                    return (n1 != n2);
                case MemoryOperation::GreaterThanOrEqual:
                    return (n1 >= n2);
                case MemoryOperation::GreaterThan:
                    return (n1 > n2);
                default:
                    throw new IllegalArgumentException("_memoryOperation has unknown value: "+MemoryOperation::toString(_memoryOperation));
            }
        } catch (NumberFormatException* nfe) {
            return _memoryOperation == MemoryOperation::NotEqual;   // n1 is a number, n2 is not
        }
    } catch (NumberFormatException* nfe) {
     try{
        bool ok;
            value2.toInt(&ok); if(!ok) throw new NumberFormatException();
            return _memoryOperation == MemoryOperation::NotEqual;     // n1 is not a number, n2 is
        } catch (NumberFormatException* ex) { // OK neither a number
        }
    }
    log->debug(tr("Compare Strings: value1= %1 to value2= %2").arg(value1, value2));
    int compare;
    if (caseInsensitive) {
        compare = value1.compare(value2,Qt::CaseInsensitive);
    } else {
        compare = value1.compare(value2);
    }
    switch (_memoryOperation) {
        case MemoryOperation::LessThan:
            if (compare < 0) {
                return true;
            }
            break;
        case MemoryOperation::LessThanOrEqual:
            if (compare <= 0) {
                return true;
            }
            break;
        case MemoryOperation::Equal:
            if (compare == 0) {
                return true;
            }
            break;
        case MemoryOperation::NotEqual:
            if (compare != 0) {
                return true;
            }
            break;
        case MemoryOperation::GreaterThanOrEqual:
            if (compare >= 0) {
                return true;
            }
            break;
        case MemoryOperation::GreaterThan:
            if (compare > 0) {
                return true;
            }
            break;
        default:
            throw new IllegalArgumentException("_memoryOperation has unknown value: "+MemoryOperation::toString(_memoryOperation));
    }
    return false;
}

/*private*/ bool ExpressionMemory::matchRegex(QString memoryValue, QString regex) {
//    Pattern pattern = Pattern.compile(regex);
//    Matcher m = pattern.matcher(memoryValue);
//    return m.matches();
 return memoryValue.contains(QRegExp(regex));
}

/** {@inheritDoc} */
//@Override
/*public*/  bool ExpressionMemory::evaluate() {
    if (_memoryHandle == nullptr) return false;

    // ConditionalVariable, line 661:  boolean compare(String value1, String value2, boolean caseInsensitive) {
    QString memoryValue = getString(_memoryHandle->getBean()->getValue());
    QString otherValue = "";
    bool result;

    switch (_compareTo) {
        case CompareTo::Value:
            otherValue = _constantValue;
            break;
        case CompareTo::Memory:
            otherValue = getString(_otherMemoryHandle->getBean()->getValue());
            break;
        case CompareTo::LocalVariable:
            otherValue = TypeConversionUtil::convertToString(getConditionalNG()->getSymbolTable()->getValue(_localVariable), false);
            break;
        case CompareTo::RegEx:
            // Do nothing
            break;
        default:
            throw new IllegalArgumentException("_compareTo has unknown value: "+CompareTo::toString(_compareTo));
    }

    switch (_memoryOperation) {
        case MemoryOperation::LessThan:
            // fall through
        case MemoryOperation::LessThanOrEqual:
            // fall through
        case MemoryOperation::Equal:
            // fall through
        case MemoryOperation::NotEqual:
            // fall through
        case MemoryOperation::GreaterThanOrEqual:
            // fall through
        case MemoryOperation::GreaterThan:
            result = compare(memoryValue, otherValue, _caseInsensitive);
            break;

        case MemoryOperation::IsNull:
            result = memoryValue == QVariant();
            break;
        case MemoryOperation::IsNotNull:
            result = memoryValue != QVariant();
            break;

        case MemoryOperation::MatchRegex:
            result = matchRegex(memoryValue, _regEx);
            break;

        case MemoryOperation::NotMatchRegex:
            result = !matchRegex(memoryValue, _regEx);
            break;

        default:
            throw new IllegalArgumentException("_memoryOperation has unknown value: "+MemoryOperation::toString(_memoryOperation));
    }

    return result;
}

//@Override
/*public*/  FemaleSocket* ExpressionMemory::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int ExpressionMemory::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString ExpressionMemory::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Memory");
}

//@Override
/*public*/  QString ExpressionMemory::getLongDescription(QLocale locale) {
    QString memoryName;
    if (_memoryHandle != nullptr) {
        memoryName = _memoryHandle->getName();
    } else {
        memoryName = tr(/*locale,*/ "''");
    }

    QString otherMemoryName;
    if (_otherMemoryHandle != nullptr) {
        otherMemoryName = _otherMemoryHandle->getName();
    } else {
        otherMemoryName = tr(/*locale,*/ "''");
    }

    QString message;
    QString other;
    switch (_compareTo) {
        case CompareTo::Value:
            message = tr("Memory %1 %2 \"%3\"");
            other = _constantValue;
            break;

        case CompareTo::Memory:
            message = tr("Memory %1 %2 memory %3 MMM");
            other = otherMemoryName;
            break;

        case CompareTo::LocalVariable:
            message = tr("Memory %1 %2 local variable %3");
            other = _localVariable;
            break;

        case CompareTo::RegEx:
            message = tr("Memory %1 %2 regular expression /%3/");
            other = _regEx;
            break;

        default:
            throw new IllegalArgumentException("_compareTo has unknown value: "+CompareTo::toString(_compareTo));
    }

    switch (_memoryOperation) {
        case MemoryOperation::LessThan:
            // fall through
        case MemoryOperation::LessThanOrEqual:
            // fall through
        case MemoryOperation::Equal:
            // fall through
        case MemoryOperation::NotEqual:
            // fall through
        case MemoryOperation::GreaterThanOrEqual:
            // fall through
        case MemoryOperation::GreaterThan:
            return QString(/*locale,*/ message).arg(memoryName, MemoryOperation::toString(_memoryOperation), other);

        case MemoryOperation::IsNull:
            // fall through
        case MemoryOperation::IsNotNull:
            return QString(/*locale,*/ "Memory_Long_CompareNull").arg(memoryName, MemoryOperation::toString(_memoryOperation));

        case MemoryOperation::MatchRegex:
            // fall through
        case MemoryOperation::NotMatchRegex:
            return QString( "Memory_Long_CompareRegEx").arg(memoryName, MemoryOperation::toString(_memoryOperation), other);

        default:
            throw new IllegalArgumentException("_memoryOperation has unknown value: "+MemoryOperation::toString(_memoryOperation));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionMemory::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionMemory::registerListenersForThisClass() {
    if (!_listenersAreRegistered && (_memoryHandle != nullptr)) {
        _memoryHandle->getBean()->addPropertyChangeListener("value", this);
        if (_listenToOtherMemory && (_otherMemoryHandle != nullptr)) {
            _otherMemoryHandle->getBean()->addPropertyChangeListener("value", this);
        }
        _listenersAreRegistered = true;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionMemory::unregisterListenersForThisClass() {
    if (_listenersAreRegistered) {
        _memoryHandle->getBean()->removePropertyChangeListener("value", this);
        if (_listenToOtherMemory && (_otherMemoryHandle != nullptr)) {
            _otherMemoryHandle->getBean()->removePropertyChangeListener("value", this);
        }
        _listenersAreRegistered = false;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionMemory::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionMemory::disposeMe() {
}




/** {@inheritDoc} */
//@Override
/*public*/  void ExpressionMemory::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ExpressionMemory: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
    if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
    }
    if (getOtherMemory() != nullptr && bean->equals(getOtherMemory()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* ExpressionMemory::log = LoggerFactory::getLogger("ExpressionMemory");
