#include "actionpositionable.h"
#include "loggerfactory.h"
#include "digitalactionmanager.h"
#include "instancemanager.h"
#include "editormanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "categorydisplay.h"
#include "conditionalng.h"
#include "typeconversionutil.h"
#include "runtimeexception.h"

/**
 * This action controls various things of a Positionable on a panel.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ActionPositionable extends AbstractDigitalAction implements VetoableChangeListener {



    /*public*/  ActionPositionable::ActionPositionable(QString sys, QString user, QObject* parent)
     : AbstractDigitalAction(sys, user)
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
            _expressionNode = parser->parseExpression(_formula);
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

    /*public*/  void  ActionPositionable::setOperation(ActionPositionable::Operation::TYPE isControlling) {
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
            case NamedBeanAddressing::Reference:
                return ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _stateReference);

            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                return TypeConversionUtil::
                        convertToString(symbolTable->getValue(_stateLocalVariable), false);
            }
            case NamedBeanAddressing::Formula:
                return _stateExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                                _stateExpressionNode->calculate(
                                        getConditionalNG()->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPositionable::execute() /*throws JmriException*/ {
        Positionable* positionable;

//        System.out.format("ActionPositionable.execute: %s%n", getLongDescription());

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                positionable = this->_positionable;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _reference);
                positionable = _editor->getIdContents().value(ref);
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                positionable = _editor->getIdContents().value(TypeConversionUtil::
                                convertToString(symbolTable->getValue(_localVariable), false));
                break;
            }
            case NamedBeanAddressing::Formula:
                positionable = _expressionNode != nullptr ?
                        _editor->getIdContents().value(TypeConversionUtil::
                                        convertToString(_expressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ActionPositionable.execute: positionable: %s%n", positionable);

        if (positionable == nullptr) {
            log->error("positionable is null");
            return;
        }

        QString name = (_stateAddressing != NamedBeanAddressing::Direct)
                ? getNewState() : nullptr;

        Operation::TYPE operation;
        if (_stateAddressing == NamedBeanAddressing::Direct) {
            operation = _operation;
        } else {
            operation = Operation::valueOf(name);
        }

        ThreadingUtil::runOnLayout(new MyThreadAction(operation, positionable, this));
}

        void MyThreadAction::run()
        {
            switch (operation) {
                case ActionPositionable::Operation::TYPE::Disable:
                    positionable->setControlling(false);
                    break;
                case ActionPositionable::Operation::Enable:
                    positionable->setControlling(true);
                    break;
                case ActionPositionable::Operation::Hide:
                    positionable->setHidden(true);
                    break;
                case ActionPositionable::Operation::Show:
                    positionable->setHidden(false);
                    break;
                default:
                    throw new RuntimeException("operation has invalid value: "+ActionPositionable::Operation::toString(operation));
            }
        };



    //@Override
    /*public*/  FemaleSocket* ActionPositionable::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        throw new UnsupportedOperationException("Not supported.");
    }

    //@Override
    /*public*/  int ActionPositionable::getChildCount() {
        return 0;
    }

    //@Override
    /*public*/  QString ActionPositionable::getShortDescription(QLocale locale) {
        return tr(/*locale, */"Icon/Label on panel");
    }

    //@Override
    /*public*/  QString ActionPositionable::getLongDescription(QLocale locale) {
        QString editorName = _editorName != nullptr ? _editorName : tr(/*locale,*/ "Bean Not Selected");
        QString positonableName;
        QString state;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString positionableName;
                if (this->_positionableName != "") {
                    positionableName = this->_positionableName;
                } else {
                    positionableName = tr(/*locale,*/ "Bean Not Selected");
                }
                positonableName = tr(/*locale,*/ "%1").arg(positionableName);
                break;
            }
            case NamedBeanAddressing::Reference:
                positonableName = tr(/*locale,*/ "by reference %1").arg(_reference);
                break;

            case NamedBeanAddressing::LocalVariable:
                positonableName = tr(/*locale, */"by local variable %1").arg(_localVariable);
                break;

            case NamedBeanAddressing::Formula:
                positonableName = tr(/*locale,*/ "by formula %1").arg(_formula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_stateAddressing) {
            case NamedBeanAddressing::Direct:
                state = tr(/*locale,*/ "by direct %1").arg(Operation::toString(_operation));
                break;

            case NamedBeanAddressing::Reference:
                state = tr(/*locale,*/ "by reference %1").arg(_stateReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                state = tr(/*locale,*/ "by local variable %1").arg(_stateLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                state = tr(/*locale,*/ "by formula %1").arg(_stateFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
        }

        return tr(/*locale,*/ "Set icon/label \"%2\" on panel \"%1\" to \"%3\"").arg(editorName, positonableName, state);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionPositionable::setup() {
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
    /*public*/  void ActionPositionable::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/  void ActionPositionable::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    ////@Override
    /*public*/  void ActionPositionable::disposeMe() {
    }


//    /*public*/  enum Operation {
//        Disable(Bundle.getMessage("ActionPositionable_Disable")),
//        Enable(Bundle.getMessage("ActionPositionable_Enable")),
//        Hide(Bundle.getMessage("ActionPositionable_Hide")),
//        Show(Bundle.getMessage("ActionPositionable_Show"));

//        /*private*/ /*final*/ String _text;

//        /*private*/ Operation(String text) {
//            this._text = text;
//        }

//        ////@Override
//        /*public*/  String toString() {
//            return _text;
//        }

//    }

    /*private*/ /*final*/ /*static*/ Logger* ActionPositionable::log = LoggerFactory::getLogger("ActionPositionable");
