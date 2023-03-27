#include "actionreporter.h"
#include "loggerfactory.h"
#include "reporter.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "referenceutil.h"
#include "typeconversionutil.h"
#include "parserexception.h"
#include "recursivedescentparser.h"
#include "abstractmemorymanager.h"
#include "vptr.h"
#include "defaultconditionalng.h"

/**
 * This action triggers a reporter.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
// /*public*/  class ActionReporter extends AbstractDigitalAction implements VetoableChangeListener {

    /*public*/  ActionReporter::ActionReporter(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    }

    //@Override
    /*public*/  Base* ActionReporter::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionReporter* copy = new ActionReporter(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setAddressing(_addressing);
        if (_reporterHandle != nullptr) copy->setReporter(_reporterHandle);
        copy->setReference(_reference);
        copy->setLocalVariable(_localVariable);
        copy->setFormula(_formula);

        copy->setReporterValue(_reporterValue);

        copy->setDataAddressing(_dataAddressing);
        copy->setDataReference(_dataReference);
        copy->setDataLocalVariable(_dataLocalVariable);
        copy->setDataFormula(_dataFormula);
        if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);

        return manager->registerAction(copy);
    }

    /*public*/  void ActionReporter::setReporter(/*@Nonnull*/ QString reporterName) {
        assertListenersAreNotRegistered(log, "setReporter");
        Reporter* reporter = (Reporter*)((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->getNamedBean(reporterName)->self();
        if (reporter != nullptr) {
            setReporter(reporter);
        } else {
            removeReporter();
            log->error(tr("Reporter \"%1\" is not found").arg(reporterName));
        }
    }

    /*public*/  void ActionReporter::setReporter(/*@Nonnull*/ Reporter* reporter) {
        assertListenersAreNotRegistered(log, "setReporter");
        setReporter(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(reporter->getDisplayName(), reporter));
    }

    /*public*/  void ActionReporter::setReporter(/*@Nonnull*/ NamedBeanHandle<Reporter*>* handle) {
        assertListenersAreNotRegistered(log, "setReporter");
        _reporterHandle = handle;
        ((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ActionReporter::removeReporter() {
        assertListenersAreNotRegistered(log, "removeReporter");
        if (_reporterHandle != nullptr) {
             ((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _reporterHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Reporter*>* ActionReporter::getReporter() {
        return _reporterHandle;
    }


    /*public*/  void ActionReporter::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionReporter::getAddressing() {
        return _addressing;
    }

    /*public*/  void ActionReporter::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString ActionReporter::getReference() {
        return _reference;
    }

    /*public*/  void ActionReporter::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString ActionReporter::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void ActionReporter::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString ActionReporter::getFormula() {
        return _formula;
    }

    /*private*/ void ActionReporter::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }


    /*public*/  void ActionReporter::setReporterValue(ReporterValue::VAL value) {
        _reporterValue = value;
    }

    /*public*/  ActionReporter::ReporterValue::VAL ActionReporter::getReporterValue() {
        return _reporterValue;
    }


    /*public*/  void ActionReporter::setMemory(/*@Nonnull*/ QString memoryName) {
        assertListenersAreNotRegistered(log, "setMemory");
        Memory* memory = (Memory*)((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getNamedBean(memoryName)->self();
        if (memory != nullptr) {
            setMemory(memory);
        } else {
            removeMemory();
            log->error(tr("Memory \"%1\" is not found").arg(memoryName));
        }
    }

    /*public*/  void ActionReporter::setMemory(/*@Nonnull*/ Memory* memory) {
        assertListenersAreNotRegistered(log, "setMemory");
        setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(memory->getDisplayName(), memory));
    }

    /*public*/  void ActionReporter::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
        assertListenersAreNotRegistered(log, "setMemory");
        _memoryHandle = handle;
        ((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ActionReporter::removeMemory() {
        assertListenersAreNotRegistered(log, "removeMemory");
        if (_memoryHandle != nullptr) {
            ((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _memoryHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Memory*>* ActionReporter::getMemory() {
        return _memoryHandle;
    }


    /*public*/  void ActionReporter::setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _dataAddressing = addressing;
        parseDataFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE ActionReporter::getDataAddressing() {
        return _dataAddressing;
    }

    /*public*/  void ActionReporter::setDataReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _dataReference = reference;
    }

    /*public*/  QString ActionReporter::getDataReference() {
        return _dataReference;
    }

    /*public*/  void ActionReporter::setDataLocalVariable(/*@Nonnull*/ QString localVariable) {
        _dataLocalVariable = localVariable;
    }

    /*public*/  QString ActionReporter::getDataLocalVariable() {
        return _dataLocalVariable;
    }

    /*public*/  void ActionReporter::setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _dataFormula = formula;
        parseDataFormula();
    }

    /*public*/  QString ActionReporter::getDataFormula() {
        return _dataFormula;
    }

    /*private*/ void ActionReporter::parseDataFormula() /*throws ParserException*/ {
        if (_dataAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _dataExpressionNode = parser->parseExpression(_dataFormula);
        } else {
            _dataExpressionNode = nullptr;
        }
    }


    //@Override
    /*public*/  void ActionReporter::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Reporter>::asPtr(evt->getOldValue())) {
                if (VPtr<Reporter>::asPtr(evt->getOldValue())->equals(getReporter()->getBean()->self())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Reporter is in use by Reporter action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
            if (VPtr<Memory>::asPtr(evt->getOldValue()) ) {
                if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Memory is in use by Reporter action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ActionReporter::getCategory() {
        return Category::ITEM;
    }


    Reporter* ActionReporter::getSourceReporter() /*throws JmriException*/ {
        Reporter* reporter = nullptr;
        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                reporter = _reporterHandle != nullptr ? _reporterHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _reference);
                reporter = (Reporter*)((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))
                        ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                reporter = (Reporter*)((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))
                        ->getNamedBean(TypeConversionUtil
                                ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                reporter = _expressionNode != nullptr ?
                        (Reporter*)((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))
                                ->getNamedBean(TypeConversionUtil
                                        ::convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }
        return reporter;
    }

    QVariant ActionReporter::getReporterData(Reporter* reporter) /*throws JmriException*/ {
        QVariant obj;
        ReporterValue::VAL value = _reporterValue;

        switch (value) {
            case ReporterValue::CopyCurrentReport:
                obj = reporter->getCurrentReport();
                break;
            case ReporterValue::CopyLastReport:
                obj = reporter->getLastReport();
                break;
            case ReporterValue::CopyState:
                obj = reporter->getState();
                break;
            default:
                throw new IllegalArgumentException("invalid value name: " + ReporterValue::toString(value));
        }

        return obj;
    }

    void ActionReporter::updateDestination(QVariant data) /*throws JmriException*/ {
        switch (_dataAddressing) {
            case NamedBeanAddressing::Direct:
                if (_memoryHandle != nullptr) {
                    _memoryHandle->getBean()->setValue(data);
                }
                break;

            case NamedBeanAddressing::Reference:
            {
                QString refName = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _dataReference);
                log->debug(tr("ref ref = %1, name = %2").arg(_dataReference, refName));
                Memory* refMem = ((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(refName);
                if (refMem == nullptr) {
                    throw new IllegalArgumentException("invalid memory reference: " + refName);
                }
                refMem->setValue(data);
                break;
            }
            case NamedBeanAddressing::LocalVariable:
                log->debug(tr("LocalVariable: lv = %1").arg(_dataLocalVariable));
                getConditionalNG()->getSymbolTable()->setValue(_dataLocalVariable, data);
                break;

            case NamedBeanAddressing::Formula:
            {
                QString formulaName = _dataExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                                _dataExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false)
                        : "";
                if (formulaName == "") {
                    throw new IllegalArgumentException("invalid memory formula, name is null");
                }

                Memory* formulaMem = ((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->getMemory(formulaName);
                if (formulaMem == nullptr) {
                    throw new IllegalArgumentException("invalid memory formula: " + formulaName);
                }
                formulaMem->setValue(data);
                break;
            }
            default:
                throw new IllegalArgumentException("invalid _dataAddressing state: " + NamedBeanAddressing::toString(_dataAddressing));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionReporter::execute() /*throws JmriException*/ {
        // Get the reporter bean
        Reporter* reporter = getSourceReporter();
        if (reporter == nullptr) return;
        log->debug(tr("reporter = %1").arg(reporter->getDisplayName()));

        // Get the reporter data
        QVariant data = getReporterData(reporter);
        log->debug(tr("data = %1").arg(data.toString()));

        // Update the destination
        updateDestination(data);
    }

    //@Override
    /*public*/  FemaleSocket* ActionReporter::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionReporter::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionReporter::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionReporter_Short");
    }

    //@Override
    /*public*/  QString ActionReporter::getLongDescription(QLocale locale) {
        QString bean = "";
        QString dest = "";

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString reporterName;
                if (_reporterHandle != nullptr) {
                    reporterName = _reporterHandle->getBean()->getDisplayName();
                } else {
                    reporterName = tr(/*locale,*/ "BeanNotSelected");
                }
                bean = tr(/*locale,*/ "%1").arg(reporterName);
                break;
            }
            case NamedBeanAddressing::Reference:
                bean = tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                bean = tr(/*locale,*/ "by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                bean = tr(/*locale,*/ "by formula %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_dataAddressing) {
            case NamedBeanAddressing::Direct:
        {
                QString memoryName;
                if (_memoryHandle != nullptr) {
                    memoryName = _memoryHandle->getBean()->getDisplayName();
                } else {
                    memoryName = tr(/*locale,*/ "BeanNotSelected");
                }
                dest = tr(/*locale,*/ "%1").arg(memoryName);
                break;
            }
            case NamedBeanAddressing::Reference:
                dest = tr(/*locale,*/ "by reference %1").arg(_dataReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                dest = tr(/*locale,*/ "by local variable %1").arg(_dataLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                dest = tr(/*locale,*/ "by formula %1").arg(_dataFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _dataAddressing state: " + NamedBeanAddressing::toString(_dataAddressing));
        }

        QString item = ReporterValue::toString(getReporterValue());

        return tr(/*locale,*/ "Copy \"%1\" for reporter \"%2\" to \"%3\"").arg(item, bean, dest);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionReporter::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionReporter::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionReporter::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionReporter::disposeMe() {
    }

//    /*public*/  enum ReporterValue {
//        CopyCurrentReport(Bundle.getMessage("ActionReporter_CopyCurrentReport")),
//        CopyLastReport(Bundle.getMessage("ActionReporter_CopyLastReport")),
//        CopyState(Bundle.getMessage("ActionReporter_CopyState"));

//        /*private*/ final String _text;

//        /*private*/ ReporterValue(String text) {
//            this._text = text;
//        }

//        //@Override
//        /*public*/  String toString() {
//            return _text;
//        }

//    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionReporter::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
        log->debug(tr("getUsageReport :: ActionReporter: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
        if (getReporter() != nullptr && bean->equals(getReporter()->getBean()->self())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
        if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionReporter::log = LoggerFactory::getLogger("ActionReporter");
