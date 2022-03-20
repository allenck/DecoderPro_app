#include "antecedent.h"
#include "instancemanager.h"
#include "loggerfactory.h"
#include "defaultdigitalexpressionmanager.h"
#include "vptr.h"

/**
 * Evaluates to True if the antecedent evaluates to true
 *
 * @author Daniel Bergqvist Copyright 2018
 */
// /*public*/  class Antecedent extends AbstractDigitalExpression implements FemaleSocketListener {

//static final java.util.ResourceBundle rbx = java.util.ResourceBundle.getBundle("jmri.jmrit.conditional.ConditionalBundle");  // NOI18N


/**
 * Create a new instance of Antecedent with system name and user name.
 * @param sys the system name
 * @param user the user name
 */
/*public*/  Antecedent::Antecedent(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user, QObject *parent)
 : AbstractDigitalExpression(sys, user, parent)
{
    //super(sys, user);
    _expressionEntries
            .append(new ExpressionEntry(((DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName())));
}

/**
 * Create a new instance of Antecedent with system name and user name.
 * @param sys the system name
 * @param user the user name
 * @param expressionSystemNames a list of system names for the expressions
 * this antecedent uses
 */
/*public*/  Antecedent::Antecedent(/*@Nonnull*/ QString sys, /*@CheckForNull*/ QString user,
        QList<QMap<QString, QString>> expressionSystemNames, QObject *parent ) :AbstractDigitalExpression(sys, user, parent)
        /*throws BadUserNameException, BadSystemNameException*/ {
    //super(sys, user);
    setExpressionSystemNames(expressionSystemNames);
}

//@Override
/*public*/  Base* Antecedent::getDeepCopy(QMap<QString, QString> systemNames,QMap<QString, QString> userNames) /*throws JmriException */{
    DigitalExpressionManager* manager = (DefaultDigitalExpressionManager*)InstanceManager::getDefault("DigitalExpressionManager");
    QString sysName = systemNames.value(AbstractNamedBean::getSystemName());
    QString userName = userNames.value(AbstractNamedBean::getSystemName());
    if (sysName == "") sysName = manager->getAutoSystemName();
    Antecedent* copy = new Antecedent(sysName, userName);
    copy->AbstractNamedBean::setComment(AbstractNamedBean::getComment());
    copy->setNumSockets(getChildCount());
    copy->setAntecedent(_antecedent);
    return manager->registerExpression(copy)->deepCopyChildren(this, systemNames, userNames);
}

/*private*/ void Antecedent::setExpressionSystemNames(QList<QMap<QString, QString>> systemNames) {
    if (!_expressionEntries.isEmpty()) {
        throw new RuntimeException("expression system names cannot be set more than once");
    }

    for (QMap<QString, QString> map : systemNames) {
     QMapIterator<QString, QString> entry(map);
     while(entry.hasNext())
     {
      entry.next();
        FemaleDigitalExpressionSocket* socket =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, entry.key());

        _expressionEntries.append(new ExpressionEntry(socket, entry.value()));
     }
    }

}

/*public*/  QString Antecedent::getExpressionSystemName(int index) {
    return _expressionEntries.at(index)->_socketSystemName;
}

/** {@inheritDoc} */
//@Override
/*public*/  Category* Antecedent::getCategory() {
    return Category::COMMON;
}

/** {@inheritDoc} */
//@Override
/*public*/  bool Antecedent::evaluate()/* throws JmriException */{

    if (_antecedent.isEmpty()) {
        return false;
    }

    bool result;

    QByteArray ch = _antecedent.toLocal8Bit();
    int n = 0;
    for (int j = 0; j < ch.length(); j++) {
        if (ch[j] != ' ') {
            if (ch[j] == '{' || ch[j] == '[') {
                ch[j] = '(';
            } else if (ch[j] == '}' || ch[j] == ']') {
                ch[j] = ')';
            }
            ch[n++] = ch[j];
        }
    }
    try {
        QList<ExpressionEntry*> list = QList<ExpressionEntry*>();
        for (ExpressionEntry* e : _expressionEntries) {
            list.append(e);
        }
        DataPair* dp = parseCalculate( QString(ch/*, 0, n*/), list);
        result = dp->result;
    }
    catch (NumberFormatException*  nfe) {
        result = false;
        log->error(AbstractNamedBean::getDisplayName() + " parseCalculation error antecedent= " + _antecedent + ", ex= " + nfe->getMessage());  // NOI18N
    }
    catch ( IndexOutOfBoundsException* nfe) {
        result = false;
        log->error(AbstractNamedBean::getDisplayName() + " parseCalculation error antecedent= " + _antecedent + ", ex= " + nfe->getMessage());  // NOI18N
    }
    catch ( JmriException* nfe) {
        result = false;
        log->error(AbstractNamedBean::getDisplayName() + " parseCalculation error antecedent= " + _antecedent + ", ex= " + nfe->getMessage());  // NOI18N
    }

    return result;
}

//@Override
/*public*/  FemaleSocket* Antecedent::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException */{
    return _expressionEntries.at(index)->_socket;
}

//@Override
/*public*/  int Antecedent::getChildCount() {
    return _expressionEntries.size();
}

/*public*/  void Antecedent::setChildCount(int count) {
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
        FemaleDigitalExpressionSocket* socket =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, addList);
}

//@Override
/*public*/  QString Antecedent::getShortDescription(QLocale locale) {
    return tr(/*locale,*/ "Antecedent");
}

//@Override
/*public*/  QString Antecedent::getLongDescription(QLocale locale) {
    if (_antecedent.isEmpty()) {
        return tr(/*locale,*/ "Antecedent: empty");
    } else {
        return tr(/*locale,*/ "Antecedent: %1").arg(_antecedent);
    }
}

/*public*/  QString Antecedent::getAntecedent() {
    return _antecedent;
}

/*public*/  /*final*/ void Antecedent::setAntecedent(QString antecedent) /*throws JmriException */{
//        String result = validateAntecedent(antecedent, _expressionEntries);
//        if (result != null) System.out.format("DANIEL: Exception: %s%n", result);
//        if (result != null) throw new IllegalArgumentException(result);
    _antecedent = antecedent;
}

// This method ensures that we have enough of children
/*private*/ void Antecedent::setNumSockets(int num) {
    QVariantList addList = QVariantList();

    // Is there not enough children?
    while (_expressionEntries.size() < num) {
        FemaleDigitalExpressionSocket* socket =((DefaultDigitalExpressionManager*)
                                                InstanceManager::getDefault("DigitalExpressionManager"))
                        ->createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));
        addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    }
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void Antecedent::checkFreeSocket() {
    bool hasFreeSocket = false;

    for (ExpressionEntry* entry : _expressionEntries) {
        hasFreeSocket |= !entry->_socket->isConnected();
    }
    if (!hasFreeSocket) {
        FemaleDigitalExpressionSocket* socket =((DefaultDigitalExpressionManager*)
                InstanceManager::getDefault("DigitalExpressionManager"))
                                ->createFemaleSocket(this, this, getNewSocketName());
        _expressionEntries.append(new ExpressionEntry(socket));

        QVariantList list = QVariantList();
        list.append(VPtr<FemaleSocket>::asQVariant(socket));
        firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), list);
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  bool Antecedent::isSocketOperationAllowed(int index, FemaleSocketOperation::TYPES oper) {
    switch (oper) {
        case FemaleSocketOperation::Remove:        // Possible if socket is not connected
            return ! getChild(index)->isConnected();
        case FemaleSocketOperation::InsertBefore:
            return true;    // Always possible
        case FemaleSocketOperation::InsertAfter:
            return true;    // Always possible
        case FemaleSocketOperation::MoveUp:
            return index > 0;   // Possible if not first socket
        case FemaleSocketOperation::MoveDown:
            return index+1 < getChildCount();   // Possible if not last socket
        default:
            throw new UnsupportedOperationException("Oper is unknown" + FemaleSocketOperation::toString(oper));
    }
}

/*private*/ void Antecedent::insertNewSocket(int index) {
    FemaleDigitalExpressionSocket* socket =((DefaultDigitalExpressionManager*)
                                           InstanceManager::getDefault("DigitalExpressionManager"))
                    ->createFemaleSocket(this, this, getNewSocketName());
    _expressionEntries.insert(index, new ExpressionEntry(socket));

    QVariantList addList = QVariantList();
    addList.append(VPtr<FemaleSocket>::asQVariant(socket));
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, QVariant(), addList);
}

/*private*/ void Antecedent::removeSocket(int index) {
    QVariantList removeList = QVariantList();
    removeList.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    _expressionEntries.removeAt(index);
    firePropertyChange(Base::PROPERTY_CHILD_COUNT, removeList, QVariant());
}

/*private*/ void Antecedent::moveSocketDown(int index) {
    ExpressionEntry* temp = _expressionEntries.at(index);
    _expressionEntries.replace(index, _expressionEntries.at(index+1));
    _expressionEntries.replace(index+1, temp);

    QVariantList list = QVariantList();
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    list.append(VPtr<FemaleSocket>::asQVariant(_expressionEntries.at(index)->_socket));
    firePropertyChange(Base::PROPERTY_CHILD_REORDER, QVariant(), list);
}

/** {@inheritDoc} */
//@Override
/*public*/  void Antecedent::doSocketOperation(int index, FemaleSocketOperation::TYPES oper) {
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
/*public*/  void Antecedent::connected(FemaleSocket* socket) {
    if (disableCheckForUnconnectedSocket) return;

    for (ExpressionEntry* entry : _expressionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName =
                    socket->getConnectedSocket()->getSystemName();
        }
    }

    checkFreeSocket();
}

//@Override
/*public*/  void Antecedent::disconnected(FemaleSocket* socket) {
    for (ExpressionEntry* entry : _expressionEntries) {
        if (socket == entry->_socket) {
            entry->_socketSystemName = "";
            break;
        }
    }
}

/** {@inheritDoc} */
//@Override
/*public*/  void Antecedent::setup() {
    // We don't want to check for unconnected sockets while setup sockets
    disableCheckForUnconnectedSocket = true;

    for (ExpressionEntry* ee : _expressionEntries) {
        try {
            if ( !ee->_socket->isConnected()
                    || ee->_socket->getConnectedSocket()->getSystemName()
                            !=(ee->_socketSystemName)) {

                QString socketSystemName = ee->_socketSystemName;
                ee->_socket->_disconnect();
                if (socketSystemName != nullptr) {
                    MaleSocket* maleSocket =(MaleSocket*)((DefaultDigitalExpressionManager*)
                                             InstanceManager::getDefault("DigitalExpressionManager"))
                                    ->getBySystemName(socketSystemName);
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

    checkFreeSocket();

    disableCheckForUnconnectedSocket = false;
}



/**
 * Check that an antecedent is well formed.
 *
 * @param ant the antecedent string description
 * @param expressionEntryList arraylist of existing ExpressionEntries
 * @return error message string if not well formed
 * @throws jmri.JmriException when an exception occurs
 */
/*public*/  QString Antecedent::validateAntecedent(QString ant, QList<ExpressionEntry*> expressionEntryList) /*throws JmriException */{
    QByteArray ch = ant.toLocal8Bit();
    int n = 0;
    for (int j = 0; j < ch.length(); j++) {
        if (ch[j] != ' ') {
            if (ch[j] == '{' || ch[j] == '[') {
                ch[j] = '(';
            } else if (ch[j] == '}' || ch[j] == ']') {
                ch[j] = ')';
            }
            ch[n++] = ch[j];
        }
    }
    int count = 0;
    for (int j = 0; j < n; j++) {
        if (ch[j] == '(') {
            count++;
        }
        if (ch[j] == ')') {
            count--;
        }
    }
    if (count > 0) {
        return tr("Unmatched parenthesis, missing < %1 >.").arg(")");  // NOI18N
    }
    if (count < 0) {
        return tr("Unmatched parenthesis, missing < %1 >.").arg("(");  // NOI18N
    }
#if 0 // TODO:
    try {
        DataPair* dp = parseCalculate(new String(ch, 0, n), expressionEntryList);
        if (n != dp->indexCount) {
            return tr("Antecedent parsing error: Unexpected character found: < %1 >").arg(dp->indexCount - 1);  // NOI18N
        }
        int index = dp->argsUsed.nextClearBit(0);
        if (index >= 0 && index < expressionEntryList.size()) {
//                System.out.format("Daniel: ant: %s%n", ant);
            return java.text.MessageFormat.format(
                    rbx.getString("ParseError5"),  // NOI18N
                    new Object[]{expressionEntryList.size(), index + 1});
        }
    } catch (NumberFormatException | IndexOutOfBoundsException | JmriException nfe) {
        return rbx.getString("ParseError6") + nfe.getMessage();  // NOI18N
    }
#endif
    return nullptr;
}

/**
 * Parses and computes one parenthesis level of a boolean statement.
 * <p>
 * Recursively calls inner parentheses levels. Note that all logic operators
 * are detected by the parsing, therefore the internal negation of a
 * variable is washed.
 *
 * @param s            The expression to be parsed
 * @param expressionEntryList ExpressionEntries for R1, R2, etc
 * @return a data pair consisting of the truth value of the level a count of
 *         the indices consumed to parse the level and a bitmap of the
 *         variable indices used.
 * @throws jmri.JmriException if unable to compute the logic
 */
Antecedent::DataPair* Antecedent::parseCalculate(QString s, QList<ExpressionEntry*> expressionEntryList)
        /*throws JmriException */{

    // for simplicity, we force the string to upper case before scanning
    s = s.toUpper();

    BitSet* argsUsed = new BitSet(expressionEntryList.size());
    DataPair* dp = nullptr;
    bool leftArg = false;
    bool rightArg = false;
#if 0
    int oper = OPERATOR_NONE;
    int k = -1;
    int i = 0;      // index of String s
    //int numArgs = 0;
    if (s.at(i) == '(') {
        dp = parseCalculate(s.mid(++i), expressionEntryList);
        leftArg = dp->result;
        i += dp->indexCount;
        argsUsed->or(dp->argsUsed);
    } else // cannot be '('.  must be either leftArg or notleftArg
    {
        if (s.at(i) == 'R') {  // NOI18N
            try {
                k = Integer.parseInt(String.valueOf(s.substring(i + 1, i + 3)));
                i += 2;
            } catch (NumberFormatException | IndexOutOfBoundsException nfe) {
                k = Integer.parseInt(String.valueOf(s.charAt(++i)));
            }
            leftArg = expressionEntryList.get(k - 1)._socket->evaluate();
            i++;
            argsUsed.set(k - 1);
        } else if ("NOT".equals(s.substring(i, i + 3))) {  // NOI18N
            i += 3;

            // not leftArg
            if (s.at(i) == '(') {
                dp = parseCalculate(s.mid(++i), expressionEntryList);
                leftArg = dp->result;
                i += dp->indexCount;
                argsUsed.or(dp->argsUsed);
            } else if (s.at(i) == 'R') {  // NOI18N
                try {
              bool ok;
                    k = Integer.parseInt(String.valueOf(s.substring(i + 1, i + 3)));
                    i += 2;
                } catch (NumberFormatException | IndexOutOfBoundsException nfe) {
                    k = Integer.parseInt(String.valueOf(s.charAt(++i)));
                }
                leftArg = expressionEntryList.get(k - 1)._socket->evaluate();
                i++;
                argsUsed.set(k - 1);
            } else {
                throw new JmriException(java.text.MessageFormat.format(
                        rbx.getString("ParseError1"), new Object[]{s.substring(i)}));  // NOI18N
            }
            leftArg = !leftArg;
        } else {
            throw new JmriException(java.text.MessageFormat.format(
                    rbx.getString("ParseError9"), new Object[]{s}));  // NOI18N
        }
    }
    // crank away to the right until a matching parent is reached
    while (i < s.length()) {
        if (s.charAt(i) != ')') {
            // must be either AND or OR
            if ("AND".equals(s.substring(i, i + 3))) {  // NOI18N
                i += 3;
                oper = OPERATOR_AND;
            } else if ("OR".equals(s.substring(i, i + 2))) {  // NOI18N
                i += 2;
                oper = OPERATOR_OR;
            } else {
                throw new JmriException(java.text.MessageFormat.format(
                        rbx.getString("ParseError2"), new Object[]{s.substring(i)}));  // NOI18N
            }
            if (s.charAt(i) == '(') {
                dp = parseCalculate(s.substring(++i), expressionEntryList);
                rightArg = dp->result;
                i += dp->indexCount;
                argsUsed.or(dp->argsUsed);
            } else // cannot be '('.  must be either rightArg or notRightArg
            {
                if (s.charAt(i) == 'R') {  // NOI18N
                    try {
                        k = Integer.parseInt(String.valueOf(s.substring(i + 1, i + 3)));
                        i += 2;
                    } catch (NumberFormatException | IndexOutOfBoundsException nfe) {
                        k = Integer.parseInt(String.valueOf(s.charAt(++i)));
                    }
                    rightArg = expressionEntryList.get(k - 1)._socket->evaluate();
                    i++;
                    argsUsed.set(k - 1);
                } else if ("NOT".equals(s.substring(i, i + 3))) {  // NOI18N
                    i += 3;
                    // not rightArg
                    if (s.charAt(i) == '(') {
                        dp = parseCalculate(s.substring(++i), expressionEntryList);
                        rightArg = dp->result;
                        i += dp->indexCount;
                        argsUsed.or(dp->argsUsed);
                    } else if (s.charAt(i) == 'R') {  // NOI18N
                        try {
                            k = Integer.parseInt(String.valueOf(s.substring(i + 1, i + 3)));
                            i += 2;
                        } catch (NumberFormatException | IndexOutOfBoundsException nfe) {
                            k = Integer.parseInt(String.valueOf(s.charAt(++i)));
                        }
                        rightArg = expressionEntryList.get(k - 1)._socket->evaluate();
                        i++;
                        argsUsed.set(k - 1);
                    } else {
                        throw new JmriException(java.text.MessageFormat.format(
                                rbx.getString("ParseError3"), new Object[]{s.substring(i)}));  // NOI18N
                    }
                    rightArg = !rightArg;
                } else {
                    throw new JmriException(java.text.MessageFormat.format(
                            rbx.getString("ParseError9"), new Object[]{s.substring(i)}));  // NOI18N
                }
            }
            if (oper == OPERATOR_AND) {
                leftArg = (leftArg && rightArg);
            } else if (oper == OPERATOR_OR) {
                leftArg = (leftArg || rightArg);
            }
        } else {  // This level done, pop recursion
            i++;
            break;
        }
    }
    dp = new DataPair();
    dp->result = leftArg;
    dp->indexCount = i;
    dp->argsUsed = argsUsed;
#endif
    return dp;
}




/** {@inheritDoc} */
//@Override
/*public*/  void Antecedent::registerListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void Antecedent::unregisterListenersForThisClass() {
    // Do nothing
}

/** {@inheritDoc} */
//@Override
/*public*/  void Antecedent::disposeMe() {
}

/*private*/ /*final*/ /*static*/ Logger* Antecedent::log = LoggerFactory::getLogger("Antecedent");
