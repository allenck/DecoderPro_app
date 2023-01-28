#include "sequence.h"
#include "loggerfactory.h"
#include "instancemanager.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultdigitalactionmanager.h"
#include "abstractdigitalexpression.h"
#include "vptr.h"

/**
 * Executes actions in a sequence.
 *
 * @author Daniel Bergqvist Copyright 2020
 */
///*public*/  class Sequence extends AbstractDigitalAction
//        implements FemaleSocketListener {



    /*public*/  Sequence::Sequence(QString sys, QString user, QObject* parent)
     : AbstractDigitalAction(sys, user, parent){
        //super(sys, user);
        _startExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
               ->createFemaleSocket(this, this, tr("Start"));
        _stopExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Stop"));
        _resetExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("Reset"));
        _actionEntries
                .append(ActionEntry(((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                        ->createFemaleSocket(this, this, getNewActionSocketName())));
        _expressionEntries
                .append(ExpressionEntry(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewExpressionSocketName())));
    }

    /*public*/  Sequence::Sequence(QString sys, QString user,
            QList<QMap<QString, QString>>* expressionSystemNames,
            QList<QMap<QString, QString>>* actionSystemNames, QObject* parent)
        : AbstractDigitalAction(sys, user, parent)
            /*throws BadUserNameException, BadSystemNameException*/ {
        //super(sys, user);
        _startExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("SequenceSocketStart"));
        _stopExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("SequenceSocketStop"));
        _resetExpressionSocket = ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                ->createFemaleSocket(this, this, tr("SequenceSocketReset"));
        setExpressionSystemNames(expressionSystemNames);
        setActionSystemNames(actionSystemNames);
    }

    /*public*/  QString Sequence::getNewActionSocketName() {
        QVector<QString> names = QVector<QString>(getChildCount());
        for (int i=0; i < getChildCount(); i++) {
            names[i] = getChild(i)->getName();
        }
        return getNewSocketName(names);
    }

    /*public*/  QString Sequence::getNewExpressionSocketName() {
        QVector<QString> names = QVector<QString>(getChildCount());
        for (int i=0; i < getChildCount(); i++) {
            names[i] = getChild(i)->getName();
        }
        return AbstractDigitalExpression::getNewSocketName(names);
    }

    //@Override
    /*public*/  Base* Sequence::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
//        if (1==1) throw new RuntimeException("Not implemented yet");
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
        QString userName = userNames->value(AbstractNamedBean::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        Sequence* copy = new Sequence(sysName, userName);
        copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
        copy->setStartImmediately(_startImmediately);
        copy->setRunContinuously(_runContinuously);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /*private*/ void Sequence::setExpressionSystemNames(QList<QMap<QString, QString>>* systemNames) {
        if (!_expressionEntries.isEmpty()) {
            throw new RuntimeException("expression system names cannot be set more than once");
        }

        for (QMap<QString, QString> entry : *systemNames) {
         QMapIterator<QString, QString> iter(entry);
         while(iter.hasNext())
         {
          iter.next();
            FemaleDigitalExpressionSocket* socket =
                    ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                            ->createFemaleSocket(this, this, iter.key());

            _expressionEntries.append( ExpressionEntry(socket, iter.value()));
         }
        }
    }

    /*private*/ void Sequence::setActionSystemNames(QList<QMap<QString, QString>>* systemNames) {
        if (!_actionEntries.isEmpty()) {
            throw new RuntimeException("action system names cannot be set more than once");
        }

        for (QMap<QString, QString> entry : *systemNames) {
        QMapIterator<QString, QString> iter(entry);
          while(iter.hasNext()){
           iter.next();
            FemaleDigitalActionSocket* socket = ((DefaultDigitalActionManager*)
                    InstanceManager::getDefault("DigitalActionManager"))
                            ->createFemaleSocket(this, this, iter.key());

            _actionEntries.append( ActionEntry(socket, iter.value()));
          }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category Sequence::getCategory() {
        return Category::COMMON;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Sequence::execute() /*throws JmriException*/ {
        if (_stopExpressionSocket->isConnected()
                && _stopExpressionSocket->evaluate()) {
            _isRunning = false;
//            System.out.format("Stop: _currentStep: %d%n", _currentStep);
            return;
        }

        if (_startExpressionSocket->isConnected()
                && _startExpressionSocket->evaluate()) {
            _isRunning = true;
//            System.out.format("Start: _currentStep: %d%n", _currentStep);
        }

        if (_resetExpressionSocket->isConnected()
                && _resetExpressionSocket->evaluate()) {
            _currentStep = -1;
//            System.out.format("Reset: _currentStep: %d%n", _currentStep);
        }

        if (!_isRunning) return;

        if (_currentStep == -1) {
            _currentStep = 0;
//            System.out.format("_currentStep: %d, size: %d%n", _currentStep, _actionEntries.size());
            FemaleDigitalActionSocket* socket =
                    _actionEntries.at(_currentStep)._socket;
            if (socket->isConnected()) socket->execute();
        }

        FemaleDigitalExpressionSocket* exprSocket =
                _expressionEntries.at(_currentStep)._socket;
        if (exprSocket->isConnected() && exprSocket->evaluate()) {
            _currentStep++;
//            System.out.format("_currentStep: %d, size: %d%n", _currentStep, _actionEntries.size());
            if (_currentStep >= _actionEntries.size()) {
                _currentStep = 0;
//                System.out.format("_currentStep set to 0: %d%n", _currentStep);
            }

            FemaleDigitalActionSocket* actionSocket =
                    _actionEntries.at(_currentStep)._socket;
            if (exprSocket->isConnected()) actionSocket->execute();
        }
    }

    /**
     * Get if to start immediately
     * @return true if to start immediately
     */
    /*public*/  bool Sequence::getStartImmediately() {
        return _startImmediately;
    }

    /**
     * Set if to start immediately
     * @param startImmediately true if to start immediately
     */
    /*public*/  void Sequence::setStartImmediately(bool startImmediately) {
        _startImmediately = startImmediately;
        if (_startImmediately) _isRunning = true;
    }

    /**
     * Get if run continuously
     * @return true if run continuously
     */
    /*public*/  bool Sequence::getRunContinuously() {
        return _runContinuously;
    }

    /**
     * Set if run continuously
     * @param runContinuously true if run continuously
     */
    /*public*/  void Sequence::setRunContinuously(bool runContinuously) {
        _runContinuously = runContinuously;
    }

    //@Override
    /*public*/  FemaleSocket* Sequence::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        if (index == EXPRESSION_START) return _startExpressionSocket;
        if (index == EXPRESSION_STOP) return _stopExpressionSocket;
        if (index == EXPRESSION_RESET) return _resetExpressionSocket;

        index -= NUM_STATIC_EXPRESSIONS;
        if ((index % 2) == 0) return _actionEntries.at(index >> 1)._socket;
        else return _expressionEntries.at(index >> 1)._socket;
    }

    //@Override
    /*public*/  int Sequence::getChildCount() {
        return NUM_STATIC_EXPRESSIONS + _expressionEntries.size() + _actionEntries.size();
    }
/*
    private void Sequence::checkFreeSocket() {
        bool hasFreeSocket = false;

        for (ActionEntry entry : _actionEntries) {
            hasFreeSocket |= !entry._socket.isConnected();
        }
        for (ExpressionEntry entry : _expressionEntries) {
            hasFreeSocket |= !entry._socket.isConnected();
        }
        if (!hasFreeSocket) {
            FemaleDigitalActionSocket actionSocket =
                    InstanceManager.getDefault(DigitalActionManager.class)
                            .createFemaleSocket(this, this, getNewActionSocketName());
            _actionEntries.add(new ActionEntry(actionSocket));

            FemaleDigitalExpressionSocket exprSocket =
                    ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                            .createFemaleSocket(this, this, getNewExpressionSocketName());
            _expressionEntries.add(new ExpressionEntry(exprSocket));

            List<FemaleSocket> list = new ArrayList<>();
            list.add(actionSocket);
            list.add(exprSocket);
            firePropertyChange(Base.PROPERTY_CHILD_COUNT, null, list);
        }
    }
*/
    /** {@inheritDoc} */
    //@Override
    /*public*/  bool Sequence::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
        index -= NUM_STATIC_EXPRESSIONS;

        switch (oper) {
            case FemaleSocketOperation::Remove:
                // Possible if not the three static sockets,
                // the socket is not connected and the next socket is not connected
                return (index >= 0)
                        && (index+1 < getChildCount())
                        && !getChild(index)->isConnected()
                        && !getChild(index+1)->isConnected();
            case FemaleSocketOperation::InsertBefore:
                // Possible if not the three static sockets
                return index >= 0;
            case FemaleSocketOperation::InsertAfter:
                // Possible if not the static sockets, except the last one
                return index >= -1;
            case FemaleSocketOperation::MoveUp:
                return index >= 2;   // Possible if not the three static sockets and the first two sockets after that
            case FemaleSocketOperation::MoveDown:
                // Possible if not the static sockets and if not last three sockets
                return (index >= 0) && (index < getChildCount());
            default:
                throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
        }
    }

    /*private*/ void Sequence::insertNewSocket(int index) {
        int actionIndex = index >> 1;
        int expressionIndex = index >> 1;

        // Does index points to an expression socket instead of an action socket?
        if ((index % 2) != 0) {
            expressionIndex = index >> 1;
            actionIndex = (index >> 1) + 1;
        }

        FemaleDigitalActionSocket* actionSocket = ((DefaultDigitalActionManager*)
                InstanceManager::getDefault("DigitalActionManager"))
                        ->createFemaleSocket(this, this, getNewActionSocketName());
        _actionEntries.insert(actionIndex,  ActionEntry(actionSocket));

        FemaleDigitalExpressionSocket* exprSocket =
                ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewExpressionSocketName());
        _expressionEntries.insert(expressionIndex, ExpressionEntry(exprSocket));

        QList<FemaleSocket*>* addList = new QList<FemaleSocket*>();
        addList->append(actionSocket);
        addList->append(exprSocket);
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), VPtr<QList<FemaleSocket*>>::asQVariant(addList));
    }

    /*private*/ void Sequence::removeSocket(int index) {
        int actionIndex = index >> 1;
        int expressionIndex = index-NUM_STATIC_EXPRESSIONS >> 1;

        QList<FemaleSocket*> removeList = QList<FemaleSocket*>();
        removeList.append(_actionEntries.at(actionIndex)._socket);
        _actionEntries.removeAt(actionIndex);
        removeList.append(_expressionEntries.at(expressionIndex)._socket);
        _expressionEntries.removeAt(expressionIndex);
        QVariantList vList;
        foreach(FemaleSocket* s, removeList) vList.append(VPtr<FemaleSocket>::asQVariant(s));

        firePropertyChange(Base::PROPERTY_CHILD_COUNT, vList, QVariant());
    }

    /*private*/ void Sequence::moveSocketDown(int index) {
        int actionIndex = index >> 1;
        int expressionIndex = index >> 1;

        // Does index points to an expression socket instead of an action socket?
        if ((index % 2) != 0) {
            expressionIndex = index >> 1;
            actionIndex = (index >> 1) + 1;
        }

        ActionEntry actionTemp = _actionEntries.at(actionIndex);
        _actionEntries.replace(actionIndex, _actionEntries.at(actionIndex+1));
        _actionEntries.replace(actionIndex+1, actionTemp);

        ExpressionEntry exprTemp = _expressionEntries.at(expressionIndex);
        _expressionEntries.replace(expressionIndex, _expressionEntries.at(expressionIndex+1));
        _expressionEntries.replace(expressionIndex+1, exprTemp);

        QList<FemaleSocket*> list = QList<FemaleSocket*>();
        list.append(_actionEntries.at(actionIndex)._socket);
        list.append(_actionEntries.at(actionIndex+1)._socket);
        list.append(_expressionEntries.at(expressionIndex)._socket);
        list.append(_expressionEntries.at(expressionIndex+1)._socket);
        QVariantList vList;
        foreach(FemaleSocket* s, list) vList.append(VPtr<FemaleSocket>::asQVariant(s));
        firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), vList);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Sequence::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
        index -= NUM_STATIC_EXPRESSIONS;

        switch (oper) {
            case FemaleSocketOperation::Remove:
                if (index+1 >= getChildCount()) throw new UnsupportedOperationException("Cannot remove only the last socket");
                if (getChild(index)->isConnected()) throw new UnsupportedOperationException("Socket is connected");
                if (getChild(index+1)->isConnected()) throw new UnsupportedOperationException("Socket below is connected");
                removeSocket(index);
                break;
            case FemaleSocketOperation::InsertBefore:
                insertNewSocket(index);
                break;
            case FemaleSocketOperation::InsertAfter:
                insertNewSocket(index+1);
                break;
            case FemaleSocketOperation::MoveUp:
                if (index < 0) throw new UnsupportedOperationException("cannot move up static sockets");
                if (index <= 1) throw new UnsupportedOperationException("cannot move up first two children");
                moveSocketDown(index-2);
                break;
            case FemaleSocketOperation::MoveDown:
                if (index+2 >= getChildCount()) throw new UnsupportedOperationException("cannot move down last two children");
                moveSocketDown(index);
                break;
            default:
                throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
        }
    }

    //@Override
    /*public*/  void Sequence::connected(FemaleSocket* socket) {
        if (disableCheckForUnconnectedSocket) return;

        if (socket == _startExpressionSocket) {
            _startExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _stopExpressionSocket) {
            _stopExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else if (socket == _resetExpressionSocket) {
            _resetExpressionSocketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            for (ExpressionEntry entry : _expressionEntries) {
                if (socket == entry._socket) {
                    entry._socketSystemName =
                            socket->getConnectedSocket()->getSystemName();
                }
            }
            for (ActionEntry entry : _actionEntries) {
                if (socket == entry._socket) {
                    entry._socketSystemName =
                            socket->getConnectedSocket()->getSystemName();
                }
            }
        }

//        checkFreeSocket();
    }

    //@Override
    /*public*/  void Sequence::disconnected(FemaleSocket* socket) {
        if (socket == _startExpressionSocket) {
            _startExpressionSocketSystemName = nullptr;
        } else if (socket == _stopExpressionSocket) {
            _stopExpressionSocketSystemName = nullptr;
        } else if (socket == _resetExpressionSocket) {
            _resetExpressionSocketSystemName = nullptr;
        } else {
            for (ExpressionEntry entry : _expressionEntries) {
                if (socket == entry._socket) {
                    entry._socketSystemName = nullptr;
                }
            }
            for (ActionEntry entry : _actionEntries) {
                if (socket == entry._socket) {
                    entry._socketSystemName = nullptr;
                }
            }
        }
    }

    //@Override
    /*public*/  QString Sequence::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Sequence");
    }

    //@Override
    /*public*/  QString Sequence::getLongDescription(QLocale locale) {
        return tr(/*locale,*/ "Sequence");
    }

    /*public*/  FemaleDigitalExpressionSocket* Sequence::getStartExpressionSocket() {
        return _startExpressionSocket;
    }

    /*public*/  QString Sequence::getStartExpressionSocketSystemName() {
        return _startExpressionSocketSystemName;
    }

    /*public*/  void Sequence::setStartExpressionSocketSystemName(QString systemName) {
        _startExpressionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalExpressionSocket* Sequence::getStopExpressionSocket() {
        return _stopExpressionSocket;
    }

    /*public*/  QString Sequence::getStopExpressionSocketSystemName() {
        return _stopExpressionSocketSystemName;
    }

    /*public*/  void Sequence::setStopExpressionSocketSystemName(QString systemName) {
        _stopExpressionSocketSystemName = systemName;
    }

    /*public*/  FemaleDigitalExpressionSocket* Sequence::getResetExpressionSocket() {
        return _resetExpressionSocket;
    }

    /*public*/  QString Sequence::getResetExpressionSocketSystemName() {
        return _resetExpressionSocketSystemName;
    }

    /*public*/  void Sequence::setResetExpressionSocketSystemName(QString systemName) {
        _resetExpressionSocketSystemName = systemName;
    }

    /*public*/  int Sequence::getNumExpressions() {
        return _expressionEntries.size();
    }

    /*public*/  FemaleDigitalExpressionSocket* Sequence::getExpressionSocket(int socket) {
        return _expressionEntries.at(socket)._socket;
    }

    /*public*/  QString Sequence::getExpressionSocketSystemName(int socket) {
        return _expressionEntries.at(socket)._socketSystemName;
    }

    /*public*/  void Sequence::setExpressionSocketSystemName(int socket, QString systemName) {
        //_expressionEntries.get(socket)._socketSystemName = systemName;
     ExpressionEntry e = _expressionEntries.at(socket);
     e._socketSystemName = systemName;
     _expressionEntries.replace(socket, e);
    }

    /*public*/  int Sequence::getNumActions() {
        return _actionEntries.size();
    }
/*
    public  void setNumActions(int num) {
        List<FemaleSocket> addList = new ArrayList<>();
        List<FemaleSocket> removeList = new ArrayList<>();

        // Is there too many children?
        while (_actionEntries.size() > num) {
            ActionEntry ae = _actionEntries.get(num);
            if (ae._socket.isConnected()) {
                throw new IllegalArgumentException("Cannot remove sockets that are connected");
            }
            removeList.add(_actionEntries.get(_actionEntries.size()-1)._socket);
            _actionEntries.remove(_actionEntries.size()-1);
        }

        // Is there not enough children?
        while (_actionEntries.size() < num) {
            FemaleDigitalActionSocket socket =
                    InstanceManager.getDefault(DigitalActionManager.class)
                            .createFemaleSocket(this, this, getNewSocketName());
            _actionEntries.add(new ActionEntry(socket));
            addList.add(socket);
        }
        firePropertyChange(Base.PROPERTY_CHILD_COUNT, removeList, addList);
    }
*/
    /*public*/  FemaleDigitalActionSocket* Sequence::getActionSocket(int socket) {
        return _actionEntries.at(socket)._socket;
    }

    /*public*/  QString Sequence::getActionSocketSystemName(int socket) {
        return _actionEntries.at(socket)._socketSystemName;
    }

    /*public*/  void Sequence::setActionSocketSystemName(int socket, QString systemName) {
        //_actionEntries.value(socket)._socketSystemName = systemName;
        ActionEntry a= _actionEntries.at(socket);
        a._socketSystemName = systemName;
        _actionEntries.replace(socket, a);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Sequence::setup() {
        // We don't want to check for unconnected sockets while setup sockets
        disableCheckForUnconnectedSocket = true;

        try {
            if ( !_startExpressionSocket->isConnected()
                    || _startExpressionSocket->getConnectedSocket()->getSystemName()
                             != (_startExpressionSocketSystemName)) {

                QString socketSystemName = _startExpressionSocketSystemName;
                _startExpressionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)
                            ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
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
                    MaleSocket* maleSocket = (MaleSocket*)
                            ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
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

            if ( !_resetExpressionSocket->isConnected()
                    || _resetExpressionSocket->getConnectedSocket()->getSystemName()
                            != (_resetExpressionSocketSystemName)) {

                QString socketSystemName = _resetExpressionSocketSystemName;
                _resetExpressionSocket->_disconnect();
                if (socketSystemName != "") {
                    MaleSocket* maleSocket = (MaleSocket*)
                            ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName)->self();
                    _resetExpressionSocket->_disconnect();
                    if (maleSocket != nullptr) {
                        _resetExpressionSocket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
                    }
                }
            } else {
                _resetExpressionSocket->getConnectedSocket()->setup();
            }

            for (ExpressionEntry ee : _expressionEntries) {
                if ( !ee._socket->isConnected()
                        || ee._socket->getConnectedSocket()->getSystemName()
                                != (ee._socketSystemName)) {

                    QString socketSystemName = ee._socketSystemName;
                    ee._socket->_disconnect();
                    if (socketSystemName != "") {
                        MaleSocket* maleSocket = (MaleSocket*)
                                ((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                                        ->getBySystemName(socketSystemName)->self();
                        ee._socket->_disconnect();
                        if (maleSocket != nullptr) {
                            ee._socket->_connect(maleSocket);
                            maleSocket->setup();
                        } else {
                            log->error("cannot load digital expression " + socketSystemName);
                        }
                    }
                } else {
                    ee._socket->getConnectedSocket()->setup();
                }
            }

            for (ActionEntry ae : _actionEntries) {
                if ( !ae._socket->isConnected()
                        || ae._socket->getConnectedSocket()->getSystemName()
                                != (ae._socketSystemName)) {

                    QString socketSystemName = ae._socketSystemName;
                    ae._socket->_disconnect();
                    if (socketSystemName != "") {
                        MaleSocket* maleSocket = (MaleSocket*)((DefaultDigitalActionManager*)
                                InstanceManager::getDefault("DigitalActionManager"))
                                        ->getBySystemName(socketSystemName)->self();
                        ae._socket->_disconnect();
                        if (maleSocket != nullptr) {
                            ae._socket->_connect(maleSocket);
                            maleSocket->setup();
                        } else {
                            log->error("cannot load digital action " + socketSystemName);
                        }
                    }
                } else {
                    ae._socket->getConnectedSocket()->setup();
                }
            }
        } catch (SocketAlreadyConnectedException* ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }

        disableCheckForUnconnectedSocket = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Sequence::registerListenersForThisClass() {
        if (!_listenersAreRegistered) {
            _listenersAreRegistered = true;
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Sequence::unregisterListenersForThisClass() {
        _listenersAreRegistered = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void Sequence::disposeMe() {
    }

    #if 0
    /*private*/ static class ExpressionEntry {
        /*private*/ String _socketSystemName;
        /*private*/ final FemaleDigitalExpressionSocket _socket;

        /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket socket, String socketSystemName) {
            _socketSystemName = socketSystemName;
            _socket = socket;
        }

        /*private*/ ExpressionEntry(FemaleDigitalExpressionSocket socket) {
            this._socket = socket;
        }

    }

    /*private*/ static class ActionEntry {
        /*private*/ String _socketSystemName;
        /*private*/ final FemaleDigitalActionSocket _socket;

        /*private*/ ActionEntry(FemaleDigitalActionSocket socket, String socketSystemName) {
            _socketSystemName = socketSystemName;
            _socket = socket;
        }

        /*private*/ ActionEntry(FemaleDigitalActionSocket socket) {
            this._socket = socket;
        }

    }
    #endif

    /*private*/ /*final*/ /*static*/ Logger* Sequence::log = LoggerFactory::getLogger("Sequence");
