#include "expressionlocalvariable.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "expressionlocalvariable.h"
#include "vptr.h"
#include "defaultconditionalng.h"
#include "defaultmemorymanager.h"
#include "typeconversionutil.h"
#include "namedbeanaddressing.h"
/**
 * Evaluates the state of a local variable.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  class ExpressionLocalVariable extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  ExpressionLocalVariable::ExpressionLocalVariable(QString sys, QString user, QObject* parent)
     : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
 setObjectName("ExpressionLocalVariable");
    }
#if 1
    //@Override
    /*public*/  Base* ExpressionLocalVariable::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionLocalVariable* copy = new ExpressionLocalVariable(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setLocalVariable(_localVariable);
        copy->setVariableOperation(_variableOperation);
        copy->setCompareTo(_compareTo);
        copy->setCaseInsensitive(_caseInsensitive);
        copy->setConstantValue(_constantValue);
        if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
        copy->setOtherLocalVariable(_localVariable);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*public*/  void ExpressionLocalVariable::setLocalVariable(QString variableName) {
        assertListenersAreNotRegistered(log, "setLocalVariable");
        _localVariable = variableName;
    }

    /*public*/  QString ExpressionLocalVariable::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ExpressionLocalVariable::setMemory(/*@Nonnull*/ QString memoryName) {
        assertListenersAreNotRegistered(log, "setMemory");
        MemoryManager* memoryManager = (DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager");
        Memory* memory = memoryManager->getMemory(memoryName);
        if (memory != nullptr) {
            setMemory(memory);
        } else {
            removeMemory();
            log->error(tr("memory \"%1\" is not found").arg(memoryName));
        }
    }

    /*public*/  void ExpressionLocalVariable::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
        assertListenersAreNotRegistered(log, "setMemory");
        _memoryHandle = handle;
        if (_memoryHandle != nullptr) {
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
        } else {
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
        }
    }

    /*public*/  void ExpressionLocalVariable::setMemory(/*CheckForNull*/ Memory* memory) {
        assertListenersAreNotRegistered(log, "setMemory");
        if (memory != nullptr) {
            _memoryHandle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                    ->getNamedBeanHandle(memory->getDisplayName(), memory);
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
        } else {
            _memoryHandle = nullptr;
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
        }
    }

    /*public*/  void ExpressionLocalVariable::removeMemory() {
        assertListenersAreNotRegistered(log, "removeMemory");
        if (_memoryHandle != nullptr) {
            InstanceManager::memoryManagerInstance()->removeVetoableChangeListener(this);
            _memoryHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Memory*>* ExpressionLocalVariable::getMemory() {
        return _memoryHandle;
    }

    /*public*/  void ExpressionLocalVariable::setOtherLocalVariable(/*@Nonnull*/ QString localVariable) {
        assertListenersAreNotRegistered(log, "setOtherLocalVariable");
        _otherLocalVariable = localVariable;
    }

    /*public*/  QString ExpressionLocalVariable::getOtherLocalVariable() {
        return _otherLocalVariable;
    }

    /*public*/  void ExpressionLocalVariable::setConstantValue(QString constantValue) {
        _constantValue = constantValue;
    }

    /*public*/  QString ExpressionLocalVariable::getConstantValue() {
        return _constantValue;
    }

    /*public*/  void ExpressionLocalVariable::setRegEx(QString regEx) {
        _regEx = regEx;
    }

    /*public*/  QString ExpressionLocalVariable::getRegEx() {
        return _regEx;
    }

    /*public*/  void ExpressionLocalVariable::setListenToMemory(bool listenToMemory) {
        this->_listenToMemory = listenToMemory;
    }

    /*public*/  bool ExpressionLocalVariable::getListenToMemory() {
        return _listenToMemory;
    }

    /*public*/  void ExpressionLocalVariable::setVariableOperation(VariableOperation::TYPE variableOperation) {
        _variableOperation = variableOperation;
    }

    /*public*/  ExpressionLocalVariable::VariableOperation::TYPE ExpressionLocalVariable::getVariableOperation() {
        return _variableOperation;
    }

    /*public*/  void ExpressionLocalVariable::setCompareTo(CompareTo::TYPE compareTo) {
        _compareTo = compareTo;
    }

    /*public*/  ExpressionLocalVariable::CompareTo::TYPE ExpressionLocalVariable::getCompareTo() {
        return _compareTo;
    }

    /*public*/  void ExpressionLocalVariable::setCaseInsensitive(bool caseInsensitive) {
        _caseInsensitive = caseInsensitive;
    }

    /*public*/  bool ExpressionLocalVariable::getCaseInsensitive() {
        return _caseInsensitive;
    }

    //@Override
    /*public*/  void ExpressionLocalVariable::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
/*
        if ("CanDelete".equals(evt->getPropertyName())) { // No I18N
            if (VPtr<Memory*>::asPtr(evt->getOldValue())) {
                if (VPtr<Memory*>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), null);
                    throw new PropertyVetoException(Bundle->getMessage("Memory_MemoryInUseMemoryExpressionVeto", getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete".equals(evt->getPropertyName())) { // No I18N
            if (VPtr<Memory*>::asPtr(evt->getOldValue())) {
                if (VPtr<Memory*>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                    removeMemory();
                }
            }
        }
*/
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ExpressionLocalVariable::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionLocalVariable::getString(QVariant o) {
        if (!o .isNull()) {
            return o.toString();
        }
        return "";
    }

    /**
     * Compare two values using the comparator set using the comparison
     * instructions in {@link #_variableOperation}.
     *
     * <strong>Note:</strong> {@link #_variableOperation} must be one of
     * {@link #ExpressionLocalVariable.MemoryOperation.LESS_THAN},
     * {@link #ExpressionLocalVariable.MemoryOperation.LESS_THAN_OR_EQUAL},
     * {@link #ExpressionLocalVariable.MemoryOperation.EQUAL},
     * {@link #ExpressionLocalVariable.MemoryOperation.GREATER_THAN_OR_EQUAL},
     * or {@link #ExpressionLocalVariable.MemoryOperation.GREATER_THAN}.
     *
     * @param value1          left side of the comparison
     * @param value2          right side of the comparison
     * @param caseInsensitive true if comparison should be case insensitive;
     *                        false otherwise
     * @return true if values compare per _memoryOperation; false otherwise
     */
    /*private*/ bool ExpressionLocalVariable::compare(QString value1, QString value2, bool caseInsensitive) {
        if (value1 == "") {
            return value2 == "";
        } else {
            if (value2 == "") {
                return false;
            }
            value1 = value1.trimmed();
            value2 = value2.trimmed();
        }
        try {
         bool ok;
            int n1 = value1.toInt(); if(!ok) throw new NumberFormatException();
            try {
                int n2 =value2.toInt(); if(!ok) throw new NumberFormatException();;
                log->debug(tr("Compare numbers: n1= %1 to n2= %2").arg(n1, n2));
                switch (_variableOperation) // both are numbers
                {
                    case VariableOperation::LessThan:
                        return (n1 < n2);
                    case VariableOperation::LessThanOrEqual:
                        return (n1 <= n2);
                    case VariableOperation::Equal:
                        return (n1 == n2);
                    case VariableOperation::NotEqual:
                        return (n1 != n2);
                    case VariableOperation::GreaterThanOrEqual:
                        return (n1 >= n2);
                    case VariableOperation::GreaterThan:
                        return (n1 > n2);
                    default:
                        throw new IllegalArgumentException("_memoryOperation has unknown value: "+VariableOperation::toString(_variableOperation));
                }
            } catch (NumberFormatException* nfe) {
                return _variableOperation == VariableOperation::NotEqual;   // n1 is a number, n2 is not
            }
        } catch (NumberFormatException* nfe) {
            try {
          bool ok;
                value2.toInt(); if(!ok) throw new NumberFormatException();
                return _variableOperation == VariableOperation::NotEqual;     // n1 is not a number, n2 is
            } catch (NumberFormatException* ex) { // OK neither a number
            }
        }
        log->debug(tr("Compare Strings: value1= %1 to value2= %2").arg(value1, value2));
        int compare;
        if (caseInsensitive) {
            compare = value1.compare(value2, Qt::CaseInsensitive);
        } else {
            compare = value1.compare(value2, Qt::CaseSensitive);
        }
        switch (_variableOperation) {
            case VariableOperation::LessThan:
                if (compare < 0) {
                    return true;
                }
                break;
            case VariableOperation::LessThanOrEqual:
                if (compare <= 0) {
                    return true;
                }
                break;
            case VariableOperation::Equal:
                if (compare == 0) {
                    return true;
                }
                break;
            case VariableOperation::NotEqual:
                if (compare != 0) {
                    return true;
                }
                break;
            case VariableOperation::GreaterThanOrEqual:
                if (compare >= 0) {
                    return true;
                }
                break;
            case VariableOperation::GreaterThan:
                if (compare > 0) {
                    return true;
                }
                break;
            default:
                throw new IllegalArgumentException("_memoryOperation has unknown value: "+VariableOperation::toString(_variableOperation));
        }
        return false;
    }

    /*private*/ bool ExpressionLocalVariable::matchRegex(QString memoryValue, QString regex) {
//        Pattern pattern = Pattern.compile(regex);
//        Matcher m = pattern.matcher(memoryValue);
//        return m.matches();
        return memoryValue.contains(QRegExp(regex));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionLocalVariable::evaluate() {
        if (_localVariable == nullptr) return false;

        QString variableValue = getString(getConditionalNG()
                        ->getSymbolTable()->getValue(_localVariable));
        QString otherValue = "";
        bool result;

        switch (_compareTo) {
            case CompareTo::Value:
                otherValue = _constantValue;
                break;
            case CompareTo::Memory:
                otherValue = getString(_memoryHandle->getBean()->getValue());
                break;
            case CompareTo::LocalVariable:
                otherValue = TypeConversionUtil::convertToString(getConditionalNG()->getSymbolTable()->getValue(_otherLocalVariable), false);
                break;
            case CompareTo::RegEx:
                // Do nothing
                break;
            default:
                throw new IllegalArgumentException("_compareTo has unknown value: "+CompareTo::toString(_compareTo));
        }

        switch (_variableOperation) {
            case VariableOperation::LessThan:
                // fall through
            case VariableOperation::LessThanOrEqual:
                // fall through
            case VariableOperation::Equal:
                // fall through
            case VariableOperation::NotEqual:
                // fall through
            case VariableOperation::GreaterThanOrEqual:
                // fall through
            case VariableOperation::GreaterThan:
                result = compare(variableValue, otherValue, _caseInsensitive);
                break;

            case VariableOperation::IsNull:
                result = variableValue == nullptr;
                break;
            case VariableOperation::IsNotNull:
                result = variableValue != nullptr;
                break;

            case VariableOperation::MatchRegex:
                result = matchRegex(variableValue, _regEx);
                break;

            case VariableOperation::NotMatchRegex:
                result = !matchRegex(variableValue, _regEx);
                break;

            default:
                throw new IllegalArgumentException("_memoryOperation has unknown value: "+VariableOperation::toString(_variableOperation));
        }

        return result;
    }

    //@Override
    /*public*/  FemaleSocket* ExpressionLocalVariable::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ExpressionLocalVariable::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ExpressionLocalVariable::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Local variable");
    }

    //@Override
    /*public*/  QString ExpressionLocalVariable::getLongDescription(QLocale locale) {
        QString variableName;
        if ((_localVariable == "") || _localVariable.isEmpty()) {
            variableName = tr(/*locale,*/ "");
        } else {
            variableName = _localVariable;
        }

        QString memoryName;
        if (_memoryHandle != nullptr) {
            memoryName = _memoryHandle->getName();
        } else {
            memoryName = tr(/*locale,*/ "BeanNotSelected");
        }

        QString message;
        QString other;
        switch (_compareTo) {
            case CompareTo::Value:
                message = "Local variable %1 %2 \"%3\"";
                other = _constantValue;
                break;

            case CompareTo::Memory:
                message = "LocalVariable_Long_CompareMemory";
                other = memoryName;
                break;

            case CompareTo::LocalVariable:
                message = "Local variable %1 %2 local variable %3";
                other = _otherLocalVariable;
                break;

            case CompareTo::RegEx:
                message = "Local variable %1 %2 /%3/";
                other = _regEx;
                break;

            default:
                throw new IllegalArgumentException("_compareTo has unknown value: "+CompareTo::toString(_compareTo));
        }

        switch (_variableOperation) {
            case VariableOperation::LessThan:
                // fall through
            case VariableOperation::LessThanOrEqual:
                // fall through
            case VariableOperation::Equal:
                // fall through
            case VariableOperation::NotEqual:
                // fall through
            case VariableOperation::GreaterThanOrEqual:
                // fall through
            case VariableOperation::GreaterThan:
                return QString(/*locale,*/ message).arg(variableName, VariableOperation::toString(_variableOperation), other);

            case VariableOperation::IsNull:
                // fall through
            case VariableOperation::IsNotNull:
                return QString(/*locale,*/ "LocalVariable_Long_CompareNull").arg(variableName, VariableOperation::toString(_variableOperation));

            case VariableOperation::MatchRegex:
                // fall through
            case VariableOperation::NotMatchRegex:
                return QString(/*locale,*/ "LocalVariable_Long_CompareRegEx").arg(variableName, VariableOperation::toString(_variableOperation), other);

            default:
                throw new IllegalArgumentException("_variableOperation has unknown value: "+VariableOperation::toString(_variableOperation));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLocalVariable::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLocalVariable::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_memoryHandle != nullptr)) {
            if (_listenToMemory) {
                _memoryHandle->getBean()->addPropertyChangeListener("value", this);
            }
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLocalVariable::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            if (_listenToMemory && (_memoryHandle != nullptr)) {
                _memoryHandle->getBean()->addPropertyChangeListener("value", this);
            }
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLocalVariable::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLocalVariable::disposeMe() {
    }





    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionLocalVariable::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ExpressionLocalVariable: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription(QLocale())));
        }
    }
#endif
    /*private*/ /*final*/ /*static*/ Logger* ExpressionLocalVariable::log = LoggerFactory::getLogger("ExpressionLocalVariable");

