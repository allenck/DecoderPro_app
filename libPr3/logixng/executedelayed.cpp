#include "executedelayed.h"
#include "instancemanager.h"
#include "defaultdigitalactionmanager.h"
#include "referenceutil.h"
#include "recursivedescentparser.h"
#include "timerutil.h"
#include "typeconversionutil.h"
#include "referenceutil.h"
#include "loggerfactory.h"

/**
 * Executes a digital action delayed.
 *
 * @author Daniel Bergqvist Copyright 2021
 */
///*public*/  class ExecuteDelayed
//        extends AbstractDigitalAction
//        implements FemaleSocketListener {



/*public*/  ExecuteDelayed::ExecuteDelayed(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent){
    //super(sys, user);
 setObjectName("ExecuteDelayed");
    _socket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
            ->createFemaleSocket(this, this, "A");
}

//@Override
/*public*/  Base* ExecuteDelayed::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
    DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    ExecuteDelayed* copy = new ExecuteDelayed(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    copy->setDelayAddressing(_stateAddressing);
    copy->setDelay(_delay);
    copy->setDelayFormula(_stateFormula);
    copy->setDelayLocalVariable(_stateLocalVariable);
    copy->setDelayReference(_stateReference);
    copy->setUnit(_unit);
    copy->setResetIfAlreadyStarted(_resetIfAlreadyStarted);
    return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* ExecuteDelayed::getCategory() {
    return Category::COMMON;
}
/*
private QString getVariables(SymbolTable* symbolTable) {
    StringWriter* stringWriter = new StringWriter();
    PrintWriter* writer = new PrintWriter(stringWriter);
    symbolTable->printSymbolTable(writer);
    return stringWriter->toString();
}
*/
/**
 * Get a new timer task.
 */
/*private*/ ProtectedTimerTask* ExecuteDelayed::getNewTimerTask(ConditionalNG* conditionalNG) /*throws JmriException*/ {
    DefaultSymbolTable* newSymbolTable = new DefaultSymbolTable(conditionalNG->getSymbolTable());

    return new EDProtectedTimerTask(conditionalNG, newSymbolTable, this);
//    {
//        //@Override
//        /*public*/  void execute() {
//            try {
//                synchronized(ExecuteDelayed.this) {
//                    _timerTask = null;
//                    long currentTimerTime = System.currentTimeMillis() - _timerStart;
//                    if (currentTimerTime < _timerDelay) {
//                        scheduleTimer(conditionalNG, _timerDelay - currentTimerTime);
//                    } else {
//                        _internalSocket.conditionalNG = conditionalNG;
//                        _internalSocket.newSymbolTable = newSymbolTable;
//                        conditionalNG.execute(_internalSocket);
//                    }
//                }
//            }
//            catch (RuntimeException* e) {
//                log->error("Exception thrown", e);
//            }
//      catch ( JmriException* e) {
//          log->error("Exception thrown", e);
//      }
//        }
//    };
}

/*private*/ void ExecuteDelayed::scheduleTimer(ConditionalNG* conditionalNG, long delay) /*throws JmriException*/ {
    if (_timerTask != nullptr) _timerTask->stopTimer();
    _timerTask = getNewTimerTask(conditionalNG);
    TimerUtil::schedule(_timerTask, delay);
}

/*private*/ long ExecuteDelayed::getNewDelay() /*throws JmriException*/ {

    switch (_stateAddressing) {
        case NamedBeanAddressing::Direct:
            return _delay;

        case NamedBeanAddressing::Reference:
            return TypeConversionUtil::convertToLong(ReferenceUtil::getReference(
                    getConditionalNG()->getSymbolTable(), _stateReference));

        case NamedBeanAddressing::LocalVariable:
    {
            SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
            return TypeConversionUtil
                    ::convertToLong(symbolTable->getValue(_stateLocalVariable));
}
        case NamedBeanAddressing::Formula:
            return _stateExpressionNode != nullptr
                    ? TypeConversionUtil::convertToLong(
                            _stateExpressionNode->calculate(
                                    getConditionalNG()->getSymbolTable()))
                    : 0;

        default:
            throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_stateAddressing));
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExecuteDelayed::execute() /*throws JmriException*/ {
    /*synchronized(this)*/ {
  QMutexLocker locker(&mutex1);
        if (_timerTask != nullptr) {
            if (_resetIfAlreadyStarted) _timerTask->stopTimer();
            else return;
        }
        _timerDelay = getNewDelay() * TimerUnit::getMultiply(_unit);
        _timerStart = System::currentTimeMillis();
        scheduleTimer(getConditionalNG(), _delay * TimerUnit::getMultiply(_unit));
    }
}

/*public*/  void ExecuteDelayed::setDelayAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
    _stateAddressing = addressing;
    parseDelayFormula();
}

/*public*/  NamedBeanAddressing::TYPE ExecuteDelayed::getDelayAddressing() {
    return _stateAddressing;
}

/**
 * Get the delay.
 * @return the delay
 */
/*public*/  int ExecuteDelayed::getDelay() {
    return _delay;
}

/**
 * Set the delay.
 * @param delay the delay
 */
/*public*/  void ExecuteDelayed::setDelay(int delay) {
    _delay = delay;
}

/*public*/  void ExecuteDelayed::setDelayReference(/*@Nonnull */QString reference) {
    if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
        throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
    }
    _stateReference = reference;
}

/*public*/  QString ExecuteDelayed::getDelayReference() {
    return _stateReference;
}

/*public*/  void ExecuteDelayed::setDelayLocalVariable(/*@Nonnull*/ QString localVariable) {
    _stateLocalVariable = localVariable;
}

/*public*/  QString ExecuteDelayed::getDelayLocalVariable() {
    return _stateLocalVariable;
}

/*public*/  void ExecuteDelayed::setDelayFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
    _stateFormula = formula;
    parseDelayFormula();
}

/*public*/  QString ExecuteDelayed::getDelayFormula() {
    return _stateFormula;
}

/*private*/ void ExecuteDelayed::parseDelayFormula() /*throws ParserException*/ {
    if (_stateAddressing == NamedBeanAddressing::Formula) {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();

        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        _stateExpressionNode = parser->parseExpression(_stateFormula);
    } else {
        _stateExpressionNode = nullptr;
    }
}

/**
 * Get the unit
 * @return the unit
 */
/*public*/  TimerUnit::VAL ExecuteDelayed::getUnit() {
    return _unit;
}

/**
 * Set the unit
 * @param unit the unit
 */
/*public*/  void ExecuteDelayed::setUnit(TimerUnit::VAL unit) {
    _unit = unit;
}

/**
 * Get reset if timer is already started.
 * @return true if the timer should be reset if this action is executed
 *         while timer is ticking, false othervise
 */
/*public*/  bool ExecuteDelayed::getResetIfAlreadyStarted() {
    return _resetIfAlreadyStarted;
}

/**
 * Set reset if timer is already started.
 * @param resetIfAlreadyStarted true if the timer should be reset if this
 *                              action is executed while timer is ticking,
 *                              false othervise
 */
/*public*/  void ExecuteDelayed::setResetIfAlreadyStarted(bool resetIfAlreadyStarted) {
    _resetIfAlreadyStarted = resetIfAlreadyStarted;
}

//@Override
/*public*/  FemaleSocket* ExecuteDelayed::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    switch (index) {
        case 0:
            return _socket;

        default:
            throw new IllegalArgumentException(
                    QString("index has invalid value: %1").arg(index));
    }
}

//@Override
/*public*/  int ExecuteDelayed::getChildCount() {
    return 1;
}

//@Override
/*public*/  void ExecuteDelayed::connected(FemaleSocket* socket) {
    if (socket == _socket) {
        _socketSystemName = socket->getConnectedSocket()->getSystemName();
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

//@Override
/*public*/  void ExecuteDelayed::disconnected(FemaleSocket* socket) {
    if (socket == _socket) {
        _socketSystemName = nullptr;
    } else {
        throw new IllegalArgumentException("unkown socket");
    }
}

//@Override
/*public*/  QString ExecuteDelayed::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Execute delayed");
}

//@Override
/*public*/  QString ExecuteDelayed::getLongDescription(QLocale locale) {
    QString delay;

    switch (_stateAddressing) {
        case NamedBeanAddressing::Direct:
            delay = tr(/*locale,*/ "%1").arg(TimerUnit::getTimeWithUnit(_unit, _delay));
            break;

        case NamedBeanAddressing::Reference:
            delay = tr(/*locale,*/ "by reference %1 in unit %2").arg(_stateReference, TimerUnit::toString(_unit));
            break;

        case NamedBeanAddressing::LocalVariable:
            delay = tr(/*locale,*/ "by local variable %1 in unit %2").arg(_stateLocalVariable, TimerUnit::toString(_unit));
            break;

        case NamedBeanAddressing::Formula:
            delay = tr(/*locale,*/ "by formula %1 in unit %2").arg(_stateFormula, TimerUnit::toString(_unit));
            break;

        default:
            throw new IllegalArgumentException("invalid _stateAddressing state: " + NamedBeanAddressing::toString(_stateAddressing));
    }

    return tr(/*locale,*/
            "Execute %1 after %2. %3").arg(
            _socket->getName(),
            delay,
            _resetIfAlreadyStarted
                    ? tr("Reset on repeat")
                    : tr("Ignore on repeat"));
}

/*public*/  FemaleDigitalActionSocket* ExecuteDelayed::getSocket() {
    return _socket;
}

/*public*/  QString ExecuteDelayed::getSocketSystemName() {
    return _socketSystemName;
}

/*public*/  void ExecuteDelayed::setSocketSystemName(QString systemName) {
    _socketSystemName = systemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExecuteDelayed::setup() {
    try {
        if (!_socket->isConnected()
                || _socket->getConnectedSocket()->getSystemName()
                         != (_socketSystemName)) {

            QString socketSystemName = _socketSystemName;

            _socket->_disconnect();

            if (socketSystemName != nullptr) {
                MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalActionManager*)
                        InstanceManager::getDefault("DigitalActionManager"))
                                ->getBySystemName(socketSystemName)->self();
                if (maleSocket != nullptr) {
                    _socket->_connect(maleSocket);
                    maleSocket->setup();
                } else {
                    log->error("cannot load analog action " + socketSystemName);
                }
            }
        } else {
            _socket->getConnectedSocket()->setup();
        }
    } catch (SocketAlreadyConnectedException* ex) {
        // This shouldn't happen and is a runtime error if it does.
        throw new RuntimeException("socket is already connected");
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExecuteDelayed::registerListenersForThisClass() {
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExecuteDelayed::unregisterListenersForThisClass() {
    if (_timerTask != nullptr) {
        _timerTask->stopTimer();
        _timerTask = nullptr;
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void ExecuteDelayed::disposeMe() {
}




/*private*/ /*final*/ /*static*/ Logger* ExecuteDelayed::log = LoggerFactory::getLogger("ExecuteDelayed");
