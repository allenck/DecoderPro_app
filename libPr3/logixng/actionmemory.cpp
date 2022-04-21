#include "actionmemory.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "recursivedescentparser.h"
#include "referenceutil.h"
#include "defaultmemorymanager.h"
#include "namedbeanhandlemanager.h"
#include "vptr.h"
#include "conditionalng.h"
#include "typeconversionutil.h"
#include "defaultlogixngmanager.h"

/**
 * This action sets the value of a memory.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class ActionMemory extends AbstractDigitalAction
//        implements PropertyChangeListener, VetoableChangeListener {


/*public*/  ActionMemory::ActionMemory(QString sys, QString user, QObject* parent)
        /*throws BadUserNameException, BadSystemNameException*/ : AbstractDigitalAction(sys, user, parent){
    //super(sys, user);
 setObjectName("ActionMemory");
}

//@Override
/*public*/  Base* ActionMemory::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws ParserException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    ActionMemory* copy = new ActionMemory(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
    copy->setAddressing(_addressing);
    copy->setFormula(_formula);
    copy->setLocalVariable(_localVariable);
    copy->setReference(_reference);
    if (_otherMemoryHandle != nullptr) copy->setOtherMemory(_otherMemoryHandle);
    copy->setMemoryOperation(_memoryOperation);
    copy->setOtherConstantValue(_otherConstantValue);
    copy->setOtherTableCell(_otherTableCell);
    copy->setOtherLocalVariable(_otherLocalVariable);
    copy->setOtherFormula(_otherFormula);
    copy->setListenToMemory(_listenToMemory);
    return manager->registerAction(copy);
}

/*public*/  void ActionMemory::setMemory(/*@Nonnull*/ QString memoryName) {
    assertListenersAreNotRegistered(log, "setMemory");
    Memory* memory = ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(memoryName);
    if (memory != nullptr) {
        setMemory(memory);
    } else {
        removeMemory();
        log->warn(tr("memory \"%1\" is not found").arg(memoryName));
    }
}

/*public*/  void ActionMemory::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
    assertListenersAreNotRegistered(log, "setMemory");
    _memoryHandle = handle;
    addRemoveVetoListener();
}

/*public*/  void ActionMemory::setMemory(/*@Nonnull*/ Memory* memory) {
    assertListenersAreNotRegistered(log, "setMemory");
    setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(memory->getDisplayName(), memory));
}

/*public*/  void ActionMemory::removeMemory() {
    assertListenersAreNotRegistered(log, "removeMemory");
    if (_memoryHandle != nullptr) {
        _memoryHandle = nullptr;
        addRemoveVetoListener();
    }
}

/*public*/  NamedBeanHandle<Memory*>* ActionMemory::getMemory() {
    return _memoryHandle;
}


/*public*/  void ActionMemory::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _addressing = addressing;
    parseFormula();
}

/*public*/  NamedBeanAddressing::TYPE ActionMemory::getAddressing() {
    return _addressing;
}

/*public*/  void ActionMemory::setReference(/*@Nonnull*/ QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _reference = reference;
}

/*public*/  QString ActionMemory::getReference() {
    return _reference;
}

/*public*/  void ActionMemory::setLocalVariable(/*@Nonnull*/ QString localVariable) {
    _localVariable = localVariable;
}

/*public*/  QString ActionMemory::getLocalVariable() {
    return _localVariable;
}

/*public*/  void ActionMemory::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _formula = formula;
    parseFormula();
}

/*public*/  QString ActionMemory::ActionMemory::getFormula() {
    return _formula;
}

/*private*/ void ActionMemory::parseFormula() /*throws ParserException*/ {
    if (_addressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _expressionNode = parser->parseExpression(_formula);
    } else {
        _expressionNode = nullptr;
    }
}


/*public*/  void ActionMemory::setMemoryOperation(MemoryOperation::TYPE state) /*throws ParserException*/ {
    _memoryOperation = state;
    parseOtherFormula();
}

/*public*/  ActionMemory::MemoryOperation::TYPE ActionMemory::getMemoryOperation() {
    return _memoryOperation;
}

// Constant tab
/*public*/  void ActionMemory::setOtherConstantValue(QString constantValue) {
    _otherConstantValue = constantValue;
}

/*public*/  QString ActionMemory::getConstantValue() {
    return _otherConstantValue;
}

// Memory tab
/*public*/  void ActionMemory::setOtherMemory(/*@Nonnull*/ QString memoryName) {
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

/*public*/  void ActionMemory::setOtherMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
    assertListenersAreNotRegistered(log, "setOtherMemory");
    _otherMemoryHandle = handle;
    addRemoveVetoListener();
}

/*public*/  void ActionMemory::setOtherMemory(/*@Nonnull*/ Memory* memory) {
    assertListenersAreNotRegistered(log, "setOtherMemory");
    setOtherMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
            ->getNamedBeanHandle(memory->getDisplayName(), memory));
}

/*public*/  void ActionMemory::removeOtherMemory() {
    assertListenersAreNotRegistered(log, "removeOtherMemory");
    if (_otherMemoryHandle != nullptr) {
        _otherMemoryHandle = nullptr;
        addRemoveVetoListener();
    }
}

/*public*/  NamedBeanHandle<Memory*>* ActionMemory::getOtherMemory() {
    return _otherMemoryHandle;
}

/*public*/  void ActionMemory::setListenToMemory(bool listenToMemory) {
    this->_listenToMemory = listenToMemory;
}

/*public*/  bool ActionMemory::getListenToMemory() {
    return _listenToMemory;
}

// Table tab
/*public*/  void ActionMemory::setOtherTableCell(/*@Nonnull*/ QString tableCell) {
    if ((! tableCell.isEmpty()) && (! ReferenceUtil::isReference(tableCell))) {
        throw new IllegalArgumentException("The table reference \"" + tableCell + "\" is not a valid reference");
    }
    _otherTableCell = tableCell;
}

/*public*/  QString ActionMemory::getOtherTableCell() {
    return _otherTableCell;
}

/**
 * Convert a table reference between direct table mode "table[row, col]"" and reference
 * table mode "{table[row, col]}".
 * @param string The current value.
 * @param toReference If true, return reference table mode, false for direct table mode.
 * @return the desired mode format.
 */
/*public*/  /*static*/ QString ActionMemory::convertTableReference(QString string, bool toReference) {
    QString tableString = string == "" ? "" : string.trimmed();
    bool referenceFormat = ReferenceUtil::isReference(tableString);

    if (toReference) {
        if (referenceFormat) return tableString;
        return "{" + tableString + "}";
    }

    if (! referenceFormat) return tableString;
    return tableString.isEmpty() ? "" : tableString.mid(1, tableString.length() - 1);
}

// Variable tab
/*public*/  void ActionMemory::setOtherLocalVariable(/*@Nonnull*/ QString localVariable) {
    assertListenersAreNotRegistered(log, "setOtherLocalVariable");
    _otherLocalVariable = localVariable;
}

/*public*/  QString ActionMemory::getOtherLocalVariable() {
    return _otherLocalVariable;
}

// Formula tab
/*public*/  void ActionMemory::setOtherFormula(QString formula) /*throws ParserException */{
    _otherFormula = formula;
    parseOtherFormula();
}

/*public*/  QString ActionMemory::getOtherFormula() {
    return _otherFormula;
}

/*private*/ void ActionMemory::parseOtherFormula() /*throws ParserException */{
    if (_memoryOperation == MemoryOperation::CalculateFormula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();
#if 0
        SymbolTable* symbolTable = ((DefaultLogixNGManager*)
                InstanceManager::getDefault("LogixNG_Manager"))
                        ->getSymbolTable();

        if (symbolTable == null && 1==1) return;    // Why does this happens?
//            if (symbolTable == null && 1==1) return;    // Nothing we can do if we don't have a symbol table
        if (symbolTable == null) throw new RuntimeException("Daniel AA");
        if (symbolTable.getSymbols() == null) throw new RuntimeException("Daniel BB");
        if (symbolTable.getSymbols().values() == null) throw new RuntimeException("Daniel BB");

        for (SymbolTable.Symbol symbol : symbolTable.getSymbols().values()) {
            variables.put(symbol.getName(),
                    new LocalVariableExpressionVariable(symbol.getName()));
        }
#endif
        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _otherExpressionNode = parser->parseExpression(_otherFormula);
    } else {
        _otherExpressionNode = nullptr;
    }
}


/*private*/ void ActionMemory::addRemoveVetoListener() {
    if ((_memoryHandle != nullptr) || (_otherMemoryHandle != nullptr)) {
        ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    } else {
        ((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
    }
}

//@Override
/*public*/  void ActionMemory::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
    if ("CanDelete" == (evt->getPropertyName())) { // No I18N
        if (VPtr<Memory>::asPtr(evt->getOldValue())) {
            bool doVeto = false;
            if ((_memoryHandle != nullptr) && VPtr<Memory>::asPtr(evt->getOldValue())->equals(_memoryHandle->getBean())) doVeto = true;
            if ((_otherMemoryHandle != nullptr) && VPtr<Memory>::asPtr(evt->getOldValue())->equals(_otherMemoryHandle->getBean())) doVeto = true;
            if (doVeto) {
                PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                throw new PropertyVetoException(tr("Memory is in use by Memory action \"%1\"").arg(getDisplayName()), e); // NOI18N
            }
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* ActionMemory::getCategory() {
    return Category::ITEM;
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionMemory::execute() /*throws JmriException*/ {

    Memory* memory;

//        System.out.format("ActionLight.execute: %s%n", getLongDescription());

    switch (_addressing) {
        case NamedBeanAddressing::Direct:
            memory = _memoryHandle != nullptr ? _memoryHandle->getBean() : nullptr;
            break;

        case NamedBeanAddressing::Reference:
        {
            QString ref = ReferenceUtil::getReference(
                    getConditionalNG()->getSymbolTable(), _reference);
            memory = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))
                    ->getNamedBean(ref)->self();
            break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
            memory = (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))
                    ->getNamedBean(TypeConversionUtil
                            ::convertToString(symbolTable->getValue(_localVariable), false))->self();
            break;
        }
        case NamedBeanAddressing::Formula:
            memory = _expressionNode != nullptr ?
                    (Memory*)((DefaultMemoryManager*)InstanceManager::getDefault("MemoryManager"))
                            ->getNamedBean(TypeConversionUtil
                                    ::convertToString(_expressionNode->calculate(
                                            getConditionalNG()->getSymbolTable()), false))->self()
                    : nullptr;
            break;

        default:
            throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
    }

//        System.out.format("ActionMemory.execute: Memory: %s%n", memory);

    if (memory == nullptr) {
//            log.warn("memory is null");
        return;
    }

    //AtomicReference<JmriException*> ref = new AtomicReference<>();
    std::atomic<JmriException*>* ref = new std::atomic<JmriException*>();

    /*final*/ ConditionalNG* conditionalNG = getConditionalNG();

//    ThreadingUtil::runOnLayoutWithJmriException(() -> {

//        switch (_memoryOperation) {
//            case MemoryOperation::SetToNull:
//                memory.setValue(nullptr);
//                break;

//            case SetToString:
//                memory.setValue(_otherConstantValue);
//                break;

//            case CopyTableCellToMemory:
//                String refValue = ReferenceUtil.getReference(
//                    conditionalNG.getSymbolTable(), _otherTableCell);
//                memory.setValue(refValue);
//                break;

//            case CopyVariableToMemory:
//                Object variableValue = conditionalNG
//                                .getSymbolTable().getValue(_otherLocalVariable);
//                memory.setValue(variableValue);
//                break;

//            case CopyMemoryToMemory:
//                if (_otherMemoryHandle != null) {
//                    memory.setValue(_otherMemoryHandle.getBean().getValue());
//                } else {
//                    log.warn("setMemory should copy memory to memory but other memory is null");
//                }
//                break;

//            case CalculateFormula:
//                if (_otherFormula.isEmpty()) {
//                    memory.setValue(null);
//                } else {
//                    try {
//                        if (_otherExpressionNode == null) {
//                            return;
//                        }
//                        memory.setValue(_otherExpressionNode.calculate(
//                                conditionalNG.getSymbolTable()));
//                    } catch (JmriException e) {
//                        ref.set(e);
//                    }
//                }
//                break;

//            default:
//                throw new IllegalArgumentException("_memoryOperation has invalid value: {}" + _memoryOperation.name());
//        }
//    });
    ThreadingUtil::runOnLayoutWithJmriException(new AMRun(ref, conditionalNG, memory, this));
    //if (ref.get() != nullptr) throw ref.get();
    if(ref->load() != nullptr) throw ref->load();
}

void AMRun::run()
{
 switch (actionMemory->_memoryOperation) {
     case ActionMemory::MemoryOperation::SetToNull:
         memory->setValue(QVariant());
         break;

     case ActionMemory::MemoryOperation::SetToString:
         memory->setValue(actionMemory->_otherConstantValue);
         break;

     case ActionMemory::MemoryOperation::CopyTableCellToMemory:
     {
         QString refValue = ReferenceUtil::getReference(
             conditionalNG->getSymbolTable(), actionMemory->_otherTableCell);
         memory->setValue(refValue);
         break;
     }
     case ActionMemory::MemoryOperation::CopyVariableToMemory:
     {
         QVariant variableValue = conditionalNG
                         ->getSymbolTable()->getValue(actionMemory->_otherLocalVariable);
         memory->setValue(variableValue);
         break;
     }
     case ActionMemory::MemoryOperation::CopyMemoryToMemory:
         if (actionMemory->_otherMemoryHandle != nullptr) {
             memory->setValue(actionMemory->_otherMemoryHandle->getBean()->getValue());
         } else {
             actionMemory->log->warn("setMemory should copy memory to memory but other memory is null");
         }
         break;

     case ActionMemory::MemoryOperation::CalculateFormula:
         if (actionMemory->_otherFormula.isEmpty()) {
             memory->setValue(QVariant());
         } else {
             try {
                 if (actionMemory->_otherExpressionNode == nullptr) {
                     return;
                 }
                 memory->setValue(actionMemory->_otherExpressionNode->calculate(
                         conditionalNG->getSymbolTable()));
             } catch (JmriException* e) {
                 ref->store(e);
             }
         }
         break;

     default:
         throw new IllegalArgumentException("_memoryOperation has invalid value: {}" + ActionMemory::MemoryOperation::toString(actionMemory->_memoryOperation));
 }
}

//@Override
/*public*/  FemaleSocket* ActionMemory::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    throw new UnsupportedOperationException("Not supported.");
}

//@Override
/*public*/  int ActionMemory::getChildCount() {
    return 0;
}

//@Override
/*public*/  QString ActionMemory::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Memory");
}

//@Override
/*public*/  QString ActionMemory::getLongDescription(QLocale locale) {
    QString memoryName;
    if (_memoryHandle != nullptr) {
        memoryName = _memoryHandle->getBean()->getDisplayName();
    } else {
        memoryName = tr(/*locale,*/ "''");
    }

    QString copyToMemoryName;
    if (_otherMemoryHandle != nullptr) {
        copyToMemoryName = _otherMemoryHandle->getBean()->getDisplayName();
    } else {
        copyToMemoryName = tr(/*locale,*/ "''");
    }

    switch (_memoryOperation) {
        case MemoryOperation::SetToNull:
            return tr(/*locale,*/ "Set memory %1 to null").arg(memoryName);
        case MemoryOperation::SetToString:
            return tr(/*locale,*/ "Set memory %1 to \"%2\"").arg(memoryName, _otherConstantValue);
        case MemoryOperation::CopyTableCellToMemory:
            return tr(/*locale,*/ "Set memory %1 to the value of table cell %2").arg(memoryName, convertTableReference(_otherTableCell, false));
        case MemoryOperation::CopyVariableToMemory:
            return tr(/*locale,*/ "Set memory %1 to the value of variable %2").arg(memoryName, _otherLocalVariable);
        case MemoryOperation::CopyMemoryToMemory:
            return tr(/*locale,*/ "Set memory %1 to the value of memory %2").arg(memoryName, copyToMemoryName);
        case MemoryOperation::CalculateFormula:
            return tr(/*locale,*/ "Set memory %1 to the result of formula \"%2\"").arg(memoryName, _otherFormula);
        default:
            throw new IllegalArgumentException("_memoryOperation has invalid value: " + MemoryOperation::toString(_memoryOperation));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionMemory::setup() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionMemory::registerListenersForThisClass() {
    if (!_listenersAreRegistered && (_otherMemoryHandle != nullptr)) {
        if (_listenToMemory) {
            _otherMemoryHandle->getBean()->addPropertyChangeListener("value", this);
        }
        _listenersAreRegistered = true;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionMemory::unregisterListenersForThisClass() {
    if (_listenersAreRegistered) {
        if (_listenToMemory && (_otherMemoryHandle != nullptr)) {
            _otherMemoryHandle->getBean()->addPropertyChangeListener("value", this);
        }
        _listenersAreRegistered = false;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionMemory::propertyChange(PropertyChangeEvent* evt) {
    getConditionalNG()->execute();
}

/** {@inheritDoc} */
//@Override
/*public*/  void ActionMemory::disposeMe() {
}



/** {@inheritDoc} */
//@Override
/*public*/  void ActionMemory::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport *> *report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ActionMemory: bean = %1, report = %2").arg(cdl->getDisplayName().arg(report->size())));
    if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
    }
    if (getOtherMemory() != nullptr && bean->equals(getOtherMemory()->getBean())) {
        report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
    }
}

/*private*/ /*final*/ /*static*/ Logger* ActionMemory::log = LoggerFactory::getLogger("ActionMemory");

