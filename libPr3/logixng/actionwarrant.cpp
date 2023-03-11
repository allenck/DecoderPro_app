#include "actionwarrant.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "logixng/conditionalng.h"
#include "warrant.h"
#include "warrantmanager.h"
#include "defaultdigitalactionmanager.h"
#include "referenceutil.h"
#include "parserexception.h"
#include "recursivedescentparser.h"
#include "vptr.h"
#include "typeconversionutil.h"

/**
 * This action triggers a warrant.
 *
 * @author Daniel Bergqvist Copyright 2021
 * @author Dave Sand Copyright 2021
 */
// /*public*/ class ActionWarrant extends AbstractDigitalAction implements VetoableChangeListener {


    /*public*/ ActionWarrant::ActionWarrant(QString sys, QString user, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractDigitalAction(sys, user, parent)
    {
        //super(sys, user);
     setObjectName("ActionWarrant");
    }

    //@Override
    /*public*/ Base* ActionWarrant::getDeepCopy(QMap<QString, QString>*  systemNames, QMap<QString, QString>*  userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionWarrant* copy = new ActionWarrant(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setAddressing(_addressing);
        if (_warrantHandle != nullptr) copy->setWarrant(_warrantHandle);
        copy->setReference(_reference);
        copy->setLocalVariable(_localVariable);
        copy->setFormula(_formula);

        copy->setOperationAddressing(_operationAddressing);
        copy->setOperationDirect(_operationDirect);
        copy->setOperationReference(_operationReference);
        copy->setOperationLocalVariable(_operationLocalVariable);
        copy->setOperationFormula(_operationFormula);

        copy->setDataAddressing(_dataAddressing);
        copy->setDataReference(_dataReference);
        copy->setDataLocalVariable(_dataLocalVariable);
        copy->setDataFormula(_dataFormula);

        copy->setTrainIdName(_trainIdName);
        copy->setControlAutoTrain(_controlAutoTrain);

        return manager->registerAction(copy);
    }

    /*public*/ void ActionWarrant::setWarrant(/*@Nonnull*/ QString warrantName) {
        assertListenersAreNotRegistered(log, "setWarrant");
        Warrant* warrant = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->getNamedBean(warrantName)->self();
        if (warrant != nullptr) {
            setWarrant(warrant);
        } else {
            removeWarrant();
            log->error(tr("Warrant \"%1\" is not found").arg(warrantName));
        }
    }

    /*public*/ void ActionWarrant::setWarrant(/*@Nonnull*/ Warrant* warrant) {
        assertListenersAreNotRegistered(log, "setWarrant");
        setWarrant(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))
                   ->getNamedBeanHandle(warrant->getDisplayName(), warrant));
    }

    /*public*/ void ActionWarrant::ActionWarrant::setWarrant(/*@Nonnull*/ NamedBeanHandle<Warrant*>* handle) {
        assertListenersAreNotRegistered(log, "setWarrant");
        _warrantHandle = handle;
        ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/ void ActionWarrant::removeWarrant() {
        assertListenersAreNotRegistered(log, "removeWarrant");
        if (_warrantHandle != nullptr) {
            ((WarrantManager*)InstanceManager::getDefault("WarrantManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _warrantHandle = nullptr;
        }
    }

    /*public*/ NamedBeanHandle<Warrant*>* ActionWarrant::getWarrant() {
        return _warrantHandle;
    }


    /*public*/ void ActionWarrant::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionWarrant::getAddressing() {
        return _addressing;
    }

    /*public*/ void ActionWarrant::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/ QString ActionWarrant::getReference() {
        return _reference;
    }

    /*public*/ void ActionWarrant::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/ QString ActionWarrant::getLocalVariable() {
        return _localVariable;
    }

    /*public*/ void ActionWarrant::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _formula = formula;
        parseFormula();
    }

    /*public*/ QString ActionWarrant::getFormula() {
        return _formula;
    }

    /*private*/ void ActionWarrant::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser->parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }


    /*public*/ void ActionWarrant::setOperationAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _operationAddressing = addressing;
        parseOperFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionWarrant::getOperationAddressing() {
        return _operationAddressing;
    }

    /*public*/ void ActionWarrant::setOperationDirect(DirectOperation::TYPE state) {
        _operationDirect = state;
    }

    /*public*/ActionWarrant::DirectOperation::TYPE ActionWarrant::getOperationDirect() {
        return _operationDirect;
    }

    /*public*/ void ActionWarrant::setOperationReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _operationReference = reference;
    }

    /*public*/ QString ActionWarrant::getOperationReference() {
        return _operationReference;
    }

    /*public*/ void ActionWarrant::setOperationLocalVariable(/*@Nonnull*/ QString localVariable) {
        _operationLocalVariable = localVariable;
    }

    /*public*/ QString ActionWarrant::getOperationLocalVariable() {
        return _operationLocalVariable;
    }

    /*public*/ void ActionWarrant::setOperationFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
        _operationFormula = formula;
        parseOperFormula();
    }

    /*public*/ QString ActionWarrant::getOperFormula() {
        return _operationFormula;
    }

    /*private*/ void ActionWarrant::parseOperFormula() /*throws ParserException*/ {
        if (_operationAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _operationExpressionNode = parser->parseExpression(_operationFormula);
        } else {
            _operationExpressionNode = nullptr;
        }
    }


    /*public*/ void ActionWarrant::setDataAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _dataAddressing = addressing;
        parseDataFormula();
    }

    /*public*/ NamedBeanAddressing::TYPE ActionWarrant::getDataAddressing() {
        return _dataAddressing;
    }

    /*public*/ void ActionWarrant::setDataReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _dataReference = reference;
    }

    /*public*/ QString ActionWarrant::getDataReference() {
        return _dataReference;
    }

    /*public*/ void ActionWarrant::setDataLocalVariable(/*@Nonnull*/ QString localVariable) {
        _dataLocalVariable = localVariable;
    }

    /*public*/ QString ActionWarrant::getDataLocalVariable() {
        return _dataLocalVariable;
    }

    /*public*/ void ActionWarrant::setDataFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _dataFormula = formula;
        parseDataFormula();
    }

    /*public*/ QString ActionWarrant::getDataFormula() {
        return _dataFormula;
    }

    /*private*/ void ActionWarrant::parseDataFormula() /*throws ParserException*/ {
        if (_dataAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*>  variables = QMap<QString, Variable*> ();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _dataExpressionNode = parser->parseExpression(_dataFormula);
        } else {
            _dataExpressionNode = nullptr;
        }
    }


    /*public*/ void ActionWarrant::setTrainIdName(/*@Nonnull*/ QString trainIdName) {
        _trainIdName = trainIdName;
    }

    /*public*/ QString ActionWarrant::getTrainIdName() {
        return _trainIdName;
    }

    /*public*/ void ActionWarrant::setControlAutoTrain(ControlAutoTrain::TYPE controlAutoTrain) {
        _controlAutoTrain = controlAutoTrain;
    }

    /*public*/ ActionWarrant::ControlAutoTrain::TYPE ActionWarrant::getControlAutoTrain() {
        return _controlAutoTrain;
    }

    //@Override
    /*public*/ void ActionWarrant::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<Warrant>::asPtr(evt->getOldValue())) {
                if (VPtr<Warrant>::asPtr(evt->getOldValue())->equals(getWarrant()->getBean())) {
                    PropertyChangeEvent* e = new PropertyChangeEvent(this, "DoNotDelete", QVariant(), QVariant());
                    throw new PropertyVetoException(tr("Warrant is in use by Warrant action \"%1\"").arg(getDisplayName()), e); // NOI18N
                }
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ Category ActionWarrant::getCategory() {
        return Category::ITEM;
    }


    /*private*/ QString ActionWarrant::getNewOper() /*throws JmriException*/ {

        switch (_operationAddressing) {
        case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _operationReference);

        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_operationLocalVariable), false);
        }
        case NamedBeanAddressing::Formula:
                return _operationExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                              _operationExpressionNode->calculate(
                                  getConditionalNG()->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_operationAddressing));
        }
    }

    /*private*/ QString ActionWarrant::getNewData() /*throws JmriException*/ {

        switch (_dataAddressing) {
        case NamedBeanAddressing::Direct:
                switch(_operationDirect) {
                case DirectOperation::SetTrainId:
                case DirectOperation::SetTrainName:
                        return _trainIdName;
                case DirectOperation::ControlAutoTrain:
                    return ControlAutoTrain::toString(_controlAutoTrain);
                default:
                    return "";
                }

        case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _dataReference);

        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_dataLocalVariable), false);
        }
        case NamedBeanAddressing::Formula:
                return _operationExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                              _dataExpressionNode->calculate(
                                  getConditionalNG()->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_dataAddressing));
        }
    }


    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionWarrant::execute() /*throws JmriException*/ {
        Warrant* warrant;

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
            warrant = _warrantHandle != nullptr ? _warrantHandle->getBean() : nullptr;
                break;

        case NamedBeanAddressing::Reference:
        {
                QString ref = ReferenceUtil::getReference(
                            getConditionalNG()->getSymbolTable(), _reference);
                warrant = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))
                        ->getNamedBean(ref)->self();
                break;
        }
        case NamedBeanAddressing::LocalVariable:
        {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                warrant = (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))
                        ->getNamedBean(TypeConversionUtil
                                       ::convertToString(symbolTable->getValue(_localVariable), false))->self();
                break;
        }
        case NamedBeanAddressing::Formula:
                warrant = _expressionNode != nullptr ?
                        (Warrant*)((WarrantManager*)InstanceManager::getDefault("WarrantManager"))
                            ->getNamedBean(TypeConversionUtil
                                              ::convertToString(_expressionNode->calculate(
                                                                    getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        if (warrant == nullptr) {
            return;
        }

        QString name = (_operationAddressing != NamedBeanAddressing::Direct)
                ? getNewOper() : nullptr;

        DirectOperation::TYPE oper;
        if (_operationAddressing == NamedBeanAddressing::Direct) {
            oper = _operationDirect;
        } else {
            oper = DirectOperation::valueOf(name);
        }

        // Variables used in lambda must be effectively final
        DirectOperation::TYPE theOper = oper;
#if 0
        ThreadingUtil.runOnLayoutWithJmriException(() -> {
            QString msg;
            QString err;

            switch (theOper) {
                case AllocateWarrantRoute:
                    msg = warrant.allocateRoute(false, null);
                    if (msg != null) {
                        log.warn("Warrant {} - {}", warrant.getDisplayName(), msg);  // NOI18N
                    }
                    break;

                case DeallocateWarrant:
                    warrant.deAllocate();
                    break;

                case SetRouteTurnouts:
                    msg = warrant.setRoute(false, null);
                    if (msg != null) {
                        log.warn("Warrant {} unable to Set Route - {}", warrant.getDisplayName(), msg);  // NOI18N
                    }
                    break;

                case AutoRunTrain:
                    jmri.jmrit.logix.WarrantTableFrame frame = jmri.jmrit.logix.WarrantTableFrame.getDefault();
                    err = frame.runTrain(warrant, Warrant.MODE_RUN);
                    if (err != null) {
                        warrant.stopWarrant(true, true);
                        throw new JmriException("runAutoTrain error - " + err);  // NOI18N
                    }
                    break;

                case ManuallyRunTrain:
                        err = warrant.setRoute(false, null);
                        if (err == null) {
                            err = warrant.setRunMode(Warrant.MODE_MANUAL, null, null, null, false);
                        }
                        if (err != null) {
                            throw new JmriException("runManualTrain error - " + err);  // NOI18N
                        }
                    break;
// can control use the other data tabs?
                case ControlAutoTrain:
                    int controlAction = 0;
                    switch (_controlAutoTrain) {
                        case Halt:
                            controlAction = Warrant.HALT;
                            break;
                        case Resume:
                            controlAction = Warrant.RESUME;
                            break;
                        case Abort:
                            controlAction = Warrant.ABORT;
                            break;
                        default:
                            throw new IllegalArgumentException("invalid train control action: " + _controlAutoTrain);
                    }
                    if (!warrant.controlRunTrain(controlAction)) {
                        log.warn("Train {} not running  - {}", warrant.getSpeedUtil().getRosterId(), warrant.getDisplayName());  // NOI18N
                    }
                    break;
                case SetTrainId:
                    if(!warrant.getSpeedUtil().setAddress(getNewData())) {
                        throw new JmriException("invalid train ID in action - " + warrant.getDisplayName());  // NOI18N
                    }
                    break;
                case SetTrainName:
                    warrant.setTrainName(getNewData());
                    break;

                default:
                    throw new IllegalArgumentException("invalid oper state: " + theOper.name());
            }
        });
#endif
    }

    //@Override
    /*public*/ FemaleSocket* ActionWarrant::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/ int ActionWarrant::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/ QString ActionWarrant::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "ActionWarrant_Short");
    }

    //@Override
    /*public*/ QString ActionWarrant::getLongDescription(QLocale locale) {
        QString namedBean;
        QString state = "";

        switch (_addressing) {
        case NamedBeanAddressing::Direct:
        {
                QString warrantName;
                if (_warrantHandle != nullptr) {
                    warrantName = _warrantHandle->getBean()->getDisplayName();
                } else {
                    warrantName = tr(/*locale,*/ "BeanNotSelected");
                }
                namedBean = tr(/*locale,*/ "%1").arg(warrantName);
                break;
        }
        case NamedBeanAddressing::Reference:
                namedBean = tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

        case NamedBeanAddressing::LocalVariable:
                namedBean = tr(/*locale,*/ "by local variable %1").arg(_localVariable);
                break;

        case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale,*/ "by formulae %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_operationAddressing) {
        case NamedBeanAddressing::Direct:
                if (_operationDirect == DirectOperation::SetTrainId) {
                    //return getLongDataDescription(locale, "Set warrant \"%1\" train id to \"%2\"", namedBean, _trainIdName);
                    return tr("Set warrant \"%1\" train id to \"%2\"").arg(namedBean, _trainIdName);
                } else if (_operationDirect == DirectOperation::SetTrainName) {
                    //return getLongDataDescription(locale, "Set warrant \"%1\" train name to \"%2\"", namedBean, _trainIdName);
                    return tr("Set warrant \"%1\" train name to \"%2\"").arg(namedBean, _trainIdName);
                } else if (_operationDirect == DirectOperation::ControlAutoTrain) {
                    //return getLongDataDescription(locale, "Set warrant \"%1\" train control to \"%2\"", namedBean, ControlAutoTrain::toString(_controlAutoTrain));
                    return tr("Set warrant \"%1\" train control to \"%2\"").arg(namedBean, ControlAutoTrain::toString(_controlAutoTrain));
                } else {
                    state = tr(/*locale,*/ "%1").arg(DirectOperation::toString(_operationDirect));
                }
                break;

        case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_operationReference);
                break;

        case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg(_operationLocalVariable);
                break;

        case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formulae %1").arg(_operationFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_operationAddressing));
        }

        return tr(/*locale,*/ "Set warrant \"%1\" to %2").arg(namedBean, state);
    }

    /*private*/ QString ActionWarrant::getLongDataDescription(QLocale locale, QString bundleKey, QString namedBean, QString value) {
//        switch (_dataAddressing) {
//        case NamedBeanAddressing::Direct:
//                return tr(/*locale,*/ bundleKey, namedBean, value);
//        case NamedBeanAddressing::Reference:
//                return tr(/*locale,*/ bundleKey, namedBean, tr("by reference %1").arg(_dataReference));
//        case NamedBeanAddressing::LocalVariable:
//                return tr(/*locale,*/ bundleKey, namedBean, tr("by local variable %1").arg(_dataLocalVariable));
//        case NamedBeanAddressing::Formula:
//                return tr(/*locale,*/ bundleKey, namedBean, tr("by formulae %1").arg(_dataFormula));
//            default:
//                throw new IllegalArgumentException("invalid _dataAddressing state: " + NamedBeanAddressing::toString(_dataAddressing));
//        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionWarrant::setup() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionWarrant::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionWarrant::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionWarrant::disposeMe() {
    }
#if 0
    /*public*/ enum DirectOperation {
        None(""),
        AllocateWarrantRoute(Bundle.getMessage("ActionWarrant_AllocateWarrantRoute")),
        DeallocateWarrant(Bundle.getMessage("ActionWarrant_DeallocateWarrant")),
        SetRouteTurnouts(Bundle.getMessage("ActionWarrant_SetRouteTurnouts")),
        AutoRunTrain(Bundle.getMessage("ActionWarrant_AutoRunTrain")),
        ManuallyRunTrain(Bundle.getMessage("ActionWarrant_ManuallyRunTrain")),
        ControlAutoTrain(Bundle.getMessage("ActionWarrant_ControlAutoTrain")),
        SetTrainId(Bundle.getMessage("ActionWarrant_SetTrainId")),
        SetTrainName(Bundle.getMessage("ActionWarrant_SetTrainName"));

        /*private*/ final String _text;

        /*private*/ DirectOperation(String text) {
            this._text = text;
        }

        //@Override
        /*public*/ String toString() {
            return _text;
        }

    }

    /*public*/ enum ControlAutoTrain {
        Halt(Bundle.getMessage("ActionWarrant_Halt_AutoTrain")),
        Resume(Bundle.getMessage("ActionWarrant_Resume_AutoTrain")),
        Abort(Bundle.getMessage("ActionWarrant_Abort_AutoTrain"));

        /*private*/ final String _text;

        /*private*/ ControlAutoTrain(String text) {
            this._text = text;
        }

        //@Override
        /*public*/ String toString() {
            return _text;
        }

    }
#endif
    /** {@inheritDoc} */
    //@Override
    /*public*/ void ActionWarrant::getUsageDetail(int level, NamedBean* bean, QList<NamedBeanUsageReport*>* report, NamedBean* cdl) {
    log->debug(tr("getUsageReport :: ActionWarrant: bean = %1, report = %2").arg(cdl->getDisplayName(), report->at(0)->usageData));
                if (getWarrant() != nullptr && bean->equals((Warrant*)getWarrant()->getBean())) {
            report->append(new NamedBeanUsageReport("LogixNGAction", cdl, getLongDescription(QLocale())));
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionWarrant::log = LoggerFactory::getLogger("ActionWarrant");
