#include "analogformula.h"
#include "loggerfactory.h"
#include "femalegenericexpressionsocket.h"
#include "analogexpressionmanager.h"
#include "runtimeexception.h"
#include "instancemanager.h"
#include "recursivedescentparser.h"
#include "femalegenericexpressionsocket.h"
#include "defaultfemalegenericexpressionsocket.h"
#include "parserexception.h"
#include "typeconversionutil.h"
#include "logixng_manager.h"
#include "genericexpressionvariable.h"
#include "conditionalng.h"

/**
 * Evaluates to True if the formula evaluates to true
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class AnalogFormula extends AbstractAnalogExpression implements FemaleSocketListener {


    /**
     * Create a new instance of Formula with system name and user name.
     * @param sys the system name
     * @param user the user name
     */
    /*public*/  AnalogFormula::AnalogFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, QObject* parent)
     : AbstractAnalogExpression(sys, user, parent)
    {
        //super(sys, user);
        _expressionEntries
                .append(new ExpressionEntry(createFemaleSocket(this, this, getNewSocketName())));
    }
    /**
     * Create a new instance of Formula with system name and user name.
     * @param sys the system name
     * @param user the user name
     * @param expressionSystemNames a list of system names for the expressions
     * this formula uses
     */
    /*public*/  AnalogFormula::AnalogFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
            QList<AnalogFormula::SocketData*> expressionSystemNames, QObject* parent) : AbstractAnalogExpression(sys, user, parent){
        //super(sys, user);
        setExpressionSystemNames(expressionSystemNames);
    }

    //@Override
    /*public*/  Base* AnalogFormula::getDeepCopy(QMap<QString, QString> systemNames, QMap<QString, QString> userNames) /*throws JmriException*/ {
        AnalogExpressionManager* manager = (AnalogExpressionManager*)InstanceManager::getDefault("AnalogExpressionManager");
        QString sysName = systemNames.value(AbstractBase::getSystemName());
        QString userName = userNames.value(AbstractBase::getSystemName());
        if (sysName == "") sysName = manager->getAutoSystemName();
        AnalogFormula* copy = new AnalogFormula(sysName, userName);
        copy->AbstractBase::setComment(AbstractBase::getComment());
        copy->setNumSockets(getChildCount());
        copy->setFormula(_formula);
        return manager->registerExpression(copy)->MaleAnalogExpressionSocket::deepCopyChildren(this, systemNames, userNames);
    }

    /*private*/ void AnalogFormula::setExpressionSystemNames(QList<SocketData*> systemNames) {
        if (!_expressionEntries.isEmpty()) {
            throw new RuntimeException("expression system names cannot be set more than once");
        }

        for (SocketData* socketData : systemNames) {
            FemaleGenericExpressionSocket* socket =
                    createFemaleSocket(this, this, socketData->_socketName);
//            FemaleGenericExpressionSocket socket =
//                    InstanceManager.getDefault(AnalogExpressionManager.class)
//                            .createFemaleSocket(this, this, entry.getKey());

            _expressionEntries.append(new ExpressionEntry(socket, socketData->_socketSystemName, socketData->_manager));
        }
    }

    /*public*/  QString AnalogFormula::getExpressionSystemName(int index) {
        return _expressionEntries.value(index)->_socketSystemName;
    }

    /*public*/  QString AnalogFormula::getExpressionManager(int index) {
        return _expressionEntries.value(index)->_manager;
    }

    /*private*/ FemaleGenericExpressionSocket* AnalogFormula::createFemaleSocket(
            Base* parent, FemaleSocketListener* listener, QString socketName) {

        return new DefaultFemaleGenericExpressionSocket(
                FemaleGenericExpressionSocket::SocketType::GENERIC, parent, listener, socketName);
    }

    /*public*/  /*final*/ void AnalogFormula::setFormula(QString formula) /*throws ParserException*/ {
        QMap<QString, Variable*> variables = QMap<QString, Variable*>();
        RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
        for (int i=0; i < getChildCount(); i++) {
            Variable* v = new GenericExpressionVariable((FemaleGenericExpressionSocket*)getChild(i));
            variables.insert(v->getName(), v);
        }
        _expressionNode = parser->parseExpression(formula);
        // parseExpression() may throw an exception and we don't want to set
        // the field _formula until we now parseExpression() has succeeded.
        _formula = formula;
    }

    /*public*/  QString AnalogFormula::getFormula() {
        return _formula;
    }

    /*private*/ void AnalogFormula::parseFormula() {
        try {
            setFormula(_formula);
        } catch (ParserException* e) {
            log->error("Unexpected exception when parsing the formula", e);
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category::TYPE AnalogFormula::getCategory() {
        return Category::TYPE::COMMON;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  double AnalogFormula::evaluate() /*throws JmriException*/ {

        if (_formula.isEmpty()) {
            return 0.0;
        }

        return TypeConversionUtil::convertToDouble(_expressionNode->calculate(
                AbstractBase::getConditionalNG()->getSymbolTable()), false);
    }

    //@Override
    /*public*/  FemaleSocket* AnalogFormula::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        return _expressionEntries.at(index)->_socket;
    }

    //@Override
    /*public*/  int AnalogFormula::getChildCount() {
        return _expressionEntries.size();
    }

    /*public*/  void AnalogFormula::setChildCount(int count) {
        QList<FemaleSocket*> addList = QList<FemaleSocket*>();
        QList<FemaleSocket*> removeList = QList<FemaleSocket*>();

        // Is there too many children?
        while (_expressionEntries.size() > count) {
            int childNo = _expressionEntries.size()-1;
            FemaleSocket* socket = _expressionEntries.at(childNo)->_socket;
            if (socket->isConnected()) {
                socket->_disconnect();
            }
            removeList.append(_expressionEntries.at(childNo)->_socket);
            _expressionEntries.removeAt(childNo);
        }

        // Is there not enough children?
        while (_expressionEntries.size() < count) {
            FemaleGenericExpressionSocket* socket =
                    createFemaleSocket(this, this, getNewSocketName());
            _expressionEntries.append(new ExpressionEntry(socket));
            addList.append(socket);
        }
        parseFormula();
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant::fromValue(removeList), QVariant::fromValue(addList));
    }

    //@Override
    /*public*/  QString AnalogFormula::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Analog Formula");
    }

    //@Override
    /*public*/  QString AnalogFormula::getLongDescription(QLocale locale) {
        if (_formula.isEmpty()) {
            return tr(/*locale,*/ "Analog Formula: empty");
        } else {
            return tr(/*locale,*/ "Analog Formula: %1").arg(_formula);
        }
    }

    // This method ensures that we have enough of children
    /*private*/ void AnalogFormula::setNumSockets(int num) {
        QList<FemaleSocket*> addList = QList<FemaleSocket*>();

        // Is there not enough children?
        while (_expressionEntries.size() < num) {
            FemaleGenericExpressionSocket* socket =
                    createFemaleSocket(this, this, getNewSocketName());
            _expressionEntries.append(new ExpressionEntry(socket));
            addList.append(socket);
        }
        parseFormula();
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), QVariant::fromValue(addList));
    }

    /*private*/ void AnalogFormula::checkFreeSocket() {
        bool hasFreeSocket = false;

        for (ExpressionEntry* entry : _expressionEntries) {
            hasFreeSocket |= !entry->_socket->isConnected();
        }
        if (!hasFreeSocket) {
            FemaleGenericExpressionSocket* socket =
                    createFemaleSocket(this, this, getNewSocketName());
            _expressionEntries.append(new ExpressionEntry(socket));

            QList<FemaleSocket*> list = QList<FemaleSocket*>();
            list.append(socket);
            parseFormula();
            firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), QVariant::fromValue(list));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  bool AnalogFormula::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
        switch (oper) {
            case FemaleSocketOperation::TYPES::Remove:        // Possible if socket is not connected
                return ! getChild(index)->isConnected();
            case FemaleSocketOperation::TYPES::InsertBefore:
                return true;    // Always possible
            case FemaleSocketOperation::TYPES::InsertAfter:
                return true;    // Always possible
            case FemaleSocketOperation::TYPES::MoveUp:
                return index > 0;   // Possible if not first socket
            case FemaleSocketOperation::TYPES::MoveDown:
                return index+1 < getChildCount();   // Possible if not last socket
            default:
                throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
        }
    }

    /*private*/ void AnalogFormula::insertNewSocket(int index) {
        FemaleGenericExpressionSocket* socket =
                createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.insert(index, new ExpressionEntry(socket));

        QList<FemaleSocket*> addList = QList<FemaleSocket*>();
        addList.append(socket);
        parseFormula();
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), QVariant::fromValue(addList));
    }

    /*private*/ void AnalogFormula::removeSocket(int index) {
        QList<FemaleSocket*> removeList = QList<FemaleSocket*>();
        //removeList.add(_expressionEntries.remove(index)._socket);
        ExpressionEntry* s = _expressionEntries.at(index);
        removeList.append(s->_socket);
        parseFormula();
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant::fromValue(removeList), QVariant());
    }

    /*private*/ void AnalogFormula::moveSocketDown(int index) {
        ExpressionEntry* temp = _expressionEntries.at(index);
        _expressionEntries.replace(index, _expressionEntries.at(index+1));
        _expressionEntries.replace(index+1, temp);

        QList<FemaleSocket*> list = QList<FemaleSocket*>();
        list.append(_expressionEntries.at(index)->_socket);
        list.append(_expressionEntries.at(index)->_socket);
        parseFormula();
        firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), QVariant::fromValue(list));
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogFormula::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
        switch (oper) {
            case FemaleSocketOperation::TYPES::Remove:
                if (getChild(index)->isConnected()) throw new UnsupportedOperationException("Socket is connected");
                removeSocket(index);
                break;
            case FemaleSocketOperation::TYPES::InsertBefore:
                insertNewSocket(index);
                break;
            case FemaleSocketOperation::TYPES::InsertAfter:
                insertNewSocket(index+1);
                break;
            case FemaleSocketOperation::TYPES::MoveUp:
                if (index == 0) throw new UnsupportedOperationException("cannot move up first child");
                moveSocketDown(index-1);
                break;
            case FemaleSocketOperation::TYPES::MoveDown:
                if (index+1 == getChildCount()) throw new UnsupportedOperationException("cannot move down last child");
                moveSocketDown(index);
                break;
            default:
                throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
        }
    }

    //@Override
    /*public*/  void AnalogFormula::connected(FemaleSocket* socket) {
        if (_disableCheckForUnconnectedSocket) return;

        for (ExpressionEntry* entry : _expressionEntries) {
            if (socket == entry->_socket) {
                entry->_socketSystemName =
                        socket->getConnectedSocket()->getSystemName();
                entry->_manager =
                        socket->getConnectedSocket()->getManager()->self()->metaObject()->className();
            }
        }

        checkFreeSocket();
    }

    //@Override
    /*public*/  void AnalogFormula::disconnected(FemaleSocket* socket) {
        for (ExpressionEntry* entry : _expressionEntries) {
            if (socket == entry->_socket) {
                entry->_socketSystemName = nullptr;
                entry->_manager = nullptr;
                break;
            }
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogFormula::socketNameChanged(FemaleSocket* socket) {
        parseFormula();
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogFormula::setup() {
        // We don't want to check for unconnected sockets while setup sockets
        _disableCheckForUnconnectedSocket = true;

        for (ExpressionEntry* ee : _expressionEntries) {
            try {
                if ( !ee->_socket->isConnected()
                        || ee->_socket->getConnectedSocket()->getSystemName()
                                 != (ee->_socketSystemName)) {

                    QString socketSystemName = ee->_socketSystemName;
                    QString manager = ee->_manager;
                    ee->_socket->_disconnect();
                    if (socketSystemName != nullptr) {
                        Manager/*<? extends MaleSocket>*/* m =
                                ((LogixNG_Manager*)InstanceManager::getDefault("LogixNG_Manager"))
                                        ->getManager(manager);
                        MaleSocket* maleSocket = (MaleSocket*)(MaleRootSocket*)m->getBySystemName(socketSystemName);
                        if (maleSocket != nullptr) {
                            ee->_socket->_connect(maleSocket);
                            maleSocket->setup();
                        } else {
                            log->error("cannot load analog expression " + socketSystemName);
                        }
                    }
                } else {
                    ee->_socket->getConnectedSocket()->setup();
                }
            } catch (SocketAlreadyConnectedException* ex) {
                // This shouldn't happen and is a runtime error if it does.
                throw new RuntimeException("socket is already connected");
            }
        }

        parseFormula();
        checkFreeSocket();

        _disableCheckForUnconnectedSocket = false;
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogFormula::registerListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogFormula::unregisterListenersForThisClass() {
        // Do nothing
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void AnalogFormula::disposeMe() {
    }


    /*private*/ /*final*/ /*static*/ Logger* AnalogFormula::log = LoggerFactory::getLogger("AnalogFormula");
