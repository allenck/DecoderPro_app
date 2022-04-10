#include "tableforeach.h"
#include "loggerfactory.h"
#include "defaultdigitalactionmanager.h"
#include "instancemanager.h"
#include "namedtablemanager.h"
#include "referenceutil.h"
#include "digitalactionmanager.h"
#include "runtimeexception.h"
#include "vptr.h"
#include "conditionalng.h"
#include "defaultnamedtablemanager.h"
#include "typeconversionutil.h"
#include "variable.h"
#include "recursivedescentparser.h"
/**
 * Executes an action when the expression is True.
 *
 * @author Daniel Bergqvist Copyright 2018
 */
///*public*/  class TableForEach extends AbstractDigitalAction
//        implements FemaleSocketListener, VetoableChangeListener {


    /*public*/  TableForEach::TableForEach(QString sys, QString user, QObject* parent) : AbstractDigitalAction(sys, user, parent) {
        //super(sys, user);
        setObjectName("TableForEach");
        _socket = ((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                ->createFemaleSocket(this, this, "A1");
    }

    //@Override
    /*public*/  Base* TableForEach::getDeepCopy(QMap<QString, QString>* systemNames, QMap<QString, QString>* userNames) /*throws JmriException*/ {
        DigitalActionManager* manager = (DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager");
        QString sysName = systemNames->value(getSystemName());
        QString userName = userNames->value(getSystemName());
        if (sysName == "") sysName = ((AbstractManager*)manager->mself())->getAutoSystemName();
        TableForEach* copy = new TableForEach(sysName, userName);
        copy->NamedBean::setComment(NamedBean::getComment());
        copy->setAddressing(_addressing);
        if(_tableHandle)
         copy->setTable(_tableHandle->getBean());
        copy->setTableReference(_tableReference);
        copy->setTableLocalVariable(_tableLocalVariable);
        copy->setTableFormula(_tableFormula);
        copy->setRowOrColumnAddressing(_rowOrColumnAddressing);
        copy->setRowOrColumn(_tableRowOrColumn);
        copy->setRowOrColumnName(_rowOrColumnName);
        copy->setLocalVariableName(_variableName);
        return manager->registerAction(copy)->deepCopyChildren(this, systemNames, userNames);
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  Category* TableForEach::getCategory() {
        return Category::COMMON;
    }

    /*private*/ QString TableForEach::getNewRowOrColumnName() /*throws JmriException*/ {

        switch (_rowOrColumnAddressing) {
            case NamedBeanAddressing::TYPE::Direct:
                return _rowOrColumnName;

            case NamedBeanAddressing::TYPE::Reference:
                return ReferenceUtil::getReference(
                        AbstractBase::getConditionalNG()->getSymbolTable(), _rowOrColumnReference);

            case NamedBeanAddressing::TYPE::LocalVariable:
            {
                SymbolTable* symbolTable = AbstractBase::getConditionalNG()->getSymbolTable();
                return TypeConversionUtil
                        ::convertToString(symbolTable->getValue(_rowOrColumnLocalVariable), false);
            }
            case NamedBeanAddressing::TYPE::Formula:
                return _rowOrColumnExpressionNode != nullptr
                        ? TypeConversionUtil::convertToString(
                                _rowOrColumnExpressionNode->calculate(
                                        AbstractBase::getConditionalNG()->getSymbolTable()), false)
                        : nullptr;

            default:
                throw new IllegalArgumentException("invalid _rowOrColumnAddressing state: " + NamedBeanAddressing::toString(_rowOrColumnAddressing));
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TableForEach::execute() /*throws JmriException */{
        Table* table;

//        System.out.format("TableForEach.execute: %s%n", getLongDescription());

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
                table = _tableHandle != nullptr ? _tableHandle->getBean() : nullptr;
                break;

            case NamedBeanAddressing::Reference:
            {
                QString ref = ReferenceUtil::getReference(
                        getConditionalNG()->getSymbolTable(), _tableReference);
                table = (Table*)((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))
                        ->getNamedBean(ref)->self();
                break;
            }
            case NamedBeanAddressing::LocalVariable:
            {
                SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();
                table = (Table*) ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))
                        ->getNamedBean(TypeConversionUtil::
                                convertToString(symbolTable->getValue(_tableLocalVariable), false))->self();
                break;
            }
            case NamedBeanAddressing::Formula:
                table = _tableExpressionNode != nullptr ?
                       (Table*) ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))
                                ->getNamedBean(TypeConversionUtil
                                        ::convertToString(_tableExpressionNode->calculate(
                                                getConditionalNG()->getSymbolTable()), false))->self()
                        : nullptr;
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

//        System.out.format("ActionTurnout.execute: turnout: %s%n", turnout);

        if (table == nullptr) {
//            log.error("turnout is null");
            return;
        }

        QString rowOrColumnName = getNewRowOrColumnName();

        if (rowOrColumnName == "") {
            log->error("rowOrColumnName is null");
            return;
        }
        if (rowOrColumnName.isEmpty()) {
            log->error("rowOrColumnName is empty string");
            return;
        }
        if (_variableName == "") {
            log->error("variableName is null");
            return;
        }
        if (!_socket->isConnected()) {
            log->error("socket is not connected");
            return;
        }

        SymbolTable* symbolTable = getConditionalNG()->getSymbolTable();

        if (_tableRowOrColumn == TableRowOrColumn::Row) {
            int row = table->getRowNumber(rowOrColumnName);
            for (int column=1; column <= table->numColumns(); column++) {
                // If the header is null or empty, treat the row as a comment
                QVariant header = table->getCell(0, column);
//                System.out.format("Row header: %s%n", header);
                if ((header != QVariant()) && (!header.toString().isEmpty())) {
                    symbolTable->setValue(_variableName, table->getCell(row, column));
//                    System.out.format("Variable: %s, value: %s%n", _variableName, table.getCell(row, column));
                     _socket->execute();
                }
            }
        } else {
            int column = table->getColumnNumber(rowOrColumnName);
            for (int row=1; row <= table->numRows(); row++) {
                // If the header is null or empty, treat the row as a comment
                QVariant header = table->getCell(row, 0);
//                System.out.format("Column header: %s%n", header);
                if ((header !=  QVariant()) && (!header.toString().isEmpty())) {
                    symbolTable->setValue(_variableName, table->getCell(row, column));
//                    System.out.format("Variable: %s, value: %s%n", _variableName, table.getCell(row, column));
                     _socket->execute();
                }
            }
        }
    }

    /*public*/  void TableForEach::setTable(/*@Nonnull*/ QString tableName) {
        assertListenersAreNotRegistered(log, "setTable");
        NamedTable* table = ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->getNamedTable(tableName);
        if (table != nullptr) {
            setTable(table);
        } else {
            removeTable();
            log->error(tr("turnout \"%1\" is not found").arg(tableName));
        }
    }

    /*public*/  void TableForEach::setAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _addressing = addressing;
        parseTableFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE TableForEach::getAddressing() {
        return _addressing;
    }

    /*public*/  void TableForEach::setTable(/*@Nonnull*/ NamedBeanHandle<NamedTable*>* handle) {
        assertListenersAreNotRegistered(log, "setTable");
        _tableHandle = handle;
        ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->VetoableChangeSupport::addVetoableChangeListener(this);
    }

    /*public*/  void TableForEach::setTable(/*@Nonnull*/ NamedTable* turnout) {
        assertListenersAreNotRegistered(log, "setTable");
        setTable(((NamedBeanHandleManager*)InstanceManager::getDefault("NamedBeanHandleManager"))->
                getNamedBeanHandle(((Turnout*)turnout)->getDisplayName(), turnout));
    }

    /*public*/  void TableForEach::removeTable() {
        assertListenersAreNotRegistered(log, "setTable");
        if (_tableHandle != nullptr) {
            ((DefaultNamedTableManager*)InstanceManager::getDefault("NamedTableManager"))->VetoableChangeSupport::removeVetoableChangeListener(this);
            _tableHandle = nullptr;
        }
    }

    /*public*/  NamedBeanHandle<NamedTable*>* TableForEach::getTable() {
        return _tableHandle;
    }

    /*public*/  void TableForEach::setTableReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _tableReference = reference;
    }

    /*public*/  QString TableForEach::getTableReference() {
        return _tableReference;
    }

    /*public*/  void TableForEach::setTableLocalVariable(/*@Nonnull*/ QString localVariable) {
        _tableLocalVariable = localVariable;
    }

    /*public*/  QString TableForEach::getTableLocalVariable() {
        return _tableLocalVariable;
    }

    /*public*/  void TableForEach::setTableFormula(/*@Nonnull*/ QString formula) /*throws ParserException */{
        _tableFormula = formula;
        parseTableFormula();
    }

    /*public*/  QString TableForEach::getTableFormula() {
        return _tableFormula;
    }

    /*private*/ void TableForEach::parseTableFormula() /*throws ParserException*/ {
        if (_addressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _tableExpressionNode = parser->parseExpression(_tableFormula);
        } else {
            _tableExpressionNode = nullptr;
        }
    }

    /**
     * Get tableRowOrColumn.
     * @return tableRowOrColumn
     */
    /*public*/  TableRowOrColumn::TYPE TableForEach::getRowOrColumn() {
        return _tableRowOrColumn;
    }

    /**
     * Set tableRowOrColumn.
     * @param tableRowOrColumn tableRowOrColumn
     */
    /*public*/  void TableForEach::setRowOrColumn(/*@Nonnull*/ TableRowOrColumn::TYPE tableRowOrColumn) {
        _tableRowOrColumn = tableRowOrColumn;
    }

    /*public*/  void TableForEach::setRowOrColumnAddressing(NamedBeanAddressing::TYPE addressing) /*throws ParserException*/ {
        _rowOrColumnAddressing = addressing;
        parseRowOrColumnFormula();
    }

    /*public*/  NamedBeanAddressing::TYPE TableForEach::getRowOrColumnAddressing() {
        return _rowOrColumnAddressing;
    }

    /**
     * Get name of row or column
     * @return name of row or column
     */
    /*public*/  QString TableForEach::getRowOrColumnName() {
        return _rowOrColumnName;
    }

    /**
     * Set name of row or column
     * @param rowOrColumnName name of row or column
     */
    /*public*/  void TableForEach::setRowOrColumnName(/*@Nonnull*/ QString rowOrColumnName) {
// TODO:        if (rowOrColumnName == "") throw new RuntimeException("Daniel");
        _rowOrColumnName = rowOrColumnName;
    }

    /*public*/  void TableForEach::setRowOrColumnReference(/*@Nonnull*/ QString reference) {
        if ((! reference.isEmpty()) && (! ReferenceUtil::isReference(reference))) {
            throw new IllegalArgumentException("The reference \"" + reference + "\" is not a valid reference");
        }
        _rowOrColumnReference = reference;
    }

    /*public*/  QString TableForEach::getRowOrColumnReference() {
        return _rowOrColumnReference;
    }

    /*public*/  void TableForEach::setRowOrColumnLocalVariable(/*@Nonnull*/ QString localVariable) {
        _rowOrColumnLocalVariable = localVariable;
    }

    /*public*/  QString TableForEach::getRowOrColumnLocalVariable() {
        return _rowOrColumnLocalVariable;
    }

    /*public*/  void TableForEach::setRowOrColumnFormula(/*@Nonnull*/ QString formula) /*throws ParserException*/ {
        _rowOrColumnFormula = formula;
        parseRowOrColumnFormula();
    }

    /*public*/  QString TableForEach::getRowOrColumnFormula() {
        return _rowOrColumnFormula;
    }

    /*private*/ void TableForEach::parseRowOrColumnFormula() /*throws ParserException*/ {
        if (_rowOrColumnAddressing == NamedBeanAddressing::Formula) {
            QMap<QString, Variable*> variables = QMap<QString, Variable*>();

            RecursiveDescentParser* parser = new RecursiveDescentParser(variables);
            _rowOrColumnExpressionNode = parser->parseExpression(_rowOrColumnFormula);
        } else {
            _rowOrColumnExpressionNode = nullptr;
        }
    }

    /**
     * Get name of local variable
     * @return name of local variable
     */
    /*public*/ QString TableForEach::getLocalVariableName() {
        return _variableName;
    }

    /**
     * Set name of local variable
     * @param localVariableName name of local variable
     */
    /*public*/  void TableForEach::setLocalVariableName(QString localVariableName) {
        _variableName = localVariableName;
    }

    //@Override
    /*public*/  void TableForEach::vetoableChange(PropertyChangeEvent* evt) /*throws java.beans.PropertyVetoException */{
        if ("CanDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<NamedTable>::asPtr(evt->getOldValue())) {
                if (VPtr<NamedTable>::asPtr(evt->getOldValue()) == (getTable()->getBean())) {
                    throw new PropertyVetoException(AbstractNamedBean::getDisplayName(), evt);
                }
            }
        } else if ("DoDelete" == (evt->getPropertyName())) { // No I18N
            if (VPtr<NamedTable>::asPtr(evt->getOldValue())) {
                if (VPtr<NamedTable>::asPtr(evt->getOldValue()) == (getTable()->getBean())) {
                    removeTable();
                }
            }
        }
    }

    //@Override
    /*public*/  FemaleSocket* TableForEach::getChild(int index) /*throws IllegalArgumentException, UnsupportedOperationException*/ {
        switch (index) {
            case 0:
                return _socket;

            default:
                throw new IllegalArgumentException(
                       tr("index has invalid value: %1").arg(index));
        }
    }

    //@Override
    /*public*/  int TableForEach::getChildCount() {
        return 1;
    }

    //@Override
    /*public*/  void TableForEach::connected(FemaleSocket* socket) {
        if (socket == _socket) {
            _socketSystemName = socket->getConnectedSocket()->getSystemName();
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/  void TableForEach::disconnected(FemaleSocket* socket) {
        if (socket == _socket) {
            _socketSystemName = nullptr;
        } else {
            throw new IllegalArgumentException("unkown socket");
        }
    }

    //@Override
    /*public*/  QString TableForEach::getShortDescription(QLocale locale) {
        return tr(/*locale,*/ "Table: For each");
    }

    //@Override
    /*public*/  QString TableForEach::getLongDescription(QLocale locale) {
        QString namedBean;
        QString rowOrColumnName;

        switch (_addressing) {
            case NamedBeanAddressing::Direct:
            {
                QString tableName;
                if (_tableHandle != nullptr) {
                    tableName = ((NamedBean*)_tableHandle->getBean())->getDisplayName();
                } else {
                    tableName = tr(/*locale, */"''");
                }
                namedBean = tr(/*locale, */"%1").arg(tableName);
                break;
            }
            case NamedBeanAddressing::Reference:
                namedBean = tr(/*locale, */"by reference %1").arg(_tableReference);
                break;

            case NamedBeanAddressing:: LocalVariable:
                namedBean =tr(/*locale, */"by local variable %1").arg(_tableLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                namedBean = tr(/*locale, */"by formula %1").arg(_tableFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _addressing state: " + NamedBeanAddressing::toString(_addressing));
        }

        switch (_rowOrColumnAddressing) {
            case NamedBeanAddressing::Direct:
                rowOrColumnName = tr(/*locale,*/ "%1").arg(_rowOrColumnName);
                break;

            case NamedBeanAddressing::Reference:
                rowOrColumnName = tr(/*locale, */"by reference %1").arg(_rowOrColumnReference);
                break;

            case NamedBeanAddressing::LocalVariable:
                rowOrColumnName =tr(/*locale, */"by local variable %1").arg(_rowOrColumnLocalVariable);
                break;

            case NamedBeanAddressing::Formula:
                rowOrColumnName = tr(/*locale,*/ "by formula %1").arg(_rowOrColumnFormula);
                break;

            default:
                throw new IllegalArgumentException("invalid _rowOrColumnAddressing state: " + NamedBeanAddressing::toString(_rowOrColumnAddressing));
        }

        return tr(/*locale, */"Table: For each %1 of %2 \"%3\" in table \"%4\" set variable \"%5\" and execute action %6").arg(
                TableRowOrColumn::toStringLowerCase(TableRowOrColumn::getOpposite(_tableRowOrColumn)),
                TableRowOrColumn::toStringLowerCase(_tableRowOrColumn),
                rowOrColumnName,
                namedBean,
                _variableName,
                 _socket->getName());
    }

    /*public*/  FemaleDigitalActionSocket* TableForEach::getSocket() {
        return _socket;
    }

    /*public*/  QString TableForEach::getSocketSystemName() {
        return _socketSystemName;
    }

    /*public*/  void TableForEach::setSocketSystemName(QString systemName) {
        _socketSystemName = systemName;
    }

    /** {@inheritDoc} */
   // @Override
    /*public*/  void TableForEach::setup() {
        try {
            if ( !_socket->isConnected()
                    ||  _socket->getConnectedSocket()->getSystemName()
                             != (_socketSystemName)) {

                QString socketSystemName = _socketSystemName;
                 _socket->_disconnect();
                if (socketSystemName != nullptr) {
                    MaleSocket* maleSocket =
                            (MaleSocket*)((DefaultDigitalActionManager*)InstanceManager::getDefault("DigitalActionManager"))
                                    ->getBySystemName(socketSystemName);
                     _socket->_disconnect();
                    if (maleSocket != nullptr) {
                         _socket->_connect(maleSocket);
                        maleSocket->setup();
                    } else {
                        log->error("cannot load digital action " + socketSystemName);
                    }
                }
            } else {
                 _socket->getConnectedSocket()->setup();
            }
        } catch (SocketAlreadyConnectedException ex) {
            // This shouldn't happen and is a runtime error if it does.
            throw new RuntimeException("socket is already connected");
        }
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TableForEach::registerListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TableForEach::unregisterListenersForThisClass() {
    }

    /** {@inheritDoc} */
    //@Override
    /*public*/  void TableForEach::disposeMe() {
    }


    /*private*/ /*final*/ /*static*/ Logger* TableForEach::log = LoggerFactory::getLogger("TableForEach");


