#include "actionlocalvariable.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "referenceutil.h"
#include "vptr.h"
#include "defaultconditionalng.h"
#include "defaultmemorymanager.h"
#include "variable.h"
#include "recursivedescentparser.h"

/**
 * This action sets the value of a local variable.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  class ActionLocalVariable extends AbstractDigitalAction
//        implements PropertyChangeListener, VetoableChangeListener {


    /*public*/  ActionLocalVariable::ActionLocalVariable(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
     setObjectName("ActionLocalVariable");
    }

    //@Override
    /*public*/  Base* ActionLocalVariable::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = systemNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionLocalVariable* copy = new ActionLocalVariable(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setLocalVariable(_localVariable);
        copy->setVariableOperation(_variableOperation);
        copy->setConstantValue(_constantValue);
        if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
        copy->setOtherTableCell(_otherTableCell);
        copy->setOtherLocalVariable(_otherLocalVariable);
        copy->setFormula(_formula);
        copy->setListenToMemory(_listenToMemory);
        return manager->registerAction(copy);
    }

    /*public*/  void ActionLocalVariable::setLocalVariable(QString variableName) {
        assertListenersAreNotRegistered(log, "setLocalVariable");   // No I18N
        _localVariable = variableName;
    }

    /*public*/  QString ActionLocalVariable::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ActionLocalVariable::setMemory(/*@Nonnull*/ QString memoryName) {
        assertListenersAreNotRegistered(log, "setMemory");  // No I18N
        MemoryManager* memoryManager = (DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager");
        Memory* memory = memoryManager->getMemory(memoryName);
        if (memory != nullptr) {
            setMemory(memory);
        } else {
            removeMemory();
            log->warn(tr("memory \"%1\" is not found").arg(memoryName));
        }
    }

    /*public*/  void ActionLocalVariable::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
        assertListenersAreNotRegistered(log, "setMemory");  // No I18N
        _memoryHandle = handle;
        if (_memoryHandle != nullptr) {
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
        } else {
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
        }
    }

    /*public*/  void ActionLocalVariable::setMemory(/*CheckForNull*/ Memory* memory) {
        assertListenersAreNotRegistered(log, "setMemory");  // No I18N
        if (memory != nullptr) {
            _memoryHandle = ((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                    ->getNamedBeanHandle(memory->getDisplayName(), memory);
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
        } else {
            _memoryHandle = nullptr;
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
        }
    }

    /*public*/  void ActionLocalVariable::removeMemory() {
        assertListenersAreNotRegistered(log, "removeMemory");   // No I18N
        if (_memoryHandle != nullptr) {
            ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _memoryHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Memory*>* ActionLocalVariable::getMemory() {
        return _memoryHandle;
    }

    /*public*/  void ActionLocalVariable::setVariableOperation(VariableOperation::TYPE variableOperation) /*throws ParserException*/ {
        _variableOperation = variableOperation;
        parseFormula();
    }

    /*public*/  ActionLocalVariable::VariableOperation::TYPE ActionLocalVariable::getVariableOperation() {
        return _variableOperation;
    }

    /*public*/  void ActionLocalVariable::setOtherTableCell(/*@Nonnull*/ QString tableCell) {
        if ((! tableCell.isEmpty()) && (! ReferenceUtil::isReference(tableCell))) {
            throw new IllegalArgumentException("The table reference \"" + tableCell + "\" is not a valid reference");
        }
        _otherTableCell = tableCell;
    }

    /*public*/  QString ActionLocalVariable::getOtherTableCell() {
        return _otherTableCell;
    }

    /**
     * Convert a table reference between direct table mode "table[row, col]"" and reference
     * table mode "{table[row, col]}".
     * @param string The current value.
     * @param toReference If true, return reference table mode, false for direct table mode.
     * @return the desired mode format.
     */
    /*public*/  /*static*/ QString ActionLocalVariable::convertTableReference(QString string, bool toReference) {
        QString tableString = string == "" ? "" : string.trimmed();
        bool referenceFormat = ReferenceUtil::isReference(tableString);

        if (toReference) {
            if (referenceFormat) return tableString;
            return "{" + tableString + "}";
        }

        if (! referenceFormat) return tableString;
        return tableString.isEmpty() ? "" : tableString.mid(1, tableString.length() - 1);
    }

    /*public*/  void ActionLocalVariable::setOtherLocalVariable(/*@Nonnull*/ QString localVariable) {
        assertListenersAreNotRegistered(log, "setOtherLocalVariable");
        _otherLocalVariable = localVariable;
    }

    /*public*/  QString ActionLocalVariable::getOtherLocalVariable() {
        return _otherLocalVariable;
    }

    /*public*/  void ActionLocalVariable::setConstantValue(QString constantValue) {
        _constantValue = constantValue;
    }

    /*public*/  QString ActionLocalVariable::getConstantValue() {
        return _constantValue;
    }

    /*public*/  void ActionLocalVariable::setFormula(QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ActionLocalVariable::getFormula() {
        return _formula;
    }

    /*public*/  void ActionLocalVariable::setListenToMemory(bool listenToMemory) {
        this->_listenToMemory = listenToMemory;
    }

    /*public*/  bool ActionLocalVariable::getListenToMemory() {
        return _listenToMemory;
    }

    /*private*/ void ActionLocalVariable::parseFormula() /*throws ParserException*/ {
        if (_variableOperation == ActionLocalVariable::VariableOperation::CalculateFormula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    //@Override
    /*public*/  void ActionLocalVariable::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Memory>::asPtr(evt->getOldValue())) {
                if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(_memoryHandle->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());   // No I18N
                    throw new PropertyVetoException(tr("Memory is in use by LocalVariable action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ActionLocalVariable::getCategory() {
        return Category::ITEM;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariable::execute() /*throws JmriException*/ {
        if (_localVariable == nullptr) return;

        SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();

        switch (_variableOperation) {
            case ActionLocalVariable::VariableOperation::SetToNull:
                symbolTable->setValue(_localVariable, QVariant());
                break;

            case ActionLocalVariable::VariableOperation::SetToString:
                symbolTable->setValue(_localVariable, _constantValue);
                break;

            case ActionLocalVariable::VariableOperation::CopyVariableToVariable:
            {
                QVariant variableValue = getConditionalNG()
                                ->getSymbolTable()->getValue(_otherLocalVariable);

                symbolTable->setValue(_localVariable, variableValue);
                break;
            }
            case ActionLocalVariable::VariableOperation::CopyMemoryToVariable:
                if (_memoryHandle != nullptr) {
                    symbolTable->setValue(_localVariable, _memoryHandle->getBean()->getValue());
                } else {
                    log->warn("ActionLocalVariable should copy memory to variable but memory is null");
                }
                break;

            case ActionLocalVariable::VariableOperation::CopyTableCellToVariable:
            {
                QString refValue = ReferenceUtil::getReference(
                    getConditionalNG()->getSymbolTable(), _otherTableCell);
                symbolTable->setValue(_localVariable, refValue);
                break;
            }
            case ActionLocalVariable::VariableOperation::CalculateFormula:
                if (_formula.isEmpty()) {
                    symbolTable->setValue(_localVariable, QVariant());
                } else {
                    if (_expressionNode == nullptr) return;

                    symbolTable->setValue(_localVariable,
                            _expressionNode->calculate(
                                    getConditionalNG()->getSymbolTable()));
                }
                break;

            default:
                // Throw exception
                throw new IllegalArgumentException("_memoryOperation has invalid value: {}" + ActionLocalVariable::VariableOperation::toString(_variableOperation));
        }
    }

    //@Override
    /*public*/  FemaleSocket* ActionLocalVariable::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionLocalVariable::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionLocalVariable::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Local variable");
    }

    //@Override
    /*public*/  QString ActionLocalVariable::getLongDescription(QLocale locale) {
        QString copyToMemoryName;
        if (_memoryHandle != nullptr) {
            copyToMemoryName = _memoryHandle->getBean()->getDisplayName();
        } else {
            copyToMemoryName = tr(/*locale,*/ "not selected");
        }

        switch (_variableOperation) {
            case ActionLocalVariable::VariableOperation::SetToNull:
                return tr(/*locale,*/ "Set variable %1 to null").arg(_localVariable);

            case ActionLocalVariable::VariableOperation::SetToString:
                return tr(/*locale,*/ "Set variable %1 to \"%2\"").arg(_localVariable, _constantValue);

            case ActionLocalVariable::VariableOperation::CopyVariableToVariable:
                return tr(/*locale,*/ "Set variable %1 to the value of variable %2").arg(
                        _localVariable, _otherLocalVariable);

            case ActionLocalVariable::VariableOperation::CopyTableCellToVariable:
                return tr(/*locale,*/ "Set variable %1 to the value of table cell %2").arg(
                        _localVariable, convertTableReference(_otherTableCell, false));

            case ActionLocalVariable::VariableOperation::CopyMemoryToVariable:
                return tr(/*locale,*/ "Set variable %1 to the value of memory %2").arg(
                        _localVariable, copyToMemoryName);

            case ActionLocalVariable::VariableOperation::CalculateFormula:
                return tr(/*locale,*/ "Set variable %1 to the result of formula \"%2\"").arg(_localVariable, _formula);

            default:
                throw new IllegalArgumentException("_memoryOperation has invalid value: " +ActionLocalVariable::VariableOperation::toString( _variableOperation));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariable::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariable::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_memoryHandle != nullptr)) {
            if (_listenToMemory) {
                _memoryHandle->getBean()->addPropertyChangeListener("value", this);
            }
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariable::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            if (_listenToMemory && (_memoryHandle != nullptr)) {
                _memoryHandle->getBean()->addPropertyChangeListener("value", this);
            }
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariable::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariable::disposeMe() {
    }




    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionLocalVariable::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ActionLocalVariable: bean = %1, report = %2").arg(cdl->getDisplayName()).arg(report->size()));
        if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionLocalVariable::log = LoggerFactory::getLogger("ActionLocalVariable");
