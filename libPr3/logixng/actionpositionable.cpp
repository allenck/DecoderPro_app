#include "actionpositionable.h"
#include "loggerfactory.h"
#include "digitalactionmanager.h"
#include "instancemanager.h"
#include "editormanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "categorydisplay.h"
/**
 * This action controls various things of a Positionable on a panel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ActionPositionable extends AbstractDigitalAction implements VetoableChangeListener {



    /*public*/  ActionPositionable::ActionPositionable(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
    }

    //@Override
    /*public*/  Base*  ActionPositionable::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws ParserException*/ {
        DigitalActionManager* manager = (DigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames.value(AbstractNamedBean::getSystemName());
        QString userName = userNames.value(AbstractNamedBean::getSystemName());
        if (sysName == nullptr) sysName = manager->getAutoSystemName();
        ActionPositionable* copy = new ActionPositionable(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setEditor(_editorName);
        copy->setPositionable(_positionableName);
        copy->setOperation(_operation);
        copy->setAddressing(_addressing);
        copy->setFormula(_formula);
        copy->setLocalVariable(_localVariable);
        copy->setReference(_reference);
        copy->setStateAddressing(_stateAddressing);
        copy->setStateFormula(_stateFormula);
        copy->setStateLocalVariable(_stateLocalVariable);
        copy->setStateReference(_stateReference);
        return manager->registerAction(copy);
    }

    /*public*/  void  ActionPositionable::setEditor(/*@CheckForNull*/ QString editorName) {
        assertListenersAreNotRegistered(log, "setEditor");
        _editorName = editorName;
        if (editorName != "") { ActionPositionable::
            _editor = (( EditorManager*)InstanceManager::getDefault("EditorManager"))->getByName(editorName);
        } else {
            _editor = nullptr;
        }
//        InstanceManager.turnoutManagerInstance().addVetoableChangeListener(this);
    }

    /*public*/  QString  ActionPositionable::getEditorName() {
        return _editorName;
    }

    /*public*/  void  ActionPositionable::setPositionable(/*@CheckForNull*/ QString positionableName) {
        assertListenersAreNotRegistered(log, "setPositionable");
        _positionableName = positionableName;
        if ((positionableName != "") && (_editor != nullptr)) {
            _positionable = _editor->getIdContents().value(_positionableName);
        } else {
            _positionable = nullptr;
        }
//        InstanceManager.turnoutManagerInstance().addVetoableChangeListener(this);
    }

    /*public*/  QString  ActionPositionable::getPositionableName() {
        return _positionableName;
    }

    /*public*/  void  ActionPositionable::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */{
        _addressing = addressing;
        parseFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE  ActionPositionable::getAddressing() {
        return _addressing;
    }

    /*public*/  void  ActionPositionable::setReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _reference = reference;
    }

    /*public*/  QString  ActionPositionable::getReference() {
        return _reference;
    }

    /*public*/  void  ActionPositionable::setLocalVariable(/*@Nonnull*/ QString localVariable) {
        _localVariable = localVariable;
    }

    /*public*/  QString  ActionPositionable::getLocalVariable() {
        return _localVariable;
    }

    /*public*/  void  ActionPositionable::setFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
        _formula = formula;
        parseFormula();
    }

    /*public*/  QString  ActionPositionable::getFormula() {
        return _formula;
    }

    /*private*/ void  ActionPositionable::parseFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _expressionNode = parser.parseExpression(_formula);
        } else {
            _expressionNode = nullptr;
        }
    }

    /*public*/  void  ActionPositionable::setStateAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException */{
        _stateAddressing = addressing;
        parseStateFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE  ActionPositionable::getStateAddressing() {
        return _stateAddressing;
    }

    /*public*/  void  ActionPositionable::setOperation(Operation::TYPE isControlling) {
        _operation = isControlling;
    }

    /*public*/  ActionPositionable::Operation::TYPE ActionPositionable::getOperation() {
        return _operation;
    }

    /*public*/  void  ActionPositionable::setStateReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _stateReference = reference;
    }

    /*public*/  QString  ActionPositionable::getStateReference() {
        return _stateReference;
    }

    /*public*/  void  ActionPositionable::setStateLocalVariable(/*@Nonnull*/ QString localVariable) {
        _stateLocalVariable = localVariable;
    }

    /*public*/  QString  ActionPositionable::getStateLocalVariable() {
        return _stateLocalVariable;
    }

    /*public*/  void  ActionPositionable::setStateFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _stateFormula = formula;
        parseStateFormula();
    }

    /*public*/  QString  ActionPositionable::getStateFormula() {
        return _stateFormula;
    }

    /*private*/ void  ActionPositionable::parseStateFormula() /*throws ParserException*/ {
        if (_stateAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _stateExpressionNode = parser->parseExpression(_stateFormula);
        } else {
            _stateExpressionNode = nullptr;
        }
    }

    //@Override
    /*public*/  void  ActionPositionable::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException*/ {
/*
        if ("CanDelete".equals(evt.getPropertyName())) { // No I18N
            if (evt.getOldValue() instanceof Turnout) {
                if (evt.getOldValue().equals(getTurnout().getBean())) {
                    PropertyChangeEvent e = new PropertyChangeEvent(this, "DoNotDelete", null, null);
                    throw new PropertyVetoException(Bundle.getMessage("Turnout_TurnoutInUseTurnoutExpressionVeto", getDisplayName()), e); // NOI18N
                }
            }
        } else if ("DoDelete".equals(evt.getPropertyName())) { // No I18N
            if (evt.getOldValue() instanceof Turnout) {
                if (evt.getOldValue().equals(getTurnout().getBean())) {
                    removeTurnout();
                }
            }
        }
*/
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category*  ActionPositionable::getCategory() {
        return CategoryDisplay::DISPLAY;
    }

    /*private*/ QString  ActionPositionable::getNewState() /*throws JmriException*/ {

        switch (_stateAddressing) {
            case Reference:
                return ReferenceUtil.getReference(
                        getConditionalNG().getSymbolTable(), _stateReference);

            case LocalVariable:
                SymbolTable symbolTable = getConditionalNG().getSymbolTable();
                return TypeConversionUtil
                        .convertToString(symbolTable.getValue(_stateLocalVariable), false);

            case Formula:
                return _stateExpressionNode != null
                        ? TypeConversionUtil.convertToString(
                                _stateExpressionNode.calculate(
                                        getConditionalNG().getSymbolTable()), false)
                        : null;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + _stateAddressing.name());
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void execute() throws JmriException {
        Positionable positionable;

//        System.out.format("ActionPositionable.execute: %s%n", getLongDescription());

        switch (_addressing) {
            case Direct:
                positionable = this._positionable;
                break;

            case Reference:
                String ref = ReferenceUtil.getReference(
                        getConditionalNG().getSymbolTable(), _reference);
                positionable = _editor.getIdContents().get(ref);
                break;

            case LocalVariable:
                SymbolTable symbolTable = getConditionalNG().getSymbolTable();
                positionable = _editor.getIdContents().get(TypeConversionUtil
                                .convertToString(symbolTable.getValue(_localVariable), false));
                break;

            case Formula:
                positionable = _expressionNode != null ?
                        _editor.getIdContents().get(TypeConversionUtil
                                        .convertToString(_expressionNode.calculate(
                                                getConditionalNG().getSymbolTable()), false))
                        : null;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + _addressing.name());
        }

//        System.out.format("ActionPositionable.execute: positionable: %s%n", positionable);

        if (positionable == null) {
            log.error("positionable is null");
            return;
        }

        String name = (_stateAddressing != NamedBeanAddressing.Direct)
                ? getNewState() : null;

        Operation operation;
        if ((_stateAddressing == NamedBeanAddressing.Direct)) {
            operation = _operation;
        } else {
            operation = Operation.valueOf(name);
        }

        ThreadingUtil.runOnLayout(() -> {
            switch (operation) {
                case Disable:
                    positionable.setControlling(false);
                    break;
                case Enable:
                    positionable.setControlling(true);
                    break;
                case Hide:
                    positionable.setHidden(true);
                    break;
                case Show:
                    positionable.setHidden(false);
                    break;
                default:
                    throw new RuntimeException("operation has invalid value: "+operation.name());
            }
        });
    }

    //@Override
    /*public*/  FemaleSocket getChild(int index) throws IllegalArgumentException, UnsupportedOperationException {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  String getShortDescription(Locale locale) {
        return Bundle.getMessage(locale, "ActionPositionable_Short");
    }

    //@Override
    /*public*/  String getLongDescription(Locale locale) {
        String editorName = _editorName != null ? _editorName : Bundle.getMessage(locale, "BeanNotSelected");
        String positonableName;
        String state;

        switch (_addressing) {
            case Direct:
                String positionableName;
                if (this._positionableName != null) {
                    positionableName = this._positionableName;
                } else {
                    positionableName = Bundle.getMessage(locale, "BeanNotSelected");
                }
                positonableName = Bundle.getMessage(locale, "AddressByDirect", positionableName);
                break;

            case Reference:
                positonableName = Bundle.getMessage(locale, "AddressByReference", _reference);
                break;

            case LocalVariable:
                positonableName = Bundle.getMessage(locale, "AddressByLocalVariable", _localVariable);
                break;

            case Formula:
                positonableName = Bundle.getMessage(locale, "AddressByFormula", _formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + _addressing.name());
        }

        switch (_stateAddressing) {
            case Direct:
                state = Bundle.getMessage(locale, "AddressByDirect", _operation._text);
                break;

            case Reference:
                state = Bundle.getMessage(locale, "AddressByReference", _stateReference);
                break;

            case LocalVariable:
                state = Bundle.getMessage(locale, "AddressByLocalVariable", _stateLocalVariable);
                break;

            case Formula:
                state = Bundle.getMessage(locale, "AddressByFormula", _stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + _stateAddressing.name());
        }

        return Bundle.getMessage(locale, "ActionPositionable_Long", editorName, positonableName, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void setup() {
        // Do nothing
/*
        if ((_editorName != null) && (_editor == null)) {
            setEditor(_editorName);
        }
        if ((_positionableName != null) && (_positionable == null)) {
            setPositionable(_positionableName);
        }
*/
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/  void unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/  void disposeMe() {
    }


    /*public*/  enum Operation {
        Disable(Bundle.getMessage("ActionPositionable_Disable")),
        Enable(Bundle.getMessage("ActionPositionable_Enable")),
        Hide(Bundle.getMessage("ActionPositionable_Hide")),
        Show(Bundle.getMessage("ActionPositionable_Show"));

        /*private*/ /*final*/ String _text;

        /*private*/ Operation(String text) {
            this._text = text;
        }

        ////@Override
        /*public*/  String toString() {
            return _text;
        }

    }

    /*private*/ /*final*/ /*static*/ Logger* log = LoggerFactory::getLogger("ActionPositionable");
