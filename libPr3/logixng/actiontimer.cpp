#include "actiontimer.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "timerutil.h"
#include "vptr.h"

/**
 * Executes an action after some time.
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class ActionTimer extends AbstractDigitalAction
//        implements FemaleSocketListener {

    /*public*/  /*static*/ /*final*/ int ActionTimer::EXPRESSION_START = 0;
    /*public*/  /*static*/ /*final*/ int ActionTimer::EXPRESSION_STOP = 1;
    /*public*/  /*static*/ /*final*/ int ActionTimer::NUM_STATIC_EXPRESSIONS = 2;



    /*public*/  ActionTimer::ActionTimer(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent){
        //super(sys, user);
        _startExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Start"));
        _stopExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Stop"));
        _actionEntries
                .append(new ActionEntry(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName())));
    }

    /*public*/  ActionTimer::ActionTimer(QString sys, QString user,
            QList<QMap<QString, QString>> expressionSystemNames,
            QList<ActionData*> actionDataList, QObject* parent)
            /*throws BadUserNameException, BadSystemNameException*/ : AbstractDigitalAction(sys, user, parent){
        //super(sys, user);
        _startExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Start"));
        _stopExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Stop"));
        setActionData(actionDataList);
    }

    //@Override
    /*public*/  Base* ActionTimer::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        ActionTimer* copy = new ActionTimer(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setNumActions(getNumActions());
        for (int i=0; i < getNumActions(); i++) {
            copy->setDelay(i, getDelay(i));
        }
        copy->setStartImmediately(_startImmediately);
        copy->setRunContinuously(_runContinuously);
        copy->setUnit(_unit);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*private*/ void ActionTimer::setActionData(QList<ActionData*> actionDataList) {
        if (!_actionEntries.isEmpty()) {
            throw new RuntimeException("action system names cannot be set more than once");
        }

        for (ActionData* data : actionDataList) {
            FemaleDigitalActionSocket* socket =((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->createFemaleSocket(this, this, data->_socketName);

            _actionEntries.append(new ActionEntry(data->_delay, socket, data->_socketSystemName));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* ActionTimer::getCategory() {
        return Category::COMMON;
    }

    /**
     * Get a new timer task.
     */
    /*private*/ ProtectedTimerTask* ActionTimer::getNewTimerTask() {
        return new ActionTimer_ProtectedTimerTask(this);
//        {
//            //@Override
//            /*public*/  void execute() {
//                try {
//                    long currentTimerTime = System.currentTimeMillis() - _currentTimerStart;
//                    if (currentTimerTime < _currentTimerDelay) {
//                        scheduleTimer(_currentTimerDelay - currentTimerTime);
//                    } else {
//                        _timerState = TimerState.Completed;
//                        getConditionalNG().execute();
//                    }
//                } catch (Exception e) {
//                    log.error("Exception thrown", e);
//                }
//            }
//        };
    }

    /*private*/ void ActionTimer::scheduleTimer(long delay) {
        /*synchronized(this)*/ {
  QMutexLocker locker(&mutex1);
            if (_timerTask != nullptr) {
                _timerTask->stopTimer();
                _timerTask = nullptr;
            }
        }
        _timerTask = getNewTimerTask();
        TimerUtil::schedule(_timerTask, delay);
    }

    /*private*/ void ActionTimer::schedule() {
        /*synchronized(this)*/ {
  QMutexLocker locker(&mutex2);
            ActionEntry* ae = _actionEntries.at(_currentTimer);
            _currentTimerDelay = ae->_delay * TimerUnit::getMultiply(_unit);
            _currentTimerStart = System::currentTimeMillis();
            _timerState = TimerState::WaitToRun;
            scheduleTimer(ae->_delay * TimerUnit::getMultiply(_unit));
        }
    }

    /*private*/ bool ActionTimer::start() /*throws JmriException*/ {
        bool lastStartIsActive = _startIsActive;
        _startIsActive = _startExpressionSocket->isConnected() && _startExpressionSocket->evaluate();
        return _startIsActive && !lastStartIsActive;
    }

    /*private*/ bool ActionTimer::checkStart() /*throws JmriException*/ {
        if (start()) _timerState = TimerState::RunNow;

        if (_timerState == TimerState::RunNow) {
            /*synchronized(this)*/ {
          QMutexLocker locker(&mutex3);
                if (_timerTask != nullptr) {
                    _timerTask->stopTimer();
                    _timerTask = nullptr;
                }
            }
            _currentTimer = 0;
            while (_currentTimer < _actionEntries.size()) {
                ActionEntry* ae = _actionEntries.at(_currentTimer);
                if (ae->_delay > 0) {
                    schedule();
                    return true;
                }
                else {
                    _currentTimer++;
                }
            }
            // If we get here, all timers has a delay of 0 ms
            _timerState = TimerState::Off;
            return true;
        }

        return false;
    }

    /*private*/ bool ActionTimer::stop() /*throws JmriException*/ {
        if (_stopExpressionSocket->isConnected()
                && _stopExpressionSocket->evaluate()) {
            /*synchronized(this)*/ {
          QMutexLocker locker(&mutex4);
                if (_timerTask != nullptr) _timerTask->stopTimer();
                _timerTask = nullptr;
            }
            _timerState = TimerState::Off;
            return true;
        }
        return false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTimer::execute() /*throws JmriException*/ {
        if (stop()) return;

        if (checkStart()) return;

        if (_timerState == TimerState::Off) return;
        if (_timerState == TimerState::Running) return;

        int startTimer = _currentTimer;
        while (_timerState == TimerState::Completed) {
            // If the timer has passed full time, execute the action
            if ((_timerState == TimerState::Completed) && _actionEntries.at(_currentTimer)->_socket->isConnected()) {
                _actionEntries.at(_currentTimer)->_socket->execute();
            }

            // Move to them next timer
            _currentTimer++;
            if (_currentTimer >= _actionEntries.size()) {
                _currentTimer = 0;
                if (!_runContinuously) {
                    _timerState = TimerState::Off;
                    return;
                }
            }

            ActionEntry* ae = _actionEntries.at(_currentTimer);
            if (ae->_delay > 0) {
                schedule();
                return;
            }

            if (startTimer == _currentTimer) {
                // If we get here, all timers has a delay of 0 ms
                _timerState = TimerState::Off;
            }
        }
    }

    /**
     * Get the delay.
     * @param actionSocket the socket
     * @return the delay
     */
    /*public*/  int ActionTimer::getDelay(int actionSocket) {
        return _actionEntries.at(actionSocket)->_delay;
    }

    /**
     * Set the delay.
     * @param actionSocket the socket
     * @param delay the delay
     */
    /*public*/  void ActionTimer::setDelay(int actionSocket, int delay) {
        _actionEntries.at(actionSocket)->_delay = delay;
    }

    /**
     * Get if to start immediately
     * @return true if to start immediately
     */
    /*public*/  bool ActionTimer::getStartImmediately() {
        return _startImmediately;
    }

    /**
     * Set if to start immediately
     * @param startImmediately true if to start immediately
     */
    /*public*/  void ActionTimer::setStartImmediately(bool startImmediately) {
        _startImmediately = startImmediately;
    }

    /**
     * Get if run continuously
     * @return true if run continuously
     */
    /*public*/  bool ActionTimer::getRunContinuously() {
        return _runContinuously;
    }

    /**
     * Set if run continuously
     * @param runContinuously true if run continuously
     */
    /*public*/  void ActionTimer::setRunContinuously(bool runContinuously) {
        _runContinuously = runContinuously;
    }

    /**
     * Get the unit
     * @return the unit
     */
    /*public*/  TimerUnit::VAL ActionTimer::getUnit() {
        return _unit;
    }

    /**
     * Set the unit
     * @param unit the unit
     */
    /*public*/  void ActionTimer::setUnit(TimerUnit::VAL unit) {
        _unit = unit;
    }

    //@Override
    /*public*/  FemaleSocket* ActionTimer::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        if (index == EXPRESSION_START) return _startExpressionSocket;
        if (index == EXPRESSION_STOP) return _stopExpressionSocket;
        if ((index < 0) || (index >= (NUM_STATIC_EXPRESSIONS + _actionEntries.size()))) {
            throw new IllegalArgumentException(
                    QString("index has invalid value: %1").arg(index));
        }
        return _actionEntries.at(index - NUM_STATIC_EXPRESSIONS)->_socket;
    }

    //@Override
    /*public*/  int ActionTimer::getChildCount() {
        return NUM_STATIC_EXPRESSIONS + _actionEntries.size();
    }

    //@Override
    /*public*/  void ActionTimer::connected(FemaleSocket* socket) {
        if (socket == _startExpressionSocket) {
            _startExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _stopExpressionSocket) {
            _stopExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            for (ActionEntry* entry : _actionEntries) {
                if (socket == entry->_socket) {
                    entry->_socketSystemName =
                            socket->getConnectedSocket()->getSystemName();
                }
            }
        }
    }

    //@Override
    /*public*/  void ActionTimer::disconnected(FemaleSocket* socket) {
        if (socket == _startExpressionSocket) {
            _startExpressionSocketSystemName = "";
        } else if (socket == _stopExpressionSocket) {
            _stopExpressionSocketSystemName = "";
        } else {
            for (ActionEntry* entry : _actionEntries) {
                if (socket == entry->_socket) {
                    entry->_socketSystemName = "";
                }
            }
        }
    }

    //@Override
    /*public*/  QString ActionTimer::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Timer");
    }

    //@Override
    /*public*/  QString ActionTimer::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Timer");
    }

    /*public*/  FemaleDigitalExpressionSocket* ActionTimer::getStartExpressionSocket() {
        return _startExpressionSocket;
    }

    /*public*/  QString ActionTimer::getStartExpressionSocketSystemName() {
        return _startExpressionSocketSystemName;
    }

    /*public*/  void ActionTimer::setStartExpressionSocketSystemName(QString systemName) {
        _startExpressionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalExpressionSocket* ActionTimer::getStopExpressionSocket() {
        return _stopExpressionSocket;
    }

    /*public*/  QString ActionTimer::getStopExpressionSocketSystemName() {
        return _stopExpressionSocketSystemName;
    }

    /*public*/  void ActionTimer::setStopExpressionSocketSystemName(QString systemName) {
        _stopExpressionSocketSystemName = systemName;
    }

    /*public*/  int ActionTimer::ActionTimer::getNumActions() {
        return _actionEntries.size();
    }

    /*public*/  void ActionTimer::ActionTimer::setNumActions(int num) {
        QVariantList addList = QVariantList();
        QVariantList removeList = QVariantList();

        // Is there too many children?
        while (_actionEntries.size() > num) {
            ActionEntry* ae = _actionEntries.at(num);
            if (ae->_socket->isConnected()) {
                throw new IllegalArgumentException("Cannot remove sockets that are connected");
            }
            removeList.append(VPtr<FemaleSocket>::asQVariant(_actionEntries.at(_actionEntries.size()-1)->_socket));
            _actionEntries.removeAt(_actionEntries.size()-1);
        }

        // Is there not enough children?
        while (_actionEntries.size() < num) {
            FemaleDigitalActionSocket* socket = ((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->createFemaleSocket(this, this, getNewSocketName());
            _actionEntries.append(new ActionEntry(socket));
            addList.append(VPtr<FemaleSocket>::asQVariant(socket));
        }
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, addList);
    }

    /*public*/  FemaleDigitalActionSocket* ActionTimer::getActionSocket(int socket) {
        return _actionEntries.at(socket)->_socket;
    }

    /*public*/  QString ActionTimer::getActionSocketSystemName(int socket) {
        return _actionEntries.at(socket)->_socketSystemName;
    }

    /*public*/  void ActionTimer::setActionSocketSystemName(int socket, QString systemName) {
        _actionEntries.at(socket)->_socketSystemName = systemName;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTimer::setup() {
        try {
            if ( !_startExpressionSocket->isConnected()
                    || _startExpressionSocket->getConnectedSocket()->getSystemName()
                            !=(_startExpressionSocketSystemName)) {

                QString socketSystemName = _startExpressionSocketSystemName;
                _startExpressionSocket->_disconnect();
                if (socketSystemName != nullptr) {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalExpressionManager*)
                            InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName)->self();
                    if (maleSocket != nullptr) {
                        _startExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                _startExpressionSocket->getConnectedSocket()->setup();
            }

            if ( !_stopExpressionSocket->isConnected()
                    || _stopExpressionSocket->getConnectedSocket()->getSystemName()
                            != (_stopExpressionSocketSystemName)) {

                QString socketSystemName = _stopExpressionSocketSystemName;
                _stopExpressionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalExpressionManager*)
                            InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName)->self();
                    _stopExpressionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _stopExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                _stopExpressionSocket->getConnectedSocket()->setup();
            }

            for (ActionEntry* ae : _actionEntries) {
                if ( !ae->_socket->isConnected()
                        || ae->_socket->getConnectedSocket()->getSystemName()
                                != (ae->_socketSystemName)) {

                    QString socketSystemName = ae->_socketSystemName;
                    ae->_socket->_disconnect();
                    if (socketSystemName != "") {
                        MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalActionManager*)
                                InstanceManager::getDefault("DigitalActionManager"))
                                        ->getBySystemName(socketSystemName)->self();
                        ae->_socket->_disconnect();
                        if (maleSocket != nullptr) {
                            ae->_socket->_connect(maleSocket);
                            maleSocket->setup();
                        } else {
                            log->error("cannot load digital action " + socketSystemName);
                        }
                    }
                } else {
                    ae->_socket->getConnectedSocket()->setup();
                }
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTimer::registerListenersForThisClass() {
        if (!_listenersAreRegistered) {
            // If _timerState is not TimerState.Off, the timer was running when listeners wss unregistered
            if ((_startImmediately) || (_timerState != TimerState::Off)) {
                if (_timerState == TimerState::Off) _timerState = TimerState::RunNow;
                getConditionalNG()->execute();
            }
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTimer::unregisterListenersForThisClass() {
        /*synchronized(this)*/ {
  QMutexLocker locker(&mutex6);
            // stopTimer() will not return until the timer task
            // is cancelled and stopped.
            if (_timerTask != nullptr) _timerTask->stopTimer();
            _timerTask = nullptr;
            _timerState = TimerState::Off;
        }
        _listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void ActionTimer::disposeMe() {
        /*synchronized(this)*/ {
        QMutexLocker locker(&mutex5);
            if (_timerTask != nullptr) _timerTask->stopTimer();
            _timerTask = nullptr;
        }
    }

    /*private*/ /*final*/ /*static*/ Logger* ActionTimer::log = LoggerFactory::getLogger("ActionTimer");
