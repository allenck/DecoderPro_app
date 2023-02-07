#include "digitalformula.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "defaultfemalegenericexpressionsocket.h"
#include "recursivedescentparser.h"
#include "genericexpressionvariable.h"
#include "parserexception.h"
#include "typeconversionutil.h"
#include "defaultconditionalng.h"
#include "vptr.h"
#include "defaultlogixngmanager.h"

/**
 * Evaluates to True if the formula evaluates to true
 *
 * @author Daniel Bergqvist Copyright 2019
 */
///*public*/  class DigitalFormula extends AbstractDigitalExpression implements FemaleSocketListener {


/**
 * Create a new instance of Formula with system name and user name.
 * @param sys the system name
 * @param user the user name
 */
/*public*/  DigitalFormula::DigitalFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, QObject* parent)
  : AbstractDigitalExpression(sys, user, parent)
{
    //super(sys, user);
    setObjectName("DigitalFormula");
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
/*public*/  DigitalFormula::DigitalFormula(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
        QList<SocketData*> expressionSystemNames, QObject* parent): AbstractDigitalExpression(sys, user, parent) {
    //super(sys, user);
 setObjectName("DigitalFormula");
    setExpressionSystemNames(expressionSystemNames);
}

//@Override
/*public*/  Base* DigitalFormula::getDeepCopy(QMap<QString, QString> *systemNames, QMap<QString, QString> *userNames) /*throws JmriException*/ {
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames->value(AbstractNamedBean::getSystemName());
    QString userName = userNames->value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
    DigitalFormula* copy = new DigitalFormula(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    copy->setNumSockets(getChildCount());
    copy->setFormula(_formula);
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*private*/ void DigitalFormula::setExpressionSystemNames(QList<SocketData*> systemNames) {
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

/*public*/  QString DigitalFormula::getExpressionSystemName(int index) {
    return _expressionEntries.at(index)->_socketSystemName;
}

/*public*/  QString DigitalFormula::getExpressionManager(int index) {
    return _expressionEntries.at(index)->_manager;
}

/*private*/ FemaleGenericExpressionSocket* DigitalFormula::createFemaleSocket(
        Base* parent, FemaleSocketListener* listener, QString socketName) {

    return new DefaultFemaleGenericExpressionSocket(
            FemaleGenericExpressionSocket::SocketType::GENERIC, parent, listener, socketName);
}

/*public*/  /*final*/ void DigitalFormula::setFormula(QString formula) /*throws ParserException */{
    QMap<QString, Variable*> variables = QMap<QString, Variable*>();
    RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
    for (int i=0; i < getChildCount(); i++) {
        FemaleSocket* fs = getChild(i);
        Variable* v = new GenericExpressionVariable((DefaultFemaleGenericExpressionSocket*)getChild(i)->bself());
        variables.insert(v->getName(), v);
    }
    _expressionNode = parser->parseExpression(formula);
    // parseExpression() may throw an exception and we don't want to set
    // the field _formula until we now parseExpression() has succeeded.
    _formula = formula;
}

/*public*/  QString DigitalFormula::getFormula() {
    return _formula;
}

/*private*/ void DigitalFormula::parseFormula() {
    try {
        setFormula(_formula);
    } catch (ParserException* e) {
        log->error("Unexpected exception when parsing the formula", e);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  Category DigitalFormula::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DigitalFormula::evaluate() /*throws JmriException*/ {

    if (_formula.isEmpty()) {
        return false;
    }

    return TypeConversionUtil::convertToBoolean(_expressionNode->calculate(
            getConditionalNG()->getSymbolTable()), false);
}

//@Override
/*public*/  FemaleSocket* DigitalFormula::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
    return _expressionEntries.at(index)->_socket;
}

//@Override
/*public*/  int DigitalFormula::getChildCount() {
    return _expressionEntries.size();
}

/*public*/  void DigitalFormula::setChildCount(int count) {
    QVariantList addList = QVariantList();
    QVariantList removeList = QVariantList();

    // Is there too many children?
    while (_expressionEntries.size() > count) {
        int childNo = _expressionEntries.size()-1;
        FemaleSocket* socket = _expressionEntries.at(childNo)->_socket;
        if (socket->isConnected()) {
            socket->_disconnect();
        }
        removeList.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(childNo)->_socket));
        _expressionEntries.removeAt(childNo);
    }

    // Is there not enough children?
    while (_expressionEntries.size() < count) {
        FemaleGenericExpressionSocket* socket =
                createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    parseFormula();
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, addList);
}

//@Override
/*public*/  QString DigitalFormula::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Digital Formula");
}

//@Override
/*public*/  QString DigitalFormula::getLongDescription(QLocale locale) {
    if (_formula.isEmpty()) {
        return tr(/*locale,*/ "Digital Formula: empty");
    } else {
        return tr(/*locale, */"Digital Formula: %1").arg(_formula);
    }
}

// This method ensures that we have enough of children
/*private*/ void DigitalFormula::setNumSockets(int num) {
    QVariantList addList = QVariantList();

    // Is there not enough children?
    while (_expressionEntries.size() < num) {
        FemaleGenericExpressionSocket* socket =
                createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    parseFormula();
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void DigitalFormula::checkFreeSocket() {
    bool hasFreeSocket = false;

    for (ExpressionEntry* entry : _expressionEntries) {
        hasFreeSocket |= !entry->_socket->isConnected();
    }
    if (!hasFreeSocket) {
        FemaleGenericExpressionSocket* socket =
                createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));

        QVariantList list = QVariantList();
        list.append(VPtr<FemaleSocket>::asQVariant(socket));
        parseFormula();
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), list);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  bool DigitalFormula::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
    switch (oper) {
        case FemaleSocketOperation::Remove:        // Possible if socket is not connected
            return ! getChild(index)->isConnected();
        case FemaleSocketOperation::InsertBefore:
            return true;    // Always possible
        case FemaleSocketOperation::InsertAfter:
            return true;    // Always possible
        case FemaleSocketOperation::FemaleSocketOperation::MoveUp:
            return index > 0;   // Possible if not first socket
        case FemaleSocketOperation::MoveDown:
            return index+1 < getChildCount();   // Possible if not last socket
        default:
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
    }
}

/*private*/ void DigitalFormula::insertNewSocket(int index) {
    FemaleGenericExpressionSocket* socket =
            createFemaleSocket(this, this, getNewSocketName());
    _expressionEntries.insert(index, new ExpressionEntry(socket));

    QVariantList addList = QVariantList();
    addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    parseFormula();
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void DigitalFormula::removeSocket(int index) {
    QVariantList removeList = QVariantList();
    removeList.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    _expressionEntries.removeAt(index);
    parseFormula();
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, QVariant());
}

/*private*/ void DigitalFormula::moveSocketDown(int index) {
    ExpressionEntry* temp = _expressionEntries.at(index);
    _expressionEntries.replace(index, _expressionEntries.at(index+1));
    _expressionEntries.replace(index+1, temp);

    QVariantList list = QVariantList();

//    list.add(_expressionEntries.get(index)._socket);
//    list.add(_expressionEntries.get(index)._socket);
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    parseFormula();
    firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), list);
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalFormula::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
    switch (oper) {
        case FemaleSocketOperation::Remove:
            if (getChild(index)->isConnected()) throw new UnsupportedOperationException("Socket is connected");
            removeSocket(index);
            break;
        case FemaleSocketOperation::InsertBefore:
            insertNewSocket(index);
            break;
        case FemaleSocketOperation::InsertAfter:
            insertNewSocket(index+1);
            break;
        case FemaleSocketOperation::MoveUp:
            if (index == 0) throw new UnsupportedOperationException("cannot move up first child");
            moveSocketDown(index-1);
            break;
        case FemaleSocketOperation::MoveDown:
            if (index+1 == getChildCount()) throw new UnsupportedOperationException("cannot move down last child");
            moveSocketDown(index);
            break;
        default:
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
    }
}

//@Override
/*public*/  void DigitalFormula::connected(FemaleSocket* socket) {
    if (_disableCheckForUnconnectedSocket) return;

    for (ExpressionEntry* entry : _expressionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName =
                    socket->getConnectedSocket()->getSystemName();
        }
    }

    checkFreeSocket();
}

//@Override
/*public*/  void DigitalFormula::disconnected(FemaleSocket* socket) {
    for (ExpressionEntry* entry : _expressionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName = "";
            break;
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalFormula::socketNameChanged(FemaleSocket* socket) {
    parseFormula();
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalFormula::setup() {
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
                if (socketSystemName != "") {
                    Manager/*<? extends MaleSocket>*/* m =
                            ((DefaultLogixNGManager*)InstanceManager::getDefault("LogixNG_Manager"))
                                    ->getManager(manager);
                    MaleSocket* maleSocket =(MaleSocket*) m->getBySystemName(socketSystemName);
                    if (maleSocket != nullptr) {
                        ee->_socket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital expression " + socketSystemName);
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
/*public*/  void DigitalFormula::registerListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalFormula::unregisterListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void DigitalFormula::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* DigitalFormula::log = LoggerFactory::getLogger("DigitalFormula");