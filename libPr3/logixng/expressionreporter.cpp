#include "expressionreporter.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "instancemanager.h"
#include "abstractreportermanager.h"
#include "abstractmemorymanager.h"
#include "conditionalng.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * Evaluates the state of a Reporter.
 *
 * @author Daniel Bergqvist Copyright 2018
 * @author Dave Sand Copyright 2021
 */
// /*public*/  class ExpressionReporter extends AbstractDigitalExpression
//        implements PropertyChangeListener, VetoableChangeListener {

    /*static*/ QList<ExpressionReporter::ReporterValue::RV> ExpressionReporter::ReporterValue::values =
    {ExpressionReporter::ReporterValue::CurrentReport, ExpressionReporter::ReporterValue::LastReport, ExpressionReporter::ReporterValue::State};
    /*static*/ QList<ExpressionReporter::ReporterOperation::RO> ExpressionReporter::ReporterOperation::values =
    {LessThan, LessThanOrEqual, Equal, GreaterThanOrEqual, GreaterThan, NotEqual, IsNull, IsNotNull,
            MatchRegex, NotMatchRegex};
    /*public*/  ExpressionReporter::ExpressionReporter(QString sys, QString user, QObject* parent)
     : AbstractDigitalExpression(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    }

    //@Override
    /*public*/  Base* ExpressionReporter::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ExpressionReporter* copy = new ExpressionReporter(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        if (_reporterHandle != nullptr) copy->setReporter(_reporterHandle);
        copy->setReporterValue(_reporterValue);
        copy->setReporterOperation(_reporterOperation);
        copy->setCompareTo(_compareTo);
        copy->setCaseInsensitive(_caseInsensitive);
        copy->setConstantValue(_constantValue);
        if (_memoryHandle != nullptr) copy->setMemory(_memoryHandle);
        copy->setListenToMemory(_listenToMemory);
        return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
    }


    /*public*/  void ExpressionReporter::setReporter(/*@Nonnull*/ QString reporterName) {
        assertListenersAreNotRegistered(log, "setReporter");
        Reporter* reporter = ((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->getReporter(reporterName);
        if (reporter != nullptr) {
            setReporter(reporter);
        } else {
            removeReporter();
            log->warn(tr("reporter \"%1\" is not found").arg(reporterName));
        }
    }

    /*public*/  void ExpressionReporter::setReporter(/*@Nonnull*/ NamedBeanHandle<Reporter*>*  handle) {
        assertListenersAreNotRegistered(log, "setReporter");
        _reporterHandle = handle;
        ((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ExpressionReporter::setReporter(/*@Nonnull*/ Reporter* reporter) {
        assertListenersAreNotRegistered(log, "setReporter");
        setReporter(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(reporter->getDisplayName(), reporter));
    }

    /*public*/  void ExpressionReporter::removeReporter() {
        assertListenersAreNotRegistered(log, "removeReporter");
        if (_reporterHandle != nullptr) {
            ((AbstractReporterManager*)InstanceManager::getDefault("ReporterManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _reporterHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<Reporter*>*  ExpressionReporter::getReporter() {
        return _reporterHandle;
    }


    /*public*/  void ExpressionReporter::setMemory(/*@Nonnull*/ QString memoryName) {
        assertListenersAreNotRegistered(log, "setMemory");
        MemoryManager* memoryManager = (AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager");
        Memory* memory = memoryManager->getMemory(memoryName);
        if (memory != nullptr) {
            setMemory(memory);
        } else {
            removeMemory();
            log->warn(tr("memory \"%1\" is not found").arg(memoryName));
        }
    }

    /*public*/  void ExpressionReporter::setMemory(/*@Nonnull*/ NamedBeanHandle<Memory*>* handle) {
        assertListenersAreNotRegistered(log, "setMemory");
        _memoryHandle = handle;
        ((AbstractMemoryManager*)InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void ExpressionReporter::setMemory(/*@Nonnull*/ Memory* memory) {
        assertListenersAreNotRegistered(log, "setMemory");
        setMemory(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                ->getNamedBeanHandle(memory->getDisplayName(), memory));
    }

    /*public*/  void ExpressionReporter::removeMemory() {
        assertListenersAreNotRegistered(log, "removeMemory");
        if (_memoryHandle != nullptr) {
            _memoryHandle = nullptr;
           ((AbstractMemoryManager*) InstanceManager::getDefault("MemoryManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
        }
    }

    /*public*/  NamedBeanHandle<Memory*>* ExpressionReporter::getMemory() {
        return _memoryHandle;
    }


    /*public*/  void ExpressionReporter::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        assertListenersAreNotRegistered(log, "setLocalVariable");
        _localVariable = localVariable;
    }

    /*public*/  QString ExpressionReporter::getLocalVariable() {
        return _localVariable;
    }


    /*public*/  void ExpressionReporter::setConstantValue(QString constantValue) {
        _constantValue = constantValue;
    }

    /*public*/  QString ExpressionReporter::getConstantValue() {
        return _constantValue;
    }


    /*public*/  void ExpressionReporter::setRegEx(QString regEx) {
        _regEx = regEx;
    }

    /*public*/  QString ExpressionReporter::getRegEx() {
        return _regEx;
    }


    /*public*/  void ExpressionReporter::setListenToMemory(bool listenToMemory) {
        this->_listenToMemory = listenToMemory;
    }

    /*public*/  bool ExpressionReporter::getListenToMemory() {
        return _listenToMemory;
    }


    /*public*/  void ExpressionReporter::setReporterValue(ReporterValue::RV reporterValue) {
        _reporterValue = reporterValue;
    }

    /*public*/  ExpressionReporter::ReporterValue::RV ExpressionReporter::getReporterValue() {
        return _reporterValue;
    }


    /*public*/  void ExpressionReporter::setReporterOperation(ReporterOperation::RO reporterOperation) {
        _reporterOperation = reporterOperation;
    }

    /*public*/  ExpressionReporter::ReporterOperation::RO ExpressionReporter::getReporterOperation() {
        return _reporterOperation;
    }


    /*public*/  void ExpressionReporter::setCompareTo(CompareTo::CT compareTo) {
        _compareTo = compareTo;
    }

    /*public*/  ExpressionReporter::CompareTo::CT ExpressionReporter::getCompareTo() {
        return _compareTo;
    }


    /*public*/  void ExpressionReporter::setCaseInsensitive(bool caseInsensitive) {
        _caseInsensitive = caseInsensitive;
    }

    /*public*/  bool ExpressionReporter::getCaseInsensitive() {
        return _caseInsensitive;
    }


    //@Override
    /*public*/  void ExpressionReporter::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N

            if (VPtr<Reporter>::asPtr(evt->getOldValue())) {
                if (VPtr<Reporter>::asPtr(evt->getOldValue()) == (getReporter()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Reporter is in use by Reporter expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }

            }

            if (VPtr<Memory>::asPtr(evt->getOldValue())) {
                if (VPtr<Memory>::asPtr(evt->getOldValue())->equals(getMemory()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Memory is in use by Reporter expression \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category ExpressionReporter::getCategory() {
        return Category::ITEM;
    }

    /*private*/ QString ExpressionReporter::getString(QVariant o) {
        if (!o.isNull()) {
            return o.toString();
        }
        return "";
    }

    /**
     * Compare two values using the comparator set using the comparison
     * instructions in {@link #_reporterOperation}.
     *
     * <strong>Note:</strong> {@link #_reporterOperation} must be one of
     * {@link #ExpressionReporter.ReporterOperation.LESS_THAN},
     * {@link #ExpressionReporter.ReporterOperation.LESS_THAN_OR_EQUAL},
     * {@link #ExpressionReporter.ReporterOperation.EQUAL},
     * {@link #ExpressionReporter.ReporterOperation.GREATER_THAN_OR_EQUAL},
     * or {@link #ExpressionReporter.ReporterOperation.GREATER_THAN}.
     *
     * @param value1          left side of the comparison
     * @param value2          right side of the comparison
     * @param caseInsensitive true if comparison should be case insensitive;
     *                        false otherwise
     * @return true if values compare per _reporterOperation; false otherwise
     */
    /*private*/ bool ExpressionReporter::compare(QString value1, QString value2, bool caseInsensitive) {
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
            int n1 = value1.toInt(&ok); if(!ok) throw new NumberFormatException();
            try {
                int n2 = value2.toInt(&ok); if(!ok) throw new NumberFormatException();
                log->debug(tr("Compare numbers: n1= %1 to n2= %2").arg(n1, n2));
                switch (_reporterOperation) // both are numbers
                {
                    case ReporterOperation::LessThan:
                        return (n1 < n2);
                    case ReporterOperation::LessThanOrEqual:
                        return (n1 <= n2);
                    case ReporterOperation::Equal:
                        return (n1 == n2);
                    case ReporterOperation::NotEqual:
                        return (n1 != n2);
                    case ReporterOperation::GreaterThanOrEqual:
                        return (n1 >= n2);
                    case ReporterOperation::GreaterThan:
                        return (n1 > n2);
                    default:
                        throw new IllegalArgumentException("_reporterOperation has unknown value: "+ReporterOperation::toString(_reporterOperation));
                }
            } catch (NumberFormatException* nfe) {
                return _reporterOperation == ReporterOperation::NotEqual;   // n1 is a number, n2 is not
            }
        } catch (NumberFormatException* nfe) {
            try {
          bool ok;
                value2.toInt(&ok); if(!ok) throw new NumberFormatException();
                return _reporterOperation == ReporterOperation::NotEqual;     // n1 is not a number, n2 is
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
        switch (_reporterOperation) {
            case ReporterOperation::LessThan:
                if (compare < 0) {
                    return true;
                }
                break;
            case ReporterOperation::LessThanOrEqual:
                if (compare <= 0) {
                    return true;
                }
                break;
            case ReporterOperation::Equal:
                if (compare == 0) {
                    return true;
                }
                break;
            case ReporterOperation::NotEqual:
                if (compare != 0) {
                    return true;
                }
                break;
            case ReporterOperation::GreaterThanOrEqual:
                if (compare >= 0) {
                    return true;
                }
                break;
            case ReporterOperation::GreaterThan:
                if (compare > 0) {
                    return true;
                }
                break;
            default:
                throw new IllegalArgumentException("_reporterOperation has unknown value: "+ReporterOperation::toString(_reporterOperation));
        }
        return false;
    }

    /*private*/ bool ExpressionReporter::matchRegex(QString reporterValue, QString regex) {
//        Pattern pattern = Pattern.compile(regex);
//        Matcher m = pattern.matcher(reporterValue);
//        return m.matches();
     QRegExp pattern(regex);
     return pattern.exactMatch(reporterValue);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool ExpressionReporter::evaluate() {
        if (_reporterHandle == nullptr) return false;

        QVariant obj;
        switch (_reporterValue) {
            case ReporterValue::CurrentReport:
                obj = _reporterHandle->getBean()->getCurrentReport();
                break;

            case ReporterValue::LastReport:
                obj = _reporterHandle->getBean()->getLastReport();
                break;

            case ReporterValue::State:
                obj = _reporterHandle->getBean()->getState();
                break;

            default:
                obj = QVariant();
        }
        QString reporterValue = getString(obj);
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
                otherValue = TypeConversionUtil::convertToString(getConditionalNG()->getSymbolTable()->getValue(_localVariable), false);
                break;
            case CompareTo::RegEx:
                // Do nothing
                break;
            default:
                throw new IllegalArgumentException("_compareTo has unknown value: "+CompareTo::toString(_compareTo));
        }

        switch (_reporterOperation) {
            case ReporterOperation::LessThan:
                // fall through
            case ReporterOperation::LessThanOrEqual:
                // fall through
            case ReporterOperation::Equal:
                // fall through
            case ReporterOperation::NotEqual:
                // fall through
            case ReporterOperation::GreaterThanOrEqual:
                // fall through
            case ReporterOperation::GreaterThan:
                result = compare(reporterValue, otherValue, _caseInsensitive);
                break;

            case ReporterOperation::IsNull:
                result = reporterValue == nullptr;
                break;

            case ReporterOperation::IsNotNull:
                result = reporterValue != nullptr;
                break;

            case ReporterOperation::MatchRegex:
                result = matchRegex(reporterValue, _regEx);
                break;

            case ReporterOperation::NotMatchRegex:
                result = !matchRegex(reporterValue, _regEx);
                break;

            default:
                throw new IllegalArgumentException("_reporterOperation has unknown value: "+ReporterOperation::toString(_reporterOperation));
        }

        return result;
    }

    //@Override
    /*public*/  FemaleSocket* ExpressionReporter::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ExpressionReporter::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ExpressionReporter::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Reporter");
    }

    //@Override
    /*public*/  QString ExpressionReporter::getLongDescription(QLocale locale) {
        QString reporterName;
        if (_reporterHandle != nullptr) {
            reporterName = _reporterHandle->getName();
        } else {
            reporterName = tr(/*locale, */"");
        }

        QString memoryName;
        if (_memoryHandle != nullptr) {
            memoryName = _memoryHandle->getName();
        } else {
            memoryName = tr(/*locale,*/ "");
        }

        QString message;
        QString other;
        switch (_compareTo) {
            case CompareTo::Value:
                message = "Reporter %1 %2 %3 \"&4\"";
                other = _constantValue;
                break;

            case CompareTo::Memory:
                message = "Reporter %1 %2 %3 memory %4";
                other = memoryName;
                break;

            case CompareTo::LocalVariable:
                message = "Reporter %1 %2 %3 local variable %4";
                other = _localVariable;
                break;

            case CompareTo::RegEx:
                message = "Reporter %1 %2 %3 regular expression /%4/";
                other = _regEx;
                break;

            default:
                throw new IllegalArgumentException("_compareTo has unknown value: "+CompareTo::toString(_compareTo));
        }

        switch (_reporterOperation) {
            case ReporterOperation::LessThan:
                // fall through
            case ReporterOperation::LessThanOrEqual:
                // fall through
            case ReporterOperation::Equal:
                // fall through
            case ReporterOperation::NotEqual:
                // fall through
            case ReporterOperation::GreaterThanOrEqual:
                // fall through
            case ReporterOperation::GreaterThan:
                return tr(/*locale,*/ message.toLocal8Bit()).arg(reporterName,ReporterValue::toString(_reporterValue), ReporterOperation::toString(_reporterOperation), other);

            case ReporterOperation::IsNull:
                // fall through
            case ReporterOperation::IsNotNull:
                return tr(/*locale,*/ "Reporter %1 %2 %3").arg(reporterName, ReporterValue::toString(_reporterValue),ReporterOperation::toString(_reporterOperation));

            case ReporterOperation::MatchRegex:
                // fall through
            case ReporterOperation::NotMatchRegex:
                return tr(/*locale,*/ "Reporter %1 &2 %3 regular expression /{%4/").arg(reporterName, ReporterValue::toString(_reporterValue), ReporterOperation::toString(_reporterOperation), other);

            default:
                throw new IllegalArgumentException("_reporterOperation has unknown value: "+ReporterOperation::toString(_reporterOperation));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReporter::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReporter::registerListenersForThisClass() {
        if (!_listenersAreRegistered && (_reporterHandle != nullptr)) {
            _reporterHandle->getBean()->addPropertyChangeListener("value", this);
            if (_listenToMemory && (_memoryHandle != nullptr)) {
                _memoryHandle->getBean()->addPropertyChangeListener("value", this);
            }
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReporter::unregisterListenersForThisClass() {
        if (_listenersAreRegistered) {
            _reporterHandle->getBean()->removePropertyChangeListener("value", this);
            if (_listenToMemory && (_memoryHandle != nullptr)) {
                _memoryHandle->getBean()->removePropertyChangeListener("value", this);
            }
            _listenersAreRegistered = false;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReporter::propertyChange(PropertyChangeEvent* evt) {
        getConditionalNG()->execute();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReporter::disposeMe() {
    }
#if 0
    /*public*/  enum ReporterValue {
        CurrentReport(Bundle.getMessage("Reporter_Value_CurrentReport")),
        LastReport(Bundle.getMessage("Reporter_Value_LastReport")),
        State(Bundle.getMessage("Reporter_Value_State"));

        /*private*/ final String _text;

        /*private*/ ReporterValue(String text) {
            this._text = text;
        }

        //@Override
        /*public*/  String toString() {
            return _text;
        }
    }


    /*public*/  enum ReporterOperation {
        LessThan(Bundle.getMessage("ReporterOperation_LessThan"), true),
        LessThanOrEqual(Bundle.getMessage("ReporterOperation_LessThanOrEqual"), true),
        Equal(Bundle.getMessage("ReporterOperation_Equal"), true),
        GreaterThanOrEqual(Bundle.getMessage("ReporterOperation_GreaterThanOrEqual"), true),
        GreaterThan(Bundle.getMessage("ReporterOperation_GreaterThan"), true),
        NotEqual(Bundle.getMessage("ReporterOperation_NotEqual"), true),
        IsNull(Bundle.getMessage("ReporterOperation_IsNull"), false),
        IsNotNull(Bundle.getMessage("ReporterOperation_IsNotNull"), false),
        MatchRegex(Bundle.getMessage("ReporterOperation_MatchRegEx"), true),
        NotMatchRegex(Bundle.getMessage("ReporterOperation_NotMatchRegEx"), true);

        /*private*/ final String _text;
        /*private*/ final boolean _extraValue;

        /*private*/ ReporterOperation(String text, boolean extraValue) {
            this._text = text;
            this._extraValue = extraValue;
        }

        //@Override
        /*public*/  String toString() {
            return _text;
        }

        /*public*/  boolean hasExtraValue() {
            return _extraValue;
        }

    }


    /*public*/  enum CompareTo {
        Value(Bundle.getMessage("Reporter_CompareTo_Value")),
        Memory(Bundle.getMessage("Reporter_CompareTo_Memory")),
        LocalVariable(Bundle.getMessage("Reporter_CompareTo_LocalVariable")),
        RegEx(Bundle.getMessage("Reporter_CompareTo_RegularExpression"));

        /*private*/ final String _text;

        /*private*/ CompareTo(String text) {
            this._text = text;
        }

        //@Override
        /*public*/  String toString() {
            return _text;
        }

    }
#endif
    /** {@inheritDoc} */
    //@Override
    /*public*/  void ExpressionReporter::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
#if 0 // TODO:
        log->debug(tr("getUsageReport :: ExpressionReporter: bean = %1, report = %2").arg(((AbstractNamedBean*)cdl.bself())->getDisplayName(), report));
        if (getReporter() != nullptr && bean ->equals(getReporter()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription()));
        }
        if (getMemory() != nullptr && bean->equals(getMemory()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGExpression", cdl, getLongDescription()));
        }
#endif
    }

    /*private*/ /*final*/ /*static*/ Logger* ExpressionReporter::log = LoggerFactory::getLogger("ExpressionReporter");
